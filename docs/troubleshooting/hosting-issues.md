# Hosting Provider Specific Issues

## Complete Guide to DayZ Server Hosting Problems

Different hosting providers have unique interfaces, tools, and issues. This guide covers common problems with major DayZ server hosts.

---

## Nitrado

### Common Issues

#### Can't Access FTP

**Problem**: FTP login fails

**Solutions**:

**Get FTP Credentials**:
```
1. Nitrado Web Interface
2. Server → Settings
3. FTP Details section
4. Server: [shown]
5. Username: [shown]
6. Password: [click to show]
7. Port: 21 (usually)
```

**FTP Client Settings**:
```
FileZilla configuration:
- Protocol: FTP
- Host: ftp.nitrado.net (or shown IP)
- Port: 21
- Username: [from panel]
- Password: [from panel]
- Encryption: Use explicit FTP over TLS if available
```

**Common Mistakes**:
```
✗ Using game server IP instead of FTP server
✗ Wrong port (should be 21)
✗ Password typo (copy/paste it!)
✗ Account not fully activated
```

#### Mods Not Loading

**Problem**: Installed mods via web interface but server doesn't load them

**Checklist**:
```
1. Mod installed via Nitrado mod manager?
2. Mod enabled (checkbox checked)?
3. Server restarted after installing?
4. Mod keys auto-copied? (usually automatic)
5. Check in Files → Expert Mode → Active mods
```

**Manual Verification**:
```
Via FTP:
1. Check folder exists: /[server]/mods/@ModName
2. Verify .pbo files inside: @ModName/addons/
3. Check keys folder: /[server]/keys/*.bikey
```

#### Can't Edit Config Files

**Problem**: Changes to serverDZ.cfg don't save

**Solutions**:

**Via Web Interface**:
```
1. Stop server first!
2. Settings → General
3. Edit settings
4. Click Save
5. Start server
```

**Via FTP**:
```
1. Stop server
2. Download file
3. Edit locally
4. Upload (overwrite)
5. Start server

Note: Some settings revert if edited via FTP
Use web interface when possible
```

**File Locked**:
```
If "file locked" error:
1. Stop server completely
2. Wait 1 minute
3. Try again
4. Contact support if persists
```

#### Server Won't Start After Mod Install

**Problem**: Server crashes after adding mods

**Debug Steps**:

**Check Logs**:
```
Web Interface → Logs
Or FTP: /[server]/config/logs/

Look for mod-related errors
```

**Test Mods Individually**:
```
1. Remove all mods
2. Start server (should work)
3. Add mods one at a time
4. Restart after each
5. Identify problematic mod
```

**Verify Mod Compatibility**:
```
- Check mod supports current DayZ version
- Read Nitrado's mod compatibility notes
- Check mod Workshop comments
```

### Nitrado-Specific Features

**Auto-Restart**:
```
Web Interface → Settings → Restarts
- Enable automatic restarts
- Set schedule (daily recommended)
- Configure warnings
```

**Backup & Restore**:
```
Settings → Backups
- Automatic backups available
- Manual backup option
- Easy restore process
```

---

## G-Portal

### Common Issues

#### Mod Installation Failed

**Problem**: Mod shows "failed" in mod manager

**Solutions**:

**Retry Installation**:
```
1. Remove failed mod
2. Refresh page
3. Search mod again
4. Install fresh
```

**Check Mod Availability**:
```
Some mods not available on G-Portal:
- Outdated mods
- Incompatible mods
- Removed from Workshop

Try alternative or manual install
```

**Manual Install via FTP**:
```
1. Download mod on local PC (Workshop)
2. FTP to server
3. Upload to: g12345/dayz/mods/@ModName/
4. Copy keys manually
5. Edit config via web interface
```

#### Can't Connect to MySQL Database

**Problem**: Database mods won't connect

**G-Portal Database Setup**:
```
1. Order MySQL database add-on
2. Note credentials:
   - Host
   - Port
   - Database name
   - Username
   - Password
3. Configure mod with these details
4. Ensure port allowed in firewall
```

**Connection String**:
```json
{
    "host": "mysql.g-portal.net",
    "port": 3306,
    "database": "your_db_name",
    "username": "your_username",
    "password": "your_password"
}
```

#### Server Performance Issues

**Problem**: Server lags despite adequate resources

**G-Portal Optimization**:
```
Settings → Performance:
- Check current CPU usage
- Monitor RAM usage
- Reduce player count if needed
- Optimize loot spawns
- Reduce AI count
```

