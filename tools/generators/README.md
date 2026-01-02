# Generators

## Overview
This directory contains code generation tools for DayZ modding.

## Available Tools

### 1. config-generator.py
**Generates complete mod structure with config.cpp**

Features:
- ✅ Creates full mod directory structure
- ✅ Generates config.cpp with proper CfgPatches and CfgMods
- ✅ Sets up script directories (3_Game, 4_World, 5_Mission)
- ✅ Creates data directory for assets
- ✅ Includes example configurations
- ✅ Validates mod name

Usage:
```bash
python config-generator.py <mod_name> <author> [output_dir]
```

Examples:
```bash
# Generate in current directory
python config-generator.py MyCustomMod "John Doe"

# Generate in specific directory
python config-generator.py ZombieHorde "ZombieTeam" ./mods
```

Output:
```
✅ Generated mod structure at: MyCustomMod/
✅ Created config.cpp

Directory structure:
  MyCustomMod/
    ├── config.cpp
    ├── scripts/
    │   ├── 3_Game/
    │   ├── 4_World/
    │   └── 5_Mission/
    └── data/

Next steps:
1. Add your script files to the scripts/ directories
2. Add your models and textures to the data/ directory
3. Update config.cpp with your custom items
4. Build the mod using Addon Builder
```

Generated config.cpp includes:
- Proper mod patches and dependencies
- Script module definitions
- Example weapon configuration
- Example clothing configuration
- Commented templates for common items

## Installation

Requirements:
- Python 3.6+
- No external dependencies

```bash
# Make executable (Linux/Mac)
chmod +x config-generator.py

# Run directly
./config-generator.py MyMod "Author Name"
```

## Workflow Example

### Creating a New Mod

1. **Generate structure:**
```bash
python config-generator.py MyWeaponMod "YourName" ./P:/MyWeaponMod
```

2. **Add scripts:**
```bash
# Copy script templates
cp ../../templates/script-templates/custom-item-class.c P:/MyWeaponMod/scripts/4_World/
```

3. **Edit config.cpp:**
- Uncomment weapon examples
- Add your weapon definitions
- Configure attachments and properties

4. **Build with Addon Builder:**
```bash
# Use DayZ Tools Addon Builder
# Source: P:/MyWeaponMod
# Output: @MyWeaponMod/Addons/MyWeaponMod.pbo
```

## Future Generators

Planned tools:
- **types-generator.py** - Generate types.xml entries from templates
- **trader-generator.py** - Generate trader configs
- **event-generator.py** - Generate event configs
- **mission-generator.py** - Generate complete mission structure

## Contributing
Have ideas for generators? We welcome:
- Item/weapon generators
- Config converters
- Batch processors
- Template expanders

See [CONTRIBUTING.md](../../CONTRIBUTING.md) for guidelines.

---

**Status**: ✅ Active - 1 Tool Available  
**Last Updated**: January 2026  
**Contributions Welcome**: Yes!
