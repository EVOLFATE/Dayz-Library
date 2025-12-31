# MapGroupPos.xml Complete Guide

## Overview

`mapgrouppos.xml` defines **WHERE** items spawn on the map. It links item categories and usage tags from types.xml to specific coordinates and building types.

## Purpose

- Define spawn point locations (X, Y, Z coordinates)
- Link locations to usage tags (Military, Town, Police, etc.)
- Specify which buildings can spawn loot
- Control loot density across the map

## File Structure

```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<territory>
    <territory-type>
        <!-- Group definitions -->
    </territory-type>
</territory>
```

## Complete Structure Example

```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<territory>
    <territory-type>
        <!-- Military Base Group -->
        <group name="Military" lootmax="20" lootmin="15">
            <container name="Land_Mil_Barracks" lootmax="10" lootmin="5">
                <pos x="3720.5" z="8954.2" a="45"/>
                <pos x="3715.8" z="8948.3" a="45"/>
            </container>
            <container name="Land_Mil_Tower" lootmax="5" lootmin="3">
                <pos x="3750.0" z="8960.0" a="90"/>
            </container>
        </group>
        
        <!-- Town Group -->
        <group name="Town" lootmax="30" lootmin="20">
            <container name="Land_House_2Story" lootmax="8" lootmin="4">
                <pos x="5234.2" z="10345.6" a="180"/>
                <pos x="5240.1" z="10350.8" a="180"/>
            </container>
        </group>
        
        <!-- More groups... -->
    </territory-type>
</territory>
```

## Element Breakdown

### 1. Territory Type
```xml
<territory-type>
    <!-- All groups go here -->
</territory-type>
```

**Purpose**: Root container for all spawn groups  
**Attributes**: None  
**Required**: Yes

### 2. Group Element

```xml
<group name="GroupName" lootmax="20" lootmin="10">
    <!-- Containers go here -->
</group>
```

#### Attributes

**name** (Required)
- Links to `<usage>` tags in types.xml
- Case-sensitive
- Standard names: Military, Town, Village, Industrial, etc.

**lootmax** (Required)
- Maximum items that can spawn in this group
- Integer value
- Affects entire group, not per building

**lootmin** (Required)  
- Minimum items that spawn in this group
- Integer value
- Must be ≤ lootmax

#### Standard Group Names

```xml
<!-- Military Groups -->
<group name="Military">
<group name="MilitaryWest">
<group name="MilitaryEast">

<!-- Civilian Groups -->
<group name="Town">
<group name="Village">
<group name="City">

<!-- Industrial Groups -->
<group name="Industrial">
<group name="Farm">

<!-- Medical Groups -->
<group name="Medic">

<!-- Police Groups -->
<group name="Police">

<!-- Special Groups -->
<group name="Prison">
<group name="FireStation">
<group name="School">
<group name="Hunting">
<group name="Coast">
```

### 3. Container Element

```xml
<container name="BuildingClassName" lootmax="8" lootmin="4">
    <!-- Position entries go here -->
</container>
```

#### Attributes

**name** (Required)
- Building class name from game files
- Must match exact class name
- Examples: Land_Mil_Barracks, Land_House_2Story

**lootmax** (Required)
- Maximum items per building instance
- Overrides group lootmax for this building type

**lootmin** (Required)
- Minimum items per building instance
- Must be ≤ lootmax

### 4. Position Element

```xml
<pos x="3720.5" z="8954.2" a="45"/>
```

#### Attributes

**x** (Required)
- X coordinate on map
- Float value
- Map range: 0-15360 (Chernarus+)

**z** (Required)
- Z coordinate on map (Y in 3D space)
- Float value
- Map range: 0-15360 (Chernarus+)

**a** (Required)
- Rotation angle in degrees
- Range: 0-360
- 0 = North, 90 = East, 180 = South, 270 = West

**Note**: Y coordinate (height) is auto-calculated from terrain

## Complete Examples

