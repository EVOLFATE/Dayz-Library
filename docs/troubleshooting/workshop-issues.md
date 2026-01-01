# Steam Workshop Upload & Download Issues

## Complete Guide to DayZ Workshop Problems

The Steam Workshop is essential for mod distribution. This guide covers all issues related to uploading, downloading, and managing Workshop content.

---

## Upload Issues

### "Upload Failed" Error

**Problem**: Can't upload mod to Workshop

**Common Causes**:

**Cause 1: File Size Too Large**
```
Steam Workshop Limits:
- Max file size: 100MB per file
- Max total size: Varies by game (usually 1-2GB)

Solution:
- Compress textures
- Use .paa format (smaller than .tga)
- Binarize configs
- Remove unnecessary files
- Split into multiple mods if needed
```

**Cause 2: Invalid Content**
```
Workshop rejects:
- Copyrighted content
- Offensive material
- Broken/corrupted files

Solution:
- Use original content
- Follow Steam guidelines
- Test mod thoroughly first
```

**Cause 3: Network Issues**
```
Upload interrupted or slow

Solution:
- Stable internet connection
- Wired > Wi-Fi
- Close bandwidth-heavy apps
- Try different time (less congestion)
- Restart Steam
```

**Cause 4: Missing Metadata**
```
Workshop requires:
- Title
- Description
- Preview image (JPG, 256x256 min)
- Tags
- Visibility setting

Solution: Fill all required fields
```

### Workshop Tool Won't Launch

**Problem**: Steam Workshop upload tool doesn't start

**Solutions**:

**Verify DayZ Tools**:
```
1. Steam Library → Tools
2. Find "DayZ Tools"
3. Right-click → Properties
4. Local Files → Verify Integrity
```

**Check Prerequisites**:
```
Required:
- .NET Framework 4.7.2+
- Visual C++ Redistributables
- DayZ must be installed
```

**Run as Administrator**:
```
Right-click DayZ Tools → Run as Administrator
```

### "Steam API Failed to Initialize"

**Error Message**:
```
Failed to initialize Steam API
```

**Solutions**:

**Method 1: Restart Steam**
```
1. Exit Steam completely
2. End Steam processes in Task Manager
3. Restart Steam
4. Try again
```

**Method 2: Verify steam_appid.txt**
```
Create file in Workshop tool folder:
steam_appid.txt

Content:
221100
```

**Method 3: Run Steam First**
```
1. Launch Steam
2. Login completely
3. Then launch Workshop tool
```

### Upload Stuck at 0%

**Problem**: Upload starts but never progresses

**Solutions**:

**Check Upload Speed**:
```
Test: https://www.speedtest.net/

Minimum required: 5 Mbps upload
Recommended: 25+ Mbps

If slow:
- Close other applications
- Contact ISP
- Try different time
```

**Verify File Integrity**:
```
Ensure all files in mod are:
- Not corrupted
- Proper format
- No special characters
- Complete downloads
```

**Clear Workshop Cache**:
```
Delete: 
Steam\steamapps\workshop\downloads

Restart Steam
Try upload again
```

---

## Download Issues

### Mods Not Downloading

**Problem**: Subscribed mods don't download

**Solutions**:

**Method 1: Restart Steam**
```
Sometimes Steam pauses downloads
1. Restart Steam
2. Check Downloads tab
3. Resume if paused
```

**Method 2: Clear Download Cache**
```
Steam → Settings → Downloads
→ "Clear Download Cache"
→ Restart Steam
→ Login again
```

**Method 3: Change Download Region**
```
Steam → Settings → Downloads
→ Download Region
→ Select closest or alternative
→ Restart Steam
```

**Method 4: Verify Disk Space**
```
Check free space:
Windows: File Explorer → This PC
Linux: df -h

Mods can be 1-10GB each
Ensure adequate space
```

### Download Stuck

**Problem**: Download never completes

**Symptoms**:
- Stuck at 0%
- Stuck at 99%/100%
- "Update queued"

**Solutions**:

**Force Re-Download**:
```
1. Unsubscribe from mod
2. Delete from:
   Steam\steamapps\workshop\content\221100\[MOD_ID]
3. Clear download cache
4. Resubscribe
5. Let download completely
```

**Check for Corruption**:
```
If mod shows downloaded but broken:
1. Unsubscribe
2. Delete mod folder
3. Delete:
   Steam\steamapps\workshop\downloads\[MOD_ID]
4. Verify game files
5. Resubscribe
```

**Verify Steam Status**:
```
Check: https://steamstat.us/

If Steam servers down:
- Wait
- Check status page
- Try later
```

