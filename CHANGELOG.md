# Changelog

## 2.1.0 - 2026-11-17 (beta)
- Weather: pick a weather entity in the blueprint and the temperature and an icon show in the footer and beside the date on the clock screen. Switch it off with "Show weather" (in Home Assistant, or Settings > Extras on the board)
- Train details: how the station's trains have run this week ("Station: 58% on time, avg 8 min late"), from My Rail Commute
- Shorter page numbers: "1/2" instead of "Page 1 of 2", in the footer and on train details
- Train details and focus mode follow the Background setting: LED gaps on Dot matrix, no bands on Plain, and the footer band as on the list
- The "Data source" reading goes back to National Rail when demo mode is switched off (it could stay on "London TfL")
- Install updates automatically: a new switch (on by default) installs new versions on the board's update channel at about 03:00
- Setup screens show a QR code to that step of the setup guide ("Scan for help")
- Home Assistant notifications: when the board hasn't had trains for 15 minutes (e.g. an expired Darwin token), and when My Rail Commute's departed train grace period needs setting to 1 minute. The board's Status page shows a tip for the grace period too
- Docs: install My Rail Commute and London TfL from Home Assistant's Marketplace (it replaced HACS in 2026.11)
- Needs the updated blueprint (re-import it) for the weather, the station's record and the notifications

## 2.0.10 - 2026-11-17 (beta)
- Panel colour warmth keeps delays orange: at high warmth they had turned red and looked like cancellations

## 2.0.9 - 2026-11-17
- New boards start with Panel colour warmth at 18, which matches the screenshots best on the CrowPanel's screen; the slider now goes up to 25. Boards that already have a setting keep it

## 2.0.8 - 2026-11-17 (beta)
- Panel colour warmth only changes the text colours, so the dot-matrix background and row bands no longer disappear when it is turned up
- Panel colour warmth goes up to 20 (was 10), and new boards start at 10, which suits the CrowPanel's screen
- Replacement buses show "Bus" in the platform column (instead of "via Bus")
- A platform given for the first time (common at big stations shortly before departure) is no longer shown in orange as a platform change
- Panel colour warmth also warms the Tube line colours, so lines like the Bakerloo look right on the panel
- Tube boards (Calm layout): a second line too long to fit scrolls to show where the train is, instead of being cut short
- High contrast theme: delays and delay reasons in orange (they were white)
- A late train with no new time yet shows "Delayed" (it could show "On time")

## 2.0.7 - 2026-11-17 (beta)
- New "Panel colour warmth" slider (0 to 10) in Home Assistant: some panels show amber too yellow, and turning this up warms the colours back towards the intended amber. Screenshots still show the intended colours

## 2.0.6 - 2026-11-17 (beta)
- New project logo, a dot-matrix train: it drives onto the start-up screen as the title wipes in, sits above the setup messages (connecting to Wi-Fi, waiting for Home Assistant or the first train data) and in the corner of the Status page. It is drawn in the theme colour
- README and install page: the logo, and a browser tab icon

## 2.0.5 - 2026-11-17 (beta)
- Tube Focus mode: "Arriving" or where the train is now (instead of "On time"), the line and direction underneath, and the line colour bar
- Tube boards: shorter second lines ("Jubilee - N/bound - Left West Hampstead") so where the train is fits
- Train details: stop names use the full width when the stops fit in one column (no more "London Kings...")
- Focus mode: the 2nd and 3rd trains drop their "2nd" / "3rd" labels when both destinations wouldn't fit

## 2.0.4 - 2026-11-17 (beta)
- Screenshots are taken from one finished frame (they could mix frames and miss text)
- National Rail demo board has 10 trains, so it no longer shows "Last train" late in the evening

## 2.0.3 - 2026-11-16 (beta)
- Screenshots as PNG (/screenshot.png), which Home Assistant cameras and GitHub can show; the Screenshot sensor now gives the PNG address (/screenshot.bmp still works)

## 2.0.2 - 2026-11-16 (beta)
- Train details: the column headings show here too (when they are on)
- Tube train details: the countdown or "Arriving", the line colour, where the train is now, the next two trains from the same platform and the line's status ("Good service" or the delay)
- Demo mode is now a choice: Off, National Rail (a made-up York board showing every feature) or London Underground (a made-up Green Park board). Home Assistant's data waits while it is on
- Screenshots: http://<board>/screenshot.bmp gives an exact copy of the screen; the address is on the new "Screenshot" sensor
- Blueprint: a deeper Bakerloo line brown, so it stands apart from the amber text
- Footer logos (track, tunnel and custom logos) sit 3 px lower, level with the footer text