### Example 1: Military Base
```xml
<group name="Military" lootmax="25" lootmin="18">
    <!-- Barracks -->
    <container name="Land_Mil_Barracks" lootmax="12" lootmin="8">
        <pos x="4523.45" z="10438.23" a="135"/>
        <pos x="4530.12" z="10445.67" a="135"/>
        <pos x="4515.89" z="10430.45" a="135"/>
    </container>
    
    <!-- Guard Towers -->
    <container name="Land_Mil_GuardTower" lootmax="5" lootmin="3">
        <pos x="4500.00" z="10400.00" a="45"/>
        <pos x="4550.00" z="10480.00" a="225"/>
    </container>
    
    <!-- Control Tower -->
    <container name="Land_Mil_ATC_Big" lootmax="8" lootmin="5">
        <pos x="4525.00" z="10440.00" a="180"/>
    </container>
    
    <!-- Hangars -->
    <container name="Land_Mil_Hangar_2" lootmax="15" lootmin="10">
        <pos x="4480.00" z="10420.00" a="90"/>
        <pos x="4570.00" z="10420.00" a="90"/>
    </container>
</group>
```

### Example 2: Town/City
```xml
<group name="Town" lootmax="40" lootmin="30">
    <!-- Residential Houses -->
    <container name="Land_House_1W01" lootmax="6" lootmin="3">
        <pos x="6234.5" z="7823.4" a="90"/>
        <pos x="6245.2" z="7825.8" a="90"/>
        <pos x="6238.9" z="7835.1" a="180"/>
    </container>
    
    <container name="Land_House_2Story" lootmax="10" lootmin="6">
        <pos x="6220.0" z="7840.0" a="270"/>
        <pos x="6225.5" z="7845.3" a="0"/>
    </container>
    
    <!-- Shops -->
    <container name="Land_Shop_01" lootmax="12" lootmin="8">
        <pos x="6240.0" z="7830.0" a="180"/>
    </container>
    
    <!-- Garages -->
    <container name="Land_Garage" lootmax="5" lootmin="3">
        <pos x="6250.0" z="7820.0" a="90"/>
        <pos x="6255.0" z="7825.0" a="90"/>
    </container>
</group>
```

### Example 3: Police Station
```xml
<group name="Police" lootmax="15" lootmin="10">
    <!-- Police Building -->
    <container name="Land_Police" lootmax="12" lootmin="8">
        <pos x="5432.1" z="8765.4" a="45"/>
    </container>
    
    <!-- Police Jail -->
    <container name="Land_Police_Jail" lootmax="8" lootmin="5">
        <pos x="5440.0" z="8770.0" a="45"/>
    </container>
</group>
```

### Example 4: Industrial Area
```xml
<group name="Industrial" lootmax="35" lootmin="25">
    <!-- Factory Buildings -->
    <container name="Land_Factory_Main" lootmax="15" lootmin="10">
        <pos x="8234.5" z="12456.7" a="0"/>
    </container>
    
    <!-- Warehouses -->
    <container name="Land_Warehouse" lootmax="12" lootmin="8">
        <pos x="8250.0" z="12470.0" a="90"/>
        <pos x="8260.0" z="12470.0" a="90"/>
    </container>
    
    <!-- Garages -->
    <container name="Land_Garage_Row" lootmax="6" lootmin="4">
        <pos x="8240.0" z="12480.0" a="180"/>
    </container>
</group>
```

### Example 5: Medical Facility
```xml
<group name="Medic" lootmax="20" lootmin="15">
    <!-- Hospital -->
    <container name="Land_Hospital" lootmax="18" lootmin="12">
        <pos x="7523.4" z="5234.6" a="270"/>
    </container>
    
    <!-- Medical Tents -->
    <container name="Land_Tent_Medical" lootmax="8" lootmin="5">
        <pos x="4520.0" z="10430.0" a="90"/>
        <pos x="4525.0" z="10430.0" a="90"/>
    </container>
</group>
```

