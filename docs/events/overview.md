# DayZ Events System Overview

## Overview

The DayZ Events System is the core mechanism that controls dynamic world events on your server, including helicopter crashes, contaminated zones, vehicle spawns, animal herds, and custom scripted encounters. Events add variety, unpredictability, and strategic value to the DayZ experience by spawning unique loot and scenarios at specific times and locations.

## Table of Contents
- [Introduction](#introduction)
- [How Events Work](#how-events-work)
- [Event Types](#event-types)
- [Configuration Files](#configuration-files)
- [Key Parameters](#key-parameters)
- [Event Lifecycle](#event-lifecycle)
- [Examples](#examples)
- [Best Practices](#best-practices)
- [Troubleshooting](#troubleshooting)
- [Advanced Topics](#advanced-topics)
- [Resources](#resources)

## Introduction

### What Are Events?

Events in DayZ are server-controlled dynamic spawns managed by the Central Economy system. Unlike regular loot that spawns in buildings, events:
- Appear at specific map locations (fixed or random)
- Have defined lifetimes (how long they persist)
- Can spawn vehicles, loot containers, or special objects
- Are controlled by proximity rules (distance from players)
- Have configurable spawn rates and quantities

### Why Use Events?

Events provide several key benefits:
- **High-value loot spawns**: Military gear at helicopter crashes
- **Unique gameplay moments**: Discovering a contaminated zone
- **Player interaction hotspots**: Multiple players converging on crash sites
- **Server economy balance**: Controlling rare item distribution
- **Dynamic world feel**: Keeps the game unpredictable and engaging

### Prerequisites

- DayZ Server with file access (FTP, local, or hosting panel)
- Text editor (VS Code, Notepad++, or XML editor)
- Basic XML syntax understanding
- Access to server mission files (mpmissions folder)

## How Events Work

### Central Economy Management

The DayZ server's Central Economy (CE) continuously monitors all active events:

1. **Check Phase**: Every few minutes, CE checks how many instances of each event are active
2. **Spawn Phase**: If the count is below `nominal`, CE attempts to spawn new instances
3. **Validation Phase**: Ensures spawn follows proximity rules (safe radius, player distance)
4. **Lifetime Phase**: After `lifetime` seconds, event objects are marked for cleanup
5. **Cleanup Phase**: Removes expired events within `cleanupradius`
6. **Restock Phase**: After `restock` seconds, a new event can spawn

### Spawn Logic Flow

```
Server Start
    ↓
Check Active Events < Nominal?
    ↓ (Yes)
Find Valid Spawn Location
    ↓
Check saferadius (no other events nearby)
    ↓
Check distanceradius (no players nearby)
    ↓
Spawn Event Objects
    ↓
Wait for lifetime to expire
    ↓
Cleanup Event
    ↓
Wait restock period → Loop
```

## Event Types

### Static Events
**Fixed spawn locations** defined in `cfgeventspawns.xml`
- Helicopter crashes at specific coordinates
- Vehicle spawns at designated parking areas
- Contaminated zones at fixed locations
- Police car events at checkpoints

**Configuration**: `init_random="0"` and `position="fixed"`

### Dynamic Events
**Random spawn locations** within allowed areas
- Random helicopter crashes across the map
- Dynamic animal herds
- Randomly placed loot drops
- Wandering AI encounters (with mods)

**Configuration**: `init_random="1"` and appropriate position logic

### Timed Events
**Scheduled or recurring events** (requires custom scripting)
- Airdrop events at specific times
- Seasonal events
- Weekly special spawns
- Custom scripted scenarios

## Configuration Files

### Primary Files

#### events.xml
**Location**: `mpmissions/dayzOffline.chernarusplus/db/events.xml`

**Purpose**: Defines all event types, their spawn rules, quantities, and behavior

**Key Content**:
- Event definitions
- Nominal/min/max counts
- Lifetime and restock timers
- Proximity and cleanup rules
- Flags and activation status

#### cfgeventspawns.xml
**Location**: `mpmissions/dayzOffline.chernarusplus/db/cfgeventspawns.xml`

**Purpose**: Defines exact coordinates for fixed event spawns

**Key Content**:
- X, Z map coordinates
- Rotation angle (a)
- Event name references

#### cfgeventgroups.xml
**Location**: `mpmissions/dayzOffline.chernarusplus/db/cfgeventgroups.xml`

**Purpose**: Defines groups of objects that spawn together as part of an event

**Key Content**:
- Object classnames
- Quantity ranges
- Loot definitions

### Secondary Files

- **cfgspawnabletypes.xml**: Defines attachments and cargo for event vehicles
- **cfgeconomycore.xml**: References custom event files
- **mapgroupproto.xml**: Advanced event grouping and clustering

## Key Parameters

### Quantity Control

| Parameter | Type | Description | Example |
|-----------|------|-------------|---------|
| **nominal** | integer | Target number of active instances | `3` (aim for 3 active crashes) |
| **min** | integer | Minimum guaranteed instances | `1` (always at least 1) |
| **max** | integer | Maximum allowed instances | `5` (never more than 5) |

### Timing Control

| Parameter | Type | Description | Example |
|-----------|------|-------------|---------|
| **lifetime** | integer | Duration in seconds event persists | `1800` (30 minutes) |
| **restock** | integer | Cooldown before new spawn (seconds) | `0` (immediate) or `3600` (1 hour) |

### Proximity Control

| Parameter | Type | Description | Example |
|-----------|------|-------------|---------|
| **saferadius** | integer | Min distance between events (meters) | `1000` (1km apart) |
| **distanceradius** | integer | Min distance from players to spawn | `500` (spawn 500m+ from players) |
| **cleanupradius** | integer | Area cleaned when event ends | `200` (cleanup 200m radius) |

### Flags

| Flag | Values | Description |
|------|--------|-------------|
| **deletable** | 0 or 1 | Can CE delete this during cleanup? (1=yes) |
| **init_random** | 0 or 1 | Use random positions? (1=yes, 0=fixed) |
| **remove_damaged** | 0 or 1 | Auto-remove damaged objects? (1=yes) |

### Other Parameters

| Parameter | Values | Description |
|-----------|--------|-------------|
| **position** | fixed/random/player | Spawn location type |
| **limit** | child/mixed/custom | Spawn logic enforcement |
| **active** | 0 or 1 | Is event enabled? (1=yes) |

## Event Lifecycle

### Phase 1: Initialization (Server Start)
- Server reads events.xml
- Loads event spawn locations from cfgeventspawns.xml
- Creates event manager instances
- Spawns initial events to reach nominal count

### Phase 2: Active Monitoring (Runtime)
- CE continuously monitors active event counts
- Checks if any events have expired (lifetime reached)
- Validates proximity rules for new spawns
- Maintains nominal/min/max constraints

### Phase 3: Spawning
```
Is event count < nominal?
    ↓ YES
Select spawn location (fixed or random)
    ↓
Check saferadius (distance from other events)
    ↓ VALID
Check distanceradius (distance from players)
    ↓ VALID
Spawn event objects and loot
    ↓
Mark spawn time
```

### Phase 4: Lifetime
- Event exists on map for `lifetime` seconds
- Players can interact with event objects
- Loot can be taken
- Objects can be damaged/destroyed

### Phase 5: Cleanup
- After lifetime expires, event is marked for cleanup
- All objects within `cleanupradius` are removed
- Event count decrements
- Restock timer begins

### Phase 6: Restock Delay
- Wait `restock` seconds before allowing new spawn
- If restock=0, immediate respawn is allowed
- If restock>0, creates artificial rarity

## Examples

### Basic Helicopter Crash Event
```xml
<event name="StaticHeliCrash">
    <nominal>3</nominal>           <!-- 3 active crashes at once -->
    <min>1</min>                   <!-- At least 1 always -->
    <max>5</max>                   <!-- Never more than 5 -->
    <lifetime>1800</lifetime>      <!-- Lasts 30 minutes -->
    <restock>0</restock>           <!-- Immediate respawn -->
    <saferadius>1000</saferadius>  <!-- 1km between crashes -->
    <distanceradius>500</distanceradius> <!-- 500m from players -->
    <cleanupradius>200</cleanupradius>   <!-- Cleanup 200m area -->
    <flags deletable="0" init_random="1" remove_damaged="1"/>
    <position>fixed</position>
    <limit>child</limit>
    <active>1</active>
</event>
```

### Police Car Spawn Event
```xml
<event name="VehiclePoliceOffroad">
    <nominal>1</nominal>           <!-- 1 police car -->
    <min>1</min>
    <max>1</max>
    <lifetime>3600</lifetime>      <!-- Lasts 1 hour -->
    <restock>0</restock>
    <saferadius>10</saferadius>
    <distanceradius>3</distanceradius>
    <cleanupradius>250</cleanupradius>
    <flags deletable="0" init_random="0" remove_damaged="1"/>
    <position>fixed</position>
    <limit>child</limit>
    <active>1</active>
    <children>
        <child type="CivilianSedan_Police" min="1" max="1"/>
    </children>
</event>
```

### Contaminated Zone (Modded)
```xml
<event name="ContaminatedArea_Static">
    <nominal>2</nominal>           <!-- 2 contaminated zones -->
    <min>2</min>
    <max>2</max>
    <lifetime>2700</lifetime>      <!-- Lasts 45 minutes -->
    <restock>900</restock>         <!-- 15 min restock -->
    <saferadius>2000</saferadius>  <!-- 2km apart -->
    <distanceradius>100</distanceradius>
    <cleanupradius>150</cleanupradius>
    <flags deletable="0" init_random="0" remove_damaged="0"/>
    <position>fixed</position>
    <limit>custom</limit>
    <active>1</active>
</event>
```

## Best Practices

### Event Balancing
1. **Don't over-spawn**: Too many events reduces their value
2. **Use appropriate lifetime**: 30-60 minutes is typical
3. **Space events apart**: Use adequate saferadius (1000m+)
4. **Consider server population**: More players = can support more events

### Performance Optimization
1. **Limit max instances**: High max values can impact performance
2. **Use cleanup radius wisely**: Large areas = more objects to check
3. **Set reasonable lifetimes**: Very long lifetimes = more persistent objects
4. **Test on your hardware**: Different servers have different limits

### Gameplay Balance
1. **High-tier loot should be rare**: Use low nominal values (1-3)
2. **Spread spawn locations**: Don't cluster all events in one area
3. **Mix event types**: Variety keeps gameplay interesting
4. **Consider travel times**: Events too far apart may be ignored

### Configuration Tips
1. **Backup before editing**: Always keep original files
2. **Validate XML syntax**: Use XML validator before uploading
3. **Test on local server**: Verify changes work before going live
4. **Document changes**: Comment your modifications
5. **Use version control**: Track what changes when

## Troubleshooting

### Events Not Spawning

**Problem**: Events configured but not appearing on map

**Solutions**:
1. Check `<active>1</active>` is set
2. Verify event name matches in events.xml and cfgeventspawns.xml
3. Ensure coordinates are valid (within map bounds)
4. Check server logs for CE errors
5. Delete `storage_1` folder to reset economy (careful - wipes bases!)

### Too Many/Few Events

**Problem**: Event spawn count doesn't match nominal

**Solutions**:
1. Verify min/max values allow nominal to be reached
2. Check if proximity rules are too strict (saferadius, distanceradius)
3. Ensure enough valid spawn locations exist
4. Monitor server console for spawn failures
5. Increase spawn location options in cfgeventspawns.xml

### Events Not Cleaning Up

**Problem**: Old events persist indefinitely

**Solutions**:
1. Check `lifetime` is set (not 0)
2. Verify `cleanupradius` is adequate
3. Ensure server CE is functioning (check logs)
4. Set `deletable="1"` if appropriate
5. Restart server to force cleanup cycle

### Player Proximity Issues

**Problem**: Events spawning near/on players

**Solutions**:
1. Increase `distanceradius` value
2. Check for valid spawn locations away from common paths
3. Verify cfgeventspawns.xml coordinates
4. Consider map hot-spots and adjust accordingly

### XML Syntax Errors

**Problem**: Server won't start or CE fails to load

**Solutions**:
1. Validate XML files (use online validator)
2. Check for unclosed tags: `<event>` must have `</event>`
3. Verify attribute quotes: `name="value"` not `name=value`
4. Look for special characters that need escaping
5. Check server console for specific error line numbers

## Advanced Topics

### Custom Event Creation

To create entirely new events:

1. **Define event in events.xml**:
   ```xml
   <event name="MyCustomEvent">
       <!-- parameters -->
   </event>
   ```

2. **Add spawn locations in cfgeventspawns.xml**:
   ```xml
   <event name="MyCustomEvent">
       <pos x="5000" z="7500" a="0"/>
       <pos x="5500" z="8000" a="90"/>
   </event>
   ```

3. **Define event group in cfgeventgroups.xml** (if needed):
   ```xml
   <group name="MyCustomEvent_Group">
       <item name="ObjectClassname" chance="1.0"/>
   </group>
   ```

4. **Reference in cfgeconomycore.xml**:
   ```xml
   <ce folder="custom">
       <file name="events_Custom.xml" type="events"/>
   </ce>
   ```

### Multi-Object Events

Events that spawn multiple objects together:

```xml
<event name="MilitaryConvoy">
    <nominal>1</nominal>
    <children>
        <child type="OffroadHatchback" min="1" max="1"/>
        <child type="Barrel_Yellow" min="2" max="4"/>
        <child type="Military_Box" min="1" max="2"/>
    </children>
</event>
```

### Scripted Events

For advanced control, use EnScript to:
- Spawn events based on player actions
- Create timed events
- Add special effects (smoke, sounds)
- Custom cleanup logic
- Dynamic loot tables

Example hook:
```cpp
modded class MissionServer
{
    void SpawnCustomEvent(vector position)
    {
        // Spawn logic here
        GetGame().CreateObject("HeliCrashEvent", position);
    }
}
```

### Event Sequencing

Create event chains where one event triggers another:
- Helicrash spawns → Smoke effect → Infected horde
- Police car spawn → Roadblock objects → Zombie spawn
- Airdrop → Parachute → Loot container

### Geographic Event Zones

Divide map into zones with different event rules:
- Coastal zone: More police cars, low-tier events
- Central zone: Balanced mix
- Military zone: Helicrashes, high-tier
- Northwest: Rare, valuable events

## Resources

### Official Documentation
- [DayZ Wiki - Events](https://community.bistudio.com/wiki/DayZ:Central_Economy)
- [Bohemia Forums - Events Discussion](https://forums.dayz.com/)

### Community Tools
- **DayZ File Toolbox**: Visual event editor and validator
  - URL: https://www.dayzfiletoolbox.com/events-hub
- **DZConfig Wiki**: Comprehensive event parameter reference
  - URL: https://dzconfig.com/wiki/events
- **Legion Killfeed**: Event configuration guide
  - URL: https://killfeed.co/dayz/

### Video Tutorials
- Scalespeeder Gaming: Event setup walkthroughs
- WOBO: Event mechanics and optimization
- M1NDR: Custom event scripting

### Example Files
- [Basic Events.xml](../../templates/config-templates/)
- [Custom Event Template](../../examples/)
- [Event Group Examples](../../examples/)

### Related Documentation
- [Static Events Guide](./static-events.md)
- [Dynamic Events Guide](./dynamic-events.md)
- [Helicopter Crash Events](./helicrash.md)
- [Police Car Events](./police-car.md)
- [Custom Events Guide](./custom-events.md)
- [types.xml Reference](../xml-configs/types-xml.md)
- [MapGroupPos System](../spawns/mapgrouppos-system.md)

## Summary

The DayZ Events System provides powerful tools for server administrators to create dynamic, engaging gameplay experiences. By understanding the configuration parameters, spawn logic, and lifecycle management, you can:

- Control high-value loot distribution
- Create hotspots for player interaction
- Balance server economy
- Add variety and unpredictability
- Customize server identity

**Key Takeaways**:
1. Events are managed by Central Economy
2. Configuration happens in events.xml and cfgeventspawns.xml
3. Proximity rules prevent clustering and exploits
4. Lifetime and restock control rarity
5. Proper balancing enhances gameplay

**Next Steps**:
1. Read specific event guides (helicrash, police car, etc.)
2. Review your server's current events.xml
3. Plan event distribution across your map
4. Test changes on local/test server
5. Monitor player feedback and adjust

---

**Last Updated**: January 2026  
**DayZ Version**: 1.26+  
**Applies To**: PC, Console (limited on console platforms)

For questions or contributions, see [CONTRIBUTING.md](../../CONTRIBUTING.md)
More complex example with additional features:
```xml
<!-- Advanced example -->
```

### Real-World Example
Practical implementation from actual use:
```xml
<!-- Real-world example -->
```

## Best Practices
### Coding Standards
- Follow DayZ coding conventions
- Use meaningful variable names
- Add comments for complex logic
- Keep code modular and reusable

### Performance
- Optimize for multiplayer environments
- Minimize network traffic
- Use efficient algorithms
- Profile and benchmark performance

### Compatibility
- Test with popular mods
- Ensure BattlEye compatibility
- Check for conflicts
- Document dependencies

### Maintenance
- Version your changes
- Document modifications
- Keep backups
- Test after updates

## Troubleshooting
### Common Issues
| Issue | Cause | Solution |
|-------|-------|----------|
| Issue 1 | Common cause | Step-by-step solution |
| Issue 2 | Another cause | Detailed fix |
| Issue 3 | Third cause | Resolution steps |

### Debugging Tips
- Enable verbose logging
- Check server/client logs
- Use Workbench debugger (for scripts)
- Test in isolation
- Verify file paths and permissions

### Getting Help
- Check [Issue Index](../ISSUE_INDEX.md)
- Review [Troubleshooting Guide](../troubleshooting/README.md)
- Visit [Community Resources](../ECOSYSTEM.md#community-platforms)
- Ask in Discord servers

## Advanced Topics
### Optimization Techniques
Advanced optimization strategies for experienced users.

### Integration with Other Systems
How this system integrates with other DayZ features.

### Customization Options
Advanced customization possibilities.

### Performance Tuning
Fine-tuning for optimal performance.

## Resources
### Official Documentation
- [Bohemia Interactive Wiki](https://community.bistudio.com/wiki/DayZ)
- [DayZ Tools Documentation](https://community.bistudio.com/wiki/DayZ:Modding_Basics)
- [Official Forums](https://forums.dayz.com/)

### Community Resources
- [Complete Ecosystem](../ECOSYSTEM.md) - All DayZ tools and services
- [Issue Index](../ISSUE_INDEX.md) - Problem lookup
- [Quick Start Guide](../QUICKSTART.md) - Getting started

### Related Guides
- Related documentation in this library
- Cross-referenced topics
- Additional reading

### External Tools
- Relevant tools from [ECOSYSTEM.md](../ECOSYSTEM.md)
- Third-party utilities
- Community resources

### Video Tutorials
- YouTube channels covering this topic
- Step-by-step video guides
- Community tutorials

## Further Learning
### Next Steps
1. Explore related documentation
2. Try the examples provided
3. Join community discussions
4. Contribute improvements

### Advanced Reading
- Advanced topics in related areas
- Performance optimization guides
- Architecture and design patterns

---

**Status**: 📝 Documentation in Progress  
**Last Updated**: January 2026  
**Contribution**: This is a placeholder document. Community contributions are welcome! See [CONTRIBUTING.md](../../CONTRIBUTING.md)

**Note**: This document is part of the comprehensive DayZ Library. Content will be expanded based on community needs and contributions.
