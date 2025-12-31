# Discord Integration & Webhooks - Complete Guide

## Overview

Discord integration allows DayZ servers to send real-time notifications, admin commands, player tracking, and automated alerts directly to Discord channels. This guide covers all major Discord integration solutions.

## Quick Comparison

| Solution | Webhooks | Bot Commands | Live Killfeed | Admin Tools | Cost |
|----------|----------|--------------|---------------|-------------|------|
| CFTools Discord Bot | ✅ Yes | ✅ Yes | ✅ Yes | ✅ Full | Free (open-source) |
| Universal API Mod | ✅ Yes | ✅ Yes | ⚠️ Custom | ⚠️ Custom | Free |
| Zen's Discord API | ✅ Yes | ⚠️ Limited | ✅ Yes | ⚠️ Limited | Free |
| Killfeed.DEV | ✅ Yes | ❌ No | ✅ Yes | ⚠️ Limited | Freemium |
| Skynet | ✅ Yes | ✅ Yes | ✅ Yes | ✅ Yes | Free |
| Advanced Logs | ✅ Yes | ❌ No | ✅ Yes | ⚠️ Logs Only | Paid |
| VPP Admin Tools | ✅ Yes | ❌ No | ⚠️ Via webhook | ⚠️ Limited | Free |

## Discord Webhook Basics

### Creating a Webhook

```
1. Open Discord server
2. Go to: Server Settings > Integrations > Webhooks
3. Click: "New Webhook"
4. Configure:
   - Name: "DayZ Server Notifications"
   - Channel: #dayz-events
   - Avatar: (optional icon)
5. Click: "Copy Webhook URL"
6. Save URL securely
```

### Webhook URL Format
```
https://discord.com/api/webhooks/1234567890/ABCdef123456_token_here
```

**IMPORTANT**: Never share webhook URLs publicly!

### Testing Webhook

```bash
# Using curl (Linux/Mac)
curl -H "Content-Type: application/json" \
     -d '{"content": "Test message from DayZ server!"}' \
     https://discord.com/api/webhooks/YOUR_WEBHOOK_URL

# Using PowerShell (Windows)
$payload = @{content="Test message"} | ConvertTo-Json
Invoke-RestMethod -Uri "https://discord.com/api/webhooks/YOUR_WEBHOOK_URL" `
                  -Method Post -Body $payload -ContentType "application/json"
