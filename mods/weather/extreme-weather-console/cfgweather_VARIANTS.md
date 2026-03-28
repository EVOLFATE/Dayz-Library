# cfgweather.xml — Pre-Tuned Variants

Three complete, copy-pasteable `cfgweather.xml` configurations tuned for
different levels of misery.  Pick one, rename it `cfgweather.xml`, and
drop it into your mission folder.

---

## Variant 1 — "APOCALYPSE"

**Profile:** Nearly constant horrible weather.  Perfect days almost never
happen.  Fog is almost always present.  Rain is nearly constant.  Wind is
relentless.  This is survival at its most punishing — players will spend
almost every session soaked, blind, and cold.  A clear sky is a once-a-week
event.

**When to use:** Hardcore/survival-focused servers where you want weather to
be a constant lethal threat.  Not recommended for new-player servers.

```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<!--
  APOCALYPSE VARIANT
  Nearly constant horrible weather. Perfect days almost never happen.
  Fog nearly constant. Rain relentless. Wind never stops.
-->
<weather>

    <!-- OVERCAST — always heavy, rarely clears -->
    <overcast>
        <min>0.4</min>
        <max>1.0</max>
        <changeMin>0.003</changeMin>
        <changeMax>0.015</changeMax>
        <forecastChangeMin>0.1</forecastChangeMin>
        <forecastChangeMax>1.0</forecastChangeMax>
        <forecastTimeMin>180</forecastTimeMin>
        <forecastTimeMax>1200</forecastTimeMax>
        <forecastChangeLimitCoef>0.95</forecastChangeLimitCoef>
    </overcast>

    <!-- FOG — almost always dense, rarely lifts fully -->
    <fog>
        <min>0.3</min>
        <max>1.0</max>
        <changeMin>0.005</changeMin>
        <changeMax>0.02</changeMax>
        <forecastChangeMin>0.1</forecastChangeMin>
        <forecastChangeMax>1.0</forecastChangeMax>
        <forecastTimeMin>180</forecastTimeMin>
        <forecastTimeMax>900</forecastTimeMax>
        <forecastChangeLimitCoef>1.0</forecastChangeLimitCoef>
    </fog>

    <!-- RAIN — near constant downpour, rarely dry -->
    <rain>
        <min>0.2</min>
        <max>1.0</max>
        <changeMin>0.003</changeMin>
        <changeMax>0.018</changeMax>
        <forecastChangeMin>0.0</forecastChangeMin>
        <forecastChangeMax>1.0</forecastChangeMax>
        <forecastTimeMin>180</forecastTimeMin>
        <forecastTimeMax>900</forecastTimeMax>
        <forecastChangeLimitCoef>1.0</forecastChangeLimitCoef>
    </rain>

    <!-- WIND — relentless, never fully calm -->
    <wind>
        <min>0.3</min>
        <max>1.0</max>
        <maxSpeed>35</maxSpeed>
        <functionParams>
            <param>0.2</param>
            <param>0.9</param>
            <param>0.85</param>
            <param>0.5</param>
        </functionParams>
    </wind>

</weather>
```

---

## Variant 2 — "BALANCED HARSH" *(Default)*

**Profile:** The default config included in `cfgweather.xml`.  Extreme and
hazardous but with meaningful contrast — rare perfect days make the misery
feel earned.  Fast weather cycles mean dramatic shifts happen within a single
play session.  This is the recommended starting point for most servers.

**When to use:** General-purpose survival servers wanting extreme weather
without making the game unplayable.  The balance of fog, storms, and rare
clear weather creates the most dynamic player experience.

```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<!--
  BALANCED HARSH VARIANT (default)
  Extreme weather with meaningful contrast. Rare perfect days.
  Fast cycles. Dramatic fog walls. Harsh storms.
-->
<weather>

    <!-- OVERCAST — full range, dramatic swings -->
    <overcast>
        <min>0.0</min>
        <max>1.0</max>
        <changeMin>0.002</changeMin>
        <changeMax>0.012</changeMax>
        <forecastChangeMin>0.0</forecastChangeMin>
        <forecastChangeMax>1.0</forecastChangeMax>
        <forecastTimeMin>300</forecastTimeMin>
        <forecastTimeMax>1800</forecastTimeMax>
        <forecastChangeLimitCoef>0.9</forecastChangeLimitCoef>
    </overcast>

    <!-- FOG — full range, rapid onset fog walls -->
    <fog>
        <min>0.0</min>
        <max>1.0</max>
        <changeMin>0.003</changeMin>
        <changeMax>0.018</changeMax>
        <forecastChangeMin>0.0</forecastChangeMin>
        <forecastChangeMax>1.0</forecastChangeMax>
        <forecastTimeMin>240</forecastTimeMin>
        <forecastTimeMax>1200</forecastTimeMax>
        <forecastChangeLimitCoef>1.0</forecastChangeLimitCoef>
    </fog>

    <!-- RAIN — full range, sudden storm onset -->
    <rain>
        <min>0.0</min>
        <max>1.0</max>
        <changeMin>0.002</changeMin>
        <changeMax>0.015</changeMax>
        <forecastChangeMin>0.0</forecastChangeMin>
        <forecastChangeMax>1.0</forecastChangeMax>
        <forecastTimeMin>300</forecastTimeMin>
        <forecastTimeMax>1500</forecastTimeMax>
        <forecastChangeLimitCoef>0.95</forecastChangeLimitCoef>
    </rain>

    <!-- WIND — dead calm to hurricane force -->
    <wind>
        <min>0.0</min>
        <max>1.0</max>
        <maxSpeed>30</maxSpeed>
        <functionParams>
            <param>0.15</param>
            <param>0.85</param>
            <param>0.75</param>
            <param>0.4</param>
        </functionParams>
    </wind>

</weather>
```

