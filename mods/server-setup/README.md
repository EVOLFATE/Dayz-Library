# DayZ Server Setup — Complete Merged Package

**This is a complete, drop-in, standalone server configuration** that merges all 5 mods so they
work together with a consistent post-apocalyptic survival vibe. Every file is a full replacement —
no partial merges, no editing required.

---

## The Vibe

> The world ended years ago. Civilization is a memory. Canned food is nearly extinct.
> Zombies roam everywhere — not just cities, but forests, roads, and open fields.
> Wildlife has reclaimed its territory. Vehicles litter every road, but almost none run.
> Fog walls drop without warning. The wilderness isn't safe anymore.

This package is tuned to deliver that experience consistently across every file.

---

## The 5 Mods Combined

| Mod | Folder |
|-----|--------|
| **Realistic Wildlife Overhaul** | `mods/animals/realistic-wildlife-overhaul` |
| **Post-Apocalyptic Loot Economy** | `mods/survival/post-apocalyptic-loot-economy` |
| **Realistic Vehicle Overhaul** | `mods/vehicles/realistic-vehicle-overhaul` |
| **Extreme Weather Console** | `mods/weather/extreme-weather-console` |
| **Realistic Everywhere Zeds** | `mods/zombies/realistic-everywhere-zeds` |

---

## Files in This Package

| File | What It Is |
|------|------------|
| `cfgeventspawns.xml` | Fixed map coordinates + animal territory refs + vehicle overhaul coords — ALL event spawn positions *(mission root)* |
| `cfgspawnabletypes.xml` | **24 types** — 8 vehicle loot configs + 16 zombie loot types (post-apoc tuned) *(mission root)* |
| `cfgweather.xml` | Extreme weather — fog walls, storm cycles, rare clear days *(mission root)* |
| `db/events.xml` | **63 events** — animals, ALL infected (with tuned nominals), static world events, foraging |
| `db/types.xml` | **1,390 items** — complete DayZ loot economy with vehicle overhaul values |
| `env/` | **14 territory files** — 13 animal + zombie_territories.xml (5,448 animal zones + 1,037 zombie zones) |

---

## Server Install Path

Copy the contents of `server-setup/` directly into your mission folder. Done.

```
mpmissions/dayzOffline.chernarusplus/
│
├── cfgweather.xml                ← server-setup/cfgweather.xml
├── cfgeventspawns.xml            ← server-setup/cfgeventspawns.xml
├── cfgspawnabletypes.xml         ← server-setup/cfgspawnabletypes.xml
│
├── db/
│   ├── events.xml                ← server-setup/db/events.xml
│   └── types.xml                 ← server-setup/db/types.xml
│
└── env/
    ├── bear_territories.xml
    ├── cattle_territories.xml
    ├── domestic_animals_territories.xml
    ├── fox_territories.xml
    ├── hare_territories.xml
    ├── hen_territories.xml
    ├── pig_territories.xml
    ├── red_deer_territories.xml
    ├── reindeer_territories.xml
    ├── roe_deer_territories.xml
    ├── sheep_goat_territories.xml
    ├── wild_boar_territories.xml
    ├── wolf_territories.xml
    └── zombie_territories.xml
```

---

## Zombie Spawn Coverage (`events.xml` — tuned for 1,037 zones)

The vanilla infected event nominals (50/50/50 for all types) were designed for a few dozen
vanilla zones. This setup has 1,037 territory zones. The nominals below are calibrated to
the actual zone count so the "zombies everywhere" vision actually works:

| Event | Zones | Nominal | Min | Max | Notes |
|-------|-------|---------|-----|-----|-------|
| `InfectedSolitude` | 708 | **250** | 50 | 500 | Wilderness grid — everywhere you go |
| `InfectedVillage` | 112 | **150** | 40 | 300 | Every farm, field, village |
| `InfectedVillageTier1` | 55 | **75** | 20 | 150 | Village outskirts density |
| `InfectedCity` | 40 | **150** | 30 | 300 | Cities overrun |
| `InfectedCityTier1` | 6 | **75** | 15 | 150 | Urban fringe density |
| `InfectedArmy` | 28 | **75** | 20 | 200 | Military zones are dangerous |
| `InfectedIndustrial` | 19 | **50** | 15 | 120 | Factories and ports |
| `InfectedPolice` | 10 | **25** | 8 | 60 | Police stations |
| `InfectedReligious` | 9 | **15** | 3 | 40 | Churches (rare) |
| `InfectedMedic` | 8 | **20** | 5 | 50 | Hospitals |
| `InfectedArmyHard` | 5 | **20** | 5 | 50 | Elite military zones |
| `InfectedNBC` | 5 | **10** | 3 | 25 | NBC/hazmat sites |
| `InfectedFirefighter` | 4 | **10** | 3 | 25 | Fire stations |
| `InfectedPrisoner` | 3 | **10** | 3 | 25 | Prison island |
| `InfectedMummy` | 25 | **15** | 3 | 30 | Rare ancient encounters |
| `InfectedPoliceHard` | (static events) | **15** | 3 | 40 | Triggered by StaticPoliceSituation |