```

## CFTools Discord Bot

### Overview
**GitHub**: https://github.com/Ariastarcos/cftools-discord-bot  
**Type**: Self-hosted Discord bot  
**Requirements**: CFTools Data API account

### Features
- Real-time server notifications
- Player join/leave tracking
- Killfeed with weapon/distance
- Admin commands (kick, ban, heal, teleport)
- Leaderboards
- Player search by Steam/BattlEye ID
- Watch lists
- Customizable alerts

### Installation

#### Prerequisites
```bash
# Required:
- Node.js 16+ installed
- CFTools Data API account (https://cftools.com/)
- Discord Bot Token
- Server with CFTools integration

# Get CFTools API credentials:
1. Register at https://cftools.com/
2. Link your DayZ server
3. Generate API token
4. Note: Application ID, Server ID, API Token
```

#### Setup Steps
```bash
# 1. Clone repository
git clone https://github.com/Ariastarcos/cftools-discord-bot
cd cftools-discord-bot

# 2. Install dependencies
npm install

# 3. Configure bot
cp config.example.json config.json
nano config.json

# 4. Start bot
node index.js

# Or use PM2 for auto-restart:
pm2 start index.js --name dayz-discord-bot
pm2 save
```

### Configuration

#### config.json
```json
{
  "token": "YOUR_DISCORD_BOT_TOKEN",
  "clientId": "YOUR_BOT_CLIENT_ID",
  "guildId": "YOUR_DISCORD_SERVER_ID",
  "cftools": {
    "applicationId": "YOUR_CFTOOLS_APP_ID",
    "secret": "YOUR_CFTOOLS_SECRET",
    "serverId": "YOUR_SERVER_ID"
  },
  "channels": {
    "killfeed": "1234567890123456",
    "joinsLeaves": "1234567890123457",
    "adminLogs": "1234567890123458"
  },
  "roles": {
    "admin": "1234567890123459"
  }
}
```

### Discord Bot Commands

#### Player Management
```
/player search [steam64id] - Search player info
/player info [name] - Get player details
/player kick [name] [reason] - Kick player
/player ban [name] [duration] [reason] - Ban player
```

#### Server Management
```
/server status - Get server info
/server restart - Restart server
/server message [text] - Send global message
/server time [hour] - Set server time
/server weather [type] - Change weather
```

#### Teleport Commands
```
/teleport player [name] [x] [y] [z] - Teleport player
/teleport to [player1] [player2] - Teleport player1 to player2
/teleport me [x] [y] [z] - Teleport yourself
```

#### Player Actions
```
/heal [player] - Heal player
/kill [player] - Kill player
/spawn [item] [player] - Spawn item for player
```

#### Statistics
```
/stats player [name] - Player statistics
/stats leaderboard [kills|deaths|playtime] - Server leaderboards
/stats server - Server statistics
```

## Universal API Mod - Discord Features

### Overview
**Workshop**: https://steamcommunity.com/sharedfiles/filedetails/?id=2237983606  
**GitHub**: https://github.com/daemonforge/DayZ-UniveralApi

### Discord API Capabilities
- Send direct messages
- Send channel messages
- Create/edit/delete channels
- Add/remove roles
- Voice channel management
- Retrieve messages
- User account linking

### Installation

#### Server Setup
```bash
# 1. Subscribe to mod
@UniversalApi

# 2. Add to server startup
-mod=@CF;@UniversalApi

# 3. Configure
# File: mpmissions/[mission]/UniversalApi/config.json
```

#### Configuration
```json
{
  "DiscordBot": {
    "Enabled": true,
    "Token": "YOUR_DISCORD_BOT_TOKEN",
    "GuildId": "YOUR_DISCORD_SERVER_ID",
    "Channels": {
      "Logs": "1234567890",
      "Killfeed": "1234567891",
      "Admin": "1234567892"
    }
  },
  "Features": {
    "DirectMessages": true,
    "RoleManagement": true,
    "ChannelCreation": true,
    "VoiceManagement": true
  }
}
```

### API Endpoints

#### Send Discord Message
```javascript
// EnScript example
void SendDiscordMessage(string channel_id, string message)
{
    UniversalApiModule api = UniversalApiModule.Cast(CF_ModuleCoreManager.Get(UniversalApiModule));
    api.SendDiscordMessage(channel_id, message);
}
```

#### Add Discord Role
```javascript
void GivePlayerRole(string user_id, string role_id)
{
    UniversalApiModule api = UniversalApiModule.Cast(CF_ModuleCoreManager.Get(UniversalApiModule));
    api.AddDiscordRole(user_id, role_id);
}
```

#### Send DM
```javascript
void SendDM(string user_id, string message)
{
    UniversalApiModule api = UniversalApiModule.Cast(CF_ModuleCoreManager.Get(UniversalApiModule));
    api.SendDirectMessage(user_id, message);
}
```

## Zen's Discord API + Raid Alarm

### Overview
**Workshop**: https://steamcommunity.com/sharedfiles/filedetails/?id=3297571122

### Features
- Custom Discord messages from in-game
- Raid alarm notifications
- Killfeed integration
- Admin tools
- Player-triggered alerts

### Installation
```bash
# Via Workshop
@ZensDiscordAPI
@CF

# Startup
-mod=@CF;@ZensDiscordAPI
```

### Configuration
```
File: mpmissions/[mission]/ZensDiscordAPI/config.json
```

```json
{
  "WebhookURL": "https://discord.com/api/webhooks/YOUR_WEBHOOK",
  "RaidAlarm": {
    "Enabled": true,
    "Cooldown": 300,
    "AlertChannel": "1234567890"
  },
  "Killfeed": {
    "Enabled": true,
    "ShowWeapon": true,
    "ShowDistance": true,
    "WebhookURL": "https://discord.com/api/webhooks/KILLFEED_WEBHOOK"
  }
}
```

## Killfeed.DEV

### Overview
**Website**: https://killfeed.dev/  
**Type**: Cloud-based killfeed service  
**Platforms**: PC, Xbox, PS4

### Features
- 32+ event types logged
- Real-time Discord embeds
- Searchable log database
- Live web map
- Moderation tools
- Analytics dashboard

### Setup

#### 1. Register Server
```
1. Go to https://killfeed.dev/
2. Create account
3. Click "Add Server"
4. Enter server details:
   - Name
   - IP
   - FTP credentials
   - Platform (PC/Xbox/PS4)
```

#### 2. Configure Discord
```
1. Server Settings > Discord
2. Add webhook URL
3. Select events to log:
   ☑ Kills
   ☑ Deaths
   ☑ Connections
   ☑ Disconnections
   ☑ Admin actions
   ☑ Base raids
4. Customize embed appearance
5. Save
```

#### 3. Event Types
- Player kills (PvP)
- Player deaths (PvE)
- Suicides
- Unconscious events
- Connections/Disconnections
- Admin actions
- Base raids/destruction
- Vehicle usage
- Item placement
- Territory actions
- Custom events

### Discord Embed Example
```
━━━━━━━━ 💀 KILL ━━━━━━━━
Killer: PlayerOne
Victim: PlayerTwo
Weapon: M4A1
Distance: 247m
Location: Stary Sobor
Time: 14:23:45
━━━━━━━━━━━━━━━━━━━━━
```

## Skynet

### Overview
**Website**: https://dayzskynet.com/  
**Type**: Free server assistant  
**Platforms**: Console (Xbox/PS4) primary

### Features
- 24/7 monitoring
- Kill/death notifications
- Weapon/distance tracking
- Multi-server support
- Moderation integration
- Admin dashboard

### Setup
```
1. Visit https://dayzskynet.com/
2. Sign up
3. Link server:
   - Server name
   - Platform
   - FTP or API access
4. Connect Discord:
   - Add bot to Discord server
   - Authorize permissions
   - Select notification channel
5. Configure events
6. Test notifications
```

## Advanced Logs Mod

### Overview
**Website**: https://huntermods.online/product/66f706f4a65871b96950be7b  
**Type**: Comprehensive logging mod

### Features
- Action logging
- Kill feed
- Item tracking
- Server start notifications
- Player connections
- Multiple webhook support

### Configuration
```json
{
  "EnableDiscordWebhooks": true,
  "Webhooks": {
    "discordPlayerConnectionWebhook": "https://discord.com/api/webhooks/...",
    "discordPlayerKillFeedWebhook": "https://discord.com/api/webhooks/...",
    "discordPlayerActionWebhook": "https://discord.com/api/webhooks/...",
    "serverStartWebhook": "https://discord.com/api/webhooks/..."
  },
  "LoggingOptions": {
    "LogPlacement": true,
    "LogDestruction": true,
    "LogItemUse": true,
    "LogCrafting": true
  },
  "BlacklistedActions": [
    "PickUpItem",
    "DropItem"
  ]
}
```

### Event Examples

#### Kill Notification
```json
{
  "embeds": [{
    "title": "💀 Player Kill",
    "color": 15158332,
    "fields": [
      {"name": "Killer", "value": "PlayerOne", "inline": true},
      {"name": "Victim", "value": "PlayerTwo", "inline": true},
      {"name": "Weapon", "value": "M4A1", "inline": true},
      {"name": "Distance", "value": "150m", "inline": true},
      {"name": "Location", "value": "Stary Sobor (6040, 7710)", "inline": false}
    ],
    "timestamp": "2025-01-01T14:23:45.000Z"
  }]
}
```

## VPP Admin Tools Discord Integration

### Overview
**Workshop**: https://steamcommunity.com/sharedfiles/filedetails/?id=1828439124

### Webhook Configuration
```
File: profiles/VPPAdminTools/Config/WebHooks.json
```

```json
{
  "WebHooks": [
    {
      "URL": "https://discord.com/api/webhooks/YOUR_WEBHOOK",
      "Events": [
        "PlayerKill",
        "PlayerDeath",
        "AdminAction",
        "ServerStart",
        "ServerStop"
      ],
      "Enabled": true
    }
  ]
}
```

## Custom Discord Embeds

### Basic Message
```json
{
  "content": "Simple text message"
}
```

### Rich Embed
```json
{
  "embeds": [{
    "title": "DayZ Server Alert",
    "description": "Server is starting up",
    "color": 3447003,
    "fields": [
      {"name": "Server", "value": "My DayZ Server", "inline": true},
      {"name": "Map", "value": "Chernarus+", "inline": true},
      {"name": "Players", "value": "0/60", "inline": true}
    ],
    "thumbnail": {"url": "https://example.com/icon.png"},
    "timestamp": "2025-01-01T12:00:00.000Z",
    "footer": {"text": "DayZ Server Bot", "icon_url": "https://example.com/footer.png"}
  }]
}
```

### Kill Feed Embed
```json
{
  "embeds": [{
    "title": "💀 Kill Feed",
    "color": 16711680,
    "fields": [
      {"name": "Killer", "value": "SniperKing", "inline": true},
      {"name": "Victim", "value": "Noob123", "inline": true},
      {"name": "Weapon", "value": "SVD", "inline": true},
      {"name": "Distance", "value": "487m", "inline": true},
      {"name": "Location", "value": "NWAF (4520, 10430)", "inline": false},
      {"name": "Headshot", "value": "✅ Yes", "inline": true}
    ],
    "thumbnail": {"url": "https://example.com/skull.png"},
    "timestamp": "2025-01-01T14:23:45.000Z"
  }]
}
```

## Admin Log Parsing

### Enable Admin Logs
```bash
# Add to server startup parameters
-adminlog

# Logs created in:
profiles/[date]_[time].ADM
```

### Log Format
```
2025-01-01, 14:23:45 | Player "PlayerOne"(id=ABC123 pos=<7500.0, 0.0, 5800.0>) killed by Player "PlayerTwo"(id=XYZ789 pos=<7650.0, 0.0, 5900.0>) with M4A1 from 150m
```

### Python Parser Example
```python
import re
import requests
import time

WEBHOOK_URL = "https://discord.com/api/webhooks/YOUR_WEBHOOK"
LOG_FILE = "profiles/latest.ADM"

def parse_kill(line):
    pattern = r'Player "([^"]+)".*killed by Player "([^"]+)".*with (\w+) from ([\d.]+)m'
    match = re.search(pattern, line)
    if match:
        return {
            "victim": match.group(1),
            "killer": match.group(2),
            "weapon": match.group(3),
            "distance": match.group(4)
        }
    return None

def send_discord(data):
    payload = {
        "embeds": [{
            "title": "💀 Kill",
            "fields": [
                {"name": "Killer", "value": data["killer"], "inline": True},
                {"name": "Victim", "value": data["victim"], "inline": True},
                {"name": "Weapon", "value": data["weapon"], "inline": True},
                {"name": "Distance", "value": f"{data['distance']}m", "inline": True}
            ],
            "color": 16711680
        }]
    }
    requests.post(WEBHOOK_URL, json=payload)

def monitor_log():
    with open(LOG_FILE, 'r') as f:
        f.seek(0, 2)  # Go to end
        while True:
            line = f.readline()
            if line:
                data = parse_kill(line)
                if data:
                    send_discord(data)
            time.sleep(1)

if __name__ == "__main__":
    monitor_log()
```

## Rate Limiting

### Discord Limits
- **Webhooks**: 30 requests per minute per webhook
- **Bot Messages**: 5 per channel per 5 seconds
- **Global**: 50 requests per second per bot

### Best Practices
```python
import time
from collections import deque

class RateLimiter:
    def __init__(self, max_calls=30, period=60):
        self.max_calls = max_calls
        self.period = period
        self.calls = deque()
    
    def __call__(self, func):
        def wrapper(*args, **kwargs):
            now = time.time()
            # Remove old calls
            while self.calls and self.calls[0] < now - self.period:
                self.calls.popleft()
            
            if len(self.calls) < self.max_calls:
                self.calls.append(now)
                return func(*args, **kwargs)
            else:
                wait = self.period - (now - self.calls[0])
                time.sleep(wait)
                self.calls.append(time.time())
                return func(*args, **kwargs)
        return wrapper

@RateLimiter(max_calls=30, period=60)
def send_discord_message(webhook_url, message):
    requests.post(webhook_url, json={"content": message})
```

## Security Best Practices

### Webhook Security
1. **Never commit webhooks to Git**
   ```bash
   # Add to .gitignore
   config.json
   webhooks.txt
   *.secret
   ```

2. **Use environment variables**
   ```bash
   export DISCORD_WEBHOOK="https://discord.com/api/webhooks/..."
   ```

3. **Rotate webhooks regularly**
   - Delete old webhooks
   - Create new ones
   - Update configs

4. **Limit permissions**
   - Only grant necessary channel access
   - Use separate webhooks per channel
   - Monitor webhook usage

### Bot Security
1. **Token protection**
   - Never share bot token
   - Use .env files
   - Rotate if compromised

2. **Permission scoping**
   - Only grant needed permissions
   - Use role-based access
   - Audit regularly

3. **Command restrictions**
   - Admin-only commands
   - Rate limiting
   - Input validation

## Troubleshooting

### Webhook Not Working
- Verify webhook URL is correct
- Check channel permissions
- Test with curl/PowerShell
- Review Discord server settings
- Check rate limits

### Messages Not Appearing
- Verify webhook isn't deleted
- Check Discord channel exists
- Review embed format (JSON valid)
- Check character limits
- Verify timestamp format

### Bot Offline
- Check bot token
- Verify bot invited to server
- Check server permissions
- Review bot code for errors
- Check hosting/uptime

## Related Documentation

- [CFTools Integration](../analytics-monitoring/cftools.md)
- [Universal API](../api-integration/universal-api.md)
- [Server Administration](../server/administration.md)
- [Killfeed Systems](../killfeed/basics.md)

## External Resources

- **CFTools Discord Bot**: https://github.com/Ariastarcos/cftools-discord-bot
- **Universal API**: https://github.com/daemonforge/DayZ-UniveralApi
- **Killfeed.DEV**: https://killfeed.dev/
- **Skynet**: https://dayzskynet.com/
- **Discord API Docs**: https://discord.com/developers/docs/intro
- **Webhook Guide**: https://discord.com/developers/docs/resources/webhook
