#!/usr/bin/env python3
"""
DayZ Link Checker
Checks all markdown files for broken links.
"""

import os
import re
from pathlib import Path

class LinkChecker:
    def __init__(self, root_dir):
        self.root_dir = Path(root_dir)
        self.broken_links = []
        self.total_links = 0
        
    def check_all_markdown_files(self):
        """Check all markdown files in the repository"""
        print("Scanning for markdown files...")
        
        md_files = list(self.root_dir.rglob("*.md"))
        print(f"Found {len(md_files)} markdown files\n")
        
        for md_file in md_files:
            self.check_file(md_file)
        
        self.print_results()
    
    def check_file(self, filepath):
        """Check a single markdown file for broken links"""
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                content = f.read()
            
            # Find all markdown links
            links = re.findall(r'\[([^\]]+)\]\(([^\)]+)\)', content)
            
            for text, link in links:
                self.total_links += 1
                
                # Skip external links
                if link.startswith('http://') or link.startswith('https://'):
                    continue
                
                # Skip anchors only
                if link.startswith('#'):
                    # Could validate anchor exists, but skip for now
                    continue
                
                # Remove anchor from link
                link_path = link.split('#')[0]
                if not link_path:
                    continue
                
                # Resolve relative path
                if link_path.startswith('/'):
                    # Absolute path from root
                    full_path = self.root_dir / link_path.lstrip('/')
                else:
                    # Relative path from current file
                    full_path = (filepath.parent / link_path).resolve()
                
                # Check if file exists
                if not full_path.exists():
                    self.broken_links.append({
                        'file': str(filepath.relative_to(self.root_dir)),
                        'link': link,
                        'text': text
                    })
                    
        except Exception as e:
            print(f"Error checking {filepath}: {e}")
    
    def print_results(self):
        """Print check results"""
        print("=" * 60)
        print("Link Check Results")
        print("=" * 60)
        print(f"Total links checked: {self.total_links}")
        print(f"Broken links found: {len(self.broken_links)}")
        print()
        
        if self.broken_links:
            print("BROKEN LINKS:")
            
            # Group by file
            by_file = {}
            for broken in self.broken_links:
                file = broken['file']
                if file not in by_file:
                    by_file[file] = []
                by_file[file].append(broken)
            
            for file, links in sorted(by_file.items()):
                print(f"\n📄 {file}")
                for link in links:
                    print(f"  ❌ [{link['text']}]({link['link']})")
            
            print()
            print("❌ Link check failed")
        else:
            print("✅ All links are valid!")

def main():
    import sys
    
    if len(sys.argv) > 1:
        root_dir = sys.argv[1]
    else:
        # Default to current directory
        root_dir = "."
    
    checker = LinkChecker(root_dir)
    checker.check_all_markdown_files()
    
    sys.exit(0 if not checker.broken_links else 1)

if __name__ == "__main__":
    main()
