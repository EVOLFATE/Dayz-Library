# DayZ Editor Integration Guide

## Overview

The DayZ Editor is a powerful 3D environment creation tool that allows you to design custom areas, place objects, test mechanics, and export builds directly to your server. This guide covers complete integration with interactive maps and coordinate workflows.

## What is DayZ Editor?

**Type**: Open-source 3D map editing mod  
**Steam Workshop**: https://steamcommunity.com/sharedfiles/filedetails/?id=2250764298  
**GitHub**: https://github.com/TheDevilsKnock/DayZ-EditorDK/

### Core Features
- **Offline Building**: Create without server load
- **3D Environment**: Full in-game visual editor
- **Object Placement**: Any in-game item/building
- **Terrain Painting**: Trees, grass, textures
- **Import/Export**: Load/save builds to files
- **Mod Support**: Works with modded items
- **Coordinate Export**: Extract precise X,Y,Z positions
- **Server Deployment**: Export to init.c or .vpp format

## Installation

### Client Installation
```bash
# Via Steam Workshop
1. Subscribe to "DayZ-Editor" on Steam Workshop
2. Launch DayZ
3. Go to: Main Menu > Mods
4. Enable: @DayZ-Editor
5. Restart DayZ

# Manual Installation
1. Download mod files
2. Extract to: DayZ/!Workshop/@DayZ-Editor/
3. Add to launch parameters: -mod=@DayZ-Editor
```

### Server Installation
```bash
# For testing exported builds
1. Subscribe to "DayZ Editor Loader" on Workshop
2. Install on server: @DayZ-Editor-Loader
3. Or use BuilderLoader mod
4. Add to server startup: -mod=@DayZ-Editor-Loader
```

## Opening the Editor

### In-Game Access
```
1. Launch DayZ with Editor mod enabled
2. Main Menu > Editor
3. Or press: Scroll Lock (default key binding)
4. Select map: Chernarus+, Livonia, Sakhal, etc.
5. Choose spawn location
6. Click "Enter Editor"
```

### Editor Interface
- **F1**: Toggle help menu
- **F2**: Copy object position
- **F3**: Object properties
- **F4**: Save project
- **ESC**: Editor menu
- **Insert**: Place object
- **Delete**: Remove selected object
- **Ctrl+Z**: Undo
- **Ctrl+Y**: Redo

## Working with Coordinates

### Getting Coordinates

#### Method 1: Object Position
```javascript
// Select any object in editor
// Press F2 to copy position
// Clipboard format:
vector position = "7500.5 0.0 5800.3";

// Extract coordinates:
X = 7500.5
Y = 0.0 (altitude)
Z = 5800.3

// 2D Map coordinates:
Map X = 7500.5
Map Y = 5800.3 (Z in 3D = Y on 2D map)
```

#### Method 2: Camera Position
```javascript
// Open console (` key)
// Type: GetCameraPosition();
// Output: <7500.5, 0.0, 5800.3>

