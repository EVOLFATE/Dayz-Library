# Mod Installation & Loading Issues

## Complete Guide to DayZ Mod Problems

Installing and managing mods is one of the most common sources of issues. This guide covers everything from Workshop downloads to load order conflicts.

---

## Workshop Download Issues

### Mods Not Downloading

**Problem**: Subscribed mods don't download

**Solutions**:

**Method 1: Clear Download Cache**
```
1. Steam → Settings → Downloads
2. "Clear Download Cache"
3. Restart Steam
4. Re-subscribe to mods
```

**Method 2: Verify Download Folder**
```
Check folder exists:
C:\Program Files (x86)\Steam\steamapps\workshop\content\221100

If missing: Create manually or reinstall Steam
```

**Method 3: Check Disk Space**
```
Mods can be large (1-10GB each)
Ensure adequate free space on Steam drive
```

**Method 4: Change Download Region**
```
1. Steam → Settings → Downloads
2. Change "Download Region"
3. Pick closest or less congested region
4. Restart Steam
```

### Download Stuck at 100%

**Problem**: Mod shows 100% but not installed

**Solutions**:

**Force Update**:
```
1. Unsubscribe from mod
2. Delete from workshop folder:
   Steam\steamapps\workshop\content\221100\[MOD_ID]
3. Clear download cache
4. Resubscribe
5. Wait for complete download
```

**Check for Corruption**:
```
Workshop folder might be corrupted
Delete entire 221100 folder (AFTER backing up!)
Steam will re-download all mods
```

### Mod Updates Breaking Server

**Problem**: Auto-update breaks working setup

**Solutions**:

**Disable Auto-Updates** (risky):
```
Not officially supported by Steam
Use third-party tools like:
- Steam Workshop Downloader
- Manually download specific versions
```

**Test Before Deploying**:
```
1. Have test server
2. Update mods on test server
3. Verify everything works
4. Then update production
```

**Version Control**:
```
Keep backup of working mod versions:
1. Copy entire @ModFolder
2. Store in archives with date
3. Can restore if update breaks
```

---

## Client-Side Mod Issues

### "Mod Mismatch" Error

**Problem**: Can't join server due to mod differences

**Causes & Solutions**:

**Cause 1: Different Mod Version**
```
Server: @Mod version 1.5
Client: @Mod version 1.6

Solution:
- Downgrade/upgrade to match server
- Server admin specifies exact versions
- Use mod collections/packs
```

**Cause 2: Missing Mod**
```
Server requires mod player doesn't have

Solution:
- Subscribe to all server mods
- Check server description for mod list
- Use DZSA Launcher (auto-downloads)
```

**Cause 3: Extra Mods**
```
Player has mods server doesn't

Solution:
- Launch DayZ with ONLY server mods
- Disable unnecessary mods
- Use mod profiles
```

### Mods Not Loading on Client

**Problem**: Subscribed mods don't appear in-game

**Check Mod Status**:
```
DayZ Launcher → Mods tab
Should show:
- Green checkmark = Active
- Red X = Not loaded
- Yellow warning = Issue
```

**Solutions**:

**Method 1: Verify Mod Files**
```
1. Right-click mod in launcher
2. "Verify integrity"
3. Wait for verification
4. Relaunch game
```

**Method 2: Manual Load**
```
Launch DayZ with parameter:
-mod=@ModName;@ModName2;@ModName3

Example:
"C:\...\DayZ.exe" -mod=@CF;@Expansion
```

**Method 3: Check Mod Folder**
```
Verify mod exists:
C:\Program Files (x86)\Steam\steamapps\common\DayZ\!Workshop\@ModName

If missing: Redownload from Workshop
```

### "Failed to Load Mod" Error

**Error Message**:
```
Error: Failed to load mod '@ModName'
```

**Common Causes**:

**Cause 1: Corrupted Download**
```
Solution:
1. Unsubscribe
2. Delete mod folder
3. Clear workshop cache
4. Resubscribe and download
```

**Cause 2: Missing Dependencies**
```
Mod requires other mods

Solution:
- Check mod description for requirements
- Install all dependencies first
- Use correct load order
```

**Cause 3: Outdated Mod**
```
Mod not updated for current DayZ version

Solution:
- Check mod workshop page for updates
- Look for alternative/updated mods
- Wait for mod author to update
```

---

## Server-Side Mod Issues

### Mods Not Loading on Server

**Problem**: Server doesn't load installed mods

**Check Startup Parameters**:
```batch
REM Windows
DayZServer_x64.exe -config=serverDZ.cfg -port=2302 -mod=@CF;@Expansion

# Linux  
./DayZServer -config=serverDZ.cfg -port=2302 -mod=@CF;@Expansion
```

**Common Mistakes**:

**Wrong Folder Names**:
```
Wrong: -mod=CF;Expansion
Correct: -mod=@CF;@Expansion

Folder MUST start with @
```

**Incorrect Separators**:
```
Windows: -mod=@CF;@Expansion
Linux: -mod=@CF;@Expansion

Both use semicolon (;)
```

