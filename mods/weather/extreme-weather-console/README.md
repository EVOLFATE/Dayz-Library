# Extreme Weather — Console Edition

A **console-compatible weather configuration** for DayZ that uses only
`cfgweather.xml` — no scripts, no mods, no `.bikey` files.  Delivers the
most extreme, hazardous, realistic weather possible on Xbox, PlayStation,
Nitrado, and PC servers.

Think catastrophic fog walls that reduce visibility to metres, sudden
torrential downpours, howling hurricane-force winds — and, very rarely, a
crystal-clear perfect day that feels like a gift.

---

## How This Differs from the PC Script Version

| Feature | PC Script Version (`extreme-weather-overhaul/`) | This Console Version |
|---------|------------------------------------------------|---------------------|
| Installation method | `.c` script files + mod loader | Single XML file drop |
| Console / Nitrado | ❌ PC/dedicated only | ✅ Works everywhere |
| Weather damage system | ✅ Active (HP drain, hypothermia) | ❌ XML cannot apply damage |
| Storm escalation logic | ✅ RAIN → THUNDER → SUPERCELL | ❌ XML-only, no escalation |
| Weather event names | Named events with broadcasts | Seamless parameter blending |
| Player announcements | ✅ Global server messages | ❌ Not available in XML |
| Visual intensity | ✅ Extreme | ✅ Extreme |
| Fog walls | ✅ Scripted instant fog event | ✅ Rapid-onset XML fog |
| Configuration | JSON config file | Edit XML values directly |

**Bottom line:** the PC version gives you named events, player damage, and
server broadcasts.  This console version gives you identical (and in some
cases more extreme) *visual* weather intensity with zero script requirements.
If you run a PC/dedicated server and want damage systems, use
`mods/weather/extreme-weather-overhaul/` instead.

---

## Contents

| File | Purpose |
|------|---------|
| `cfgweather.xml` | Drop-in weather config — the only file you need |
| `cfgweather_VARIANTS.md` | Three pre-tuned variant configs to copy-paste |
| `README.md` | This file |

---

## Weather Behaviour — What Players Experience

### 🌤 Rare Perfect Days (~5-10 % of the time)
Zero overcast, zero fog, zero rain, dead-calm wind.  The world looks
stunning.  These moments are genuinely rare — the contrast makes them
feel earned.  When it happens, players will stop and notice.

### 🌫 Heavy Fog / Fog Walls (~25-30 % of the time)
Near-total whiteout conditions roll in without warning.  Visibility
collapses to metres.  Navigation becomes nearly impossible.  PvP ranges
shrink to knife-fight distances.  Fog is the single most disorienting
hazard this config delivers — it comes and goes fast and unpredictably.

### ⛈ Harsh Rain Storms (~30-35 % of the time)
Full maximum overcast, torrential downpours, howling wind.  Wet clothing
accelerates cold stat loss.  Running in the open becomes genuinely
miserable.  Storms arrive fast — short forecast times mean little warning.

### ☁️ Mixed / Transitional (~20-25 % of the time)
Heavy overcast building or clearing.  Intermittent rain.  The feeling that
something worse is coming.  Unsettling and oppressive.

### 🌥 Calm but Gloomy (~5-10 % of the time)
No precipitation.  Low wind.  But still heavy cloud — never truly relaxing
unless it's a perfect day.

---

## Installation

### Console Servers (Xbox / PlayStation / Nitrado)

1. Connect to your server via FTP (Nitrado: File Browser → FTP Credentials).
2. Navigate to your mission folder:
   ```
   /games/<your-server>/nfsshares/mpmissions/dayzOffline.chernarusplus/
   ```
   *(Replace `chernarusplus` with your map name — `enoch` for Livonia, etc.)*
3. Upload `cfgweather.xml` directly into that mission folder.
4. **No other files required.**  No mod folder.  No keys.
5. Restart your server.

> **Nitrado tip:** On Nitrado console servers, the mission folder path is
> usually found under **Expert Mode -> Config Files** or via the FTP path
> shown in your Nitrado dashboard.

### PC / Steam Dedicated Server

1. Navigate to your mission folder:
   ```
   YourDayZServer/mpmissions/dayzOffline.chernarusplus/
   ```
2. Drop `cfgweather.xml` into that folder.
3. No launch parameter changes needed — the game reads `cfgweather.xml`
   automatically if it exists in the mission folder.
4. Restart the server.

### Verifying It Worked

After restart, join the server.  Within the first few minutes of play you
should notice significantly more dramatic weather — heavy fog events, fast
overcast changes, and sudden storms.  If weather feels exactly like vanilla,
double-check the file is in the **mission folder** (not the server root or
mod folder).

---

## Parameter Reference

Every value you might want to tune:

### Overcast (`<overcast>`)

| Parameter | Default | Description |
|-----------|---------|-------------|
| `min` | 0.0 | Minimum cloud cover — 0.0 allows clear skies |
| `max` | 1.0 | Maximum cloud cover — 1.0 is full pitch-black overcast |
| `changeMin` | 0.002 | Slowest per-tick overcast change rate |
| `changeMax` | 0.012 | Fastest per-tick overcast change rate |
| `forecastChangeMin` | 0.0 | Smallest swing a forecast update can make |
| `forecastChangeMax` | 1.0 | Largest swing — allows clear→overcast in one step |
| `forecastTimeMin` | 300 | Shortest interval between forecast updates (seconds) |
| `forecastTimeMax` | 1800 | Longest interval between forecast updates (seconds) |
| `forecastChangeLimitCoef` | 0.9 | How far a single update can push overcast (0–1) |

