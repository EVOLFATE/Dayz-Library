# Third-Party Tools Issues

## Common Problems with DayZ Third-Party Tools

This guide covers troubleshooting for all popular third-party tools used in DayZ modding and server administration.

---

## CFTools Suite

### CFTools Cloud Issues

#### Can't Connect Server to CFTools Cloud

**Problem**: Server won't connect to CFTools Cloud dashboard

**Solutions**:

**Verify API Key**:
```json
// serverDZ.cfg or startup parameters
{
    "cftools": {
        "serverApiId": "YOUR_SERVER_ID",
        "serverApiSecret": "YOUR_SECRET_KEY"
    }
}
```

**Check Firewall**:
```
Allow outbound connections to:
- api.cftools.cloud
- Port: 443 (HTTPS)
```

**Verify Mod Installation**:
```
1. Subscribe to CFTools on Workshop
2. Add to startup: -mod=@CF;@CFToolsModPack
3. Ensure CF loads BEFORE CFTools
4. Check server console for CFTools connection messages
```

**Common Issues**:
- Wrong API credentials → Check dashboard for correct values
- Server ID mismatch → Verify server is claimed in dashboard
- Firewall blocking → Allow CFTools domain
- Missing Community Framework → Install CF mod first

#### CFTools Discord Bot Not Responding

**Problem**: Discord bot commands don't work

**Solutions**:

**Verify Bot Setup**:
```
1. Bot is added to Discord server
2. Bot has proper permissions:
   - Send Messages
   - Embed Links
   - Read Message History
   - Add Reactions
3. Bot is online (green status)
```

**Check Command Permissions**:
```
Dashboard → Discord Integration → Command Permissions
- Enable commands for specific roles
- Check channel restrictions
```

**Test Connection**:
```
In Discord: !cftools ping
Should respond with: "Pong! Connection active"
```

#### CFTools Omega Not Launching

**Problem**: CFTools Omega desktop app won't start

**Solutions**:
```
1. Update to latest version
   Download: https://cftools.cloud/omega

2. Clear cache:
   Delete: %APPDATA%\CFTools\Omega\cache

3. Check for conflicting software:
   - Close DayZ Launcher
   - Close Steam overlay
   - Disable antivirus temporarily

4. Run as Administrator

5. Reinstall:
   - Uninstall completely
   - Delete remaining files
   - Fresh install
```

---

## DayZ Editor

### DayZ Editor Issues

#### Editor Won't Load

**Problem**: DayZ Editor doesn't start or crashes

**Solutions**:

**Verify Installation**:
```
1. Subscribe on Workshop:
   https://steamcommunity.com/sharedfiles/filedetails/?id=2250764298

2. Add to launch parameters:
   -mod=@DayZ Editor

3. Launch DayZ normally
   Editor available in main menu
```

**Check for Mod Conflicts**:
```
Common conflicts with:
- Custom UI mods
- Admin tools (VPP, COT)
- Some trader mods

Test with ONLY DayZ Editor loaded
```

**Update Editor**:
```
1. Unsubscribe from Workshop
2. Clear Workshop download cache
3. Resubscribe and download
```

#### Can't Export Objects

**Problem**: Export function doesn't work

**Solutions**:

**Enable Export Permissions**:
```
1. Ensure you're in single player OR
2. Have admin rights on server
3. Check editor settings for export path
```

**Output Location**:
```
Default export path:
C:\Users\[Username]\Documents\DayZ Editor\Exports\

Check this folder for exported files
```

**Export Formats**:
```
Available formats:
- .json (for traders, spawns)
- .xml (for mapgrouppos)
- .dze (editor save format)
```

#### Coordinates Don't Match iZurvive

**Problem**: Editor coordinates different from map coordinates

**Solutions**:

**Coordinate Conversion**:
```cpp
// Editor uses XYZ (world position)
// iZurvive uses grid coordinates

// Convert in both tools or use:
X = Grid X * 100
Z = Grid Y * 100
Y = Elevation
```

**Use Coordinate Tools**:
```
WOBO Tools: https://wobo.tools/dayz-map-coordinates-converter.php

Input: Editor XYZ
Output: iZurvive grid coordinates
```

---

## DZB Tools (BoosterZ)

### DZB Tools Issues

#### Tool Won't Launch

**Problem**: DZB Tools application doesn't start

**Solutions**:

**Install .NET Framework**:
```
Required: .NET Framework 4.7.2 or higher
Download: https://dotnet.microsoft.com/download/dotnet-framework
```

**Check Antivirus**:
```
DZB Tools may be flagged as false positive

Whitelist:
C:\Program Files\DZB Tools\
```

**Run as Administrator**:
```
Right-click → Run as Administrator
Some features require elevated permissions
```

#### Batch Operations Failing

