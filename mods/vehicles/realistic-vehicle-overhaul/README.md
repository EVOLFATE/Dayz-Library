# Realistic Vehicle Overhaul

A **full replacement** vehicle configuration mod for DayZ Chernarus+. Vehicles
are everywhere — littering roads, towns, parking lots, farms, and highways — but
almost all of them are broken down. Finding one that actually runs is a genuine
achievement. Every vehicle is worth checking because you never know what's inside.

---

## Philosophy

> *Most abandoned cars in a real apocalypse would be stripped, broken, empty, or
> junked. Finding one that runs is a genuine achievement worth celebrating.*

1. **Vehicles are everywhere** — towns, roads, highways, villages, gas stations,
   industrial areas, parking lots. You will see cars constantly.
2. **Rare to find a working one** — most vehicles are missing critical parts
   (wheels, battery, spark plug, radiator). A fully driveable car is a ~5-8%
   find. A fully stocked running car is rarer still (~2%).
3. **Every vehicle is a surprise loot box** — cargo ranges wildly: rotten fruit
   and rags, a pistol with ammo, medical supplies, tools, clothing, spare parts.
   Players should ALWAYS want to check vehicles.
4. **Part scavenging loop** — vehicle parts appear as cargo inside other vehicles.
   Check multiple wrecks to build one working car. The ecosystem rewards
   thorough exploration.

---

## What This Mod Changes

- **High spawn counts** — 20-40 civilian cars, 10-20 trucks, 5-10 police variants
  active on the map at any time. Vehicles are a constant presence in the world.
- **Low part attachment chances** — CarWheel: 25%, CarBattery: 15%,
  SparkPlug: 12%, CarRadiator: 20%. Getting all four wheels plus battery, spark
  plug, and radiator is extremely unlikely from a single spawn.
- **Diverse, randomised cargo** — each vehicle type has a unique loot pool of
  20-30+ possible items across food, medicine, tools, weapons, clothing,
  vehicle parts, and junk. The cargo feels genuinely random every time.
- **All vanilla vehicle types covered** — sedans, police cars, offroad/hatchbacks,
  trucks, and their colour variants.

---

## Vehicle Types Covered

### Civilian Cars

| Type | Description | Spawn Count |
|------|-------------|-------------|
| `CivilianSedan` | Standard family car — most common | 30 nominal |
| `CivilianSedan_Police` | Police patrol car | 8 nominal |
| `OffroadHatchback` | Rugged hatchback (multiple colours) | 25 nominal |
| `OffroadHatchback_Police` | Police offroad hatchback | 6 nominal |
| `HatchbackSedan` | Compact hatchback | 20 nominal |
| `Sedan_02` | Mid-size sedan | 20 nominal |
| `Sedan_02_Police` | Police sedan | 6 nominal |

### Trucks

| Type | Description | Spawn Count |
|------|-------------|-------------|
| `Truck_01_02` | V3S military/utility truck | 12 nominal |

---

## Vehicle Condition Tiers

Vehicles spawn in five condition tiers determined by the random combination of
attached parts. Here is roughly what you should expect to find:

### Wrecked (~40%)

Missing most or all parts. Zero to one wheel attached. No battery, spark plug,
or radiator. Engine will not turn over under any circumstances.

- **Purpose:** Scavenge cargo only
- **Common cargo:** Rags, rotten food, junk, occasional tools
- **Key tell:** Multiple empty wheel slots, hood empty

### Heavily Damaged (~30%)

Missing two to three wheels. May have a battery *or* a spark plug but not both.
Radiator usually absent.

- **Purpose:** Salvage parts for a better car; check cargo
- **Common cargo:** Food, clothing, tools, occasional pistol
- **Key tell:** Uneven wheel slots, partial engine components

### Partially Working (~20%)

Missing one to two parts. Has most wheels. One engine component present. Close
to driveable with some scavenging from other wrecks.

- **Purpose:** Repair candidate — worth investing in
- **Common cargo:** Better quality items, occasional vehicle parts
- **Key tell:** Three wheels, partial engine

### Rare Functional (~8%)

All four wheels attached. Has battery, spark plug, and radiator. May have some
fuel already. Nearly ready to drive — check the fuel gauge and any missing
headlight bulbs.

- **Purpose:** Drive it
- **Common cargo:** Mixed civilian gear, potential pistol
- **Key tell:** Full wheels, all engine components present

### Pristine Jackpot (~2%)

Fully functional with fuel. Good cargo inside. An extremely rare find that
rewards thorough map exploration.

- **Purpose:** The jackpot
- **Common cargo:** Quality food, good medical kit, weapon, spare parts
- **Key tell:** Full wheels, full engine, fuel gauge reads non-zero

