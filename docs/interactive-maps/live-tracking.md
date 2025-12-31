# Live Location Tracking & Real-Time Interactive Maps

## Overview

Live location tracking in DayZ allows players and server administrators to monitor positions, share markers, and coordinate activities in real-time. This guide covers all major interactive mapping tools and their real-time tracking capabilities.

## iZurvive - The Standard for Live Tracking

### Overview
**Website**: https://www.izurvive.com/  
**Platforms**: Web, iOS, Android  
**Cost**: Free with premium features

iZurvive is the most popular and feature-rich interactive map solution for DayZ, offering the only true live tracking system through group synchronization.

### Core Features

#### Real-Time Group Tracking
- **Create Groups**: No account required, just username
- **Instant Sync**: All markers sync in real-time to all group members
- **Multi-Player Markers**: Each player can place their own position marker
- **Custom Markers**: Add loot spots, vehicles, bases, danger zones, meeting points
- **Route Planning**: Draw paths and waypoints that sync to whole team

#### Map Features
- **High-Resolution Maps**: All official maps (Chernarus+, Livonia, Sakhal)
- **Coordinate Display**: Click anywhere for exact X,Y,Z coordinates
- **Distance Measurement**: Measure routes and ranges
- **Elevation Data**: See terrain height for planning
- **Grid Overlay**: Military-style grid references
- **Search Function**: Find locations quickly
- **Loot Database**: Filter by item types
- **Offline Mode**: Download maps for offline use

### How to Use iZurvive for Live Tracking

#### Step 1: Create a Group
```
1. Open iZurvive website or app
2. Click "Groups" or team icon
3. Click "Create Group"
4. Enter a group name
5. Choose a username (no registration needed)
6. Share the group code with teammates
```

#### Step 2: Join a Group
```
1. Receive group code from team leader
2. Click "Join Group" 
3. Enter group code
4. Choose your username
5. Click "Join"
```

#### Step 3: Place Your Position
```
1. Identify your in-game position (town signs, GPS, landmarks)
2. Find matching location on iZurvive map
3. Click/tap to place marker
4. Label it with your name
5. Marker instantly appears for all group members
```

#### Step 4: Coordinate Movement
```
1. Place markers for:
   - Your current position
   - Destination/meeting point
   - Loot locations
   - Danger areas (PvP, zombies)
   - Vehicle locations
   - Base locations
2. Update markers as you move
3. Use draw tools for routes
4. Use distance tool to plan travel times
```

### Advanced iZurvive Features

#### Marker Types
- **Player Position**: Where you are now
- **Destination**: Where you're going
- **Loot**: Important items/buildings
- **Danger**: Enemy activity, zombies
- **Vehicle**: Car/truck locations
- **Base**: Camp/storage locations
- **Waypoint**: Navigation points
- **Custom**: Any note or marker

#### Sharing Options
- **Group Sync**: Real-time for team members
- **Share Link**: Send map view to anyone
- **Screenshot**: Export current map view
- **Coordinate Copy**: Copy X,Y for paste

#### Mobile App Advantages
- **GPS Integration**: Use phone GPS for approximate in-game position
- **Quick Access**: Faster than web browser
- **Notifications**: Alert when group members add markers
- **Battery Saver**: Optimized for long sessions

### Limitations
- **Manual Position**: Must manually update your position (no automatic GPS from game)
- **Internet Required**: Live sync needs active connection
- **No In-Game Overlay**: Cannot overlay on DayZ screen

## Alternative Map Tools

### WOBO Tools Map
**Website**: https://wobo.tools/toolbox/dayz-map-tool-1693/

#### Features
- Interactive maps for Chernarus, Livonia, Sakhal
- Water source locations
- Vehicle spawn points
- Loot location database
- Dynamic event markers (helicrashes, etc.)
- Map measurement tool
- Night brightness toggle
- Search functionality
- **No Live Tracking**: Does not support group sync

#### Best Used For
- Reference during gameplay
- Planning loot routes
- Finding water sources
- Vehicle spawn farming
- Solo play planning

### DayZ Intel (GInfo.gg)
**Website**: https://dayz.ginfo.gg/

#### Features
- 3D terrain visualization
- Advanced loot filters
- Vehicle spawns
- Animal locations
- Well locations
- Garden plot locations
- Updated for latest patches
- **No Live Tracking**: Individual use only

#### Best Used For
- Visual terrain analysis
- Detailed loot planning
- Vehicle spawn memorization
- Finding specific resources

### DayZ Interactive Map (XAM)
**Website**: https://dayz.xam.nu/

#### Features
- ChernarusPlus interactive map
- Building-level loot info
- Marker placement
- Basic squad sharing
- Steam Workshop map support
- **Limited Sync**: Markers can be shared via links but no real-time sync

