# Quick Reference: Common Errors & Solutions

## Fast Lookup Guide for DayZ Issues

This is your emergency reference. Find your error, get the solution fast.

---

## Error Messages A-Z

### A

**"Access Violation" / "0xC0000005"**
- **Cause**: Script accessing null pointer
- **Fix**: Check for null before using objects
- **See**: [Scripting Errors](scripting-errors.md#null-reference-error)

**"Addon requires newer version"**
- **Cause**: Mod needs newer DayZ version
- **Fix**: Update DayZ or find compatible mod version
- **See**: [Mod Installation](mod-installation-issues.md#addon-requires-newer-version)

**"Already defined" / "Member already defined"**
- **Cause**: Duplicate class or variable
- **Fix**: Remove duplicate or use different name
- **See**: [Scripting Errors](scripting-errors.md#member-already-defined)

### B

**"BattlEye: Client not responding"**
- **Cause**: Network/software conflict
- **Fix**: Reinstall BattlEye, check network, disable overlays
- **See**: [BattlEye Issues](battleye-issues.md#getting-kicked-battleye-client-not-responding)

**"BattlEye: Global Ban"**
- **Cause**: Cheating detected (or false positive)
- **Fix**: Appeal to BattlEye with evidence
- **See**: [BattlEye Issues](battleye-issues.md#battleye-global-ban)

**"Build Failed" (no details)**
- **Cause**: Various (path length, special chars, permissions)
- **Fix**: Enable verbose logging, check common issues
- **See**: [Addon Builder](addon-builder-issues.md#build-failed-with-no-error-message)

### C

**"Cannot Cast to Type"**
- **Cause**: Invalid type conversion
- **Fix**: Use Type.Cast() and check result
- **See**: [Scripting Errors](scripting-errors.md#cannot-cast-to-type)

**"Cannot connect to server"**
- **Cause**: Mod mismatch, outdated client
- **Fix**: Match server mods exactly, update game
- **See**: [Mod Installation](mod-installation-issues.md#mod-mismatch-error)

**"Cannot find class 'ClassName'"**
- **Cause**: Class not defined or loaded
- **Fix**: Check config.cpp, verify scripts loaded
- **See**: [Scripting Errors](scripting-errors.md#cannot-find-class)

**"Cannot load texture" / "Cannot load model"**
- **Cause**: Missing file or wrong path
- **Fix**: Verify file exists, check path syntax
- **See**: [Workbench Issues](workbench-issues.md#common-error-messages--solutions)

**"Content file locked"**
- **Cause**: File in use by another program
- **Fix**: Close DayZ, check Task Manager
- **See**: [Workshop Issues](workshop-issues.md#content-file-locked)

### D

**"Division by zero"**
- **Cause**: Dividing by zero in script
- **Fix**: Check divisor != 0 before dividing
- **See**: [Scripting Errors](scripting-errors.md#division-by-zero)

**"Duplicate addon detected"**
- **Cause**: Same addon loaded twice
- **Fix**: Remove duplicate mod folders
- **See**: [Mod Installation](mod-installation-issues.md#common-error-messages)

### E

**"Exception: Stack overflow"**
- **Cause**: Infinite recursion
- **Fix**: Add recursion depth limit, check base case
- **See**: [Server Crashes](server-crashes.md#stack-overflow-crash)

### F

**"Failed to compile script module"**
- **Cause**: Syntax error in scripts
- **Fix**: Check error line, fix syntax
- **See**: [Scripting Errors](scripting-errors.md#common-error-messages)

**"Failed to load addon"**
- **Cause**: Corrupted mod files
- **Fix**: Redownload mod, verify integrity
- **See**: [Mod Installation](mod-installation-issues.md#failed-to-load-mod-error)

**"Failed to load DLL"**
- **Cause**: Missing system libraries
- **Fix**: Install Visual C++ Redistributables
- **See**: [Server Crashes](server-crashes.md#failed-to-load-dll)

### H

**"HEAP CORRUPTION DETECTED"**
- **Cause**: Memory corruption, usually script issue
- **Fix**: Check for memory leaks, double deletes
- **See**: [Server Crashes](server-crashes.md#heap-corruption-crash)

### I

**"Index out of bounds"**
- **Cause**: Accessing array element that doesn't exist
- **Fix**: Check array.Count() before accessing
- **See**: [Scripting Errors](scripting-errors.md#index-out-of-bounds)

**"Invalid signature"**
- **Cause**: PBO signature doesn't match key
- **Fix**: Re-sign PBO with correct key
- **See**: [Addon Builder](addon-builder-issues.md#invalid-signature)

### M

**"Mem alloc" / "Out of memory"**
- **Cause**: Insufficient RAM
- **Fix**: Close apps, increase virtual memory, add RAM
- **See**: [Performance Issues](performance-issues.md#memory-errors)

**"Missing ;"**
- **Cause**: Forgot semicolon in code
- **Fix**: Add semicolon at end of statement
- **See**: [Scripting Errors](scripting-errors.md#missing-semicolon)

**"Mod mismatch"**
- **Cause**: Client/server mod versions differ
- **Fix**: Ensure exact same mods and versions
- **See**: [Mod Installation](mod-installation-issues.md#mod-mismatch-error)

**"Mod not signed"**
- **Cause**: PBO lacks .bisign file
- **Fix**: Sign PBO with DSSignFile
- **See**: [Addon Builder](addon-builder-issues.md#mod-not-signed)

### N

**"Null pointer access"**
- **Cause**: Using object that is null
- **Fix**: Check if (object) before using
- **See**: [Scripting Errors](scripting-errors.md#null-reference-error)

### P

**"P: drive not mounted"**
- **Cause**: Virtual drive not created
- **Fix**: Mount via Workbench or subst command
- **See**: [Workbench Issues](workbench-issues.md#p-drive-not-mounting)

### R

**"RPC function not registered"**
- **Cause**: RPC called without registration
- **Fix**: Register RPC ID and implement handler
- **See**: [Scripting Errors](scripting-errors.md#rpc-errors)

### S

**"Steam API failed to initialize"**
- **Cause**: Steam not running or connection issue
- **Fix**: Restart Steam, verify login
- **See**: [Workshop Issues](workshop-issues.md#steam-api-failed-to-initialize)

### T

**"Texture not found"**
- **Cause**: Missing .paa file or wrong path
- **Fix**: Convert texture to .paa, verify path
- **See**: [Addon Builder](addon-builder-issues.md#textures-not-in-pbo)

**"Type mismatch"**
- **Cause**: Assigning wrong type to variable
- **Fix**: Use correct type or convert
- **See**: [Scripting Errors](scripting-errors.md#type-mismatch)

### U

**"Unterminated string constant"**
- **Cause**: Missing closing quote on string
- **Fix**: Add closing quote
- **See**: [Scripting Errors](scripting-errors.md#incorrect-string-syntax)

### V

**"Variable not networked"**
- **Cause**: Trying to sync variable without setup
- **Fix**: Implement OnStoreSave/OnStoreLoad
- **See**: [Scripting Errors](scripting-errors.md#variable-not-networked)

### X

**"XML parsing failed"**
- **Cause**: Syntax error in XML file
- **Fix**: Validate XML, check for unclosed tags
- **See**: [Server Config Errors](server-config-errors.md#cannot-parse-typesxml)

---

## Quick Fixes by Category

### Server Won't Start
```
1. Check logs (serverDZ.cfg location)
2. Test without mods
3. Verify all mods loaded
4. Check port availability
5. Run as Administrator
```
**Full Guide**: [Server Crashes](server-crashes.md#server-wont-start)

### Client Can't Connect
```
1. Match server mods exactly
2. Update DayZ
3. Verify mod files
4. Check ping/connection
5. Restart Steam
```
**Full Guide**: [Mod Installation](mod-installation-issues.md#mod-mismatch-error)

### FPS Too Low
```
1. Lower graphics settings
2. Reduce view distance
3. Close background apps
4. Update drivers
5. Install on SSD
```
**Full Guide**: [Performance Issues](performance-issues.md#low-fps-frames-per-second)

### Build Fails
```
1. Check file paths (< 260 chars)
2. Run as Administrator
3. Verify P: drive mounted
4. Remove special characters
5. Check $PBOPREFIX$
```
**Full Guide**: [Addon Builder](addon-builder-issues.md#build-failures)

### Mods Not Loading
```
1. Check -mod= parameter syntax
2. Verify @ folder names
3. Copy .bikey to keys/
4. Check load order
5. Test mods individually
```
**Full Guide**: [Mod Installation](mod-installation-issues.md#mods-not-loading-on-server)

---

## Diagnostic Commands

### Check Logs

**Client Logs**:
```
Location: C:\Users\[User]\AppData\Local\DayZ\
Files: *.rpt, script.log

Look for: Error, Warning, Exception
```

**Server Logs**:
```
Location: ServerProfile\
Files: *.log, *.rpt

Look for: Error, Crash, Exception
```

### Test Commands

**Verify Game Files** (Steam):
```
Library → DayZ → Properties → Local Files
→ Verify integrity of game files
```

**Test Server (Vanilla)**:
```batch
REM No mods
DayZServer_x64.exe -config=serverDZ.cfg
```

**Test Mod (Client)**:
```
Launch parameters:
-mod=@TestMod -filePatching
```

### Check System

**RAM Usage**:
```batch
REM Windows
wmic process where name="DayZ.exe" get WorkingSetSize

# Linux
ps aux | grep DayZ
```

**Network Test**:
```
ping [server-ip]
tracert [server-ip]
```

**Disk Space**:
```batch
REM Windows
dir /s

# Linux
df -h
```

---

## Emergency Procedures

### Server Down Emergency
```
1. Check if actually down (multiple sources)
2. Check server logs
3. Try restart
4. If crashes persist: start vanilla
5. Add mods back one by one
6. Restore from backup if needed
```

### Game Won't Launch
```
1. Verify game files
2. Update drivers
3. Reinstall BattlEye
4. Check for Windows updates
5. Reinstall Visual C++ Redistributables
6. Last resort: Reinstall game
```

### Lost All Progress
```
1. Check ServerProfile\players\
2. Check backup files
3. Look for .old or .backup files
4. Check hosting provider backups
5. Contact host support
```

---

## Prevention Checklist

### Before Making Changes
- [ ] Backup current configuration
- [ ] Document what you're changing
- [ ] Test on test server first
- [ ] Have rollback plan
- [ ] Save working mod versions

### Regular Maintenance
- [ ] Update DayZ regularly
- [ ] Keep mods updated
- [ ] Clean old logs
- [ ] Check disk space
- [ ] Monitor performance
- [ ] Review crash reports
- [ ] Test backups work

### Development Best Practices
- [ ] Use version control (Git)
- [ ] Test incrementally
- [ ] Validate before deploying
- [ ] Document code
- [ ] Use descriptive names
- [ ] Check for null
- [ ] Clean up resources
- [ ] Handle errors gracefully

---

## When to Ask for Help

### You've Tried Everything If:
- ✓ Searched this guide
- ✓ Checked logs
- ✓ Tested vanilla
- ✓ Verified files
- ✓ Restarted everything
- ✓ Updated everything
- ✓ Still doesn't work

### Where to Ask:
1. **Mod Discord** - If mod-specific
2. **DayZ Forums** - General issues
3. **Reddit r/dayz** - Community help
4. **Server Discord** - Server issues
5. **Hosting Support** - If using host
6. **GitHub Issues** - For open-source mods

### What to Include:
```
- Exact error message
- DayZ version
- Mods list (with versions)
- What you were doing
- What you've tried
- Relevant log excerpts (not entire logs!)
- System specs (if client issue)
```

---

## Most Common Issues (90% of Problems)

### 1. Mod Load Order
**Fix**: CF first, frameworks before dependents, maps last

### 2. Missing Semicolon
**Fix**: Use IDE with syntax checking

### 3. Null Pointer
**Fix**: Always check if (object) before using

### 4. Mod Version Mismatch
**Fix**: Ensure exact same versions client/server

### 5. BattlEye Kick
**Fix**: Check filters, whitelist mod functions

### 6. P: Drive Not Mounted
**Fix**: Use Workbench or subst command

### 7. Out of Memory
**Fix**: Close apps, add RAM, optimize scripts

### 8. Port Already in Use
**Fix**: Close conflicting app or change port

### 9. Corrupted Download
**Fix**: Delete and redownload

### 10. File Path Too Long
**Fix**: Move project closer to drive root

---

## Quick Links

- [Main Troubleshooting Guide](README.md)
- [Workbench Issues](workbench-issues.md)
- [Scripting Errors](scripting-errors.md)
- [Server Crashes](server-crashes.md)
- [Mod Installation](mod-installation-issues.md)
- [BattlEye Issues](battleye-issues.md)
- [Performance](performance-issues.md)
- [Config Errors](server-config-errors.md)
- [Addon Builder](addon-builder-issues.md)
- [Workshop Issues](workshop-issues.md)
- [Third-Party Tools](third-party-tools.md)

---

**Remember**: Most issues have been solved by someone before. Search, read logs, and ask the community!

