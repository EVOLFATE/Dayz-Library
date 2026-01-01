# Server Crashes & Startup Issues

## Complete Guide to DayZ Server Problems

Server crashes and startup failures are among the most frustrating issues. This guide covers everything from basic startup problems to complex crash analysis.

---

## Server Won't Start

### Server Stops Immediately After Launch

**Problem**: Server window closes right away or shows error

**Common Causes & Solutions**:

**Cause 1: Missing Files**
```bash
# Check for required files
DayZServer.exe
steam_appid.txt
steamclient64.dll

Solution: Verify server files via SteamCMD
```

**Cause 2: Invalid Configuration**
```
Check serverDZ.cfg for syntax errors

Common issues:
- Missing commas
- Incorrect quotation marks
- Invalid values
```

**Cause 3: Port Already in Use**
```bash
# Windows: Check port usage
netstat -ano | findstr :2302

# Linux: Check port usage
netstat -tulpn | grep 2302

Solution:
- Close conflicting application
- Change server port
- Kill process using port
```

**Cause 4: Insufficient Permissions**
```
Windows:
- Run as Administrator
- Check folder permissions

Linux:
- chmod +x DayZServer
- Check file ownership
```

### "Failed to Load DLL"

**Error Message**:
```
Failed to load 'steamclient64.dll'
```

**Solutions**:

**Method 1: Copy from Steam Client**
```
Copy from:
C:\Program Files (x86)\Steam\steamclient64.dll

To server folder:
[ServerRoot]\steamclient64.dll
```

**Method 2: Reinstall Prerequisites**
```
Install:
- Visual C++ 2013 Redistributable (x64)
- Visual C++ 2015-2022 Redistributable (x64)
- DirectX End-User Runtime
```

**Method 3: Verify Server Installation**
```bash
# Using SteamCMD
steamcmd +login anonymous +app_update 223350 validate +quit
```

### "Cannot Find Server Config"

**Error Message**:
```
Error: Cannot find serverDZ.cfg
```

**Solutions**:

**Check Startup Parameters**:
```batch
REM Windows
DayZServer_x64.exe -config=serverDZ.cfg -port=2302

# Linux
./DayZServer -config=serverDZ.cfg -port=2302
```

**Verify File Location**:
```
Config should be in:
[ServerRoot]\serverDZ.cfg

OR use full path:
-config="C:\Path\To\serverDZ.cfg"
```

**Check File Encoding**:
```
Must be UTF-8 without BOM
Use Notepad++ to check/convert
```

---

## Server Crashes During Runtime

### Random Crashes (No Error)

**Problem**: Server crashes unpredictably

**Diagnostic Steps**:

**Step 1: Check Logs**
```
Locations:
ServerProfile\*.log
ServerProfile\*.rpt

Look for patterns before crashes
```

**Step 2: Monitor Resources**
```
Check:
- RAM usage (should be under 80%)
- CPU usage
- Disk I/O
- Network connections

Tools:
- Task Manager (Windows)
- htop (Linux)
- Resource Monitor
```

**Step 3: Test Without Mods**
```batch
# Start vanilla server
DayZServer_x64.exe -config=serverDZ.cfg -port=2302
# NO -mod= parameter

If stable: Mod conflict
If still crashes: Core issue
```

**Common Fixes**:

**Fix 1: Increase RAM**
```
Minimum: 4GB
Recommended: 8GB+
With mods: 12GB+
```

**Fix 2: Reduce Entity Count**
```xml
<!-- In types.xml -->
<type name="Zombie">
    <nominal>100</nominal>  <!-- Reduce this -->
    <min>50</min>
</type>
```

**Fix 3: Update Everything**
```
1. Update DayZ Server
2. Update all mods
3. Update OS
4. Update server hosting software
```

### Crash on Player Connect

**Problem**: Server crashes when players join

**Causes & Solutions**:

**Cause 1: Mod Mismatch**
```
Player has different mod version

Solution:
- Enforce exact mod versions
- Use mod pack/collection
- Check server mod list
```

