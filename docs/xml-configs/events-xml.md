# Events.xml Complete Guide

## Overview

`events.xml` defines **dynamic world events** that spawn at random locations and times across the map. These include helicopter crashes, police cars, convoys, and custom events that add excitement and rare loot opportunities.

## Purpose

- Define dynamic event types
- Control event spawn frequency
- Set event lifetimes
- Configure loot and positioning
- Create memorable server moments

## File Structure

```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<events>
    <event name="EventName">
        <!-- Event configuration -->
    </event>
    <!-- More events... -->
</events>
```

## Complete Event Definition

### Full Example
```xml
<event name="StaticHeliCrash">
    <nominal>3</nominal>
    <min>2</min>
    <max>4</max>
    <lifetime>3600</lifetime>
    <restock>0</restock>
    <saferadius>500</saferadius>
    <distanceradius>500</distanceradius>
    <cleanupradius>1000</cleanupradius>
    <flags deletable="1" init_random="0" remove_damaged="0"/>
    <position>fixed</position>
    <limit>child</limit>
    <active>1</active>
    <children>
        <child lootmax="15" lootmin="10" max="4" min="2" type="Wreck_UH1Y"/>
    </children>
</event>
```

## Parameter Breakdown

### Core Parameters

#### nominal
**Type**: Integer  
**Purpose**: Target number of active events  
**Range**: 1-20 typical

```xml
<nominal>3</nominal>
```

**Examples**:
- Helicopter crash: 2-4
- Police car: 5-10
- Rare events: 1-2

#### min
**Type**: Integer  
**Purpose**: Minimum events before spawning more  
**Must be**: ≤ nominal

```xml
<min>2</min>
```

#### max
**Type**: Integer  
**Purpose**: Maximum events allowed  
**Must be**: ≥ nominal

```xml
<max>4</max>
```

#### lifetime
**Type**: Integer (seconds)  
**Purpose**: How long event exists before cleanup  
**Range**: 1800-7200 typical

```xml
<lifetime>3600</lifetime> <!-- 1 hour -->
```

**Common Values**:
- Short events: 1800 (30 min)
- Standard: 3600 (1 hour)
- Long-lasting: 7200 (2 hours)

#### restock
**Type**: Integer (seconds)  
**Purpose**: Cooldown before event can spawn again  
**Note**: Usually 0 for dynamic events

```xml
<restock>0</restock>
```

**Usage**:
- 0 = Spawn when nominal not met
- >0 = Wait this many seconds between spawns

### Radius Parameters

#### saferadius
**Type**: Integer (meters)  
**Purpose**: Minimum distance from players for spawn  
**Range**: 200-1000

```xml
<saferadius>500</saferadius>
```

**Purpose**: Prevents events spawning on top of players

#### distanceradius
**Type**: Integer (meters)  
**Purpose**: Minimum distance between similar events  
**Range**: 200-2000

```xml
<distanceradius>500</distanceradius>
```

**Purpose**: Spreads events across map

#### cleanupradius
**Type**: Integer (meters)  
**Purpose**: Area cleaned when event despawns  
**Range**: 500-2000

```xml
<cleanupradius>1000</cleanupradius>
```

**Purpose**: Removes debris and loot

### Flags

```xml
<flags deletable="1" init_random="0" remove_damaged="0"/>
```

#### deletable
**Values**: 0 or 1  
**Purpose**: Can be deleted by cleanup system  
**Recommendation**: 1 for most events

#### init_random
**Values**: 0 or 1  
**Purpose**: Randomize initial spawn  
**Note**: 0 = spawn at server start, 1 = random delay

#### remove_damaged
**Values**: 0 or 1  
**Purpose**: Remove when damaged threshold reached  
**Usage**: Rarely used

### Position Types

```xml
<position>fixed</position>
```

**Options**:
- `fixed` - Spawns at predefined coordinates
- `random` - Spawns at random valid locations

### Limit Types

```xml
<limit>child</limit>
```

**Options**:
- `child` - Limits apply to child objects
- `parent` - Limits apply to parent event
- `mixed` - Both parent and child limits

### Active Status

```xml
<active>1</active>
```

**Values**:
- `1` = Event enabled
- `0` = Event disabled

### Children Objects

```xml
<children>
    <child lootmax="15" lootmin="10" max="4" min="2" type="Wreck_UH1Y"/>
    <child lootmax="8" lootmin="5" max="2" min="1" type="Wreck_Mi8"/>
</children>
```

#### Child Parameters

**lootmax**: Maximum loot items in this object  
**lootmin**: Minimum loot items in this object  
**max**: Maximum instances of this child type  
**min**: Minimum instances of this child type  
**type**: Object class name

## Complete Event Examples

### Example 1: Helicopter Crash (US)
```xml
<event name="StaticHeliCrash">
    <nominal>3</nominal>
    <min>2</min>
    <max>4</max>
    <lifetime>3600</lifetime>
    <restock>0</restock>
    <saferadius>500</saferadius>
    <distanceradius>500</distanceradius>
    <cleanupradius>1000</cleanupradius>
    <flags deletable="1" init_random="0" remove_damaged="0"/>
    <position>fixed</position>
    <limit>child</limit>
    <active>1</active>
    <children>
        <child lootmax="20" lootmin="15" max="4" min="2" type="Wreck_UH1Y"/>
    </children>
</event>
```

