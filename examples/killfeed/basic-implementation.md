# Basic Killfeed Implementation

## Overview

This is a complete, working implementation of a basic killfeed system for DayZ. It displays kill notifications in the chat and can be extended with graphical elements.

## Files Structure

```
@YourKillfeedMod/
├── Addons/
│   └── YourKillfeedMod.pbo
├── config.cpp
└── Scripts/
    ├── 4_World/
    │   ├── KillfeedManager.c
    │   └── KillfeedConfig.c
    ├── 5_Mission/
    │   └── MissionGameplay.c
    └── 3_Game/
        └── PlayerBase.c
```

## Implementation

### 1. KillfeedConfig.c
```javascript
class KillfeedConfig
{
    // Display settings
    static bool ENABLED = true;
    static bool SHOW_WEAPON = true;
    static bool SHOW_DISTANCE = true;
    static bool SHOW_HEADSHOT = true;
    static float MESSAGE_LIFETIME = 8.0; // seconds
    
    // Filter settings
    static bool SHOW_SUICIDE = false;
    static bool SHOW_ENVIRONMENT_DEATHS = false;
    static bool SHOW_AI_KILLS = true;
    
    // Color settings (ARGB format)
    static int COLOR_KILLER = 0xFFFF5555;   // Red
    static int COLOR_VICTIM = 0xFFAAAAAA;   // Gray
    static int COLOR_WEAPON = 0xFFFFFF55;   // Yellow
    static int COLOR_INFO = 0xFF55FF55;     // Green
}
```

### 2. KillfeedManager.c
```javascript
class KillfeedManager
{
    private static ref KillfeedManager instance;
    
    // Singleton pattern
    static KillfeedManager GetInstance()
    {
        if (!instance)
        {
            instance = new KillfeedManager();
        }
        return instance;
    }
    
    // Process kill event
    void ProcessKillEvent(PlayerBase killer, PlayerBase victim, string weapon, float distance, bool is_headshot)
    {
        if (!KillfeedConfig.ENABLED)
            return;
            
        // Filter suicides
        if (killer == victim && !KillfeedConfig.SHOW_SUICIDE)
            return;
            
        // Build message
        string message = BuildKillMessage(killer, victim, weapon, distance, is_headshot);
        
        // Send to all clients
        BroadcastMessage(message);
    }
    
    // Build formatted message
    private string BuildKillMessage(PlayerBase killer, PlayerBase victim, string weapon, float distance, bool is_headshot)
    {
        string message = "";
        
        if (killer && victim)
        {
            string killer_name = killer.GetIdentity().GetName();
            string victim_name = victim.GetIdentity().GetName();
            
            // Basic format: "Killer killed Victim"
            message = killer_name + " killed " + victim_name;
            
            // Add weapon info
            if (KillfeedConfig.SHOW_WEAPON && weapon != "")
            {
                message += " with " + weapon;
            }
            
            // Add distance info
            if (KillfeedConfig.SHOW_DISTANCE && distance > 0)
            {
                message += " [" + Math.Round(distance).ToString() + "m]";
            }
            
            // Add headshot indicator
            if (KillfeedConfig.SHOW_HEADSHOT && is_headshot)
            {
                message += " (Headshot)";
            }
        }
        else if (victim)
        {
            // Environmental death or suicide
            string victim_name = victim.GetIdentity().GetName();
            message = victim_name + " died";
        }
        
        return message;
    }
    
    // Broadcast message to all clients
    private void BroadcastMessage(string message)
    {
        // Get all players
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        
        // Send to each player
        foreach (Man player : players)
        {
            if (player && player.GetIdentity())
            {
                // Send RPC to client
                SendKillfeedMessage(player.GetIdentity(), message);
            }
        }
    }
    
    // RPC to send message to specific client
    private void SendKillfeedMessage(PlayerIdentity identity, string message)
    {
        auto ctx = new Param1<string>(message);
        GetGame().RPCSingleParam(null, ERPCs.RPC_USER_ACTION_MESSAGE, ctx, true, identity);
    }
    
    // Calculate distance between two entities
    float CalculateDistance(EntityAI ent1, EntityAI ent2)
    {
        if (!ent1 || !ent2)
            return 0;
            
        vector pos1 = ent1.GetPosition();
        vector pos2 = ent2.GetPosition();
        
        return vector.Distance(pos1, pos2);
    }
    
    // Determine weapon used
    string GetWeaponName(PlayerBase player)
    {
        if (!player)
            return "";
            
        Weapon_Base weapon = Weapon_Base.Cast(player.GetHumanInventory().GetEntityInHands());
        if (weapon)
        {
            return weapon.GetDisplayName();
        }
        
        return "Unknown";
    }
    
    // Check if kill was a headshot
    bool CheckHeadshot(PlayerBase victim, string hit_component)
    {
        // Common head component names
        if (hit_component.Contains("Head") || hit_component.Contains("head") || 
            hit_component.Contains("Brain") || hit_component.Contains("brain"))
        {
            return true;
        }
        
        return false;
    }
}
```

