# ZedLands — Zombie Territory Configuration Pack

A comprehensive zombie territory configuration pack for DayZ Chernarus servers. ZedLands transforms the default sparse zombie experience into a truly post-apocalyptic world — zombies in the woods, on the roads, in the fields, and in terrifying random hordes.

---

## Overview

ZedLands provides two drop-in `zombie_territories` XML files that dramatically increase the realism, density, and immersion of the infected population across the full Chernarus map (~15360×15360m):

- **Zombies everywhere** — not just in towns, but in forests, fields, roads, farms, and hills
- **Organic zombie hordes** — random mega-horde zones scattered across the map for surprise encounters
- **Road corridor zones** — infected wandering along major highways and the coast road
- **Woodland blanket coverage** — systematic 800m grid of low-density forest zones
- **Performance-conscious design** — woodland zones use `dmin="2" dmax="6"` to minimize server load

---

## File Variants

### `zombie_territories-ZedLands-REMASTERED.xml`

The full-featured version. Recommended for servers wanting maximum immersion.

**Includes:**
- **Village & City zones** — All major Chernarus towns and cities with high-density `InfectedVillage` and `InfectedCity` spawns
- **Industrial zones** — Factories, power plants, ports, and quarries with `InfectedIndustrial`
- **Military zones** — All airfields, army bases, radar sites with `InfectedArmy` and `InfectedArmyHard`
- **Specialty zones** — Police stations, hospitals, and churches with `InfectedPolice`, `InfectedMedic`, and `InfectedReligious`
- **Farm & field zones** — Agricultural areas and open countryside with `InfectedVillage` (low density)
- **Woodland grid** — 337 zones covering the entire map at 800m intervals
- **Road corridors** — Coast road, north highway, and central road corridor zones
- **Horde zones** — 50 mega-horde zones distributed across the map

**Total zones: ~578**

### `zombie_territories-ZedLands-SIMPLE.xml`

A streamlined version focused on military zones with woodland and horde coverage layered on top. Recommended for servers that want a lighter touch on civilian areas but still want the "zombies everywhere" feel.

**Includes:**
- **Military zones only** — All airfields, bases, and outposts
- **Woodland grid** — Same 337 zones as REMASTERED
- **Road corridors** — Same corridor zones as REMASTERED
- **Horde zones** — Same 50 mega-horde zones as REMASTERED

**Total zones: ~480**

---

## Territory Color Key

| Color Code | Name | Description |
|---|---|---|
| `2809946700` | Village/City Territory | Primary civilian infected — villages, towns, and cities |
| `3460713605` | Industrial Territory | Factories, power plants, shipyards, and quarries |
| `3212836864` | Military Territory | Army bases, airfields, and military outposts |
| `2139062143` | Specialty Territory | Police, medical, and religious sites |
| `1594180865` | Farm/Field Territory | Agricultural areas and open countryside |
| `1910952871` | Woodland Territory | Forest roaming zones — entire map grid coverage |
| `666013337` | Horde Territory | Random mega-horde zones for surprise encounters |

---

## The Horde Zone System

The horde territory (`color="666013337"`) is the heart of ZedLands's organic feel. Fifty zones are scattered across the map — in forests, near roads, in fields, and on hills — using high spawn values:

```xml
<zone name="InfectedCity" smin="8" smax="20" dmin="15" dmax="30" x="..." z="..." r="200"/>
```

- **`smin`/`smax`**: 8–20 permanent zombies always present (static)
- **`dmin`/`dmax`**: 15–30 additional zombies spawned as players approach (dynamic)
- **`r`**: 150–300m radius — a sizable danger zone

When a player stumbles into a horde zone, they will encounter 23–50 zombies in a relatively small area. These are not tied to any named location — they exist as roaming population concentrations, simulating the organic spread of infection across the landscape.

---

## Woodland Coverage

The woodland grid uses a systematic 800m spacing across the full 15360×15360m Chernarus map:

```
Start: x=400, z=400
Step:  800m in both X and Z directions
End:   x=15000, z=15000
Skip:  Zones within 300m of major town centers
```

This produces **337 woodland zones**, each with `r="400"` for 400m radius coverage. With 800m spacing and 400m radius, zones overlap slightly to ensure no gaps in the forest.

**Spawn parameters:**
```xml
<zone name="InfectedSolitude" smin="0" smax="0" dmin="2" dmax="6" x="..." z="..." r="400"/>
```

- `smin="0" smax="0"` — no permanent zombies, dynamic only (server-friendly)
- `dmin="2" dmax="6"` — 2–6 zombies per zone when players are nearby

---

## Road Corridor Zones

Three major road corridors are covered with `r="120"` `InfectedSolitude` zones spaced every 600m:

| Road | Z-Band | Coverage |
|---|---|---|
| **Coast Road** | ~2000–2500 | x: 1000 to 14000 (22 zones) |
| **North Highway** | ~8500–9000 | x: 1500 to 14000 (21 zones) |
| **Central Road** | ~5500–6000 | x: 1500 to 14000 (21 zones) |

Road zones use slightly lower density than woodland: `dmin="2" dmax="5"` with `r="120"`.

---

## Installation

1. Copy your chosen file to your server's mission environment folder:

   ```
   mpmissions/dayzOffline.chernarusplus/env/zombie_territories.xml
   ```

   Or for custom missions:
   ```
   mpmissions/<your_mission>/env/zombie_territories.xml
   ```

2. Restart your server. The new territory configuration will take effect immediately.

> **Note:** DayZ typically only reads one `zombie_territories.xml` file per mission. Rename the file to `zombie_territories.xml` when deploying.

---

## Performance Notes

ZedLands is designed to be server-friendly despite its large number of zones:

- **Woodland zones** use `smin="0" smax="0"` — no static zombies are kept alive in empty areas
- **Dynamic spawning** (`dmin`/`dmax`) only activates when a player enters the zone radius
- **Low dmin/dmax** for woodland (2–6) and roads (2–5) means minimal active zombies in unpopulated areas
- The horde zones have higher values but only 50 exist on the entire map
- DayZ's built-in distance culling means distant zones have zero performance cost

For very performance-limited servers, you can reduce the woodland density by editing the `color="1910952871"` territory and removing every other `<zone>` entry, or reducing `r="400"` to `r="200"`.

---

## Zone Type Reference

| Class Name | Description |
|---|---|
| `InfectedCity` | Urban civilian infected — aggressive, fast |
| `InfectedVillage` | Rural civilian infected |
| `InfectedSolitude` | Isolated wandering infected — forest/road types |
| `InfectedArmy` | Military infected with army gear |
| `InfectedArmyHard` | Heavily armored military infected |
| `InfectedIndustrial` | Industrial worker infected |
| `InfectedMedic` | Medical staff infected |
| `InfectedPolice` | Police officer infected |
| `InfectedFirefighter` | Firefighter infected |
| `InfectedNBC` | Hazmat/NBC suit infected |
| `InfectedReligious` | Priest/clergy infected |
| `InfectedPrisoner` | Prison inmate infected |

---

## XML Attribute Reference

| Attribute | Description |
|---|---|
| `smin` / `smax` | Static (permanent) zombie count min/max — always present regardless of player proximity |
| `dmin` / `dmax` | Dynamic zombie count min/max — spawned as players approach the zone |
| `r` | Zone radius in meters |
| `x` / `z` | World coordinates (DayZ uses X/Z for the ground plane, not X/Y) |
| `name` | Zombie class name — must match a valid class registered in the mod |

---

## License

These configuration files are provided free to use for any DayZ server. Credit to EVOLFATE/Dayz-Library appreciated but not required.
