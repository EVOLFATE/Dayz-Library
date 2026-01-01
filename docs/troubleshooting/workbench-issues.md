# DayZ Workbench Issues

## Common Problems with DayZ Workbench and Solutions

DayZ Workbench is the official development tool for creating DayZ mods. This guide covers all common issues and their solutions.

---

## Installation & Setup Issues

### Workbench Won't Install

**Problem**: Workbench installation fails or doesn't appear in Steam Tools

**Solutions**:
1. **Verify you own DayZ** - Workbench requires ownership
2. **Check Steam Library** → Tools → DayZ Tools
3. **Right-click DayZ Tools** → Properties → Local Files → Verify Integrity
4. **Ensure enough disk space** - Requires ~15GB
5. **Run Steam as Administrator**

### Workbench Won't Launch

**Problem**: Clicking launch does nothing or crashes immediately

**Solutions**:
```
1. Check logs at:
   C:\Users\[YourUser]\AppData\Local\DayZ\

2. Common fixes:
   - Update graphics drivers
   - Install Visual C++ Redistributables (all versions)
   - Install DirectX End-User Runtime
   - Disable antivirus temporarily
   - Run as Administrator
```

### "Missing DLLs" Error

**Problem**: Error about missing .dll files (VCRUNTIME140.dll, etc.)

**Solution**:
```
Download and install:
- Visual C++ 2015-2022 Redistributable (x64)
- Visual C++ 2013 Redistributable (x64)
- Visual C++ 2010 Redistributable (x64)

Download from Microsoft official site:
https://support.microsoft.com/en-us/help/2977003/
```

---

## P: Drive Issues

### P: Drive Not Mounting

**Problem**: P: drive doesn't appear after mounting in Workbench

**Solutions**:

**Method 1: Via Workbench**
```
1. Launch Workbench
2. Tools → Options → Environment
3. Set "P: Drive Path" to your DayZ directory
4. Click "Mount P: Drive"
5. Restart Workbench
```

**Method 2: Manual Mount**
```batch
REM Create mount_p.bat
@echo off
subst P: "C:\Program Files (x86)\Steam\steamapps\common\DayZ"
pause
```

**Method 3: Using Command Prompt (Admin)**
```batch
subst P: "C:\Path\To\Your\DayZ"
```

### P: Drive Disappears After Restart

**Problem**: P: drive unmounts when computer restarts

**Solutions**:

**Permanent Mount Script**
```batch
REM Create permanent_p_drive.bat in Startup folder
@echo off
subst P: "C:\Program Files (x86)\Steam\steamapps\common\DayZ"
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Run" /v "MountPDrive" /t REG_SZ /d "%~f0" /f
```

**Startup Folder Location**:
```
C:\Users\[YourName]\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup
```

### "Drive P: is already mapped"

**Problem**: Can't mount because drive letter is in use

**Solutions**:
```batch
REM Unmount first
subst P: /D

REM Then remount
subst P: "C:\Path\To\DayZ"
```

---

## Workbench Scripting Editor Issues

### Intellisense Not Working

**Problem**: Code completion and suggestions don't appear

**Solutions**:
1. **Rebuild Script Modules**:
   - Tools → Options → Scripts
   - Click "Rebuild All"
   - Wait for completion (can take 5-10 minutes)

2. **Check Script Paths**:
   - Tools → Options → Scripts
   - Verify paths point to correct directories

3. **Clear Cache**:
   - Delete: `C:\Users\[User]\AppData\Local\DayZ\cache`
   - Restart Workbench

### Syntax Highlighting Broken

**Problem**: Code appears in plain text without colors

**Solutions**:
1. **Reset Editor Settings**:
   - Tools → Options → Editor
   - Click "Reset to Defaults"

2. **Reinstall Script Module**:
   - Delete Script module cache
   - Rebuild from Tools menu

### "Cannot Find Script Module"

**Problem**: Workbench can't locate script files

**Solutions**:
```
1. Verify P: drive is mounted
2. Check config.cpp points to correct script paths
3. Verify class names match file names
4. Check for typos in #include statements

Example correct structure:
P:\MyMod\
  ├── Config\
  │   └── config.cpp
  └── Scripts\
      └── 4_World\
          └── MyClass.c
```

---

## Building & Packaging Issues

### Addon Builder Not Found

**Problem**: Workbench can't find AddonBuilder.exe

**Solutions**:
1. **Locate AddonBuilder**:
   ```
   Default location:
   C:\Program Files (x86)\Steam\steamapps\common\DayZ Tools\Bin\AddonBuilder\AddonBuilder.exe
   ```

2. **Set Path in Workbench**:
   - Tools → Options → Add-ons
   - Set "Addon Builder Path"

3. **Alternative**: Use standalone Addon Builder
   - Launch directly from DayZ Tools folder
   - Configure paths manually

