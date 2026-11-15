# UK Departure Board for ESPHome

An amber dot-matrix style UK train departure board for the **Elecrow CrowPanel Basic 7.0" (ESP32-S3, 800x480, touch)**. It shows live departures from your Home Assistant, using the **My Rail Commute** integration (National Rail Darwin data). No cloud service or proxy is needed beyond that.

Features: up to 5 trains on screen, platform, delay and cancellation reasons, tap a train for a detail page (operator, countdown, calling points with times), scrolling info line, destination filter, favourite stop highlight, clock screen, focus mode (one big view of the next train), night dimming or screen-off, and an on-device settings screen.

> Status: built and tested on one CrowPanel Basic 7" running ESPHome 2026.10. This is a hobby project, not affiliated with National Rail or Elecrow.

## What you need
- Elecrow CrowPanel Basic 7.0" (the ESP32-S3 800x480 one, not other sizes)
- Home Assistant with the ESPHome Builder add-on
- [HACS](https://hacs.xyz) and the **My Rail Commute** integration, with a free Darwin token from National Rail

## Setup

### 1. Set up My Rail Commute
Install it from HACS, then add your station with the number of services set to **10** (the board shows up to 5 at once; 10 allows for filtering and cancelled trains).

### 2. Find your entity prefix
In Home Assistant go to Developer tools > States and search for `train_1`. You will see something like `sensor.departures_from_beverley_train_1`. Your **entity prefix** is everything between `sensor.` and `_train_1`, here `departures_from_beverley`. Check that `sensor.<prefix>_status` and `sensor.<prefix>_train_2` to `_10` exist too.

### 3. Add the board in ESPHome Builder
1. New device > Skip, then replace the contents with `example/departure-board.yaml` from this repo.
2. Change the three lines marked CHANGE (name, station name as shown on screen, entity prefix) and the GitHub address if you forked this repo.
3. Add your Wi-Fi and keys to ESPHome's secrets file (`wifi_ssid`, `wifi_password`, `api_key`, `ota_password`). Builder's "Secrets" button opens it. `api_key` is a base64 32-byte key; ESPHome's new-device wizard generates one.
4. Put **`departure_board.h`** in the same folder as your device file (the ESPHome config folder, usually `/config/esphome/`). Download it from this repo, don't copy and paste it.
5. Install. The first install to the board is by USB cable (Plug into this computer); later updates go over Wi-Fi.

The first compile takes a while: it downloads fonts and builds a large display config.

### 4. Optional: per-stop times
Open `ha-stops-sensors.yaml`, follow the three steps in its first lines (replace the prefix, paste into `configuration.yaml`, reload template entities). This enables the calling-point times and the favourite-stop highlight. Without it the board still works and shows a plain "Calling at" list.

## Using the board
- **Tap a train** for the detail page; tap anywhere to close it.
- **Tap the clock** (bottom right) for settings. NEXT cycles pages, CLOSE returns to the board.
- Settings pages: Display, Trains, Extras (highlight stop, disruption banner, logo, focus mode, clock screen), Screen (night dimming/screen-off, idle dimming), Status (Wi-Fi, IP, Home Assistant link, data age, uptime, versions, free memory).
- All the same switches and numbers also appear in Home Assistant under the device, so you can automate them.
- The little train icon beside the station name is off by default (Extras page).

## Updating
When this repo changes, open the device in ESPHome Builder and install again; it re-downloads the package. Pin `@main` to a release tag (for example `@v1.2.0`) if you want updates only when you choose.

## If something is wrong
- **Board says it can't reach Home Assistant:** check the device is adopted in HA and the API key matches.
- **No trains / empty rows:** the entity prefix is wrong. Re-check step 2.
- **Fonts fail to download during compile:** Builder needs internet access to Google Fonts; retry.
- **Compile errors mentioning `departure_board.h`:** the file is missing or was pasted incorrectly; download it again into the same folder as your device file.

## Credits and notes
- Train data comes from the National Rail Darwin feed via the My Rail Commute integration; check its terms for your use.
- Touch and display settings follow the CrowPanel ESPHome guidance; `departure_board.h` includes a USB-pin workaround for the touch bus, reconstructed from the ESPHome devices page. Compare against the upstream version if you see touch problems.
