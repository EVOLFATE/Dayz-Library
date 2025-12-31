# Killfeed Basics

## What is a Killfeed?

A killfeed (also known as kill log or death feed) is a UI element that displays information about player deaths, kills, and other combat-related events in real-time. It's a crucial feature for PvP servers and helps players understand the combat dynamics of the server.

## Core Concepts

### 1. Kill Events
Kill events occur when a player dies and can include:
- **Killer**: The player who caused the death
- **Victim**: The player who died
- **Weapon**: The weapon used to cause the death
- **Distance**: Distance between killer and victim
- **Timestamp**: When the death occurred
- **Additional Context**: Headshot, vehicle kill, fall damage, etc.

### 2. Killfeed Types

#### Basic Killfeed
```
Player1 killed Player2
Player3 killed Player4 with M4A1
```

#### Advanced Killfeed
```
[15:30] Player1 [350m] → Player2 (Headshot) [M4A1]
[15:31] Player3 → Player4 [SVD] 
[15:32] Player5 died (Zombie)
```

#### Icon-Based Killfeed
```
🎯 Player1 ━━━ 350m ━━━► Player2 💀 [Headshot]
⚔️ Player3 ━━━━━━━━━► Player4 [SVD]
```

### 3. Information Hierarchy

Priority of information to display:
1. **Essential**: Killer name, Victim name
2. **Important**: Weapon used
3. **Contextual**: Distance, headshot indicator
4. **Optional**: Faction, location, timestamp

## Key Features

### Display Duration
- **Standard**: 5-10 seconds per message
- **Fade-out**: 1-2 second fade animation
- **Maximum entries**: 5-10 visible messages

### Positioning
- **Top-right**: Most common position
- **Top-center**: Alternative for central focus
- **Custom**: Server-specific positioning

### Styling
- **Colors**: Faction-based or role-based colors
- **Icons**: Weapon icons, kill type icons
- **Animations**: Slide-in, fade-out effects

## Implementation Overview

### Client-Side Components
```javascript
// Simplified structure
class KillfeedUI extends UIScriptedMenu
{
    protected Widget m_KillfeedPanel;
    protected ref array<Widget> m_Messages;
    
    void AddMessage(string killer, string victim, string weapon)
    {
        // Create and display message
    }
}
```

### Server-Side Components
```javascript
// Event broadcasting
class KillfeedManager
{
    void BroadcastKillEvent(PlayerBase killer, PlayerBase victim, string weapon)
    {
        // Send to all clients
        GetRPCManager().SendRPC(...);
    }
}
```

## Best Practices

### 1. Performance
- Limit concurrent messages (5-10 max)
- Use object pooling for message widgets
- Efficient memory management

### 2. Network Efficiency
- Batch multiple kills if possible
- Compress data sent over network
- Use player IDs instead of full names

### 3. User Experience
- Clear, readable fonts
- High contrast colors
- Smooth animations
- Configurable settings

### 4. Privacy Considerations
- Option to hide killfeed
- Anonymous mode options
- Distance-based visibility

## Common Use Cases

### 1. PvP Servers
- Display all kills
- Show weapon and distance
- Highlight special kills (headshots, long-range)

### 2. Role-Play Servers
- Limited information display
- Optional anonymous kills
- Faction-specific colors

### 3. PvE Servers
- Show AI kills
- Environmental deaths
- Team-based information

## Technical Considerations

### Network Synchronization
- Events must be server-authoritative
- Client prediction for local player
- Lag compensation for accurate timing

### Anti-Cheat Integration
- Validate all kill events server-side
- Prevent false kill messages
- Log suspicious patterns

### Mod Compatibility
- Standard naming conventions
- Event system integration
- Configuration file support

## Next Steps

- [Killfeed Architecture](architecture.md) - Understand the technical structure
- [Implementation Guide](implementation.md) - Build your first killfeed
- [Examples](examples.md) - See complete implementations

## References

- [DayZ Player Events](../scripting/event-system.md)
- [UI Development](../scripting/enscript-fundamentals.md)
- [Network Synchronization](../scripting/network-sync.md)
