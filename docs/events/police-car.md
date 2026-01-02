# Police Car Event Configuration Guide

## Overview

Police car events spawn police vehicles at designated locations across the map, providing civilian/police-tier loot and creating points of interest for players. These static vehicle spawns are easier to configure than dynamic helicrashes and serve as excellent early-game loot opportunities or roadblock scenarios.

## Table of Contents
- [Introduction](#introduction)
- [How Police Car Events Work](#how-police-car-events-work)
- [Configuration Files](#configuration-files)
- [Event Setup Guide](#event-setup-guide)
- [Vehicle Types](#vehicle-types)
- [Loot Configuration](#loot-configuration)
- [Examples](#examples)
- [Best Practices](#best-practices)
- [Troubleshooting](#troubleshooting)
- [Advanced Scenarios](#advanced-scenarios)
- [Resources](#resources)

## Introduction

### What Are Police Car Events?

Police car events are static vehicle spawns that:
- Spawn **police vehicles** at fixed locations (checkpoints, stations, roads)
- Contain **police/civilian loot** (pistols, police uniforms, basic supplies)
- Have **configurable lifetimes** (how long vehicle persists)
- Can spawn **with or without parts** (wheels, battery, spark plug)
- Provide **early-game content** for coastal and inland areas

### Why Configure Police Car Events?

- **Add vehicle spawns**: Increase vehicle availability on your server
- **Create roadblocks**: Simulate police checkpoints or abandoned scenes
- **Distribute loot**: Police gear at strategic locations
- **Enhance immersion**: Crashed or abandoned police vehicles tell stories
- **Balance travel**: Give players vehicle options in specific areas

### Prerequisites

- DayZ Server with file access
- Text editor (VS Code, Notepad++, or XML editor)
- Basic XML syntax knowledge
- Access to `mpmissions/[yourmap]/db/` folder
- Vehicle classnames knowledge (for mods)

## How Police Car Events Work

### Event System Integration

Police car events use the same Central Economy system as helicrashes:

1. **Server Boot**: Loads events.xml configuration
2. **Spawn Check**: Checks if police car event is active and below nominal
3. **Location Selection**: Uses fixed coordinates from cfgeventspawns.xml
4. **Vehicle Spawn**: Spawns police car at specified position
5. **Attachments/Loot**: Adds wheels, parts, and inventory items (if configured)
6. **Lifetime**: Vehicle persists for specified duration
7. **Cleanup**: After lifetime, vehicle and nearby objects are removed
8. **Restock**: After restock delay, new vehicle can spawn

### Differences from Helicrashes

| Aspect | Helicrash | Police Car |
|--------|-----------|------------|
| **Movement** | Static object (wreck) | Functional vehicle |
| **Player Use** | Loot only | Can be driven |
| **Spawn Logic** | Often random | Usually fixed locations |
| **Loot Tier** | Military (high) | Civilian/Police (low-mid) |
| **Despawn** | After lifetime | After lifetime or if moved far |

## Configuration Files

### Primary File: events.xml

**Location**: `mpmissions/dayzOffline.chernarusplus/db/events.xml`

Add or modify police car event block:

```xml
<event name="VehiclePoliceOffroad">
    <nominal>1</nominal>
    <min>1</min>
    <max>1</max>
    <lifetime>3600</lifetime>
    <restock>0</restock>
    <saferadius>10</saferadius>
    <distanceradius>3</distanceradius>
    <cleanupradius>250</cleanupradius>
    <flags deletable="0" init_random="0" remove_damaged="1"/>
    <position>fixed</position>
    <limit>child</limit>
    <active>1</active>
    <children>
        <child type="CivilianSedan_Police" min="1" max="1" lootmax="0" lootmin="0"/>
    </children>
</event>
```

### Secondary File: cfgeventspawns.xml

**Location**: `mpmissions/dayzOffline.chernarusplus/db/cfgeventspawns.xml`

Define exact spawn coordinates:

```xml
<event name="VehiclePoliceOffroad">
    <pos x="5682.47" z="11906.29" a="-27"/>
    <pos x="3842.15" z="8901.33" a="90"/>
    <!-- Add more positions as needed -->
</event>
```

### Tertiary File: cfgspawnabletypes.xml (Optional)

**Location**: `mpmissions/dayzOffline.chernarusplus/db/cfgspawnabletypes.xml`

Configure vehicle attachments and cargo:

```xml
<type name="CivilianSedan_Police">
    <attachments chance="0.80">
        <item name="CarWheel" chance="0.90" />
        <item name="CarBattery" chance="0.70" />
        <item name="SparkPlug" chance="0.60" />
        <item name="CarRadiator" chance="0.85" />
    </attachments>
    <cargo chance="0.40">
        <item name="Pistol_CZ75" chance="0.20" />
        <item name="Mag_CZ75_15Rnd" chance="0.30" />
        <item name="PoliceJacket" chance="0.25" />
        <item name="PoliceCap" chance="0.20" />
    </cargo>
</type>
```

### Quaternary File: cfgeconomycore.xml (For Custom Events)

If creating custom events file:

```xml
<ce folder="custom">
    <file name="events_Custom.xml" type="events"/>
</ce>
```

## Event Setup Guide

### Step 1: Choose Vehicle Type

Determine which police vehicle to spawn:

**Vanilla Options**:
- `CivilianSedan_Police` (Police sedan - most common)
- `OffroadHatchback_Police` (Police hatchback)
- `Sedan_02_Police` (Alternative police sedan)

**Modded Options** (requires mods):
- `ExpansionPolice` (Expansion mod police vehicles)
- Custom police vehicles from Workshop

### Step 2: Get Spawn Coordinates

**Option A: Use iZurvive Map**
1. Go to https://www.izurvive.com/
2. Select your map (Chernarus+, Livonia, Sakhal)
3. Click desired location
4. Note X and Z coordinates
5. Choose rotation angle (0-360 degrees)

**Option B: Use In-Game Admin Tools**
1. Install admin tools mod
2. Teleport to desired location
3. Use position command to get coordinates
4. Note XYZ position

**Option C: Use DayZ Editor**
1. Install DayZ Editor from Workshop
2. Place object at desired location
3. Export position
4. Extract X, Z, and angle from export

### Step 3: Configure events.xml

Add event definition to events.xml:

```xml
<event name="VehiclePoliceOffroad">
    <nominal>3</nominal>                <!-- Number of police cars -->
    <min>2</min>
    <max>4</max>
    <lifetime>7200</lifetime>           <!-- 2 hours -->
    <restock>0</restock>
    <saferadius>500</saferadius>        <!-- Distance from other events -->
    <distanceradius>50</distanceradius> <!-- Distance from players -->
    <cleanupradius>250</cleanupradius>
    <flags deletable="0" init_random="0" remove_damaged="1"/>
    <position>fixed</position>
    <limit>child</limit>
    <active>1</active>
    <children>
        <child type="CivilianSedan_Police" min="1" max="1"/>
    </children>
</event>
```

### Step 4: Add Spawn Locations

Edit cfgeventspawns.xml:

```xml
<event name="VehiclePoliceOffroad">
    <!-- Police Station in Elektro -->
    <pos x="10458.5" z="2287.3" a="180"/>
    
    <!-- Checkpoint on main road -->
    <pos x="7523.8" z="5142.6" a="90"/>
    
    <!-- Crashed on roadside -->
    <pos x="6234.9" z="7821.1" a="-45"/>
</event>
```

**Important**: Positions must be at least 25 meters apart for proper spawning

### Step 5: Configure Vehicle Condition (Optional)

Edit cfgspawnabletypes.xml to control vehicle state:

**Fully Functional Vehicle**:
```xml
<type name="CivilianSedan_Police">
    <attachments chance="1.0">
        <item name="CarWheel" chance="1.0" />
        <item name="CarBattery" chance="1.0" />
        <item name="SparkPlug" chance="1.0" />
        <item name="CarRadiator" chance="1.0" />
    </attachments>
</type>
```

**Damaged/Missing Parts** (requires repair):
```xml
<type name="CivilianSedan_Police">
    <attachments chance="0.60">
        <item name="CarWheel" chance="0.50" />
        <item name="CarBattery" chance="0.30" />
        <item name="SparkPlug" chance="0.25" />
        <item name="CarRadiator" chance="0.70" />
    </attachments>
</type>
```

### Step 6: Test and Deploy

1. **Backup files**: Save original XML files
2. **Upload changes**: Transfer to server via FTP
3. **Restart server**: Full restart required to load new configuration
4. **Test in-game**: Visit spawn locations to verify
5. **Adjust as needed**: Fine-tune based on observations

## Vehicle Types

### Vanilla Police Vehicles

#### CivilianSedan_Police
- **Type**: 4-door sedan
- **Seats**: 4 passengers
- **Speed**: Medium
- **Fuel Capacity**: 40L
- **Common Spawn**: Police stations, checkpoints

#### OffroadHatchback_Police  
- **Type**: 2-door hatchback
- **Seats**: 2 passengers
- **Speed**: Medium-Fast
- **Fuel Capacity**: 30L
- **Common Spawn**: Rural police posts

#### Sedan_02_Police
- **Type**: Alternative sedan model
- **Seats**: 4 passengers
- **Speed**: Medium
- **Fuel Capacity**: 40L
- **Common Spawn**: Urban areas

### Modded Vehicles (Examples)

With mods like **DayZ Expansion**, you can spawn:
- `ExpansionPoliceUAZ` (Russian police SUV)
- `ExpansionPoliceLada` (Soviet police car)
- `ExpansionPoliceBus` (Riot control vehicle)
- Custom police vehicles from Workshop mods

## Loot Configuration

### Default Police Vehicle Loot

Police cars typically contain:

**Weapons**:
- CZ 75 (pistol)
- 1911 (pistol)
- CR-61 Skorpion (SMG - rare)
- Glock (with mods)

**Ammunition**:
- 9x19mm
- .45 ACP
- 9x18mm Makarov

**Clothing**:
- Police Jacket
- Police Pants
- Police Cap
- Traffic Vest
- Patrol boots

**Equipment**:
- Handcuffs
- Radio
- Flashlight
- Batteries
- Road flares
- Megaphone (with mods)

**Medical**:
- Bandages
- Tetracycline (pills)
- Painkillers
- First Aid Kit (rare)

### Customizing Loot

Edit cfgspawnabletypes.xml cargo section:

```xml
<type name="CivilianSedan_Police">
    <cargo chance="0.60">
        <!-- Weapons (lower chance) -->
        <item name="CZ75" chance="0.15" />
        <item name="Mag_CZ75_15Rnd" chance="0.25" />
        
        <!-- Clothing (medium chance) -->
        <item name="PoliceJacket" chance="0.30" />
        <item name="PolicePants" chance="0.30" />
        <item name="PoliceCap" chance="0.20" />
        
        <!-- Equipment (higher chance) -->
        <item name="Handcuffs" chance="0.40" />
        <item name="PersonalRadio" chance="0.35" />
        <item name="Flashlight" chance="0.50" />
        <item name="Battery9V" chance="0.45" />
        
        <!-- Medical (medium chance) -->
        <item name="Bandage_Dressed" chance="0.35" />
        <item name="TetracyclineAntibiotics" chance="0.20" />
    </cargo>
</type>
```

## Examples

### Example 1: Checkpoint Roadblock
Police car at major intersection:

```xml
<!-- events.xml -->
<event name="VehiclePoliceCheckpoint">
    <nominal>2</nominal>
    <min>2</min>
    <max>2</max>
    <lifetime>7200</lifetime>
    <restock>0</restock>
    <saferadius>1000</saferadius>
    <distanceradius>100</distanceradius>
    <cleanupradius>300</cleanupradius>
    <flags deletable="0" init_random="0" remove_damaged="1"/>
    <position>fixed</position>
    <limit>child</limit>
    <active>1</active>
    <children>
        <child type="CivilianSedan_Police" min="1" max="1"/>
    </children>
</event>
```

```xml
<!-- cfgeventspawns.xml -->
<event name="VehiclePoliceCheckpoint">
    <!-- Main road checkpoint near Elektro -->
    <pos x="10523.4" z="2456.8" a="90"/>
    
    <!-- Crossroads near Cherno -->
    <pos x="6842.7" z="2634.1" a="180"/>
</event>
```

### Example 2: Police Station Spawns
Multiple vehicles at police stations:

```xml
<event name="VehiclePoliceStation">
    <nominal>5</nominal>
    <min>4</min>
    <max>6</max>
    <lifetime>10800</lifetime>  <!-- 3 hours -->
    <restock>1800</restock>      <!-- 30 min cooldown -->
    <saferadius>500</saferadius>
    <distanceradius>50</distanceradius>
    <cleanupradius>200</cleanupradius>
    <flags deletable="0" init_random="0" remove_damaged="1"/>
    <position>fixed</position>
    <limit>child</limit>
    <active>1</active>
    <children>
        <child type="CivilianSedan_Police" min="1" max="1"/>
    </children>
</event>
```

Spawn at all major police stations:
```xml
<event name="VehiclePoliceStation">
    <pos x="10458.2" z="2287.5" a="180"/>  <!-- Elektro Police -->
    <pos x="6723.1" z="2533.8" a="270"/>    <!-- Cherno Police -->
    <pos x="5343.2" z="8644.7" a="90"/>     <!-- Kabanino Police -->
    <pos x="9710.3" z="8835.6" a="0"/>      <!-- Gorka Police -->
    <pos x="8040.5" z="12670.1" a="135"/>   <!-- Severograd Police -->
</event>
```

### Example 3: Crashed Police Cars (RP Scenario)
Damaged vehicles on roadsides:

```xml
<event name="VehiclePoliceCrashed">
    <nominal>3</nominal>
    <min>2</min>
    <max>4</max>
    <lifetime>5400</lifetime>
    <restock>0</restock>
    <saferadius>800</saferadius>
    <distanceradius>200</distanceradius>
    <cleanupradius>250</cleanupradius>
    <flags deletable="0" init_random="0" remove_damaged="1"/>
    <position>fixed</position>
    <limit>child</limit>
    <active>1</active>
    <children>
        <child type="CivilianSedan_Police" min="1" max="1"/>
    </children>
</event>
```

In cfgspawnabletypes.xml, configure as damaged:
```xml
<type name="CivilianSedan_Police">
    <attachments chance="0.40">
        <item name="CarWheel" chance="0.30" />  <!-- Often missing wheels -->
        <item name="CarBattery" chance="0.20" />
        <item name="SparkPlug" chance="0.15" />
        <item name="CarRadiator" chance="0.50" />
    </attachments>
    <cargo chance="0.70">
        <!-- More loot since players can't drive it -->
        <item name="CZ75" chance="0.35" />
        <item name="PoliceJacket" chance="0.50" />
    </cargo>
</type>
```

### Example 4: High-Pop Server
More police cars for active servers:

```xml
<event name="VehiclePoliceOffroad">
    <nominal>8</nominal>
    <min>6</min>
    <max>10</max>
    <lifetime>5400</lifetime>
    <restock>1800</restock>
    <saferadius>600</saferadius>
    <distanceradius>100</distanceradius>
    <cleanupradius>250</cleanupradius>
    <flags deletable="0" init_random="0" remove_damaged="1"/>
    <position>fixed</position>
    <limit>child</limit>
    <active>1</active>
    <children>
        <child type="CivilianSedan_Police" min="1" max="1"/>
    </children>
</event>
```

## Best Practices

### Spawn Location Selection

**Good Locations**:
- ✅ Police station parking lots
- ✅ Major road checkpoints
- ✅ Intersections with good visibility
- ✅ Roadside pulloffs
- ✅ Military checkpoints (mixed with military vehicles)

**Avoid**:
- ❌ Inside buildings (vehicles clip through)
- ❌ Steep slopes (vehicles roll/flip)
- ❌ Player spawn areas (coastal towns)
- ❌ Too close to water (vehicles can slide in)
- ❌ Dense forests (hard to spot, navigation issues)

### Vehicle Condition Balancing

**Fully Functional** (Easy Mode):
- All attachments at 100% chance
- Players can drive immediately
- Good for low-pop or RP servers

**Needs Minor Repairs** (Balanced):
- 60-80% chance for most parts
- 1-2 missing items typically
- Encourages scavenging

**Heavily Damaged** (Hard Mode):
- 20-40% chance for parts
- Often missing multiple wheels/battery
- Becomes static loot source

### Server Population Considerations

| Population | Nominal | Lifetime | Notes |
|------------|---------|----------|-------|
| **Low (0-20)** | 6-8 | 10800s (3hr) | More vehicles, longer persistence |
| **Medium (20-50)** | 4-6 | 7200s (2hr) | Balanced availability |
| **High (50+)** | 2-4 | 3600s (1hr) | Competitive, quick turnover |

### Performance Impact

Police car events are **lightweight** compared to helicrashes:
- Single vehicle object (vs multiple debris)
- Small loot pool
- Fixed locations (easier for server to track)
- Minimal performance impact even with many spawns

## Troubleshooting

### Police Cars Not Spawning

**Check 1: Event is active**
```xml
<active>1</active>  <!-- Must be 1 -->
```

**Check 2: Spawn locations exist**
- Verify cfgeventspawns.xml has coordinates
- Ensure event name matches exactly (case-sensitive)

**Check 3: Coordinates are valid**
- X, Z must be within map bounds
- On Chernarus+: 0-15360 for both axes
- Test coordinates in DayZ Editor first

**Check 4: Vehicle classname is correct**
```xml
<child type="CivilianSedan_Police" />  <!-- Check spelling -->
```

**Check 5: Not blocked by proximity**
- Reduce saferadius temporarily to test
- Check if other events are preventing spawn

### Vehicle Spawns But Can't Be Driven

**Problem**: Police car appears but won't start

**Solutions**:
1. **Check fuel**: Vehicles may spawn empty
   ```xml
   <cargo chance="1.0">
       <item name="CanisterGasoline" chance="1.0" />
   </cargo>
   ```

2. **Check attachments**: Needs wheels, battery, spark plug
   - Increase attachment chances in cfgspawnabletypes.xml

3. **Check damage**: Vehicle may be ruined
   - Vehicles can spawn with damage
   - Set health in custom spawn script

### Vehicle Disappears Immediately

**Cause**: Lifetime too short or cleanup issue

**Solution**:
- Increase lifetime value (try 3600 or 7200)
- Check cleanupradius isn't too large
- Verify vehicle isn't spawning in invalid location (inside object)

### Too Many/Few Vehicles

**Adjust nominal, min, max values**:
```xml
<nominal>4</nominal>  <!-- Target count -->
<min>3</min>          <!-- Guaranteed minimum -->
<max>5</max>          <!-- Hard cap -->
```

**Check spawn location count**:
- Need enough positions in cfgeventspawns.xml
- At least nominal + 2 recommended

### Vehicle Spawns in Air or Underground

**Cause**: Y coordinate issue (height)

**Solution**:
Events use X and Z only. Server calculates Y (height) automatically. If vehicle floats/clips:
1. Move spawn location slightly (adjust X/Z by 1-2 meters)
2. Avoid spawning on slopes
3. Test location in DayZ Editor first

## Advanced Scenarios

### Multi-Vehicle Event Groups

Spawn multiple vehicles together (police convoy):

```xml
<event name="PoliceConvoy">
    <nominal>1</nominal>
    <min>1</min>
    <max>1</max>
    <lifetime>7200</lifetime>
    <restock>0</restock>
    <saferadius>1000</saferadius>
    <distanceradius>300</distanceradius>
    <cleanupradius>400</cleanupradius>
    <flags deletable="0" init_random="0" remove_damaged="0"/>
    <position>fixed</position>
    <limit>child</limit>
    <active>1</active>
    <children>
        <child type="CivilianSedan_Police" min="2" max="3"/>  <!-- 2-3 police cars -->
        <child type="Barrel_Yellow" min="1" max="2"/>          <!-- Roadblock barrels -->
    </children>
</event>
```

### Scripted Vehicle Spawns

For dynamic control, use EnScript:

```cpp
void SpawnPoliceCarAt(vector position, float angle)
{
    // Spawn vehicle
    Car vehicle = Car.Cast(GetGame().CreateObject("CivilianSedan_Police", position, false, true));
    
    // Set orientation
    vector orientation = Vector(0, angle, 0);
    vehicle.SetOrientation(orientation);
    
    // Add fuel
    vehicle.Fill(CarFluid.FUEL, 40);  // 40 liters
    
    // Add attachments (wheels, battery, etc.)
    EntityAI wheel1 = vehicle.GetInventory().CreateAttachment("CarWheel");
    EntityAI wheel2 = vehicle.GetInventory().CreateAttachment("CarWheel");
    EntityAI wheel3 = vehicle.GetInventory().CreateAttachment("CarWheel");
    EntityAI wheel4 = vehicle.GetInventory().CreateAttachment("CarWheel");
    EntityAI battery = vehicle.GetInventory().CreateAttachment("CarBattery");
    EntityAI spark = vehicle.GetInventory().CreateAttachment("SparkPlug");
    EntityAI radiator = vehicle.GetInventory().CreateAttachment("CarRadiator");
    
    // Add cargo loot
    vehicle.GetInventory().CreateInInventory("CZ75");
    vehicle.GetInventory().CreateInInventory("Mag_CZ75_15Rnd");
    vehicle.GetInventory().CreateInInventory("PoliceJacket");
}
```

### Notification System

Alert players to new police car spawns:

```cpp
void NotifyPoliceCarSpawn(vector position)
{
    string message = "Police vehicle spotted in the area!";
    
    // Notify all players
    array<Man> players = new array<Man>;
    GetGame().GetPlayers(players);
    
    for (int i = 0; i < players.Count(); i++)
    {
        PlayerBase player = PlayerBase.Cast(players[i]);
        if (player)
        {
            player.MessageStatus(message, 10);  // 10 second display
        }
    }
}
```

### Integration with Discord

Send Discord webhook when police car spawns (requires Universal API mod or custom implementation):

```cpp
void SendDiscordPoliceAlert(vector position, string vehicleType)
{
    string message = "🚓 Police vehicle spawned: " + vehicleType;
    message += "\\nLocation: X:" + position[0] + " Z:" + position[2];
    message += "\\nTime: " + GetServerTime();
    
    // Send to Discord webhook (implementation depends on mod used)
    SendWebhookMessage(webhookURL, message);
}
```

### Rotation Based on Time/Population

Spawn different numbers based on server activity:

```cpp
void AdjustPoliceCarSpawns()
{
    int playerCount = GetGame().GetPlayers().Count();
    
    if (playerCount < 20)
    {
        // Low pop: More vehicles
        SetEventNominal("VehiclePoliceOffroad", 8);
    }
    else if (playerCount < 50)
    {
        // Medium pop: Balanced
        SetEventNominal("VehiclePoliceOffroad", 5);
    }
    else
    {
        // High pop: Competitive
        SetEventNominal("VehiclePoliceOffroad", 3);
    }
}
```

## Resources

### Official Documentation
- [Bohemia Wiki - Central Economy](https://community.bistudio.com/wiki/DayZ:Central_Economy)
- [DayZ Modding - Events](https://community.bistudio.com/wiki/DayZ:Modding_Basics)
- [Vehicle Configuration](https://community.bistudio.com/wiki/DayZ:Vehicles)

### Community Tools
- **DZConfig Wiki**: Events configuration reference
  - URL: https://dzconfig.com/wiki/events
  
- **DayZ File Toolbox**: Event editor
  - URL: https://www.dayzfiletoolbox.com/events-hub
  
- **iZurvive**: Map coordinates
  - URL: https://www.izurvive.com/

### Video Tutorials
- **Scalespeeder Gaming**: Vehicle spawn tutorials
  - Custom vehicle spawn locations
  - Console and PC setup guides
  
- **WOBO**: Vehicle mechanics
  - How vehicles work in DayZ
  - Spawn system explanation

### Related Documentation
- [Events System Overview](./overview.md)
- [Helicopter Crash Events](./helicrash.md)
- [Static Events Guide](./static-events.md)
- [Dynamic Events Guide](./dynamic-events.md)
- [Custom Events Guide](./custom-events.md)
- [Vehicle Configuration](../config/vehicles.md)

### Configuration Examples
- [Events Template](../../templates/config-templates/)
- [Vehicle Spawn Examples](../../examples/)

### GitHub Resources
- [Brandon10x15/DayZ-Modding](https://github.com/Brandon10x15/DayZ-Modding)
- [scalespeeder Vehicle Tutorials](https://github.com/scalespeeder)

## Summary

Police car events are an excellent way to add civilian vehicles and police-tier loot to your DayZ server. They're easier to configure than helicrashes and have minimal performance impact.

### Key Configuration Steps
1. **Define event in events.xml**: Set nominal, lifetime, flags
2. **Add spawn locations in cfgeventspawns.xml**: X, Z coordinates and rotation
3. **Configure vehicle state in cfgspawnabletypes.xml**: Attachments and cargo (optional)
4. **Test and adjust**: Verify spawns work, tune quantities

### Important Parameters
- **nominal**: How many vehicles (2-6 typical)
- **lifetime**: How long they last (3600-7200 seconds)
- **saferadius**: Distance between spawns (500-1000m)
- **vehicle type**: CivilianSedan_Police (most common)

### Best Practices
- Place at police stations and checkpoints
- Balance vehicle condition based on server difficulty
- More vehicles for low-pop, fewer for high-pop
- Test spawn locations for valid terrain
- Configure loot appropriate for police/civilian tier

---

**Last Updated**: January 2026  
**DayZ Version**: 1.26+  
**Platform**: PC (full support), Console (Nitrado panel editing)  
**Difficulty**: Beginner-Intermediate (XML editing, coordinates)

For questions or contributions, see [CONTRIBUTING.md](../../CONTRIBUTING.md)

**Happy patrolling! 🚓**
