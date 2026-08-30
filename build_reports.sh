#!/usr/bin/env bash
set -e

# Resolve script directory (equivalent to %~dp0)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$SCRIPT_DIR"
REPORT_DIR="$PROJECT_DIR/ReportFiles"
OUTPUT_DIR="$REPORT_DIR/ReportPDF"
IMAGE_DIR="$REPORT_DIR/images"

if [ ! -d "$REPORT_DIR" ]; then
    echo ""
    echo "ERROR: ReportFiles folder was not found:"
    echo "$REPORT_DIR"
    exit 1
fi

if [ ! -d "$IMAGE_DIR" ]; then
    echo ""
    echo "ERROR: Images folder was not found:"
    echo "$IMAGE_DIR"
    exit 1
fi

if ! command -v pandoc &> /dev/null; then
    echo ""
    echo "ERROR: Pandoc was not found in PATH."
    exit 1
fi

if ! command -v pandoc-crossref &> /dev/null; then
    echo ""
    echo "ERROR: pandoc-crossref was not found in PATH."
    exit 1
fi

if [ ! -d "$OUTPUT_DIR" ]; then
    mkdir -p "$OUTPUT_DIR" || {
        echo ""
        echo "ERROR: ReportPDF folder could not be created:"
        echo "$OUTPUT_DIR"
        exit 1
    }
fi

echo ""
echo "Building individual PDF reports..."
echo ""

# Enter ReportFiles folder so relative image paths work correctly
cd "$REPORT_DIR"

FILES=(
    "Theoretical_Background.md"
    "Domain_Discretization.md"
    "Numerical_Schemes.md"
    "FTCS_Scheme.md"
    "Richardson_Scheme.md"
    "DuFortFrankel_Scheme.md"
)

for FILE in "${FILES[@]}"; do
    if [ ! -f "$FILE" ]; then
        echo ""
        echo "ERROR: Markdown file was not found:"
        echo "$REPORT_DIR/$FILE"
        exit 1
    fi

    BASENAME="${FILE%.*}"
    echo "Converting: $FILE"

    pandoc "$FILE" \
      --from=markdown+implicit_figures+tex_math_dollars+raw_tex \
      --filter=pandoc-crossref \
      --standalone \
      --pdf-engine=xelatex \
      -V geometry:"top=2.5cm,bottom=2.5cm,left=2.5cm,right=2.5cm" \
      -V fontsize=12pt \
      --resource-path="$REPORT_DIR:$IMAGE_DIR" \
      --output="$OUTPUT_DIR/$BASENAME.pdf"

    echo "Created: $BASENAME.pdf"
    echo ""
done

echo ""
echo "All individual PDF reports were created successfully."
echo "Opening PDF folder..."
xdg-open "$OUTPUT_DIR" &> /dev/null &