### Example 6: Hunting Areas
```xml
<group name="Hunting" lootmax="12" lootmin="8">
    <!-- Hunting Stands -->
    <container name="Land_HuntingStand" lootmax="4" lootmin="2">
        <pos x="9234.5" z="11456.2" a="180"/>
        <pos x="9456.7" z="11234.8" a="90"/>
        <pos x="9567.3" z="11678.4" a="270"/>
    </container>
    
    <!-- Feedshacks -->
    <container name="Land_FeedShack" lootmax="3" lootmin="2">
        <pos x="9345.6" z="11567.8" a="45"/>
        <pos x="9678.9" z="11890.1" a="135"/>
    </container>
</group>
```

## Building Class Reference

### Common Military Buildings
```
Land_Mil_Barracks
Land_Mil_Barracks2
Land_Mil_Barracks3
Land_Mil_GuardTower
Land_Mil_GuardTower_Big
Land_Mil_ATC_Big
Land_Mil_ATC_Small
Land_Mil_Hangar_2
Land_Mil_House
Land_Mil_Tent_Big
Land_Mil_Tent_Small
```

### Common Civilian Buildings
```
Land_House_1W01
Land_House_1W02
Land_House_2Story
Land_House_2Story2
Land_Shop_01
Land_Shop_02
Land_Office_01
Land_Office_02
Land_Garage
Land_Garage_Row
```

### Common Industrial Buildings
```
Land_Factory_Main
Land_Factory_Repair
Land_Warehouse
Land_Warehouse_Small
Land_Workshop
Land_Shed_Ind
```

### Special Buildings
```
Land_Hospital
Land_Police
Land_Police_Jail
Land_FireStation
Land_School
Land_Prison
Land_Castle_Tower
```

## Coordinate System

### Finding Coordinates

#### Method 1: In-Game (Admin)
```
1. Enable admin mode
2. Use getpos command
3. Note X and Z coordinates
```

#### Method 2: DayZ Editor
```
1. Open map in DayZ Editor
2. Place object
3. Copy coordinates from properties
```

#### Method 3: Community Online Map
```
1. Visit iZurvive or similar
2. Click location
3. Note coordinates
```

### Coordinate Ranges by Map

**Chernarus Plus**:
- X: 0 to 15360
- Z: 0 to 15360
- Size: 225 km²

**Livonia**:
- X: 0 to 12800  
- Z: 0 to 12800
- Size: 163 km²

**Sakhal**:
- X: 0 to 12800
- Z: 0 to 12800
- Size: 163 km²

## Loot Distribution Strategy

### Density Guidelines

**High Density Areas** (Cities, Major Military)
```xml
<group lootmax="40" lootmin="30">
    <container lootmax="10" lootmin="6">
```

**Medium Density** (Towns, Minor Military)
```xml
<group lootmax="25" lootmin="18">
    <container lootmax="6" lootmin="4">
```

**Low Density** (Villages, Hunting)
```xml
<group lootmax="12" lootmin="8">
    <container lootmax="4" lootmin="2">
```

### Balancing Formula
```
Total map loot points = Sum of all group lootmax
Recommended: 3000-8000 for 60-player server

Per building: lootmax = (building_size / 10) + 2
```

## Advanced Techniques

### Tier-Based Distribution

Use multiple groups with same usage tag but different tiers:

```xml
<!-- Coastal Military (Tier 1) -->
<group name="Military" lootmax="15" lootmin="10">
    <container name="Land_Mil_Tent_Small" lootmax="5" lootmin="3">
        <pos x="1234.5" z="2345.6" a="90"/>
    </container>
</group>

<!-- Inland Military (Tier 3) -->
<group name="Military" lootmax="25" lootmin="18">
    <container name="Land_Mil_Barracks" lootmax="12" lootmin="8">
        <pos x="8765.4" z="10987.6" a="180"/>
    </container>
</group>

<!-- NWAF (Tier 4) -->
<group name="Military" lootmax="35" lootmin="28">
    <container name="Land_Mil_Hangar_2" lootmax="15" lootmin="12">
        <pos x="4523.4" z="10432.1" a="0"/>
    </container>
</group>
```