**Problem**: Batch file processing doesn't complete

**Solutions**:

**Verify File Paths**:
```
- No special characters
- Keep paths under 260 characters
- Use absolute paths not relative
```

**Check File Permissions**:
```
Ensure you have write access to:
- Source files
- Destination folder
```

**Process in Smaller Batches**:
```
If processing many files:
1. Split into smaller groups
2. Process sequentially
3. Monitor for errors
```

---

## Universal API

### Universal API Issues

#### API Not Responding

**Problem**: API endpoints return no data

**Solutions**:

**Verify Mod Installation**:
```
1. Workshop: https://steamcommunity.com/sharedfiles/filedetails/?id=2116157322
2. Startup parameter: -mod=@UniversalAPI
3. Check mod is loaded in server console
```

**Check Port Configuration**:
```
// init.c or config
UniversalAPI.Port = 2302; // Default
UniversalAPI.Enabled = true;
```

**Test Connection**:
```bash
# Test API availability
curl http://YOUR_SERVER_IP:2302/api/v1/status

# Should return JSON with server info
```

**Firewall Rules**:
```
Allow inbound on API port (default 2302)
Protocol: TCP
Direction: Inbound
```

#### Webhook Not Sending

**Problem**: Discord webhooks not triggering

**Solutions**:

**Verify Webhook URL**:
```cpp
// In config
string webhookURL = "https://discord.com/api/webhooks/YOUR_WEBHOOK_ID/YOUR_WEBHOOK_TOKEN";
```

**Test Webhook Manually**:
```bash
curl -X POST "https://discord.com/api/webhooks/ID/TOKEN" \
  -H "Content-Type: application/json" \
  -d '{"content": "Test message"}'
```

**Check Rate Limits**:
```
Discord webhooks limited to:
- 30 requests per minute per webhook
- May be throttled if exceeded

Solution: Implement queue system or reduce frequency
```

#### Authentication Errors

**Problem**: API returns 401 Unauthorized

**Solutions**:

**Set API Key**:
```cpp
// In mod config
class UniversalAPI
{
    string APIKey = "your-secure-api-key";
    bool RequireAuth = true;
}
```

**Send API Key in Requests**:
```bash
curl -H "Authorization: Bearer YOUR_API_KEY" \
  http://SERVER_IP:2302/api/v1/players
```

---

## DayZ SA Launcher

### Launcher Issues

#### Mods Not Downloading

**Problem**: Workshop mods stuck downloading

**Solutions**:

**Clear Steam Download Cache**:
```
1. Steam → Settings → Downloads
2. Clear Download Cache
3. Restart Steam
4. Re-download mods
```

**Check Disk Space**:
```
Mods require significant space
Check: C:\Program Files (x86)\Steam\steamapps\workshop\content\221100
```

**Verify Workshop Subscription**:
```
1. Go to Steam Workshop page
2. Ensure you're subscribed
3. Check for errors on mod page
```

#### Can't Join Server (Mod Mismatch)

**Problem**: "Mod mismatch" or "You were kicked from the game"

**Solutions**:

**Verify Exact Mod Versions**:
```
Server may use specific versions
Check server description for required mods
```

**Update All Mods**:
```
1. Unsubscribe from all mods
2. Clear workshop cache
3. Resubscribe to exact server mod list
4. Verify download completed
```

**Check Mod Load Order**:
```
Some mods require specific load order:
1. Community Framework
2. Other dependency mods
3. Main mods
4. Map mods last
```

---

## iZurvive Issues

### iZurvive Issues

#### Live Location Not Working

**Problem**: Can't share location with team

**Solutions**:

**Enable GPS Sharing**:
```
1. Open iZurvive app/website
2. Settings → GPS
3. Enable "Share Location"
4. Create or join group
```

**Check Permissions** (Mobile):
```
iOS/Android:
Settings → iZurvive → Location → While Using
```

**Group Sync Issues**:
```
1. Ensure all members use same group code
2. Check internet connection
3. Refresh app (pull down to refresh)
4. Leave and rejoin group if stuck
```

#### Markers Not Syncing

**Problem**: Markers don't appear for team members

**Solutions**:
```
1. Verify everyone in same group
2. Check marker permissions (group settings)
3. Refresh map
4. Clear app cache and restart
```

---

## WOBO Tools Issues

### WOBO Tools Issues

#### Site Not Loading

**Problem**: wobo.tools won't open

**Solutions**:
```
1. Check internet connection
2. Try different browser
3. Clear browser cache
4. Disable ad blockers temporarily
5. Try mobile version
```

#### Calculators Not Working

**Problem**: Damage calculator or other tools not responding

**Solutions**:
```
1. Enable JavaScript
2. Update browser
3. Clear cookies and cache
4. Disable browser extensions
5. Try incognito/private mode
```

