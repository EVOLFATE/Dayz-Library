# Web Tools - README

Interactive HTML tools for DayZ modding and server administration.

## 🌐 Available Tools

### 1. Coordinate Converter

**File:** `coordinate-converter.html`

Convert between different coordinate systems used in DayZ:
- iZurvive map coordinates
- DayZ Editor coordinates (X, Y, Z)
- In-game script coordinates

**Features:**
- Support for all major maps (Chernarus+, Livonia, Sakhal, Namalsk, DeerIsle)
- Bidirectional conversion
- Generate EnScript code snippets
- Copy-to-clipboard functionality
- Responsive design

**Usage:**
1. Open the HTML file in any web browser
2. Select your map
3. Enter coordinates
4. Click convert
5. Copy the generated code

**Example Use Cases:**
- Find a location from iZurvive on your server
- Convert DayZ Editor coordinates to script format
- Generate spawn code for specific locations

### 2. Configuration Builder (Coming Soon)

**Planned Features:**
- Visual types.xml editor
- Event configuration wizard
- Trader setup assistant
- Server config generator

### 3. Loot Spawn Visualizer (Coming Soon)

**Planned Features:**
- Interactive map with loot spawn points
- Filter by item type and tier
- Export spawn configurations
- Import from existing configs

## 🚀 How to Use

### Option 1: Local Files

1. Download the HTML file
2. Open in your web browser (Chrome, Firefox, Edge, Safari)
3. No installation required - works offline

### Option 2: GitHub Pages

Visit the live versions:
- Coordinate Converter: `https://evolfate.github.io/Dayz-Library/tools/web/coordinate-converter.html`

### Option 3: Self-Host

If you want to host these tools on your own server:

```bash
# Simple HTTP server with Python
cd tools/web
python -m http.server 8000

# Or with Node.js
npx http-server -p 8000
```

Then visit `http://localhost:8000/coordinate-converter.html`

## 📱 Mobile Support

All web tools are mobile-responsive and work on:
- 📱 Smartphones
- 📱 Tablets
- 💻 Desktop browsers

## 🛠️ Development

### Adding New Tools

1. Create a new HTML file in `tools/web/`
2. Follow the design pattern of existing tools
3. Use the same color scheme and styling
4. Add responsive CSS
5. Update this README

### Style Guide

```css
/* Primary colors */
--primary: #667eea;
--secondary: #764ba2;
--success: #4caf50;
--warning: #ffc107;
--dark: #434343;
```

## 🤝 Contributing

Contributions welcome! Ideas for new tools:

- [ ] XML/JSON validator with visual feedback
- [ ] Server performance calculator
- [ ] Mod compatibility checker
- [ ] Discord webhook tester
- [ ] Backup schedule planner

## 📄 License

These tools are part of the DayZ Library project and follow the same MIT license.

## 🔗 Links

- [Main Documentation](../../README.md)
- [Issue Tracker](https://github.com/EVOLFATE/Dayz-Library/issues)
- [Contributing Guide](../../CONTRIBUTING.md)

---

**Last Updated:** January 2026  
**Status:** Active Development  
**Browser Support:** All modern browsers (Chrome, Firefox, Safari, Edge)
