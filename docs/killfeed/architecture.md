# Killfeed Architecture

## System Overview

The killfeed system consists of three main layers working together:

```
┌─────────────────────────────────────────────────────────┐
│                     CLIENT LAYER                         │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐  │
│  │   UI Widget   │  │  Animation   │  │    Display   │  │
│  │   Manager     │  │   Controller │  │    Manager   │  │
│  └──────────────┘  └──────────────┘  └──────────────┘  │
└─────────────────────────────────────────────────────────┘
                            ▲
                            │ RPC
                            ▼
┌─────────────────────────────────────────────────────────┐
│                    NETWORK LAYER                         │
│  ┌──────────────────────────────────────────────────┐   │
│  │           RPC Manager & Serialization             │   │
│  └──────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────┘
                            ▲
                            │ Events
                            ▼
┌─────────────────────────────────────────────────────────┐
│                     SERVER LAYER                         │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐  │
│  │    Event      │  │  Validation  │  │   Database   │  │
│  │   Collector   │  │    Layer     │  │    Logger    │  │
│  └──────────────┘  └──────────────┘  └──────────────┘  │
└─────────────────────────────────────────────────────────┘
```

## Component Breakdown

### 1. Server Layer

#### Event Collector
**Purpose**: Captures all death/kill events in the game

**Key Responsibilities**:
- Hook into player death events
- Extract killer information
- Determine cause of death
- Calculate additional metrics (distance, headshot, etc.)

**Implementation Pattern**:
```javascript
modded class PlayerBase
{
    override void EEKilled(Object killer)
    {
        super.EEKilled(killer);
        
        // Collect kill event data
        KillfeedEventData event_data = new KillfeedEventData();
        event_data.victim_id = GetIdentity().GetId();
        event_data.victim_name = GetIdentity().GetName();
        
        if (killer && killer.IsPlayer())
        {
            event_data.killer_id = PlayerBase.Cast(killer).GetIdentity().GetId();
            event_data.killer_name = PlayerBase.Cast(killer).GetIdentity().GetName();
            event_data.weapon = GetWeaponUsed();
            event_data.distance = CalculateDistance(killer);
            event_data.is_headshot = CheckHeadshot();
        }
        
        // Send to killfeed manager
        GetKillfeedManager().ProcessKillEvent(event_data);
    }
}
```

#### Validation Layer
**Purpose**: Ensure kill events are legitimate

**Checks Performed**:
- Verify killer and victim exist
- Validate weapon ownership
- Check for impossible distances
- Detect suspicious patterns
- Rate limiting

**Example Validation**:
```javascript
class KillfeedValidator
{
    bool ValidateKillEvent(KillfeedEventData data)
    {
        // Distance validation
        if (data.distance > MAX_WEAPON_RANGE)
            return false;
            
        // Time validation
        if (GetGame().GetTime() - data.timestamp > MAX_EVENT_AGE)
            return false;
            
        // Player validation
        if (!IsValidPlayer(data.killer_id) || !IsValidPlayer(data.victim_id))
            return false;
            
        return true;
    }
}
```

#### Database Logger
**Purpose**: Record kill events for statistics and analytics

**Stored Data**:
- Kill timestamp
- Player identifiers
- Weapon information
- Location coordinates
- Server population

### 2. Network Layer

#### RPC Manager
**Purpose**: Efficiently transmit kill events to clients

**Optimization Strategies**:
- **Batching**: Group multiple kills into single packets
- **Compression**: Minimize data size
- **Prioritization**: Send to relevant players first

**RPC Structure**:
```javascript
class KillfeedRPC
{
    static const int RPC_KILLFEED_EVENT = 12345;
    
    void SendKillEvent(PlayerIdentity target, KillfeedEventData data)
    {
        auto ctx = new Param4<string, string, string, int>(
            data.killer_name,
            data.victim_name,
            data.weapon,
            data.distance
        );
        
        GetGame().RPCSingleParam(
            null,
            RPC_KILLFEED_EVENT,
            ctx,
            true,
            target
        );
    }
    
    void BroadcastKillEvent(KillfeedEventData data)
    {
        // Send to all connected players
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        
        foreach (Man player : players)
        {
            if (player && player.GetIdentity())
            {
                SendKillEvent(player.GetIdentity(), data);
            }
        }
    }
}
```

### 3. Client Layer

#### UI Widget Manager
**Purpose**: Create and manage UI elements for killfeed messages

**Widget Hierarchy**:
```
KillfeedPanel (Parent)
  └── MessageContainer (Scrollable)
      ├── Message1 (TextWidget + Icons)
      ├── Message2 (TextWidget + Icons)
      ├── Message3 (TextWidget + Icons)
      └── ... (Up to MAX_MESSAGES)
```