Each infected event contains the **complete vanilla skin variant list** (all `ZmbM_*`/`ZmbF_*` children),
so every zone type spawns the correct mix of zombie models.

---

## Zombie Loot Tables (`cfgspawnabletypes.xml`)

Loot drops are tuned for **post-apocalyptic scarcity** — mostly rags and bandages, occasionally
something worth dying for:

| Type | What They Drop | Notes |
|------|----------------|-------|
| `InfectedCity` | Rag, bandage, purse, wallet, keys | 20% cargo chance — sparse city debris |
| `InfectedCityTier1` | Rag, bandage, canned food, plastic bottle | Slightly better odds |
| `InfectedVillage` | Rag, bandage, apple, kitchen knife | Rural survival gear |
| `InfectedVillageTier1` | Rag, canned food, apple, knife | Village scavenge |
| `InfectedSolitude` | Rag, bandage, matches, opened tuna | 10% cargo — wilderness wanderers carried almost nothing |
| `InfectedArmy` | Rag, bandage; rare: morphine, epinephrine, mil-mag | 35% block chance — most carry only basics |
| `InfectedArmyHard` | Same as army + grenade chance | 45% block chance — still mostly rags |
| `InfectedIndustrial` | Rag, bandage, screwdriver, pliers, wire | Workshop tools |
| `InfectedMedic` | Rag, bandage, morphine, tetracycline, amoxicillin | 40% block — medics had supplies, most are gone |
| `InfectedPolice` | Rag, bandage, handcuffs, pistol mag | 35% cargo chance |
| `InfectedPoliceHard` | Rag, bandage; separate: handcuffs, pistol mags | 50%/40% dual blocks — tactical police carry more |
| `InfectedFirefighter` | Rag, bandage; rare: firefighter axe | 20% cargo |
| `InfectedNBC` | Rag, bandage, tetracycline, atropine, gas mask | Contamination zone survivors |
| `InfectedReligious` | Rag, bandage, candle, paper, pen | 15% cargo — spiritual remnants, no weapons |
| `InfectedPrisoner` | Rag, bandage, rope, tattoo kit | 15% cargo — prison island scraps |
| `InfectedMummy` | Rag, bandage; ultra-rare: gold bar, old key, treasure map | 8% cargo — ancient artifacts if you're lucky |

---

## Wildlife Spawn Counts

| Animal | Nominal | Territory File | Zones |
|--------|---------|----------------|-------|
| Hare | 80 | `env/hare_territories.xml` | 1,896 |
| Hen | 60 | `env/hen_territories.xml` | 762 |
| Roe Deer | 50 | `env/roe_deer_territories.xml` | 312 |
| Red Deer | 35 | `env/red_deer_territories.xml` | 294 |
| Fox | 30 | `env/fox_territories.xml` | 360 |
| Wild Boar | 30 | `env/wild_boar_territories.xml` | 228 |
| Cattle | 25 | `env/cattle_territories.xml` | 252 |
| Domestic Animals | 25 | `env/domestic_animals_territories.xml` | 264 |
| Wolf | 20 | `env/wolf_territories.xml` | 324 |
| Sheep/Goat | 20 | `env/sheep_goat_territories.xml` | 204 |
| Pig | 20 | `env/pig_territories.xml` | 228 |
| Bear | 15 | `env/bear_territories.xml` | 192 |
| Reindeer | 15 | `env/reindeer_territories.xml` | 132 |
| White Wolf | 8 | (part of wolf territories) | — |

Wolf and bear territories overlap with prey zones by design — hunting in deer meadows means
wolves hunted there first.

---

## Loot Economy — 1,390 Items

