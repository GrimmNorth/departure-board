# UK Departure Board

An amber dot-matrix style UK train departure board for the **Elecrow CrowPanel Basic 7.0" (ESP32-S3, 800x480, touch)**, fed by Home Assistant. Flash it from your browser, join it to your Wi-Fi, add it to Home Assistant, then pick your board and station in a ready-made automation. No ESPHome knowledge and no YAML needed.

**Install page:** https://grimmnorth.github.io/departure-board/

## For users

You need the CrowPanel above, Home Assistant, [HACS](https://hacs.xyz), and the **My Rail Commute** integration (free Darwin token from National Rail).

1. **Flash.** Open the install page in Chrome or Edge on a computer, plug the board in by USB, click Install.
2. **Wi-Fi.** Join the board's own Wi-Fi (`Departure-Board`) from a phone and pick your home network.
3. **Home Assistant.** Settings > Devices & services: add the discovered ESPHome device. No key needed. If it isn't discovered, use Add integration > ESPHome and enter the board's IP address (see your router).
4. **My Rail Commute.** Add your station with **10 services**.
5. **Connect them.** Use the *Import blueprint* button on the install page, then Settings > Automations & scenes > Blueprints > UK Departure Board > Create automation. Pick your board, pick your station, type the station name to show, Save.

Updates appear in Home Assistant as an Update button on the board's device page.

### Using the board
- Tap a train for its detail page (operator, countdown, calling points with times); tap anywhere to close.
- Tap the clock (bottom right) for settings: display, trains, extras (highlight stop, disruption banner, logo, focus mode, clock screen), screen (night dimming, screen off), status.
- All the same switches and numbers appear in Home Assistant under the device.

### Troubleshooting
- **Board shows no trains or says it is waiting:** the automation from step 5 sends the data once a minute. Check it exists and is switched on (Settings > Automations), that you picked the right board and station, and that My Rail Commute has trains. Run the automation by hand with the three-dots menu > Run actions.
- **Board says "No trains calling at ...":** a destination filter is set (common if the board was flashed over an older build). Clear it in Home Assistant under the board's "destination filter" text entity.
- **No update appears:** the board checks for updates when it starts and then every 6 hours. Press the board's *restart* button on its device page to make it check straight away.

## For the maintainer

The firmware source is `firmware/departure-board.yaml` with `firmware/departure_board.h` beside it (compile in ESPHome Builder; it contains no secrets).

To publish a new version:
1. Build in ESPHome Builder and download both the **factory** and **OTA** files.
2. `./release.sh 1.4.1 "What changed" factory.bin ota.bin`
3. `git add -A && git commit -m "Release 1.4.1" && git push`

GitHub Pages serves `manifest.json` and `releases/`. Boards compare the manifest version to their own and offer the update.

## Notes
- Licensed under the MIT licence (see `LICENSE`).
- Built and tested on one CrowPanel Basic 7" with ESPHome 2026.10. Hobby project, not affiliated with National Rail or Elecrow.
- The board's API is unencrypted so setup stays simple; keep it on your home network.
- Train data comes from the National Rail Darwin feed via My Rail Commute; check its terms for your use.
- `departure_board.h` includes a USB-pin workaround for the CrowPanel touch bus, based on the community notes on the ESPHome devices page.