---

## Variant 3 — "FOG NIGHTMARE"

**Profile:** Fog is the primary hazard and it is nearly constant.  Extreme
density fog is almost always present — visibility is perpetually degraded.
Rain is secondary.  Overcast stays high.  Wind is moderate.  Players will
almost never be able to see more than 50–100 metres.  Sniping is essentially
impossible.  Navigation and PvP become extreme close-quarters affairs.

**When to use:** Servers wanting maximum psychological pressure through
visibility loss.  Excellent for horror-themed servers, high-tension PvP
servers where long-range combat is considered too dominant, or any server
wanting to create a genuinely oppressive survival atmosphere.

```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<!--
  FOG NIGHTMARE VARIANT
  Fog is the primary and near-constant hazard. Visibility perpetually
  degraded. Rain secondary. Maximum psychological pressure.
-->
<weather>

    <!-- OVERCAST — always high, never truly clear -->
    <overcast>
        <min>0.5</min>
        <max>1.0</max>
        <changeMin>0.001</changeMin>
        <changeMax>0.008</changeMax>
        <forecastChangeMin>0.0</forecastChangeMin>
        <forecastChangeMax>0.5</forecastChangeMax>
        <forecastTimeMin>600</forecastTimeMin>
        <forecastTimeMax>2400</forecastTimeMax>
        <forecastChangeLimitCoef>0.7</forecastChangeLimitCoef>
    </overcast>

    <!-- FOG — near-constant, maximum density, barely ever lifts -->
    <fog>
        <min>0.5</min>
        <max>1.0</max>
        <changeMin>0.002</changeMin>
        <changeMax>0.012</changeMax>
        <forecastChangeMin>0.0</forecastChangeMin>
        <forecastChangeMax>0.8</forecastChangeMax>
        <forecastTimeMin>600</forecastTimeMin>
        <forecastTimeMax>2400</forecastTimeMax>
        <forecastChangeLimitCoef>1.0</forecastChangeLimitCoef>
    </fog>

    <!-- RAIN — secondary hazard, intermittent moderate rain -->
    <rain>
        <min>0.0</min>
        <max>0.8</max>
        <changeMin>0.001</changeMin>
        <changeMax>0.01</changeMax>
        <forecastChangeMin>0.0</forecastChangeMin>
        <forecastChangeMax>0.8</forecastChangeMax>
        <forecastTimeMin>600</forecastTimeMin>
        <forecastTimeMax>2400</forecastTimeMax>
        <forecastChangeLimitCoef>0.8</forecastChangeLimitCoef>
    </rain>

    <!-- WIND — moderate, eerie stillness punctuated by gusts -->
    <wind>
        <min>0.0</min>
        <max>0.7</max>
        <maxSpeed>20</maxSpeed>
        <functionParams>
            <param>0.1</param>
            <param>0.6</param>
            <param>0.5</param>
            <param>0.3</param>
        </functionParams>
    </wind>

</weather>
```

---

## Quick Comparison

| Variant | Perfect Days | Fog Intensity | Rain | Wind | Overall Feel |
|---------|-------------|---------------|------|------|--------------|
| **APOCALYPSE** | Almost never | Near-constant dense | Near-constant | Relentless | Maximum misery — survival hell |
| **BALANCED HARSH** | Rare (~5-10%) | Frequent walls | Frequent storms | Variable | Extreme but playable |
| **FOG NIGHTMARE** | Never | Always present, often max | Moderate | Calm-ish | Psychological horror, no visibility |

---

## How to Apply a Variant

1. Copy the entire `<weather>...</weather>` XML block from your chosen variant.
2. Create a new file called `cfgweather.xml`.
3. Paste the XML block into the file, replacing any existing content.
4. Upload to your mission folder (see `README.md` for path details).
5. Restart the server.