**Cause 2: Corrupted Character**
```
Player's character file is corrupted

Solution:
# Delete character file
ServerProfile\players\[STEAMID].bin

Player will respawn fresh
```

**Cause 3: Memory Leak**
```
Server memory fills up over time

Solution:
- Restart server regularly (cron job)
- Fix memory leaks in scripts
- Increase available RAM
```

### Crash During Restart

**Problem**: Server crashes when trying to restart

**Solutions**:

**Graceful Shutdown Process**:
```batch
REM Windows batch script
@echo off
echo Sending shutdown signal...
# Use RCON or admin command to warn players
timeout /t 300
taskkill /IM DayZServer_x64.exe /F
timeout /t 10
start DayZServer_x64.exe -config=serverDZ.cfg -port=2302
```

**Linux Script**:
```bash
#!/bin/bash
echo "Server restarting in 5 minutes"
# Send RCON message
sleep 300
pkill -SIGTERM DayZServer
sleep 10
./DayZServer -config=serverDZ.cfg -port=2302 &
```

**Check for File Locks**:
```
Ensure all files are closed before restart:
- Database connections
- Log files
- PBO files
```

---

## Specific Crash Patterns

### "Access Violation" Crash

**Error Message**:
```
Exception code: 0xC0000005 (Access Violation)
```

**Meaning**: Program tried to access invalid memory

**Common Causes**:

**Cause 1: Bad Script**
```cpp
// Accessing null pointer
ItemBase item;
item.DoSomething();  // Crash!

Solution: Always check for null
if (item)
    item.DoSomething();
```

**Cause 2: Corrupted Mod**
```
Reinstall problematic mod:
1. Remove from server
2. Delete mod folder
3. Re-download
4. Verify file integrity
```

**Cause 3: Memory Corruption**
```
Solution:
- Restart server fresh
- Check RAM (run memtest)
- Update server files
```

### "Stack Overflow" Crash

**Error Message**:
```
Exception: Stack overflow
```

**Causes**:

**Infinite Loop in Script**:
```cpp
// Wrong
void BadFunction()
{
    BadFunction();  // Calls itself forever
}

// Correct
void GoodFunction(int depth)
{
    if (depth <= 0) return;
    GoodFunction(depth - 1);
}
```

**Too Deep Recursion**:
```cpp
// Limit recursion depth
const int MAX_DEPTH = 100;

void RecursiveFunc(int depth)
{
    if (depth > MAX_DEPTH)
    {
        Error("Maximum recursion depth exceeded");
        return;
    }
    // Function logic
}
```

### "Heap Corruption" Crash

**Error Message**:
```
HEAP CORRUPTION DETECTED
```

**Causes**:
- Memory leak in scripts
- Buffer overflow
- Double-free of memory
- Using deleted objects

**Solutions**:

**Fix Memory Leaks**:
```cpp
// Track created objects
array<Object> m_Objects = new array<Object>;

void CreateObjects()
{
    Object obj = GetGame().CreateObject(...);
    m_Objects.Insert(obj);
}

void CleanupObjects()
{
    foreach (Object obj : m_Objects)
    {
        if (obj) obj.Delete();
    }
    m_Objects.Clear();
}
```

**Avoid Double Delete**:
```cpp
// Wrong
Object obj = CreateObj();
obj.Delete();
obj.Delete();  // Crash!

// Correct
Object obj = CreateObj();
if (obj)
{
    obj.Delete();
    obj = null;  // Clear reference
}
```

---

## Performance-Related Crashes

### Server Crashes Under Load

**Problem**: Crashes when many players online

**Solutions**:

**Optimize Server Settings**:
```json
// serverDZ.cfg
{
    "maxPlayers": 60,  // Don't exceed your capacity
    "instanceId": 1,
    "loginQueueConcurrentPlayers": 5,
    "loginQueueMaxPlayers": 100,
    
    // Performance settings
    "networkRangeClose": 20,
    "networkRangeNear": 150,
    "networkRangeFar": 1000,
    "networkRangeDistantEffect": 4000,
    
    // Reduce if needed
    "lootHistory": 1,
    "disableMultiPlace": true,
    "disableContainerDamage": true
}
```

