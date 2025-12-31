# Types.xml Complete Guide

## Overview

`types.xml` is the **core configuration file** for DayZ's Central Economy system. It defines:
- What items spawn in the game
- Where items can spawn
- How many of each item exist
- Item spawn conditions and rules
- Loot distribution across the map

## File Structure

### Basic Structure
```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<types>
    <type name="ItemClassName">
        <!-- Configuration parameters -->
    </type>
    <!-- More items... -->
</types>
```

## Complete Type Definition

### Full Example with All Parameters
```xml
<type name="AKM">
    <!-- Core Parameters -->
    <nominal>15</nominal>
    <lifetime>3600</lifetime>
    <restock>1800</restock>
    <min>10</min>
    <quantmin>-1</quantmin>
    <quantmax>-1</quantmax>
    <cost>100</cost>
    
    <!-- Spawn Flags -->
    <flags count_in_cargo="0" count_in_hoarder="0" count_in_map="1" count_in_player="0" crafted="0" deloot="0"/>
    
    <!-- Category -->
    <category name="weapons"/>
    
    <!-- Usage Locations -->
    <usage name="Military"/>
    <usage name="Police"/>
    
    <!-- Value/Tier -->
    <value name="Tier3"/>
    <value name="Tier4"/>
    
    <!-- Tags -->
    <tag name="shelves"/>
</type>
```

## Parameter Breakdown

### 1. Core Parameters

#### nominal
**Type**: Integer  
**Purpose**: Target number of items that should exist on the server  
**Range**: 0-10000+  

```xml
<nominal>50</nominal>
```

**Examples**:
- Common items (Canned Food): 200-500
- Uncommon items (Rifles): 20-50
- Rare items (Night Vision): 1-5

**Important**: This is a TARGET, not a hard limit. The actual number can vary.

#### lifetime
**Type**: Integer (seconds)  
**Purpose**: How long the item exists before cleanup  
**Range**: 300-28800 (5 minutes to 8 hours)  

```xml
<lifetime>3600</lifetime> <!-- 1 hour -->
```

**Common Values**:
- Food/Drinks: 3600 (1 hour)
- Weapons: 7200 (2 hours)
- Tools: 10800 (3 hours)
- Vehicles: 28800 (8 hours)

#### restock
**Type**: Integer (seconds)  
**Purpose**: Cooldown before item can spawn again at same location  
**Range**: 0-7200  

```xml
<restock>1800</restock> <!-- 30 minutes -->
```

**Best Practices**:
- High-tier items: 1800-3600
- Mid-tier items: 900-1800
- Low-tier items: 300-900

#### min
**Type**: Integer  
**Purpose**: Minimum number of items before spawning more  
**Range**: 0 to nominal value  

```xml
<min>10</min>
```

**Rule**: When item count < min, system spawns more items up to nominal

#### quantmin & quantmax
**Type**: Integer (-1 or 0-100)  
**Purpose**: Minimum and maximum quantity percentage for stackable items  
**Special**: -1 = use default values  

```xml
<quantmin>20</quantmin>  <!-- Spawn at minimum 20% quantity -->
<quantmax>80</quantmax>  <!-- Spawn at maximum 80% quantity -->
```

**Examples**:
- Ammo boxes: `<quantmin>10</quantmin> <quantmax>50</quantmax>`
- Water bottles: `<quantmin>25</quantmin> <quantmax>100</quantmax>`
- Magazines: `<quantmin>30</quantmin> <quantmax>100</quantmax>`

#### cost
**Type**: Integer  
**Purpose**: Performance impact value (higher = more expensive)  
**Range**: 1-1000  

```xml
<cost>100</cost>
```

**Guidelines**:
- Simple items: 50-100
- Complex items: 100-200
- Vehicles: 200-1000

### 2. Flags System

```xml
<flags 
    count_in_cargo="0" 
    count_in_hoarder="0" 
    count_in_map="1" 
    count_in_player="0" 
    crafted="0" 
    deloot="0"
/>
```

#### count_in_cargo
**Values**: 0 or 1  
**Purpose**: Count items inside containers/vehicles toward nominal  
**Recommendation**: 0 for weapons, 1 for common items

#### count_in_hoarder
**Values**: 0 or 1  
**Purpose**: Count items in player stashes toward nominal  
**Recommendation**: 1 for rare items to prevent hoarding

#### count_in_map
**Values**: 0 or 1  
**Purpose**: Count items spawned in world toward nominal  
**Default**: 1 (always enabled)

#### count_in_player
**Values**: 0 or 1  
**Purpose**: Count items on players toward nominal  
**Recommendation**: 1 for very rare items

#### crafted
**Values**: 0 or 1  
**Purpose**: Item can be crafted by players  
**Effect**: If 1, doesn't spawn naturally

#### deloot
**Values**: 0 or 1  
**Purpose**: Item spawns in dynamic contaminated zones  
**Use**: For special event loot