// Use for:
- Scouting locations
- Finding center points
- Planning views
```

#### Method 3: Player Position
```javascript
// Spawn into editor
// Press key to show position (configure in settings)
// Or use: GetGame().GetPlayer().GetPosition();
// Returns current standing position
```

### Using Coordinates with Maps

#### Export to iZurvive
```
1. Get coordinates from Editor (e.g., 7500, 5800)
2. Open iZurvive.com
3. Click search icon
4. Enter coordinates: 7500 5800
5. Map centers on location
6. Place marker for reference
```

#### Export to WOBO Tools
```
1. Get X,Z coordinates
2. Open WOBO Tools map
3. Click map at approximate location
4. Fine-tune using coordinate display
5. Use for loot planning
```

#### Export to DZB Tools
```
1. Copy coordinates from Editor
2. Open DZB Tools (https://app.dzbtools.com/tools)
3. Select Territory Editor
4. Click "Add Point"
5. Paste X,Z coordinates
6. Design territories around position
```

## Base Planning Workflow

### Step-by-Step Base Design

#### Phase 1: Location Scouting
```
1. Open iZurvive or in-game
2. Find suitable base location:
   - Near water source
   - Defendable terrain
   - Away from high-traffic areas
   - Access to loot
3. Mark coordinates on iZurvive
4. Note: X=7500, Z=5800 (example)
```

#### Phase 2: Editor Design
```
1. Open DayZ Editor
2. Teleport to coordinates:
   - Open console: `
   - Type: GetGame().GetPlayer().SetPosition(vector(7500, 0, 5800));
3. Place base objects:
   - Walls, gates, towers
   - Storage containers
   - Workbenches
   - Decorative items
4. Test layout:
   - Walk through base
   - Check sightlines
   - Verify door placements
   - Test vehicle access
5. Adjust as needed
```

#### Phase 3: Coordinate Export
```
1. Select all base objects:
   - Ctrl+A or drag selection box
2. Export options:
   
   Option A - Copy All Positions:
   - F2 on each object
   - Paste to text file
   
   Option B - Export Project:
   - ESC > Save Project
   - File saved to: DayZ/Profiles/DayZEditor/
   
   Option C - Use Export Tool:
   - ESC > Export > init.c
   - Generates code file
```

#### Phase 4: Convert for Server
```
1. Open exported file
2. Extract spawn commands
3. Convert format if needed:

From Editor format:
vector pos = "7500 0 5800";
vector ori = "0 0 0";

To init.c format:
CreateObject("LandWatchtower", "7500 0 5800", "0 0 0");

Or to XML format:
<object name="LandWatchtower" pos="7500 0 5800" ypr="0 0 0"/>
```

#### Phase 5: Server Deployment
```
1. Upload files via FTP:
   - init.c to: mpmissions/[mission]/
   - Or .vpp to: mpmissions/[mission]/storage_1/
   
2. If using DayZ Editor Loader:
   - Place .dze file in: Editor/Exports/
   - Loader auto-loads on server start
   
3. If using init.c:
   - Add to: MissionServer.c > void SetRandomHealth()
   - Include spawn commands
   
4. Restart server
5. Check in-game at coordinates
```

### Advanced Base Planning

#### Multi-Location Bases
```
# Base 1 (Main Camp): 7500, 5800
# Base 2 (Outpost): 8200, 6300
# Base 3 (Storage): 7100, 5400

1. Design each in Editor
2. Export separately
3. Mark all on iZurvive
4. Color-code markers
5. Note travel times between
```

#### Territory Integration
```
1. Design base in Editor
2. Export coordinates
3. Open DZB Tools Territory Editor
4. Place territory flag at center
5. Set radius to cover base
6. Export territory XML
7. Upload both base + territory files
```

#### Loot Route Planning
```
1. Open Editor at base coordinates
2. Teleport to nearby loot locations
3. Note coordinates of each
4. Map in iZurvive:
   - Base (green marker)
   - Loot spots (yellow markers)
   - Route (draw path)
5. Measure distances
6. Plan safest route
```

## Object Placement Best Practices

### Precise Positioning

#### Grid Snapping
```
// Enable in Editor settings
Grid Size: 1m, 5m, 10m options
Snap to Grid: On/Off
Rotation Snap: 15°, 30°, 45°, 90°

// Manual precision:
1. Place object roughly
2. Press F3 for properties
3. Enter exact coordinates
4. Enter exact rotation
5. Apply
```

#### Height Adjustment
```
// Y-axis (altitude) important for:
- Floating platforms
- Multi-story bases
- Bridges
- Elevated positions

// Find ground level:
1. Place object
2. Check Y coordinate
3. Adjust up/down
4. Use in increments (e.g., floor height = 3.0)
```

#### Rotation
```
// Yaw, Pitch, Roll (Y, P, R)
Yaw: 0-360° (rotation around vertical axis)
Pitch: Tilt forward/back
Roll: Tilt left/right

// Common rotations:
North: 0°
East: 90°
South: 180°
West: 270°

// Align with roads:
1. Check road direction
2. Rotate to match
3. Use compass in Editor
```

### Object Categories

#### Static Objects (Buildings)
```
Category: Structures
Examples:
- Land_House_*
- Land_Barn_*
- Land_Shed_*

Notes:
- Cannot be moved in-game
- Good for permanent bases
- No lifetime/decay
```

#### Base Building Items
```
Category: Base Building
Examples:
- Fence_*
- Watchtower_*
- BarbedWire_*

Notes:
- Can be destroyed in-game
- Subject to raiding
- Set health in properties
```

#### Containers
```
Category: Storage
Examples:
- SeaChest
- WoodenCrate
- Barrel_*

Notes:
- Can store items
- Configure inventory size
- Set persistence
```

#### Decorative
```
Category: Decorations
Examples:
- Furniture
- Props
- Clutter

Notes:
- Visual only (usually)
- Adds realism
- Minimal performance impact
```

## Terrain Editing

### Painting Trees/Grass
```
1. Open Editor
2. Select Terrain Brush
3. Choose:
   - Tree type
   - Grass/bush type
   - Density
   - Brush size
4. Paint on terrain
5. Remove with eraser mode
6. Export as .vpp for server
```

### Clutter Cutter
```
// Remove existing trees/grass
1. Place "ClutterCutter" object
2. Set radius (e.g., 50m)
3. Clears area for building
4. Export with base build
```

### Custom Terrain Objects
```
// Add rocks, debris, etc.
1. Search: "Land_Rock_", "Land_Rubble_"
2. Place naturally
3. Vary rotation
4. Group objects for realism
```

## Integration with Other Tools

### DZB Tools Integration

#### Territory Export
```
1. Design base in Editor
2. Note center coordinates
3. Open DZB Tools (app.dzbtools.com/tools)
4. Territory Editor > New Territory
5. Enter center coordinates
6. Set radius
7. Export XML
```

#### Spawn Point Creation
```
1. Find good spawn locations in Editor
2. Export coordinates
3. DZB Tools > Spawn Editor
4. Add spawn points at coordinates
5. Configure spawn loadout
6. Export XML
```

### DayZ Tool Hub Integration

#### Build Relocator
```
1. Export build from Editor (init.c format)
2. Open Tool Hub Build Relocator
3. Upload file
4. Enter new coordinates
5. Tool adjusts all object positions
6. Download relocated build
```

### iZurvive Integration

#### Visual Planning
```
1. Open iZurvive
2. Place markers at planned locations:
   - Base: 7500, 5800
   - Watch towers: 7510, 5820 / 7490, 5820
   - Gates: 7500, 5790 / 7500, 5810
   - Storage: 7500, 5800 (center)
3. Visualize layout
4. Open Editor at coordinates
5. Build matching design
```

#### Team Coordination
```
1. Create iZurvive group
2. Share base coordinates
3. Team members scout in-game
4. Mark threats/resources nearby
5. Designer builds in Editor
6. Deploy when safe
```

## Exporting Formats

### init.c Format
```c
void main()
{
    // Create objects
    GetGame().CreateObject("Land_Watchtower", "7500 0 5800", false, true);
    GetGame().CreateObject("Fence", "7505 0 5800", false, true);
    
    // With rotation
    Object obj = GetGame().CreateObject("Gate", "7500 0 5795", false, true);
    obj.SetOrientation("0 90 0"); // Yaw Pitch Roll
}
```

### XML Format
```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<objects>
    <object name="Land_Watchtower" pos="7500 0 5800" ypr="0 0 0" scale="1.0"/>
    <object name="Fence" pos="7505 0 5800" ypr="0 0 0" scale="1.0"/>
    <object name="Gate" pos="7500 0 5795" ypr="0 90 0" scale="1.0"/>
</objects>
```

### JSON Format (Expansion Mod)
```json
{
    "Objects": [
        {
            "name": "Land_Watchtower",
            "pos": [7500.0, 0.0, 5800.0],
            "ypr": [0.0, 0.0, 0.0],
            "scale": 1.0
        },
        {
            "name": "Fence",
            "pos": [7505.0, 0.0, 5800.0],
            "ypr": [0.0, 0.0, 0.0],
            "scale": 1.0
        }
    ]
}
```

### .dze Format (Editor Native)
```
// Binary format
// Best for Editor Loader mod
// Preserves all object properties
// Not human-readable
```

## Common Workflows

### Workflow 1: Simple Base
```
1. iZurvive: Scout location, mark coordinates
2. Editor: Teleport to location
3. Editor: Place walls, gate, storage
4. Editor: Export to init.c
5. FTP: Upload init.c to server
6. Server: Restart
7. In-Game: Verify build
```

### Workflow 2: Territory Base
```
1. iZurvive: Plan territory shape
2. DZB Tools: Create territory polygon
3. Editor: Build inside territory
4. Export: Base as init.c, territory as XML
5. Upload: Both files to server
6. Configure: Territory flags, permissions
7. Test: In-game functionality
```

### Workflow 3: Loot Route
```
1. Editor: Scout multiple loot buildings
2. Editor: Note each building coordinate
3. iZurvive: Mark all buildings
4. iZurvive: Draw route between them
5. iZurvive: Measure distances
6. iZurvive: Share with team
7. In-Game: Follow route
```

### Workflow 4: Relocation
```
1. Editor: Build at temporary location (0,0,0)
2. Editor: Export all objects
3. iZurvive: Find final location coordinates
4. Tool Hub: Use Build Relocator
5. Tool Hub: Enter final coordinates
6. Tool Hub: Download adjusted build
7. Server: Deploy
```

## Troubleshooting

### Objects Not Spawning
**Problem**: Exported objects don't appear on server  
**Solutions**:
- Check init.c syntax
- Verify coordinates are within map bounds
- Ensure object classnames are correct
- Check server logs for errors
- Verify mod dependencies (if using modded objects)

### Wrong Position
**Problem**: Objects spawn in wrong location  
**Solutions**:
- Double-check coordinate format (X Y Z)
- Verify you're on correct map
- Check for coordinate system confusion (X,Z vs X,Y)
- Use Tool Hub Relocator to adjust

### Objects Underground/Floating
**Problem**: Y-coordinate wrong  
**Solutions**:
- Use 0 for Y (game auto-adjusts to ground)
- Or measure exact terrain height in Editor
- Check for terrain modifications
- Test in Editor before deploying

### Rotation Issues
**Problem**: Objects facing wrong direction  
**Solutions**:
- Use in-game compass to verify direction
- Check YPR values (Yaw, Pitch, Roll)
- Remember: 0°=North, 90°=East, 180°=South, 270°=West
- Test rotation in Editor first

## Performance Considerations

### Object Count
- **Recommended**: < 500 objects per area
- **Maximum**: Depends on server hardware
- **Impact**: More objects = lower FPS

### Optimization Tips
1. Use fewer, larger objects when possible
2. Group decorative items sparingly
3. Avoid excessive clutter
4. Test performance in Editor before deploying
5. Monitor server FPS after deployment

## Related Documentation

- [Live Location Tracking](live-tracking.md)
- [Territory Planning](territory-planning.md)
- [Base Building Guide](../custom-content/base-building.md)
- [DZB Tools Guide](../utility-tools/dzb-tools.md)
- [Server Deployment](../server/mod-installation.md)

## External Resources

- **DayZ Editor Workshop**: https://steamcommunity.com/sharedfiles/filedetails/?id=2250764298
- **DayZ Editor GitHub**: https://github.com/TheDevilsKnock/DayZ-EditorDK/
- **DZB Tools**: https://app.dzbtools.com/
- **DayZ Tool Hub**: https://www.dayztoolhub.com/
- **iZurvive**: https://www.izurvive.com/
- **Editor Documentation**: https://app.dzbtools.com/wiki/page/dayz-editor