### 3. PlayerBase.c (Modded)
```javascript
modded class PlayerBase
{
    private string m_LastHitComponent = "";
    
    // Override damage handler to track hit components
    override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
        super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
        
        // Store hit component for headshot detection
        m_LastHitComponent = dmgZone;
    }
    
    // Override death event
    override void EEKilled(Object killer)
    {
        super.EEKilled(killer);
        
        // Server-side only
        if (GetGame().IsServer())
        {
            ProcessDeath(killer);
        }
    }
    
    // Process death and send to killfeed
    private void ProcessDeath(Object killer)
    {
        PlayerBase killer_player = null;
        string weapon_name = "";
        float distance = 0;
        bool is_headshot = false;
        
        // Check if killer is a player
        if (killer && killer.IsPlayer())
        {
            killer_player = PlayerBase.Cast(killer);
            
            if (killer_player)
            {
                // Get weapon info
                weapon_name = KillfeedManager.GetInstance().GetWeaponName(killer_player);
                
                // Calculate distance
                distance = KillfeedManager.GetInstance().CalculateDistance(killer_player, this);
                
                // Check headshot
                is_headshot = KillfeedManager.GetInstance().CheckHeadshot(this, m_LastHitComponent);
            }
        }
        
        // Send to killfeed system
        KillfeedManager.GetInstance().ProcessKillEvent(killer_player, this, weapon_name, distance, is_headshot);
    }
}
```

### 4. Config.cpp
```cpp
class CfgPatches
{
    class YourKillfeedMod
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Scripts"};
    };
};

class CfgMods
{
    class YourKillfeedMod
    {
        dir = "YourKillfeedMod";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        name = "Your Killfeed Mod";
        credits = "YourName";
        author = "YourName";
        authorID = "0";
        version = "1.0";
        extra = 0;
        type = "mod";
        
        dependencies[] = {"Game", "World", "Mission"};
        
        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"YourKillfeedMod/Scripts/3_Game"};
            };
            
            class worldScriptModule
            {
                value = "";
                files[] = {"YourKillfeedMod/Scripts/4_World"};
            };
            
            class missionScriptModule
            {
                value = "";
                files[] = {"YourKillfeedMod/Scripts/5_Mission"};
            };
        };
    };
};
```

## Installation

### For Server Owners

1. **Pack the mod**:
   ```bash
   # Use PBO Manager or Mikero's Tools
   makepbo -N YourKillfeedMod @YourKillfeedMod
   ```

2. **Upload to server**:
   ```
   Place @YourKillfeedMod folder in server root
   ```

3. **Add to startup**:
   ```
   -mod=@YourKillfeedMod
   ```

4. **Restart server**

### For Players (if client-side required)

1. **Subscribe on Workshop**
2. **Enable in DayZ Launcher**
3. **Join server**

## Testing

### In-Game Testing

1. Start your server with the mod
2. Join with 2+ players
3. Have one player kill another
4. Verify message appears in chat

### Expected Output
```
Player1 killed Player2 with M4A1 [350m] (Headshot)
Player3 killed Player4 with Mosin [45m]
Player5 died
```

## Customization

### Change Message Format

Edit `BuildKillMessage()` in KillfeedManager.c:

```javascript
// Custom format
message = "💀 " + killer_name + " eliminated " + victim_name + " 💀";
```

### Add Kill Streak Tracking

```javascript
class KillfeedManager
{
    private ref map<string, int> m_KillStreaks;
    
    void TrackKillStreak(string player_id)
    {
        if (!m_KillStreaks)
            m_KillStreaks = new map<string, int>;
            
        int current_streak = m_KillStreaks.Get(player_id);
        current_streak++;
        m_KillStreaks.Set(player_id, current_streak);
        
        // Announce streak milestones
        if (current_streak == 5)
        {
            BroadcastMessage(player_id + " is on a killing spree! (5 kills)");
        }
    }
}
```

### Filter by Distance

```javascript
// Only show kills over 100m
if (distance > 100)
{
    BroadcastMessage(message);
}
```

## Common Issues

### Issue: Messages not appearing
**Solution**: Check server logs for RPC errors

### Issue: Duplicate messages
**Solution**: Ensure code only runs server-side

### Issue: Wrong weapon name
**Solution**: Verify GetWeaponName() logic

## Next Steps

- [Add Graphical UI](graphical-killfeed.md)
- [Discord Integration](discord-integration.md)
- [Advanced Features](../killfeed/advanced-features.md)
- [Performance Optimization](../killfeed/performance.md)

## Complete Example Repository

Download complete working examples:
- [Basic Killfeed](../../examples/killfeed/basic-killfeed/)
- [Advanced Killfeed](../../examples/killfeed/advanced-killfeed/)
- [Graphical Killfeed](../../examples/killfeed/graphical-killfeed/)