**Spaces in Names**:
```
Wrong: -mod=@My Mod;@Other Mod
Correct: -mod=@MyMod;@OtherMod

Avoid spaces in folder names!
```

**Path Issues**:
```
Mods should be in server root:
ServerRoot/
├── @CF/
├── @Expansion/
└── DayZServer_x64.exe

Not in subdirectories!
```

### Mod Keys Missing

**Problem**: BattlEye kicks players (missing key)

**Symptoms**:
```
"You were kicked from the game"
BattlEye log: "Client key validation failed"
```

**Solutions**:

**Method 1: Auto-Copy Keys**
```
Many server tools auto-copy from @Mod/Keys/
to ServerRoot/keys/

Verify this happened!
```

**Method 2: Manual Copy**:
```
Copy all .bikey files:

From: @ModName/Keys/*.bikey
To: keys/*.bikey

Example:
@CF/Keys/CF.bikey → keys/CF.bikey
```

**Method 3: Script to Auto-Copy**:
```batch
@echo off
REM copy_keys.bat
for /d %%i in (@*) do (
    if exist "%%i\Keys\*.bikey" (
        copy "%%i\Keys\*.bikey" "keys\"
    )
)
echo Keys copied!
pause
```

**Linux Script**:
```bash
#!/bin/bash
# copy_keys.sh
for mod in @*/; do
    if [ -d "$mod/Keys" ]; then
        cp -f "$mod/Keys/"*.bikey keys/
    fi
done
echo "Keys copied!"
```

### Wrong Mod Load Order

**Problem**: Mods crash due to incorrect loading sequence

**Understanding Load Order**:

**Category 1: Framework Mods (FIRST)**
```
@CF (Community Framework)
@DayZ-Expansion-Core
@Dabs Framework

These MUST load before mods that use them!
```

**Category 2: Major Mods**
```
@DayZ-Expansion (full mod)
@TraderPlus
@BreachingCharge
```

**Category 3: Minor/Utility Mods**
```
@VPPAdminTools
@AdvancedBanking
@CarCover
```

**Category 4: Map Mods (LAST)**
```
@DeerIsle
@Namalsk
@Esseker

Map mods should load last!
```

**Example Correct Order**:
```batch
-mod=@CF;@DayZ-Expansion-Core;@DayZ-Expansion;@TraderPlus;@VPPAdminTools;@DeerIsle
```

**How to Find Load Order**:
```
1. Read mod Workshop description
2. Check mod author's instructions
3. Ask in mod Discord
4. Test different orders if unclear
```

---

## Mod Conflicts

### Identifying Conflicting Mods

**Problem**: Multiple mods trying to modify same thing

**Common Conflict Patterns**:

**UI Conflicts**:
```
Multiple HUD mods active
Multiple inventory mods
Custom UI overlays

Solution: Use only ONE of each type
```

**Trader Conflicts**:
```
Expansion Trader + TraderPlus = Conflict!

Solution: Choose ONE trader system
```

**Admin Tool Conflicts**:
```
VPP Admin Tools + COT + Omega = Issues!

Solution: Use ONE admin tool
```

**Testing for Conflicts**:
```
Binary search method:
1. Start with ALL mods
2. Disable half
3. If problem gone: conflict in disabled half
4. If problem persists: conflict in active half
5. Repeat until found
```

### Mod Compatibility Matrix

**Known Compatible**:
```
✅ CF + TraderPlus
✅ CF + VPP Admin Tools
✅ Expansion + Trader (Expansion's own)
✅ Most weapon mods + Expansion
✅ Map mods + Most other mods
```

**Known Incompatible**:
```
❌ Expansion Trader + TraderPlus
❌ VPP + COT simultaneously
❌ Some map mods + certain spawn mods
❌ Multiple killfeed mods
❌ Multiple base raiding mods
```

---

## Server Installation Methods

### Method 1: Steam Workshop (Easiest)

**For Windows Server**:
```
1. Subscribe to mods on Workshop
2. Let Steam download to client
3. Copy from:
   C:\...\Steam\steamapps\workshop\content\221100\[MOD_ID]
4. Rename to @ModName
5. Upload to server
6. Copy keys
7. Add to startup
```

### Method 2: SteamCMD (Recommended)

**Install SteamCMD**:
```batch
REM Download from:
https://steamcdn-a.akamaihd.net/client/installer/steamcmd.zip

Extract to: C:\steamcmd\
```

**Download Mod via SteamCMD**:
```batch
steamcmd +login anonymous +workshop_download_item 221100 [MOD_ID] +quit

Example:
steamcmd +login anonymous +workshop_download_item 221100 1559212036 +quit
```

**Organize Downloaded Mod**:
```
Downloaded to:
steamcmd\steamapps\workshop\content\221100\[MOD_ID]

Move/rename to server:
ServerRoot\@ModName\
```