## 2.0.1 - 2026-11-16 (beta)
- New defaults for new boards (boards that already have settings keep them): Calm layout, Dot matrix background, white footer, column headings, fade cancelled trains, page animation and the logo on; pin next train and the disruption banner off; 15 s page interval; 30% night brightness
- New "Brightness" slider in Home Assistant for the daytime brightness, next to Night brightness and Idle brightness; it stays in step with the board's Settings and the Backlight light
- The "Logo image" setting is now called "National Rail board logo image" (next to "TfL board logo image"). Set your logo address again after updating, and delete the old "Logo image" entity from the board's device page
- Help page: rows for the orange arrow (update ready) and the orange i (messages and line status)
- Blueprint and README: the board takes up to 5 stations in total, including Tube stations
- TfL board logo image: a coloured logo now works (it showed blank). It is drawn in the footer colour like the National Rail logo: coloured parts solid, white parts (lettering) cut out
- Fixed: Tube stations no longer show "Last train" in the evening (TfL sends fewer trains, which looked like the end of service)
- TfL line colours: only the darkest lines are brightened, so the Bakerloo line stays brown instead of looking amber
- Update ready: an orange arrow icon in the footer instead of the small dot (next to the station message "i" when there is one). Tap it to see the new version and install it from the board

## 2.0.0 - 2026-11-16 (beta)
London Underground and DLR support: the board now works with Tube stations as well as National Rail.

- London Underground and DLR stations, from the London TfL integration: pick them in the blueprint's new "London Underground / DLR stations" box. They count down ("Due", "3 min"), show each train's line, direction and where it is now, and use a tunnel logo
- New "TfL board logo image" setting: your own logo for Tube / DLR stations
- TfL: several lines at the same station are merged into one board; "Arriving" when a train is approaching or at the platform; a bar in the line's colour on each train (new "TfL line colours" switch, also on the Style page); line status from the London Underground integration via the footer "i" (titled "Line status")
- New "Data source" diagnostic sensor (National Rail or London TfL)
- Route boards (and the "calling at" filter): the heading reads "Destination (all call at Hull)", since trains going beyond your destination are listed too
- Column heading "Expt" now reads "Expected"

## 1.20.0 - 2026-11-16 (beta)
- Press and hold a train to make it a favourite (or hold again to remove it); a short message confirms it
- "Last train" on the second line of the evening's last train
- Update ready: an orange dot by the clock, and the Status page shows the new version
- Help page: a row for press and hold
- New default logo: a simple railway track instead of the train carriage
- Second lines (operator, calling points, arrival times) slightly dimmer: 60% instead of 70% (High contrast unchanged)
- Removed the "Trains shown" setting (and its Home Assistant entity): the board always shows 5 trains a page, or 4 with large text. Compact still fits as many as it can

## 1.19.1 - 2026-11-16
- Arrival times on routes are now dimmed like the rest of the second line (dimmed orange when late)
- Fixed: at a busy station the board could say "No more trains tonight" in the daytime when every train it had just left before the next update arrived. It now says "Waiting for new train times" (and suggests a route)

## 1.19.0 - 2026-11-16 (beta)
- Station messages: an orange "i" in the footer when National Rail has a notice for your station; tap it to read the messages (Prev / Next, closes after a minute). New "Station messages" diagnostic sensor
- Routes: each train's second line starts with its arrival time at your destination ("Arrives 17:39", orange when running late)
- Help page: a row for the station message icon
- Blueprint: sends station messages (web links removed) to boards that support them

