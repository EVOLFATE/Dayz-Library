# Server Configuration Errors (XML/JSON)

## Complete Guide to DayZ Configuration File Issues

Configuration files control loot spawns, server settings, events, and more. This guide covers all common configuration errors and how to fix them.

---

## Types.xml Issues

### "Cannot Parse types.xml"

**Error Message**:
```
Error: XML parsing failed in types.xml
Line: 145
```

**Common Causes**:

**Cause 1: Unclosed Tags**
```xml
<!-- Wrong -->
<type name="AKM">
    <nominal>10</nominal>
<!-- Missing </type>! -->

<!-- Correct -->
<type name="AKM">
    <nominal>10</nominal>
</type>
```

**Cause 2: Invalid Characters**
```xml
<!-- Wrong -->
<type name="Item&Stuff">

<!-- Correct -->
<type name="ItemStuff">
<!-- or use HTML entities -->
<type name="Item&amp;Stuff">
```

**Cause 3: Wrong Encoding**
```
File must be UTF-8
Use Notepad++ to check/convert:
Encoding → Convert to UTF-8
```

### "Item Not Spawning"

**Problem**: Added item to types.xml but doesn't spawn

**Checklist**:

**1. Verify Nominal Value**
```xml
<type name="MyItem">
    <nominal>0</nominal>  <!-- WRONG - must be > 0! -->
    <min>0</min>
</type>

<!-- Correct -->
<type name="MyItem">
    <nominal>10</nominal>  <!-- At least 1 -->
    <min>5</min>
</type>
```

**2. Check Category**
```xml
<type name="MyItem">
    <category name="weapons"/>  <!-- Must match usage! -->
</type>

Categories:
- weapons
- clothes
- food
- tools
- vehicles
```

**3. Verify Usage Flags**
```xml
<type name="MyItem">
    <usage name="Military"/>  <!-- Where it spawns -->
    <usage name="Police"/>
</usage>

Common flags:
- Military
- Police
- Hunting
- Farm
- Village
- Town
- City
- Industrial
```

**4. Check Value Flags**
```xml
<type name="MyItem">
    <value name="Tier1"/>  <!-- Spawn tier -->
</type>

Tiers:
- Tier1 (coast/common)
- Tier2 (inland)
- Tier3 (military)
- Tier4 (rare)
```

**5. Ensure in MapGroupPos**
```
Item must have spawn locations defined
Check mapgrouppos.xml or mapgroupproto.xml
```

### Loot Economy Not Working

**Problem**: Loot spawn seems broken or imbalanced

**Debug Steps**:

**Step 1: Check Nominal vs Min**
```xml
<type name="AKM">
    <nominal>5</nominal>   <!-- Max in world -->
    <min>3</min>           <!-- Min respawn threshold -->
    <quantmin>-1</quantmin>
    <quantmax>-1</quantmax>
    <cost>100</cost>       <!-- Rarity (higher = rarer) -->
    <lifetime>3600</lifetime>  <!-- 1 hour -->
</type>

Rules:
- min should be < nominal
- If current count < min, respawn occurs
- lifetime = seconds before cleanup
```

**Step 2: Verify Restock**
```xml
<type name="Food">
    <restock>1800</restock>  <!-- Check every 30 min -->
</type>

Lower = faster respawn checks
Higher = slower, less server load
```

**Step 3: Check Count Limits**
```xml
<type name="AKM">
    <count_in_cargo>1</count_in_cargo>
    <count_in_hoarder>5</count_in_hoarder>
    <count_in_map>1</count_in_map>
    <count_in_player>0</count_in_player>
</type>

These limit how many exist in:
- Containers (cargo)
- Stashes/buried (hoarder)
- World spawns (map)
- Player inventory (player)
```

---

## MapGroupPos.xml Issues

### "No Spawn Points"

**Problem**: Items added to types.xml but still don't spawn

**Understanding MapGroupPos**:
```xml
<group name="Military" default="1">
    <container name="bldr_mil_camonet_roof_door"/>
    <container name="land_mil_barracks1"/>
    <!-- Maps buildings to loot groups -->
</group>

Links:
Building → Group Name → Items with that usage flag
```

