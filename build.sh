#!/usr/bin/env bash
set -e
echo "Creating ./bin directory..."
mkdir -p ./bin

make

echo "Running RecompModTool..."
./RecompModTool ./mod.toml ./bin

echo "Zipping output file into ./bin..."
zip -j ./bin/tag_anywhere_sparkles.zip ./bin/tag_anywhere_sparkles.nrm

echo "Complete"