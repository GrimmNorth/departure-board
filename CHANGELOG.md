# Changelog

## Unreleased
- Fixed: the column heading showed boxes for some letters on a route (e.g. "Destination (to Leeds only)")

## 1.17.0 - 2026-11-16 (beta)
- Faster drawing with Rows and Dot matrix; routes show the destination in the heading and real train destinations

## 1.17.0 - 2026-11-16 (beta)
- Much faster drawing with the Rows and Dot matrix backgrounds: the bands and LED grid are written in bulk instead of pixel by pixel, so scrolling, page animation and taps are smoother
- Routes (e.g. Manchester Piccadilly to Leeds): the footer shows the station, the column heading says "Destination (to Leeds only)", and each train shows its real final destination; the board's Calling at filter also shows in the heading
- New "Route" diagnostic sensor
- Blueprint: pick a station or a route; the optional "Names on the board" now takes a name for each station

## 1.16.1 - 2026-11-16 (beta)
- Page animation now visible; white column headings; display frame time sensor

## 1.16.1 - 2026-11-16 (beta)
- Page animation reworked so it shows on the panel: rows appear one after another from the top, each sliding up into place
- New diagnostic sensor: Display frame time (how long a screen redraw takes)
- Column headings are white (dark on Daylight), sit higher, and no longer have a line underneath

## 1.16.0 - 2026-11-16 (beta)
- Compact layout fixed; softer second lines; new Style page (fade cancelled, column headings, page animation); night dimming can follow the sun

## 1.16.0 - 2026-11-16 (beta)
- Compact layout fixed: the next train now shows at the top (it was missing and the rows below overlapped)
- Calm and Compact: only the next train scrolls (the first train on later pages no longer does)
- Second lines (operator and calling points) use a softer version of the theme colour in every layout, so the main line stands out; the High contrast theme keeps full brightness
- New Style settings page: Fade cancelled trains, Column headings and Page animation (all off by default)
- Night dimming can follow sunset and sunrise from Home Assistant (Settings > Screen > Night dimming: Off / Set times / Sunset)

## 1.15.0 - 2026-11-16 (beta)
- New Layout setting: Classic, Calm and Compact

## 1.15.0 - 2026-11-16 (beta)
- New Layout setting: Classic (as before, default), Calm and Compact

## 1.14.1 - 2026-11-16 (beta)
- Focus mode layout fixed: no overlapping lines, tidier spacing

## 1.14.1 - 2026-11-16 (beta)
- Focus mode layout fixed: bands hug the text, lines evenly spaced, the 2nd/3rd strip no longer overlaps the footer, and a short destination leaves room for a long one

## 1.14.0 - 2026-11-16 (beta)
- Focus mode shows 1st, 2nd and 3rd trains, delay reasons and platform changes; new footer colour setting

## 1.14.0 - 2026-11-16 (beta)
- Focus mode: the train is labelled 1st, with the 2nd and 3rd trains along the bottom; shows the delay reason (scrolling if long) and highlights a platform change; skips trains you can no longer catch when a walking time is set
- New Footer colour setting (Theme or White) for the logo and station name

## 1.13.1 - 2026-11-16 (stable)
Everything since 1.5.0, now on the stable channel:
- Six colour themes, and dot-matrix style row bands (Rows / Dot matrix / Plain)
- Paging through all trains, with an optional pinned next train
- Switch between several stations: tap the station name, or set Station number in Home Assistant
- Custom logo from a PNG address
- Redesigned train detail page and settings screens
- Startup animation; calmer delay colours; normal case instead of capitals
- Platform number flashes when it changes; factory reset button
- DotGothic text drawn crisply, with layout measured from the letters
- Shorter entity names in Home Assistant (settings return to defaults once on this update)

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
