# Performance & Optimization Issues

## Complete Guide to DayZ Performance Problems

Performance issues affect both servers and clients. This guide covers FPS drops, server lag, memory issues, and optimization techniques.

---

## Client-Side Performance Issues

### Low FPS (Frames Per Second)

**Problem**: Game runs slowly, stuttering, poor framerates

**Quick Fixes**:

**1. Lower Graphics Settings**
```
In-Game Settings → Video:
- Object Detail: Low/Medium
- Terrain Detail: Low
- Texture Detail: Medium
- Shadow Detail: Low/Disabled
- Antialiasing: Disabled
- Postprocess Quality: Low
- VSync: Disabled (unless screen tearing)
```

**2. Resolution Scaling**
```
Rendering Resolution: 90% or lower
Maintains UI clarity while improving FPS
```

**3. View Distance**
```
Preferred: 1500-2500m
Overall: 2000-3000m

Lower = better FPS
```

**Advanced Fixes**:

**Update Graphics Drivers**:
```
NVIDIA: https://www.nvidia.com/Download/index.aspx
AMD: https://www.amd.com/en/support

Use DDU (Display Driver Uninstaller) first:
1. Boot to Safe Mode
2. Run DDU
3. Install fresh drivers
4. Reboot
```

**Optimize Launch Parameters**:
```
Steam → DayZ → Properties → Launch Options:

-nologs
-skipintro
-noPause
-cpuCount=4
-exThreads=7
-malloc=system

Adjust cpuCount to your CPU cores
```

**Windows Optimizations**:
```
1. Power Plan: High Performance
2. Game Mode: Enabled
3. Game Bar: Disabled (can cause stuttering)
4. Windows Updates: Up to date
5. Background apps: Minimize
```

### Stuttering / Hitching

**Problem**: Game freezes briefly every few seconds

**Common Causes**:

**Cause 1: Loading Assets**
```
Solution: Install on SSD
NVMe SSD > SATA SSD > HDD

Move DayZ to faster drive:
1. Steam → DayZ → Properties
2. Local Files → Move Install Folder
```

**Cause 2: Memory Usage**
```
Check Task Manager during stutters

If RAM > 90%:
- Close background apps
- Increase virtual memory
- Add more physical RAM
```

**Cause 3: CPU Bottleneck**
```
Check CPU usage in Task Manager

If CPU at 100%:
- Close background processes
- Lower Object/Terrain Detail
- Reduce view distance
- Update CPU (if old)
```

**Cause 4: Network Lag**
```
If stutters sync with network activity:
- Check ping (under 100ms good)
- Use wired connection
- Close download/streaming apps
```

### Memory Errors

**Error**: "Out of Memory" or crashes due to RAM

**Solutions**:

**Increase Virtual Memory**:
```
Windows:
1. System Properties → Advanced
2. Performance → Settings
3. Advanced → Virtual Memory → Change
4. Custom size: 
   Initial: 1.5x RAM (e.g., 24576 MB for 16GB)
   Maximum: 3x RAM (e.g., 49152 MB)
5. Set → OK → Restart
```

**Close Memory-Hungry Apps**:
```
Common culprits:
- Chrome (many tabs)
- Discord (hardware acceleration)
- OBS (when not streaming)
- Spotify
- Background updates

Check Task Manager → Memory
```

**Add More RAM**:
```
Minimum: 8GB
Recommended: 16GB
Ideal: 32GB

DayZ with mods can use 8GB+ easily
```

---

## Server-Side Performance Issues

### Server Lag / Low TPS

**Problem**: Server running slow, players experiencing lag

**Understanding TPS**:
```
TPS = Ticks Per Second
Target: 60 TPS
Acceptable: 50-60 TPS
Poor: Below 40 TPS

Check in server logs or admin tools
```

**Common Causes**:

**Cause 1: Too Many Entities**
```
Solution: Reduce spawned items

types.xml - Reduce nominals:
<type name="Apple">
    <nominal>100</nominal>  <!-- Reduce this -->
    <min>50</min>
</type>

Focus on:
- Food items (apples, mushrooms)
- Common items (stones, sticks)
- Clothing
```

**Cause 2: AI/Zombie Load**
```
Solution: Reduce zombie count

events.xml:
<event name="InfectedArmy">
    <nominal>50</nominal>  <!-- Lower this -->
    <min>30</min>
</event>

Or use zombie limit mods
```

**Cause 3: Script Performance**
```
Badly optimized mods cause lag

Debug:
1. Remove mods one by one
2. Test TPS after each
3. Identify culprit
4. Contact mod author or replace
```

**Cause 4: Database Queries**
```
If using database mods:
- Add indexes to frequently queried columns
- Use connection pooling
- Optimize query frequency
- Consider caching
```

### High CPU Usage

**Problem**: Server CPU at 100%

**Solutions**:

**Optimize Server Settings**:
```json
// serverDZ.cfg
{
    "networkRangeClose": 20,
    "networkRangeNear": 150,
    "networkRangeFar": 1000,
    "networkRangeDistantEffect": 4000,
    
    // Reduce update frequency
    "guaranteedUpdates": 1,
    
    // Limit concurrent logins
    "loginQueueConcurrentPlayers": 3
}
```

