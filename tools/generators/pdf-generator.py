#!/usr/bin/env python3
"""
Quick Reference PDF Generator
Generates a printable PDF cheat sheet from the quick reference markdown
"""

import argparse
from pathlib import Path

def generate_html_for_pdf():
    """Generate HTML optimized for PDF printing"""
    
    html_content = """
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>DayZ Quick Reference Cheat Sheet</title>
    <style>
        @page {
            size: A4;
            margin: 1cm;
        }
        
        body {
            font-family: 'Arial', sans-serif;
            font-size: 10pt;
            line-height: 1.4;
            color: #333;
            max-width: 100%;
        }
        
        h1 {
            color: #2c3e50;
            font-size: 20pt;
            border-bottom: 3px solid #3498db;
            padding-bottom: 5px;
            margin-top: 0;
            text-align: center;
        }
        
        h2 {
            color: #34495e;
            font-size: 14pt;
            border-bottom: 2px solid #95a5a6;
            padding-bottom: 3px;
            margin-top: 15px;
            margin-bottom: 8px;
            page-break-after: avoid;
        }
        
        h3 {
            color: #7f8c8d;
            font-size: 11pt;
            margin-top: 10px;
            margin-bottom: 5px;
            page-break-after: avoid;
        }
        
        code {
            background: #ecf0f1;
            padding: 2px 5px;
            border-radius: 3px;
            font-family: 'Courier New', monospace;
            font-size: 9pt;
        }
        
        pre {
            background: #2c3e50;
            color: #ecf0f1;
            padding: 10px;
            border-radius: 5px;
            overflow-x: auto;
            font-size: 8pt;
            page-break-inside: avoid;
        }
        
        pre code {
            background: none;
            color: inherit;
            padding: 0;
        }
        
        table {
            width: 100%;
            border-collapse: collapse;
            margin: 10px 0;
            font-size: 9pt;
            page-break-inside: avoid;
        }
        
        th, td {
            border: 1px solid #bdc3c7;
            padding: 5px 8px;
            text-align: left;
        }
        
        th {
            background: #3498db;
            color: white;
            font-weight: bold;
        }
        
        tr:nth-child(even) {
            background: #ecf0f1;
        }
        
        .section {
            page-break-inside: avoid;
            margin-bottom: 15px;
        }
        
        .two-column {
            columns: 2;
            column-gap: 15px;
        }
        
        .box {
            border: 2px solid #3498db;
            padding: 10px;
            margin: 10px 0;
            border-radius: 5px;
            background: #ebf5fb;
            page-break-inside: avoid;
        }
        
        .warning {
            border-color: #e74c3c;
            background: #fadbd8;
        }
        
        .success {
            border-color: #27ae60;
            background: #d4edda;
        }
        
        ul, ol {
            margin: 5px 0;
            padding-left: 20px;
        }
        
        li {
            margin: 3px 0;
        }
        
        .footer {
            position: fixed;
            bottom: 0;
            width: 100%;
            text-align: center;
            font-size: 8pt;
            color: #7f8c8d;
            padding: 5px 0;
            border-top: 1px solid #bdc3c7;
        }
        
        @media print {
            .no-print {
                display: none;
            }
        }
    </style>
</head>
<body>
    <h1>🎮 DayZ Quick Reference Cheat Sheet</h1>
    
    <div class="box">
        <strong>📖 Documentation:</strong> github.com/EVOLFATE/Dayz-Library | 
        <strong>Version:</strong> 2.0 | 
        <strong>Updated:</strong> January 2026
    </div>
    
    <div class="section">
        <h2>🔧 Configuration Files</h2>
        
        <h3>types.xml - Loot Economy</h3>
        <pre><code>&lt;type name="ItemName"&gt;
    &lt;nominal&gt;10&lt;/nominal&gt;     &lt;!-- Target spawn count --&gt;
    &lt;min&gt;5&lt;/min&gt;              &lt;!-- Minimum guaranteed --&gt;
    &lt;lifetime&gt;3600&lt;/lifetime&gt;  &lt;!-- Cleanup time (seconds) --&gt;
    &lt;restock&gt;1800&lt;/restock&gt;    &lt;!-- Respawn time (seconds) --&gt;
    &lt;category name="weapons"/&gt; &lt;!-- Item category --&gt;
    &lt;usage name="Military"/&gt;   &lt;!-- Spawn location --&gt;
    &lt;value name="Tier2"/&gt;      &lt;!-- Loot tier --&gt;
&lt;/type&gt;</code></pre>
        
        <h3>config.cpp - Mod Configuration</h3>
        <pre><code>class CfgPatches {
    class YourMod {
        requiredAddons[] = {"DZ_Data"};
    };
};
class CfgMods {
    class YourMod {
        dir = "YourMod";
        name = "Your Mod Name";
        dependencies[] = {"Game", "World", "Mission"};
    };
};</code></pre>
    </div>
    
    <div class="two-column">
        <div class="section">
            <h2>💻 Common Code Snippets</h2>
            
            <h3>Spawn Item</h3>
            <pre><code>vector pos = "7500 0 5500";
pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
EntityAI item = GetGame().CreateObject("AKM", pos);</code></pre>
            
            <h3>Give Health</h3>
            <pre><code>player.AddHealth("", "Health", 25);
player.AddHealth("", "Blood", 50);
player.GetStatEnergy().Add(100);</code></pre>
            
            <h3>Send Message</h3>
            <pre><code>player.MessageStatus("Your message");
player.MessageAction("Action message");</code></pre>
        </div>
        
        <div class="section">
            <h2>📊 Common Values</h2>
            
            <h3>Loot Tiers</h3>
            <ul>
                <li><strong>Tier1</strong> - Common items</li>
                <li><strong>Tier2</strong> - Uncommon items</li>
                <li><strong>Tier3</strong> - Rare items</li>
                <li><strong>Tier4</strong> - Very rare items</li>
            </ul>
            
            <h3>Usage Types</h3>
            <ul>
                <li><strong>Military</strong> - Military buildings</li>
                <li><strong>Police</strong> - Police stations</li>
                <li><strong>Town</strong> - Urban areas</li>
                <li><strong>Village</strong> - Small settlements</li>
                <li><strong>Farm</strong> - Agricultural</li>
                <li><strong>Hunting</strong> - Hunting locations</li>
                <li><strong>Industrial</strong> - Factories</li>
            </ul>
        </div>
    </div>
    
    <div class="section">
        <h2>🎯 Quick Troubleshooting</h2>
        
        <table>
            <tr>
                <th>Problem</th>
                <th>Quick Fix</th>
            </tr>
            <tr>
                <td>Server Won't Start</td>
                <td>Check logs → Verify config syntax → Check mod load order</td>
            </tr>
            <tr>
                <td>Mod Not Loading</td>
                <td>Check -mod= parameter → Verify signatures → Check console errors</td>
            </tr>
            <tr>
                <td>Items Not Spawning</td>
                <td>Check nominal/min → Verify usage tags → Restart economy</td>
            </tr>
            <tr>
                <td>BattlEye Kicks</td>
                <td>Check filters → Add exceptions → Verify signatures</td>
            </tr>
        </table>
    </div>
    
    <div class="section">
        <h2>🛠️ Server Management</h2>
        
        <h3>Start Server (Linux)</h3>
        <pre><code>./DayZServer -config=serverDZ.cfg -port=2302 \\
  -profiles=profiles -mod=@CF;@YourMod</code></pre>
        
        <h3>View Logs</h3>
        <pre><code>tail -f server_console.log</code></pre>
    </div>
    
    <div class="box success">
        <strong>💡 Pro Tips:</strong>
        <ul>
            <li>Always validate configs before deployment</li>
            <li>Test mods on local server first</li>
            <li>Keep backups of working configurations</li>
            <li>Check logs when something doesn't work</li>
        </ul>
    </div>
    
    <div class="footer no-print">
        DayZ Library - Complete Modding Resource | github.com/EVOLFATE/Dayz-Library
    </div>
</body>
</html>
    """
    
    return html_content


def main():
    parser = argparse.ArgumentParser(description='Generate PDF-ready cheat sheet')
    parser.add_argument('-o', '--output', default='quick-reference.html',
                       help='Output HTML file (default: quick-reference.html)')
    
    args = parser.parse_args()
    
    print("Generating PDF-ready cheat sheet...")
    
    html = generate_html_for_pdf()
    
    output_path = Path(args.output)
    output_path.write_text(html, encoding='utf-8')
    
    print(f"✅ Generated: {output_path}")
    print("\n📄 To convert to PDF:")
    print("   1. Open the HTML file in a browser")
    print("   2. Press Ctrl+P (Cmd+P on Mac)")
    print("   3. Select 'Save as PDF'")
    print("   4. Adjust margins if needed")
    print("\n   Or use a tool like wkhtmltopdf:")
    print(f"   wkhtmltopdf {output_path} quick-reference.pdf")


if __name__ == '__main__':
    main()
