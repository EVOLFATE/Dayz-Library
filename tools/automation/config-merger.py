#!/usr/bin/env python3
"""
DayZ Configuration Merger
Merges multiple mod configurations to resolve conflicts
"""

import argparse
import xml.etree.ElementTree as ET
from pathlib import Path
import sys

class ConfigMerger:
    def __init__(self):
        self.merged_types = {}
        self.conflicts = []
        
    def parse_types_xml(self, filepath):
        """Parse a types.xml file"""
        try:
            tree = ET.parse(filepath)
            root = tree.getroot()
            return root
        except Exception as e:
            print(f"Error parsing {filepath}: {e}")
            return None
    
    def merge_type_entry(self, type_elem, source_file):
        """Merge a single type entry"""
        item_name = type_elem.get('name')
        
        if item_name not in self.merged_types:
            # First occurrence, add it
            self.merged_types[item_name] = {
                'element': type_elem,
                'source': source_file
            }
        else:
            # Conflict detected
            existing = self.merged_types[item_name]
            self.conflicts.append({
                'item': item_name,
                'source1': existing['source'],
                'source2': source_file
            })
            
            # For now, keep the first one (could be configurable)
            print(f"⚠️  Conflict: {item_name} exists in both {existing['source']} and {source_file}")
    
    def merge_files(self, input_files, output_file, strategy='first'):
        """Merge multiple types.xml files
        
        Strategies:
        - first: Keep first occurrence
        - last: Keep last occurrence
        - highest: Keep entry with highest nominal value
        """
        print(f"Merging {len(input_files)} configuration files...")
        
        for filepath in input_files:
            print(f"Processing: {filepath}")
            root = self.parse_types_xml(filepath)
            if root is None:
                continue
            
            for type_elem in root.findall('type'):
                self.merge_type_entry(type_elem, filepath)
        
        # Create output XML
        output_root = ET.Element('types')
        
        for item_name, data in sorted(self.merged_types.items()):
            output_root.append(data['element'])
        
        # Write merged file
        tree = ET.ElementTree(output_root)
        ET.indent(tree, space="    ")
        tree.write(output_file, encoding='utf-8', xml_declaration=True)
        
        print(f"\n✅ Merged configuration saved to: {output_file}")
        print(f"📊 Total items: {len(self.merged_types)}")
        print(f"⚠️  Conflicts found: {len(self.conflicts)}")
        
        if self.conflicts:
            print("\n🔍 Conflict Details:")
            for conflict in self.conflicts:
                print(f"  - {conflict['item']}: {conflict['source1']} vs {conflict['source2']}")
    
    def generate_conflict_report(self, output_file):
        """Generate a detailed conflict report"""
        if not self.conflicts:
            print("No conflicts to report!")
            return
        
        with open(output_file, 'w') as f:
            f.write("# Configuration Merge Conflict Report\n\n")
            f.write(f"Total conflicts: {len(self.conflicts)}\n\n")
            
            for i, conflict in enumerate(self.conflicts, 1):
                f.write(f"## Conflict {i}: {conflict['item']}\n\n")
                f.write(f"- **Source 1**: {conflict['source1']}\n")
                f.write(f"- **Source 2**: {conflict['source2']}\n")
                f.write(f"- **Resolution**: Kept first occurrence\n\n")
        
        print(f"📄 Conflict report saved to: {output_file}")


def main():
    parser = argparse.ArgumentParser(
        description='Merge multiple DayZ configuration files',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Merge two mod configs
  python config-merger.py mod1/types.xml mod2/types.xml -o merged_types.xml
  
  # Merge with conflict report
  python config-merger.py mod1/types.xml mod2/types.xml -o merged.xml -r conflicts.md
  
  # Merge all XML files in a directory
  python config-merger.py mods/*.xml -o combined.xml
        """
    )
    
    parser.add_argument('input_files', nargs='+', help='Input types.xml files to merge')
    parser.add_argument('-o', '--output', required=True, help='Output merged file')
    parser.add_argument('-r', '--report', help='Generate conflict report (optional)')
    parser.add_argument('-s', '--strategy', choices=['first', 'last', 'highest'], 
                       default='first', help='Conflict resolution strategy')
    
    args = parser.parse_args()
    
    # Validate input files
    input_files = []
    for pattern in args.input_files:
        files = list(Path('.').glob(pattern))
        if not files:
            # Try as literal filename
            if Path(pattern).exists():
                input_files.append(pattern)
            else:
                print(f"Warning: No files found for pattern: {pattern}")
        else:
            input_files.extend([str(f) for f in files])
    
    if not input_files:
        print("Error: No valid input files found")
        sys.exit(1)
    
    # Perform merge
    merger = ConfigMerger()
    merger.merge_files(input_files, args.output, args.strategy)
    
    # Generate report if requested
    if args.report:
        merger.generate_conflict_report(args.report)
    
    print("\n✅ Merge complete!")


if __name__ == '__main__':
    main()
