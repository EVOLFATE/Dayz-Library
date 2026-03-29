#!/usr/bin/env bash
# validate.sh — XML well-formedness checker for mods/server-setup
#
# Usage:  bash validate.sh
# Returns exit code 0 if all XML files parse cleanly, 1 if any errors are found.
#
# Requires xmllint (libxml2) or Python 3 (used as fallback).

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

ERRORS=0
CHECKED=0

# Collect all XML files relative to this script's directory
mapfile -t XML_FILES < <(find "$SCRIPT_DIR" -name "*.xml" | sort)

# ---------------------------------------------------------------------------
# Choose parser
# ---------------------------------------------------------------------------
if command -v xmllint &>/dev/null; then
    validate_file() {
        xmllint --noout "$1" 2>&1
    }
    PARSER="xmllint"
elif command -v python3 &>/dev/null; then
    validate_file() {
        python3 - "$1" <<'PYEOF'
import sys, xml.etree.ElementTree as ET
try:
    ET.parse(sys.argv[1])
except ET.ParseError as e:
    print(f"{sys.argv[1]}: {e}", file=sys.stderr)
    sys.exit(1)
PYEOF
    }
    PARSER="python3 xml.etree.ElementTree"
else
    echo "ERROR: Neither xmllint nor python3 is available. Install one and re-run." >&2
    exit 1
fi

echo "Using parser: $PARSER"
echo "Checking ${#XML_FILES[@]} XML files under $SCRIPT_DIR"
echo "---"

# ---------------------------------------------------------------------------
# Validate each file
# ---------------------------------------------------------------------------
for f in "${XML_FILES[@]}"; do
    rel="${f#$SCRIPT_DIR/}"
    output=$(validate_file "$f" 2>&1)
    status=$?
    CHECKED=$((CHECKED + 1))
    if [ $status -ne 0 ]; then
        echo "FAIL  $rel"
        echo "      $output"
        ERRORS=$((ERRORS + 1))
    else
        echo "OK    $rel"
    fi
done

echo "---"
echo "Checked: $CHECKED  Errors: $ERRORS"

if [ $ERRORS -gt 0 ]; then
    echo "RESULT: $ERRORS file(s) failed XML validation."
    exit 1
else
    echo "RESULT: All files are well-formed."
    exit 0
fi