### 3. Category System

```xml
<category name="CategoryName"/>
```

**Standard Categories**:
```xml
<category name="weapons"/>      <!-- Firearms -->
<category name="tools"/>        <!-- Tools and equipment -->
<category name="food"/>         <!-- Food items -->
<category name="containers"/>   <!-- Bags, cases, boxes -->
<category name="clothes"/>      <!-- Clothing items -->
<category name="vehiclesparts"/> <!-- Vehicle parts -->
<category name="explosives"/>   <!-- Grenades, mines, etc -->
```

**Purpose**:
- Logical grouping
- Used by cleanup system
- Affects spawn priorities

### 4. Usage Tags

```xml
<usage name="UsageArea"/>
```

**All Usage Tags**:
```xml
<!-- Military -->
<usage name="Military"/>
<usage name="MilitaryWest"/>
<usage name="MilitaryEast"/>

<!-- Civilian -->
<usage name="Town"/>
<usage name="Village"/>
<usage name="City"/>

<!-- Industrial -->
<usage name="Industrial"/>
<usage name="Farm"/>
<usage name="Hunting"/>
<usage name="Coast"/>

<!-- Medical -->
<usage name="Medic"/>

<!-- Police -->
<usage name="Police"/>
<usage name="Prison"/>

<!-- Special -->
<usage name="FireStation"/>
<usage name="School"/>
<usage name="Office"/>
```

**Multiple Usage Example**:
```xml
<!-- AK can spawn in multiple military areas -->
<usage name="Military"/>
<usage name="MilitaryWest"/>
<usage name="MilitaryEast"/>
```

### 5. Value/Tier System

```xml
<value name="TierX"/>
```

**Tier Definitions**:
```xml
<value name="Tier1"/>  <!-- Coast spawns -->
<value name="Tier2"/>  <!-- Low-mid inland -->
<value name="Tier3"/>  <!-- Mid-tier areas -->
<value name="Tier4"/>  <!-- High-tier areas -->
```

**Tier Map Distribution**:
- **Tier1**: Coastal areas, easy access
- **Tier2**: Small towns, minor military
- **Tier3**: Major cities, military bases
- **Tier4**: NWAF, high-value locations

**Multiple Tiers**:
```xml
<!-- M4 can spawn in both Tier3 and Tier4 -->
<value name="Tier3"/>
<value name="Tier4"/>
```

### 6. Tag System

```xml
<tag name="TagName"/>
```

**Common Tags**:
```xml
<tag name="floor"/>       <!-- Can spawn on floor -->
<tag name="shelves"/>     <!-- Can spawn on shelves -->
<tag name="office"/>      <!-- Spawns in office areas -->
<tag name="police"/>      <!-- Police-specific -->
<tag name="hunting"/>     <!-- Hunting-related -->
<tag name="food"/>        <!-- Food-related -->
<tag name="medical"/>     <!-- Medical facilities -->
```

## Complete Item Examples

### Example 1: Common Food Item
```xml
<type name="Apple">
    <nominal>300</nominal>
    <lifetime>900</lifetime>
    <restock>300</restock>
    <min>200</min>
    <quantmin>-1</quantmin>
    <quantmax>-1</quantmax>
    <cost>10</cost>
    <flags count_in_cargo="0" count_in_hoarder="0" count_in_map="1" count_in_player="0" crafted="0" deloot="0"/>
    <category name="food"/>
    <usage name="Town"/>
    <usage name="Village"/>
    <usage name="Farm"/>
    <value name="Tier1"/>
    <value name="Tier2"/>
</type>
```

### Example 2: Military Rifle
```xml
<type name="M4A1">
    <nominal>10</nominal>
    <lifetime>7200</lifetime>
    <restock>3600</restock>
    <min>5</min>
    <quantmin>-1</quantmin>
    <quantmax>-1</quantmax>
    <cost>150</cost>
    <flags count_in_cargo="0" count_in_hoarder="1" count_in_map="1" count_in_player="1" crafted="0" deloot="0"/>
    <category name="weapons"/>
    <usage name="Military"/>
    <value name="Tier4"/>
    <tag name="shelves"/>
</type>
```

### Example 3: Medical Supply
```xml
<type name="Epinephrine">
    <nominal>50</nominal>
    <lifetime>3600</lifetime>
    <restock>1800</restock>
    <min>30</min>
    <quantmin>-1</quantmin>
    <quantmax>-1</quantmax>
    <cost>50</cost>
    <flags count_in_cargo="0" count_in_hoarder="0" count_in_map="1" count_in_player="0" crafted="0" deloot="0"/>
    <category name="tools"/>
    <usage name="Medic"/>
    <usage name="Military"/>
    <value name="Tier2"/>
    <value name="Tier3"/>
    <value name="Tier4"/>
    <tag name="shelves"/>
    <tag name="medical"/>
</type>
```

