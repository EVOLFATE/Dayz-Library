# BattlEye & Anti-Cheat Issues

## Complete Guide to BattlEye Problems in DayZ

BattlEye is the anti-cheat system used by DayZ. While essential for keeping servers clean, it can cause legitimate issues for both players and modders.

---

## Player Issues

### Getting Kicked: "BattlEye: Client Not Responding"

**Problem**: Constant kicks with BattlEye error messages

**Common Causes**:
- Network instability
- Software conflicts
- Corrupted BattlEye files
- Router/firewall issues
- Outdated game files

**Solutions**:

**Method 1: Reinstall BattlEye**
```
1. Close DayZ completely
2. Navigate to: C:\Program Files (x86)\Steam\steamapps\common\DayZ\BattlEye
3. Delete the entire BattlEye folder
4. Launch DayZ - BattlEye will auto-reinstall
5. Join server again
```

**Method 2: Verify Game Files**
```
1. Steam Library → Right-click DayZ
2. Properties → Local Files
3. Verify Integrity of Game Files
4. Wait for completion
5. Restart Steam and DayZ
```

**Method 3: Network Fixes**
```
1. Restart modem/router
2. Use wired connection (not Wi-Fi)
3. Update router firmware
4. Flush DNS:
   - Open CMD as Admin
   - ipconfig /flushdns
   - ipconfig /release
   - ipconfig /renew
```

**Method 4: Firewall Configuration**
```
Windows Firewall:
1. Control Panel → Windows Defender Firewall
2. Allow an app through firewall
3. Add DayZ.exe and DayZ_BE.exe
4. Enable both Private and Public

Third-party Firewall:
- Add exceptions for BattlEye service
- Allow inbound/outbound for DayZ ports
```

**Method 5: Disable Conflicting Software**
```
Temporarily disable:
- VPN services
- Bandwidth monitors (NetLimiter, cFosSpeed)
- Overlays (Discord, Steam, GeForce Experience)
- Screen capture software (OBS when not recording)
- RGB control software
- Macro software
```

### "BattlEye: Global Ban"

**Problem**: Permanently banned from all BattlEye-protected servers

**Understanding Bans**:
- **Global Ban (BattlEye)**: HWID ban, permanent, affects all BattlEye games
- **Developer Ban (Bohemia)**: Account ban for toxicity, duping, exploits
- **Server Ban**: Only affects specific server

**Common Causes of False Positives**:
```
- AutoHotkey scripts running
- Cheat Engine or memory editors (even for other games)
- Debugging tools (OllyDbg, x64dbg)
- Development IDEs with debugging features
- System optimization tools
- Certain driver-level software
```

**Appeal Process**:

**For BattlEye Global Bans**:
```
1. Gather evidence:
   - BattlEye logs from: C:\Users\[User]\AppData\Local\DayZ\
   - Screenshot of ban message
   - List of software running at time of ban
   - Malware scan results (Malwarebytes)

2. Contact BattlEye:
   - Website: https://www.battleye.com/support/
   - Be honest and professional
   - Provide all evidence
   - Explain situation clearly

3. Wait for response (can take weeks)
   - BattlEye rarely overturns bans
   - Need strong evidence of false positive
```

**For Developer Bans**:
```
Contact Bohemia Interactive:
- Support: https://support.bistudio.com/
- Explain the situation
- These are easier to appeal if unjust
```

**Prevention**:
```
- Don't run ANY cheat software (even for other games)
- Close all dev tools before playing
- Disable macro software
- Keep only essential software running
- Regular malware scans
- Don't share your PC with others who might cheat
```

### "You were kicked from the game"

**Problem**: Generic kick message without details

**Possible Causes**:
1. **Mod Mismatch**: Client mods don't match server
2. **Outdated Client**: DayZ needs updating
3. **Server Full**: Max players reached
4. **Reserved Slot**: VIP/admin slot needed
5. **BattlEye Filter**: Triggered anticheat filter

**Solutions**:

**Check Mod Versions**:
```
1. Note server's mod list (usually in description)
2. Unsubscribe from ALL current mods
3. Clear Workshop cache:
   Steam\steamapps\workshop\downloads
4. Subscribe to exact server mods
5. Verify all downloaded (check file sizes)
```

**Update Everything**:
```
1. Update DayZ (Steam)
2. Update all mods (Workshop)
3. Update graphics drivers
4. Update Windows
5. Update BattlEye (delete and reinstall)
```

---

## Server Administrator Issues

### BattlEye Filter Configuration

**Problem**: Need to configure filters for custom mods

