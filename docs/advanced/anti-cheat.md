# Anti-Cheat Compatibility

## Overview
Guide to ensuring your mods are compatible with BattlEye and other anti-cheat systems used in DayZ.

## BattlEye Integration
### What is BattlEye?
- Anti-cheat system used by DayZ
- Monitors game files and memory
- Can kick/ban players for violations

### Making Mods BattlEye-Compatible
1. **Avoid Memory Manipulation**
   - Don't use memory injection
   - Avoid hooking into game functions
   - Use official modding APIs only

2. **Script Restrictions**
   - Some script functions are filtered
   - Configure scripts.txt for whitelisting
   - Test thoroughly with BattlEye enabled

## Common Issues
See [BattlEye Issues](../troubleshooting/battleye-issues.md) for troubleshooting.

## Best Practices
- Always test with BattlEye enabled
- Document required BattlEye filter changes
- Provide scripts.txt configuration
- Avoid triggering false positives

## Resources
- [BattlEye Official](https://www.battleye.com/)
- [DayZ BattlEye Filters](https://community.bistudio.com/wiki/BattlEye_Filters)
