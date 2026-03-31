# Realistic Wildlife Overhaul

A **full replacement** wildlife configuration mod for DayZ Chernarus+. This mod
makes the world feel truly alive — animals are present across the entire map, not
just hidden in the far-north forests like vanilla. Wildlife is the backbone of
survival on this server, and this mod makes hunting a reliable, rewarding, and
occasionally dangerous activity everywhere you go.

---

## What This Mod Does

### Prey Animals — Widespread and Huntable

- **Hares** everywhere — fields, forest edges, coastlines, village outskirts.
  Fresh spawns on the coast can find food immediately. 80 active on map at once.
- **Roe Deer** across all rural and forested areas — 50 active, the reliable
  everyday hunting target.
- **Red Deer** in inland meadows, large clearings, and river valleys — 35 active,
  bigger animal, bigger meat reward.
- **Wild Boar** in woodland floors, oak groves, and farmland edges — 30 active,
  they fight back so come prepared.

### Farm Animals — At Every Settlement

- **Hens/Chickens** at every farm and village — 60 active, feathers for arrows
  and easy early-game meat.
- **Cattle** at farms and wandering fields — 25 active, large meat haul.
- **Sheep & Goats** on farms and hillsides — 20 active, some feral on rocky terrain.
- **Pigs** at farms, some feral near forests — 20 active.
- **Domestic Animals** mixed near villages — 25 active, general settlement fauna.

### Predators — A Constant Threat

- **Foxes** on forest edges and near farms — 30 active. They hunt hens and hares
  so their territories deliberately overlap with prey areas.
- **Wolves** across the **ENTIRE MAP** — 20 active packs (vs. vanilla's 8,
  all in the far north). Coastal wolves, forest packs, mountain packs. Pack sizes
  range from 2-3 scouts to 8-12 mega-packs for variety and terror.
  White wolves additionally patrol northern forests and mountain ridges.