**Automation Script**:
```batch
@echo off
REM download_mods.bat

set STEAMCMD=C:\steamcmd\steamcmd.exe
set MOD1=1559212036
set MOD2=2116157322

%STEAMCMD% +login anonymous +workshop_download_item 221100 %MOD1% +quit
%STEAMCMD% +login anonymous +workshop_download_item 221100 %MOD2% +quit

echo Mods downloaded!
pause
```

### Method 3: Third-Party Tools

**DZSA Launcher** (Client):
```
Automatically downloads and manages mods
Best for players
```

**Server Tools**:
```
- CFTools Omega (server management)
- Nitrado Auto-Install
- G-Portal Mod Manager
```

---

## Hosting Provider Specific

### Nitrado Mod Installation

**Via Web Interface**:
```
1. Login to Nitrado panel
2. Go to "Mods" section
3. Search Workshop
4. Click install
5. Restart server
6. Keys auto-copied
```

**Manual Installation**:
```
1. FTP to server
2. Upload @Mod folder
3. Copy keys manually
4. Edit startup via web panel
5. Restart
```

### G-Portal Mod Installation

**Steps**:
```
1. Server panel → Mods
2. Browse Workshop
3. Add to server
4. Save and restart
5. Verify in game
```

### Self-Hosted Installation

**Full Process**:
```
1. Download mod (SteamCMD or Workshop)
2. Extract to @ModName folder
3. Upload to server (FTP/RDP)
4. Place in server root
5. Copy .bikey files to keys/
6. Edit startup script/batch file
7. Restart server
8. Test connection
```

---

## Troubleshooting Tools

### DayZ Launcher Mod Manager

**Features**:
```
- See all subscribed mods
- Verify integrity
- Enable/disable mods
- Create mod presets
- Launch with specific mods
```

**Using Presets**:
```
1. Launcher → Mods
2. "Create Preset"
3. Name it (e.g., "Server1")
4. Select mods for that server
5. Save
6. Quick-join with preset
```

### DZSA Launcher

**Benefits**:
```
- Auto-downloads server mods
- Manages mod versions
- One-click join
- Updates automatically
```

**Setup**:
```
1. Download from: https://dayzsalauncher.com/
2. Install
3. Find server in list
4. Click Play
5. Auto-downloads all mods
```

### Steam Workshop Downloader

**For Manual Downloads**:
```
Website: https://steamworkshopdownloader.io/

Use Case:
- Server without Steam
- Specific mod versions
- Offline installation
```

---

## Common Error Messages

### "Failed to load addon"

**Error**: `Failed to load addon '@ModName'`

**Solutions**:
1. Verify folder name starts with @
2. Check folder contains addon/ or addons/
3. Ensure .pbo files exist
4. Verify not corrupted (redownload)

### "Addon requires newer version"

**Error**: `Addon requires game version X.XX`

**Solutions**:
1. Update DayZ server
2. Downgrade mod if possible
3. Find compatible mod version
4. Wait for mod update

### "Duplicate addon detected"

**Error**: `Duplicate addon 'AddonName'`

**Solutions**:
1. Check for duplicate mods
2. Remove old versions
3. Verify mod list for duplicates
4. Check if base game has same content

---

## Best Practices

### For Server Admins

**Documentation**:
```
Keep a mod list with:
- Mod name
- Workshop ID
- Version
- Load order
- Required dependencies
- Known issues
```

**Testing**:
```
1. Test mods on local server first
2. Test one mod at a time
3. Document working configurations
4. Keep backups of working setups
```

**Updates**:
```
1. Read mod changelogs
2. Test updates on test server
3. Announce update to players
4. Have rollback plan ready
```

### For Players

**Mod Management**:
```
1. Only subscribe to mods you use
2. Unsubscribe from unused mods
3. Regularly verify mod integrity
4. Keep mods updated (or frozen per server)
```

**Multiple Servers**:
```
Use mod presets/profiles:
- Preset for Server A
- Preset for Server B
- Preset for Single Player
```

---

## Performance Impact

### Mod Performance

**Resource Usage by Category**:
```
Light (<100MB RAM):
- UI mods
- Simple item mods
- Small map additions

Medium (100-500MB RAM):
- Weapon packs
- Vehicle packs
- Small frameworks

Heavy (500MB+ RAM):
- Large maps
- Expansion mod
- Comprehensive overhauls
```

**Optimization Tips**:
```
1. Don't use more mods than needed
2. Lightweight alternatives exist
3. Monitor server RAM usage
4. Consider mod impact on load times
```

---

## Getting Help

### Information to Provide

When asking for mod help:
```
1. Mod name and Workshop ID
2. DayZ version
3. Other installed mods
4. Error messages
5. Logs (script.log, RPT)
6. Startup parameters
7. Load order
```

### Where to Get Help

- **Mod Workshop Page**: Comments/discussions
- **Mod Discord**: Most popular mods have one
- **DayZ Forums**: Server admin section
- **Reddit r/dayzservers**: Community support
- **Hosting Provider Support**: If using managed hosting

---

**Pro Tip**: Keep a "known working" backup of your entire mod folder. When things break, you can quickly restore!

