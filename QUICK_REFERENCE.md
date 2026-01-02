# DayZ Quick Reference Cheat Sheet

Quick lookup for common DayZ modding and server administration tasks.

## 🎯 Essential Links

| What You Need | Where to Find It |
|---------------|------------------|
| **Troubleshoot an error** | [Issue Index](docs/ISSUE_INDEX.md) |
| **Find tools/services** | [Ecosystem Guide](docs/ECOSYSTEM.md) |
| **Get started modding** | [Getting Started](docs/getting-started/introduction.md) |
| **Server setup** | [Server Hosting](docs/server-hosting/) |
| **Navigation help** | [Navigation Guide](docs/NAVIGATION.md) |

---

## 📝 Configuration Files

### types.xml - Loot Economy
```xml
<type name="ItemName">
    <nominal>10</nominal>     <!-- Target spawn count -->
    <min>5</min>              <!-- Minimum guaranteed -->
    <lifetime>3600</lifetime>  <!-- Cleanup time (seconds) -->
    <restock>1800</restock>    <!-- Respawn time (seconds) -->
    <category name="weapons"/> <!-- Item category -->
    <usage name="Military"/>   <!-- Spawn location -->
    <value name="Tier2"/>      <!-- Loot tier -->
</type>
```

**Template**: [types-xml-template.xml](templates/config-templates/types-xml-template.xml)

### config.cpp - Mod Configuration
```cpp
class CfgPatches {
    class YourMod {
        requiredAddons[] = {"DZ_Data"};
    };
};

class CfgMods {
    class YourMod {
        dir = "YourMod";
        name = "Your Mod Name";
        dependencies[] = {"Game", "World", "Mission"};
    };
};
```

**Template**: [config-cpp-template.cpp](templates/config-templates/config-cpp-template.cpp)

### serverDZ.cfg - Server Settings
```json
{
  "hostname": "Server Name",
  "maxPlayers": 60,
  "passwordAdmin": "adminpass",
  "serverTimeAcceleration": 4
}
```

**Template**: [serverDZ-cfg-template.json](templates/config-templates/serverDZ-cfg-template.json)

---

## 💻 Common Code Snippets

### Spawn an Item
```cpp
vector pos = "7500 0 5500";
pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
EntityAI item = GetGame().CreateObject("AKM", pos);
```

### Give Player Health
```cpp
player.AddHealth("", "Health", 25);
player.AddHealth("", "Blood", 50);
player.GetStatEnergy().Add(100);
player.GetStatWater().Add(50);
```

### Send Player Message
```cpp
player.MessageStatus("Your message here");
player.MessageAction("Action message");
player.MessageImportant("Important message");
```

### Get Player Position
```cpp
vector playerPos = player.GetPosition();
Print("Player at: " + playerPos.ToString());
```

**More Examples**: [examples/scripts/](examples/scripts/)

---

## 🛠️ Useful Tools

### Validate types.xml
```bash
python tools/validators/types-validator.py path/to/types.xml
```

### Check Documentation Links
```bash
python tools/validators/link-checker.py
```

### Generate New Mod
```bash
python tools/generators/config-generator.py ModName "Author" ./output
```

**All Tools**: [tools/](tools/)

---

## 🎮 Server Management

### Start Server (Linux)
```bash
./DayZServer -config=serverDZ.cfg -port=2302 \
  -profiles=profiles -mod=@CF;@YourMod
```

**Script Template**: [server-start-script.sh](templates/config-templates/server-start-script.sh)

### Check Server Status
```bash
ps aux | grep DayZServer
```

### View Server Logs
```bash
tail -f server_console.log
```

---

## 📊 Common Values

### Loot Tiers
- `Tier1` - Common items
- `Tier2` - Uncommon items
- `Tier3` - Rare items
- `Tier4` - Very rare items

