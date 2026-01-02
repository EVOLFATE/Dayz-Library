# Script Examples

## Overview
This directory contains practical, working examples of common DayZ scripting tasks.

## Available Examples

### 1. simple-spawn-item.c
**Item spawning utilities**

Features:
- ✅ Spawn single items at specific locations
- ✅ Spawn items with random rotation
- ✅ Spawn items near players
- ✅ Spawn multiple items in a circle pattern
- ✅ Spawn items with specific health/quantity
- ✅ Spawn containers with items inside

Example usage:
```cpp
// Spawn AK-47 at coordinates
vector pos = "7500 0 5500";
pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
SimpleItemSpawner.SpawnItem("AKM", pos);

// Spawn items in circle (like airdrops)
SimpleItemSpawner.SpawnItemsInCircle("Apple", centerPos, 5.0, 8);

// Give player a gift
SimpleItemSpawner.SpawnItemNearPlayer(player, "WaterBottle", 1.5);
```

### 2. player-stats-monitor.c
**Player statistics tracking system**

Features:
- ✅ Track health, blood, shock
- ✅ Monitor energy, water, temperature
- ✅ Calculate play time
- ✅ Track distance traveled
- ✅ Position logging
- ✅ Auto-updating statistics
- ✅ Per-player data storage

Example usage:
```cpp
// Initialize monitoring
PlayerStatsMonitor.Init();

// Track a player
PlayerStatsMonitor.TrackPlayer(player);

// Print stats
PlayerStatsMonitor.PrintPlayerStats(player);

// Get stats as string
string stats = PlayerStatsMonitor.GetStatsString(player);
player.MessageStatus(stats);
```

Sample output:
```
=== Player Stats: PlayerName ===
UID: 76561198012345678
Health: 100
Blood: 5000
Shock: 0
Energy: 800
Water: 500
Temperature: 36.5
Play Time: 45 minutes
Distance Traveled: 2847 meters
Position: 7548.23, 315.67, 5612.45
============================
```

## Integration Examples

### In MissionServer:
```cpp
modded class MissionServer
{
    void MissionServer()
    {
        // Initialize systems
        PlayerStatsMonitor.Init();
    }
    
    override void PlayerConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.PlayerConnect(player, identity);
        
        // Track new player
        PlayerStatsMonitor.TrackPlayer(player);
        
        // Give welcome gift
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(
            GiveWelcomeGift, 1000, false, player
        );
    }
    
    void GiveWelcomeGift(PlayerBase player)
    {
        SimpleItemSpawner.SpawnItemNearPlayer(player, "WaterBottle", 1.5);
        player.MessageStatus("Welcome! Here's a gift!");
    }
}
```

## How to Use

1. **Copy the example file** to your mod's scripts directory
2. **Include in your mod** by importing the class
3. **Call the functions** from your mission or other scripts
4. **Modify as needed** for your specific use case

## File Structure
```
examples/scripts/
├── README.md                    (this file)
├── simple-spawn-item.c          (item spawning utilities)
└── player-stats-monitor.c       (player statistics tracking)
```

## Best Practices

- ✅ Test examples in a development environment first
- ✅ Review performance impact before production use
- ✅ Customize to match your server's needs
- ✅ Add error handling for your specific cases
- ✅ Log important events for debugging

## More Examples

For additional examples, see:
- [examples/killfeed/](../killfeed/) - Complete killfeed implementation
- [templates/script-templates/](../../templates/script-templates/) - Code templates
- [docs/scripting/](../../docs/scripting/) - Scripting documentation

## Contributing
Have useful examples to share? We'd love to include them!

Requirements:
- Well-commented code
- Working example usage
- Tested on current DayZ version
- Clear documentation

See [CONTRIBUTING.md](../../CONTRIBUTING.md) for guidelines.

---

**Status**: ✅ Active - 2 Examples Available  
**Last Updated**: January 2026  
**Contributions Welcome**: Yes!
