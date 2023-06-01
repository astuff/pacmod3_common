#!/bin/bash
set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
OUTPUT_DIR="$SCRIPT_DIR/src/autogen"
DBC_VERSION="$1"
CODER_DBC_PATH="$2"

main()
{
  DBC_MAJOR_VERSION="${DBC_VERSION%%.*}"
  DRIVER_NAME="pacmod$DBC_MAJOR_VERSION"

  TEMP_DIR="$(mktemp -d)"

  cd "$TEMP_DIR"
  mkdir -p output

  get_dbc

  echo "Auto-generating code for version $DBC_VERSION of the PacMod DBC."
  echo "Generated code will use the name $DRIVER_NAME"
  echo ""

  "$CODER_DBC_PATH" -dbc "$TEMP_DIR/pacmod_dbc/as_pacmod.dbc" -out "$TEMP_DIR/output" -drvname "$DRIVER_NAME" -rw

  cp "$TEMP_DIR/output/lib/$DRIVER_NAME.c" "$OUTPUT_DIR/"
  cp "$TEMP_DIR/output/lib/$DRIVER_NAME.h" "$OUTPUT_DIR/"
  cp "$TEMP_DIR/output/conf/$DRIVER_NAME-config.h" "$OUTPUT_DIR/"
  if ! [ -e "$OUTPUT_DIR/dbccodeconf.h" ]; then
    cp "$TEMP_DIR/output/conf/dbccodeconf.h" "$OUTPUT_DIR/"
    sed -i "/\/\/ typedef double sigfloat_t;/c\typedef double sigfloat_t;" "$OUTPUT_DIR/dbccodeconf.h"
    echo "" >> "$OUTPUT_DIR/dbccodeconf.h"
    echo "typedef int64_t bitext_t;" >> "$OUTPUT_DIR/dbccodeconf.h"
    echo "typedef uint64_t ubitext_t;" >> "$OUTPUT_DIR/dbccodeconf.h"
  fi

  # Enable USE_SIGFLOAT
  sed -i "/#define PACMOD${DBC_MAJOR_VERSION}_USE_SIGFLOAT/c\#define PACMOD${DBC_MAJOR_VERSION}_USE_SIGFLOAT" "$OUTPUT_DIR/$DRIVER_NAME-config.h"

  # Pull out all CAN IDS:
  grep -h "_CANID" "$OUTPUT_DIR/$DRIVER_NAME.h" > "$OUTPUT_DIR/dbc$DBC_MAJOR_VERSION.canids"

  echo ""
  echo "Done"
}

get_dbc()
{
  git clone https://github.com/astuff/pacmod_dbc.git
  cd pacmod_dbc
  git checkout "$DBC_VERSION"
}

main