> **Note:** These percentages are emergent from the independent per-slot chances
> defined in `cfgspawnabletypes.xml`. Actual observed rates will vary slightly
> depending on random seed.

---

## Cargo Loot Pools

Each vehicle type has a distinct cargo profile. Below are the categories used
across all vehicles.

### Food & Drink (common/uncommon)

Canned goods (BakedBeans, FoodCanPeach, FoodCanSardines, FoodCanTuna,
FoodCanBacon, FoodCanSpaghetti), rotten food (RottenKiwi, RottenApple,
RottenPear, RottenTomato, RottenBanana), sodas (SodaCan_Cola, SodaCan_Spite,
SodaCan_Pipsi, SodaCan_Kvass), PlasticBottle.

### Medical (uncommon/rare)

BandageDressing, Rag, BloodBagIV, Morphine, EpinephrineAutoInjector,
Painkiller, Tetracycline, VitaminBottle, SalineBagIV.

### Tools (uncommon/rare)

Wrench, Pliers, Screwdriver, Hacksaw, Handsaw, Hammer, SledgeHammer, Crowbar,
LugWrench, TireRepairKit, EpoxyPutty, DuctTape.

### Weapons — Pistols (rare)

FX45, CZ75, MK2, IJ70, Deagle, Glock19.
> Police vehicles have higher pistol chances.

### Weapons — Rifles (very rare)

Mosin9130, CZ527, KA74.

### Weapons — Shotguns (rare)

Izh18, BK18.

### Weapons — Melee (uncommon)

KitchenKnife, SteakKnife, Machete, BaseballBat, PipeWrench, Crowbar.

### Ammunition (rare, matching weapons)

.45 ACP, 9×19mm, 7.62×39mm, .357, 7.62×54mmR — small quantities (1-5 rounds).

### Clothing & Gear (uncommon)

RainCoat, M65Jacket, Jeans, WorkingBoots, WorkingGloves, SmallProtectorCase,
DryBag, TaloonBag, HuntingBag, ChestHolster, BaseballCap, BoonieHat.

### Vehicle Parts as Cargo (uncommon/rare)

CarWheel, CarBattery, SparkPlug, CarRadiator, HeadlightH7Bulb,
CanisterGasoline. Finding parts inside *wrecked* cars is the core of the
scavenging loop.

### Junk & Misc (common)

DuctTape, Rope, Nail, WoodenPlank, Paper, Pen, Compass, Map, Matches, Lighter,
FlashlightEveready, Battery9V, Rag, BrokenBottle.

---

## File Inventory

| File | Purpose | Install Path |
|------|---------|--------------|
| `types.xml` | Vehicle spawn counts, lifetimes, tiers | `db/types.xml` |
| `cfgspawnabletypes.xml` | Vehicle part chances and cargo pools | `db/cfgspawnabletypes.xml` |
| `events.xml` | Named spawn events for fixed-location spawns | `db/events.xml` |
| `cfgeventspawns.xml` | Map coordinates for each event | `db/cfgeventspawns.xml` |
| `README.md` | This documentation | — |

---

## How to Install

> ⚠️ **These are full replacement files.** They completely replace the vanilla
> versions. Do NOT merge `types.xml` or `events.xml` with vanilla — replace them.
> For `cfgspawnabletypes.xml`, merge the `<type>` blocks if you have existing
> custom entries.

### Console Server Admins (PS4/Xbox/Console)

1. Navigate to your mission file manager
2. Open `mpmissions/dayzOffline.chernarusplus/db/`
3. Upload `types.xml` — replaces the vanilla file
4. Upload `events.xml` — replaces the vanilla file
5. Upload `cfgeventspawns.xml` — replaces the vanilla file
6. Open `cfgspawnabletypes.xml` and merge the `<type>` blocks from this mod's
   file (or replace if you have no custom entries)
7. Restart your server — changes take effect on the next server restart

### PC/Steam Server Admins

```
YourServerFolder/
└── mpmissions/
    └── dayzOffline.chernarusplus/
        └── db/
            ├── types.xml              ← replace with mod's types.xml
            ├── events.xml             ← replace with mod's events.xml
            ├── cfgeventspawns.xml     ← replace with mod's cfgeventspawns.xml
            └── cfgspawnabletypes.xml  ← merge mod's <type> blocks into existing
```

### Custom Mission Name

If your mission folder is not `dayzOffline.chernarusplus`, replace it with your
mission folder name (e.g., `mpmissions/MyCustomMission.chernarusplus/`).

### Merging `cfgspawnabletypes.xml`

If you already have a `cfgspawnabletypes.xml`:

