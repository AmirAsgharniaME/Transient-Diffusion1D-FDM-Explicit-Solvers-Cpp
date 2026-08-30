#!/usr/bin/env bash
set -e

# Resolve script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$SCRIPT_DIR"
REPORT_DIR="$PROJECT_DIR/ReportFiles"
OUTPUT_DIR="$REPORT_DIR/ReportPDF"
IMAGE_DIR="$REPORT_DIR/images"
HASH_DIR="$PROJECT_DIR/.build_cache"

# 1. Check required directories
if [ ! -d "$REPORT_DIR" ]; then
    echo "ERROR: ReportFiles folder was not found: $REPORT_DIR"
    exit 1
fi

if [ ! -d "$IMAGE_DIR" ]; then
    echo "ERROR: Images folder was not found: $IMAGE_DIR"
    exit 1
fi

# 2. Check required dependencies
for COMMAND in pandoc pandoc-crossref xelatex md5sum; do
    if ! command -v "$COMMAND" &> /dev/null; then
        echo "ERROR: $COMMAND was not found in PATH."
        exit 1
    fi
done

# 3. Create output and cache directories
mkdir -p "$OUTPUT_DIR" || {
    echo "ERROR: ReportPDF folder could not be created: $OUTPUT_DIR"
    exit 1
}

mkdir -p "$HASH_DIR" || {
    echo "ERROR: Build cache folder could not be created: $HASH_DIR"
    exit 1
}

echo "Building individual PDF reports..."

# Enter ReportFiles so relative image paths work correctly
cd "$REPORT_DIR"

# 4. Exact list of Markdown files
FILES=(
    "Theoretical_Background.md"
    "Domain_Discretization.md"
    "Numerical_Schemes.md"
    "FTCS_Scheme.md"
    "Richardson_Scheme.md"
    "DuFortFrankel_Scheme.md"
)

# 5. Compile each Markdown document
for FILE in "${FILES[@]}"; do
    if [ ! -f "$FILE" ]; then
        echo "WARNING: Markdown file was not found, skipping: $REPORT_DIR/$FILE"
        continue
    fi

    BASENAME="${FILE%.*}"
    PDF_FILE="$OUTPUT_DIR/$BASENAME.pdf"
    HASH_FILE="$HASH_DIR/$BASENAME.md5"
    CURRENT_HASH="$(md5sum "$FILE" | cut -d' ' -f1)"

    # Skip unchanged documents only when their PDF still exists
    if [ -f "$PDF_FILE" ] && [ -f "$HASH_FILE" ] && \
       [ "$CURRENT_HASH" = "$(cat "$HASH_FILE")" ]; then
        echo "No changes detected: $FILE — skipping."
        continue
    fi

    echo "Converting: $FILE -> $BASENAME.pdf"

    if pandoc "$FILE" \
      --from=markdown+implicit_figures+tex_math_dollars+raw_tex \
      --filter=pandoc-crossref \
      --standalone \
      --pdf-engine=xelatex \
      -V geometry:"top=2.5cm,bottom=2.5cm,left=2.5cm,right=2.5cm" \
      -V fontsize=12pt \
      --resource-path="$REPORT_DIR:$IMAGE_DIR" \
      --output="$PDF_FILE"; then
        # Update the cache only after a successful build
        printf '%s\n' "$CURRENT_HASH" > "$HASH_FILE"
        echo "Created: $BASENAME.pdf"
    else
        echo "WARNING: Could not convert $FILE — skipping."
    fi
done

echo "All individual PDF reports were processed successfully."

# 6. Open the output directory when xdg-open is available
if command -v xdg-open &> /dev/null; then
    echo "Opening PDF folder..."
    xdg-open "$OUTPUT_DIR" &> /dev/null &
fi

