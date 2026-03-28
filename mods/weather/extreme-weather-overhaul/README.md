# Extreme Weather Overhaul

A **server-side weather mod** for DayZ that turns the sky into a genuine threat.
Forget mild drizzle and a bit of fog.  This mod introduces a randomised system of
nine distinct weather events — from rare crystal-clear perfect days to catastrophic
supercells that will kill players caught in the open.

---

## Contents

| File | Purpose |
|------|---------|
| `config.cpp` | Mod patch/module registration |
| `scripts/4_World/ExtremeWeatherSystem.c` | Core weather controller and event scheduler |
| `scripts/4_World/StormDamageSystem.c` | Player damage during extreme events |
| `scripts/5_Mission/MissionWeatherInit.c` | Mission integration — starts the systems on server boot |
| `data/weather_config.json` | Tunable configuration (edit this, not the scripts) |

---

## Weather Events

### 🌤 CALM (20 % weight)
Light overcast, gentle breeze, zero precipitation.  The world is quiet.  This is
your baseline "normal" day — peaceful but short-lived.  *Weight: 20 out of 100.*

### ☁️ OVERCAST (20 % weight)
Thick, oppressive cloud cover with an eerie stillness in the air.  No rain yet —
just that unsettling feeling that something is coming.  Perfect for tense player
encounters.  *Weight: 20 out of 100.*

### 🌧 RAIN STORM (18 % weight)
Moderate to heavy rain with rising wind.  Visibility degrades.  Movement through
open fields becomes miserable.  Wet clothing accelerates cold stat loss — get
under cover or change your clothes.  *Weight: 18 out of 100.*

### ⛈ THUNDERSTORM (12 % weight)
The full package: maximum overcast, near-torrential rain, high wind, fog rolling
in from all directions.  Lightning lights up the sky with screen-flash effects.
There is a **0.5 % chance each tick** that any unsheltered player is struck by
lightning, taking 50 shock damage and additional health damage.  Get inside.
*Weight: 12 out of 100.*

### 🌀 SUPERCELL (**DEADLY** — 5 % weight)
A catastrophic supercell.  Hurricane-force winds.  Maximum rain.  Near-zero fog
visibility.  Players caught outdoors take **1 HP of health damage every 5 seconds**
from direct exposure plus minor blood loss from wind-driven debris.  This is a
server-wide emergency.  The system broadcasts a full-capitalised global warning
message the moment the event triggers.  *Weight: 5 out of 100.*

### ❄️ BLIZZARD (**DEADLY** — 5 % weight)
A deadly winter blizzard.  Extreme fog, howling wind, sleet/snow precipitation.
Players outdoors take **2 HP per 5 seconds** and have their body temperature
forcibly drained at 4× the normal rate — hypothermia onset is almost instant.
Only viable protection is a building with a roof; tents and vehicles also count.
*Weight: 5 out of 100.*

### 🌫 FOG WALL (8 % weight)
A near-total whiteout fog rolls in without warning.  Visibility drops to almost
nothing.  The wind stops completely — unnatural eerie silence.  Navigation
becomes extremely difficult and PvP ranges collapse to knife-fight distances.
*Weight: 8 out of 100.*

### ✨ PERFECT DAY (**RARE** — 5 % weight)
Crystal-clear sky.  Zero overcast.  Zero fog.  A warm, gentle breeze.  These
moments are genuinely rare — when one triggers the server receives a global
broadcast: *"The skies have cleared... a rare perfect day. Cherish it."*
Players will stop fighting (sometimes) just to enjoy it.  *Weight: 5 out of 100.*

### 🌡 HEAT WAVE (7 % weight)
Blazing sun with no cloud cover, hazy shimmer on the horizon.  Players outdoors
have their **water stat drained at 3× the normal rate**.  A full water bottle is
not enough for an extended run across open ground.  *Weight: 7 out of 100.*

---

## Storm Escalation

Storms don't always stay polite.  Two escalation paths exist:

```
RAIN_STORM   ---(15% chance)---> THUNDERSTORM
THUNDERSTORM ---(10% chance)---> SUPERCELL
```

This means a routine rainstorm can quietly escalate into a world-ending supercell
over the course of a single play session.  The 15 % and 10 % chances are
configurable in `data/weather_config.json`.

---

## Player Protection

Players are considered **sheltered** (protected from environmental damage) when
any of the following is true:

1. `IsInBuilding()` returns `true` — they are inside a house, factory, or similar.
2. They are inside a vehicle (cars, trucks, boats, helicopters).
3. A raycast fired 5 m straight up from their head hits solid geometry — covers
   tents, shipping containers, ruins with ceilings, and other covered spaces.

