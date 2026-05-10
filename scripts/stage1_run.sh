#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${ROOT_DIR}/build"
OUTPUT_FILE="${ROOT_DIR}/data/output/addressbook.bin"

echo "[stage1] build project"
"${ROOT_DIR}/scripts/build.sh"

echo
echo "[stage1] write protobuf binary"
"${BUILD_DIR}/addressbook_write" "${OUTPUT_FILE}"

echo
echo "[stage1] read protobuf binary"
"${BUILD_DIR}/addressbook_read" "${OUTPUT_FILE}"

echo
echo "[stage1] generated files to inspect:"
echo "  ${BUILD_DIR}/generated/tutorial/addressbook.pb.h"
echo "  ${BUILD_DIR}/generated/tutorial/addressbook.pb.cc"

echo
echo "[stage1] suggested grep commands:"
echo "  grep -n \"class Person\" ${BUILD_DIR}/generated/tutorial/addressbook.pb.h"
echo "  grep -n \"set_name\" ${BUILD_DIR}/generated/tutorial/addressbook.pb.h"
echo "  grep -n \"add_people\" ${BUILD_DIR}/generated/tutorial/addressbook.pb.h"