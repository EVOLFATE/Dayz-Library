# Mods

This directory contains community-contributed and curated DayZ server configuration mods organized by category. Each mod is a self-contained folder with its XML configuration files and a README explaining installation and tuning.

---

## Structure

```
mods/
└── zombies/                    # Zombie spawn and behavior mods
    └── realistic-everywhere-zeds/   # Full replacement zombie spawn mod
        ├── zombie_territories.xml   # Full replacement territory file
        ├── cfgspawnabletypes.xml    # Companion spawnable types config
        └── README.md                # Installation and tuning guide
```

---

## Available Mods

### Zombies

| Mod | Description | Zones |
|---|---|---|
| [realistic-everywhere-zeds](zombies/realistic-everywhere-zeds/) | Full replacement zombie territory file. Zombies in forests, random hordes, rare mummies, dense map-wide coverage. | 1,037 |

---

## Contributing

To add a new mod:

1. Create a subfolder under the appropriate category (e.g., `mods/zombies/my-mod-name/`)
2. Include your XML configuration file(s)
3. Add a `README.md` explaining what the mod does, how to install it, and any tuning options
4. Open a pull request

See [CONTRIBUTING.md](../CONTRIBUTING.md) for general contribution guidelines.
