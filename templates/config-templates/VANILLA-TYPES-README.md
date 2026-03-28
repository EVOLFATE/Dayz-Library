# vanilla-types-full.xml — Post-Apocalyptic Loot Economy (v4)

**Full vanilla DayZ types.xml — 1,382 entries — DayZ 1.28 — Chernarus**

Part of the [EVOLFATE/Dayz-Library](https://github.com/EVOLFATE/Dayz-Library) server configuration suite.

---

## What Is This File?

`vanilla-types-full.xml` is a complete, production-ready `types.xml` covering **every vanilla DayZ item** (as of DayZ 1.28), including all confirmed working removed/legacy items. Every entry has been hand-tuned to reflect a **hardcore post-apocalyptic server experience**: loot is scarce, survival is brutal, and every find matters.

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
| **Barter currency system** | **Vodka, cigarettes, cannabis = hard currency** |

---

## The Barter Economy

Three commodities became the post-collapse **currency** of Chernarus. They are treated differently from all other items:

| Currency | Classnames | Why It Has Value |
|---|---|---|
| 🍶 **Vodka** | `Vodka`, `VodkaBottleLarge` | Disinfectant, anaesthetic, social lubricant. Every survivor wants it. |
| 🚬 **Cigarettes** | 8 brands (see below) | Pre-war comfort. The last pack of Sobranie is worth a rifle. |
| 🌿 **Cannabis** | `Cannabis`, `CannabisSeedsPack`, `CannabisSeeds` | Grows on forgotten farms. Barter, morale, survival. |

### Currency Tuning
All currency items use:
```xml
<nominal>1</nominal> or <nominal>2</nominal>
<lifetime>43200</lifetime>   <!-- 12 hours — they persist, waiting to be found -->
<restock>14400</restock>     <!-- 4 hours  — scarce restock maintains real value -->
<flags count_in_hoarder="1" count_in_player="1" .../>
```

> **The hoarding mechanic**: `count_in_hoarder="1"` means when players stockpile these items in stashes, they count against the world's global spawn cap. The more people hoard, the scarcer they become in the open world — driving up barter value organically.

### Cigarette Brands
| Brand | Rarity | Spawn Locations |
|---|---|---|
| `CigarettePack_Chernamorka` | nominal 2 | Town, Village, Coast, School |
| `CigarettePack_Merkur` | nominal 2 | Town, Village, Coast, School |
| `CigarettePack_Partyzanka` | nominal 2 | Town, Village, Coast |
| `CigarettePack_Kosmos` | nominal 2 | Town, Village |
| `CigarettePack_Luckis` | nominal 2 | Town, Village |
| `CigarettePack_Lucky` | nominal 1 | Town, Village, Office |
| `CigarettePack_Prima` | nominal 1 | Town, Village |
| `CigarettePack_Sobranie` | nominal 1 | Town, Office — *rarest brand* |

---

### Nominal Tuning Guide

| Rarity | Nominal | Examples |
|---|---|---|
| Very Common | 12–25 | Rags, water bottle, basic tools |
| Common | 6–12 | Food cans, basic clothing |
| Uncommon | 3–6 | Mid-tier gear, civilian firearms |
| Rare | 1–3 | Military weapons, morphine |
| Very Rare | 1 | M4A1, surgical kit, saline bag |
| **Currency** | **1–2** | **Vodka, cigarettes, cannabis** |

---

### Lifetime / Restock Philosophy

| Item Category | Lifetime | Restock | Reasoning |
|---|---|---|---|
| Legacy firearms | 43200 (12h) | 14400 (4h) | Relics of the old world — rare and persistent |
| Military gear | 43200 (12h) | 14400 (4h) | Endgame tier, long despawn |
| **Currency items** | **43200 (12h)** | **14400 (4h)** | **Scarce and persistent — feels valuable** |
| Magazines / ammo | 28800 (8h) | 7200 (2h) | Ammo degrades, still precious |
| Melee weapons | 28800 (8h) | 7200 (2h) | Backbone of survival |
| Clothing / tools | 14400 (4h) | 3600 (1h) | Standard rotation |
| Food / drink | 14400 (4h) | 3600 (1h) | Consumed, cycles faster |

---

## Category Breakdown (~1,382 total entries)

| Category | Est. Count | Notes |
|---|---|---|
| 🔫 Weapons (rifles, pistols, shotguns) | ~125 | Melee > firearms |
| 🗡️ Melee weapons | ~35 | Includes removed melee (hockey sticks, chainsaw, batons) |
| 📦 Magazines & speedloaders | ~95 | All variants including removed |
| 🎯 Ammunition | ~70 | All calibres, small post-apoc stacks |
| 🔭 Optics & Attachments | ~95 | Suppressors, stocks, rails, removed scopes |
| 👕 Clothing | ~275 | All civilian, military, specialist + full leather sets |
| 🎒 Containers & Storage | ~42 | Backpacks, barrels, cases, quiver |
| �� Food & Drink | ~105 | Canned goods, fruit, drinks + removed items |
| 💊 Medical | ~50 | Rags to surgical kits |
| 🔧 Tools & Equipment | ~95 | Hand tools, pens, spray cans, mess tin, defibrillator |
| 🏗️ Base Building | ~40 | Kits, tents, locks, camo nets |
| 🚗 Vehicle Parts | ~60 | Wheels, batteries, body panels |
| 📻 Electronics & Navigation | ~30 | Radios, batteries, NVGs |
| 🧱 Resources & Crafting | ~50 | Pelts, seeds, wire, rope |
| 📚 Books (literary) | ~130 | All DayZ literary classics removed from CE in 1.16 |
| 📖 Books (gameplay/skill) | ~17 | Farming, Medicine, Engineering, Military + more |
| 🍶 Currency (barter economy) | ~12 | Vodka × 2, Cannabis × 3, Cigarettes × 8 |
| 🗑️ Other Removed/Legacy Items | ~85 | Working items marked `<!-- REMOVED/LEGACY ITEM -->` |
| 🔩 Miscellaneous | ~120+ | Flags, grenades, traps, maps |

**Total removed/legacy items marked in XML: 101+**

---

## Removed/Legacy Items Added (v4)

All entries are marked with `<!-- REMOVED/LEGACY ITEM -->` and confirmed working in DayZ 1.28+.

### Firearms
`Derringer` · `Red9` · `Trumpet` · `SawedoffIzh18` · `MP133Shotgun_PistolGrip` · `1911Engraved` · `M4A1_Green`

### Melee
`Chainsaw` · `StunBaton` · `CattleProd` · `TelescopicBaton` · `HockeyStick` · `IceHockeyStick` · `HayHook` · `CanoePaddle`

### Archery
`Improvised_Bow` · `Quiver` · `BoltComposite` · `BoltBone` · `ArrowComposite` · `ArrowBone`

### Magazines & Speedloaders
`Red9_10Rnd_Mag` · `Trumpet_15Rnd_Mag` · `Mag_Derringer_2Rnd` · `Mag_Repeater_6Rnd` · `Mag_Longhorn_1Rnd` · `SpeedLoader_357` · `SpeedLoader_12ga` · `Mag_CLIP_762x54_5Rnd` · `Mag_CZ527_5Rnd` · `Mag_Coupled_STANAG_30Rnd`

### Attachments & Optics
`LongRangeScope` · `ATLASBipod` · `Red9Bttstck`

### Leather Clothing (full sets in Natural / Beige / Brown / Black)
`LeatherShirt` · `LeatherPants` · `LeatherJacket` · `LeatherHat` · `LeatherShoes` · `LeatherGloves` · `LeatherVest_Natural` · `SkateHelmet_White`

### Removed Food & Drink
`FoxSteak` · `Elderberries` · `RoseHip` · `LeatherBottle` · `Lard` · `Powderedmilk` · `HumanSteakMeat`

### Barter Currency
`Vodka` · `VodkaBottleLarge` · `Cannabis` · `CannabisSeedsPack` · `CannabisSeeds` · all 8 `CigarettePack_*` brands

### Tools & Equipment
`Pen_Blue` · `Pen_Black` · `Pen_Red` · `Pen_Green` · `SprayCan_Black` · `SprayCan_Green` · `SprayCan_Red` · `MessTin` · `Defibrillator` · `Paper`

### Gameplay / Skill Books
`BookFarming` · `BookMedicine` · `BookEngineering` · `BookMilitary` · `BookCooking` · `BookHunting` · `BookSurvival` · `BookFishing` · `BookMechanics` · `BookElectronics` · `BookForaging` · `BookCrafting` · `BookFirstAid` · `BookTactics` · `BookGunsmithing` · `BookHerbalMedicine` · `BookNavigating`

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

### Tune the barter economy
Increase or decrease the nominal of currency items to control how scarce they are:
```xml
<!-- Make vodka extremely rare (1 bottle per tier, 12h lifetime) -->
<type name="Vodka">
    <nominal>1</nominal>
    <lifetime>43200</lifetime>
    <restock>14400</restock>
    ...
    <flags count_in_hoarder="1" count_in_player="1" .../>
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

### Remove removed/legacy items
Search for `<!-- REMOVED/LEGACY ITEM -->` and delete those `<type>` blocks if you want strictly vanilla-CE items only.

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
