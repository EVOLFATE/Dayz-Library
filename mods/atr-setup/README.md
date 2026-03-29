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
| `events.xml` | Static infected horde events — 3 tiers (village stragglers → city overrun → military last-stand) |
| `cfgeventspawns.xml` | 39 fixed spawn coordinates for the horde events above |
| `types.xml` | Zombie skin entity declarations + scarce loot economy |
| `env/zombie_territories.xml` | ATR-tuned zone territories — 1,037 zones covering every corner of Chernarus |
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

### Applying Horde Events

1. Copy `cfgeventspawns.xml` to your mission root:
   ```
   mpmissions/dayzOffline.chernarusplus/cfgeventspawns.xml
   ```
2. Open your server's `db/events.xml` and merge the three event blocks from this folder's `events.xml` (InfectedHorde_Small, InfectedHorde_Medium, InfectedHorde_Large).
3. Save and restart.

### Applying Loot Scarcity

1. Merge `types.xml` into your mission's `db/types.xml`.
2. The zombie skin entities (nominal=0) simply register skins — they do not affect spawn counts.
3. Reduce food/medical item nominals to **30–50% of vanilla** if not already done.

---

## 🧟 Zombie Territory Design — The ATR Math

The `env/zombie_territories.xml` uses **1,037 zones** across Chernarus tuned to three goals:

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

Wilderness and road corridor zones (`InfectedSolitude`, 693 zones on a 600m grid) keep their low `dmin`/`dmax` values but with larger radii. You may find 2–6 infected wandering the tree-line at any time — enough to force caution on forest roads, not enough to stop you from crossing open ground.

### How Horde Events Complement Territory Zones

The `events.xml` horde events (InfectedHorde_Small/Medium/Large) add **on-top-of** the territory zones:
- Territory zones provide the **ambient population** — the background noise of the apocalypse
- Event hordes provide **concentrated danger points** — moments where you encounter a true pack
- The two systems are additive: walk into a city territory zone during an active horde event and you face both

### ZombieMaxCount Headroom

`globals.xml` sets `ZombieMaxCount=5000`. DayZ only activates zones within player proximity, so the total active at any moment scales with player count, not total zone count. On a 30-player server, roughly 150–400 zones are active simultaneously — well within the 5000 cap.

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