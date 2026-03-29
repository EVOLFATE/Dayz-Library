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
| `cfgeconomycore.xml` | CE engine configuration — registers `db/` folder so events, globals, and types are loaded *(mission root)* |
| `cfgeventspawns.xml` | Fixed map coordinates + animal territory refs + vehicle overhaul coords — ALL event spawn positions *(mission root)* |
| `cfgspawnabletypes.xml` | **24 types** — 8 vehicle loot configs + 16 zombie loot types (post-apoc tuned) *(mission root)* |
| `cfgweather.xml` | Extreme weather — fog walls, storm cycles, rare clear days *(mission root)* |
| `db/events.xml` | **63 events** — animals, ALL infected (with tuned nominals), static world events, foraging |
| `db/types.xml` | **1,390 items** — complete DayZ loot economy with vehicle overhaul values |
| `env/` | **14 territory files** — 13 animal + zombie_territories.xml (5,448 animal zones + 1,037 zombie zones) |

---

## Server Install Path

Copy the contents of `server-setup/` directly into your mission folder.

> ⚠️ **cfgeconomycore.xml is REQUIRED** — this file tells the DayZ Central Economy engine
> where to find `events.xml`, `globals.xml`, and `types.xml`. Without it, the CE engine
> won't load ANY of your custom files — resulting in no zombies, no animals, and no vehicles.
> If you already have a `cfgeconomycore.xml`, ensure it contains the `<ce folder="db">` block.

> ✅ **globals.xml is now included** — `server-setup/db/globals.xml` ships with all required
> values pre-configured (`ZombieMaxCount=5000`, `VehicleMaxCount=250`, `AnimalMaxCount=2000`).
> Simply copy it along with the other files — no manual editing required.
>
> If you already have a customised `globals.xml` on your server, merge in these key values:
> - `ZombieMaxCount` → **5000** (vanilla 800 silently starves all zombie zones)
> - `VehicleMaxCount` → **250** (vanilla 2–10 caps total cars across the entire map)

