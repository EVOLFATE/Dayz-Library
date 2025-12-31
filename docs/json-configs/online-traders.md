# Online Traders - Complete Configuration Guide

## Overview

Online traders in DayZ allow players to buy and sell items using various currency systems. This guide covers complete setup for all major trader mods with JSON configuration, X,Y,Z coordinate placement, and integration with interactive maps.

## Trader System Comparison

| Feature | Expansion Mod | TraderPlus | TravelingTrader | Classic Trader |
|---------|---------------|------------|-----------------|----------------|
| Static Traders | ✅ Yes | ✅ Yes | ✅ Yes | ✅ Yes |
| Moving Traders | ❌ No | ❌ No | ✅ Yes | ❌ No |
| Trade Zones | ✅ Yes | ✅ Yes | ❌ No | ⚠️ Limited |
| Currency | Custom | Custom | Custom | Custom |
| Vehicle Trading | ✅ Yes | ✅ Yes | ⚠️ Limited | ❌ No |
| Base Trading | ✅ Yes | ⚠️ Limited | ❌ No | ❌ No |
| JSON Config | ✅ Yes | ✅ Yes | ✅ Yes | ❌ No (TXT) |
| Coordinates | X,Y,Z Array | X Y Z String | X Y Z String | X Y Z String |
| Active Development | ✅ Yes | ✅ Yes | ✅ Yes | ❌ No |

## DayZ Expansion Mod Traders

### Overview
**Workshop**: https://steamcommunity.com/sharedfiles/filedetails/?id=2116157322  
**Docs**: https://github.com/ExpansionModTeam/DayZ-Expansion-Settings

The Expansion mod is the most feature-rich trader system with zones, static NPCs, and extensive customization.

### Installation

#### Server Setup
```bash
# Via Steam Workshop
1. Subscribe to @DayZ-Expansion-Core
2. Install @DayZ-Expansion-Market
3. Install @DayZ-Expansion-Vehicles (optional)

# Add to server startup
-mod=@CF;@DayZ-Expansion-Core;@DayZ-Expansion-Market

# File structure created:
mpmissions/[mission]/expansion/
├── traderzones/
│   └── World.json
├── settings/
│   └── MarketSettings.json
└── market/
    ├── Weapons.json
    ├── Ammo.json
    ├── Items.json
    └── [category].json
```

### Trader Zone Configuration

#### File Location
```
mpmissions/[mission]/expansion/traderzones/World.json
```

#### Basic Zone Example
```json
{
  "m_Version": 6,
  "TraderZones": [
    {
      "m_Version": 7,
      "m_DisplayName": "Green Mountain Trader",
      "Position": [3690.0, 402.0, 5990.0],
      "Radius": 150.0,
      "BuyPricePercent": 100.0,
      "SellPricePercent": 75.0,
      "m_Icon": "Trader"
    }
  ]
}
```

#### Finding and Using Coordinates

##### Method 1: iZurvive
```
1. Open iZurvive.com
2. Search for desired location (e.g., "Green Mountain")
3. Click on exact trader position
4. Note coordinates in URL or display
   Example: X=3690, Y=5990 (Y on map = Z in config)
5. Add to JSON:
   "Position": [3690.0, 0.0, 5990.0]
   Note: Middle value (Y) is altitude - use 0.0 for auto-adjust
```

##### Method 2: DayZ Editor
```
1. Open DayZ Editor
2. Navigate to desired location
3. Place marker object
4. Press F2 to copy position
5. Format copied: "3690.0 402.0 5990.0"
6. Convert to JSON array: [3690.0, 402.0, 5990.0]
```

##### Method 3: In-Game GPS
```
1. Get GPS receiver in-game
2. Stand at trader location
3. Read coordinates
4. Convert GPS format to X,Y,Z
5. Use in JSON config
```

