# Realistic Everywhere Zeds

A **full replacement** zombie territory configuration mod for DayZ Chernarus. This mod delivers the full post-apocalyptic feel — zombies in the deep woods, random horde pockets, rare ancient mummies, and highly saturated coverage across the entire ~15,360×15,360m map.

---

## What This Mod Does

- **Zombies everywhere** — not just in towns. The entire map is covered by a 600m wilderness grid ensuring you will encounter infected wandering through forests, along ridgelines, and in remote valleys.
- **Random horde pockets** — 80 horde zones distributed unpredictably across the full map. Stumbling into one means facing 23–55 zombies in a concentrated area. Location varies enough that players cannot "learn the map" to avoid them.
- **Rare mummy encounters** — 25 special `InfectedMummy` zones placed at ruins, forgotten hilltops, derelict churches, and lost campsites. These zones spawn only 1–3 mummies each and only when a player is nearby. They are deliberate rare events, not common fodder.
- **Full civilian coverage** — All major Chernarus cities, towns, and villages covered. Tier-1 variant zones add density within settlement perimeters.
- **Road corridors** — Five road corridors (coast road, north highway, central road, NW forest road, east road) ensure you are never completely safe while traveling.
- **Industrial, military, specialty zones** — Full coverage of factories, airbases, military outposts, police stations, hospitals, churches, and NBC hazmat sites with appropriate infected types.

---

## File Inventory

| File | Purpose |
|---|---|
| `zombie_territories.xml` | **Full replacement** territory file — place as `env/zombie_territories.xml` |
| `cfgspawnabletypes.xml` | Companion spawnable types — merge into `db/cfgspawnabletypes.xml` |
| `README.md` | This documentation |

---

## Zone Count Summary

| Territory | Color Code | Zones | Primary Class |
|---|---|---|---|
| Village & City | `2809946700` | 122 | `InfectedCity`, `InfectedVillage` |
| Industrial | `3460713605` | 16 | `InfectedIndustrial` |
| Military | `3212836864` | 30 | `InfectedArmy`, `InfectedArmyHard` |
| Specialty | `2139062143` | 35 | `InfectedPolice`, `InfectedMedic`, `InfectedReligious`, `InfectedNBC`, `InfectedPrisoner`, `InfectedFirefighter` |
| Farm & Field | `1594180865` | 36 | `InfectedVillage` |
| Wilderness & Roads | `1910952871` | 693 | `InfectedSolitude` |
| Horde Pockets | `666013337` | 80 | `InfectedCity`, `InfectedVillage`, `InfectedSolitude` + mixed |
| Mummy Encounters | `4201337042` | 25 | `InfectedMummy` |
| **Total** | | **1,037** | |

---

## How to Install

### Step 1 — Territory File (Full Replacement)

Copy `zombie_territories.xml` to your mission's environment folder:

```
mpmissions/dayzOffline.chernarusplus/env/zombie_territories.xml
```

For custom missions:
```
mpmissions/<your_mission>/env/zombie_territories.xml
```

> ⚠️ **This is a full replacement file.** It completely replaces your existing `zombie_territories.xml`. Do not merge — replace.

### Step 2 — Spawnable Types (Companion File)

The `cfgspawnabletypes.xml` controls which specific zombie variants are chosen for each zone and what loot they carry.

**If you do not have an existing `cfgspawnabletypes.xml`:**

Copy the file directly:
```
mpmissions/<your_mission>/db/cfgspawnabletypes.xml
```

**If you already have a `cfgspawnabletypes.xml`:**

Open both files and merge the `<type>` blocks from this mod's file into your existing file. Add them inside the root `<cfgspawnabletypes>` element. Do not duplicate entries — if you already have a `<type name="InfectedCity">` block, use yours or selectively merge loot tables.

### Step 3 — Restart Server

Restart your server. Territory changes take effect on the next server start. No client-side mod is needed.

---

## Mummy Rarity Explained

Mummies are intentionally rare. The territory configuration for the mummy block uses:

```xml
<zone name="InfectedMummy" smin="0" smax="1" dmin="1" dmax="3" x="..." z="..." r="80"/>
```

- `smin="0" smax="1"` — at most 1 permanent mummy per zone
- `dmin="1" dmax="3"` — only 1–3 mummies spawn when a player is within 80m
- Only **25 zones** exist on the entire map
- Zones are at remote, unusual locations — ruins, forgotten hilltops, abandoned camps

This ensures mummies are genuine surprise encounters, not common enemies.

To **increase** mummy frequency (if desired), edit the mummy territory in `zombie_territories.xml` and increase `dmax` values, or increase the number of zones.

To **disable mummies entirely**, remove the `<territory color="4201337042">` block from `zombie_territories.xml`.

---

## Performance Notes

This mod is designed to be server-friendly despite 1,037 total zones:

- **Wilderness zones** use `smin="0" smax="0"` — zero permanent zombies. Dynamic spawning only activates when a player enters the zone radius.
- **600m grid spacing** with **350m radius** provides overlapping coverage with no gaps, but each zone is independently culled by DayZ's distance system.
- **Horde zones** are higher density but only 80 exist on the full 15km² map.
- **Mummy zones** are maximally sparse — 25 zones, 1–3 dynamic spawns each.
- DayZ's built-in distance culling means zones more than ~500m from any player have zero active cost.

### Performance Tuning Options

**For lower-end servers (reduce wilderness density):**

Edit `zombie_territories.xml`, find the `<territory color="1910952871">` block, and either:
- Remove every other `<zone>` line in the grid section (halves zone count)
- Reduce `r="350"` to `r="200"` (reduces overlap, same zone count but smaller activation radius)
- Reduce `dmax` values from `8` to `4` (fewer spawns per zone activation)

**For higher-end servers (increase density):**

- Reduce grid step from 600m to 400m (more zones, more coverage)
- Increase `dmax` on wilderness zones from `8` to `12`
- Increase horde zone `dmax` from `35` to `50`

---

## Optional Tuning Knobs

| What to change | Where | Effect |
|---|---|---|
| Horde intensity | `color=666013337` zones: change `dmax` | More/fewer zombies per horde |
| Horde count | Add/remove zones in `color=666013337` | More/fewer horde locations |
| Mummy rarity | `color=4201337042` zones: change `dmax` | More/fewer mummies per zone |
| Wilderness density | `color=1910952871` zones: change `dmax` | More/fewer forest wanderers |
| Road corridor density | Road corridor zones: change `dmax` | More/fewer roadside infected |
| Mummy loot | `cfgspawnabletypes.xml`: `InfectedMummy` cargo | What mummies drop |

---

## Zone Type Reference

| Class Name | Territory Use |
|---|---|
| `InfectedCity` | Cities, hordes |
| `InfectedCityTier1` | City outskirts, suburban zones |
| `InfectedVillage` | Villages, farms, hordes |
| `InfectedVillageTier1` | Village outskirts |
| `InfectedSolitude` | Forest grid, road corridors, some hordes |
| `InfectedArmy` | Military zones, some hordes |
| `InfectedArmyHard` | Elite military barracks |
| `InfectedIndustrial` | Factories, ports, sawmills |
| `InfectedMedic` | Hospitals, clinics |
| `InfectedPolice` | Police stations |
| `InfectedFirefighter` | Fire stations |
| `InfectedNBC` | Hazmat/contamination sites |
| `InfectedReligious` | Churches |
| `InfectedPrisoner` | Prison island, holding cells |
| `InfectedMummy` | Ancient ruins, forgotten places (rare) |

---

## License

Free to use on any DayZ server. Credit to EVOLFATE/Dayz-Library appreciated but not required.