#### Best Used For
- Building-specific loot info
- Manual marker sharing
- Custom map exploration

### DayZ Tool Hub
**Website**: https://www.dayztoolhub.com/map.html

#### Features
- Multiple map support
- Marker placement
- Coordinate tools
- Integration with other tools
- **No Live Tracking**: Static markers only

## In-Game Position Finding

### Method 1: Town Signs
- Most towns have entrance signs with names
- Cross-reference with map to find position
- Most accurate method

### Method 2: GPS Receiver
- Rare in-game item
- Shows exact grid coordinates
- Must be powered with battery
- Format: Grid letter-number (e.g., "042 104")

### Method 3: Compass + Map
1. Use in-game compass
2. Identify landmarks (mountains, coast, roads)
3. Triangulate position
4. Update map tool manually

### Method 4: iZurvive Coordinates
1. Find in-game GPS coordinates or town
2. Enter into iZurvive search
3. Map centers on location
4. Place marker

### Method 5: Trail and Error
1. Spawn and check spawn town
2. Read road signs as you travel
3. Update position periodically
4. Use coastline as reference

## Live Tracking for Server Administrators

### Admin Map Plugins
Some server mods offer admin-only live tracking:

#### VPP Admin Tools
- **In-Game ESP**: See all players on admin map
- **Teleport**: Click map to teleport
- **Heatmap**: Player activity zones
- **No External Access**: Admin must be in-game

#### CFTools Cloud
- **Web Dashboard**: See players on map
- **Real-Time**: Updates every few seconds
- **Admin Actions**: Teleport, kick, ban from map
- **Session Data**: See player paths over time
- **Requires**: CFTools subscription + server integration

#### DayZ Server Tools (DST)
- **Discord Bot Integration**: Query player positions
- **Map Commands**: Show player on map via Discord
- **Session Tracking**: Historical position data
- **Requires**: DST bot + server setup

### Server-Side Tracking Setup

#### CFTools Integration
```bash
# Install CFTools mod on server
@CFTools

# Register server at https://cftools.com/
# Link server ID to dashboard
# Configure permissions
# Access dashboard: https://app.cftools.cloud/

# Features accessible:
- Live player map
- Player search
- Kick/ban from map interface
- Teleport players
- Session analytics
```

#### VPP Admin Tools Map
```bash
# Install VPP Admin Tools
@VPPAdminTools
@CF (Community Framework - required)

# Add admin Steam64ID to SuperAdmins.txt
# In-game: Press HOME key to open menu
# Navigate to: Map > Player Positions
# View all online players on map
```

## Coordinate Systems Explained

### DayZ Coordinate Format
- **Format**: X Y Z or X Z (Y is altitude, often omitted)
- **Example**: 7500 5800 or 7500.0 0.0 5800.0
- **Range**: 0 to 15360 (Chernarus+), varies by map
- **Origin**: Southwest corner = 0,0

### Grid Coordinate Format
- **Format**: Letter-Number (e.g., E7, M12)
- **Letters**: West to East (A-O for Chernarus+)
- **Numbers**: South to North (1-15 for Chernarus+)
- **Conversion**: Divide X,Y by ~1024

### GPS Format (In-Game)
- **Format**: 3-digit bearing (e.g., "042 104")
- **First Number**: Degrees east (042 = 42° east)
- **Second Number**: Degrees north (104 = 104° north)

### Converting Between Formats

#### X,Y to Grid
```
Letter = floor(X / 1024)
Number = floor(Y / 1024)
Example: 7500, 5800
Letter = 7500 / 1024 = 7.32 = "H" (A=0, B=1... H=7)
Number = 5800 / 1024 = 5.66 = 6
Result: H6
```

#### Grid to X,Y (Center of Grid)
```
X = (Letter_Index × 1024) + 512
Y = (Number × 1024) + 512
Example: E7
Letter E = 4 (A=0, B=1, C=2, D=3, E=4)
X = (4 × 1024) + 512 = 4608
Y = (7 × 1024) + 512 = 7680
Result: 4608, 7680
```

## Best Practices for Live Tracking

### Team Coordination
1. **Designate Map Manager**: One person maintains primary map
2. **Color Code Players**: Assign each player a marker color
3. **Update Frequency**: Update position every 5-10 minutes
4. **Use Landmarks**: Reference nearby towns/buildings
5. **Mark Threats**: Immediately mark enemy positions
6. **Clear Old Markers**: Remove outdated markers regularly

### Security Considerations
1. **Private Groups**: Use unique group codes
2. **Don't Share Publicly**: Keep group codes secret
3. **Base Security**: Be cautious marking base locations
4. **Enemy Tracking**: Never share group code with untrusted players
5. **Alt-Tabbing**: Practice quick Alt+Tab for map checks

