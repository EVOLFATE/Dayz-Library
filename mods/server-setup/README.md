# DayZ Server Setup — Combined 5-Mod Package

This folder contains **fully merged, standalone, drop-in replacement files** that combine all 5 mods so they work together on a single DayZ Chernarus+ server.

Every file is a **complete replacement** — no partial merges or additional editing required by you.

---

## What's Included

### Mods Combined

| Mod | Folder | What It Adds |
|-----|--------|--------------|
| **Realistic Wildlife Overhaul** | `animals/realistic-wildlife-overhaul` | 13 animal spawn events + 12 territory files |
| **Post-Apocalyptic Loot Economy** | `survival/post-apocalyptic-loot-economy` | Full 1,282-item loot overhaul |
| **Realistic Vehicle Overhaul** | `vehicles/realistic-vehicle-overhaul` | 7 vehicle events + 8 vehicle types + spawn coordinates |
| **Extreme Weather Console** | `weather/extreme-weather-console` | Aggressive fog/rain/wind weather cycles |
| **Realistic Everywhere Zeds** | `zombies/realistic-everywhere-zeds` | 15 zombie types + territory coverage across the whole map |

---

## Files in This Folder

| File | Merged From | Description |
|------|-------------|-------------|
| `events.xml` | Animals + Vehicles | 13 animal events + 7 vehicle events |
| `cfgeventspawns.xml` | Animals + Vehicles | Animal territory mappings + ~105 vehicle spawn coordinates |
| `cfgspawnabletypes.xml` | Vehicles + Zombies | 8 vehicle part/cargo configs + 15 zombie loot configs |
| `types.xml` | Loot Economy + Vehicles | Full 1,282-item loot economy + 8 vehicle type definitions |
| `cfgweather.xml` | Weather (standalone) | Extreme weather config, copied as-is |
| `env/` | Animals + Zombies | 12 animal territory files + 1 zombie territory file |

---

## Server Install Instructions

All files install into your mission folder:

```
mpmissions/dayzOffline.chernarusplus/
```

### Full Folder Structure

```
mpmissions/dayzOffline.chernarusplus/
├── cfgweather.xml                         ← server-setup/cfgweather.xml
├── db/
│   ├── events.xml                         ← server-setup/events.xml
│   ├── cfgeventspawns.xml                 ← server-setup/cfgeventspawns.xml
│   ├── cfgspawnabletypes.xml              ← server-setup/cfgspawnabletypes.xml
│   └── types.xml                          ← server-setup/types.xml
└── env/
    ├── bear_territories.xml               ← server-setup/env/bear_territories.xml
    ├── cattle_territories.xml             ← server-setup/env/cattle_territories.xml
    ├── domestic_animals_territories.xml   ← server-setup/env/domestic_animals_territories.xml
    ├── fox_territories.xml                ← server-setup/env/fox_territories.xml
    ├── hare_territories.xml               ← server-setup/env/hare_territories.xml
    ├── hen_territories.xml                ← server-setup/env/hen_territories.xml
    ├── pig_territories.xml                ← server-setup/env/pig_territories.xml
    ├── red_deer_territories.xml           ← server-setup/env/red_deer_territories.xml
    ├── roe_deer_territories.xml           ← server-setup/env/roe_deer_territories.xml
    ├── sheep_goat_territories.xml         ← server-setup/env/sheep_goat_territories.xml
    ├── wild_boar_territories.xml          ← server-setup/env/wild_boar_territories.xml
    ├── wolf_territories.xml               ← server-setup/env/wolf_territories.xml
    └── zombie_territories.xml             ← server-setup/env/zombie_territories.xml
```

> **Nitrado servers**: The mission path is typically `dayzps/missions/dayzOffline.chernarusplus/`

---

## How to Install

1. **Back up** your existing mission folder first.
2. Copy each file from `server-setup/` to the matching path on your server (see table above).
3. Replace the originals entirely — these are **full replacement files**, not patches.
4. Restart your server.

---

## Merge Details

### `events.xml`
- **Animal events first**, then vehicle events — both within a single `<events>` root.
- 13 animal events (AnimalHare, AnimalRoeDeer, AnimalRedDeer, AnimalWildBoar, AnimalHen, AnimalCow, AnimalSheepGoat, AnimalPig, AnimalDomestic, AnimalFox, AnimalWolf, AnimalWolf_White, AnimalBear).
- 7 vehicle events (VehicleCivilianParking, VehicleRoadsideBreakdown, VehicleGasStation, VehicleIndustrial, VehiclePoliceCheckpoint, VehicleRuralFarm, VehicleHighway).

### `cfgeventspawns.xml`
- Animal entries use `<file>` references pointing to the `env/` territory files.
- Vehicle entries use fixed `<pos x= z= a=>` coordinate sets (~105 positions spread across Chernarus+).
- All coordinate data is preserved exactly as authored.

### `cfgspawnabletypes.xml`
- **Vehicle types first** (8 types with part/attachment/cargo tables), then **zombie types** (15 infected variants with loot tables).
- No name conflicts — vehicle type names and zombie type names are entirely different.

### `types.xml`
- The Post-Apocalyptic Loot Economy file (651 KB, ~1,282 item types) does **not** contain vanilla vehicle entries, so there are no conflicts.
- All 1,282 loot economy items are included in full.
- The 8 vehicle overhaul type definitions are appended at the end with their custom nominal counts and spawn zone assignments.

### `cfgweather.xml`
- Copied directly from `weather/extreme-weather-console/cfgweather.xml` with no changes.

### `env/` territory files
- 12 animal territory files copied from `animals/realistic-wildlife-overhaul/env/`.
- `zombie_territories.xml` copied from `zombies/realistic-everywhere-zeds/`.
- All files kept exactly as authored — no modifications.

---

## Nominal Counts at a Glance

### Animals (on map at any time)
| Animal | Nominal |
|--------|---------|
| Hare | 80 |
| Hen | 60 |
| Roe Deer | 50 |
| Red Deer | 35 |
| Fox | 30 |
| Wild Boar | 30 |
| Cattle | 25 |
| Domestic Animals | 25 |
| Wolf | 20 |
| Sheep/Goat | 20 |
| Pig | 20 |
| Bear | 15 |
| White Wolf | 8 |

### Vehicles (on map at any time)
| Event | Nominal |
|-------|---------|
| Civilian Parking | 20 |
| Roadside Breakdown | 18 |
| Highway | 16 |
| Rural Farm | 14 |
| Gas Station | 12 |
| Industrial | 10 |
| Police Checkpoint | 8 |

### Vehicles (types pool)
| Type | Nominal |
|------|---------|
| CivilianSedan | 30 |
| OffroadHatchback | 25 |
| HatchbackSedan | 20 |
| Sedan_02 | 20 |
| Truck_01_02 | 12 |
| CivilianSedan_Police | 8 |
| OffroadHatchback_Police | 6 |
| Sedan_02_Police | 6 |