**Check Group Assignment**:
```xml
<!-- In types.xml -->
<type name="AKM">
    <usage name="Military"/>  <!-- Must match group -->
</type>

<!-- In mapgrouppos.xml -->
<group name="Military">
    <!-- Buildings where Military items spawn -->
</group>
```

### Custom Spawn Locations

**Problem**: Want items to spawn in custom locations

**Method 1: Add to Existing Group**
```xml
<group name="Military">
    <container name="my_custom_building"/>
    <!-- Add your building classname -->
</group>
```

**Method 2: Create New Group**
```xml
<group name="CustomGroup" default="1">
    <container name="my_building_1"/>
    <container name="my_building_2"/>
</group>

Then in types.xml:
<type name="MyItem">
    <usage name="CustomGroup"/>
</type>
```

**Method 3: Use Events.xml**
```xml
<!-- For dynamic spawns -->
<event name="CustomLootEvent">
    <nominal>5</nominal>
    <min>3</min>
    <max>10</max>
    <lifetime>3600</lifetime>
    <restock>0</restock>
    <saferadius>0</saferadius>
    <distanceradius>0</distanceradius>
    <cleanupradius>0</cleanupradius>
    <pos>4512.45 8912.12</pos>  <!-- X Z coordinates -->
</event>
```

---

## Events.xml Issues

### "Event Not Spawning"

**Problem**: Helicopter crashes, police cars, etc. not appearing

**Debug Checklist**:

**1. Verify Nominal**
```xml
<event name="StaticHeliCrash">
    <nominal>3</nominal>  <!-- Max concurrent -->
    <min>2</min>          <!-- Min to maintain -->
    <max>5</max>          <!-- Hard cap -->
</event>

Nominal = 0 disables event!
```

**2. Check Lifetime**
```xml
<event name="StaticHeliCrash">
    <lifetime>3600</lifetime>  <!-- Exists for 1 hour -->
    <restock>0</restock>       <!-- Time between spawns -->
</event>

lifetime = 0 means permanent (until server restart)
```

**3. Verify Position**
```xml
<event name="StaticHeliCrash">
    <pos>4512.45 8912.12</pos>  <!-- X Z (not X Y Z!) -->
</event>

Check coordinates:
- Must be on map
- Use iZurvive to verify
- Z = second coordinate (not third!)
```

**4. Check Map Limit**
```xml
<event name="StaticHeliCrash">
    <limit>mixed</limit>  <!-- or "parent", "child" -->
</event>

Limits:
- mixed: Counts ALL instances
- parent: Only parent objects
- child: Only child objects
```

### Custom Event Not Working

**Problem**: Created custom event but nothing happens

**Required Structure**:
```xml
<!-- events.xml -->
<event name="MyCustomEvent">
    <nominal>5</nominal>
    <min>3</min>
    <max>10</max>
    <lifetime>3600</lifetime>
    <restock>1800</restock>
    <saferadius>50</saferadius>
    <distanceradius>50</distanceradius>
    <cleanupradius>100</cleanupradius>
    <secondary>MySecondaryEvent</secondary>
    <pos>X Z</pos>  <!-- Spawn location -->
</event>

<!-- Also need in cfgeventspawns.xml -->
<event name="MyCustomEvent">
    <zone smin="0" smax="0" dmin="1" dmax="3" r="50"/>
</event>
```

**Link to Spawnable Items**:
```xml
<!-- cfgspawnabletypes.xml -->
<type name="MyCustomEvent">
    <attachments chance="1.00">
        <item name="AKM" chance="0.50"/>
        <item name="Ammo_762x39" chance="0.80"/>
    </attachments>
    <cargo chance="0.75">
        <item name="MilitaryBoots" chance="0.30"/>
    </cargo>
</type>
```

---

## ServerDZ.cfg Issues

### "Server Won't Start" (Config Error)

**Problem**: serverDZ.cfg has syntax errors

