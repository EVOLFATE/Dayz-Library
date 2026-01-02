# Helicopter Crash Events Guide

## Overview

Helicopter crash sites (helicrashes) are one of the most sought-after dynamic events in DayZ. These crashed military helicopters spawn high-tier weapons, military gear, and rare items, making them critical hotspots for player interaction and PvP encounters. This guide covers everything you need to know about configuring, customizing, and optimizing helicopter crash events on your server.

## Table of Contents
- [Introduction](#introduction)
- [How Helicrashes Work](#how-helicrashes-work)
- [Configuration Files](#configuration-files)
- [Event Parameters](#event-parameters)
- [Spawn Locations](#spawn-locations)
- [Loot Configuration](#loot-configuration)
- [Examples](#examples)
- [Best Practices](#best-practices)
- [Troubleshooting](#troubleshooting)
- [Advanced Customization](#advanced-customization)
- [Resources](#resources)

## Introduction

### What Are Helicopter Crashes?

Helicopter crash events spawn wrecked military helicopters at specific locations across the map. These events:
- Spawn **high-tier military loot** (M4, SVD, VSS, NVGs, plate carriers)
- Create **player interaction hotspots** (PvP/PvE)
- Have **limited lifetimes** (typically 30-60 minutes)
- Follow **Central Economy rules** (nominal, min, max spawning)
- Can spawn **infected** around the crash site (with mods)

### Why Configure Helicrashes?

- **Control loot rarity**: Adjust how many crashes exist simultaneously
- **Balance server economy**: Limit or increase high-tier gear availability
- **Create PvP zones**: More crashes = more player encounters
- **Customize spawn locations**: Add new crash sites in specific areas
- **Adjust respawn timing**: Control how often crashes appear

### Prerequisites

- DayZ Server with file access (FTP or local)
- Text editor (VS Code, Notepad++, or XML editor)
- Basic XML syntax knowledge
- Access to `mpmissions/[yourmap]/db/` folder

## How Helicrashes Work

### Central Economy System

Helicrashes are managed by DayZ's Central Economy (CE) system:

1. **Monitoring Phase**: CE checks active crash count every few minutes
2. **Spawn Decision**: If count < nominal, CE attempts to spawn new crash
3. **Location Selection**: Chooses from cfgeventspawns.xml (fixed) or random valid location
4. **Proximity Check**: Ensures crash is not within saferadius of another crash and distanceradius from players
5. **Object Spawning**: Spawns helicopter wreck model and loot containers
6. **Lifetime Countdown**: Crash persists for lifetime seconds
7. **Cleanup Phase**: After lifetime, all objects within cleanupradius are removed
8. **Restock Wait**: After restock seconds, new crash can spawn

### Event Lifecycle

```
Server Boot
    ↓
Load events.xml
    ↓
Check: Active crashes < nominal?
    ↓ YES
Select spawn location
    ↓
Validate: saferadius + distanceradius OK?
    ↓ YES
Spawn helicopter wreck + loot
    ↓
[Active for 'lifetime' seconds]
    ↓
Player discovers and loots
    ↓
Lifetime expires
    ↓
Cleanup all crash objects
    ↓
Wait 'restock' seconds
    ↓
Loop back to "Check active crashes"
```

### Crash Site Components

A typical helicrash spawns:
- **Helicopter wreck model**: UH1Y_Wreck, UH60_Wreck, or Mi8_Wreck
- **Loot containers**: AmmoBox, SeaChest, or spawned directly on ground
- **Ambient objects**: Debris, fire effects (with mods)
- **Infected** (optional, with mods): Military zombies, special infected

## Configuration Files

### Primary File: events.xml

**Location**: `mpmissions/dayzOffline.chernarusplus/db/events.xml`

This file defines all helicrash event rules. Look for event names like:
- `StaticHeliCrash` (Russian Mi-8 crash)
- `StaticHeliCrash_UH1Y` (American UH-1Y Venom crash)  
- `StaticHeliCrash_UH60` (American UH-60 Black Hawk crash - modded)

### Secondary File: cfgeventspawns.xml

**Location**: `mpmissions/dayzOffline.chernarusplus/db/cfgeventspawns.xml`

This file contains X, Z coordinates and rotation angle for each spawn location:

```xml
<event name="StaticHeliCrash">
    <pos x="7042.490234" z="9212.530273" a="-27"/>
    <pos x="4782.330078" z="10367.200195" a="134"/>
    <!-- More positions... -->
</event>
```

### Tertiary File: cfgeventgroups.xml (Optional)

**Location**: `mpmissions/dayzOffline.chernarusplus/db/cfgeventgroups.xml`

Defines what loot spawns at crash sites (usually already configured):

```xml
<group name="StaticHeliCrash_Loot">
    <item name="M4A1" chance="0.1"/>
    <item name="SVD" chance="0.05"/>
    <!-- More loot items... -->
</group>
```

## Event Parameters

### Complete Parameter Reference

```xml
<event name="StaticHeliCrash">
    <nominal>3</nominal>                    <!-- Target active crashes -->
    <min>1</min>                            <!-- Minimum guaranteed -->
    <max>5</max>                            <!-- Maximum allowed -->
    <lifetime>1800</lifetime>               <!-- Duration in seconds (30 min) -->
    <restock>0</restock>                    <!-- Respawn delay (0 = immediate) -->
    <saferadius>1000</saferadius>          <!-- Distance between crashes (meters) -->
    <distanceradius>500</distanceradius>    <!-- Min distance from players (meters) -->
    <cleanupradius>200</cleanupradius>      <!-- Cleanup area radius (meters) -->
    <flags deletable="0" init_random="1" remove_damaged="1"/>
    <position>fixed</position>              <!-- fixed or random -->
    <limit>child</limit>                    <!-- Spawn logic type -->
    <active>1</active>                      <!-- 1=enabled, 0=disabled -->
</event>
```

### Parameter Explanations

| Parameter | Description | Recommended Values |
|-----------|-------------|-------------------|
| **nominal** | Target number of active crashes | 2-4 (low pop), 3-6 (high pop) |
| **min** | Guaranteed minimum crashes | 1-2 |
| **max** | Hard cap on crashes | nominal + 2 to 4 |
| **lifetime** | How long crash persists (seconds) | 1800-3600 (30-60 min) |
| **restock** | Cooldown before respawn (seconds) | 0 (instant) or 1800-3600 (delay) |
| **saferadius** | Minimum distance between crashes | 1000-2000 (1-2 km) |
| **distanceradius** | Minimum distance from players | 500-1000 (prevents spawn on players) |
| **cleanupradius** | Area cleaned up | 150-250 (covers crash site) |

### Flags Explained

- **deletable="0"**: Crash won't be force-deleted by CE cleanup (recommended: 0)
- **init_random="1"**: Use random spawn selection from cfgeventspawns.xml (1 = random from list, 0 = sequential)
- **remove_damaged="1"**: Auto-remove ruined crash parts (recommended: 1)

## Spawn Locations

### Viewing Current Spawn Locations

To see where crashes can spawn, open `cfgeventspawns.xml` and look for your event name:

```xml
<event name="StaticHeliCrash">
    <pos x="7042.49" z="9212.53" a="-27"/>
    <!-- x = East/West, z = North/South, a = rotation angle -->
</event>
```

### Adding New Spawn Locations

**Step 1**: Get coordinates from map tool or in-game
- Use iZurvive.com to find coordinates
- Or use in-game admin tools to get current position
- Or extract from DayZ Editor

**Step 2**: Add to cfgeventspawns.xml
```xml
<event name="StaticHeliCrash">
    <!-- Existing spawns... -->
    <pos x="5000.00" z="8500.00" a="90"/>  <!-- Your new location -->
</event>
```

**Step 3**: Save, upload, and restart server

### Coordinate System

- **X axis**: West (0) to East (15360) on Chernarus+
- **Z axis**: South (0) to North (15360) on Chernarus+
- **a (angle)**: Rotation in degrees (0-360)
  - 0 = North
  - 90 = East
  - 180 = South
  - 270 = West
  - Negative values also work (-90 = 270)

### Recommended Spawn Areas

**High Traffic (PvP Hotspots)**:
- Northwest Airfield (NWAF): X:4500, Z:10500
- Tisy Military Base: X:1000, Z:14000
- Kamensk Military: X:7800, Z:14400

**Balanced Areas**:
- Central Fields: X:6000-8000, Z:7000-9000
- Northeast Wilderness: X:11000-13000, Z:13000-14000
- Western Forests: X:2000-4000, Z:6000-8000

**Low Traffic (Rare Loot)**:
- Deep South: X:10000-12000, Z:2000-4000
- Coastal Remote: X:14000-15000, Z:6000-9000
- Mountain Ranges: High elevation areas

## Loot Configuration

### Default Helicrash Loot

Vanilla DayZ helicrashes typically spawn:

**Weapons**:
- M4A1 (very rare)
- AKM (uncommon)
- SVD (rare)
- VSS (rare)
- LAR/FAL (rare)
- UMP45 (uncommon)

**Attachments**:
- ACOG Optic
- M4 Suppressor
- Various high-tier scopes
- Bipods, flashlights

**Gear**:
- Plate Carrier vest
- Combat helmet
- NVGs (night vision goggles)
- Ghillie suit pieces
- Military backpacks

**Ammo**:
- 5.56×45mm NATO
- 7.62×39mm
- 7.62×54mmR
- .308 Winchester

### Modifying Loot

To change what spawns at crashes, edit `cfgeventgroups.xml`:

```xml
<group name="StaticHeliCrash">
    <item name="M4A1" chance="0.15"/>        <!-- Increase M4 chance -->
    <item name="SVD" chance="0.08"/>         <!-- Increase SVD chance -->
    <item name="NVGoggles" chance="0.05"/>   <!-- Lower NVG chance -->
    <item name="MyCustomWeapon" chance="0.1"/> <!-- Add custom item -->
</group>
```

**chance** values:
- 0.0 = Never spawns
- 0.01 = 1% chance
- 0.10 = 10% chance
- 1.0 = Always spawns (not recommended for rare items)

## Examples

### Example 1: Low Population Server (Casual)
More crashes, longer lifetime, wider spacing:

```xml
<event name="StaticHeliCrash">
    <nominal>5</nominal>           <!-- More crashes for small player base -->
    <min>3</min>
    <max>7</max>
    <lifetime>3600</lifetime>      <!-- 1 hour lifetime -->
    <restock>0</restock>
    <saferadius>1500</saferadius>  <!-- Wider spacing OK -->
    <distanceradius>300</distanceradius>
    <cleanupradius>200</cleanupradius>
    <flags deletable="0" init_random="1" remove_damaged="1"/>
    <position>fixed</position>
    <limit>child</limit>
    <active>1</active>
</event>
```

### Example 2: High Population Server (Competitive)
Fewer crashes, shorter lifetime, strict spacing:

```xml
<event name="StaticHeliCrash">
    <nominal>2</nominal>           <!-- Rare, high value -->
    <min>1</min>
    <max>3</max>
    <lifetime>1800</lifetime>      <!-- 30 minutes -->
    <restock>1800</restock>        <!-- 30 min cooldown -->
    <saferadius>2000</saferadius>  <!-- Force wide spacing -->
    <distanceradius>750</distanceradius>
    <cleanupradius>200</cleanupradius>
    <flags deletable="0" init_random="1" remove_damaged="1"/>
    <position>fixed</position>
    <limit>child</limit>
    <active>1</active>
</event>
```

### Example 3: RP/PvE Server (Exploration)
Many crashes, long lifetime, clustered in PvE zones:

```xml
<event name="StaticHeliCrash">
    <nominal>8</nominal>           <!-- Lots of content -->
    <min>6</min>
    <max>10</max>
    <lifetime>5400</lifetime>      <!-- 90 minutes -->
    <restock>0</restock>
    <saferadius>800</saferadius>   <!-- Can be closer together -->
    <distanceradius>200</distanceradius>
    <cleanupradius>200</cleanupradius>
    <flags deletable="0" init_random="1" remove_damaged="1"/>
    <position>fixed</position>
    <limit>child</limit>
    <active>1</active>
</event>
```

### Example 4: Custom Map (Sakhal - New 1.26)
```xml
<event name="StaticHeliCrash">
    <nominal>4</nominal>
    <min>2</min>
    <max>6</max>
    <lifetime>2400</lifetime>      <!-- 40 minutes -->
    <restock>600</restock>         <!-- 10 min cooldown -->
    <saferadius>1200</saferadius>
    <distanceradius>600</distanceradius>
    <cleanupradius>200</cleanupradius>
    <flags deletable="0" init_random="1" remove_damaged="1"/>
    <position>fixed</position>
    <limit>child</limit>
    <active>1</active>
</event>
```

## Best Practices

### Server Population Balance
- **Low Pop (0-20 players)**: 4-6 crashes, 60+ min lifetime
- **Medium Pop (20-50 players)**: 3-5 crashes, 30-45 min lifetime
- **High Pop (50+ players)**: 2-4 crashes, 30 min lifetime, use restock delay

### Geographic Distribution
1. **Spread crashes across the map**: Don't cluster in one region
2. **Balance high/low traffic areas**: Mix safe and dangerous zones
3. **Consider travel time**: Place some crashes in remote areas
4. **Avoid player spawn zones**: Don't put crashes near coastal spawns

### Loot Economy Impact
1. **More crashes = more high-tier loot**: Affects server balance significantly
2. **Coordinate with types.xml**: Ensure crash loot aligns with overall economy
3. **Monitor player feedback**: Adjust if too easy/hard to get geared
4. **Test changes gradually**: Make small adjustments, observe effects

### Performance Considerations
1. **Limit max crashes**: Each crash = multiple objects (wreck, loot, debris)
2. **Use appropriate cleanup radius**: Too large = performance hit
3. **Monitor server FPS**: Check impact of crash events
4. **Consider map size**: Larger maps can support more events

### Configuration Management
1. **Backup before changes**: Always keep original files
2. **Document your changes**: Add XML comments explaining customizations
3. **Test locally first**: Use offline mode or test server
4. **Version control**: Track changes over time
5. **Coordinate with team**: If multiple admins, communicate changes

## Troubleshooting

### Crashes Not Spawning

**Symptom**: No helicopter crashes appearing on server

**Possible Causes & Solutions**:

1. **Event disabled**
   - Check `<active>1</active>` in events.xml
   - Solution: Set to 1 to enable

2. **No valid spawn locations**
   - Check cfgeventspawns.xml has coordinates
   - Solution: Add spawn positions (see [Spawn Locations](#spawn-locations))

3. **Proximity rules too strict**
   - saferadius or distanceradius preventing spawns
   - Solution: Reduce radius values temporarily to test

4. **Nominal/min/max misconfigured**
   - min > nominal or max < nominal
   - Solution: Ensure min ≤ nominal ≤ max

5. **Central Economy not running**
   - Server CE system crashed or disabled
   - Solution: Check server logs, restart server

### Too Many/Few Crashes

**Symptom**: Crash count doesn't match nominal setting

**Diagnosis**:
```
Check server console during CE cycles
Look for: "[CE] Spawning event: StaticHeliCrash"
```

**Solutions**:
1. **Too few crashes**:
   - Increase nominal and max values
   - Check if saferadius is preventing spawns (crashes too close together)
   - Add more spawn locations in cfgeventspawns.xml
   - Reduce distanceradius if players constantly nearby

2. **Too many crashes**:
   - Decrease nominal and max values
   - Check if multiple event types are active (UH1Y + Mi8)
   - Verify you're not running duplicate events

### Crashes Spawning Near Players

**Symptom**: Crashes appearing right next to players

**Solution**:
- Increase `<distanceradius>` value (try 750-1000)
- Verify distanceradius is actually set in XML
- Check for XML syntax errors

### Crashes Not Despawning

**Symptom**: Old crashes stay forever

**Solutions**:
1. **Check lifetime value**:
   - Ensure `<lifetime>` is set (not 0)
   - Typical: 1800-3600 seconds

2. **Check deletable flag**:
   - Set `deletable="1"` if you want CE to force-delete old crashes

3. **Manual cleanup**:
   - Delete `storage_1` folder in mission directory
   - Restart server (WARNING: Resets all persistence including bases!)

### Loot Not Spawning at Crashes

**Symptom**: Crash appears but no loot

**Solutions**:
1. **Check cfgeventgroups.xml**:
   - Verify crash has assigned loot group
   - Check item classnames are correct

2. **Verify types.xml**:
   - Ensure crash loot items have proper nominal values
   - Check items aren't disabled or set to 0

3. **Check children in events.xml**:
   - Some events use `<children>` tags to spawn containers
   - Verify syntax is correct

### Server Performance Issues

**Symptom**: FPS drops when crashes are active

**Solutions**:
1. Reduce nominal/max values
2. Decrease cleanup radius
3. Lower lifetime (less time objects persist)
4. Remove debris/effects (if modded)
5. Check for other heavy events running simultaneously

### XML Syntax Errors

**Symptom**: Server won't start, CE fails to load

**Solutions**:
1. **Validate XML**:
   - Use online XML validator
   - Check for unclosed tags
   - Verify quotes around attributes

2. **Common errors**:
   ```xml
   <!-- WRONG -->
   <event name=StaticHeliCrash>
   
   <!-- CORRECT -->
   <event name="StaticHeliCrash">
   ```

3. **Check server logs**:
   - Look for specific line numbers
   - Error messages point to problem area

## Advanced Customization

### Multiple Crash Types

Run different helicopter types simultaneously:

```xml
<!-- Russian Mi-8 crashes -->
<event name="StaticHeliCrash">
    <nominal>2</nominal>
    <!-- config -->
</event>

<!-- American UH-1Y crashes -->
<event name="StaticHeliCrash_UH1Y">
    <nominal>2</nominal>
    <!-- config -->
</event>
```

Each gets its own spawn locations and loot tables!

### Scripted Crash Events

For advanced control, use EnScript to spawn crashes programmatically:

```cpp
void SpawnHelicrashAt(vector position)
{
    // Spawn wreck
    Object wreck = GetGame().CreateObject("UH1Y_Wreck", position);
    
    // Spawn loot container
    vector lootPos = position + "2 0 2";
    Object container = GetGame().CreateObject("AmmoBox", lootPos);
    
    // Fill with loot
    ItemBase weapon = ItemBase.Cast(container.GetInventory().CreateInInventory("M4A1"));
    container.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
}
```

### Smoke/Fire Effects

Add visual markers (requires modding):

```cpp
// Spawn smoke particle at crash
Particle smoke = Particle.PlayOnObject(ParticleList.SMOKING_HELI_CRASH, wreck);

// Spawn fire light
EffectSound fire = SEffectManager.PlaySound("Fire_Burning", position);
```

### Infected Spawns at Crashes

Spawn zombies around crash sites (requires custom scripting or mods like Expansion):

```cpp
void SpawnInfectedAtCrash(vector crashPos, int count = 10)
{
    for (int i = 0; i < count; i++)
    {
        vector spawnPos = crashPos + Vector(Math.RandomFloat(-20,20), 0, Math.RandomFloat(-20,20));
        spawnPos[1] = GetGame().SurfaceY(spawnPos[0], spawnPos[2]);
        
        GetGame().CreateObject("ZmbM_SoldierNormal", spawnPos, false, true);
    }
}
```

### Dynamic Crash Spawning

Spawn crashes based on player activity or time:

```cpp
// Spawn crash every 2 hours
override void OnUpdate(float timeslice)
{
    super.OnUpdate(timeslice);
    
    m_Timer += timeslice;
    if (m_Timer >= 7200) // 2 hours
    {
        m_Timer = 0;
        SpawnRandomCrash();
    }
}
```

### Notification System

Alert players when crashes spawn (requires UI modding or Discord webhooks):

```cpp
void NotifyPlayersOfCrash(vector position)
{
    // In-game notification
    GetGame().GetMission().OnEvent(ChatMessageEventTypeID, 
        new ChatMessageEventParams(CCDirect, "", "Helicopter crash detected!", ""));
    
    // Discord webhook (with Universal API mod)
    string message = "🚁 Helicopter crash at " + position.ToString();
    SendDiscordWebhook(webhook_url, message);
}
```

### Map-Specific Configurations

Different configs for different maps:

**Chernarus+** (Large, 225km²):
- nominal: 3-4
- saferadius: 2000
- Many spawn locations

**Livonia** (Medium, 163km²):
- nominal: 2-3
- saferadius: 1500
- Moderate spawn locations

**Sakhal** (New, ~100km²):
- nominal: 2-3
- saferadius: 1000
- Focus on key areas

## Resources

### Official Documentation
- [Bohemia Wiki - Central Economy](https://community.bistudio.com/wiki/DayZ:Central_Economy)
- [DayZ Modding Basics](https://community.bistudio.com/wiki/DayZ:Modding_Basics)
- [Official Forums - Events Discussion](https://forums.dayz.com/)

### Community Tools
- **DayZ File Toolbox**: Visual event editor
  - URL: https://www.dayzfiletoolbox.com/events-hub
  - Features: Drag-and-drop event configuration
  
- **DZConfig Wiki**: Complete parameter reference
  - URL: https://dzconfig.com/wiki/events
  - Comprehensive attribute documentation

- **iZurvive**: Map coordinate tool
  - URL: https://www.izurvive.com/
  - Get precise spawn coordinates

- **DayZ Editor**: In-game coordinate extraction
  - Steam Workshop: Search "DayZ Editor"
  - Extract positions from placed objects

### Video Tutorials
- **Scalespeeder Gaming**: Console and PC setup guides
  - Helicrash configuration walkthroughs
  - Custom spawn location tutorials
  
- **WOBO**: Mechanics and optimization
  - Event system deep dives
  - Performance analysis

- **M1NDR**: Scripting and advanced topics
  - Custom event scripting
  - Mod integration

### Configuration Examples
- [Basic events.xml Template](../../templates/config-templates/)
- [Advanced Event Configurations](../../examples/)
- [Custom Event Scripts](../../examples/scripts/)

### Related Documentation
- [Events System Overview](./overview.md)
- [Static Events Guide](./static-events.md)
- [Dynamic Events Guide](./dynamic-events.md)
- [Police Car Events](./police-car.md)
- [Custom Events Guide](./custom-events.md)
- [types.xml Reference](../xml-configs/types-xml.md)
- [Server Configuration](../server/configuration.md)

### Community Resources
- [DayZ Modding Discord](../resources/community.md#discord-servers)
- [Reddit r/dayzservers](https://reddit.com/r/dayzservers)
- [Bohemia Forums](https://forums.dayz.com/)

### GitHub Repositories
- [Brandon10x15/DayZ-Modding](https://github.com/Brandon10x15/DayZ-Modding)
- [scalespeeder/DayZ-SAKHAL-Community-Server](https://github.com/scalespeeder/DayZ-SAKHAL-Community-Server-xml-Code-Snippets-To-Add-Heli-Crash-Sites-On-PC-and-Console-126-Update)
- Community event configurations and examples

## Summary

Helicopter crash events are a cornerstone of DayZ's high-tier loot economy and create exciting moments of risk and reward. By understanding the configuration parameters and spawn logic, you can:

**✅ Control server balance**: Adjust rarity of top-tier gear
**✅ Create hotspots**: Drive player interaction and PvP
**✅ Customize experience**: Tailor crashes to your server's playstyle  
**✅ Maintain performance**: Optimize for your hardware
**✅ Enhance gameplay**: Add variety and unpredictability

### Key Configuration Files
1. **events.xml**: Spawn rules, quantities, timers
2. **cfgeventspawns.xml**: Exact coordinates
3. **cfgeventgroups.xml**: Loot tables (optional)

### Critical Parameters
- **nominal**: How many crashes at once (2-4 recommended)
- **lifetime**: How long they last (1800-3600 seconds)
- **saferadius**: Distance apart (1000-2000m)
- **distanceradius**: Distance from players (500-1000m)

### Next Steps
1. Review your current events.xml configuration
2. Decide on crash quantity based on population
3. Add or adjust spawn locations
4. Test on local server before deploying
5. Monitor player feedback and adjust

---

**Last Updated**: January 2026  
**DayZ Version**: 1.26+ (includes Sakhal)  
**Platform**: PC (full support), Console (basic events.xml editing via Nitrado)  
**Difficulty**: Intermediate (XML editing, coordinate systems)

For questions, improvements, or contributions, see [CONTRIBUTING.md](../../CONTRIBUTING.md)

**Happy crash hunting! 🚁**
