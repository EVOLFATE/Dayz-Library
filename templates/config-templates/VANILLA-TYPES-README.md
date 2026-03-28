# vanilla-types-full.xml — Post-Apocalyptic Loot Economy (v3)

**Full vanilla DayZ types.xml — 1,282 entries — DayZ 1.28 — Chernarus**

Part of the [EVOLFATE/Dayz-Library](https://github.com/EVOLFATE/Dayz-Library) server configuration suite.

---

## What Is This File?

`vanilla-types-full.xml` is a complete, production-ready `types.xml` covering **every vanilla DayZ item** (as of DayZ 1.28), including all working removed/legacy items. Every entry has been hand-tuned to reflect a **hardcore post-apocalyptic server experience**: loot is scarce, survival is hard, and every find matters.

This file is the companion to:
- **ZedLands** — 578 zombie territory zones covering all of Chernarus
- **Realistic Wildlife Overhaul** — dangerous predators force players to hunt, not just loot
- **Realistic Vehicle Overhaul** — vehicles are rare, vehicle parts are precious
- **Extreme Weather** — harsh conditions demand preparation

---

## Design Philosophy

> *Civilization collapsed years ago. Everything remaining is worn, broken, or almost used up.*

| Principle | Implementation |
|---|---|
| Post-apocalyptic scarcity | Nominals reduced 30–50% from vanilla defaults |
| Military gear is rare | Nominals 1–5, `count_in_hoarder="1"`, `count_in_player="1"` |
| Civilian gear is the backbone | Town/Village spawn, still scarce |
| Melee > Firearms | Sledgehammer easier to find than an M4 |
| Food is scarce | Players must hunt (wildlife overhaul) and farm |
| Medical supplies are precious | Rags common, morphine/epinephrine rare |
| Vehicle parts are rare | Spark plug = striking gold |
| Base building encouraged | Nails, planks moderately available |
| Removed/legacy items included | Marked with `<!-- REMOVED/LEGACY ITEM -->` |
| Proper tier distribution | Tier1 coast junk → Tier4 elite military |

### Nominal Tuning Guide

| Rarity | Nominal | Examples |
|---|---|---|
| Very Common | 12–25 | Rags, water bottle, basic tools |
| Common | 6–12 | Food cans, basic clothing |
| Uncommon | 3–6 | Mid-tier gear, civilian firearms |
| Rare | 1–3 | Military weapons, morphine |
| Very Rare | 1 | M4A1, surgical kit, saline bag |

---

## Category Breakdown (~1,282 total entries)

| Category | Est. Count | Notes |
|---|---|---|
| 🔫 Weapons (rifles, pistols, shotguns, melee, bows) | ~120 | Melee > firearms |
| 📦 Magazines | ~80 | All variants |
| 🎯 Ammunition | ~70 | All calibres, small stacks |
| 🔭 Optics & Attachments | ~90 | Suppressors, stocks, rails |
| 👕 Clothing | ~250 | All civilian, military, specialist |
| 🎒 Containers & Storage | ~40 | Backpacks, barrels, cases |
| 🍎 Food & Drink | ~100 | Canned goods, fruit, drinks |
| 💊 Medical | ~50 | Rags to surgical kits |
| 🔧 Tools & Equipment | ~80 | Hand tools, navigation, lights |
| 🏗️ Base Building | ~40 | Kits, tents, locks, camo nets |
| 🚗 Vehicle Parts | ~60 | Wheels, batteries, body panels |
| 📻 Electronics & Navigation | ~30 | Radios, batteries, NVGs |
| 🧱 Resources & Crafting | ~50 | Pelts, seeds, wire, rope |
| 🗑️ Removed/Legacy Items | ~100+ | Working items marked in XML |
| 🔩 Miscellaneous | ~120+ | Books, flags, grenades, traps |

---

## Installation

### Basic install
```bash
# Copy to your mission folder (replace <mission> with your mission name)
cp vanilla-types-full.xml mpmissions/<mission>/db/types.xml
```

### Nitrado (console)
Upload to: `dayzps/missions/<mission>/db/types.xml`

### Restart required
A full server restart is required after replacing `types.xml`. The Central Loot Economy re-initialises on startup.

---

## Customisation

### Adjust scarcity (make loot more common)
Find any `<type>` entry and increase `nominal` and `min`:
```xml
<!-- Before (post-apoc scarcity) -->
<nominal>2</nominal>
<min>1</min>

<!-- After (more common) -->
<nominal>8</nominal>
<min>4</min>
```

### Change spawn tier distribution
Add or remove `<value>` tags to control which map zones an item spawns in:
```xml
<!-- Military only (Tier3/4) -->
<value name="Tier3"/>
<value name="Tier4"/>

<!-- Spawn everywhere (Tier1–4) -->
<value name="Tier1"/>
<value name="Tier2"/>
<value name="Tier3"/>
<value name="Tier4"/>
```

### Adjust anti-hoard flags for military gear
```xml
<!-- Strict anti-hoard (default for military) -->
<flags count_in_cargo="0" count_in_hoarder="1" count_in_map="1" count_in_player="1" crafted="0" deloot="0"/>

<!-- No restriction (default for civilian items) -->
<flags count_in_cargo="0" count_in_hoarder="0" count_in_map="1" count_in_player="0" crafted="0" deloot="0"/>
```

### Remove removed/legacy items
Search for `<!-- REMOVED/LEGACY ITEM -->` and delete those `<type>` blocks if you want to keep strictly in-game items only.

---

## Spawn Zone Reference

| Usage Tag | Location |
|---|---|
| `Military` | Military bases, barracks |
| `MilitaryWest` | NATO-style military locations |
| `MilitaryEast` | Eastern bloc military locations |
| `Police` | Police stations |
| `Medic` | Hospitals, clinics |
| `FireStation` | Fire stations |
| `Town` | Urban residential/commercial |
| `Village` | Small rural settlements |
| `Farm` | Agricultural buildings |
| `Hunting` | Hunting stands, forests |
| `Coast` | Coastal buildings |
| `Industrial` | Factories, warehouses |
| `School` | Schools |
| `Office` | Office buildings |
| `Prison` | Prison complexes |

---

## Compatibility

- **DayZ version**: 1.28 (Chernarus)
- **Map**: Chernarus (all tiers present)
- **Mods required**: None — this is a vanilla types.xml
- **Works with**: All EVOLFATE/Dayz-Library companion configs (ZedLands, weather, wildlife, vehicle overhaul)

---

## Related Files

| File | Purpose |
|---|---|
| `mods/survival/post-apocalyptic-loot-economy/types.xml` | Source/alternate location for this same economy |
| `mods/vehicles/realistic-vehicle-overhaul/types.xml` | Vehicle spawn overrides (merge with this file) |
| `templates/config-templates/types-xml-template.xml` | Blank template for adding custom items |
| `docs/xml-configs/types-xml.md` | Full types.xml parameter reference |

---

## Links

- **Repository**: [EVOLFATE/Dayz-Library](https://github.com/EVOLFATE/Dayz-Library)
- **ZedLands**: [`ZedLands/`](../../ZedLands/) — zombie territory system
- **Weather**: [`mods/weather/`](../../mods/weather/) — extreme weather configs
- **Wildlife**: [`mods/animals/`](../../mods/animals/) — realistic wildlife overhaul
- **Vehicles**: [`mods/vehicles/`](../../mods/vehicles/) — realistic vehicle overhaul
