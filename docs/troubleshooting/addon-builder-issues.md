# Addon Builder & PBO Packaging Issues

## Complete Guide to PBO Creation Problems

PBO (Packed Bank Of files) is the archive format used by DayZ mods. This guide covers all issues related to creating, packing, and signing PBOs.

---

## Addon Builder Won't Launch

### "Addon Builder Not Found"

**Problem**: Workbench or scripts can't find AddonBuilder.exe

**Solutions**:

**Default Location**:
```
C:\Program Files (x86)\Steam\steamapps\common\DayZ Tools\Bin\AddonBuilder\AddonBuilder.exe
```

**If Missing**:
```
1. Verify DayZ Tools installation via Steam
2. Steam Library → Tools → DayZ Tools
3. Right-click → Properties → Local Files
4. "Verify integrity of tool files"
```

**Set Path in Workbench**:
```
1. Workbench → Tools → Options
2. Add-ons tab
3. Set "Addon Builder Path" to correct location
4. Click OK
5. Restart Workbench
```

### Addon Builder Crashes on Launch

**Problem**: Application closes immediately or shows error

**Solutions**:

**Method 1: Run as Administrator**
```
Right-click AddonBuilder.exe
Run as administrator
```

**Method 2: Install Prerequisites**
```
Required:
- .NET Framework 4.7.2+
- Visual C++ Redistributables
- DirectX End-User Runtime

Download from Microsoft official sites
```

**Method 3: Check Windows Version**
```
Addon Builder requires:
- Windows 7 SP1 or higher
- 64-bit OS
```

---

## P: Drive Issues

### P: Drive Not Mounted

**Problem**: Addon Builder can't find source files

**Why P: Drive?**
```
DayZ tools expect files on P: drive
This is a virtual drive pointing to your DayZ installation
Required for building mods
```

**Mount P: Drive via Workbench**:
```
1. Launch Workbench
2. Tools → Options → Environment
3. Set "P: Drive Path" to:
   C:\Program Files (x86)\Steam\steamapps\common\DayZ
4. Click "Mount P: Drive"
5. Verify in File Explorer
```

**Mount P: Drive Manually**:
```batch
REM mount_p.bat
@echo off
subst P: "C:\Program Files (x86)\Steam\steamapps\common\DayZ"
echo P: drive mounted!
pause
```

**Linux Alternative**:
```bash
#!/bin/bash
# Linux doesn't use P: drive
# Use absolute paths instead
# Or create symlink if needed
ln -s /path/to/DayZ /path/to/P
```

### P: Drive Unmounts After Reboot

**Problem**: P: drive disappears when computer restarts

**Permanent Mount Solution**:

**Windows Startup Script**:
```batch
REM Save to Startup folder
REM C:\Users\[User]\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\mount_p.bat

@echo off
subst P: "C:\Program Files (x86)\Steam\steamapps\common\DayZ"
```

**Registry Method**:
```batch
@echo off
REM permanent_p_drive.bat
subst P: "C:\Program Files (x86)\Steam\steamapps\common\DayZ"
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Run" /v "MountPDrive" /t REG_SZ /d "%~dpnx0" /f
```

**Task Scheduler Method**:
```
1. Open Task Scheduler
2. Create Basic Task
3. Trigger: At startup
4. Action: Start a program
5. Program: cmd.exe
6. Arguments: /c subst P: "C:\Path\To\DayZ"
7. Finish
```

---

## Build Failures

### "Build Failed" with No Error Message

**Problem**: Build stops but gives no details

**Enable Verbose Logging**:

**In Addon Builder**:
```
1. Options → Settings
2. Enable "Verbose Logging"
3. Enable "Show Console Window"
4. Try build again
5. Read output for errors
```

**Via Command Line**:
```batch
AddonBuilder.exe "P:\MyMod\Addons\MyPBO" "C:\Output" -project=P:\MyMod -clear -prefix=MyMod
```

**Common Hidden Errors**:
```
1. File path too long (Windows 260 char limit)
   Solution: Move project closer to root

2. Special characters in filenames
   Solution: Rename files (alphanumeric only)

3. Locked files
   Solution: Close all editors, restart

4. Insufficient permissions
   Solution: Run as Administrator

5. Corrupted project file
   Solution: Create new project
```