### Fog (`<fog>`)

| Parameter | Default | Description |
|-----------|---------|-------------|
| `min` | 0.0 | No fog during perfect days |
| `max` | 1.0 | Absolute near-zero visibility whiteout |
| `changeMin` | 0.003 | Fog rolls in at this minimum speed per tick |
| `changeMax` | 0.018 | Fog walls arrive at this maximum speed per tick |
| `forecastChangeMin` | 0.0 | Can forecast zero fog change (hold clear) |
| `forecastChangeMax` | 1.0 | Can forecast full fog swing — instant walls |
| `forecastTimeMin` | 240 | Very short minimum — fog is unpredictable (seconds) |
| `forecastTimeMax` | 1200 | Maximum hold time (seconds) |
| `forecastChangeLimitCoef` | 1.0 | Max — allows single-tick full fog-range swing |

### Rain (`<rain>`)

| Parameter | Default | Description |
|-----------|---------|-------------|
| `min` | 0.0 | Dry during calm/perfect weather |
| `max` | 1.0 | Maximum torrential downpour |
| `changeMin` | 0.002 | Gentle onset minimum |
| `changeMax` | 0.015 | Fast storm onset maximum |
| `forecastChangeMin` | 0.0 | Can forecast dry periods |
| `forecastChangeMax` | 1.0 | Can forecast full storm in one step |
| `forecastTimeMin` | 300 | Storms arrive quickly (seconds) |
| `forecastTimeMax` | 1500 | Moderate maximum hold time (seconds) |
| `forecastChangeLimitCoef` | 0.95 | Near-maximum — full storm onset in one tick |

### Wind (`<wind>`)

| Parameter | Default | Description |
|-----------|---------|-------------|
| `min` | 0.0 | Dead calm during perfect days |
| `max` | 1.0 | Maximum base wind |
| `maxSpeed` | 30 | Hurricane-force maximum gust speed (m/s) |
| `functionParams[0]` | 0.15 | Base wind multiplier offset |
| `functionParams[1]` | 0.85 | Gust amplitude — higher = wilder gusts |
| `functionParams[2]` | 0.75 | Gust frequency / turbulence level |
| `functionParams[3]` | 0.4 | Directional drift rate |

---

## Tuning Tips

### To make perfect days even rarer
Keep `<overcast>` `<min>` at 0.0 but reduce `forecastChangeMax` slightly so the
engine is less likely to swing all the way to zero:
```xml
<forecastChangeMin>0.3</forecastChangeMin>
<forecastChangeMax>1.0</forecastChangeMax>
```

### To make fog more constant (less clearing)
Raise fog `min` so it never fully clears:
```xml
<min>0.15</min>
```

### To slow down weather cycling
Increase both forecast time values:
```xml
<forecastTimeMin>900</forecastTimeMin>
<forecastTimeMax>3600</forecastTimeMax>
```

### To make weather cycle even faster
Lower forecast time values (minimum ~120 seconds to avoid engine jank):
```xml
<forecastTimeMin>120</forecastTimeMin>
<forecastTimeMax>600</forecastTimeMax>
```

### To reduce wind intensity
Lower `maxSpeed` and reduce gust amplitude:
```xml
<maxSpeed>15</maxSpeed>
<!-- functionParams -->
<param>0.1</param>
<param>0.5</param>
<param>0.4</param>
<param>0.2</param>
```

### To cap fog so it never fully whiteouts
Lower fog `max`:
```xml
<max>0.75</max>
```

---

## Three Pre-Tuned Variants

See `cfgweather_VARIANTS.md` for three ready-to-use complete configs:

1. **APOCALYPSE** — nearly constant horrible weather, perfect days almost
   never happen, fog almost always present, rain almost constant
2. **BALANCED HARSH** — the default config (this file), described above
3. **FOG NIGHTMARE** — fog is the primary hazard, nearly constant maximum
   density fog, rain secondary, overcast always high

---

## Compatibility

| Platform | Status |
|----------|--------|
| Xbox console servers | ✅ Fully compatible |
| PlayStation console servers | ✅ Fully compatible |
| Nitrado hosted servers | ✅ Fully compatible |
| PC / Steam dedicated servers | ✅ Fully compatible |
| DayZ 1.23+ | ✅ Fully compatible |
| DayZ 1.22 and below | ⚠️ XML schema may differ — test first |
| Vanilla weather (no cfgweather.xml) | ✅ This file replaces it cleanly |
| Combined with PC script weather mods | ❌ Conflict — the script mod will override XML |
| Namalsk (EVR storm system) | ⚠️ Namalsk overrides weather — limited effect |
| Any other map with no special weather scripting | ✅ Compatible |

---

## License

Free to use on any DayZ server.  Credit appreciated but not required.
Contributions welcome — open a PR or issue on the DayZ Library GitHub.