Players in the open — fields, roads, beaches, forest floors — are **fully exposed**
and will receive all applicable damage.

---

## Installation

### PC / Steam Server

1. Copy the `ExtremeWeatherOverhaul/` folder to your mods directory:
   ```
   YourDayZServer/@ExtremeWeatherOverhaul/
   ```
2. Add the mod to your server launch parameters:
   ```
   -mod=@ExtremeWeatherOverhaul
   ```
3. Copy the mod's `.bikey` file to your server's `keys/` directory.
4. Start/restart the server — the system initialises automatically.

### Console / Nitrado Servers

This mod requires custom scripting (`*.c` files) and is therefore **PC/dedicated
server only**.  Console server owners using XML-only server management panels
cannot load this mod.

### Conflict Awareness

This mod calls `weather.MissionWeather(false)` and takes full ownership of the
DayZ weather system.  **Do not load any other mod that also calls
`MissionWeather(false)`** or the two systems will fight over weather control,
producing unpredictable results.  Mods that only read weather (e.g., UI mods
that display current conditions) are fine.

---

## Configuration

Edit `data/weather_config.json` — **no recompilation required** if you use a
mod loader that hot-reads JSON:

```json
{
    "enabled": true,
    "minEventDurationMinutes": 10,
    "maxEventDurationMinutes": 45,
    "transitionTimeSeconds": 180,
    "stormEscalationChance": 0.15,
    "superCellEscalationChance": 0.10,
    "lightningStrikeChance": 0.005,
    "lightningDamage": 50,
    "supercellDamagePerTick": 1.0,
    "blizzardDamagePerTick": 2.0,
    "heatWaveDehydrationMultiplier": 3.0,
    "blizzardHypothermiaMultiplier": 4.0,
    "perfectDayAnnouncement": true,
    "debugLogging": true,
    "weights": {
        "CALM": 20,
        "OVERCAST": 20,
        "RAIN_STORM": 18,
        "THUNDERSTORM": 12,
        "SUPERCELL": 5,
        "BLIZZARD": 5,
        "FOG_WALL": 8,
        "PERFECT_DAY": 5,
        "HEAT_WAVE": 7
    }
}
```

> **Note:** The scripts currently read their constants from compile-time values
> in the `.c` files (matching the JSON defaults).  Full runtime JSON parsing
> requires an additional file-read utility; see **Advanced Tuning** below.

### Key Parameters

| Parameter | Default | Description |
|-----------|---------|-------------|
| `minEventDurationMinutes` | 10 | Shortest a single weather event lasts |
| `maxEventDurationMinutes` | 45 | Longest a single weather event lasts |
| `transitionTimeSeconds` | 180 | Fade time between weather states (3 min) |
| `stormEscalationChance` | 0.15 | Probability RAIN_STORM becomes THUNDERSTORM |
| `superCellEscalationChance` | 0.10 | Probability THUNDERSTORM becomes SUPERCELL |
| `lightningStrikeChance` | 0.005 | Per-player, per-tick chance of lightning |
| `lightningDamage` | 50 | Shock + 50 % health damage per strike |
| `supercellDamagePerTick` | 1.0 | HP drained every 5 s in a SUPERCELL |
| `blizzardDamagePerTick` | 2.0 | HP drained every 5 s in a BLIZZARD |
| `heatWaveDehydrationMultiplier` | 3.0 | Water drain rate multiplier during HEAT_WAVE |
| `blizzardHypothermiaMultiplier` | 4.0 | Temperature drain multiplier during BLIZZARD |
| `weights.*` | see above | Relative chance each event is selected |

---

## Advanced Tuning

### Making the server more deadly

```json
{
    "supercellDamagePerTick": 2.5,
    "blizzardDamagePerTick": 4.0,
    "lightningStrikeChance": 0.02,
    "stormEscalationChance": 0.30,
    "superCellEscalationChance": 0.25
}
```

### Reducing extreme event frequency

Lower the weights for SUPERCELL and BLIZZARD and redistribute to CALM/OVERCAST:

```json
"weights": {
    "CALM": 30,
    "OVERCAST": 25,
    "RAIN_STORM": 18,
    "THUNDERSTORM": 10,
    "SUPERCELL": 2,
    "BLIZZARD": 2,
    "FOG_WALL": 7,
    "PERFECT_DAY": 3,
    "HEAT_WAVE": 3
}
```

### Faster / slower weather cycling

```json
{
    "minEventDurationMinutes": 5,
    "maxEventDurationMinutes": 20,
    "transitionTimeSeconds": 60
}
```

### Disabling the mod without removing it

```json
{
    "enabled": false
}
```

> The `enabled` flag is checked at init time in `MissionWeatherInit.c` — the
> systems simply do not register if it is false.