### "Cannot Find $PBOPREFIX$"

**Problem**: Addon Builder can't determine PBO structure

**Understanding $PBOPREFIX$**:
```
File name: $PBOPREFIX$
Location: Root of your addon folder
Content: Internal PBO path

Example:
P:\MyMod\Addons\Core\$PBOPREFIX$
Content: MyMod\Addons\Core
```

**Create $PBOPREFIX$ File**:
```
1. Navigate to addon folder:
   P:\MyMod\Addons\MyAddon\

2. Create text file: $PBOPREFIX$
   (No extension!)

3. Content should be:
   MyMod\Addons\MyAddon

4. Save (UTF-8 without BOM)
```

**Multiple Addons Example**:
```
P:\MyMod\
├── Addons\
│   ├── Core\
│   │   └── $PBOPREFIX$ → "MyMod\Addons\Core"
│   ├── Scripts\
│   │   └── $PBOPREFIX$ → "MyMod\Addons\Scripts"
│   └── Data\
│       └── $PBOPREFIX$ → "MyMod\Addons\Data"
```

### Build Extremely Slow

**Problem**: PBO packaging takes forever

**Optimization Tips**:

**Method 1: Exclude Unnecessary Files**
```
Addon Builder automatically excludes:
- .txt
- .log  
- .bak
- .psd (Photoshop)
- .blend (Blender)
- .fbx (source models)
- .max (3ds Max)

Add more exclusions in Addon Builder settings
```

**Method 2: Use Exclude File**
```
Create: .pboignore

Content (each line is a pattern):
*.psd
*.blend
*.max
*.fbx
temp/
backup/
```

**Method 3: Build on SSD**
```
NVMe SSD: Fastest
SATA SSD: Fast
HDD: Slow

Move project to SSD for faster builds
```

**Method 4: Disable Antivirus**
```
Temporarily disable real-time scanning:
- Antivirus
- Windows Defender

Add Addon Builder to exclusions
Add project folder to exclusions
```

**Method 5: Binarize Only When Needed**
```
Binarization = slower but smaller files

Development: Don't binarize
Release: Binarize

Setting in Addon Builder options
```

---

## File & Path Issues

### Windows Path Length Limit

**Error**: `The filename or extension is too long`

**Windows Limit**: 260 characters total path

**Solutions**:

**Method 1: Shorten Path**
```
Wrong:
C:\Users\MyName\Documents\Projects\Games\DayZ\Mods\MyAwesomeMod\Addons\Core\Scripts\4_World\Entities\...

Correct:
C:\DayZ\MyMod\Addons\Core\Scripts\...
```

**Method 2: Enable Long Paths (Windows 10+)**
```
1. Win+R → gpedit.msc
2. Computer Configuration
   → Administrative Templates
   → System
   → Filesystem
3. "Enable Win32 long paths" → Enabled
4. Reboot
```

**Method 3: Use Registry**
```
Windows Registry Editor Version 5.00

[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\FileSystem]
"LongPathsEnabled"=dword:00000001
```

### Special Characters in Filenames

**Problem**: Build fails with certain characters

**Invalid Characters**:
```
< > : " / \ | ? *

Also avoid:
- Spaces (use underscore)
- Accented characters (é, ñ, ü)
- Emojis
- Special symbols
```

**Naming Convention**:
```
Good:
my_item.p3d
player_animation.rtm
weapon_config.cpp

Bad:
my item.p3d
player@animation.rtm
weapon(config).cpp
```

### Case Sensitivity Issues

**Problem**: Works on Windows, breaks on Linux server

**Remember**:
```
Windows: Case-insensitive
Linux: Case-sensitive

File: MyTexture.paa
Reference in config:

Wrong on Linux: "mytexture.paa"
Correct: "MyTexture.paa"
```

**Best Practice**:
```
Use consistent casing:
- Lowercase for folders
- PascalCase for classes
- lowercase for files

Example:
P:\MyMod\
├── data\
│   ├── textures\
│   │   └── my_texture_co.paa
│   └── models\
│       └── my_item.p3d
└── scripts\
    └── 4_world\
        └── MyItem.c
```

---

## Content Issues

### Textures Not in PBO

**Problem**: Built PBO missing texture files