### "Content File Locked"

**Error Message**:
```
Content file locked
```

**Solutions**:

**Close DayZ**:
```
Mod files locked while game running
1. Exit DayZ completely
2. Check Task Manager (no DayZ processes)
3. Try download again
```

**Check File Permissions**:
```
Workshop folder might be read-only
1. Right-click workshop folder
2. Properties → Uncheck "Read-only"
3. Apply to subfolders
```

**Antivirus Blocking**:
```
Some AV locks Workshop files
1. Add Workshop folder to exclusions
2. Temporarily disable AV
3. Try download
```

---

## Mod Update Issues

### Mod Auto-Updated and Broke

**Problem**: Workshop auto-updated mod, broke server

**Prevent Future Issues**:

**Pin Mod Version** (Not Official Support):
```
Use third-party tools:
- Steam Workshop Downloader
- Download specific version
- Manually manage updates
```

**Test Server Setup**:
```
1. Have test server
2. Let mods auto-update there
3. Test thoroughly
4. Manually update production if stable
```

**Monitor Mod Changes**:
```
- Subscribe to mod discussions
- Join mod Discord
- Follow mod author
- Read changelogs
```

### "Mod Out of Date"

**Problem**: Server requires newer/older version

**Solutions**:

**Update Mod**:
```
1. Steam Library → DayZ
2. Manage → Workshop
3. Find mod
4. Unsubscribe + Resubscribe
5. Or wait for auto-update
```

**Check Server Requirements**:
```
Server description usually specifies:
- Required mods
- Specific versions
- Workshop IDs

Match exactly!
```

**Use Mod Collection**:
```
Many servers provide:
- Steam Collection link
- Subscribe to collection
- Auto-downloads all with versions
```

---

## Upload Process (Step-by-Step)

### Preparing Your Mod

**Required Structure**:
```
@YourMod/
├── mod.cpp          # Mod metadata
├── Addons/
│   └── yourmod.pbo  # Your content
├── Keys/
│   └── yourmod.bikey # Signature
└── meta.cpp         # Optional metadata
```

**Create mod.cpp**:
```cpp
name = "Your Mod Name";
author = "Your Name";
class cfgMods
{
    class YourMod
    {
        dir = "YourMod";
        name = "Your Mod Name";
        credits = "Your Name";
        author = "Your Name";
        version = "1.0";
        extra = 0;
        type = "mod";
        dependencies[] = {"Game", "World", "Mission"};
        
        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"YourMod/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"YourMod/scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"YourMod/scripts/5_Mission"};
            };
        };
    };
};
```

### Workshop Upload Tool

**Launch Tool**:
```
Steam Library → Tools → DayZ Tools
→ Workshop Publisher
```

**Upload Steps**:
```
1. "Create New Item"
2. Select mod folder (@YourMod)
3. Fill metadata:
   - Title
   - Description (use BBCode)
   - Preview image (256x256+)
   - Tags
   - Visibility (Public/Friends/Private)
4. Click "Upload"
5. Wait for completion
6. Test download
```

**Update Existing Mod**:
```
1. Select existing item
2. Make changes to mod
3. Update description/image if needed
4. Click "Upload Update"
5. Change notes (optional)
6. Submit
```

---

## Workshop Visibility & Permissions

### Mod Not Appearing in Search

**Problem**: Uploaded mod isn't findable

**Check Settings**:

**Visibility**:
```
- Private: Only you see it
- Friends Only: You and friends
- Public: Everyone (required for servers)

Change in Workshop settings
```

**Tags**:
```
Add relevant tags:
- Mod type (Weapons, Vehicles, etc.)
- Gameplay type (Survival, PvP, etc.)
- Quality tags

More tags = better discoverability
```

**Content Status**:
```
Check if:
- Under review by Steam
- Flagged for review
- Banned (against ToS)

Check Workshop item page for status
```

### Can't Edit Uploaded Mod

**Problem**: No edit option on Workshop item

**Common Causes**:

**Cause 1: Wrong Account**
```
Logged into different Steam account

Solution: Login to uploading account
```

**Cause 2: Permissions Changed**
```
If uploaded through group/organization

Solution: Check group permissions
```

**Cause 3: Banned Content**
```
If violated Workshop rules

Solution: Contact Steam Support
```

---

## Downloading for Server

### Download Mods to Server

