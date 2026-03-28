# 🎮 DayZ Mod Builder Tool

A fully self-contained, browser-based tool for generating DayZ server XML configuration files — no coding knowledge required.

**Location:** `tools/mod-builder/index.html`

---

## What Is It?

The DayZ Mod Builder is a visual, point-and-click interface that generates valid, ready-to-upload XML snippets and complete configuration files for DayZ servers. It's designed for both **PC** and **Console (Nitrado)** server owners.

Open `index.html` in any web browser — no install, no server, no internet required.

---

## How to Use

### Step 1 — Open the Tool
Download `index.html` and open it in any modern browser (Chrome, Firefox, Edge, Safari). No installation needed.

### Step 2 — Choose a Preset (Optional)
Use the **Presets** dropdown at the top to apply a pre-built server profile:
- 🟢 **Vanilla** — No changes, all values at default
- 🔵 **Casual PvE** — More animals and hunting gear, fewer military weapons
- 🟡 **Survival Hardcore** — Less loot, more dangerous wildlife
- 🔴 **PvP Loot Fest** — Heavy weapon and ammo spawns
- 🟣 **Hunter's Paradise** — Maxed animals and hunting gear
- ⚪ **Custom** — Start from scratch

### Step 3 — Adjust Settings by Tab
Navigate between the 6 tabs and adjust sliders, checkboxes, and inputs:

| Tab | What It Controls |
|-----|-----------------|
| 🐺 Animal Spawns | Wolf, bear, deer, boar and more spawn rates |
| 🔫 Weapons & Ammo | Weapon and ammunition spawn rates by category |
| 🏕️ Hunting & Survival | Hunting gear, traps, medical supplies |
| 🚁 Events Builder | Heli/plane crash sites, police cars, contaminated zones |
| 🧟 Zombie Density | Infected counts per zone type |
| 🏠 Spawn Hub Builder | Player spawn points and teleport hub system |

### Step 4 — Review the Live XML Preview
At the bottom of each tab, the **XML Output** updates in real time as you make changes.

### Step 5 — Copy or Download
- **📋 Copy XML** — Copies the XML to your clipboard
- **💾 Download XML** — Downloads the file with the correct filename

### Step 6 — Upload to Your Server
The **File Target** label tells you exactly where to upload each file on your server.

---

## Files Generated & Where to Upload

### PC Servers (custom missions folder)

| Tab | Generated File | Upload Location |
|-----|---------------|-----------------|
| Animal Spawns | `events.xml` | `/mpmissions/dayzOffline.chernarusplus/db/events.xml` |
| Weapons & Ammo | `types.xml` | `/mpmissions/dayzOffline.chernarusplus/db/types.xml` |
| Hunting & Survival | `types.xml` | `/mpmissions/dayzOffline.chernarusplus/db/types.xml` |
| Events Builder | `events.xml` + `cfgeventspawns.xml` | `/mpmissions/.../db/` |
| Zombie Density | `cfgeconomycore.xml` | `/mpmissions/dayzOffline.chernarusplus/cfgeconomycore.xml` |
| Spawn Hub | `cfgplayerspawnpoints.xml` | `/mpmissions/dayzOffline.chernarusplus/cfgplayerspawnpoints.xml` |

### Console Servers (Nitrado)

Nitrado console servers use a different file structure. Upload files through the Nitrado **Expert Mode** file browser:

| File | Nitrado Path |
|------|-------------|
| `types.xml` | `dayzps/missions/dayzOffline.chernarusplus/db/types.xml` |
| `events.xml` | `dayzps/missions/dayzOffline.chernarusplus/db/events.xml` |
| `cfgeconomycore.xml` | `dayzps/missions/dayzOffline.chernarusplus/cfgeconomycore.xml` |
| `cfgplayerspawnpoints.xml` | `dayzps/missions/dayzOffline.chernarusplus/cfgplayerspawnpoints.xml` |

> **Note:** Always back up existing files before uploading new ones.

---

## Tab Details

