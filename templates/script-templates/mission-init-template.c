// DayZ Mission Server Init Template
// Place this in your mission's init.c file

void main()
{
    // Initialize random generator
    Math.Randomize(-1);
    
    // Load terrain (required)
    Hive ce = CreateHive();
    if (ce)
        ce.InitOffline();
    
    // Create weather system
    Weather weather = g_Game.GetWeather();
    
    // Set initial weather
    weather.MissionWeather(false);    // false = use weather from init.c
    
    weather.GetOvercast().Set(0.3, 1, 0);           // Overcast level (0-1)
    weather.GetRain().Set(0.0, 0, 0);               // Rain level (0-1)
    weather.GetFog().Set(0.1, 1, 0);                // Fog level (0-1)
    
    weather.GetOvercast().SetLimits(0.0, 1.0);
    weather.GetRain().SetLimits(0.0, 1.0);
    weather.GetFog().SetLimits(0.0, 0.25);
    
    weather.GetOvercast().SetForecastChangeLimits(0.2, 0.4);
    weather.GetRain().SetForecastChangeLimits(0.1, 0.3);
    weather.GetFog().SetForecastChangeLimits(0.1, 0.2);
    
    weather.GetOvercast().SetForecastTimeLimits(1800, 3600);
    weather.GetRain().SetForecastTimeLimits(600, 1200);
    weather.GetFog().SetForecastTimeLimits(1800, 3600);
    
    weather.GetOvercast().Set(0.3, 0, 0);
    weather.GetRain().Set(0.0, 0, 0);
    weather.GetFog().Set(0.1, 0, 0);
    
    weather.SetWindFunctionParams(0.1, 0.3, 50);
}

class CustomMission : MissionServer
{
    // Called when mission starts
    void CustomMission()
    {
        Print("[CustomMission] Mission initialized");
        
        // Initialize your custom systems here
    }
    
    // Called when server starts
    override void OnInit()
    {
        super.OnInit();
        Print("[CustomMission] OnInit called");
        
        // Server-specific initialization
    }
    
    // Called every frame
    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        
        // Update logic here (be careful with performance)
    }
    
    // Called when player connects
    override void PlayerConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.PlayerConnect(player, identity);
        
        if (player)
        {
            string playerName = identity.GetName();
            string playerID = identity.GetId();
            
            Print("[CustomMission] Player connected: " + playerName + " (" + playerID + ")");
            
            // Welcome message
            player.MessageStatus("Welcome to the server!");
        }
    }
    
    // Called when player disconnects
    override void PlayerDisconnected(PlayerBase player, PlayerIdentity identity, string uid)
    {
        super.PlayerDisconnected(player, identity, uid);
        
        if (identity)
        {
            Print("[CustomMission] Player disconnected: " + identity.GetName());
        }
    }
    
    // Called when player dies
    override void PlayerKilled(PlayerBase player, Object killer)
    {
        super.PlayerKilled(player, killer);
        
        if (player)
        {
            Print("[CustomMission] Player killed: " + player.GetIdentity().GetName());
            
            // Handle killfeed, death logging, etc.
            if (killer && killer.IsPlayer())
            {
                PlayerBase killerPlayer = PlayerBase.Cast(killer);
                Print("[CustomMission] Killer: " + killerPlayer.GetIdentity().GetName());
            }
        }
    }
    
    // Spawn player with custom loadout
    override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
    {
        super.StartingEquipSetup(player, clothesChosen);
        
        // Clear default inventory
        player.RemoveAllItems();
        
        // Add custom starting gear
        EntityAI itemTop = player.FindAttachmentBySlotName("Body");
        EntityAI itemBottom = player.FindAttachmentBySlotName("Legs");
        EntityAI itemShoes = player.FindAttachmentBySlotName("Feet");
        
        // Give clothing
        if (!itemTop)
        {
            player.GetInventory().CreateInInventory("TacticalShirt_Grey");
        }
        if (!itemBottom)
        {
            player.GetInventory().CreateInInventory("CargoPants_Grey");
        }
        if (!itemShoes)
        {
            player.GetInventory().CreateInInventory("AthleticShoes_Grey");
        }
        
        // Give starting items
        player.GetInventory().CreateInInventory("Rag");
        player.GetInventory().CreateInInventory("Apple");
        player.GetInventory().CreateInInventory("WaterBottle");
        player.GetInventory().CreateInInventory("Flashlight");
        player.GetInventory().CreateInInventory("Battery9V");
        
        // Give starting tool
        player.GetInventory().CreateInInventory("StoneKnife");
    }
}

// Register the custom mission
Mission CreateCustomMission(string path)
{
    return new CustomMission();
}