### Usage Types (Spawn Locations)
- `Military` - Military buildings
- `Police` - Police stations
- `Town` - Urban areas
- `Village` - Small settlements
- `Farm` - Agricultural buildings
- `Hunting` - Hunting locations
- `Industrial` - Factories

### Item Categories
- `weapons` - Firearms, melee
- `ammunition` - Bullets, magazines
- `clothes` - Clothing items
- `food` - Food and drinks
- `tools` - Tools and equipment
- `containers` - Storage items

---

## 🔍 Troubleshooting Quick Fixes

### Server Won't Start
1. Check server logs: `server_console.log`
2. Verify config syntax: Use validator
3. Check mod load order
4. Ensure ports are open

### Mod Not Loading
1. Check `-mod=` parameter format
2. Verify mod signature
3. Check console for errors
4. Ensure all dependencies loaded

### Items Not Spawning
1. Check `nominal` and `min` values
2. Verify `usage` tags exist
3. Check `value` (tier) tags
4. Restart economy: delete `storage_` files

### BattlEye Kicks
1. Check BattlEye filters
2. Add exceptions if needed
3. Verify mod signatures
4. Check `verifySignatures` setting

**Full Guide**: [Troubleshooting](docs/troubleshooting/README.md)

---

## 🎯 Workflow Examples

### Creating a Custom Item
1. Add to config.cpp (weapon/clothing def)
2. Add to types.xml (loot economy)
3. Create script class if needed
4. Build and test

### Setting Up Traders
1. Install trader mod (Expansion/TraderPlus)
2. Configure trader config.json
3. Set X,Y,Z coordinates
4. Add item prices
5. Restart server

### Adding Discord Integration
1. Set up webhook URL
2. Install notification mod
3. Configure events to log
4. Test notifications

**Detailed Guides**: [Documentation](docs/)

---

## 📚 Additional Resources

### Documentation
- [Complete Ecosystem](docs/ECOSYSTEM.md) - All tools and services
- [Issue Index](docs/ISSUE_INDEX.md) - Problem solutions
- [Verification Report](docs/VERIFICATION_REPORT.md) - Tested solutions

### Templates
- [Configuration Templates](templates/config-templates/)
- [Script Templates](templates/script-templates/)

### Examples
- [Working Code Examples](examples/scripts/)
- [Killfeed Implementations](examples/killfeed/)

### Tools
- [Validators](tools/validators/) - Check your configs
- [Generators](tools/generators/) - Create new mods

---

## 🚀 Quick Start Paths

### "I Want to Run a Server"
1. Choose hosting: [Server Hosting Guide](docs/server-hosting/)
2. Configure: Use [serverDZ.cfg template](templates/config-templates/serverDZ-cfg-template.json)
3. Add mods: See [Popular Mods](docs/popular-mods/)
4. Setup traders: [Online Traders Guide](docs/json-configs/online-traders.md)

### "I Want to Create a Mod"
1. Setup tools: [Tools Setup](docs/getting-started/tools-setup.md)
2. Generate structure: Use [config-generator.py](tools/generators/config-generator.py)
3. Use templates: [Script Templates](templates/script-templates/)
4. Reference examples: [Code Examples](examples/scripts/)

### "I Have a Problem"
1. Search: [Issue Index](docs/ISSUE_INDEX.md)
2. Browse: [Troubleshooting Guide](docs/troubleshooting/README.md)
3. Check: [Verification Report](docs/VERIFICATION_REPORT.md)

---

## 💡 Pro Tips

- ✅ Always validate configs before deployment
- ✅ Test mods on local server first
- ✅ Keep backups of working configurations
- ✅ Use version control for your mods
- ✅ Check logs when something doesn't work
- ✅ Join DayZ Discord communities for help

---

**Last Updated**: January 2026  
**Full Documentation**: [Main README](README.md)  
**Contribute**: [Contributing Guide](CONTRIBUTING.md)

*Bookmark this page for quick reference!*