### 🐺 Animal Spawns
- Set a **multiplier** (0.5x–5x) for each animal species
- Check **Coastal only** to restrict an animal's spawn zone to Tier 1 coastal areas
- Generates `events.xml` entries with correct nominal/min/max values

### 🔫 Weapons & Ammo
- Apply a **global multiplier** to all weapons, or enable/disable specific categories
- Separate **ammo multiplier** for ammunition and magazines
- Generates `types.xml` with updated nominal values

### 🏕️ Hunting & Survival
- Three sub-sections: **Hunting Gear**, **Survival/Trapping**, **Medical**
- Each section has its own multiplier and individual item toggles
- Generates `types.xml` snippets

### 🚁 Events Builder
- **Helicopter Crash Sites** — Set number of sites, frequency, loot tier, and enter GPS coordinates
- **Plane Crash** — Same as heli with custom classname
- **Police Cars** — Set number of police car spawns
- **Contaminated Zone** — Enable with intensity and coordinates
- Generates both `events.xml` and `cfgeventspawns.xml`

### 🧟 Zombie Density
- **Global multiplier** affects all zone types
- **Per-zone sliders** for Residential, Military, Police, Medical, Industrial, Prison, Firefighter
- Generates `cfgeconomycore.xml`

### 🏠 Spawn Hub Builder
- Define a **central hub** where players spawn (great for Skalisty Island or Prison Island setups)
- Add up to 10 **destination zones** with names and coordinates
- Optional presets for Skalisty Island (Chernarus) and Prison Island (Livonia)
- **Starter Kit** toggle generates increased spawn of basic survival items
- Generates `cfgplayerspawnpoints.xml` AND a ready-to-post Discord player guide

---

## Presets Reference

| Preset | Animals | Weapons | Ammo | Hunting | Medical |
|--------|---------|---------|------|---------|---------|
| 🟢 Vanilla | 1x | 1x | 1x | 1x | 1x |
| 🔵 Casual PvE | 2x | 0.5x military | 1.5x | 2x | 1.5x |
| 🟡 Survival Hardcore | 3x wolves/bears | 0.5x | 0.5x | 0.5x | 1x |
| 🔴 PvP Loot Fest | 1x | 3x | 3x | 1x | 1x |
| 🟣 Hunter's Paradise | 4x | 1x | 3x | 4x | 2x |

---

## Validation Warnings

The tool will show warnings when:
- ⚠️ **Weapon nominal > 50** — May impact server performance
- ⚠️ **Animal multiplier > 4x** — Very high counts may cause server lag
- ⚠️ **No coordinates entered** — Events tab Download button is disabled until coordinates are added

---

## Limitations

### Console (Nitrado) Restrictions
- Console servers **cannot** use mods from the Steam Workshop
- Only vanilla classnames work on console — mod-added items will not work
- The `cfgeconomycore.xml` on Nitrado may have a different default path depending on your server version
- Always test changes on a development server before applying to live

### PC Server Notes
- PC servers running mods may have additional classnames not listed in this tool
- Custom mod classnames can be typed into the relevant fields as needed
- Always validate XML syntax before uploading — malformed XML will prevent server startup

### General Notes
- This tool generates **snippets** to merge into existing files, not complete replacement files
- When merging into `types.xml`, find the matching `<type name="...">` entry and replace it, or add new entries inside the `<types>` root element
- For `events.xml`, find and replace matching `<event name="...">` entries or add new ones inside `<events>`

---

## Contributing

Found a bug or want to add more classnames? See [CONTRIBUTING.md](../../CONTRIBUTING.md) for guidelines.

---

## Related Resources

- [Main Dayz-Library Documentation](../../README.md)
- [DayZ Official Wiki](https://community.bistudio.com/wiki/DayZ:Central_Economy_Configuration)
- [Nitrado DayZ Server Help](https://server.nitrado.net/en-US/guides/dayz)
- [DayZ Server Files Reference](../../docs/)

---

*Generated files include the comment `<!-- Generated by DayZ Mod Builder — EVOLFATE/Dayz-Library -->` for easy identification.*
