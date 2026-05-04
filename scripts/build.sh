#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${ROOT_DIR}/build"

mkdir -p "${ROOT_DIR}/data/output"

cmake -S "${ROOT_DIR}" -B "${BUILD_DIR}" -DCMAKE_BUILD_TYPE=Debug
cmake --build "${BUILD_DIR}" -j$(nproc)

echo
echo "Build finished."
echo "Executables:"
echo "  ${BUILD_DIR}/addressbook_write"
echo "  ${BUILD_DIR}/addressbook_read"