```
mpmissions/dayzOffline.chernarusplus/
│
├── cfgeconomycore.xml            ← server-setup/cfgeconomycore.xml   ← NEW (REQUIRED)
├── cfgweather.xml                ← server-setup/cfgweather.xml
├── cfgeventspawns.xml            ← server-setup/cfgeventspawns.xml  ← UPDATED
├── cfgspawnabletypes.xml         ← server-setup/cfgspawnabletypes.xml
│
├── db/
│   ├── events.xml                ← server-setup/db/events.xml       ← UPDATED
│   ├── globals.xml               ← server-setup/db/globals.xml      ← INCLUDED (pre-configured)
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

## Zombie Spawn Coverage (`events.xml` — tuned for 919 territory zones + rolling horde events)

The vanilla infected event nominals (50/50/50 for all types) were designed for a few dozen
vanilla zones. This setup has 919 territory zones. The nominals below are calibrated to
the actual zone count so the "zombies everywhere" vision actually works:

**Realism gradient:** Cities → highest density, urban civilians. Villages → moderate density,
rural civilians. Wilderness → sparse, hikers/hunters/hermits only. Specialty locations →
matching types (soldiers at bases, doctors at hospitals). Hordes → dramatic timer-based
EVENT encounters, not permanent territory blobs.

| Event | Zones | Nominal | Min | Max | Notes |
|-------|-------|---------|-----|-----|-------|
| `InfectedVillage` | 112 | **1450** | 725 | 2175 | Villages — rural civilians, noticeable but stealthable |
| `InfectedVillageTier1` | 55 | **530** | 265 | 800 | Village outskirts |
| `InfectedArmy` | 28 | **390** | 195 | 585 | Military zones |
| `InfectedCity` | 40 | **900** | 450 | 1350 | Cities — urban civilians, populated but gaps exist |
| `InfectedSolitude` | 693 | **500** | 250 | 750 | Wilderness — sparse; hikers/hunters/hermits only |
| `InfectedIndustrial` | 19 | **250** | 125 | 375 | Factories and ports |
| `InfectedCityTier1` | 6 | **155** | 78 | 235 | Urban fringe |
| `InfectedArmyHard` | 5 | **70** | 35 | 105 | Elite military zones |
| `InfectedPrisoner` | 3 | **70** | 35 | 105 | Prison island |
| `InfectedMedic` | 8 | **35** | 18 | 70 | Hospitals |
| `InfectedPolice` | 10 | **35** | 7 | 70 | Police stations |
| `InfectedNBC` | 5 | **35** | 7 | 70 | NBC/hazmat sites |
| `InfectedFirefighter` | 4 | **35** | 18 | 70 | Fire stations |
| `InfectedReligious` | 9 | **35** | 18 | 70 | Churches |
| `InfectedMummy` | 25 | **35** | 18 | 70 | Rare ancient encounters |
| `InfectedPoliceHard` | (static events) | **15** | 3 | 40 | Triggered by StaticPoliceSituation |
| `StaticZombieHorde` | (fixed event) | **8** | 4 | 12 | 8 active hordes from 118-position pool — see below |

> **Note:** Total nominal across all infected territory types ≈ 4,060. The 8 active horde events
> each pull additional InfectedCity zombies via `secondary=` (controlled by the `<zone>` density
> in `cfgeventspawns.xml`). `globals.xml` ships with `ZombieMaxCount=5000` to let the full
> budget be active simultaneously. The vanilla default of 800 silently starves higher-tier zones.

### Zombie Horde Events (`StaticZombieHorde`)

Works **exactly like a helicrash** — a timer-based rolling event, not a permanent zone:

- **8 hordes active** at any given moment across the entire map
- Each horde **lives for 30 minutes** (`lifetime=1800`), then despawns and immediately
  respawns at a **new random location** chosen from a pool of **118 possible positions**
- `init_random=1` — positions are randomised on every server start; you never know where
  they'll be
- A wrecked abandoned car (`Land_Wreck_sed01_aban1`) marks the horde centre; `InfectedCity`
  zombies swarm around it with `smin=5 smax=10 dmin=20 dmax=35` at `r=200m`
- **No budget waste** — the 117 inactive positions cost nothing; only the 8 active sites
  draw from `ZombieMaxCount`
- The "oh no" factor: stumble into a horde site and you're surrounded; come back 30 minutes
  later and it's gone, moved somewhere else on the map

**Spawn distance tuning (all infected events):**

| Field | Value | What It Does |
|-------|-------|-------------|
| `saferadius` | **150m** | Zombies cannot spawn within 150m of you — your clear planning bubble |
| `distanceradius` | **80m** | Zombies spawn in the **150m–230m ring** around you — visible at distance before they're close |
| `cleanupradius` | **300m** | Zombies persist until you're 300m away — well beyond the 230m spawn edge, so newly spawned zombies don't instantly despawn |

> **Zombie AI aggro range** (how far they *see you*) is hardcoded in the DayZ engine — not
> configurable from mission files. Vanilla sight range is ~50–80m; crouching reduces your
> detectable footprint significantly. Route-planning benefit: with the 150m spawn bubble,
> you can observe the 150–230m ring before committing to a path.

**Horde zone system (`zombie_territories.xml`):** 118 zones in the horde territory
(color=666013337), up from 80 — covering road chokepoints, bridge approaches, gas stations,
between-town corridors, and forest clearings across the full map. Horde density raised to
`smin="12" smax="30" dmin="30" dmax="65"` for intense, memorable encounters.

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

**Animal saferadius/cleanupradius (after fix — animals now spawn near players):**

| Animal | saferadius | cleanupradius | Notes |
|--------|-----------|---------------|-------|
| Hare | **50** | **800** | Spawn close, persist far |
| Hen | **50** | **600** | Settlement flocks visible to players |
| Roe Deer | **100** | **800** | Common prey, close encounters |
| Red Deer | **150** | **800** | Mid-range reward prey |
| Wild Boar | **100** | **800** | Close forest encounters |
| Fox | **80** | **800** | Near settlements and fields |
| Cow | **150** | **800** | Farm herds visible from roads |
| Sheep/Goat | **100** | **800** | Hillside and farm flocks |
| Pig | **100** | **800** | Farm and feral groups |
| Domestic | **100** | **800** | Mixed village animals |
| Reindeer | **150** | **800** | Northern wilderness herds |
| Wolf | **500** | **1000** | Vanilla saferadius — fair warning distance for packs |
| White Wolf | **600** | **1000** | Northern ghost packs |
| Bear | **700** | **1000** | Visible apex predator |

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

**Drivable vehicles — managed by `VehicleCivilianParking`, `VehicleRoadsideBreakdown`,
`VehicleHighway`, `VehicleGasStation`, `VehicleIndustrial`, `VehicleRuralFarm`,
`VehiclePoliceCheckpoint`, `VehicleHatchback02`, `VehicleOffroad02` events:**

| Vehicle | Nominal | Key: Low Part Chances |
|---------|---------|----------------------|
| CivilianSedan | 30 | Battery 15%, SparkPlug 12%, Wheels 25% |
| OffroadHatchback | 25 | Same low part chances |
| HatchbackSedan | 20 | — |
| Sedan_02 | 20 | — |
| Truck_01_02 | 12 | — |
| Hatchback_02 (Gunter 2) | 8 | — (via VehicleHatchback02 event, 56 positions) |
| CivilianSedan_Police | 8 | — |
| OffroadHatchback_Police | 6 | — |
| Sedan_02_Police | 6 | — |
| Offroad_02 (M1025) | 3 | — (via VehicleOffroad02 event, 21 positions — rare) |

**Vehicle Overhaul scenario event nominals (~486 total spawn positions):**

| Event | Nominal | Min | Max | Positions |
|-------|---------|-----|-----|-----------|
| `VehicleCivilianParking` | **40** | 24 | 56 | 102 |
| `VehicleRoadsideBreakdown` | **35** | 20 | 50 | 90 |
| `VehicleHighway` | **30** | 18 | 45 | 99 |
| `VehicleGasStation` | **20** | 12 | 30 | 40 |
| `VehicleIndustrial` | **20** | 12 | 30 | 42 |
| `VehicleRuralFarm` | **25** | 15 | 38 | 83 |
| `VehiclePoliceCheckpoint` | **15** | 8 | 22 | 30 |

High nominal counts mean you see cars everywhere. Low part attachment chances mean almost none
of them run. The ecosystem rewards scavenging multiple wrecks to build one working vehicle.

> ✅ **VehicleMaxCount is pre-configured** — `globals.xml` ships with `VehicleMaxCount=250`,
> allowing all 196 vehicle nominals to be active simultaneously. No manual editing required.

---

## Accident Sites (`events.xml` + `cfgeventspawns.xml`)

Four dedicated events place **static decorative wrecks** at fixed road-shoulder positions
across Chernarus. These are completely separate from the drivable vehicle events — they use
different event names, different positions, and different types (non-drivable `Land_Wreck_*_DE`
and `StaticObj_Wreck_*_DE` props). Drivable vehicle budgets are not touched.

Works **exactly like a helicrash** — a true lifecycle event, not a permanent fixture:
each wreck site spawns at a random position from the pool, lives for **1 hour** (`lifetime=3600`),
then despawns (`deletable=1`) and immediately reappears at a **new random position**. The world's
road debris is constantly shifting — the dangerous stretch of highway changes every hour.

| Event | Positions | Active | Wreck Types | Purpose |
|-------|-----------|--------|-------------|---------|
| `AccidentSite` | 25 | **15** | 17 civilian car variants | Primary crashed/abandoned car at each site |
| `AccidentSiteCollision` | 15 | **8** | 10 crash-damaged variants | Second vehicle — turns ~8 sites into two-car collisions |
| `AccidentSiteLarge` | 10 | **4** | Bus, truck × 3, firetruck, ambulance | Rare dramatic large-vehicle wrecks on highways |
| `AccidentSiteMilitary` | 12 | **4** | V3S, UAZ, Ural, BMP-1, BRDM-2 | Military convoy remnants near military zone roads |

**Road safety:** All positions are placed on road *shoulders* — offset from the driving lane.
Positions are in the same z/x bands as the existing `VehicleRoadsideBreakdown` event, which
Bohemia placed manually at safe roadside positions. At least one full lane remains passable.

**Narrative logic:** The military wrecks near Balota, NWAF, Pavlovo, Tisy, and the NE
military zones tell the story of the last days of organised resistance — convoys that
never made it, armoured vehicles that burned out on the approach roads.

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

These timer-based events spawn, live out their lifecycle, despawn, then reappear at a new
random position — exactly like a helicrash. None are permanent:

| Event | Nominal | Lifetime | What Happens |
|-------|---------|----------|-------------|
| `StaticZombieHorde` | **8** | 30 min | Abandoned car wreck + `InfectedCity` swarm (25–45 zombies); cycles through 118 positions |
| `StaticHeliCrash` | **3** | 35 min | Crash site, guarded by `InfectedArmy` |
| `StaticMilitaryConvoy` | **5** | 30 min | Convoy wreck sites, guarded by `InfectedArmy` |
| `StaticPoliceSituation` | **5** | 30 min | Police incident sites, guarded by `InfectedPoliceHard` |
| `StaticTrain` | **3** | 90 min | Train wreck sites, guarded by `InfectedIndustrial` |
| `StaticAirplaneCrate` | **9** | 30 min | Airplane supply crates |
| `StaticContaminatedArea` | 0–4 | dynamic | Dynamic contaminated zones |
| `AccidentSite` | **15** | 1 hr | Civilian car wreck; cycles through 25 road-shoulder positions |
| `AccidentSiteCollision` | **8** | 1 hr | Second car at ~8 collision sites; cycles through 15 positions |
| `AccidentSiteLarge` | **4** | 1 hr | Bus/truck/firetruck wreck; cycles through 10 positions |
| `AccidentSiteMilitary` | **4** | 1 hr | Military convoy wreck; cycles through 12 positions |

Every event uses `deletable=1` + `init_random=1` — they genuinely come and go during a session,
not just on restart. The map looks different every hour.

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
- [ ] `cfgeconomycore.xml` — contains `<ce folder="db">` block that registers `events.xml`, `globals.xml`, and `types.xml`
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