### Applying runtime JSON config parsing

By default the scripts use compile-time constants that match the JSON defaults.
To wire up full runtime parsing, read `data/weather_config.json` in
`MissionWeatherInit.OnInit()` using `FileExist()` / `OpenFile()` / `FGetContent()`
(available in DayZ Enforce Script), parse the result with `JsonFileLoader`, and
pass the values to `ExtremeWeatherSystem` via setter methods before calling
`Init()`.  The JSON file is already structured to support this.

---

## Performance Considerations

> **Always profile on your specific hardware before deploying to live servers.**

- **Damage tick rate** is 5 seconds.  At 60 players that is 60 iterations × 12
  ticks/min = 720 player-checks per minute.  Each check involves an `IsInBuilding()`
  call plus a raycast.  Raycasts have a CPU cost — if you run a large server with
  50+ players consider raising `DAMAGE_TICK_MS` to `10000` (10 seconds) in
  `StormDamageSystem.c`.

- **Weather transitions** happen every 10–45 minutes and involve only a handful of
  `Weather` API calls with no iteration — negligible cost.

- **`GetGame().GetPlayers()`** re-allocates an array every call.  On high-population
  servers you may wish to cache this array and only refresh it on player
  connect/disconnect events.

- **Broadcast messages** (`player.MessageStatus()`) are cheap but fire for every
  online player on each weather change.  They are not batched — 100-player servers
  will see 100 individual RPC calls per event.  This is standard DayZ practice and
  should not cause issues.

---

## Compatibility

| Condition | Result |
|-----------|--------|
| DayZ 1.23 + | ✅ Fully compatible |
| DayZ 1.22 and below | ⚠️ Weather API may differ — test before deploying |
| Any other mod calling `MissionWeather(false)` | ❌ Conflict — only one mod can own weather |
| Mods that read weather values (HUD, UI) | ✅ Compatible |
| Namalsk map | ⚠️ Namalsk has its own EVR storm system — conflicts possible |
| Console servers | ❌ Requires script compilation — PC/dedicated only |

---

## How It Works — Technical Overview

```
Server start
     │
     ▼  (OnInit fires)
MissionWeatherInit.OnInit()
     │  calls weather.MissionWeather(false)
     │  creates ExtremeWeatherSystem   ──► g_ExtremeWeather
     │  creates StormDamageSystem      ──► g_StormDamage
     │
     ▼  (30 s delay)
ExtremeWeatherSystem.Init()
     │  re-applies weather limits
     │  schedules PickAndApplyNextEvent()
     │
     ▼  (31 s delay)
StormDamageSystem.Init()
     │  schedules DamageTick()
     │
     ┌────────────────────────────────────────────────┐
     │              Main loop (server only)           │
     │                                                │
     │  Every 10–45 min:                              │
     │    PickAndApplyNextEvent()                     │
     │      → RollNextEvent() (weighted rand)         │
     │      → MaybeEscalate() (RAIN→THUNDER→SUPER)   │
     │      → ApplyWeatherEvent() (Weather API calls) │
     │      → BroadcastWeatherMessage() (all players) │
     │                                                │
     │  Every 5 s:                                    │
     │    DamageTick()                                │
     │      → iterate all online players              │
     │      → IsPlayerSheltered() check               │
     │      → apply damage / stat drain if exposed   │
     └────────────────────────────────────────────────┘
```

---

## FAQ

**Q: Players are dying too fast in blizzards.  How do I reduce the damage?**
Lower `blizzardDamagePerTick` in `weather_config.json` (e.g. to `0.5`) and
reduce `blizzardHypothermiaMultiplier` to `2.0`.

**Q: Will lightning ever kill a player outright?**
Yes.  50 shock + 25 health damage (defaults) is immediately lethal to a player
who is already in poor health.  A healthy full-blood player will survive one
strike but will be heavily impaired.  Increase `lightningDamage` if you want
instant kills.

**Q: The fog wall event is making the server unplayable.  Can I remove it?**
Set `"FOG_WALL": 0` in the weights section.  An event with weight 0 will never
be selected.

**Q: Does this work on Livonia / Namalsk / custom maps?**
The weather API is map-independent — it should work on any map.  Namalsk may
have EVR conflicts (see Compatibility table above).  Custom maps with no special
weather scripting will work fine.

**Q: Can players see which weather event is active?**
Not directly — they experience it through visual changes and status messages.
Adding a HUD element that displays the current event name is a straightforward
extension: read `g_ExtremeWeather.GetCurrentEvent()` from a client-side script
and display the result.

---

## License

Free to use on any DayZ server.  Credit appreciated but not required.
Contributions welcome — open a PR or issue on the DayZ Library GitHub.