#### Complete Trader Zone Config
```json
{
  "m_Version": 6,
  "TraderZones": [
    {
      "m_Version": 7,
      "m_DisplayName": "Northwest Airfield Trader",
      "Position": [4520.0, 0.0, 10430.0],
      "Radius": 200.0,
      "BuyPricePercent": 100.0,
      "SellPricePercent": 80.0,
      "m_Icon": "Trader"
    },
    {
      "m_Version": 7,
      "m_DisplayName": "Coastal Trader - Cherno",
      "Position": [6670.0, 0.0, 2530.0],
      "Radius": 100.0,
      "BuyPricePercent": 110.0,
      "SellPricePercent": 70.0,
      "m_Icon": "Trader"
    },
    {
      "m_Version": 7,
      "m_DisplayName": "Black Market - Tisy",
      "Position": [1020.0, 0.0, 13810.0],
      "Radius": 75.0,
      "BuyPricePercent": 150.0,
      "SellPricePercent": 90.0,
      "m_Icon": "Trader"
    }
  ]
}
```

#### Zone Parameters Explained

**m_DisplayName**
- Name shown to players
- Appears when entering zone
- Should be descriptive

**Position**
- Format: [X, Y, Z]
- X: West-East (0-15360 on Chernarus)
- Y: Altitude (0.0 for auto-adjust to ground)
- Z: South-North (0-15360 on Chernarus)

**Radius**
- Zone size in meters
- Safe zone / PvP disabled area
- Typical values: 50-200m
- Too large = too much safe area
- Too small = hard to trade safely

**BuyPricePercent**
- Price multiplier when player BUYS
- 100 = normal price
- 150 = 50% more expensive
- 80 = 20% discount
- Use for economy balance

**SellPricePercent**
- Price multiplier when player SELLS
- -1 = cannot sell to this trader
- 75 = player gets 75% of item value
- 100 = full value (rare)
- Prevents money duplication

### Trader NPC Configuration

#### File Location
```
mpmissions/[mission]/expansion/settings/MarketSettings.json
```

#### NPC Trader Setup
```json
{
  "m_Version": 13,
  "EnableAutoCalculateTraderStock": 1,
  "TraderObjects": [
    {
      "ClassName": "ExpansionTraderObject",
      "Position": [3690.0, 402.0, 5990.0],
      "Orientation": [0.0, 180.0, 0.0],
      "TraderID": 1,
      "EmoteID": 0,
      "LoadoutID": 0
    }
  ]
}
```

#### NPC Parameters

**ClassName**
- "ExpansionTraderObject" = Standard trader
- Can use other humanoid classes

**Position**
- [X, Y, Z] coordinates
- Should be INSIDE trader zone
- Typically near zone center

**Orientation**
- [Yaw, Pitch, Roll]
- Yaw: 0°=North, 90°=East, 180°=South, 270°=West
- Pitch/Roll: Usually 0.0
- Face trader toward customer approach direction

**TraderID**
- Links to trader inventory (1-based)
- Each trader can have unique stock
- Configure in Weapons.json, Items.json, etc.

### Market Item Configuration

#### File Structure
```
mpmissions/[mission]/expansion/market/
├── Weapons.json        # Guns, melee weapons
├── Ammo.json           # Ammunition
├── Items.json          # General items
├── Clothing.json       # Wearables
├── Food.json           # Consumables
├── Medical.json        # Medical supplies
├── Vehicles.json       # Cars, trucks
└── Base.json           # Base building
```

#### Example: Weapons.json
```json
{
  "m_Version": 22,
  "Items": [
    {
      "ClassName": "M4A1",
      "MaxPriceThreshold": 5000,
      "MinPriceThreshold": 2500,
      "SellPricePercent": 75,
      "MaxStockThreshold": 5,
      "MinStockThreshold": 1,
      "QuantityPercent": -1,
      "SpawnAttachments": [
        "M4_OEBttstck",
        "M4_PlasticHndgrd",
        "ACOGOptic"
      ],
      "Variants": []
    }
  ]
}
```