**Method 1: SteamCMD (Recommended)**
```batch
REM download_mod.bat
steamcmd +login anonymous +workshop_download_item 221100 [MOD_ID] +quit

Example:
steamcmd +login anonymous +workshop_download_item 221100 1559212036 +quit

Downloaded to:
steamcmd\steamapps\workshop\content\221100\[MOD_ID]

Rename and move to server
```

**Method 2: Download on Client, Upload**
```
1. Subscribe and download on local machine
2. Find in:
   Steam\steamapps\workshop\content\221100\[MOD_ID]
3. Rename folder to @ModName
4. Upload to server via FTP
5. Copy keys to server keys/ folder
```

**Method 3: Hosting Provider Tools**
```
Many hosts offer:
- Workshop ID input
- Auto-download
- Auto-key copying
- One-click install

Use if available (easiest!)
```

### Find Workshop ID

**From Workshop Page**:
```
URL format:
https://steamcommunity.com/sharedfiles/filedetails/?id=1234567890

ID = numbers after "?id="

Example:
https://steamcommunity.com/sharedfiles/filedetails/?id=1559212036
ID: 1559212036
```

**From Local Files**:
```
Folder name in:
Steam\steamapps\workshop\content\221100\[THIS_NUMBER]

That number is the Workshop ID
```

---

## Mod Collections

### Create a Collection

**Purpose**: Bundle multiple mods for easy subscription

**Steps**:
```
1. Steam Community → Workshop
2. Browse → DayZ
3. Collections tab
4. "Create Collection"
5. Add mods
6. Set visibility
7. Save
```

**Server Use**:
```
Provide collection URL to players:
"Subscribe to this collection for our server"

One click subscribes to all mods!
```

### Collection Not Working

**Problem**: Subscribed to collection but mods not downloading

**Solutions**:

**Subscribe to Individual Mods**:
```
Sometimes collections don't trigger download

Workaround:
1. Open collection page
2. Manually subscribe to each mod
3. Or click "Subscribe to all"
```

**Check Collection Status**:
```
Collection might be:
- Private (can't access)
- Deleted
- Mods removed

Try accessing mods directly
```

---

## Common Error Messages

### "Failed to download workshop item"

**Solutions**:
1. Clear download cache
2. Verify game files
3. Check disk space
4. Restart Steam
5. Try different download region

### "Workshop item needs update"

**Solutions**:
1. Unsubscribe + resubscribe
2. Clear workshop cache
3. Force update via Steam
4. Delete and redownload

### "Could not find workshop content"

**Solutions**:
1. Mod might be deleted
2. Check Workshop page status
3. Find alternative mod
4. Contact mod author

---

## Best Practices

### For Mod Authors

**Before Upload**:
```
✓ Test thoroughly
✓ Check file sizes
✓ Optimize assets
✓ Create good description
✓ Make preview image
✓ Add proper tags
✓ Include changelog
✓ Test download after upload
```

**After Upload**:
```
✓ Monitor comments
✓ Fix reported bugs
✓ Update regularly
✓ Respond to users
✓ Maintain compatibility
✓ Document changes
```

### For Players

**Mod Management**:
```
✓ Only subscribe to mods you use
✓ Unsubscribe from unused mods
✓ Check for updates regularly
✓ Read mod descriptions
✓ Follow server requirements
✓ Report issues to mod author
```

### For Server Admins

**Workshop Management**:
```
✓ Document required mods
✓ Provide Workshop IDs
✓ Create collection for players
✓ Test mod updates before deploying
✓ Keep backup of working versions
✓ Monitor mod health/updates
```

---

## Alternative Distribution

### If Workshop Fails

**GitHub Releases**:
```
1. Create GitHub repository
2. Create release with mod files
3. Users download .zip
4. Manual installation

Pros: Version control, no Steam dependency
Cons: Manual updates, more steps
```

**Direct Download**:
```
Host files on:
- Own website
- Google Drive
- Dropbox
- File hosting service

Provide direct link
```

**Modpacks**:
```
Bundle multiple mods:
- Create launcher
- Auto-updater
- Simplified installation

Examples: Technic Launcher style
```

---

## Tools & Resources

### Useful Tools

**SteamCMD**:
```
Download: https://developer.valvesoftware.com/wiki/SteamCMD
Purpose: Command-line Workshop access
```

**Steam Workshop Downloader**:
```
Website: https://steamworkshopdownloader.io/
Purpose: Download without Steam client
```

**Workshop Monitor Tools**:
```
Track mod updates:
- IFTTT with Steam RSS
- Custom scripts
- Discord webhooks
```

---

**Pro Tip**: Always test your mod download after uploading to Workshop. Subscribe on a different PC to verify it works!

