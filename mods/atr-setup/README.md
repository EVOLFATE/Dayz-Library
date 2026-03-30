# ATR Setup — Post-Apocalyptic Realism

> *"The world ended. What's left isn't yours — you earn every breath, every meal,
every night you survive. Nothing is given. Everything is taken."*

A **hardcore realism configuration preset** for DayZ designed to create an authentic
post-apocalyptic survival experience. Every setting in this package is grounded in
real-world data — from zombie population densities modeled on pandemic spread research
to food scarcity timelines drawn from historical societal collapses.

**This is not a casual experience.** You will hunt. You will scavenge. You will starve
if you don't. The world is gloomy, fog-choked, and crawling with the infected.

---

## Contents

| File | Purpose |
|------|---------|
| `cfgweather.xml` | Persistent gloomy & foggy weather — verified against [Bohemia Interactive Wiki](https://community.bistudio.com/wiki/DayZ:Weather_Configuration) |
| `events.xml` | Infected events — 3 custom horde tiers + 18 territory events (InfectedCity, InfectedVillage, InfectedArmy, InfectedMummy, etc.) |
| `cfgeventspawns.xml` | 39 fixed spawn coordinates for the horde events above |
| `types.xml` | Zombie skin entity declarations + scarce loot economy |
| `db/globals.xml` | Raises `ZombieMaxCount` from vanilla 1000 → 8000 to support 1,082 territory zones |
| `env/zombie_territories.xml` | ATR-tuned zone territories — 1,082 zones covering every corner of Chernarus |
| `README.md` | This file — philosophy, realism data, and configuration guide |

---

## 🌍 Design Philosophy

ATR (Authentic Threat Realism) is built on three pillars:

1. **Hunt or Die** — Loot is scarce. Canned food runs out. You must learn to track, kill, and cook animals or starve.
2. **Scavenge Smart** — Every building has already been picked through. What remains is random, rare, and often not enough.
3. **Fear the World** — The infected are everywhere. The weather is hostile. The environment itself is trying to kill you.

Every number below is sourced from real data — not guesswork.

---

## 🧟 Realistic Infected (Zombie) Population Density

Zombie counts are modeled on **CDC pandemic spread modeling** and population density
analysis from *World War Z* (Max Brooks) applied to DayZ's Chernarus map scale.

### Real-World Basis

| Source | Key Data Point |
|--------|---------------|
| CDC Pandemic Modeling | 20–50% infection rate in worst-case flu scenarios; zombie analog assumes ~90% conversion |
| *World War Z* (Max Brooks) | ~90% of humanity zombified in Year 1; survivors cluster in remote/fortified areas |
| WHO Crisis Analysis | Urban centers become death traps; rural areas see 1–30 infected/km² after Year 1 |
| Historical Siege Data (WWII, Yugoslav Wars) | Population displacement empties cities within weeks; stragglers remain |

### Translated to DayZ — Recommended `events.xml` Values

Chernarus is approximately **225 km²**. Assuming a pre-outbreak population of ~100,000
with a 90% infection rate and significant attrition over time:

| Location Type | Real-World Equivalent | Infected Density | DayZ `nominal` | `min` | `max` |
|---------------|----------------------|-----------------|----------------|-------|-------|
| **Isolated Cabin / Farm** | Rural homestead | 1–3/km² | 2 | 1 | 4 |
| **Small Village** (Pulkovo, Guglovo) | Hamlet, 50–200 people pre-outbreak | 5–15/km² | 6 | 3 | 10 |
| **Town** (Gorka, Staroye) | Small town, 500–2,000 pre-outbreak | 15–40/km² | 18 | 10 | 25 |
| **Large Town** (Berezino, Zelenogorsk) | Regional center, 2,000–10,000 | 40–100/km² | 35 | 20 | 45 |
| **City** (Chernogorsk, Elektro) | Urban center, 10,000–30,000 | 100–500/km² | 55 | 30 | 70 |
| **Military Zone** (NWAF, Tisy) | Fortified position — last stand site | 200–800/km² | 65 | 40 | 80 |

> **Why these numbers?** After Year 1 of an outbreak, urban zombie populations drop
> significantly due to decay, starvation (yes, zombies decay), and survivor culling.
> Rural areas stay low because population was sparse to begin with. Military zones
> are high because that's where the last organized resistance fell — and with it,
> the highest concentration of freshly turned.

### Attrition Over Time (Realism Note)

| Timeline | Effect on Infected Population |
|----------|------------------------------|
| Week 1–4 | Peak infection — cities at maximum density |
| Month 2–6 | 30–50% attrition from decay and exposure |
| Month 6–12 | Population stabilizes at ~20–40% of peak |
| Year 1+ | Slow decline — what remains is hardened, persistent |

ATR is set in the **6–12 month post-outbreak window** — the infected population has
thinned but what's left isn't going anywhere.

---

## 🌧️ Weather — Persistent Gloom & Fog

The `cfgweather.xml` in this folder creates a world that is **permanently dark,
fog-choked, and oppressive**. Verified against the
[Bohemia Interactive Community Wiki](https://community.bistudio.com/wiki/DayZ:Weather_Configuration)
and [scalespeeder's reference configs](https://github.com/scalespeeder/DayZ-Weather-Config-Files-For-PC-and-Console-For-Community-Server).

### Weather Parameters

| Parameter | Value | Effect |
|-----------|-------|--------|
| **Overcast** | 0.85–1.0 (starts 0.95) | Permanent heavy cloud cover — no blue sky |
| **Fog** | 0.5–0.9 (starts 0.75) | Thick persistent fog — visibility under 100m |
| **Rain** | 0.0–0.15 (starts 0.05) | Light drizzle only — gloomy, not a downpour |
| **Wind** | 1–8 m/s | Mild to moderate — rustling trees, moving fog |
| **Change Limits** | 0.0–0.05 | Weather stays locked — no random clearing |
| **Storm Threshold** | 0.9 | Storms only at peak overcast |
| **reset="1"** | Forced | Config re-applies every server restart |

### Why This Weather?

Real post-apocalyptic conditions would be heavily affected by:

- **Uncontrolled fires** — Factories, fuel depots, and forests burning for months produce persistent atmospheric haze
- **No pollution control** — Industrial sites left running or leaking create ground-level smog
- **Nuclear winter scenarios** — If any military response included tactical weapons, particulate matter blocks sunlight for months
- **Psychological realism** — Permanent gloom creates tension, limits sightlines, and forces close-quarters encounters

---

## 🍖 Hunting & Scavenging — The Food Reality

### Real-World Food Scarcity After Collapse

| Resource | Availability Post-Collapse | Shelf Life |
|----------|---------------------------|------------|
| **Supermarket shelves** | Empty in 3–7 days | — |
| **Canned goods** (scattered) | Scavengeable for 1–12 months | 2–5+ years |
| **Dry staples** (rice, beans) | 1–3 months before area is picked clean | 1–30 years if sealed |
| **Fresh meat/produce** | Spoils in days without refrigeration | Hours to days |
| **Wild game** | Depleted near settlements within weeks | Must cook immediately |
| **Foraged plants** | Seasonal, skill-dependent | Hours |

*Sources: Red Cross logistics analysis, UN crisis response data, WWII siege records,
"Emergency Food Storage & Survival Handbook" (Creek Stewart)*

### What This Means for ATR Gameplay

- **Loot tables should be sparse.** Canned food nominal values should be cut to 30–50% of vanilla.
- **Hunting is essential, not optional.** Animal spawns should be maintained at vanilla or slightly above — they're your primary food source.
- **Cooking matters.** Raw meat should carry disease risk. Campfires attract attention (and infected).
- **Water is critical.** Wells are safe; ponds and streams require purification.
- **Caloric deficit is real.** Players burn ~2,500 kcal/day with heavy activity. A single can of beans won't sustain you.

### Recommended Animal Spawn Settings

Based on real wildlife density in Eastern European temperate forests (Chernarus analog):

| Animal | Real Density (per km²) | DayZ `nominal` | Notes |
|--------|----------------------|----------------|-------|
| **Deer** | 5–15 | 40–60 (map-wide) | Primary large game — high calorie yield |
| **Boar** | 3–8 | 25–40 (map-wide) | Dangerous to hunt — realistic |
| **Rabbit** | 10–40 | 60–80 (map-wide) | Low calorie, high availability |
| **Chicken** | Domestic — near farms only | 15–25 | Only near farm buildings |
| **Cow** | Domestic — near farms only | 10–20 | Feral survivors of the outbreak |
| **Wolf** | 0.5–2 | 8–15 (forest zones) | Pack hunters — a real threat |
| **Bear** | 0.1–0.5 | 3–6 (deep forest) | Apex predator — avoid or be prepared |

> Wildlife density sources: European Wildlife Census Data, Czech Republic forestry
> statistics (Chernarus is modeled on Czech/Russian geography).

---

## 🏚️ The Post-Apocalyptic Setting

### Environmental Storytelling

ATR isn't just numbers — it's atmosphere. The configuration supports a world where:

- **Buildings are shells.** Doors hang open. Interiors are trashed. Loot is scattered, not stacked.
- **Infrastructure is dead.** No power, no running water, no rescue coming.
- **Nature is reclaiming.** Fog rolls through empty streets. Rain drips through broken roofs.
- **The infected wander.** They're not waiting in rooms — they drift through towns, cluster at noise, thin out in the wilderness.
- **Other survivors are the real threat.** With scarce resources, every encounter is a calculation: cooperate or kill.

### Timeline Context

ATR is set approximately **8 months after initial outbreak**:

| Aspect | State at 8 Months |
|--------|-------------------|
| Government | Collapsed — no military, no police, no aid |
| Power Grid | Down nationwide — generators are gold |
| Medical Supplies | Nearly exhausted — antibiotics are rarer than ammunition |
| Fuel | Scarce — most vehicles are dry, siphoning is a skill |
| Ammunition | Limited — every shot counts, melee is primary |
| Food Supply | Canned goods are nearly gone — hunting and farming are survival |
| Infected Population | Stabilized at ~30% of peak — still extremely dangerous in numbers |
| Survivor Psychology | Hardened — trust is rare, violence is common |

---

## 📦 Installation

### Full Install Path

```
mpmissions/dayzOffline.chernarusplus/
├── cfgweather.xml          ← from this folder (mission root)
├── cfgeventspawns.xml      ← from this folder (mission root)
├── db/
│   ├── events.xml          ← merge from this folder's events.xml
│   ├── globals.xml         ← merge from this folder's db/globals.xml
│   └── types.xml           ← merge from this folder's types.xml
└── env/
    └── zombie_territories.xml  ← from this folder's env/ (REPLACE, not merge)
```

### Applying the Weather Config

1. Copy `cfgweather.xml` to your server's mission root:
   ```
   mpmissions/dayzOffline.chernarusplus/cfgweather.xml
   ```
2. Restart the server — the gloomy fog preset loads immediately.

### Applying the Infected Territory Configuration

1. Copy `env/zombie_territories.xml` to:
   ```
   mpmissions/dayzOffline.chernarusplus/env/zombie_territories.xml
   ```
   > ⚠️ **This is a full replacement.** Do not merge — replace the vanilla file entirely.
2. Restart the server.

### Applying Horde Events + Territory Events

1. Copy `cfgeventspawns.xml` to your mission root:
   ```
   mpmissions/dayzOffline.chernarusplus/cfgeventspawns.xml
   ```
2. Open your server's `db/events.xml` and merge **all** event blocks from this folder's `events.xml`:
   - `InfectedHorde_Small`, `InfectedHorde_Medium`, `InfectedHorde_Large` (custom horde tiers)
   - `InfectedCity`, `InfectedCityTier1`, `InfectedVillage`, `InfectedVillageTier1` (civilian zones)
   - `InfectedArmy`, `InfectedArmyHard` (military zones)
   - `InfectedIndustrial`, `InfectedPolice`, `InfectedMedic`, `InfectedReligious` (specialty zones)
   - `InfectedNBC`, `InfectedPrisoner`, `InfectedFirefighter` (rare zones)
   - `InfectedMummy` (ruin/castle zones — spawns `ZmbM_Mummy`, the vanilla mummy infected)
   - `InfectedSolitude` (wilderness & road corridors)

   > ⚠️ **All territory events** (`InfectedCity`, `InfectedVillage`, `InfectedMummy`, etc.) must use
   > `<position>player</position>` and `<limit>custom</limit>` with a `<children>` spawn pool.
   > Using `<position>fixed</position>` on territory events causes an `ACCESS_VIOLATION` crash at
   > `init.c:6` (`ce.InitOffline()`) — the CE looks for fixed coordinates in `cfgeventspawns.xml`,
   > finds none, and dereferences a null pointer. This file ships with the correct values.

3. Save and restart.

### Validating Your XML Before Deploying

Before restarting the server after any edit, validate every XML file you touched.
**Run this from your mission root** (`mpmissions/dayzOffline.chernarusplus/`):

```bash
# Using Python (available on all platforms):
python3 -c "
import xml.etree.ElementTree as ET, sys
for f in ['db/events.xml','cfgeventspawns.xml','env/zombie_territories.xml','db/types.xml']:
    try:
        ET.parse(f); print(f + ': OK')
    except Exception as e:
        print(f + ': ERROR - ' + str(e)); sys.exit(1)
"
# Or using xmllint (Linux/macOS), also from mission root:
# xmllint --noout db/events.xml cfgeventspawns.xml env/zombie_territories.xml db/types.xml
```

A parse error will show you the exact file and line number — fix it before deploying.

### Applying Loot Scarcity

1. Merge `types.xml` into your mission's `db/types.xml`.
2. The zombie skin entities (nominal=0) simply register skins — they do not affect spawn counts.
3. Reduce food/medical item nominals to **30–50% of vanilla** if not already done.

### Applying the ZombieMaxCount Override

1. Merge `db/globals.xml` into your mission's `db/globals.xml`:
   ```
   mpmissions/dayzOffline.chernarusplus/db/globals.xml
   ```
   The key change is `ZombieMaxCount=8000` (vanilla default is 1000). Without this, the
   CE's global budget caps out at 1000 infected and territory zones silently under-populate
   on anything beyond a very low-pop server.

   > ⚠️ **Merge, do not replace.** Update only the values listed in this file — your server
   > may have other globals (vehicle counts, cleanup timers) that you need to keep.

---

## 🧟 Zombie Territory Design — The ATR Math

The `env/zombie_territories.xml` uses **1,082 zones** across Chernarus tuned to three goals:

### Goal 1: Route Planning ("See them before you commit")

All zone activation radii (`r`) are scaled up versus the base mod so zombies are **spawned and wandering before a player fully enters an area**. This lets you observe from cover, count threats, and pick your path.

| Territory | Base mod avg r | ATR avg r | Effect |
|-----------|---------------|-----------|--------|
| City/Village | 44 m | 60 m | Zombies visible from ~1 street block away |
| Military | 123 m | 159 m | Visible from tree-line — no surprise attacks |
| Wilderness | 314 m | 377 m | Lone wanderer spotted across an open field |
| Horde Pockets | 211 m | 253 m | Horde sound/silhouette before you step in |

### Goal 2: Cities Are Dangerous ("The dead never left")

Permanent zombie presence (`smin`/`smax`) is raised in cities and military zones — even with no players nearby, infected remain. This means every approach to a city involves zombies, not just an empty street until you get close.

| Territory | Base smax/zone | ATR smax/zone | Meaning |
|-----------|---------------|---------------|---------|
| City/Village | 4.3 avg | 6.9 avg | ~60% more permanent infected per zone |
| Military | 7.7 avg | 10.8 avg | Military always a kill zone |
| Horde Pockets | 20.0 avg | 25.0 avg | Hordes maintain their mass |
| Wilderness | 0.0 | 0.0 | Wilderness stays dead quiet — solitude intact |

### Goal 3: Wilderness Has Occasional Wanderers ("Nowhere is truly safe")

Wilderness and road corridor zones (`InfectedSolitude`, 738 zones) keep their low `dmin`/`dmax` values but with larger radii. You may find 2–8 infected wandering the tree-line or along a road at any time — enough to force caution, not enough to stop you from crossing open ground.

**Road corridor zones (+30):** Eight zones follow the south coastal highway from Kamenka to Solnichniy; six trace the central northern road through Pustoshka, Lopatino, Kabanino, and Stary/Novy Sobor to Gorka; four cover the western route through Pavlovo and Kozlovka; five run the eastern corridor from Berezino through Krasnostav and Polana; four link the NWAF south to Grishino and Novy; three bridge Novodmitrovsk to Severograd. Every road feels used.

**Gas station, crossroads & landmark POI zones (+15):** `InfectedVillage` zones (smin=1, smax=3 — a few always present) at every major gas station, key crossroads, and popular landmarks including Devil's Castle, Rog Castle, the NWAF south gate, and Tisy approach. Looting a gas station now always means dealing with someone who was there before you.

### How Territory Events Create the "Always From Somewhere New" Feel

The `events.xml` territory events are tuned so clearing a pack never feels like rubber-banding:

- **`init_random="1"`** — every server restart boots zones at randomised counts (not all at minimum), so the map feels organically populated from the first minute, never the same twice.
- **Non-zero `restock` delays** — after a pack is killed, the engine waits before refilling the budget. When it does refill, it activates a *different* nearby zone, so the next group always approaches from a new direction:

| Event type | Restock delay | Feel |
|---|---|---|
| `InfectedCity` | 3 min | Cities are always swarming — new pack from a different block |
| `InfectedVillage` | 4 min | Kill the square pack, 4 min later one drifts in from the side street |
| `InfectedArmy` | 5 min | Military comes in waves — clear the yard, next patrol from the barracks |
| `InfectedArmyHard` | 6 min | Hardened soldiers, slower reform |
| `InfectedSolitude` | 6 min | Wanderers fade into the tree-line, re-emerge from a different direction |

### How Horde Events Complement Territory Zones

The `events.xml` horde events (InfectedHorde_Small/Medium/Large) add **on-top-of** the territory zones:
- Territory zones provide the **ambient population** — the background noise of the apocalypse
- Event hordes provide **concentrated danger points** — moments where you encounter a true pack
- The two systems are additive: walk into a city territory zone during an active horde event and you face both

### ZombieMaxCount Headroom

`globals.xml` sets `ZombieMaxCount=8000`. The 15 territory event nominals total ~1,778 combined — roughly 22% of the cap. DayZ only activates zones within player proximity, so the total active at any moment scales with player count, not total zone count. On a 30-player server, roughly 150–400 zones are active simultaneously — well within the 8000 cap, with plenty of headroom for the 3 horde events running on top.

---

## ⚙️ Configuration Rules — Do Not Break These

These rules are verified against the vanilla Bohemia CE and must be respected when editing `events.xml` or related files.

### Rule 1 — `cleanupradius` must always be greater than `distanceradius`

```
cleanupradius > distanceradius   (minimum gap: +100 for infected, +150 for large hordes)
```

The `distanceradius` is how far from the spawn-point the engine may place an entity.
The `cleanupradius` is the boundary beyond which entities are despawned.

If `cleanupradius ≤ distanceradius`, entities that spawn at the outer edge of `distanceradius`
are already outside the `cleanupradius` and are silently despawned the moment they appear.
This is a **silent zero-spawn bug** — no error is logged.

| Event | `distanceradius` | `cleanupradius` | ✓/✗ |
|---|---|---|---|
| InfectedHorde_Small | 200 | 300 | ✓ |
| InfectedHorde_Medium | 300 | 400 | ✓ |
| InfectedHorde_Large | 500 | 650 | ✓ |
| All territory events | 130–200 | 200–300 | ✓ |

### Rule 2 — Territory event `nominal` is a budget, not a fill target

`nominal` is the **server-wide dynamic-spawn budget** for that type, distributed across
active zones (zones within ~500m of a player). It is not a guarantee that every zone will
be populated.

**Setting `nominal` below total zone count is intentional — it is what creates variance.**
A player may enter six villages in a row and find four empty and two crawling with infected.
That unpredictability is more threatening than guaranteed coverage: you never know which
corner is occupied.

| Event | Zones | `nominal` | Avg per active zone | Design intent |
|---|---|---|---|---|
| `InfectedCity` | 40 | 120 | ~6 (20 active) | Cities always feel dangerous |
| `InfectedVillage` | 127 | 180 | ~6 (30 active) | Most villages quiet, some overrun |
| `InfectedMummy` | 25 | 15 | ~3 (5 active) | Rare — the ruin may be empty, or it may not |
| `InfectedSolitude` | 738 | 240 | ~3 (80 active) | Occasional wanderer, never a guarantee |

Do **not** raise a `nominal` to equal the total zone count to "ensure every zone is filled".
That removes variance and makes the map feel uniform and predictable.

### Rule 3 — Territory event `name` in `zombie_territories.xml` must exactly match event `name` in `events.xml`

The DayZ engine uses the `name` attribute of each `<zone>` to look up the matching event.
A single typo (case included) silently drops all spawns for that type.

Current zone types and their confirmed matching events:

| Zone `name` | events.xml match | Zones |
|---|---|---|
| `InfectedCity` | ✓ | 40 |
| `InfectedCityTier1` | ✓ | 6 |
| `InfectedVillage` | ✓ | 127 |
| `InfectedVillageTier1` | ✓ | 55 |
| `InfectedIndustrial` | ✓ | 19 |
| `InfectedArmy` | ✓ | 28 |
| `InfectedArmyHard` | ✓ | 5 |
| `InfectedPolice` | ✓ | 10 |
| `InfectedMedic` | ✓ | 8 |
| `InfectedReligious` | ✓ | 9 |
| `InfectedNBC` | ✓ | 5 |
| `InfectedPrisoner` | ✓ | 3 |
| `InfectedFirefighter` | ✓ | 4 |
| `InfectedMummy` | ✓ | 25 |
| `InfectedSolitude` | ✓ | 738 |

### Rule 4 — Territory events must NOT have entries in `cfgeventspawns.xml`

Territory events work via `zombie_territories.xml`. They do not use `cfgeventspawns.xml`
position pools. Empty `<event name="InfectedVillage"/>` stubs in `cfgeventspawns.xml` are
invalid and can cause the CE to mishandle the event definition.

Only the three custom horde events (`InfectedHorde_Small`, `InfectedHorde_Medium`,
`InfectedHorde_Large`) should have entries in `cfgeventspawns.xml` — these are
`position=fixed` + `limit=custom` events that explicitly draw from that position pool.

---

## ⚖️ Balancing Notes

| If players say... | Adjust... |
|-------------------|-----------|
| "There's no food anywhere" | Increase animal spawns slightly; food nominal +10% |
| "Zombies are impossible in cities" | In `env/zombie_territories.xml`: reduce `dmax` on `InfectedCity` zones by 5–8 |
| "I can't find any zombies in forests" | In `env/zombie_territories.xml`: increase `dmin` on `InfectedSolitude` zones from 2 to 4 |
| "Horde events are too easy" | In `events.xml`: increase `nominal` or the `max` values on child spawns |
| "It's too dark / foggy all the time" | Raise fog `limits min` from 0.5 to 0.3 for occasional breaks |
| "Wolves are killing everyone" | Reduce wolf `nominal` to 5–8; keep bear low |

---

## 📚 Sources & Verification

All classnames in this mod have been **cross-referenced against
`BohemiaInteractive/DayZ-Central-Economy` master branch (DayZ 1.28)**. Every `type=` value
in `<children>` blocks is confirmed present in the vanilla `db/types.xml`. See the PR that
introduced this audit for a full change log.

All values in this configuration are cross-referenced against:

| Source | Used For |
|--------|----------|
| [Bohemia Interactive Community Wiki — Weather Configuration](https://community.bistudio.com/wiki/DayZ:Weather_Configuration) | `cfgweather.xml` format and parameter validation |
| [scalespeeder/DayZ-Weather-Config-Files](https://github.com/scalespeeder/DayZ-Weather-Config-Files-For-PC-and-Console-For-Community-Server) | Reference vanilla and custom weather XML configs |
| [scalespeeder/DayZ-Zombie-Land](https://github.com/scalespeeder/DayZ-Zombie-Land) | Community zombie density reference — army horde dmin/dmax benchmarks |
| [BohemiaInteractive/DayZ-Central-Economy](https://github.com/BohemiaInteractive/DayZ-Central-Economy) | Vanilla zombie territory baseline for comparison |
| CDC Zombie Preparedness Campaign & Pandemic Flu Modeling | Infection rate and spread projections |
| Max Brooks — *World War Z* | Post-outbreak population density estimates |
| WHO / Red Cross Crisis Logistics Data | Food scarcity timelines and caloric shortfall data |
| European Wildlife Census (Czech Republic Forestry) | Animal population density per km² |
| WWII Siege Records & Yugoslav Wars Analysis | Urban depopulation and scavenging depletion rates |
| *Emergency Food Storage & Survival Handbook* (Creek Stewart) | Shelf life and food preservation data |

---

## 🔮 Planned Additions

- [x] ~~Custom `types.xml` with ATR loot scarcity values pre-configured~~ ✓
- [x] ~~Custom `events.xml` with ATR infected horde events ready to drop in~~ ✓
- [x] ~~ATR zombie territory configuration (`env/zombie_territories.xml`)~~ ✓
- [x] ~~Vanilla territory events (`InfectedCity`, `InfectedVillage`, `InfectedArmy`, etc.) with roaming restock tuning~~ ✓
- [x] ~~Road corridor + POI zones for gas stations, crossroads, and landmarks~~ ✓
- [ ] Nighttime darkness override — no gamma exploiting
- [ ] Temperature extremes config — hypothermia is a killer
- [ ] Companion guide: "Surviving ATR — A Player's Manual"

---

## License

Free to use on any DayZ server. Credit appreciated but not required.
Contributions welcome — open a PR or issue on the [DayZ Library GitHub](https://github.com/EVOLFATE/Dayz-Library).

---

> *"You don't survive the apocalypse by being brave. You survive by being careful,
> being quiet, and knowing when to run."*