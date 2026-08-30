#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$SCRIPT_DIR"
REPORT_DIR="${PROJECT_DIR}/ReportFiles"
OUTPUT_DIR="${REPORT_DIR}/ReportPDF"
IMAGE_DIR="${REPORT_DIR}/images"
OUTPUT_FILE="${OUTPUT_DIR}/TransientDiffusion1D_FDM_Solver_Cpp.pdf"

if [ ! -d "${REPORT_DIR}" ]; then
    echo
    echo "ERROR: ReportFiles folder was not found:"
    echo "${REPORT_DIR}"
    exit 1
fi

if [ ! -d "${IMAGE_DIR}" ]; then
    echo
    echo "ERROR: Images folder was not found:"
    echo "${IMAGE_DIR}"
    exit 1
fi

if ! command -v pandoc &> /dev/null; then
    echo
    echo "ERROR: Pandoc was not found in PATH."
    exit 1
fi

if ! command -v pandoc-crossref &> /dev/null; then
    echo
    echo "ERROR: pandoc-crossref was not found in PATH."
    exit 1
fi

if [ ! -d "${OUTPUT_DIR}" ]; then
    mkdir -p "${OUTPUT_DIR}"
    if [ $? -ne 0 ]; then
        echo
        echo "ERROR: ReportPDF folder could not be created:"
        echo "${OUTPUT_DIR}"
        exit 1
    fi
fi

MARKDOWN_FILES=(
    "Theoretical_Background.md"
    "Domain_Discretization.md"
    "Numerical_Schemes.md"
    "FTCS_Scheme.md"
    "Richardson_Scheme.md"
    "DuFortFrankel_Scheme.md"
)

for file in "${MARKDOWN_FILES[@]}"; do
    if [ ! -f "${REPORT_DIR}/${file}" ]; then
        echo
        echo "ERROR: Markdown file was not found:"
        echo "${REPORT_DIR}/${file}"
        exit 1
    fi
done

echo
echo "Building the complete PDF report..."
echo

# Run Pandoc from ReportFiles so relative image paths work correctly.
pushd "${REPORT_DIR}" > /dev/null

if ! pandoc \
  "Theoretical_Background.md" \
  "Domain_Discretization.md" \
  "Numerical_Schemes.md" \
  "FTCS_Scheme.md" \
  "Richardson_Scheme.md" \
  "DuFortFrankel_Scheme.md" \
  --from=markdown+implicit_figures+tex_math_dollars+raw_tex \
  --filter=pandoc-crossref \
  --standalone \
  --pdf-engine=xelatex \
  -V geometry:"top=2.5cm,bottom=2.5cm,left=2.5cm,right=2.5cm" \
  -V fontsize=12pt \
  --resource-path="${REPORT_DIR}:${IMAGE_DIR}" \
  --output="${OUTPUT_FILE}"; then
    echo
    echo "ERROR: Complete PDF build failed."
    popd > /dev/null
    exit 1
fi

popd > /dev/null

echo
echo "Complete PDF report created successfully:"
echo "${OUTPUT_FILE}"
echo

if command -v xdg-open &> /dev/null; then
    echo "Opening PDF folder..."
    xdg-open "${OUTPUT_DIR}" &> /dev/null &
fi
