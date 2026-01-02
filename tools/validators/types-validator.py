#!/usr/bin/env python3
"""
DayZ Types.xml Validator
Validates types.xml files for common errors and configuration issues.
"""

import xml.etree.ElementTree as ET
import sys
import os
from pathlib import Path

class TypesValidator:
    def __init__(self):
        self.errors = []
        self.warnings = []
        self.item_count = 0
        
    def validate_file(self, filepath):
        """Validate a types.xml file"""
        print(f"Validating: {filepath}")
        print("=" * 50)
        
        if not os.path.exists(filepath):
            self.errors.append(f"File not found: {filepath}")
            return False
        
        try:
            tree = ET.parse(filepath)
            root = tree.getroot()
            
            # Check root element
            if root.tag != 'types':
                self.errors.append(f"Root element should be 'types', found '{root.tag}'")
                return False
            
            # Validate each type entry
            for type_elem in root.findall('type'):
                self.validate_type(type_elem)
                self.item_count += 1
            
            # Print results
            self.print_results()
            
            return len(self.errors) == 0
            
        except ET.ParseError as e:
            self.errors.append(f"XML Parse Error: {e}")
            return False
        except Exception as e:
            self.errors.append(f"Unexpected error: {e}")
            return False
    
    def validate_type(self, type_elem):
        """Validate a single type entry"""
        # Check for name attribute
        name = type_elem.get('name')
        if not name:
            self.errors.append("Type entry missing 'name' attribute")
            return
        
        # Required fields
        required_fields = ['nominal', 'lifetime', 'restock', 'min', 'quantmin', 
                          'quantmax', 'cost', 'flags', 'category']
        
        for field in required_fields:
            elem = type_elem.find(field)
            if elem is None:
                self.warnings.append(f"{name}: Missing field '{field}'")
        
        # Validate numeric values
        self.validate_numeric_field(type_elem, name, 'nominal', min_val=0)
        self.validate_numeric_field(type_elem, name, 'lifetime', min_val=0)
        self.validate_numeric_field(type_elem, name, 'restock', min_val=0)
        self.validate_numeric_field(type_elem, name, 'min', min_val=0)
        self.validate_numeric_field(type_elem, name, 'cost', min_val=0)
        
        # Validate nominal vs min
        nominal_elem = type_elem.find('nominal')
        min_elem = type_elem.find('min')
        
        if nominal_elem is not None and min_elem is not None:
            try:
                nominal = int(nominal_elem.text)
                min_val = int(min_elem.text)
                if min_val > nominal:
                    self.errors.append(f"{name}: 'min' ({min_val}) cannot be greater than 'nominal' ({nominal})")
            except ValueError:
                pass
        
        # Check for usage tags
        usage_tags = type_elem.findall('usage')
        if not usage_tags:
            self.warnings.append(f"{name}: No 'usage' tags defined (item won't spawn)")
        
        # Check for value tags
        value_tags = type_elem.findall('value')
        if not value_tags:
            self.warnings.append(f"{name}: No 'value' tags defined (loot tier not set)")
        
        # Validate flags
        flags_elem = type_elem.find('flags')
        if flags_elem is not None:
            valid_flags = ['count_in_cargo', 'count_in_hoarder', 'count_in_map', 
                          'count_in_player', 'crafted', 'deloot']
            for attr in flags_elem.attrib:
                if attr not in valid_flags:
                    self.warnings.append(f"{name}: Unknown flag '{attr}'")
                    
                value = flags_elem.get(attr)
                if value not in ['0', '1']:
                    self.errors.append(f"{name}: Flag '{attr}' should be 0 or 1, found '{value}'")
    
    def validate_numeric_field(self, type_elem, item_name, field_name, min_val=None, max_val=None):
        """Validate a numeric field"""
        elem = type_elem.find(field_name)
        if elem is not None:
            try:
                value = int(elem.text)
                if min_val is not None and value < min_val:
                    self.errors.append(f"{item_name}: '{field_name}' ({value}) is below minimum ({min_val})")
                if max_val is not None and value > max_val:
                    self.errors.append(f"{item_name}: '{field_name}' ({value}) exceeds maximum ({max_val})")
            except ValueError:
                self.errors.append(f"{item_name}: '{field_name}' must be numeric, found '{elem.text}'")
    
    def print_results(self):
        """Print validation results"""
        print(f"\nValidation Results:")
        print(f"Items validated: {self.item_count}")
        print(f"Errors: {len(self.errors)}")
        print(f"Warnings: {len(self.warnings)}")
        print()
        
        if self.errors:
            print("ERRORS:")
            for error in self.errors:
                print(f"  ❌ {error}")
            print()
        
        if self.warnings:
            print("WARNINGS:")
            for warning in self.warnings:
                print(f"  ⚠️  {warning}")
            print()
        
        if not self.errors and not self.warnings:
            print("✅ All checks passed!")
        elif not self.errors:
            print("✅ No errors found (warnings can be ignored)")
        else:
            print("❌ Validation failed")

def main():
    if len(sys.argv) < 2:
        print("Usage: python types-validator.py <path-to-types.xml>")
        print("\nExample:")
        print("  python types-validator.py ./mpmissions/dayzOffline.chernarusplus/db/types.xml")
        sys.exit(1)
    
    filepath = sys.argv[1]
    validator = TypesValidator()
    
    success = validator.validate_file(filepath)
    sys.exit(0 if success else 1)

if __name__ == "__main__":
    main()