**Reduce AI/Zombies**:
```xml
<!-- Events.xml -->
<event name="InfectedArmy">
    <nominal>0</nominal>  <!-- Reduce or disable
    <min>0</min>
</event>
```

**Optimize Database**:
```
If using database:
- Regular optimization/vacuum
- Index frequently queried columns
- Archive old data
- Use SSD storage
```

### Memory Exhaustion Crash

**Problem**: Server runs out of memory

**Monitor Memory**:
```batch
REM Windows PowerShell
Get-Process DayZServer_x64 | Select-Object WorkingSet64

# Linux
ps aux | grep DayZServer
```

**Solutions**:

**Increase Virtual Memory**:
```
Windows:
System Properties → Advanced → Performance Settings
→ Advanced → Virtual Memory
Set to 1.5x-2x physical RAM
```

**Implement Auto-Restart**:
```batch
REM Restart when memory exceeds threshold
@echo off
:loop
DayZServer_x64.exe -config=serverDZ.cfg
timeout /t 60
goto loop
```

**Reduce Memory Usage**:
```
- Fewer mods
- Smaller loot tables
- Fewer spawned entities
- Cleanup scripts
```

---

## Mod-Related Crashes

### Crash After Adding Mod

**Problem**: Server crashes after installing new mod

**Debugging Process**:

**Step 1: Verify Mod Compatibility**
```
Check:
- Mod supports current DayZ version
- Required dependencies installed
- No conflicting mods
- Mod load order correct
```

**Step 2: Test Mod Isolation**
```
Add mods one at a time:
1. Start with NO mods
2. Add mod 1, test
3. Add mod 2, test
4. Continue until crash occurs
5. Last mod added is likely culprit
```

**Step 3: Check Mod Logs**
```
Look for mod-specific errors in:
ServerProfile\script.log
ServerProfile\*.rpt

Search for mod name or related classes
```

**Step 4: Verify Mod Files**
```
Check:
- All .pbo files present
- .bikey in keys folder
- No corrupted downloads
- Correct folder structure
```

### Mod Load Order Issues

**Problem**: Mods crash due to wrong load order

**Common Load Orders**:

**Framework Mods FIRST**:
```batch
-mod=@CF;@DayZ-Expansion;@TraderPlus;@OtherMods

Correct order:
1. Community Framework (CF)
2. Large framework mods (Expansion)
3. Mods depending on frameworks
4. Independent mods
5. Map mods LAST
```

**Check Mod Requirements**:
```
Read each mod's Workshop page:
- Required mods
- Load order requirements
- Known conflicts
```

---

## Database Crashes

### MySQL Connection Lost

**Error Message**:
```
Error: Lost connection to MySQL server
```

**Solutions**:

**Fix 1: Increase Timeouts**
```sql
-- In my.cnf or my.ini
[mysqld]
wait_timeout = 600
interactive_timeout = 600
max_allowed_packet = 64M
```

**Fix 2: Connection Pooling**
```cpp
// In scripts
class DatabaseManager
{
    protected ref MySQL m_Connection;
    protected int m_LastConnectAttempt;
    
    MySQL GetConnection()
    {
        if (!m_Connection || !m_Connection.IsConnected())
        {
            ReconnectDatabase();
        }
        return m_Connection;
    }
    
    void ReconnectDatabase()
    {
        if (m_Connection)
            m_Connection.Close();
        
        m_Connection = new MySQL();
        m_Connection.Connect("localhost", "user", "pass", "db");
    }
}
```

**Fix 3: Check Network**
```
- Verify MySQL server is running
- Check firewall allows connection
- Test connection manually
- Check MySQL error logs
```

### Database Lock Timeout

**Error Message**:
```
Lock wait timeout exceeded
```

**Solutions**:

