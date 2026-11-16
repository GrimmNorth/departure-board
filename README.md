# UK Departure Board

An amber dot-matrix style UK train departure board for the **Elecrow CrowPanel Basic 7.0" (ESP32-S3, 800x480, touch)**, fed by Home Assistant. Flash it from your browser, join it to your Wi-Fi, add it to Home Assistant, then pick your board and station in a ready-made automation. No ESPHome knowledge and no YAML needed.

**Install page:** https://grimmnorth.github.io/departure-board/

## For users

You need the CrowPanel above, Home Assistant 2026.11 or newer, and the **My Rail Commute** integration from the Home Assistant Marketplace (free Darwin token from National Rail). On older Home Assistant versions, install My Rail Commute through HACS instead.

1. **Flash.** Open the install page in Chrome or Edge on a computer, plug the board in by USB, click Install.
2. **Wi-Fi.** When the install finishes the page asks for your Wi-Fi details. (Fallback: join the board's own Wi-Fi, `Departure-Board`, from a phone and pick your home network.)
3. **Home Assistant.** Settings > Devices & services: add the discovered ESPHome device. No key needed. If it isn't discovered, use Add integration > ESPHome and enter the board's IP address (see your router).
4. **My Rail Commute.** Install it from **Settings > Marketplace** ([open it in your Home Assistant](https://my.home-assistant.io/redirect/hacs_repository/?owner=adamf83&repository=my-rail-commute&category=integration)), then add your station with **10 services**. Afterwards open the station's **Configure > Disruption** settings and set **Departed train grace period** to **1 minute** (the default is 5). My Rail Commute keeps departed trains in its list for that long, and they use up places that would otherwise show upcoming trains, so with 5 minutes the board often shows only 8.
5. **Connect them.** Use the *Import blueprint* button on the install page, then Settings > Automations & scenes > Blueprints > UK Departure Board > Create automation. Pick your board and your station (or a route, see *Busy stations* below), then Save. Add *More stations or routes* if you want to switch between several. The footer shows each station's name (the optional *Names on the board* setting changes the wording if you want to).

Updates appear in Home Assistant as an Update button on the board's device page.

### Busy stations
My Rail Commute sends at most 10 trains. At a big station like Manchester Piccadilly or Clapham Junction that is only the next 10 to 15 minutes, across every platform and destination, and the board's *Calling at* filter can only pick from those same 10.

The fix is a **route**: in My Rail Commute, add your station **with a destination** (for example Manchester Piccadilly to Leeds, 10 services). You then get the next 10 trains that go there, which can cover a couple of hours. Pick the route in the blueprint just like a station. You can add several routes as extra stations (say Manchester Piccadilly to Leeds and Manchester Piccadilly to London) and tap the station name on the board to switch, and keep "Departures from" as one of them for the full picture. On a route the footer still shows your station, the *Destination* column heading says, for example, *Destination (to Leeds only)* (with Column headings on; otherwise the footer shows *Manchester Piccadilly > Leeds*), and each train shows its real final destination. The calling points listed stop at the route's end, because that is what My Rail Commute provides for routes. My Rail Commute's *operator filter* (Configure > Trains) can also narrow a busy station to, say, one train company.

### Built-in safety nets
- **Safe mode:** if an update ever stops the board starting, after 5 failed starts it boots a minimal mode that can still take a fixed update. No USB cable needed. There is also a "restart in safe mode" button.
- **Stale data warning:** the footer turns red ("Data 7 min old") if Home Assistant stops sending trains, and the board says so plainly if no data has arrived at all, instead of showing old times as live.
- **Memory watchdog:** if memory runs critically low the board restarts cleanly; if it is slowly running down it restarts quietly at 03:30.
- **Diagnostics** in Home Assistant under the device: uptime, restart reason, data age, free memory, Wi-Fi signal.
- **Update channel:** leave on *Stable*. Set it to *Beta* (under the device's configuration) to get test versions first.
- **Factory reset:** a button on the device page clears Wi-Fi and all settings, for passing a board on. The board then starts its `Departure-Board` setup hotspot again.

### Using the board
- **Help:** Settings > Help (the last settings page) lists all the touch controls. Until you first open settings, the footer says "Tap the clock for help". Settings close by themselves after a minute.
- Each train shows its time, destination, platform and status, with the calling points (and any delay reason) scrolling underneath. A platform number flashes for a minute when it changes.
- **Switching station:** add extra stations under *More stations* in the board's automation. Then swipe left or right across the board, or tap the station name at the bottom, to move between them, or set the board's *Station number* in Home Assistant (handy in your own automations, e.g. your work station in the evening). The board shows "Switching station or route" (with, say, "3 of 5") for a moment while the new trains arrive.
- **Paging:** when there are more trains than rows, the board flicks between pages ("Page 1 of 2" in the footer), every 10 seconds by default. *Pin next train* keeps the next departure on every page. Switch either off under Settings > Trains, and change the interval with *page interval* in Home Assistant.
- Tap a train for its detail page: status and expected time, platform and operator, countdown, delay reason, arrival time, and the calling points as a route line with times. Tap the left or right side (or swipe) for the previous or next train; tap the middle to close.
- **Themes:** Classic amber, White LED, Modern LCD, Retro green, High contrast and Daylight (which switches to Classic amber during night hours). Settings > Display > Theme on the board, or the theme setting in Home Assistant.
- **Background:** *Rows* (default) puts each line on a faint unlit band like a real LED board; *Dot matrix* adds the grid of unlit dots; *Plain* turns it off. Set it in Home Assistant.
- **Style** (Settings > Style): *Fade cancelled* dims a cancelled train so the running ones stand out; *Column headings* adds a small Time / Destination / Plat / Expt line (handy without a case); *Page animation* slides each row in when the page changes.
- **Night dimming** can use set times or follow sunset and sunrise (from Home Assistant's `sun.sun`).
- **Layout** (Settings > Display): *Classic* (every train on two lines, all scrolling), *Calm* (only the first train scrolls; later trains show the operator, or the delay reason in orange) or *Compact* (the next train on two lines, the rest on one line each with a reason line under any late or cancelled train, so 7 or 8 trains fit).
- Tap the clock (bottom right) for settings: display, trains, extras (highlight stop, disruption banner, logo, focus mode, clock screen, footer colour), screen (night dimming, screen off), status.
- **Focus mode** (Settings > Extras) shows just the next train with a big countdown, labelled 1st, with its delay reason and any platform change, and the 2nd and 3rd trains along the bottom. If you set a walking time, it skips trains you can no longer catch.
- All the same switches and numbers appear in Home Assistant under the device.

### Custom logo
The board shows a small train icon at the bottom left (switch it off with *Show logo*). To use your own logo instead:
1. Make a PNG of your logo: **white (or light) on a transparent background**, ideally about 56 x 35 pixels (larger images are shrunk to fit). It is drawn in the theme colour, or in white if you set *Footer colour* to White.
2. Put it where the board can download it, for example in Home Assistant's `www` folder (`/config/www/logo.png` is served as `http://homeassistant.local:8123/local/logo.png`; use your Home Assistant's IP address if `homeassistant.local` doesn't work).
3. On the board's device page in Home Assistant, set **Logo image** to that address. The logo appears within a minute. Clear the setting to go back to the train icon.

### Troubleshooting
- **Board shows no trains or says it is waiting:** the automation from step 5 sends the data once a minute. Check it exists and is switched on (Settings > Automations), that you picked the right board and station, and that My Rail Commute has trains. Run the automation by hand with the three-dots menu > Run actions.
- **Fewer than 10 trains:** set My Rail Commute's *Departed train grace period* to 1 minute (station > Configure > Disruption), as in step 4. Quiet stations can also run out of trains inside the 2-hour window My Rail Commute looks ahead, which is its maximum.
- **One automation per board:** two automations sending to the same board make it flick between stations. Add extra stations to the one automation instead.
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
- Text uses the DotGothic16 font (SIL Open Font License), downloaded from Google Fonts at build time.
- `departure_board.h` includes a USB-pin workaround for the CrowPanel touch bus, based on the community notes on the ESPHome devices page.