**Filter Files Location**:
```
ServerProfile/battleye/
├── scripts.txt       # Script filters
├── publicvariable.txt # Network variable filters
├── createvehicle.txt # Vehicle/object spawn filters
├── setvariable.txt   # Variable assignment filters
├── attachto.txt      # Object attachment filters
└── addmagazine.txt   # Inventory addition filters
```

**Understanding Filter Syntax**:
```
1 "pattern"     // Log and kick
2 "pattern"     // Log only (debugging)
5 "pattern"     // Kick only
!"exception"    // Exception to allow

Example:
1 "deleteVehicle" !"_vehicle = deleteVehicle"
```

**Common Whitelist Needs**:

**For Expansion Mod**:
```
// scripts.txt
!"ExpansionMarket"
!"ExpansionParty"
!"ExpansionBook"
!"ExpansionVehicle"

// createvehicle.txt
!"ExpansionHeli"
!"ExpansionBoat"
!"ExpansionAirdrop"
```

**For Trader Mods**:
```
// publicvariable.txt
!"TraderPlus"
!"MarketItems"
!"SellItemToTrader"
!"BuyItemFromTrader"
```

**For Admin Tools**:
```
// setvariable.txt
!"AdminTool"
!"TPPlayer"
!"GodMode"
!"ESP"
```

### Players Kicked for Legitimate Actions

**Problem**: BattlEye kicks players doing normal gameplay

**Debugging Process**:

**Step 1: Check Logs**
```
ServerProfile/battleye/scripts.log
ServerProfile/battleye/publicvariable.log

Look for player name and what triggered kick
```

**Step 2: Identify Pattern**
```
Example log entry:
08:30:12 PlayerName (IP:PORT) GUID - #0 "myFunction"

#0 = Filter line 0 in scripts.txt
"myFunction" = What was detected
```

**Step 3: Create Exception**
```
Add to appropriate filter file:
!"myFunction"

Or make filter more specific:
1 "myFunction" !"_legitimate = myFunction"
```

**Step 4: Test**
```
1. Save filter file
2. BattlEye auto-reloads (no restart needed)
3. Test the action again
4. Check logs to verify no kick
```

### False Positive Script Kicks

**Problem**: Custom mod scripts triggering BattlEye

**Solution Pattern**:

**Example Issue**: Custom loot spawn script kicks players

**Before (kicks)**:
```
// scripts.txt
1 "createVehicle"
```

**After (whitelist your mod)**:
```
// scripts.txt
1 "createVehicle" !"MyMod_LootSpawn"
```

**Best Practices**:
```
1. Prefix all custom functions with mod name
   Example: MyMod_SpawnItem, MyMod_CleanupLoot

2. Document required filters in mod README

3. Provide example filter files with mod

4. Use specific patterns, not broad exceptions

5. Test thoroughly before release
```

### BattlEye Service Issues

**Problem**: BattlEye service not starting on server

**Solutions**:

**Windows Server**:
```batch
# Check service status
sc query BEService

# Start service manually
sc start BEService

# Set to auto-start
sc config BEService start= auto
```

**Linux Server**:
```bash
# Check BattlEye process
ps aux | grep BattlEye

# Check permissions
chmod +x ./BattlEye/BEServer_x64.so

# Check library dependencies
ldd ./BattlEye/BEServer_x64.so
```

**Installation Issues**:
```
1. Verify BattlEye files exist:
   - BEServer_x64.dll (Windows)
   - BEServer_x64.so (Linux)

2. Correct permissions:
   - Read & Execute for Windows
   - chmod 755 for Linux

3. Reinstall if missing:
   - Download from BattlEye official site
   - Place in server root directory
```

---

## Modder Issues

### Testing Mods with BattlEye

**Problem**: Need to test without BattlEye kicks

**Development Server Setup**:
```
// serverDZ.cfg
battlEye = 0;  // Disable BattlEye

Note: Only for testing! Never use in production
```

**Alternative: Localhost Testing**:
```
1. Host local server without BattlEye
2. Test all features thoroughly
3. Document what might trigger filters
4. Create filter exceptions
5. Test on server WITH BattlEye
```

### Providing Filter Configs with Mods

**Best Practice**: Include BattlEye filter files

**Example Mod Package**:
```
@MyMod/
├── Addons/
├── Keys/
└── BattlEye/          # Include this!
    ├── filters.txt     # Instructions
    ├── scripts.txt     # Required exceptions
    └── publicvariable.txt
```