**Optimize Queries**:
```sql
-- Add indexes
CREATE INDEX idx_steamid ON players(steam_id);

-- Use transactions properly
START TRANSACTION;
-- Multiple queries
COMMIT;
```

**Increase Lock Timeout**:
```sql
SET innodb_lock_wait_timeout = 120;
```

---

## Logging & Diagnostics

### Enable Detailed Logging

**Server Start Parameters**:
```batch
-dologs -adminlog -netlog -freezecheck
```

**What Each Does**:
```
-dologs        = Enable all logging
-adminlog      = Log admin actions
-netlog        = Network traffic log
-freezecheck   = Detect server freezes
```

### Crash Dump Analysis

**Windows**:
```
Crash dumps location:
C:\Users\[User]\AppData\Local\CrashDumps

Use WinDbg or Visual Studio to analyze
```

**Linux**:
```bash
# Enable core dumps
ulimit -c unlimited

# Core dumps saved to:
/var/crash/

# Analyze with gdb
gdb ./DayZServer core
```

### Log Rotation

**Prevent Huge Log Files**:
```bash
#!/bin/bash
# log_rotation.sh

LOG_DIR="/path/to/ServerProfile"
MAX_SIZE=100M  # 100 MB

find $LOG_DIR -name "*.log" -size +$MAX_SIZE -exec gzip {} \;
find $LOG_DIR -name "*.log.gz" -mtime +7 -delete
```

---

## Emergency Recovery

### Server Won't Start at All

**Nuclear Option**:
```
1. Backup everything
2. Delete ServerProfile folder
3. Server creates fresh profile on start
4. Restore mission folder
5. Test startup
6. Gradually restore configs
```

### Corrupted Mission File

**Problem**: server_data.bin corrupted

**Solutions**:
```
1. Delete: ServerProfile\[Mission]\storage_1\data\
2. Server regenerates on restart
3. Players keep characters
4. World state resets (bases, vehicles gone)

ALWAYS backup before this!
```

### Complete Server Reset

**Fresh Start Steps**:
```
1. Backup current setup
2. Uninstall server
3. Delete all server files
4. Fresh SteamCMD install
5. Reinstall mods
6. Restore configs
7. Test thoroughly
```

---

## Prevention Strategies

### Regular Maintenance

**Daily**:
```
- Check logs for errors
- Monitor RAM/CPU usage
- Check player count trends
```

**Weekly**:
```
- Clean old logs
- Backup database
- Update mods (test first!)
- Check disk space
```

**Monthly**:
```
- Update server
- Update OS
- Review crash logs
- Optimize database
```

### Monitoring Setup

**Use Monitoring Tools**:
```
- CFTools Cloud
- Battlemetrics
- Custom scripts
- Server monitoring software
```

**Alert on Issues**:
```
- Server offline > 5 minutes
- Memory > 90%
- CPU > 90% for 10 min
- Crash detected
```

### Backup Strategy

**What to Backup**:
```
Daily:
- ServerProfile\players\
- Mission folder
- Database

Weekly:
- Entire server folder
- Configuration files
```

**Automated Backup Script**:
```batch
@echo off
set BACKUP_DIR=D:\Backups\DayZ
set DATE=%DATE:~-4,4%%DATE:~-10,2%%DATE:~-7,2%

xcopy /E /I /Y "ServerProfile" "%BACKUP_DIR%\%DATE%\ServerProfile"
xcopy /E /I /Y "mpmissions" "%BACKUP_DIR%\%DATE%\mpmissions"
```

---

## Getting Help

### Information to Provide

When asking for help:
```
1. Server version (DayZ version)
2. Operating System
3. RAM/CPU specs
4. Mods list with versions
5. Startup parameters
6. Last 100 lines of logs
7. What changed before crash
8. How to reproduce
```

### Where to Get Help

- **DayZ Forums**: https://forums.dayz.com/
- **Server Discord Communities**
- **Hosting Provider Support**
- **Mod Author Discord**
- **Reddit r/dayzservers**

---

**Pro Tip**: Keep a changelog of every server change. When crashes start, you'll know exactly what changed!