#### Price Calculation
```
Buy Price = (MaxPriceThreshold + MinPriceThreshold) / 2
          = (5000 + 2500) / 2
          = 3750

Sell Price = Buy Price × (SellPricePercent / 100)
           = 3750 × 0.75
           = 2812.5
```

### Multiple Trader Locations Example

#### Chernarus+ Trader Network
```json
{
  "m_Version": 6,
  "TraderZones": [
    {
      "m_DisplayName": "Coastal Trader - Elektro",
      "Position": [10420.0, 0.0, 2150.0],
      "Radius": 120.0,
      "BuyPricePercent": 110.0,
      "SellPricePercent": 70.0
    },
    {
      "m_DisplayName": "Coastal Trader - Cherno",
      "Position": [6670.0, 0.0, 2530.0],
      "Radius": 100.0,
      "BuyPricePercent": 110.0,
      "SellPricePercent": 70.0
    },
    {
      "m_DisplayName": "Inland Trader - Stary Sobor",
      "Position": [6040.0, 0.0, 7710.0],
      "Radius": 150.0,
      "BuyPricePercent": 100.0,
      "SellPricePercent": 75.0
    },
    {
      "m_DisplayName": "Military Trader - NWAF",
      "Position": [4520.0, 0.0, 10430.0],
      "Radius": 200.0,
      "BuyPricePercent": 90.0,
      "SellPricePercent": 80.0
    },
    {
      "m_DisplayName": "Black Market - Tisy",
      "Position": [1020.0, 0.0, 13810.0],
      "Radius": 75.0,
      "BuyPricePercent": 150.0,
      "SellPricePercent": 90.0
    },
    {
      "m_DisplayName": "Green Mountain",
      "Position": [3690.0, 402.0, 5990.0],
      "Radius": 100.0,
      "BuyPricePercent": 100.0,
      "SellPricePercent": 75.0
    }
  ]
}
```

## TraderPlus Mod

### Overview
**Workshop**: https://steamcommunity.com/sharedfiles/filedetails/?id=2458896948  
**Type**: Lightweight trader alternative

### Installation
```bash
# Via Steam Workshop
@TraderPlus
@CF (Community Framework - Required)

# Add to startup
-mod=@CF;@TraderPlus
```

### Configuration File
```
mpmissions/[mission]/TraderPlus/TraderConfig.txt
```

### Trader Format
```json
<Trader>
    Name:Green Mountain Trader
    Position:3690.27 402.13 5967.91
    Orientation:-13.234265 0 0
    <Currency>
        Classname:TraderPlus_Money,TraderPlus_Coin_Silver
        Amount:1,10
    </Currency>
    <Categories>
        Weapons,Ammo,Clothing,Medical,Food,Vehicles
    </Categories>
</Trader>
```

### Coordinate Format
- **Format**: "X Y Z" (space-separated string)
- **Example**: "3690.27 402.13 5967.91"
- X = 3690.27
- Y = 402.13 (altitude)
- Z = 5967.91

### Extracting Coordinates
```
1. Use DayZ Editor at location
2. Press F2 to copy position
3. Result: "3690.27 402.13 5967.91"
4. Paste directly into Position field
```

## TravelingTrader Mod

### Overview
**Workshop**: https://steamcommunity.com/sharedfiles/filedetails/?id=3050988801  
**Unique Feature**: Traders that move between locations

### Installation
```bash
# Via Steam Workshop
@TravelingTrader
@CF (Required)

# Startup
-mod=@CF;@TravelingTrader
```

### Configuration File
```
mpmissions/[mission]/RTT/Config.json
```