**Verify File Format**:
```
DayZ requires:
- Textures: .paa or .edds
- NOT .png, .jpg, .tga (must convert)

Use:
- Pal2PacE
- TexView 2
- Photoshop DDS plugin
```

**Check File Extensions**:
```
Addon Builder includes:
.paa
.edds
.rvmat

Excludes:
.psd
.tga
.png
.jpg

Convert before building!
```

**Verify in Config**:
```cpp
// config.cpp - check paths
class MyItem
{
    model = "\MyMod\Data\my_item.p3d";
    // .p3d must reference .rvmat
};
```

```cpp
// my_item.rvmat
class Stage1
{
    texture = "MyMod\Data\textures\my_texture_co.paa";
    // .paa must exist!
};
```

### Models Not Including

**Problem**: Built PBO missing .p3d files

**Check Model Format**:
```
DayZ requires: .p3d
NOT:
- .fbx (export to .p3d first)
- .obj
- .blend

Use Object Builder to convert
```

**Verify Model Paths**:
```cpp
class CfgVehicles
{
    class MyItem: ItemBase
    {
        model = "\MyMod\Data\Models\my_item.p3d";
        // Path must be correct!
    };
};
```

### Config.cpp Not Processing

**Problem**: Config.cpp syntax errors prevent build

**Common Syntax Errors**:

**Missing Semicolons**:
```cpp
// Wrong
class MyClass
{
    value = 10
}

// Correct
class MyClass
{
    value = 10;
};
```

**Array Syntax**:
```cpp
// Wrong
array[] = {1,2,3}

// Correct
array[] = {1,2,3};
```

**String Escaping**:
```cpp
// Wrong
path = "MyMod\Data\file.p3d";

// Correct
path = "\MyMod\Data\file.p3d";
// or
path = "MyMod\\Data\\file.p3d";
```

**Use Config Validator**:
```
Tools:
- Workbench config validator
- Online validators
- VSCode with DayZ extension
```

---

## Signing Issues

### "Mod Not Signed"

**Problem**: Server requires signed mods

**Understanding Signing**:
```
Signature = .bisign file
Proves PBO hasn't been modified
Required by many servers
```

**Generate Key Pair**:

**Using DSSignFile**:
```batch
REM Generate private key (.biprivatekey)
DSSignFile.exe mykey.biprivatekey

This also creates public key (.bikey)
```

**Sign PBO**:
```batch
REM Sign the PBO
DSSignFile.exe mykey.biprivatekey MyMod.pbo

Creates: MyMod.pbo.mykey.bisign
```

**Distribute**:
```
Give players:
- MyMod.pbo
- MyMod.pbo.mykey.bisign

Give server:
- MyMod.pbo
- MyMod.pbo.mykey.bisign
- mykey.bikey (in keys folder)
```

### "Invalid Signature"

**Problem**: Server rejects mod signature

**Causes**:

**Cause 1: Wrong Key**
```
Signed with keyA.biprivatekey
Server has keyB.bikey

Solution: Use matching keys!
```

**Cause 2: Modified PBO**
```
PBO changed after signing
Signature no longer valid

Solution: Re-sign after ANY changes
```

**Cause 3: Corrupted Files**
```
Transfer corruption
Download issue

Solution: Redownload/retransfer
```

**Verify Signature**:
```batch
REM Check if signature is valid
DSCheckSignatures.exe MyMod.pbo

Shows:
- Which key was used
- If signature is valid
```

---

## Batch Building

### Building Multiple PBOs

**Problem**: Need to build many addons

**Script Solution**:

**Windows Batch**:
```batch
@echo off
REM build_all.bat

set ADDONBUILDER="C:\...\AddonBuilder.exe"
set PROJECT=P:\MyMod
set OUTPUT=C:\Output

%ADDONBUILDER% "%PROJECT%\Addons\Core" "%OUTPUT%" -project=%PROJECT% -prefix=MyMod\Addons\Core
%ADDONBUILDER% "%PROJECT%\Addons\Scripts" "%OUTPUT%" -project=%PROJECT% -prefix=MyMod\Addons\Scripts
%ADDONBUILDER% "%PROJECT%\Addons\Data" "%OUTPUT%" -project=%PROJECT% -prefix=MyMod\Addons\Data

echo All PBOs built!
pause
```

