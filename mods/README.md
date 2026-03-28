# Mods

This directory contains community-contributed and curated DayZ server configuration mods organized by category. Each mod is a self-contained folder with its XML configuration files and a README explaining installation and tuning.

---

## Structure

```
mods/
├── zombies/                    # Zombie spawn and behavior mods
│   └── realistic-everywhere-zeds/   # Full replacement zombie spawn mod
│       ├── zombie_territories.xml   # Full replacement territory file
│       ├── cfgspawnabletypes.xml    # Companion spawnable types config
│       └── README.md                # Installation and tuning guide
└── animals/                    # Animal spawn and behavior mods
    └── realistic-wildlife-overhaul/ # Full replacement wildlife mod
        ├── events.xml               # All animal events (counts, pack sizes)
        ├── cfgeventspawns.xml       # Links events to territory files
        ├── README.md                # Installation and tuning guide
        └── env/                     # Territory files (one per species)
            ├── hare_territories.xml
            ├── roe_deer_territories.xml
            ├── red_deer_territories.xml
            ├── wild_boar_territories.xml
            ├── hen_territories.xml
            ├── cattle_territories.xml
            ├── sheep_goat_territories.xml
            ├── pig_territories.xml
            ├── domestic_animals_territories.xml
            ├── fox_territories.xml
            ├── wolf_territories.xml
            └── bear_territories.xml
```

---

## Available Mods

### Zombies

| Mod | Description | Zones |
|---|---|---|
| [realistic-everywhere-zeds](zombies/realistic-everywhere-zeds/) | Full replacement zombie territory file. Zombies in forests, random hordes, rare mummies, dense map-wide coverage. | 1,037 |

### Animals

| Mod | Description | Files |
|---|---|---|
| [realistic-wildlife-overhaul](animals/realistic-wildlife-overhaul/) | Full replacement wildlife mod for Chernarus+. Prey animals everywhere, wolves across the entire map (not just far north), bears near rivers and farms, foxes hunting hens. Designed for hunting-as-survival servers. | 14 |

---

## Contributing

To add a new mod:

1. Create a subfolder under the appropriate category (e.g., `mods/zombies/my-mod-name/`)
2. Include your XML configuration file(s)
3. Add a `README.md` explaining what the mod does, how to install it, and any tuning options
4. Open a pull request

See [CONTRIBUTING.md](../CONTRIBUTING.md) for general contribution guidelines.
