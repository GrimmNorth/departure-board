# UK Departure Board

An amber dot-matrix style UK train departure board for the **Elecrow CrowPanel Basic 7.0" (ESP32-S3, 800x480, touch)**, fed by Home Assistant. Flash it from your browser, join it to your Wi-Fi, add it to Home Assistant, then pick your board and station in a ready-made automation. No ESPHome knowledge and no YAML needed.

**Install page:** https://grimmnorth.github.io/departure-board/

## For users

You need the CrowPanel above, Home Assistant 2026.11 or newer, and the **My Rail Commute** integration from the Home Assistant Marketplace (free Darwin token from National Rail). On older Home Assistant versions, install My Rail Commute through HACS instead.

1. **Flash.** Open the install page in Chrome or Edge on a computer, plug the board in by USB, click Install.
2. **Wi-Fi.** When the install finishes the page asks for your Wi-Fi details. (Fallback: join the board's own Wi-Fi, `Departure-Board`, from a phone and pick your home network.)
3. **Home Assistant.** Settings > Devices & services: add the discovered ESPHome device. No key needed. If it isn't discovered, use Add integration > ESPHome and enter the board's IP address (see your router).
4. **My Rail Commute.** Install it from **Settings > Marketplace** ([open it in your Home Assistant](https://my.home-assistant.io/redirect/hacs_repository/?owner=adamf83&repository=my-rail-commute&category=integration)), then add your station with **10 services**.
5. **Connect them.** Use the *Import blueprint* button on the install page, then Settings > Automations & scenes > Blueprints > UK Departure Board > Create automation. Pick your board, pick your station, type the station name to show, Save.

Updates appear in Home Assistant as an Update button on the board's device page.

### Built-in safety nets
- **Safe mode:** if an update ever stops the board starting, after 5 failed starts it boots a minimal mode that can still take a fixed update. No USB cable needed. There is also a "restart in safe mode" button.
- **Stale data warning:** the footer turns red ("Data 7 min old") if Home Assistant stops sending trains, and the board says so plainly if no data has arrived at all, instead of showing old times as live.
- **Memory watchdog:** if memory runs critically low the board restarts cleanly; if it is slowly running down it restarts quietly at 03:30.
- **Diagnostics** in Home Assistant under the device: uptime, restart reason, data age, free memory, Wi-Fi signal.
- **Update channel:** leave on *Stable*. Set it to *Beta* (under the device's configuration) to get test versions first.

### Using the board
- Tap a train for its detail page (operator, countdown, calling points with times); tap anywhere to close.
- Six colour themes: Classic amber, White LED, Modern LCD, Retro green, High contrast and Daylight (which switches to Classic amber during night hours). Change it under Settings > Display > Theme on the board, or the board's theme setting in Home Assistant.
- Tap the clock (bottom right) for settings: display, trains, extras (highlight stop, disruption banner, logo, focus mode, clock screen), screen (night dimming, screen off), status.
- All the same switches and numbers appear in Home Assistant under the device.

### Custom logo
The board shows a small train icon at the bottom left (switch it off with *Show logo*). To use your own logo instead:
1. Make a PNG of your logo: **white (or light) on a transparent background**, ideally about 56 x 35 pixels (larger images are shrunk to fit). It is drawn in the theme colour.
2. Put it where the board can download it, for example in Home Assistant's `www` folder (`/config/www/logo.png` is served as `http://homeassistant.local:8123/local/logo.png`; use your Home Assistant's IP address if `homeassistant.local` doesn't work).
3. On the board's device page in Home Assistant, set **Logo image** to that address. The logo appears within a minute. Clear the setting to go back to the train icon.

### Troubleshooting
- **Board shows no trains or says it is waiting:** the automation from step 5 sends the data once a minute. Check it exists and is switched on (Settings > Automations), that you picked the right board and station, and that My Rail Commute has trains. Run the automation by hand with the three-dots menu > Run actions.
- **Changing station:** edit the board's automation and pick a different station; the board switches within a minute. Keep one automation per board. Two automations sending to the same board make it flick between stations.
- **Board says "No trains calling at ...":** a destination filter is set (common if the board was flashed over an older build). Clear it in Home Assistant under the board's "destination filter" text entity.
- **No update appears:** the board checks for updates when it starts and then every 6 hours. Press the board's *restart* button on its device page to make it check straight away.

## For the maintainer

The firmware source is `firmware/departure-board.yaml` with `firmware/departure_board.h` beside it. It contains no secrets. Every push that changes `firmware/` is compiled by the **Build check** workflow, so a broken build shows up as a red cross on GitHub before it can be released.

To publish a new version (no downloads, no scripts on your computer):
1. On GitHub open **Actions > Release > Run workflow**.
2. Choose **beta**, type the new version number (e.g. `1.5.1`) and a one-line summary, and run it. It compiles the firmware, publishes it to boards on the Beta channel, adds a GitHub Release and updates `CHANGELOG.md`.
3. Try it on your own board (set to Beta) for a day or so.
4. Run the workflow again with **promote** to give that version to everyone and the install page.

Choosing **stable** in step 2 skips the beta stage. `release.sh` does the same publishing by hand if you ever build locally. To move to a newer ESPHome, change `ESPHOME_VERSION` in both workflow files.

## Notes
- Licensed under the MIT licence (see `LICENSE`).
- Built and tested on one CrowPanel Basic 7" with ESPHome 2026.10. Hobby project, not affiliated with National Rail or Elecrow.
- The board's API is unencrypted so setup stays simple; keep it on your home network.
- Train data comes from the National Rail Darwin feed via My Rail Commute; check its terms for your use.
- `departure_board.h` includes a USB-pin workaround for the CrowPanel touch bus, based on the community notes on the ESPHome devices page.