**Common Mistakes**:

**Missing Commas**:
```json
// Wrong
{
    "hostname": "My Server"
    "maxPlayers": 60  // Missing comma!
}

// Correct
{
    "hostname": "My Server",
    "maxPlayers": 60
}
```

**Trailing Commas**:
```json
// Wrong
{
    "hostname": "My Server",
    "maxPlayers": 60,  // Trailing comma before }
}

// Correct (no trailing comma)
{
    "hostname": "My Server",
    "maxPlayers": 60
}
```

**Wrong Quotes**:
```json
// Wrong - curly/smart quotes
{
    "hostname": "My Server"
}

// Correct - straight quotes
{
    "hostname": "My Server"
}
```

**Invalid Values**:
```json
{
    "maxPlayers": "60",  // Wrong - should be number
    "disableThirdPerson": "true",  // Wrong - should be boolean
    "timeStampFormat": Full  // Wrong - should be quoted
}

// Correct
{
    "maxPlayers": 60,
    "disableThirdPerson": true,
    "timeStampFormat": "Full"
}
```

### Server Settings Not Applied

**Problem**: Changed settings but server ignores them

**Verify Config Path**:
```batch
REM Check startup parameter
DayZServer_x64.exe -config=serverDZ.cfg

# Ensure file exists at that path!
```

**Check File Permissions**:
```
File must be:
- Not read-only
- Writable by server process
- Correct encoding (UTF-8)
```

**Restart Required**:
```
Most settings require server restart:
- Server name
- Max players
- Password
- Gameplay settings

No restart needed:
- MOTD (message of the day)
- Some admin settings
```

---

## JSON Config Issues

### Economy.json Problems

**Problem**: Custom economy settings not working

**Validate JSON**:
```
Use online validator:
https://jsonlint.com/

Paste your JSON
Fix any errors shown
```

**Common Structure**:
```json
{
    "version": "1",
    "data": {
        "item1": {
            "nominal": 10,
            "min": 5,
            "spawnWeight": 1.0,
            "variants": ["Red", "Blue"]
        }
    }
}
```

### Trader Config Issues (Expansion/TraderPlus)

**Problem**: Trader items not showing or wrong prices

**Check Item Classnames**:
```json
{
    "Items": [
        {
            "ClassName": "AKM",  // Must be EXACT classname!
            "Price": 15000,
            "Stock": 10
        }
    ]
}

Test classname in-game:
- Spawn item
- Check if correct one appears
```

**Verify Trader Zone**:
```json
{
    "Position": [4512.45, 0, 8912.12],  // X Y Z
    "Radius": 50.0
}

Check position:
- Use iZurvive
- Use DayZ Editor
- Test in-game
```

**Check Categories**:
```json
{
    "Categories": [
        {
            "Category": "Weapons",
            "Items": [...]
        }
    ]
}

Category names are case-sensitive!
```

---

## XML Validation

### Using XML Validators

**Online Validators**:
```
- https://www.xmlvalidation.com/
- https://codebeautify.org/xmlvalidator

Paste XML
Check for errors
```

**Notepad++ Plugin**:
```
1. Install Notepad++
2. Plugins → Plugin Admin
3. Install "XML Tools"
4. Plugins → XML Tools → Validate Now
```

**Command Line (xmllint)**:
```bash
# Linux/Mac
xmllint --noout types.xml

# Windows (with Git Bash or WSL)
xmllint --noout types.xml

No output = valid
Errors shown if invalid
```

### Common XML Errors

**Unclosed Tags**:
```xml
<!-- Wrong -->
<type name="AKM">
    <nominal>10</ nominal>  <!-- Space in closing tag! -->

<!-- Correct -->
<type name="AKM">
    <nominal>10</nominal>
```

**Attribute Quotes**:
```xml
<!-- Wrong -->
<type name=AKM>

<!-- Correct -->
<type name="AKM">
```

**Special Characters**:
```xml
<!-- Wrong -->
<type name="Item&Stuff">

<!-- Correct -->
<type name="ItemAndStuff">
<!-- or -->
<type name="Item&amp;Stuff">

Escape these:
& → &amp;
< → &lt;
> → &gt;
" → &quot;
' → &apos;
```