### Performance Tips
1. **Minimize Markers**: Too many markers cause clutter
2. **Use Categories**: Organize by marker type
3. **Mobile Data**: Use WiFi when possible to save data
4. **Battery**: Keep phone charged for long sessions
5. **Screen Brightness**: Reduce for battery savings

## Integration with DayZ Editor

### Exporting Coordinates from DayZ Editor

The DayZ Editor mod allows precise coordinate extraction:

```javascript
// In DayZ Editor, select object
// Press F2 to copy position
// Format: vector position = "7500 0 5800";

// Convert to map coordinates:
X = 7500
Z = 5800 (Y in game = Z on 2D map)
```

### Using Exported Coordinates
1. Copy coordinates from DayZ Editor
2. Open iZurvive or other map tool
3. Search or navigate to X,Z position
4. Place marker for reference
5. Use for base planning or mod placement

### Base Planning Workflow
1. **Scout in DayZ**: Find potential base location
2. **Mark on iZurvive**: Place marker with coordinates
3. **Design in Editor**: Use coordinates to build offline
4. **Export Build**: Convert to server files
5. **Deploy**: Upload to server via FTP

## Mobile App Comparison

| Feature | iZurvive | DayZ Companion | DayZ SA Offline Map |
|---------|----------|----------------|---------------------|
| Live Sync | ✅ Yes | ❌ No | ❌ No |
| Group Features | ✅ Yes | ❌ No | ❌ No |
| Offline Mode | ✅ Yes | ✅ Yes | ✅ Yes |
| Loot Database | ✅ Yes | ✅ Yes | ⚠️ Limited |
| Custom Markers | ✅ Yes | ✅ Yes | ✅ Yes |
| Multiple Maps | ✅ Yes | ⚠️ Limited | ✅ Yes |
| Distance Tool | ✅ Yes | ✅ Yes | ❌ No |
| Free | ✅ Yes | ✅ Yes | ✅ Yes |
| iOS | ✅ Yes | ✅ Yes | ✅ Yes |
| Android | ✅ Yes | ✅ Yes | ✅ Yes |

**Recommendation**: iZurvive for teams, others for solo offline reference

## Future Live Tracking Possibilities

### Potential Future Features
- **Automatic Position**: Game API integration (not currently possible)
- **In-Game Overlay**: HUD map overlay (mod-dependent)
- **Voice Integration**: Discord location sharing
- **AR Navigation**: Phone AR pointing to destinations
- **Smartwatch Support**: Quick map glance

### Community Requests
- Direct game integration
- Automatic player position updates
- Server-specific maps with custom locations
- Heat maps of player activity
- Integration with base building mods

## Troubleshooting Live Tracking

### iZurvive Group Not Syncing
**Problem**: Markers not appearing for team members  
**Solutions**:
1. Check internet connection
2. Refresh browser/restart app
3. Verify same group code
4. Check if group is full (max 30 members)
5. Clear browser cache
6. Try different browser

### Position Inaccurate
**Problem**: Map position doesn't match game  
**Solutions**:
1. Double-check town name
2. Use GPS in-game if available
3. Verify you're on correct map (Chernarus vs Livonia)
4. Check for map updates
5. Use multiple landmarks to triangulate

### Markers Disappearing
**Problem**: Placed markers vanish  
**Solutions**:
1. Check if group expired (inactive groups timeout)
2. Verify you're logged into group
3. Check if another member deleted it
4. Browser issue - try different device
5. Report to iZurvive support

### Can't Find Location
**Problem**: Can't locate yourself on map  
**Solutions**:
1. Travel to nearest town
2. Read all road signs
3. Use compass + coastline
4. Ask teammates familiar with area
5. Use sun position (east morning, west evening)

## Related Documentation

- [Interactive Maps Overview](chernarus.md)
- [DayZ Editor Integration](../development-tools/dayz-editor.md)
- [Coordinate Systems](territory-planning.md)
- [Server Admin Tools](../server/admin-tools.md)
- [Base Planning Guide](territory-planning.md)

## External Resources

- **iZurvive**: https://www.izurvive.com/
- **WOBO Tools**: https://wobo.tools/
- **DayZ Intel**: https://dayz.ginfo.gg/
- **XAM Map**: https://dayz.xam.nu/
- **DayZ Tool Hub**: https://www.dayztoolhub.com/
- **iZurvive Mobile (iOS)**: https://apps.apple.com/app/izurvive-dayz-maps/id585632597
- **iZurvive Mobile (Android)**: https://play.google.com/store/apps/details?id=com.innovaptor.izurvive