### Custom Spawn Areas

Create custom groups for mod-specific areas:

```xml
<group name="CustomBase" lootmax="30" lootmin="20">
    <container name="MyCustomBuilding" lootmax="15" lootmin="10">
        <pos x="7890.1" z="8901.2" a="45"/>
    </container>
</group>
```

Then in types.xml:
```xml
<type name="MyCustomItem">
    <usage name="CustomBase"/>
    <!-- Other parameters -->
</type>
```

## Integration with Types.xml

### Matching Usage Tags

**types.xml**:
```xml
<type name="AKM">
    <usage name="Military"/>
    <usage name="Police"/>
</type>
```

**mapgrouppos.xml**:
```xml
<group name="Military" lootmax="20" lootmin="15">
    <!-- AKM can spawn here -->
</group>

<group name="Police" lootmax="12" lootmin="8">
    <!-- AKM can also spawn here -->
</group>
```

### Tier System Integration

**types.xml**:
```xml
<type name="M4A1">
    <usage name="Military"/>
    <value name="Tier4"/>
</type>
```

**mapgrouppos.xml**:
```xml
<!-- Tier 4 military locations only -->
<group name="Military" lootmax="35" lootmin="28">
    <container name="Land_Mil_Hangar_2">
        <pos x="4523.4" z="10432.1" a="0"/> <!-- NWAF -->
    </container>
</group>
```

## Performance Optimization

### Reduce Spawn Points
```xml
<!-- Instead of many low-loot buildings -->
<container lootmax="2" lootmin="1">
    <pos x="..." z="..." a="..."/> <!-- 50 positions -->
</container>

<!-- Use fewer high-loot buildings -->
<container lootmax="8" lootmin="5">
    <pos x="..." z="..." a="..."/> <!-- 10 positions -->
</container>
```

### Group Consolidation
```xml
<!-- Combine nearby buildings into same group -->
<group name="Town" lootmax="40" lootmin="30">
    <!-- Multiple buildings in same area -->
</group>
```

## Testing & Validation

### XML Validation
```bash
xmllint --noout mapgrouppos.xml
```

### In-Game Testing
1. Restart server
2. Visit spawn locations
3. Check loot spawns
4. Verify quantities match lootmin/lootmax
5. Test over multiple restocks

### Common Issues

**Issue**: No loot spawning
- Verify building names are correct
- Check coordinates are on map
- Ensure usage tags match types.xml

**Issue**: Too much/little loot
- Adjust lootmin/lootmax values
- Check total loot points vs server capacity
- Review nominal values in types.xml

## Tools

### Coordinate Extraction
```python
# Python script to extract coordinates from mission file
import xml.etree.ElementTree as ET

tree = ET.parse('your_mission.xml')
for obj in tree.findall('.//Object'):
    name = obj.get('name')
    x = obj.get('x')
    z = obj.get('z')
    print(f'<pos x="{x}" z="{z}" a="0"/>')
```

### Loot Calculator
```javascript
// Calculate total loot points
let totalLoot = 0;
groups.forEach(group => {
    totalLoot += group.lootmax;
});
console.log(`Total loot points: ${totalLoot}`);
```

## Related Files

- [types.xml](types-xml.md) - Defines what spawns
- [cfgeconomycore.xml](cfgeconomycore-xml.md) - Economy settings
- [mapgroupproto.xml](mapgroupproto-xml.md) - Building prototypes

## Examples Repository

See [examples/mapgrouppos/](../../examples/mapgrouppos/) for:
- Complete map configurations
- Balanced distributions
- Custom area examples
- Tier-based setups

## Next Steps

- [Economy System Overview](../economy/overview.md)
- [Loot Distribution Guide](../economy/loot-distribution.md)
- [Custom Spawn Points](../spawns/custom-spawns.md)
