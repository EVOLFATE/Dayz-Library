# Animals — Wolf Territories (Chernarus)

## Overview

This directory contains animal territory configurations for DayZ servers running on the **Chernarus** map. The file `wolf_territories-chernarus.xml` adds wolf spawn zones across the entire map, making wolves feel like a constant, dangerous presence — patrolling the coast, lurking near towns, and forming large, unpredictable packs in the wilderness. It provides **113 zones** across three territory types.

---

## File

| File | Description |
|------|-------------|
| `wolf_territories-chernarus.xml` | Wolf spawn territories for Chernarus — 100+ zones across three territory types |

---

## Territory Types

### 1. Coastal Wolves (color `1090519039` — blue)
Small roaming packs of 1–3 wolves that stalk beaches, cliffs, and docks along the **entire southern and eastern coastline**:
- Kamenka and Komarovo coasts
- Chernogorsk waterfront
- Elektrozavodsk coast
- Solnechiy and Berezino shore
- Svetloyarsk and Kamyshovo northeast coast
- Coastal villages and docks

**Settings:** `dmin="1" dmax="3"`, radius `r="150"` to `r="200"`

---

### 2. Near-Town Wolves (color `4278255615` — yellow/amber)
Packs of 2–4 wolves lurking on **forest edges and outskirts** near major towns. Wolves stay outside town perimeters, but close enough to ambush survivors:
- Chernogorsk, Elektrozavodsk, Berezino, Zelenogorsk
- Krasnostav, Severograd, Novodmitrovsk, Novaya Petrovka
- Novy Sobor, Stary Sobor, Vybor, Lopatino, Gorka, Polana

**Settings:** `dmin="2" dmax="4"`, radius `r="150"` to `r="200"`

---

### 3. Wilderness Large Packs (color `4278190335` — red/orange)
Large, dangerous packs in **remote wilderness, deep forests, mountain ridges, and far-from-town areas**. Some zones use `smin`/`smax` to activate only when player count thresholds are met — making solo server runs especially deadly.

**50 wilderness pack zones** covering:
- Tisy / northwest forest
- Black Forest / Myshkino
- Green Mountain hillsides
- Central wilderness and plateau
- Grozovoy Pass ridge
- Northeast remote forests
- East coast wilderness
- North map ridge

**Settings:** `dmin="6" dmax="12"` or `dmin="8" dmax="15"`, radius `r="300"` to `r="500"`
Some zones: `smin="4" smax="8"` (activates only with 4+ players online)

---

## How to Use

1. **Copy the XML file** to your server's mission environment folder:
   ```
   mpmissions/dayzOffline.chernarusplus/env/
   ```

2. **Rename it** to match your server's animal territory loading convention.  
   DayZ Expansion and vanilla servers typically load animal territories from a specific filename — check your mod documentation. Common names:
   - `animal_territories.xml`
   - `wolf_territories.xml`

3. **Restart your server.** Wolves will begin spawning in the defined zones on the next server cycle.

4. This file is **additive** — it does not replace any existing territory files. Add it alongside your zombie territory files safely.

---

## Customization

| Setting | Effect |
|---------|--------|
| Increase `dmax` | Larger packs per zone |
| Increase `r` | Bigger zone radius (wolves spawn further spread) |
| Set `smin`/`smax` | Zone only activates when player count is between these values |
| Change `color` | Visual distinction in map editors only — no gameplay effect |

---

## Zone Count Summary

| Territory Type | Zones | Pack Size |
|----------------|-------|-----------|
| Coastal wolves | 32 | 1–3 |
| Near-town wolves | 31 | 2–4 |
| Wilderness large packs | 50 | 6–15 |
| **Total** | **113** | — |

---

## Coordinate Reference

Chernarus coordinates:
- `x`: east–west (`0` = far west, `~15360` = far east)
- `z`: north–south (`0` = far south coast, `~15360` = far north)

---

## Related Files

- [`../../ZedLands/zombie_territories-ZedLands-REMASTERED.xml`](../../ZedLands/zombie_territories-ZedLands-REMASTERED.xml) — Zombie territory reference (same XML format)
- [`../../ZedLands/zombie_territories-ZedLands-SIMPLE.xml`](../../ZedLands/zombie_territories-ZedLands-SIMPLE.xml) — Simplified zombie territories