**Reduce Player Count**:
```
If server struggles with 60 players:
- Reduce to 40-50
- Upgrade server hardware
- Optimize mods
```

**CPU Affinity** (Windows):
```
Dedicate cores to server:
1. Task Manager
2. Right-click DayZServer
3. Set Affinity
4. Select specific cores
5. Leave others for OS
```

**Linux nice/ionice**:
```bash
# Give server high priority
nice -n -10 ./DayZServer ...

# Or use ionice for disk I/O
ionice -c 1 -n 0 ./DayZServer ...
```

### High Memory Usage

**Problem**: Server using excessive RAM

**Solutions**:

**Monitor Memory**:
```batch
REM Windows PowerShell
while ($true) {
    Get-Process DayZServer* | Select WorkingSet64
    Start-Sleep -Seconds 60
}

# Linux
while true; do
    ps aux | grep DayZServer
    sleep 60
done
```

**Identify Memory Leaks**:
```
If memory grows steadily:
1. Note memory at server start
2. Monitor over hours
3. If continuous growth: memory leak

Common causes:
- Bad mod scripts
- Database connection leaks
- Not cleaning up objects
```

**Implement Auto-Restart**:
```batch
REM Restart every 4 hours
@echo off
:loop
start /wait DayZServer_x64.exe -config=serverDZ.cfg
timeout /t 14400
taskkill /F /IM DayZServer_x64.exe
goto loop
```

**Increase Server RAM**:
```
Minimum: 4GB
Recommended: 8GB
With mods: 12GB+
Heavily modded: 16GB+
```

### Network Performance

**Problem**: High ping, packet loss, desync

**Solutions**:

**Check Network Usage**:
```bash
# Linux
iftop
nethogs

# Windows
Resource Monitor → Network tab
```

**Optimize Network Settings**:
```json
// serverDZ.cfg
{
    "maxPing": 200,  // Kick high ping players
    "enableCfgGameplayFile": 0,
    "disableMultiPlace": true,
    "disableContainerDamage": true,
    
    // Reduce network ranges if needed
    "networkRangeClose": 15,
    "networkRangeNear": 100,
    "networkRangeFar": 800
}
```

**Server Location**:
```
Host server:
- Close to players
- Good datacenter
- Low latency routes

Test ping from player locations
```

**Bandwidth Requirements**:
```
Per Player: ~50-100 Kbps
60 Players: ~6 Mbps

Upload speed most critical!

Recommended: 100 Mbps+ up/down
```

---

## Optimization Techniques

### Loot Economy Optimization

**Reduce Total Loot**:
```xml
<!-- types.xml -->
<!-- Drastically reduce common items -->
<type name="Apple">
    <nominal>50</nominal>  <!-- Was 200 -->
    <min>25</min>
</type>

<type name="Pear">
    <nominal>50</nominal>
    <min>25</min>
</type>

Focus reductions on:
- Food (fruit, vegetables)
- Common clothes
- Stones/sticks
- Low-value items
```

**Increase Cleanup Speed**:
```xml
<type name="Apple">
    <lifetime>600</lifetime>  <!-- 10 min instead of 3600 -->
</type>

Faster cleanup = fewer entities
```

**Smart Nominal Values**:
```xml
<!-- Only spawn what's needed -->
<type name="RareMilitaryGear">
    <nominal>3</nominal>  <!-- Not 50! -->
    <min>1</min>
</type>
```

### Event Optimization

**Reduce Concurrent Events**:
```xml
<!-- events.xml -->
<event name="StaticHeliCrash">
    <nominal>2</nominal>  <!-- Was 5 -->
    <min>1</min>
</event>

<event name="VehicleHummer">
    <nominal>3</nominal>  <!-- Was 10 -->
</event>
```

**Disable Unused Events**:
```xml
<event name="UnusedEvent">
    <nominal>0</nominal>  <!-- Disabled -->
    <min>0</min>
</event>
```

### AI/Zombie Optimization

**Reduce Zombie Count**:
```xml
<event name="InfectedArmy">
    <nominal>30</nominal>  <!-- Was 100 -->
</event>
```

**Increase Despawn Distance**:
```
Zombies further from players despawn
Reduces total AI load
```

**Use AI Limit Mods**:
```
Mods that cap zombie count
Better than vanilla limits
```

### Script Optimization

**Avoid Frequent Loops**:
```cpp
// Bad
override void OnUpdate(float deltaTime)
{
    // Runs 60 times per second!
    CheckEverything();
}

// Good
float m_CheckTimer;
override void OnUpdate(float deltaTime)
{
    m_CheckTimer += deltaTime;
    if (m_CheckTimer > 5.0)  // Every 5 seconds
    {
        m_CheckTimer = 0;
        CheckEverything();
    }
}
```

**Minimize Network Calls**:
```cpp
// Bad - sends RPC every frame
void SendData()
{
    GetGame().RPCSingleParam(...);  // Spams network!
}

// Good - batch updates
array<ref Data> m_PendingData;
void QueueData(Data data)
{
    m_PendingData.Insert(data);
}

void SendBatch()  // Called periodically
{
    if (m_PendingData.Count() > 0)
    {
        GetGame().RPC(..., m_PendingData);
        m_PendingData.Clear();
    }
}
```