### Traveling Trader Config
```json
{
  "RTTraderData": [
    {
      "ID": 0,
      "DisplayName": "Weapons Dealer",
      "MoveTime": 1800000,
      "MoveMessage": "The Weapons Dealer has moved to a new location!",
      "Position": [
        "3699.27 402.13 5967.91",
        "6670.50 10.25 2530.80",
        "10420.30 5.10 2150.40",
        "4520.00 15.00 10430.00"
      ],
      "Orientation": [
        "-13.234265 0 0",
        "0 0 0",
        "45.0 0 0",
        "90.0 0 0"
      ],
      "Categories": ["Weapons", "Ammo", "Attachments"]
    },
    {
      "ID": 1,
      "DisplayName": "General Trader",
      "MoveTime": 3600000,
      "MoveMessage": "The General Trader has relocated!",
      "Position": [
        "7040.0 0.0 7710.0",
        "8040.0 0.0 12670.0"
      ],
      "Orientation": [
        "0 0 0",
        "180.0 0 0"
      ],
      "Categories": ["Food", "Medical", "Clothing", "Tools"]
    }
  ]
}
```

### Parameters Explained

**MoveTime**
- Milliseconds between moves
- 1800000 = 30 minutes
- 3600000 = 1 hour
- 7200000 = 2 hours

**Position Array**
- List of all possible locations
- Trader cycles through them
- Format: "X Y Z" strings

**Orientation Array**
- Must match Position array length
- One orientation per position

**Movement Notification**
- Discord webhooks supported
- Announces new location
- Helps players find traders

### Finding Multiple Locations

#### Using iZurvive
```
1. Open iZurvive
2. Plan trader route:
   - Stop 1: Green Mountain (3690, 5990)
   - Stop 2: Cherno (6670, 2530)
   - Stop 3: Elektro (10420, 2150)
   - Stop 4: NWAF (4520, 10430)
3. Create markers at each stop
4. Export coordinates
5. Add to Position array
```

## Trader Converter Tools

### Mavericks Trader Converter
**Workshop**: https://steamcommunity.com/sharedfiles/filedetails/?id=3398433763

Converts between trader formats:
- Classic Trader (TXT) → Expansion (JSON)
- TraderPlus → Expansion
- Expansion → TraderPlus

### Manual Conversion

#### From Expansion to TraderPlus
```javascript
// Expansion format:
"Position": [3690.0, 402.0, 5990.0]

// Convert to TraderPlus format:
Position:3690.0 402.0 5990.0
```

#### From TraderPlus to Expansion
```javascript
// TraderPlus format:
Position:3690.27 402.13 5967.91

// Convert to Expansion format:
"Position": [3690.27, 402.13, 5967.91]
```

## Trader Editor Tools

### TraderX Editor
**URL**: https://traderpluseditor.dmitri-dev-area.dev/

Features:
- Visual item selection
- Price configuration
- Category management
- Export to TraderPlus format

### DayZConfigEditor
**GitHub**: https://github.com/EcoVisionAnalytics/DayZConfigEditor

Features:
- Multi-format support
- Bulk price editing
- Import/Export
- Validation

## Mapping Traders on Interactive Maps

### iZurvive Integration

#### Mark All Traders
```
1. Export all trader coordinates from configs
2. Open iZurvive
3. For each trader:
   - Search coordinates
   - Place marker
   - Label with trader name
   - Color-code by type:
     * Green = General trader
     * Red = Weapons trader
     * Blue = Vehicle trader
     * Yellow = Black market
4. Create group
5. Share with players
```

### DZB Tools Integration

#### Territory Protection
```
1. Open DZB Tools Territory Editor
2. For each trader location:
   - Add territory polygon
   - Center on trader coordinates
   - Set radius (match safe zone)
   - Configure as safe zone
3. Export territories.xml
4. Upload to server
5. Traders protected from raiding/PvP
```

## Currency Systems

### Expansion Mod Currency
```json
// Default: Expansion_Money_Ruble
{
  "ClassName": "Expansion_Money_Ruble",
  "MaxPriceThreshold": 1,
  "MinPriceThreshold": 1,
  "MaxStockThreshold": -1,
  "MinStockThreshold": -1
}

// Alternative currencies:
- Expansion_Money_Dollar
- Expansion_Money_Euro
- Custom items (nails, bullets, etc.)
```