### Build Fails with No Error Message

**Problem**: Build process fails silently

**Solutions**:

**Check Common Issues**:
```
1. File path too long (Windows 260 char limit)
   Solution: Move project closer to root (C:\Projects\)

2. Special characters in filenames
   Solution: Use only alphanumeric, underscore, hyphen

3. Spaces in folder names
   Solution: Replace with underscores

4. Missing required files
   Solution: Check $PBOPREFIX$ and all references
```

**Enable Verbose Logging**:
1. Tools → Options → Add-ons
2. Enable "Verbose Logging"
3. Check output window for details

### PBO Missing Files

**Problem**: Built PBO doesn't contain all files

**Solutions**:

**Check File Filters**:
```
AddonBuilder includes/excludes certain extensions by default

Common excluded:
- .psd (Photoshop)
- .blend (Blender)
- .max (3ds Max)
- .fbx (before conversion)

Solution: Convert to proper formats:
- Models: .p3d
- Textures: .paa
- Configs: .cpp, .rvmat
```

**Verify $PBOPREFIX$**:
```
Create file: $PBOPREFIX$
Content: MyMod\Data

This sets the internal PBO path structure
```

---

## Performance & Crashes

### Workbench Crashes on Launch

**Problem**: Workbench crashes immediately or during startup

**Solutions**:

**Update Graphics Drivers**:
```
NVIDIA: https://www.nvidia.com/Download/index.aspx
AMD: https://www.amd.com/en/support
```

**Check Event Viewer** (Windows):
```
1. Win + X → Event Viewer
2. Windows Logs → Application
3. Look for Workbench errors
4. Note error codes and search online
```

**Safe Mode Launch**:
```batch
REM Create safe_launch.bat
"C:\Program Files (x86)\Steam\steamapps\common\DayZ Tools\Bin\Workbench\workbenchApp.exe" -nosplash -noWorkspace
```

### Workbench Freezes During Build

**Problem**: Workbench becomes unresponsive while building

**Solutions**:
1. **Increase priority** in Task Manager
2. **Close other programs** to free RAM
3. **Build smaller sections** at a time
4. **Disable real-time antivirus scanning** for project folder
5. **Use standalone Addon Builder** instead

### Memory Errors

**Problem**: "Out of memory" or similar errors

**Solutions**:
```
1. Close unnecessary programs
2. Increase virtual memory (pagefile)
3. Build in smaller chunks
4. Optimize textures (reduce resolution)
5. Remove unused assets before building

Recommended RAM: 16GB minimum for large mods
```

---

## Project & Workspace Issues

### "Failed to Load Workspace"

**Problem**: Workbench can't open your project

**Solutions**:

**Repair Workspace File**:
```xml
<!-- Check .wbproject file syntax -->
<?xml version="1.0" encoding="UTF-8"?>
<Project Name="MyMod">
    <Script File="Scripts"/>
    <Config File="Config"/>
</Project>
```

**Create New Workspace**:
1. File → New → Workspace
2. Set correct paths
3. Re-add files manually if needed

### Files Not Showing in Project Explorer

**Problem**: Your files exist but don't appear in Workbench

**Solutions**:
1. **Refresh**: Right-click → Refresh
2. **Check Filters**: View → Show Hidden Files
3. **Verify P: Drive**: Must be mounted
4. **Check File Extensions**: Workbench hides some by default

### Changes Not Saving

**Problem**: Edits to files don't persist

**Solutions**:
```
1. Check file permissions (not read-only)
2. Run Workbench as Administrator
3. Check if file is locked by another program
4. Verify save location (P: vs local drive)
5. Check disk space
```

---

## Debugging Issues

### Debugger Won't Attach

**Problem**: Can't debug scripts in Workbench

**Solutions**:

**Enable Debug Mode**:
```
1. Run DayZ with -filePatching parameter
2. In Workbench: Debug → Attach to Process
3. Select DayZ.exe or DayZServer.exe
4. Set breakpoints in code
```

**Launch Config** (shortcuts):
```
Launch DayZ: -mod=@YourMod -filePatching
Launch Server: -config=serverDZ.cfg -mod=@YourMod -filePatching
```

### Breakpoints Not Hitting

**Problem**: Debugger doesn't stop at breakpoints

**Solutions**:
1. **Verify -filePatching** is enabled
2. **Check code is actually executing** (add Print() statements)
3. **Rebuild scripts** (Tools → Rebuild All)
4. **Restart both DayZ and Workbench**

### "Cannot Read Variables"

**Problem**: Can't inspect variable values in debugger

**Solutions**:
1. **Build with debug symbols** enabled
2. **Check variable scope** (local vs member)
3. **Use watch window** explicitly
4. **Print to console** as fallback

---