### Example 2: Helicopter Crash (Russian)
```xml
<event name="StaticHeliCrash_Russian">
    <nominal>3</nominal>
    <min>2</min>
    <max>4</max>
    <lifetime>3600</lifetime>
    <restock>0</restock>
    <saferadius>500</saferadius>
    <distanceradius>500</distanceradius>
    <cleanupradius>1000</cleanupradius>
    <flags deletable="1" init_random="0" remove_damaged="0"/>
    <position>fixed</position>
    <limit>child</limit>
    <active>1</active>
    <children>
        <child lootmax="20" lootmin="15" max="4" min="2" type="Wreck_Mi8"/>
    </children>
</event>
```

### Example 3: Police Car
```xml
<event name="VehiclePolice">
    <nominal>8</nominal>
    <min>6</min>
    <max>10</max>
    <lifetime>2400</lifetime>
    <restock>0</restock>
    <saferadius>300</saferadius>
    <distanceradius>300</distanceradius>
    <cleanupradius>500</cleanupradius>
    <flags deletable="1" init_random="0" remove_damaged="0"/>
    <position>fixed</position>
    <limit>child</limit>
    <active>1</active>
    <children>
        <child lootmax="8" lootmin="5" max="10" min="6" type="OffroadHatchback_Police"/>
    </children>
</event>
```

### Example 4: Military Convoy
```xml
<event name="MilitaryConvoy">
    <nominal>2</nominal>
    <min>1</min>
    <max>3</max>
    <lifetime>4800</lifetime>
    <restock>0</restock>
    <saferadius>800</saferadius>
    <distanceradius>1000</distanceradius>
    <cleanupradius>1500</cleanupradius>
    <flags deletable="1" init_random="0" remove_damaged="0"/>
    <position>fixed</position>
    <limit>mixed</limit>
    <active>1</active>
    <children>
        <child lootmax="12" lootmin="8" max="2" min="1" type="Wreck_Hmmwv"/>
        <child lootmax="10" lootmin="6" max="2" min="1" type="Wreck_Ural"/>
        <child lootmax="5" lootmin="3" max="3" min="2" type="Land_Wreck_Ammocrate"/>
    </children>
</event>
```

### Example 5: Contaminated Zone
```xml
<event name="ContaminatedArea_Dynamic">
    <nominal>5</nominal>
    <min>3</min>
    <max>7</max>
    <lifetime>3600</lifetime>
    <restock>0</restock>
    <saferadius>1000</saferadius>
    <distanceradius>2000</distanceradius>
    <cleanupradius>500</cleanupradius>
    <flags deletable="1" init_random="1" remove_damaged="0"/>
    <position>random</position>
    <limit>parent</limit>
    <active>1</active>
    <children>
        <child lootmax="0" lootmin="0" max="7" min="3" type="ContaminatedArea_Dynamic"/>
    </children>
</event>
```

### Example 6: Custom Treasure Hunt
```xml
<event name="TreasureHunt">
    <nominal>5</nominal>
    <min>3</min>
    <max>6</max>
    <lifetime>7200</lifetime>
    <restock>0</restock>
    <saferadius>400</saferadius>
    <distanceradius>800</distanceradius>
    <cleanupradius>600</cleanupradius>
    <flags deletable="1" init_random="1" remove_damaged="0"/>
    <position>random</position>
    <limit>child</limit>
    <active>1</active>
    <children>
        <child lootmax="25" lootmin="20" max="6" min="3" type="SeaChest"/>
    </children>
</event>
```

## Event Spawn Locations

### Using eventspawns.xml
Events spawn at predefined positions in `eventspawns.xml`:

```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<eventposdef>
    <event name="StaticHeliCrash">
        <pos x="7523.45" z="10234.67" a="0"/>
        <pos x="8234.12" z="11456.89" a="45"/>
        <pos x="6789.34" z="9876.54" a="90"/>
        <!-- More positions -->
    </event>
</eventposdef>
```

### Random vs Fixed Positioning

**Fixed Positioning** (`<position>fixed</position>`):
- Uses coordinates from eventspawns.xml
- Predictable locations
- Player can learn spawn points
- Good for iconic locations

**Random Positioning** (`<position>random</position>`):
- System chooses valid terrain
- Unpredictable for players
- Requires valid spawn zones
- Better for repeatability

## Event Object Types

### Helicopter Wrecks
```
Wreck_UH1Y          - US Helicopter
Wreck_Mi8           - Russian Helicopter
Wreck_UH60          - Blackhawk
```

### Vehicle Wrecks
```
Wreck_Hmmwv         - Humvee
Wreck_Ural          - Truck
Wreck_S120          - Sedan
Wreck_Volha         - Car
```

### Police Vehicles
```
OffroadHatchback_Police
Sedan_02_Police
```

### Military Objects
```
Land_Wreck_Ammocrate
Land_Wreck_Weaponcrate
Land_Tent_Military
```

