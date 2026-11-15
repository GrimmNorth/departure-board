#!/bin/sh
# Publish a new firmware version.
# Usage: ./release.sh 1.3.1 "What changed" departure-board.factory.bin departure-board.ota.bin
# Run inside your clone of the repo, then: git add -A && git commit -m "Release 1.3.1" && git push
set -e
VER="$1"; SUMMARY="$2"; FACTORY="$3"; OTA="$4"
[ -n "$VER" ] && [ -f "$FACTORY" ] && [ -f "$OTA" ] || { echo "usage: $0 version \"summary\" factory.bin ota.bin"; exit 1; }
mkdir -p releases
cp "$FACTORY" "releases/departure-board-$VER.factory.bin"
cp "$OTA" "releases/departure-board-$VER.ota.bin"
MD5=$(md5sum "releases/departure-board-$VER.ota.bin" | cut -d' ' -f1)
sed -e "s|@@VERSION@@|$VER|g" -e "s|@@MD5@@|$MD5|" -e "s|@@SUMMARY@@|$SUMMARY|" manifest.template.json > manifest.json
echo "Wrote manifest.json for $VER (md5 $MD5)."
