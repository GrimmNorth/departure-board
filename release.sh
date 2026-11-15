#!/bin/sh
# Publish a new firmware version (normally run for you by the GitHub "Release" workflow).
# Usage: ./release.sh 1.5.1 "What changed" factory.bin ota.bin [stable|beta]
#   beta   updates manifest-beta.json only (boards set to the Beta update channel)
#   stable updates manifest.json and manifest-beta.json (everyone, and the install page)
set -e
VER="$1"; SUMMARY="$2"; FACTORY="$3"; OTA="$4"; CHANNEL="${5:-stable}"
[ -n "$VER" ] && [ -f "$FACTORY" ] && [ -f "$OTA" ] || { echo "usage: $0 version \"summary\" factory.bin ota.bin [stable|beta]"; exit 1; }
case "$CHANNEL" in stable|beta) ;; *) echo "channel must be stable or beta"; exit 1;; esac
mkdir -p releases
cp "$FACTORY" "releases/departure-board-$VER.factory.bin"
cp "$OTA" "releases/departure-board-$VER.ota.bin"
MD5=$(md5sum "releases/departure-board-$VER.ota.bin" | cut -d' ' -f1)
VER="$VER" MD5="$MD5" SUMMARY="$SUMMARY" python3 - <<'PYEOF'
import json, os
t = open("manifest.template.json").read()
t = t.replace("@@VERSION@@", os.environ["VER"]).replace("@@MD5@@", os.environ["MD5"])
t = t.replace('"@@SUMMARY@@"', json.dumps(os.environ["SUMMARY"]))
json.loads(t)  # fail loudly if the result is not valid JSON
open("manifest-beta.json", "w").write(t)
PYEOF
[ "$CHANNEL" = "stable" ] && cp manifest-beta.json manifest.json
echo "Wrote manifest for $VER to $CHANNEL (md5 $MD5)."