## 1.18.0 - 2026-11-16 (beta)
- Fixed: the column heading showed boxes for some letters on a route (e.g. "Destination (to Leeds only)")
- Clearer message while changing station: "Switching station or route", with "3 of 5" underneath
- Help page in settings listing the touch controls; the footer says "Tap the clock for help" until settings are first opened (which opens Help)
- Swipe left or right to change station or route; on a train's details, tap the sides (or swipe) for the previous or next train
- A tapped train's row is outlined briefly before its details open
- Settings close by themselves after a minute without a tap
- Clearer status screens: what is happening and what to do (including the board's address when Home Assistant is not connected), with moving dots while waiting

## 1.17.0 - 2026-11-16 (beta)
- Much faster drawing with the Rows and Dot matrix backgrounds: the bands and LED grid are written in bulk instead of pixel by pixel, so scrolling, page animation and taps are smoother
- Routes (e.g. Manchester Piccadilly to Leeds): the footer shows the station, the column heading says "Destination (to Leeds only)", and each train shows its real final destination; the board's Calling at filter also shows in the heading
- New "Route" diagnostic sensor
- Blueprint: pick a station or a route; the optional "Names on the board" now takes a name for each station

## 1.16.1 - 2026-11-16 (beta)
- Page animation reworked so it shows on the panel: rows appear one after another from the top, each sliding up into place
- New diagnostic sensor: Display frame time (how long a screen redraw takes)
- Column headings are white (dark on Daylight), sit higher, and no longer have a line underneath

## 1.16.0 - 2026-11-16 (beta)
- Compact layout fixed: the next train now shows at the top (it was missing and the rows below overlapped)
- Calm and Compact: only the next train scrolls (the first train on later pages no longer does)
- Second lines (operator and calling points) use a softer version of the theme colour in every layout, so the main line stands out; the High contrast theme keeps full brightness
- New Style settings page: Fade cancelled trains, Column headings and Page animation (all off by default)
- Night dimming can follow sunset and sunrise from Home Assistant (Settings > Screen > Night dimming: Off / Set times / Sunset)

## 1.15.0 - 2026-11-16 (beta)
- New Layout setting: Classic (as before, default), Calm and Compact

## 1.14.1 - 2026-11-16 (beta)
- Focus mode layout fixed: bands hug the text, lines evenly spaced, the 2nd/3rd strip no longer overlaps the footer, and a short destination leaves room for a long one

## 1.14.0 - 2026-11-16 (beta)
- Focus mode: the train is labelled 1st, with the 2nd and 3rd trains along the bottom; shows the delay reason (scrolling if long) and highlights a platform change; skips trains you can no longer catch when a walking time is set
- New Footer colour setting (Theme or White) for the logo and station name

## 1.13.1 - 2026-11-16 (beta)
- Redesigned train detail page in the board style

## 1.13.0 - 2026-11-16 (beta)
- DotGothic only; restyled settings screen with Back/Next/Close

## 1.12.1 - 2026-11-15 (beta)
- Station switching responds instantly and reliably

## 1.12.0 - 2026-11-15 (beta)
- Station switching, startup animation, calmer delay colours, shorter entity names (settings reset once)

## 1.11.0 - 2026-11-15 (beta)
- Paging through all trains, with optional pinned next train

## 1.10.0 - 2026-11-15 (beta)
- Platform number flashes when it changes; factory reset button

## 1.9.2 - 2026-11-15 (beta)
- Rows laid out from the real letter shapes; even row bands

## 1.9.1 - 2026-11-15 (beta)
- Clearer gap between departure and calling-points lines

## 1.9.0 - 2026-11-15 (beta)
- Calling-points line no longer crowds the departure line; new dot-matrix fonts: London Underground, Bitcount, Handjet

## 1.8.1 - 2026-11-15 (beta)
- Row bands line up with the text

## 1.8.0 - 2026-11-15 (beta)
- Dot-matrix style backgrounds: row bands or LED grid

## 1.7.1 - 2026-11-15 (beta)
- Settings page titles in the highlight colour

## 1.7.0 - 2026-11-15 (beta)
- Custom logo: set a PNG address in Home Assistant

## 1.6.2 - 2026-11-15 (beta)
- Redesigned train detail screen; footer and clock lined up

## 1.6.1 - 2026-11-15 (beta)
- Normal case instead of capitals across the board

## 1.6.0 - 2026-11-15 (beta)
- Six colour themes; sharper DotGothic text; scrolling line no longer cut off

## 1.5.0 - 2026-11-15 (beta)
- Safe mode, Wi-Fi setup from the install page, update channels, stale-data warnings, memory watchdog, more diagnostics

## 1.4.0 - 2026-11-15
- Home Assistant blueprint sends train data to the board - no YAML pasting.

## 1.3.0 - 2026-11-15
- One prebuilt firmware for everyone, installed from the browser, with updates through Home Assistant.

## 1.2.0 - 2026-11-14
- First public version (ESPHome package).