1. Open both files
2. Copy every `<type name="...">` block from this mod's file
3. Paste them inside the root `<cfgspawnabletypes>` element of your existing file
4. Do not duplicate — if you already have a `<type name="CivilianSedan">` block,
   replace yours with this mod's version or merge the cargo/attachments manually

---

## Customisation

### Adjusting Spawn Counts

Edit `types.xml`. For each vehicle:

- `<nominal>` — target active count on map at any time
- `<min>` — minimum count before restock triggers
- `<max>` — ceiling count (set higher than nominal for variety)

**Reduce spawn density (lower-end server):**
Lower `nominal` by 30-50% across all vehicle types.

**Increase spawn density:**
Raise `nominal` by up to 50%. Ensure `max` is at least `nominal × 1.4`.

### Adjusting Part Chances (makes cars easier or harder to fix)

Edit `cfgspawnabletypes.xml`. Each `<attachments>` block controls part chances:

```xml
<!-- Make wheels easier to find — raise chance from 0.25 to 0.45 -->
<item name="CarWheel" chance="0.45"/>

<!-- Make batteries rarer — lower from 0.15 to 0.08 -->
<item name="CarBattery" chance="0.08"/>
```

The outer `<attachments chance="...">` value is the probability the entire
attachment slot is filled at all. The inner `<item chance="...">` values
are the relative weights among items that can fill that slot.

### Adjusting Cargo Chances

Edit `cfgspawnabletypes.xml`. Each `<cargo>` block controls what appears inside
the vehicle:

```xml
<!-- Make pistols more common in civilian sedans -->
<item name="Glock19" chance="0.12"/>  <!-- was 0.04 -->

<!-- Remove rifles from trucks entirely — delete or set to 0.00 -->
<item name="Mosin9130" chance="0.00"/>
```

### Event Spawn Locations

Edit `cfgeventspawns.xml` to add or remove spawn coordinates. Each `<pos>`
entry is a fixed map location:

```xml
<pos x="7612.0" z="2450.0" a="90"/>
```

Where `x` and `z` are map coordinates and `a` is the vehicle's heading
(0-360 degrees).

---

## Compatibility

- **Map:** Chernarus+ (`dayzOffline.chernarusplus`)
- **Compatible with console:** Yes — all files are standard vanilla XML formats
- **Compatible with:** DayZ 1.23+
- **Conflicts with:** Any other mod that replaces `types.xml`, `events.xml`,
  `cfgeventspawns.xml`, or vehicle entries in `cfgspawnabletypes.xml`. Use one
  vehicle overhaul mod at a time.
- **Works alongside:** Zombie mods (e.g., `realistic-everywhere-zeds`), wildlife
  mods (e.g., `realistic-wildlife-overhaul`) — these do not conflict as they
  affect different entity categories.

---

## Spawn Counts Reference

| Vehicle | Nominal | Min | Max | Spawn Zones |
|---------|---------|-----|-----|-------------|
| CivilianSedan | 30 | 20 | 45 | Town, Village, Coast, all Tiers |
| CivilianSedan_Police | 8 | 4 | 12 | Town, all Tiers |
| OffroadHatchback | 25 | 15 | 38 | Town, Village, Forest, all Tiers |
| OffroadHatchback_Police | 6 | 3 | 10 | Town, all Tiers |
| HatchbackSedan | 20 | 12 | 30 | Town, Village, Coast, all Tiers |
| Sedan_02 | 20 | 12 | 30 | Town, Village, all Tiers |
| Sedan_02_Police | 6 | 3 | 10 | Town, all Tiers |
| Truck_01_02 | 12 | 6 | 18 | Industrial, Farm, all Tiers |

---

## Design Philosophy

This mod was built around five convictions:

1. **Every vehicle is worth checking** — even a completely wrecked car with no
   wheels might contain a pistol, canned food, medical supplies, or spare parts.
   The cargo randomisation ensures no vehicle can be safely ignored.
2. **Loot variety is king** — cargo pools are diverse enough that players
   genuinely don't know what they'll find. One car might have rotten fruit and
   rags, the next a pistol and ammo, another a full medical kit.
3. **Realism** — most abandoned cars in a real apocalypse would be stripped,
   broken, empty, or junked. Finding one that runs is a genuine achievement.
4. **Reward exploration** — high spawn counts mean players encounter vehicles
   often. Randomised condition and cargo make each one an exciting prospect.
5. **Part scavenging loop** — vehicle parts appear as cargo inside other wrecked
   cars. This creates a satisfying progression loop: check multiple wrecks,
   collect the parts, build one working vehicle.

---

## License

Free to use on any DayZ server. Credit to EVOLFATE/Dayz-Library appreciated but
not required.
