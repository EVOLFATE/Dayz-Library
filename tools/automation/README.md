# DayZ Library - Automation Tools

This directory contains automation tools for common DayZ server administration tasks.

## Available Tools

### 🔧 config-merger.py

Merge multiple mod configuration files to resolve conflicts.

**Features:**
- Merge types.xml from multiple mods
- Detect and report conflicts
- Multiple merge strategies
- Detailed conflict reporting

**Usage:**

```bash
# Basic merge
python config-merger.py mod1/types.xml mod2/types.xml -o merged_types.xml

# With conflict report
python config-merger.py mod1/types.xml mod2/types.xml -o merged.xml -r conflicts.md

# Merge all mods in a directory
python config-merger.py mods/*/types.xml -o combined.xml

# Use different strategy (keep last occurrence)
python config-merger.py file1.xml file2.xml -o output.xml -s last
```

**Strategies:**
- `first` (default) - Keep first occurrence of conflicting items
- `last` - Keep last occurrence
- `highest` - Keep entry with highest nominal value

**Example Output:**
```
Merging 3 configuration files...
Processing: mod1/types.xml
Processing: mod2/types.xml
Processing: mod3/types.xml
⚠️  Conflict: AKM exists in both mod1/types.xml and mod2/types.xml

✅ Merged configuration saved to: merged_types.xml
📊 Total items: 1,234
⚠️  Conflicts found: 15
```

### 🎯 Planned Tools

- **backup-manager.py** - Automated backup and restore
- **batch-converter.py** - Convert between XML and JSON
- **performance-profiler.py** - Analyze server performance
- **mod-updater.py** - Check for mod updates
- **log-analyzer.py** - Parse and analyze server logs

## Requirements

```bash
pip install lxml  # For XML parsing
```

## Integration with CI/CD

These tools can be integrated into your deployment pipeline:

```yaml
# GitHub Actions example
- name: Merge mod configs
  run: |
    python tools/automation/config-merger.py \
      mods/*/types.xml \
      -o server/types.xml \
      -r artifacts/conflicts.md
```

## Contributing

When adding new automation tools:

1. Follow the existing code style
2. Add comprehensive error handling
3. Include usage examples in this README
4. Add tests if applicable
5. Document all options and parameters

## Support

For issues or questions:
- Check the [main documentation](../../docs/)
- Review existing issues on GitHub
- Create a new issue with the `automation` label