### TraderPlus Currency
```xml
<Currency>
    Classname:TraderPlus_Money,SodaCan_Pipsi
    Amount:1,5
</Currency>
<!-- 1 Money = 5 Soda cans -->
```

### Custom Currency
```json
// Use any item as currency
{
  "Currency": [
    {
      "ClassName": "Nail",
      "Amount": 1
    },
    {
      "ClassName": "WoodenPlank",
      "Amount": 10
    }
  ]
}
// 10 nails = 1 plank value
```

## Best Trader Locations

### Chernarus+ Recommended
| Location | Coordinates | Type | Reason |
|----------|-------------|------|--------|
| Green Mountain | 3690, 5990 | General | Central, iconic |
| Stary Sobor | 6040, 7710 | Military | Mid-map, accessible |
| NWAF | 4520, 10430 | Weapons | High-tier zone |
| Cherno Hospital | 6690, 2690 | Medical | Coastal, high traffic |
| Elektro | 10420, 2150 | General | Spawn area |
| Tisy | 1020, 13810 | Black Market | Remote, NBC zone |
| Kamensk | 7890, 14640 | Military | Alternative to NWAF |

### Livonia Recommended
| Location | Coordinates | Type |
|----------|-------------|------|
| Swarog | 6100, 3100 | General |
| Nadbor | 10300, 9500 | Military |
| Sitnik | 4800, 8200 | Medical |
| Kolembrody | 2900, 11300 | Vehicles |

## FTP Deployment

### Upload Process
```bash
# Connect via FTP (FileZilla recommended)
Host: your-server-ip
Port: 21 (or custom)
User: your-ftp-user
Pass: your-ftp-pass

# Navigate to mission folder
cd /mpmissions/dayzOffline.chernarusplus/

# For Expansion Mod
cd expansion/
# Upload: traderzones/World.json
# Upload: settings/MarketSettings.json
# Upload: market/*.json

# For TraderPlus
cd TraderPlus/
# Upload: TraderConfig.txt
# Upload: Categories/*.json

# Restart server
```

### Verification
```
1. Join server
2. Navigate to trader coordinates
3. Check for trader zone notification
4. Verify NPC presence
5. Test buy/sell
6. Check prices
7. Monitor server logs for errors
```

## Troubleshooting

### Trader Not Appearing
- Verify coordinates are within map bounds
- Check mod is loaded (-mod parameter)
- Review server logs for errors
- Ensure JSON syntax is valid
- Check file permissions (FTP)

### Wrong Location
- Double-check X,Z values (not X,Y)
- Verify map (Chernarus vs Livonia)
- Use iZurvive to confirm coordinates
- Check for typos in JSON

### Can't Trade
- Verify currency in inventory
- Check trade zone radius
- Ensure player is inside zone
- Review trader stock configuration
- Check server economy settings

### Prices Wrong
- Review BuyPricePercent
- Check SellPricePercent
- Verify item price thresholds
- Check for economy mods conflicts

## Related Documentation

- [Territory Configuration](territories-json.md)
- [Economy System](economy-json.md)
- [Interactive Maps](../interactive-maps/chernarus.md)
- [DayZ Editor](../interactive-maps/dayz-editor-integration.md)
- [Server Configuration](../server/configuration.md)

## External Resources

- **Expansion Mod**: https://github.com/ExpansionModTeam/DayZ-Expansion-Settings
- **TraderPlus**: https://steamcommunity.com/sharedfiles/filedetails/?id=2458896948
- **TravelingTrader**: https://steamcommunity.com/sharedfiles/filedetails/?id=3050988801
- **TraderX Editor**: https://traderpluseditor.dmitri-dev-area.dev/
- **Converter**: https://steamcommunity.com/sharedfiles/filedetails/?id=3398433763