**Widget Creation**:
```javascript
class KillfeedWidgetManager
{
    protected Widget m_Root;
    protected ref array<KillfeedMessage> m_ActiveMessages;
    protected const int MAX_MESSAGES = 10;
    
    Widget CreateMessageWidget(KillfeedEventData data)
    {
        Widget msg = GetGame().GetWorkspace().CreateWidgets(
            "YourMod/GUI/layouts/killfeed_message.layout",
            m_Root
        );
        
        TextWidget killer = TextWidget.Cast(msg.FindAnyWidget("KillerName"));
        TextWidget victim = TextWidget.Cast(msg.FindAnyWidget("VictimName"));
        TextWidget weapon = TextWidget.Cast(msg.FindAnyWidget("WeaponName"));
        
        killer.SetText(data.killer_name);
        victim.SetText(data.victim_name);
        weapon.SetText(data.weapon);
        
        return msg;
    }
}
```

#### Animation Controller
**Purpose**: Handle smooth animations for messages

**Animation Types**:
1. **Slide-In**: New messages slide in from the right
2. **Fade-Out**: Old messages fade out after duration
3. **Stack-Shift**: Messages move up when new ones appear

**Animation Implementation**:
```javascript
class KillfeedAnimator
{
    protected const float SLIDE_DURATION = 0.3;
    protected const float FADE_DURATION = 1.0;
    protected const float MESSAGE_LIFETIME = 8.0;
    
    void AnimateSlideIn(Widget message)
    {
        float start_x = 1920; // Off-screen right
        float end_x = 1700;   // Final position
        
        // Interpolate position over SLIDE_DURATION
        message.SetPos(start_x, message.GetPosY());
        AnimatePosition(message, start_x, end_x, SLIDE_DURATION);
    }
    
    void AnimateFadeOut(Widget message, float delay)
    {
        GetGame().GetCallQueue(CALL_CATEGORY_GUI)
            .CallLater(FadeOutWidget, delay * 1000, false, message);
    }
    
    void FadeOutWidget(Widget message)
    {
        AnimateAlpha(message, 1.0, 0.0, FADE_DURATION);
    }
}
```

#### Display Manager
**Purpose**: Coordinate message display and lifetime

**Responsibilities**:
- Add new messages
- Remove expired messages
- Manage message queue
- Handle overflow

**Message Lifecycle**:
```
1. Receive RPC → 2. Create Widget → 3. Animate In → 
4. Display (8s) → 5. Animate Out → 6. Destroy Widget
```

## Data Flow

### Complete Kill Event Flow

```
[Server] Player Death Detected
    ↓
[Server] Collect Event Data
    ↓
[Server] Validate Event
    ↓
[Server] Log to Database
    ↓
[Network] Serialize & Send RPC
    ↓
[Client] Receive RPC
    ↓
[Client] Deserialize Data
    ↓
[Client] Create Widget
    ↓
[Client] Animate & Display
    ↓
[Client] Schedule Removal
    ↓
[Client] Cleanup Widget
```

## Performance Considerations

### Memory Management
- **Widget Pooling**: Reuse widgets instead of creating new ones
- **Message Limit**: Cap active messages at 10
- **Cleanup**: Properly destroy expired widgets

### Network Optimization
- **Batching**: Send multiple kills in one packet when possible
- **Compression**: Use IDs instead of full names where possible
- **Relevance**: Only send to nearby players (optional)

### CPU Optimization
- **Event Throttling**: Limit events processed per frame
- **Lazy Updates**: Update UI only when needed
- **Efficient Animations**: Use hardware-accelerated animations

## Extensibility

### Plugin System
The architecture supports plugins for:
- Custom message formats
- Additional data collection
- Alternative UI styles
- Integration with other mods

### Configuration
All major components support configuration:
```javascript
class KillfeedConfig
{
    bool enabled = true;
    int max_messages = 10;
    float message_lifetime = 8.0;
    bool show_distance = true;
    bool show_weapon = true;
    bool show_headshots = true;
    string position = "top-right";
}
```

## Error Handling

### Common Issues & Solutions

1. **RPC Failures**: Retry mechanism with exponential backoff
2. **Widget Creation Failures**: Fallback to text-only display
3. **Network Lag**: Queue messages and display when available
4. **Memory Leaks**: Implement proper cleanup in destructors

## Testing Strategy

### Unit Tests
- Event data validation
- RPC serialization/deserialization
- Widget creation

### Integration Tests
- Server-to-client communication
- Multiple simultaneous kills
- Edge cases (suicide, environment kills)

### Performance Tests
- High kill rate scenarios
- Memory usage monitoring
- Network bandwidth measurement

## Next Steps

- [Implementation Guide](implementation.md) - Build the system step-by-step
- [Advanced Features](advanced-features.md) - Add sophisticated features
- [Performance Optimization](performance.md) - Optimize your implementation