---

## Battlemetrics Issues

### Battlemetrics Issues

#### Server Not Showing on Battlemetrics

**Problem**: Your server doesn't appear in Battlemetrics

**Solutions**:

**Verify Server is Public**:
```json
// serverDZ.cfg
{
    "disableCrosshair": false,
    "disableThirdPerson": false,
    "internetServer": 1  // Must be 1 for public
}
```

**Check Steam Query Port**:
```
Default: Game port + 1
Example: Game on 2302, Query on 2303

Firewall must allow UDP on query port
```

**Wait for Discovery**:
```
New servers take 15-30 minutes to appear
Battlemetrics scans periodically
```

#### RCON Not Connecting

**Problem**: Can't connect to server via RCON

**Solutions**:

**Enable RCON**:
```json
// serverDZ.cfg or startup
{
    "BERConPort": 2310,
    "BERConPassword": "your-secure-password"
}
```

**Firewall Settings**:
```
Allow TCP on RCON port (default 2310)
May need to port forward if behind NAT
```

**Test RCON**:
```
Use BEC or other RCON tool to test connection
Verify password is correct
```

---

## VPP Admin Tools Issues

### VPP Admin Tools Issues

#### Admin Menu Not Opening

**Problem**: Can't access admin menu in-game

**Solutions**:

**Add Yourself as Admin**:
```xml
<!-- ServerProfile/VPPAdminTools/Permissions/SuperAdmins.txt -->
76561198012345678
```

**Verify Keybind**:
```
Default: Insert key
Can be changed in VPP settings
```

**Check Mod Loading**:
```
Startup: -mod=@VPP Admin Tools
Verify loaded in server console
```

#### Permission Issues

**Problem**: Admin actions don't work

**Solutions**:

**Check Permission Levels**:
```xml
<!-- Permissions.xml -->
<Permissions>
    <Admin steamid="YOUR_STEAM_ID" permission="SuperAdmin"/>
</Permissions>
```

**Verify SuperAdmin Rights**:
```
SuperAdmin has all permissions
If using custom roles, check each permission is granted
```

---

## Community Framework Issues

### Community Framework Issues

#### CF Not Loading

**Problem**: Community Framework mod not initializing

**Solutions**:

**Load Order Critical**:
```
CF MUST load before mods that depend on it

Correct order:
-mod=@CF;@TraderPlus;@OtherMods
```

**Update CF**:
```
1. Workshop: https://steamcommunity.com/sharedfiles/filedetails/?id=1559212036
2. Always use latest version
3. Check for updates regularly
```

#### Script Errors with CF

**Problem**: Errors mentioning "CF" classes

**Solutions**:
```
1. Verify CF is loaded FIRST
2. Check all dependent mods are updated
3. Look for mod conflicts
4. Check RPT logs for specific errors
```

---

## Troubleshooting Checklist

### Universal Troubleshooting Steps

For any third-party tool issue:

1. **Update Everything**
   - Tool itself
   - DayZ game
   - All mods
   - Operating system

2. **Check Logs**
   - Tool logs
   - DayZ RPT files
   - Server logs
   - Windows Event Viewer

3. **Verify Installation**
   - Correct version
   - All files present
   - No corruption

4. **Test Isolated**
   - Disable other mods
   - Fresh install
   - Vanilla game

5. **Check Documentation**
   - Official docs
   - GitHub README
   - Workshop description
   - Community guides

6. **Ask Community**
   - Tool Discord server
   - DayZ modding forums
   - Reddit communities
   - Steam discussions

---

## Getting Help

### Tool-Specific Support

#### CFTools Support
- Discord: https://discord.gg/K7ZpDA8
- Documentation: https://docs.cftools.cloud/
- Status Page: https://status.cftools.cloud/

#### DayZ Editor Support
- Discord: Check Workshop page for link
- GitHub: Report bugs and feature requests

#### Universal API Support
- Workshop: Comments and discussions
- Discord: DayZ Modding communities

#### VPP Admin Tools Support
- Discord: Link on Workshop page
- GitHub: Issues and documentation

### General Resources
- **DayZ Modding Discord Servers**
- **Reddit r/dayzservers**
- **Bohemia Forums**
- **YouTube Tutorials**

---

## Prevention Tips

1. **Keep Tools Updated** - Enable auto-updates where possible
2. **Read Changelogs** - Know what changed before updating
3. **Test Updates** - Try on test server first
4. **Document Setup** - Note configurations that work
5. **Backup Configs** - Before making changes
6. **Monitor Logs** - Catch issues early
7. **Join Communities** - Stay informed of known issues

---

**Pro Tip**: Most third-party tools have Discord servers where developers and experienced users can help with specific issues!

