# Validators

## Overview
This directory contains validation tools for DayZ configuration files and documentation.

## Available Tools

### 1. types-validator.py
**Validates types.xml files for common errors**

Features:
- ✅ XML structure validation
- ✅ Required field checking
- ✅ Numeric value validation
- ✅ Logical consistency checks (nominal vs min)
- ✅ Flag validation
- ✅ Usage and tier warnings

Usage:
```bash
python types-validator.py /path/to/types.xml
```

Example:
```bash
python types-validator.py ./mpmissions/dayzOffline.chernarusplus/db/types.xml
```

Output:
```
Validating: types.xml
==================================================

Validation Results:
Items validated: 150
Errors: 2
Warnings: 5

ERRORS:
  ❌ CustomWeapon: 'min' (15) cannot be greater than 'nominal' (10)
  ❌ CustomFood: Flag 'count_in_cargo' should be 0 or 1, found '2'

WARNINGS:
  ⚠️  CustomItem: No 'usage' tags defined (item won't spawn)
```

### 2. link-checker.py
**Checks all markdown files for broken links**

Features:
- ✅ Scans all .md files in repository
- ✅ Validates internal links
- ✅ Checks file existence
- ✅ Groups broken links by file
- ✅ Skips external URLs (for now)

Usage:
```bash
python link-checker.py [root_directory]
```

Example:
```bash
# Check from current directory
python link-checker.py

# Check from specific directory
python link-checker.py /path/to/Dayz-Library
```

Output:
```
============================================================
Link Check Results
============================================================
Total links checked: 205
Broken links found: 3

BROKEN LINKS:

📄 README.md
  ❌ [Missing Guide](docs/guides/missing.md)
  
📄 docs/NAVIGATION.md
  ❌ [Old Link](old-file.md)
```

## Installation

Requirements:
- Python 3.6+
- No external dependencies (uses standard library only)

```bash
# Make scripts executable (Linux/Mac)
chmod +x types-validator.py
chmod +x link-checker.py

# Run directly
./types-validator.py types.xml
./link-checker.py
```

## Integration

### Pre-commit Hook
Add to `.git/hooks/pre-commit`:
```bash
#!/bin/bash
python tools/validators/link-checker.py
if [ $? -ne 0 ]; then
    echo "❌ Link validation failed"
    exit 1
fi
```

### CI/CD
Add to your CI pipeline:
```yaml
- name: Validate Links
  run: python tools/validators/link-checker.py
  
- name: Validate Types.xml
  run: python tools/validators/types-validator.py mission/db/types.xml
```

## Contributing
Have ideas for more validators? We welcome:
- JSON config validators
- Script syntax checkers
- PBO structure validators
- Economy balance analyzers

See [CONTRIBUTING.md](../../CONTRIBUTING.md) for guidelines.

---

**Status**: ✅ Active - 2 Tools Available  
**Last Updated**: January 2026  
**Contributions Welcome**: Yes!