---

## Configuration Best Practices

### Backup Before Editing

**Always**:
```batch
REM Before editing
copy types.xml types.xml.backup
copy serverDZ.cfg serverDZ.cfg.backup

# Linux
cp types.xml types.xml.backup
```

### Use Version Control

**Git for Configs**:
```bash
git init
git add *.xml *.json *.cfg
git commit -m "Working configuration"

# After changes
git diff  # See what changed
git commit -m "Increased AKM spawn rate"
```

### Test Changes Incrementally

**Process**:
```
1. Make ONE change
2. Validate file
3. Test on server
4. Verify it works
5. Commit/backup
6. Repeat
```

### Document Your Changes

**Add Comments**:
```xml
<!-- MODIFIED: Increased spawn rate for testing 2024-01-15 -->
<type name="AKM">
    <nominal>20</nominal>  <!-- Was: 10 -->
</type>
```

```json
{
    "_comment": "Modified weapon prices 2024-01-15",
    "Price": 20000
}
```

---

## Debugging Tools

### Log Analysis

**Enable Economy Logs**:
```batch
# Startup parameter
-dologs

# Creates detailed economy logs
```

**Check Logs**:
```
ServerProfile/DayZServer_*.RPT
ServerProfile/script.log

Search for:
- Your item classname
- "spawn"
- "economy"
- Error messages
```

### In-Game Testing

**Admin Commands**:
```
// Spawn item to test
#spawn AKM

// Check current count
#checkitem AKM

// Teleport to location
#teleport 4512 8912
```

**Use DayZ Editor**:
```
1. Subscribe to DayZ Editor mod
2. Load in single player
3. Place objects at coordinates
4. Test spawns visually
5. Export coordinates
```

---

## Recovery from Broken Configs

### Server Won't Start

**Emergency Fix**:
```
1. Restore backup config
2. If no backup, use vanilla config:
   - Delete ServerProfile/
   - Server recreates defaults

3. Gradually re-add changes
4. Test after each change
```

### Corrupted Economy

**Reset Economy**:
```
1. Stop server
2. Delete: ServerProfile/storage_*
3. Server regenerates on start
4. Fresh economy state

WARNING: Resets world state!
- Vehicles gone
- Bases persist (if using persistence)
- Player characters persist
```

---

## Configuration Templates

### Minimal types.xml Entry
```xml
<type name="MyItem">
    <nominal>10</nominal>
    <lifetime>3600</lifetime>
    <restock>1800</restock>
    <min>5</min>
    <quantmin>-1</quantmin>
    <quantmax>-1</quantmax>
    <cost>100</cost>
    <flags count_in_cargo="0" count_in_hoarder="0" count_in_map="1" count_in_player="0" crafted="0" deloot="0"/>
    <category name="tools"/>
    <usage name="Town"/>
    <value name="Tier1"/>
</type>
```

### Minimal Event Entry
```xml
<event name="MyEvent">
    <nominal>5</nominal>
    <min>3</min>
    <max>10</max>
    <lifetime>3600</lifetime>
    <restock>1800</restock>
    <saferadius>50</saferadius>
    <distanceradius>50</distanceradius>
    <cleanupradius>100</cleanupradius>
    <pos>X Z</pos>
</event>
```

### Basic serverDZ.cfg
```json
{
    "hostname": "My DayZ Server",
    "maxPlayers": 60,
    "password": "",
    "passwordAdmin": "adminpass",
    "serverTime": "SystemTime",
    "serverTimeAcceleration": 4,
    "serverNightTimeAcceleration": 8,
    "guaranteedUpdates": 1,
    "loginQueueConcurrentPlayers": 5,
    "loginQueueMaxPlayers": 100,
    "instanceId": 1,
    "storageAutoFix": 1
}
```

---

**Pro Tip**: Always validate XML/JSON files BEFORE uploading to server. Use validators to catch syntax errors early!