**Consider Upgrade**:
```
G-Portal slot limits:
Basic: 10-20 players
Standard: 30-40 players
Premium: 50-60 players

Upgrade if exceeding capacity
```

---

## HostHavoc

### Common Issues

#### Can't Upload Large Files

**Problem**: FTP upload fails for large mods

**Solutions**:

**Use SFTP Instead of FTP**:
```
SFTP allows larger transfers:
- Protocol: SFTP
- Host: [from panel]
- Port: 2022 (HostHavoc specific)
- Username: [from panel]
- Password: [from panel]
```

**Split Upload**:
```
If still fails:
1. Zip mod files
2. Upload .zip
3. Extract via File Manager
4. Or upload smaller chunks
```

**Use TCAdmin File Manager**:
```
HostHavoc Panel → File Manager
- Web-based upload
- More reliable for large files
- Max size varies
```

#### Startup Parameters Not Saving

**Problem**: Custom startup params reset

**Correct Method**:
```
1. TCAdmin → Configuration Files
2. Find "Commandline Customization"
3. Edit parameters
4. Save
5. Restart server

NOT via startup page!
```

**Parameter Format**:
```
-mod=@CF;@Expansion
-config=serverDZ.cfg
-port=2302
-profiles=ServerProfile
-dologs
-adminlog
-netlog
```

#### Billing/Technical Issues

**Problem**: Various account or technical problems

**Contact Support**:
```
HostHavoc Support:
- Live Chat (fastest)
- Support Ticket
- Email: support@hosthavoc.com

Include:
- Service ID
- Server name
- Issue description
- Screenshots if applicable
```

---

## GTXGaming

### Common Issues

#### Control Panel Won't Load

**Problem**: Can't access game panel

**Solutions**:

**Clear Browser Cache**:
```
1. Clear cache and cookies
2. Try incognito/private mode
3. Try different browser
4. Disable browser extensions
```

**Check Panel Status**:
```
GTX Status Page:
https://status.gtxgaming.co.uk/

If down: Wait for resolution
If up: Contact support
```

#### Mod Manager Not Working

**Problem**: Can't install mods via panel

**Workaround - Manual Install**:
```
1. Use FTP access
2. Download mods locally
3. Upload to: /dayz/mods/@ModName/
4. Copy keys
5. Edit startup in panel
```

**Alternative - SteamCMD**:
```
Some GTX packages include SteamCMD access:
1. SSH to server (if available)
2. Use steamcmd to download mods
3. Configure via panel
```

#### Database Not Accessible

**Problem**: Can't connect to MySQL

**GTX Database Info**:
```
Available in panel:
Database → MySQL Databases

Note:
- Host may be different from game server IP
- Port usually 3306
- Remote access may need enabling
```

---

## Self-Hosted (Dedicated/VPS)

### Common Issues

#### DayZ Server Won't Install

**Problem**: Server files won't download

**SteamCMD Method**:
```bash
# Linux
./steamcmd.sh +login anonymous +force_install_dir /path/to/server +app_update 223350 validate +quit

REM Windows
steamcmd +login anonymous +force_install_dir C:\DayZServer +app_update 223350 validate +quit
```

**Common Issues**:
```
- Insufficient disk space
- Permission errors (use sudo/admin)
- Network firewall blocking
- SteamCMD not updated
```

#### Port Forwarding Issues

**Problem**: Players can't connect

**Required Ports**:
```
Game Port: 2302 (UDP)
Query Port: 2303 (UDP)
Steam Port: 2304 (UDP)
RCON Port: 2310 (TCP) [if using]

Forward ALL of these!
```

**Router Configuration**:
```
1. Find router IP (usually 192.168.1.1)
2. Login to router admin
3. Find Port Forwarding section
4. Add rules for each port
5. Point to server local IP
6. Save and restart router
```

**Test Ports**:
```
Online tool: https://www.yougetsignal.com/tools/open-ports/

Or use: nmap [your-ip]
```

#### Linux Startup Script Issues

**Problem**: Server won't start automatically

**Systemd Service Example**:
```bash
# /etc/systemd/system/dayz-server.service

[Unit]
Description=DayZ Server
After=network.target

[Service]
Type=simple
User=dayz
WorkingDirectory=/home/dayz/server
ExecStart=/home/dayz/server/DayZServer -config=serverDZ.cfg -port=2302 -profiles=ServerProfile
Restart=always
RestartSec=10

[Install]
WantedBy=multi-user.target
```

**Enable Service**:
```bash
sudo systemctl daemon-reload
sudo systemctl enable dayz-server
sudo systemctl start dayz-server
sudo systemctl status dayz-server
```