**Clean Up Objects**:
```cpp
// Always delete objects when done
class MyManager
{
    array<Object> m_Objects;
    
    void Cleanup()
    {
        foreach (Object obj : m_Objects)
        {
            if (obj) obj.Delete();
        }
        m_Objects.Clear();
    }
    
    ~MyManager()  // Destructor
    {
        Cleanup();
    }
}
```

---

## Mod-Specific Optimization

### Expansion Mod

**Performance Settings**:
```json
// ExpansionMod Settings
{
    "AI": {
        "MaximumAI": 20,  // Reduce if laggy
        "DespawnRadius": 1000
    },
    "BaseBuilding": {
        "CanRaidSafes": false  // Reduces checks
    }
}
```

### Trader Mods

**Optimization**:
```
- Reduce trader item count
- Increase trader zone radius (fewer zones)
- Cache trader data client-side
- Batch database queries
```

### Map Mods

**Large Maps**:
```
DeerIsle, Namalsk = Higher resource usage

Compensate:
- Reduce loot nominals
- Fewer AI
- Lower player count
- Better server hardware
```

---

## Monitoring Tools

### Server Monitoring

**CFTools Cloud**:
```
- Real-time TPS
- Player count
- Crash detection
- Performance graphs
```

**Battlemetrics**:
```
- Server status
- Player tracking
- Performance history
```

**Custom Monitoring**:
```batch
REM monitor.bat
@echo off
:loop
echo [%date% %time%]
wmic process where name="DayZServer_x64.exe" get WorkingSetSize
timeout /t 60
goto loop
```

### Client Monitoring

**In-Game**:
```
Show FPS: 
- GeForce Experience overlay
- AMD overlay
- Steam FPS counter
- MSI Afterburner + RivaTuner
```

**Performance Tools**:
```
- Task Manager (CPU, RAM, GPU)
- Resource Monitor (detailed)
- GPU-Z (GPU monitoring)
- HWiNFO64 (comprehensive)
```

---

## Benchmark & Testing

### Server Load Testing

**Simulate Players**:
```
Tools:
- DayZ Bot (if available)
- Multiple client instances (low settings)

Test scenarios:
- 10 players
- 30 players
- 60 players
- Peak capacity

Monitor TPS, CPU, RAM, bandwidth
```

### Client Benchmarking

**Consistent Testing**:
```
1. Same location (e.g., Cherno center)
2. Same time of day
3. Same settings
4. Same mods

Compare FPS before/after changes
```

**Benchmark Tools**:
```
Use:
- In-game FPS counter
- FrameView (NVIDIA)
- OCAT (AMD)

Record:
- Average FPS
- 1% Low FPS (shows stutters)
- Frame times
```

---

## Hardware Recommendations

### Client Minimum (1080p Medium)
```
CPU: Intel i5-8400 / AMD Ryzen 5 2600
GPU: GTX 1060 6GB / RX 580 8GB
RAM: 16GB DDR4
Storage: SATA SSD
```

### Client Recommended (1440p High)
```
CPU: Intel i7-10700K / AMD Ryzen 7 3700X
GPU: RTX 3070 / RX 6700 XT
RAM: 32GB DDR4
Storage: NVMe SSD
```

### Server Minimum (30 players, vanilla)
```
CPU: Intel i5-9600K / AMD Ryzen 5 3600
RAM: 8GB
Storage: SATA SSD
Bandwidth: 50 Mbps up
```

### Server Recommended (60 players, modded)
```
CPU: Intel i7-11700K / AMD Ryzen 7 5800X
RAM: 16GB+
Storage: NVMe SSD
Bandwidth: 100+ Mbps up
```

---

## Emergency Performance Fixes

### Server About to Crash

**Quick Actions**:
```
1. Kick all players
2. Save and restart
3. Check logs
4. Reduce load temporarily
```

### Immediate FPS Boost (Client)

**Ultra-Low Settings**:
```
Resolution: 720p
All settings: Disabled/Low
View Distance: 500m
Objects: 500m

Should give 2x FPS boost
```

---

## Performance Checklist

### Server Optimization
- [ ] Reduced loot nominals
- [ ] Lowered AI count
- [ ] Disabled unused events
- [ ] Optimized network settings
- [ ] Cleaned up old data
- [ ] Updated all mods
- [ ] Removed unnecessary mods
- [ ] Scheduled regular restarts
- [ ] Monitoring enabled
- [ ] Regular backups

### Client Optimization
- [ ] Updated drivers
- [ ] Game on SSD
- [ ] Lowered graphics settings
- [ ] Closed background apps
- [ ] Disabled overlays
- [ ] Optimized Windows
- [ ] Verified game files
- [ ] Adequate RAM/VRAM
- [ ] Good internet connection
- [ ] Latest game version

---

**Pro Tip**: Performance is a balance. Sometimes you must sacrifice features (mods, graphics, player count) for smooth gameplay!