**filters.txt Example**:
```
===========================================
MyMod BattlEye Filter Configuration
===========================================

Copy the contents of each file to your server's
corresponding BattlEye filter files:

ServerProfile/battleye/scripts.txt
ServerProfile/battleye/publicvariable.txt

DO NOT replace your existing filters!
ADD these lines to your existing files.

These exceptions are required for MyMod to work
without BattlEye kicks.
===========================================
```

---

## Advanced Configuration

### Custom Filter Development

**Creating Robust Filters**:

**Template**:
```
// General pattern (strict)
1 "functionName"

// Whitelist your mod
!"MyMod_functionName"

// Whitelist specific usage
!"_var = functionName(_param)"

// Multiple exceptions
!"exception1" !"exception2" !"exception3"
```

**Testing Process**:
```
1. Enable logging (change 1 to 2 temporarily)
2 "functionName"

2. Monitor logs for ALL occurrences
3. Identify legitimate vs malicious patterns
4. Create specific exceptions
5. Change back to kick mode (2 to 1)
6. Test thoroughly
```

### Regular Expression Filters

**Advanced Patterns**:
```
// Match specific patterns
1 "deleteVehicle.*player"

// Exclude specific patterns
!"myModCleanup.*deleteVehicle"

// Case insensitive
1 "(?i)spawn.*cheat"

// Multiple words
1 "(hack|cheat|exploit)"
```

**Example: Protect Against Item Spawning**:
```
// scripts.txt
1 "CreateInInventory" !"_item = CreateInInventory\(.*,.*\)"
```

---

## Troubleshooting Checklist

### Player Checklist
- [ ] Reinstalled BattlEye
- [ ] Verified game files
- [ ] Updated all mods
- [ ] Disabled overlay software
- [ ] Checked firewall settings
- [ ] Tested with wired connection
- [ ] No cheat software running
- [ ] Malware scan clean

### Server Admin Checklist
- [ ] BattlEye service running
- [ ] Filter files exist
- [ ] Filters updated for mods
- [ ] Logs checked for patterns
- [ ] Exceptions added for custom mods
- [ ] Tested player actions
- [ ] Documented required exceptions
- [ ] Backup of working filters

### Modder Checklist
- [ ] Tested without BattlEye
- [ ] Identified trigger functions
- [ ] Created filter exceptions
- [ ] Tested with BattlEye enabled
- [ ] Documented requirements
- [ ] Included filter files with mod
- [ ] Used prefixed function names
- [ ] Tested on multiple servers

---

## Prevention & Best Practices

### For Players
1. **Keep clean system** - No cheat software
2. **Update regularly** - Game, mods, drivers
3. **Minimal background apps** - Close unnecessary programs
4. **Stable connection** - Wired > Wi-Fi
5. **Legitimate software only** - No cracks, trainers

### For Server Admins
1. **Start with default filters** - Don't disable completely
2. **Log before kicking** - Use "2" to monitor
3. **Specific exceptions** - Not blanket allowlists
4. **Regular updates** - Check for new filter patterns
5. **Document changes** - Know what you modified
6. **Test thoroughly** - Before going live

### For Modders
1. **Prefix functions** - ModName_FunctionName
2. **Provide filters** - Include with mod download
3. **Document triggers** - Tell users what to whitelist
4. **Test with BattlEye** - Don't skip this step
5. **Monitor reports** - Users will report kicks
6. **Update filters** - As BattlEye updates

---

## Common Myths

### Myth 1: "VPN will help with HWID ban"
**FALSE**: Hardware bans persist regardless of IP/VPN

### Myth 2: "Reinstalling Windows removes HWID ban"
**PARTIALLY TRUE**: Need to change hardware components that BattlEye tracks

### Myth 3: "BattlEye only detects known cheats"
**FALSE**: Also uses heuristics and behavioral analysis

### Myth 4: "Disabling BattlEye is safe for private servers"
**FALSE**: Opens door to cheaters, only use for local testing

### Myth 5: "All BattlEye kicks are false positives"
**FALSE**: Vast majority are legitimate detections

---

## Getting Help

### Official Support
- **BattlEye**: https://www.battleye.com/support/
- **DayZ Feedback**: https://feedback.bistudio.com/
- **Bohemia Support**: https://support.bistudio.com/

### Community Resources
- **DayZ Forums**: https://forums.dayz.com/
- **Reddit r/dayz**: Report false positives
- **Server Discord**: Ask admins

### Log Files to Provide
```
For Players:
C:\Users\[User]\AppData\Local\DayZ\*.rpt

For Admins:
ServerProfile/battleye/*.log
ServerProfile/*.log
```

---

**Remember**: BattlEye is essential for fair gameplay. Work WITH it, not against it!

