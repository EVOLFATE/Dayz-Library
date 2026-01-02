# Script Templates

## Overview
This directory contains EnFusion script templates for common DayZ modding tasks.

## Available Templates

### 1. custom-item-class.c
Complete template for creating custom items with:
- **Custom consumables** with health/status effects
- **Custom weapons** with special properties
- **Custom clothing** with temperature/protection stats
- **Custom containers** with item restrictions
- **Custom tools** with durability
- **Vehicle parts** with engine hooks
- **Utility functions** for common tasks

### 2. mission-init-template.c
Mission initialization template featuring:
- **Weather system** configuration
- **Custom mission class** structure
- **Player connection/disconnection** handlers
- **Player death** handling
- **Custom starting loadout** system
- **Event hooks** for killfeed and logging

## How to Use

### For Custom Items:
```cpp
// 1. Copy the relevant class from custom-item-class.c
// 2. Rename the class to your item name
// 3. Modify behavior as needed
// 4. Place in your mod's scripts directory

class MyCustomFood : Edible_Base
{
    override void OnConsume(float amount, PlayerBase consumer)
    {
        super.OnConsume(amount, consumer);
        // Add custom effects
        consumer.AddHealth("", "Health", 50);
    }
}
```

### For Mission Setup:
```cpp
// 1. Copy mission-init-template.c to your mission folder
// 2. Rename CustomMission to your mission name
// 3. Customize weather, spawn loadout, etc.
// 4. Place in mission's init.c
```

## Template Features

All templates include:
- ✅ **Detailed comments** explaining each section
- ✅ **Working examples** you can copy directly
- ✅ **Best practices** from the DayZ community
- ✅ **Common use cases** covered
- ✅ **Error handling** patterns

## Quick Reference

### Common Modifications:

**Add health to player:**
```cpp
player.AddHealth("", "Health", 25);
player.AddHealth("", "Blood", 50);
```

**Change item stats:**
```cpp
player.GetStatEnergy().Add(100);
player.GetStatWater().Add(50);
```

**Spawn items:**
```cpp
EntityAI item = GetGame().CreateObject("ItemType", position);
```

## Examples Directory

For complete working examples, see:
- [examples/scripts/](../../examples/scripts/) - Working code samples
- [examples/killfeed/](../../examples/killfeed/) - Killfeed implementations

## Contributing
Have useful script templates? We'd love to add them!
1. Ensure code is well-commented
2. Test thoroughly
3. Review [CONTRIBUTING.md](../../CONTRIBUTING.md)
4. Submit a pull request

---

**Status**: ✅ Active - 2 Templates Available  
**Last Updated**: January 2026  
**Contributions Welcome**: Yes!
