#!/bin/sh
# Create/update the local Python venv used for esptool (PEP 668 safe).
set -e
cd "$(dirname "$0")/.."
python3 -m venv .venv-esptool
.venv-esptool/bin/pip install --upgrade pip
if [ -f requirements-esptool.txt ]; then
  .venv-esptool/bin/pip install -r requirements-esptool.txt
else
  .venv-esptool/bin/pip install esptool
fi
echo "OK: use .venv-esptool/bin/esptool (or: source .venv-esptool/bin/activate)"
.venv-esptool/bin/esptool version