- **Bears** map-wide — 15 active (vs. vanilla's ~5-6 in just the far north).
  Bears follow food sources: rivers (salmon), forest (berries), farms (livestock).
  Post-apocalypse boldness means they range further south than before.

### Ecosystem Design

Wolf and bear territories are **deliberately placed to overlap** with deer, boar,
and hare territories. This creates emergent ecosystem behavior — hunt in the same
areas as the predators do, and you'll encounter them.

---

## File Inventory

| File | Purpose | Install Path |
|------|---------|--------------|
| `events.xml` | Animal spawn events (counts, pack sizes, lifetimes) | `db/events.xml` |
| `cfgeventspawns.xml` | Registers events for territory-based spawning | `cfgeventspawns.xml` |
| `env/hare_territories.xml` | Hare behavior zones — entire map | `env/hare_territories.xml` |
| `env/roe_deer_territories.xml` | Roe deer zones — rural/forest | `env/roe_deer_territories.xml` |
| `env/deer_territories.xml` | Red deer zones — inland/meadows | `env/deer_territories.xml` |
| `env/wild_boar_territories.xml` | Wild boar zones — woodland | `env/wild_boar_territories.xml` |
| `env/hen_territories.xml` | Hen zones — settlements/farms | `env/hen_territories.xml` |
| `env/cow_territories.xml` | Cattle zones — farms/fields | `env/cow_territories.xml` |
| `env/sheep_territories.xml` | Sheep zones — farms/hills | `env/sheep_territories.xml` |
| `env/goat_territories.xml` | Goat zones — farms/hills | `env/goat_territories.xml` |
| `env/pig_territories.xml` | Pig zones — farms/forest edges | `env/pig_territories.xml` |
| `env/domestic_animals_territories.xml` | Domestic animal zones — villages | `env/domestic_animals_territories.xml` |
| `env/fox_territories.xml` | Fox zones — forest edges/farms | `env/fox_territories.xml` |
| `env/wolf_territories.xml` | Wolf zones — entire map | `env/wolf_territories.xml` |
| `env/bear_territories.xml` | Bear zones — rivers/forests/farms | `env/bear_territories.xml` |
| `env/reindeer_territories.xml` | Reindeer zones — far north wilderness | `env/reindeer_territories.xml` |

---

## How to Install

> ⚠️ **These are full replacement files.** They completely replace the vanilla
> versions. Do NOT merge — replace.

### Console Server Admins (PS4/Xbox/Console)

On console servers using the DayZ server management interface:

1. Navigate to your mission file manager
2. Open `mpmissions/dayzOffline.chernarusplus/db/`
3. Upload `events.xml` from this mod — this replaces the vanilla file
4. Navigate to `mpmissions/dayzOffline.chernarusplus/` (mission root)
5. Upload `cfgeventspawns.xml` from this mod — this replaces the vanilla file
6. Navigate to `mpmissions/dayzOffline.chernarusplus/env/`
7. Upload ALL files from this mod's `env/` folder, replacing any existing files
8. Restart your server — changes take effect on the next server start

> **Note for console:** If your server manager requires you to edit files one at
> a time, copy the XML content from each file and paste it into your server's
> file editor for that path.

### PC/Steam Server Admins

```
YourServerFolder/
└── mpmissions/
    └── dayzOffline.chernarusplus/
        ├── db/
        │   └── events.xml              ← replace with mod's events.xml
        ├── cfgeventspawns.xml          ← replace with mod's cfgeventspawns.xml
        └── env/
            ├── hare_territories.xml              ← replace
            ├── roe_deer_territories.xml           ← replace
            ├── deer_territories.xml               ← replace
            ├── wild_boar_territories.xml          ← replace
            ├── hen_territories.xml                ← replace
            ├── cow_territories.xml                ← replace
            ├── sheep_territories.xml              ← replace
            ├── goat_territories.xml               ← replace
            ├── pig_territories.xml                ← replace
            ├── domestic_animals_territories.xml   ← replace
            ├── fox_territories.xml                ← replace
            ├── reindeer_territories.xml           ← replace
            ├── wolf_territories.xml               ← replace
            └── bear_territories.xml               ← replace
```

### Custom Mission Name

If your mission folder is not `dayzOffline.chernarusplus`, replace it with your
mission folder name (e.g., `mpmissions/MyCustomMission.chernarusplus/`).

---

## Spawn Counts Reference

| Animal | Nominal | Min | Max | Group Size | Notes |
|--------|---------|-----|-----|------------|-------|
| Hare | 80 | 50 | 120 | 1-3 | Everywhere |
| Roe Deer | 50 | 30 | 70 | 2-5 | Rural/forest |
| Red Deer | 35 | 20 | 50 | 3-8 (♂) + 1-4 (♀) | Inland/meadows |
| Wild Boar | 30 | 18 | 45 | 3-8 | Woodland |
| Hen | 60 | 35 | 90 | 3-6 | Settlements |
| Cattle | 25 | 12 | 38 | 2-5 | Farms/fields |
| Sheep/Goat | 20 | 10 | 32 | 3-6 | Farms/hills |
| Pig | 20 | 10 | 30 | 2-5 | Farms |
| Domestic | 25 | 12 | 38 | 2-4 | Villages |
| Fox | 30 | 18 | 45 | 1-3 | Forest edges/farms |
| Wolf | 20 | 12 | 30 | 2-12 (mixed) | Entire map |
| Wolf (White) | 8 | 4 | 12 | 2-5 | North forests |
| Bear | 15 | 8 | 22 | 1-2 | Rivers/forests |
| Reindeer | 15 | 8 | 25 | 2-8 | Far north/wilderness |

---

## Compatibility

- **Map:** Chernarus+ (`dayzOffline.chernarusplus`)
- **Compatible with console:** Yes — all files are standard vanilla XML formats
- **Compatible with:** DayZ 1.23+ (territory file format unchanged since 1.0)
- **Conflicts with:** Any other mod that replaces `events.xml`, `cfgeventspawns.xml`,
  or any of the listed `env/` territory files. Use one wildlife mod at a time.

---

## Tuning Guide

### Server Performance

All territory zones use `smin="0" smax="0"` — zero permanent spawns — so only
zones within player range become active. The server will not be loaded by animals
in unpopulated areas.

**For lower-end servers (reduce spawn counts):**

- In `events.xml`, lower `nominal` and `max` values by ~30%
- Example: `AnimalHare` from nominal=80 to nominal=55

**For higher-end servers (increase density):**

- Increase `nominal` by up to 50%
- Decrease `saferadius` values to allow more spawn points to be used

### Adjusting Predator Danger

**Make wolves less threatening:**

- In `events.xml`, remove the `max="12" min="8"` children entry from `AnimalWolf`
- Lower nominal from 20 to 12-15

**Make wolves more terrifying:**

- Increase nominal to 25-30
- Increase max pack size to 15

**Adjust bear range:**

- In `bear_territories.xml`, remove the southern territory groups
- Or add more by duplicating existing blocks with new coordinates

---

## Spawn Radius Reference

These values control when animals spawn relative to players and how far they
must travel before they despawn. `saferadius` = minimum spawn distance from a
player; `cleanupradius` = despawn distance (must always be larger).

**Rule:** `cleanupradius` must always be greater than `saferadius`. If they are
equal or reversed, animals are immediately despawned — a silent zero-spawn bug.

**Predator design note:** Wolves and bears have a large `saferadius` on purpose.
This ensures they always appear at a realistic detection distance — players will
*hear* wolves howling or *spot* a bear before it closes in, giving time to
react. This makes predators harder and more realistic, not invisible gotchas.

| Animal | saferadius | cleanupradius | Notes |
| ------ | ---------- | ------------- | ----- |
| Hare | 50 | 800 | Spawns very close — everywhere |
| Roe Deer | 100 | 800 | Spawns close, persists far |
| Red Deer | 150 | 800 | |
| Wild Boar | 100 | 800 | |
| Hen | 50 | 600 | Settlement animal |
| Cattle | 150 | 800 | |
| Sheep/Goat | 100 | 800 | |
| Pig | 100 | 800 | |
| Domestic | 100 | 800 | |
| Fox | 80 | 800 | |
| **Wolf** | **500** | **1000** | Heard before seen — 500 m buffer |
| **Wolf (White)** | **600** | **1000** | Extra distance — apex north predator |
| **Bear** | **700** | **1000** | 700 m buffer — see/hear before charge |
| Reindeer | 150 | 800 | |

---

## Zone Count Summary

| Territory File | Territories | Total Zones | Zone Types |
| -------------- | ----------- | ----------- | ---------- |
| hare_territories.xml | 1 | 1896 | Water, Rest, Graze |
| roe_deer_territories.xml | 1 | 312 | Water, Rest, Graze |
| deer_territories.xml | 1 | 294 | Water, Rest, Graze |
| wild_boar_territories.xml | 1 | 228 | Water, Rest, HuntingGround |
| hen_territories.xml | 1 | 762 | Water, Rest, Graze |
| cow_territories.xml | 1 | 252 | Water, Rest, Graze |
| sheep_territories.xml | 1 | 204 | Water, Rest, Graze |
| goat_territories.xml | 1 | 204 | Water, Rest, Graze |
| pig_territories.xml | 1 | 228 | Water, Rest, HuntingGround |
| domestic_animals_territories.xml | 1 | 264 | Water, Rest, Graze |
| fox_territories.xml | 1 | 360 | Water, Rest, HuntingGround |
| reindeer_territories.xml | 1 | 132 | Water, Rest, Graze |
| wolf_territories.xml | 1 | 324 | Water, Rest, HuntingGround |
| bear_territories.xml | 1 | 192 | Water, Rest, HuntingGround |

---

## Design Philosophy

This mod was built around a server where **hunting is the primary food source**.
Canned food and item-spawned nutrition are reduced, so players *must* hunt to
survive. That required:

1. **Prey must be reliable, not just occasional:** Hares and roe deer are
   everywhere so no region of the map is a food desert.
2. **Hunting must be rewarding:** Red deer and boar offer big meat payoffs for
   skilled hunters.
3. **Predators follow prey:** Wolves and bears are placed near prey territories
   so the ecosystem feels coherent. Chase deer in the forest? Wolves are there too.
4. **Post-apocalyptic boldness:** Wolves and bears no longer avoid humans the way
   they did before the outbreak. They've been the dominant predator for months.
   Coastal wolves, bears near farms — they go where the food is.
5. **Atmosphere:** Foxes near henhouses, hares everywhere, cattle in fields —
   the world feels alive even when no players are nearby.

---

## License

Free to use on any DayZ server. Credit appreciated but not required.