### Containers
```
SeaChest
Barrel_ColorBase
WoodenCrate
```

## Advanced Configuration

### Multiple Child Types
```xml
<children>
    <child lootmax="15" lootmin="10" max="2" min="1" type="Wreck_UH1Y"/>
    <child lootmax="10" lootmin="5" max="1" min="0" type="Land_Wreck_Ammocrate"/>
    <child lootmax="5" lootmin="3" max="3" min="1" type="Barrel_ColorBase"/>
</children>
```

### Balanced Event Density
```
Total nominal events = Sum of all nominal values
Recommended: 20-40 total events for 60-player server
```

### Event Lifetime Strategy
```
Short (30min): High-traffic areas, common events
Medium (1hr): Standard events, balanced spawns
Long (2hr): Rare events, valuable loot
```

## Integration with Types.xml

### Linking Event Loot

**types.xml**:
```xml
<type name="M4A1">
    <nominal>10</nominal>
    <flags deloot="1"/>  <!-- Spawns in events -->
    <usage name="Military"/>
    <value name="Tier4"/>
</type>
```

**events.xml**:
```xml
<event name="StaticHeliCrash">
    <children>
        <child lootmax="20" lootmin="15" type="Wreck_UH1Y"/>
        <!-- M4A1 can spawn here due to deloot flag -->
    </children>
</event>
```

### Creating Event-Only Items
Set `nominal="0"` and `deloot="1"` in types.xml for event-exclusive loot.

## Performance Considerations

### Event Count Limits
```
Too few events: Predictable, less exciting
Too many events: Performance impact, diluted rewards
Sweet spot: 20-40 total nominal
```

### Cleanup Optimization
```xml
<!-- Efficient cleanup -->
<cleanupradius>1000</cleanupradius>
<lifetime>3600</lifetime>
```

Use appropriate cleanup radius to remove debris without affecting nearby areas.

## Testing Events

### In-Game Commands (Admin)
```
#event spawn EventName
#event list
#event delete EventName
```

### Monitoring
1. Check server logs for event spawns
2. Monitor active event count
3. Verify loot spawning correctly
4. Test cleanup after lifetime

## Common Issues

### Issue 1: Events Not Spawning
**Causes**:
- Active set to 0
- No valid spawn locations
- Nominal already met
- Conflicting saferadius

**Solution**: Check eventspawns.xml, verify active=1

### Issue 2: Too Many/Few Events
**Causes**:
- Incorrect nominal/min/max values
- Lifetime too short/long

**Solution**: Adjust nominal and lifetime values

### Issue 3: Events Spawning on Players
**Causes**:
- Saferadius too small
- Not enough valid spawn points

**Solution**: Increase saferadius to 500+

### Issue 4: Loot Not Spawning
**Causes**:
- Lootmax too low
- No items with deloot flag
- Types.xml misconfiguration

**Solution**: Verify lootmin/lootmax, check types.xml deloot flags

## Best Practices

### 1. Balanced Distribution
```xml
<!-- Spread events across tiers -->
Coastal events: nominal 5-8
Inland events: nominal 3-5
High-tier events: nominal 1-3
```

### 2. Appropriate Lifetimes
```xml
<!-- Match lifetime to value -->
Common events: 1800-2400 seconds
Rare events: 3600-7200 seconds
```

### 3. Proper Spacing
```xml
<!-- Prevent clustering -->
<distanceradius>500</distanceradius>  <!-- Minimum -->
<distanceradius>2000</distanceradius> <!-- Rare events -->
```

### 4. Gradual Scaling
```
Start conservative, increase gradually
Monitor performance
Adjust based on player feedback
```

## Custom Event Ideas

### 1. Supply Drop
```xml
<event name="SupplyDrop">
    <nominal>3</nominal>
    <lifetime>1800</lifetime>
    <children>
        <child lootmax="30" lootmin="25" type="Land_Container_1Bo"/>
    </children>
</event>
```

### 2. Abandoned Camp
```xml
<event name="AbandonedCamp">
    <nominal>6</nominal>
    <lifetime>5400</lifetime>
    <children>
        <child lootmax="10" lootmin="6" type="Land_Tent_Military"/>
        <child lootmax="15" lootmin="10" type="Barrel_ColorBase"/>
    </children>
</event>
```

### 3. Medical Emergency
```xml
<event name="MedicalEmergency">
    <nominal>4</nominal>
    <lifetime>3600</lifetime>
    <children>
        <child lootmax="20" lootmin="15" type="Wreck_Ambulance"/>
    </children>
</event>
```

## Related Files

- [types.xml](types-xml.md) - Configure event loot
- [eventspawns.xml](#) - Define spawn locations
- [cfgeconomycore.xml](cfgeconomycore-xml.md) - Economy settings

## Examples Repository

See [examples/events/](../../examples/events/) for:
- Complete event configurations
- Balanced event sets
- Custom event examples
- Theme-based event packs

## Next Steps

- [Economy System Overview](../economy/overview.md)
- [Custom Events Guide](../events/custom-events.md)
- [Loot Distribution](../economy/loot-distribution.md)
