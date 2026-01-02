// Player Stats Monitor Example
// This script monitors and logs player statistics

class PlayerStatsMonitor
{
    private static ref array<ref PlayerStatsData> m_PlayerStats = new array<ref PlayerStatsData>;
    
    // Initialize the monitor
    static void Init()
    {
        Print("[PlayerStatsMonitor] Initialized");
        
        // Start periodic update
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(UpdateAllStats, 60000, true); // Every 60 seconds
    }
    
    // Track a player
    static void TrackPlayer(PlayerBase player)
    {
        if (!player) return;
        
        PlayerIdentity identity = player.GetIdentity();
        if (!identity) return;
        
        string uid = identity.GetId();
        
        // Check if already tracking
        PlayerStatsData existingData = GetPlayerData(uid);
        if (existingData)
        {
            Print("[PlayerStatsMonitor] Already tracking player: " + identity.GetName());
            return;
        }
        
        // Create new stats data
        PlayerStatsData data = new PlayerStatsData();
        data.uid = uid;
        data.name = identity.GetName();
        data.connectTime = GetGame().GetTime();
        m_PlayerStats.Insert(data);
        
        Print("[PlayerStatsMonitor] Now tracking: " + data.name);
    }
    
    // Stop tracking a player
    static void UntrackPlayer(string uid)
    {
        for (int i = 0; i < m_PlayerStats.Count(); i++)
        {
            if (m_PlayerStats[i].uid == uid)
            {
                Print("[PlayerStatsMonitor] Stopped tracking: " + m_PlayerStats[i].name);
                m_PlayerStats.Remove(i);
                return;
            }
        }
    }
    
    // Get player data
    static PlayerStatsData GetPlayerData(string uid)
    {
        foreach (PlayerStatsData data : m_PlayerStats)
        {
            if (data.uid == uid)
                return data;
        }
        return null;
    }
    
    // Update stats for all tracked players
    static void UpdateAllStats()
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (player && player.GetIdentity())
            {
                UpdatePlayerStats(player);
            }
        }
    }
    
    // Update stats for specific player
    static void UpdatePlayerStats(PlayerBase player)
    {
        if (!player || !player.GetIdentity()) return;
        
        string uid = player.GetIdentity().GetId();
        PlayerStatsData data = GetPlayerData(uid);
        
        if (!data) return;
        
        // Update survival stats
        data.health = player.GetHealth("", "Health");
        data.blood = player.GetHealth("", "Blood");
        data.shock = player.GetHealth("", "Shock");
        
        // Update status values
        data.energy = player.GetStatEnergy().Get();
        data.water = player.GetStatWater().Get();
        data.temperature = player.GetStatHeatComfort().Get();
        
        // Calculate play time
        data.playTime = (GetGame().GetTime() - data.connectTime) / 1000; // Convert to seconds
        
        // Update position
        data.lastPosition = player.GetPosition();
        
        // Update distance traveled
        if (data.previousPosition != "0 0 0")
        {
            float distance = vector.Distance(data.lastPosition, data.previousPosition);
            data.totalDistance += distance;
        }
        data.previousPosition = data.lastPosition;
    }
    
    // Print stats for a player
    static void PrintPlayerStats(PlayerBase player)
    {
        if (!player || !player.GetIdentity()) return;
        
        string uid = player.GetIdentity().GetId();
        PlayerStatsData data = GetPlayerData(uid);
        
        if (!data)
        {
            Print("[PlayerStatsMonitor] No data for player: " + player.GetIdentity().GetName());
            return;
        }
        
        UpdatePlayerStats(player); // Update before printing
        
        Print("=== Player Stats: " + data.name + " ===");
        Print("UID: " + data.uid);
        Print("Health: " + data.health);
        Print("Blood: " + data.blood);
        Print("Shock: " + data.shock);
        Print("Energy: " + data.energy);
        Print("Water: " + data.water);
        Print("Temperature: " + data.temperature);
        Print("Play Time: " + (data.playTime / 60) + " minutes");
        Print("Distance Traveled: " + data.totalDistance + " meters");
        Print("Position: " + data.lastPosition.ToString());
        Print("============================");
    }
    
    // Get stats summary
    static string GetStatsString(PlayerBase player)
    {
        if (!player || !player.GetIdentity()) return "";
        
        string uid = player.GetIdentity().GetId();
        PlayerStatsData data = GetPlayerData(uid);
        
        if (!data) return "";
        
        UpdatePlayerStats(player);
        
        string stats = "Health: " + Math.Round(data.health) + " | ";
        stats += "Blood: " + Math.Round(data.blood) + " | ";
        stats += "Energy: " + Math.Round(data.energy) + " | ";
        stats += "Water: " + Math.Round(data.water);
        
        return stats;
    }
}

// Data class to store player statistics
class PlayerStatsData
{
    string uid;
    string name;
    int connectTime;
    int playTime;
    
    float health;
    float blood;
    float shock;
    
    float energy;
    float water;
    float temperature;
    
    vector lastPosition;
    vector previousPosition;
    float totalDistance;
}

// Example integration in MissionServer:
/*
modded class MissionServer
{
    void MissionServer()
    {
        PlayerStatsMonitor.Init();
    }
    
    override void PlayerConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.PlayerConnect(player, identity);
        
        if (player && identity)
        {
            PlayerStatsMonitor.TrackPlayer(player);
        }
    }
    
    override void PlayerDisconnected(PlayerBase player, PlayerIdentity identity, string uid)
    {
        super.PlayerDisconnected(player, identity, uid);
        
        // Print final stats before disconnect
        if (player && identity)
        {
            PlayerStatsMonitor.PrintPlayerStats(player);
            PlayerStatsMonitor.UntrackPlayer(uid);
        }
    }
    
    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        
        // You can add periodic checks here if needed
    }
}

// Example admin command to view stats:
modded class PlayerBase
{
    void ShowMyStats()
    {
        PlayerStatsMonitor.PrintPlayerStats(this);
        MessageStatus(PlayerStatsMonitor.GetStatsString(this));
    }
}
*/
