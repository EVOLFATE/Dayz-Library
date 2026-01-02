# Debugging Techniques

## Overview
Comprehensive guide to debugging DayZ mods and server issues.

## Workbench Debugger
### Setup
1. Launch DayZ with -filePatching parameter
2. Attach Workbench debugger
3. Set breakpoints in your scripts

### Debugging Features
- **Breakpoints**: Pause execution at specific lines
- **Watch Variables**: Monitor variable values
- **Call Stack**: See function call hierarchy
- **Step Through**: Execute line-by-line

## Logging
### Adding Log Statements
```cpp
void MyFunction()
{
    Print("Debug: Function started");
    Print("Value: " + myVariable);
}
```

### Log Locations
- **Client**: `DayZ/profiles/`
- **Server**: `Server/profiles/`
- **Script Logs**: Look for `script.log`

## Common Debugging Scenarios
### Null Reference Errors
- Check object existence before use
- Use `if (obj)` checks
- Log object states

### Network Synchronization Issues
- Log on both client and server
- Check RPC calls
- Verify data transmission

## Performance Debugging
### Profiling
- Use `GetGame().GetProfiler()` ##
- Measure function execution time
- Identify bottlenecks

### Memory Leaks
- Track object creation/deletion
- Use weak references where appropriate
- Monitor memory usage over time

## Tools
- **DayZ Workbench**: Official debugger
- **Script Logging**: Print statements
- **Server Logs**: Check for errors
- **Client Logs**: Check client-side issues

## Resources
- [Workbench Guide](../getting-started/workbench-guide.md)
- [Scripting Errors](../troubleshooting/scripting-errors.md)
