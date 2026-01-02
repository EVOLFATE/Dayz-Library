# Configuration Templates

## Overview
This directory contains ready-to-use configuration templates for DayZ modding and server administration.

## Available Templates

### 1. types-xml-template.xml
Complete template for adding custom items to the loot economy. Includes:
- Weapons configuration
- Clothing items setup
- Food and consumables
- Tools and equipment
- Comments explaining all fields and common values

### 2. config-cpp-template.cpp
Comprehensive config.cpp template for creating DayZ mods. Includes:
- Basic mod structure (CfgPatches, CfgMods)
- Custom weapons configuration
- Custom clothing setup
- Food items
- Tools and equipment
- Sounds and audio
- Ammo types and magazines

### 3. serverDZ-cfg-template.json
Complete server configuration template with:
- Basic server settings (name, password, slots)
- Performance tuning options
- Network configuration
- Logging and admin settings
- MOTD configuration

### 4. server-start-script.sh
Bash script template for Linux server startup with:
- Configurable server parameters
- Mod loading
- Automatic log backup
- Process monitoring

## How to Use

1. **Copy the template** you need to your project
2. **Modify the values** to match your requirements
3. **Read the comments** for guidance on each setting
4. **Test thoroughly** before deploying to production

## Examples

### Using the types.xml template:
```bash
cp types-xml-template.xml /path/to/your/mission/db/types.xml
# Edit and add your custom items
```

### Using the config.cpp template:
```bash
cp config-cpp-template.cpp /path/to/your/mod/config.cpp
# Customize for your mod
```

### Using the server startup script:
```bash
cp server-start-script.sh /path/to/your/server/start.sh
chmod +x /path/to/your/server/start.sh
# Edit configuration variables
./start.sh
```

## Contributing
We welcome additional templates! If you have useful configuration templates:
1. Review [CONTRIBUTING.md](../../CONTRIBUTING.md)
2. Add your template with detailed comments
3. Update this README
4. Submit a pull request

---

**Status**: ✅ Active - 4 Templates Available  
**Last Updated**: January 2026  
**Contributions Welcome**: Yes!