### Example 4: Vehicle
```xml
<type name="OffroadHatchback">
    <nominal>5</nominal>
    <lifetime>28800</lifetime>
    <restock>7200</restock>
    <min>3</min>
    <quantmin>-1</quantmin>
    <quantmax>-1</quantmax>
    <cost>1000</cost>
    <flags count_in_cargo="0" count_in_hoarder="0" count_in_map="1" count_in_player="0" crafted="0" deloot="0"/>
    <category name="vehicles"/>
    <usage name="Town"/>
    <usage name="Village"/>
    <value name="Tier1"/>
    <value name="Tier2"/>
</type>
```

### Example 5: Ammo Box with Quantity
```xml
<type name="Ammo_762x39_20Rnd">
    <nominal>200</nominal>
    <lifetime>3600</lifetime>
    <restock>1800</restock>
    <min>150</min>
    <quantmin>20</quantmin>  <!-- Spawn 20-80% full -->
    <quantmax>80</quantmax>
    <cost>40</cost>
    <flags count_in_cargo="1" count_in_hoarder="0" count_in_map="1" count_in_player="0" crafted="0" deloot="0"/>
    <category name="weapons"/>
    <usage name="Military"/>
    <usage name="Police"/>
    <value name="Tier2"/>
    <value name="Tier3"/>
    <tag name="shelves"/>
</type>
```

## Advanced Configuration

### Preventing Hoarding
```xml
<!-- Rare item that counts everywhere -->
<type name="NVGoggles">
    <nominal>3</nominal>
    <flags 
        count_in_cargo="1" 
        count_in_hoarder="1" 
        count_in_map="1" 
        count_in_player="1"
    />
    <!-- Other params... -->
</type>
```

### Crafted-Only Items
```xml
<type name="CraftedBow">
    <nominal>0</nominal>
    <flags crafted="1"/>
    <!-- This item never spawns, only crafted -->
</type>
```

### Dynamic Event Items
```xml
<type name="M249">
    <nominal>2</nominal>
    <flags deloot="1"/>  <!-- Spawns in contaminated zones -->
    <usage name="Military"/>
    <value name="Tier4"/>
</type>
```

## Best Practices

### 1. Balancing Nominal Values
```
Total server items = Sum of all nominals
Target: 10,000-50,000 items for 60-player server
```

### 2. Lifetime Guidelines
```
Lifetime should be > Restock
Typical ratio: lifetime = restock * 2 to 4
```

### 3. Min Value Calculation
```
min = nominal * 0.5 to 0.7
Ensures items respawn before running out
```

### 4. Flag Configuration
**Common items**: All count_in flags = 0  
**Rare items**: All count_in flags = 1  
**Mid-tier**: count_in_hoarder = 1, others = 0

## Testing & Validation

### XML Validation
```bash
# Check XML syntax
xmllint --noout types.xml

# Validate against schema
xmllint --schema types.xsd types.xml
```

### In-Game Testing
1. Monitor item counts: `#ce show`
2. Check spawn locations: Visit usage areas
3. Verify timings: Test lifetime/restock
4. Balance check: Monitor total items

## Common Issues

### Issue 1: Items Not Spawning
**Causes**:
- nominal = 0
- No usage tags
- No matching mapgrouppos entries
- Tier mismatch with map

**Solution**: Verify usage tags match mapgrouppos.xml

### Issue 2: Too Many/Few Items
**Causes**:
- Nominal too high/low
- Min value incorrect
- Count_in flags misconfigured

**Solution**: Adjust nominal and min values

### Issue 3: Items Despawn Too Fast
**Causes**:
- Lifetime too low
- Cleanup system removing items

**Solution**: Increase lifetime, check cfgeconomycore.xml

## Performance Optimization

### Reduce Item Count
```xml
<!-- Instead of many common items -->
<nominal>1000</nominal>

<!-- Use fewer with faster restock -->
<nominal>200</nominal>
<restock>300</restock>
```

### Optimize Flags
```xml
<!-- Disable unnecessary counting -->
<flags count_in_cargo="0" count_in_hoarder="0"/>
```

## Related Files

- [mapgrouppos.xml](mapgrouppos-xml.md) - Defines spawn locations
- [cfgeconomycore.xml](cfgeconomycore-xml.md) - Economy settings
- [cfgspawnabletypes.xml](cfgspawnabletypes-xml.md) - Item attachments

## Examples Repository

See [examples/types-files/](../../examples/types-files/) for:
- Complete types.xml examples
- Balanced configurations
- Custom item types
- Mod integration examples

## Tools

- **DayZ Editor**: Visual types.xml editor
- **Community Offline Mode**: Test configurations offline
- **Types.xml Generator**: Automated generation tools

## Next Steps

- [MapGroupPos Guide](mapgrouppos-xml.md)
- [Economy System Overview](../economy/overview.md)
- [Loot Distribution](../economy/loot-distribution.md)