## Terrain & Object Editor Issues

### Terrain Won't Load

**Problem**: Terrain Builder can't load terrain files

**Solutions**:
1. **Check file paths** are correct
2. **Verify all layers** exist (satellite, mask, etc.)
3. **Check heightmap resolution** matches config
4. **Ensure enough RAM** (terrain editing is memory-intensive)

### Objects Not Placing

**Problem**: Can't place objects in Object Editor

**Solutions**:
1. **Verify P: drive** is mounted
2. **Check object exists** in object browser
3. **Load correct libraries** (Tools → Object Browser)
4. **Check layer is unlocked** and visible

---

## Integration with External Tools

### Blender Models Won't Import

**Problem**: Can't import models from Blender

**Solutions**:

**Use Correct Export Format**:
```
Blender → FBX 7.4 Binary
Settings:
- Apply Modifiers
- Selected Objects
- Mesh: Enabled
- Armature: Enabled (if animated)
```

**Import in Object Builder First**:
```
1. Export from Blender as FBX
2. Import in Object Builder
3. Configure LODs
4. Export as P3D
5. Use P3D in Workbench
```

### Textures Not Showing

**Problem**: Models appear black or white

**Solutions**:
1. **Convert to PAA format** using Pal2PacE or TexView
2. **Check texture paths** in RVMAT files
3. **Verify textures are in correct folder**
4. **Check UV mapping** in model

**Example RVMAT**:
```cpp
ambient[] = {1, 1, 1, 1};
diffuse[] = {1, 1, 1, 1};
forcedDiffuse[] = {0, 0, 0, 0};
emmisive[] = {0, 0, 0, 0};
specular[] = {0, 0, 0, 0};
specularPower = 1;
PixelShaderID = "Normal";
VertexShaderID = "Basic";

class Stage1 {
    texture = "MyMod\Data\textures\my_texture_co.paa";
    uvSource = "tex";
};
```

---

## Third-Party Plugin Issues

### Enforce Extension Not Working (VSCode)

**Problem**: Syntax highlighting for EnScript not working in VSCode

**Solutions**:

**Install Enforce Extension**:
```
1. Open VSCode
2. Extensions (Ctrl+Shift+X)
3. Search "Enforce"
4. Install "Enforce Script" by DayZ Community
5. Reload window
```

**Configure File Associations**:
```json
// settings.json
{
    "files.associations": {
        "*.c": "enforce"
    }
}
```

---

## Common Error Messages & Solutions

### Error: "Failed to compile script module"

**Cause**: Syntax error in scripts

**Solution**:
```
1. Read the full error message (shows line number)
2. Check for:
   - Missing semicolons
   - Unmatched brackets
   - Incorrect class names
   - Wrong inheritance
3. Use VSCode with Enforce for better error detection
```

### Error: "Cannot find class 'ClassName'"

**Cause**: Class not defined or not inherited correctly

**Solution**:
```cpp
// Make sure class is modded correctly
modded class ExistingClass
{
    // Your code
}

// Or defined if new
class MyNewClass : ExistingClass
{
    // Your code
}
```

### Error: "Texture not found"

**Cause**: Incorrect path or texture doesn't exist

**Solution**:
```
1. Check path syntax:
   - Use backslashes: MyMod\Data\texture.paa
   - No leading slash
   - Case-sensitive on Linux servers

2. Verify file exists in PBO

3. Check file extension (.paa not .png)
```

---

## Performance Optimization

### Speed Up Workbench

**Tips**:
1. **Exclude project folder from antivirus**
2. **Use SSD for project files**
3. **Increase virtual memory** (16GB+)
4. **Close unnecessary background apps**
5. **Disable Windows Search indexing** for project folder
6. **Use incremental builds** when possible

### Reduce Build Times

**Strategies**:
```
1. Build only changed files
2. Use binarize sparingly (slower but smaller)
3. Exclude unnecessary files (use .biprivatekey)
4. Build on faster storage (NVMe SSD)
5. Consider build server for large projects
```

---

## Getting More Help

### Official Resources
- **DayZ Tools Forum**: https://forums.dayz.com/forum/134-dayz-modding/
- **Bohemia Wiki**: https://community.bistudio.com/wiki/DayZ:Workbench

### Community Resources
- **DayZ Modding Discord**: Active community with experienced modders
- **YouTube Tutorials**: Search "DayZ Workbench tutorial"
- **Reddit r/dayzmodding**: Community support

### Log Files to Check
```
Workbench Logs:
C:\Users\[User]\AppData\Local\DayZ\

Server Logs:
[ServerRoot]\profiles\*.log

Client RPT:
C:\Users\[User]\AppData\Local\DayZ\*.rpt
```

---

**Pro Tip**: Always keep a backup of working versions before making major changes to Workbench settings or projects!