**PowerShell**:
```powershell
# build_all.ps1

$AddonBuilder = "C:\...\AddonBuilder.exe"
$Project = "P:\MyMod"
$Output = "C:\Output"

$addons = @("Core", "Scripts", "Data")

foreach ($addon in $addons) {
    $source = "$Project\Addons\$addon"
    $prefix = "MyMod\Addons\$addon"
    
    & $AddonBuilder $source $Output -project=$Project -prefix=$prefix
    
    if ($LASTEXITCODE -ne 0) {
        Write-Error "Failed to build $addon"
        exit 1
    }
}

Write-Host "All PBOs built successfully!"
```

### Automated Build Pipeline

**CI/CD Example** (GitHub Actions):
```yaml
# .github/workflows/build.yml

name: Build PBOs

on:
  push:
    branches: [ main ]

jobs:
  build:
    runs-on: windows-latest
    
    steps:
    - uses: actions/checkout@v2
    
    - name: Setup DayZ Tools
      run: |
        # Install DayZ Tools via SteamCMD
        # Mount P: drive
        # Setup paths
    
    - name: Build PBOs
      run: |
        ./build_all.bat
    
    - name: Upload Artifacts
      uses: actions/upload-artifact@v2
      with:
        name: built-pbos
        path: Output/*.pbo
```

---

## Verification & Testing

### Verify PBO Contents

**Using PBO Manager**:
```
Tools:
- PBO Manager (Mikero's Tools)
- Eliteness
- PBO Project

Extract and inspect PBO contents
```

**Command Line**:
```batch
REM List PBO contents
ExtractPboDos.exe -L MyMod.pbo

REM Extract PBO
ExtractPboDos.exe MyMod.pbo C:\Extracted\
```

### Test Built PBO

**Quick Test**:
```
1. Copy MyMod.pbo to:
   C:\...\DayZ\@MyMod\Addons\

2. Launch DayZ with:
   -mod=@MyMod

3. Check for errors in logs
4. Test in-game functionality
```

**Server Test**:
```
1. Upload to test server
2. Add to -mod= parameter
3. Restart server
4. Check server logs
5. Connect and test
```

---

## Best Practices

### Project Structure

**Recommended Layout**:
```
P:\MyMod\
├── Addons\
│   ├── Core\
│   │   ├── $PBOPREFIX$
│   │   └── config.cpp
│   ├── Scripts\
│   │   ├── $PBOPREFIX$
│   │   └── 4_World\
│   └── Data\
│       ├── $PBOPREFIX$
│       ├── models\
│       └── textures\
├── Keys\
│   ├── mymod.biprivatekey
│   └── mymod.bikey
└── Build\
    └── build.bat
```

### Building Workflow

**Development**:
```
1. Make changes
2. Quick build (no binarize)
3. Test locally
4. Repeat
```

**Release**:
```
1. Final changes committed
2. Full build (with binarize)
3. Sign PBOs
4. Test thoroughly
5. Package for distribution
6. Create version tag
```

### Version Control

**What to Commit**:
```
✅ Source files (.c, .cpp, .xml)
✅ Build scripts
✅ Documentation
✅ $PBOPREFIX$ files

❌ Built PBOs
❌ Private keys
❌ Large binary files (use LFS)
```

---

## Tools Reference

### Essential Tools

**Addon Builder**:
```
Location: DayZ Tools\Bin\AddonBuilder\
Purpose: Build PBOs
Free: Yes (with DayZ Tools)
```

**DSSignFile / DSCheckSignatures**:
```
Location: DayZ Tools\Bin\DSUtils\
Purpose: Sign and verify PBOs
Free: Yes (with DayZ Tools)
```

**Mikero's Tools** (Community):
```
Website: https://mikero.bytex.digital/Downloads
Tools:
- DeP3D (model converter)
- DePbo (PBO extractor)
- Rapify (config binarizer)
- MakePbo (PBO creator)

Free: Some tools
Paid: Full suite
```

**Eliteness**:
```
Purpose: PBO viewer/editor
Free: Yes
Simple GUI for PBO management
```

---

**Pro Tip**: Always keep your source files separate from build output. Never edit files inside PBOs!