#### Permission Errors

**Problem**: Script/file permission denied

**Fix Permissions**:
```bash
# Make server executable
chmod +x DayZServer

# Fix ownership
chown -R dayz:dayz /path/to/server

# Fix folder permissions
chmod -R 755 /path/to/server
```

---

## Comparison Matrix

### Features by Host

| Feature | Nitrado | G-Portal | HostHavoc | GTXGaming | Self-Host |
|---------|---------|----------|-----------|-----------|-----------|
| Web Panel | ✅ Easy | ✅ Easy | ✅ TCAdmin | ✅ Custom | ❌ DIY |
| Mod Manager | ✅ Yes | ✅ Yes | ⚠️ Limited | ⚠️ Basic | ❌ Manual |
| FTP Access | ✅ Yes | ✅ Yes | ✅ SFTP | ✅ Yes | ✅ Full |
| Auto-Update | ✅ Yes | ✅ Yes | ✅ Yes | ✅ Yes | ❌ Script |
| Backup | ✅ Auto | ✅ Auto | ✅ Auto | ✅ Manual | ❌ DIY |
| Database | 💰 Addon | 💰 Addon | ✅ Included | 💰 Addon | ✅ Full |
| Support | ✅ 24/7 | ✅ 24/7 | ✅ 24/7 | ✅ Ticket | ❌ Self |
| Price | 💰💰💰 | 💰💰 | 💰💰 | 💰💰 | 💰 |
| Performance | ⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐⭐⭐⭐ |

### Recommended For

**Nitrado**:
```
✅ Beginners
✅ Console migration
✅ Easy setup
❌ Cost-sensitive
```

**G-Portal**:
```
✅ European players
✅ Good value
✅ Multiple game support
❌ Advanced customization
```

**HostHavoc**:
```
✅ Performance-focused
✅ Database needs
✅ Custom configs
❌ Budget hosting
```

**GTXGaming**:
```
✅ UK/EU players
✅ Good support
✅ Competitive pricing
❌ Heavy modding
```

**Self-Hosted**:
```
✅ Full control
✅ Best performance
✅ Custom everything
❌ Beginners
❌ 24/7 availability
```

---

## Universal Tips (All Hosts)

### Before Contacting Support

**Gather Info**:
```
✓ Service ID / Server name
✓ Exact error message
✓ What you were doing
✓ What you've tried
✓ Screenshots
✓ Log files (last 50 lines)
```

### Common Solutions

**Most Issues Fixed By**:
```
1. Restart server (70%)
2. Verify mod files (15%)
3. Update everything (10%)
4. Contact support (5%)
```

### Best Practices

**Maintenance Schedule**:
```
Daily:
- Check server status
- Monitor player count
- Review quick logs

Weekly:
- Full log review
- Backup check
- Mod updates

Monthly:
- Performance review
- Cost analysis
- Player feedback
```

**Configuration Backups**:
```
Keep local copies of:
- serverDZ.cfg
- types.xml
- events.xml
- Custom configs
- Mod lists

Update when you make changes!
```

---

## Migration Between Hosts

### Steps to Migrate

**Preparation**:
```
1. Backup EVERYTHING:
   - All files via FTP
   - Database export
   - Configuration files
   - Player data

2. Document setup:
   - Mod list with IDs
   - Startup parameters
   - Custom configs
   - Database structure
```

**Migration Process**:
```
1. Order new host
2. Install same DayZ version
3. Upload files
4. Install mods (same versions!)
5. Configure settings
6. Import database
7. Test thoroughly
8. Update IP/DNS
9. Cancel old host
```

**Testing**:
```
Before going live:
- Test solo
- Test with team
- Verify all mods work
- Check performance
- Test database features
```

---

## Getting Maximum Value

### Cost Optimization

**Save Money**:
```
- Choose right slot count
- Annual > monthly pricing
- Reduce during low seasons
- Use coupons/promos
- Share costs with admins
```

**Performance per Dollar**:
```
Often better to:
- Start small, grow as needed
- Self-host if tech-savvy
- Use VPS over game host
- Buy more RAM vs more slots
```

### Support Utilization

**Get Fastest Support**:
```
1. Live chat (instant)
2. Priority ticket (12-24h)
3. Regular ticket (24-48h)
4. Forum/community (varies)
```

**Before Asking**:
```
✓ Check knowledge base
✓ Search community forums
✓ Try basic troubleshooting
✓ Gather all relevant info
```

---

**Pro Tip**: Join your hosting provider's Discord/community. Other customers often solve problems faster than support!