Built from the full DayZ 1.28 vanilla item set (1,382 items) with 8 vehicle overhaul
type definitions replacing the vanilla vehicle entries.

**Post-apocalyptic tuning (all preserved from source mod):**
- Canned food: nominal 1–3 (nearly extinct)
- Most clothing: damaged/worn condition
- Repair materials dominate (rags, duct tape, sewing kits)
- Firearms: rare civilian, ultra-rare military
- Military gear: Tier3/Tier4 only
- Medical: rags common, morphine rare (nominal 1)

**Vehicle overhaul nominal counts (many cars, most broken):**

| Vehicle | Nominal | Key: Low Part Chances |
|---------|---------|----------------------|
| CivilianSedan | 30 | Battery 15%, SparkPlug 12%, Wheels 25% |
| OffroadHatchback | 25 | Same low part chances |
| HatchbackSedan | 20 | — |
| Sedan_02 | 20 | — |
| Truck_01_02 | 12 | — |
| CivilianSedan_Police | 8 | — |
| OffroadHatchback_Police | 6 | — |
| Sedan_02_Police | 6 | — |

High nominal counts mean you see cars everywhere. Low part attachment chances mean almost none
of them run. The ecosystem rewards scavenging multiple wrecks to build one working vehicle.

---

## Weather

Extreme weather from `cfgweather.xml`:
- ~5–10% of the time: Rare clear days (these feel like gifts)
- ~25–30% of the time: Fog walls — visibility collapses to metres
- ~30–35% of the time: Torrential rain and howling wind
- The rest: Heavy overcast, drizzle, poor visibility

Console/Nitrado compatible — no scripts, no mods required.

---

## Static World Events (in `events.xml`)

These vanilla DayZ world events are included and work alongside the mod content:

| Event | What Happens |
|-------|-------------|
| `StaticHeliCrash` | 3 crash sites across the map, guarded by `InfectedArmy` |
| `StaticContaminatedArea` | 2–4 dynamic contaminated zones |
| `StaticMilitaryConvoy` | 5 convoy wreck sites, guarded by `InfectedArmy` |
| `StaticPoliceSituation` | 5 police incident sites, guarded by `InfectedPoliceHard` |
| `StaticTrain` | 3 train wreck sites, guarded by `InfectedIndustrial` |
| `StaticAirplaneCrate` | 9 airplane supply crates |

These reinforce the post-apocalyptic atmosphere — crash sites, abandoned convoys, contaminated ruins.

---

## Foraging Events (in `events.xml`)

Fruits, mushrooms, and stones spawn naturally across the map. With food so scarce, foraging
matters. These vanilla trajectory events are included:

`TrajectoryApple`, `TrajectoryPear`, `TrajectoryPlum` — fruit trees  
`TrajectoryConiferous`, `TrajectoryDeciduous`, `TrajectoryHumus` — mushrooms  
`TrajectoryStones` — stones for crafting

---

## QC / Testing Checklist

Use this checklist before deploying to a live server. Run `validate.sh` first to catch XML
errors automatically, then work through the manual checks below.

### Automated (run `validate.sh`)

- [ ] All XML files are well-formed (valid XML syntax — no parse errors reported)

### Configuration cross-checks

- [ ] `types.xml` — every item has required fields: `nominal`, `min`, `lifetime`, `restock`, `category`, `usage`
- [ ] `events.xml` — every event `name` has a matching entry in `cfgeventspawns.xml`
- [ ] `cfgspawnabletypes.xml` — every `<type name="…">` references a name that exists in `types.xml`
- [ ] `cfgweather.xml` — all weather parameters are within valid DayZ ranges (`overcast`, `fog`, `rain` 0.0–1.0; `wind` ≥ 0)
- [ ] Territory files (`env/`) — all zone coordinates are within Chernarus map bounds (x/z: 0–15360)
- [ ] No duplicate `<type name="…">` entries across `types.xml` and `cfgspawnabletypes.xml`
- [ ] No duplicate `<event name="…">` entries in `events.xml`

### Live server validation

- [ ] Server loads without errors with this configuration
- [ ] Loot economy spawns as expected in-game (check a variety of building tiers)
- [ ] Animal spawns are functioning in defined territories
- [ ] Zombie spawns are active in all defined zones (city, village, solitude, army, etc.)

---

## License

All files are free to use on any DayZ server.
Credit to EVOLFATE/Dayz-Library appreciated but not required.
