# Changelog

## Unreleased
- Blueprint: a train shown as just "Delayed" (no new time yet) no longer sets off the "change one My Rail Commute setting" notification, and is still announced when it becomes delayed. Both treated it as having left at its booked time. Re-import the blueprint

## 2.3.3 - 2026-11-19 (beta)
- Announcements: no gap between the chime and the voice. The speech is now requested as the chime starts, and the board plays the voice over the end of the chime (fading the chime down), like a real station, instead of waiting for it or cutting it off. Needs this firmware and the new blueprint; older boards keep a short wait so the chime isn't cut off
- Announcements: a train that's already left is no longer announced when the data catches up late (e.g. an on-time train that suddenly shows as expected two minutes ago). The delay or cancellation reason now has its space after the sentence before it, in announcements and favourite alerts. Re-import the blueprint
- Announcements: no more odd pauses in the middle of names ("Manchester ... Airport") with Google's voice, which reads at most 100 characters at a time. Sentences now have commas in natural places, like a real station announcer

## 2.3.2 - 2026-11-19 (beta)
- Announcements: a train that becomes 5 or more minutes late, or is cancelled, while it's on the board is announced straight away ("We are sorry to announce that the 17:42 ... is delayed, and is now expected at 17:50"), instead of waiting for its usual slot. Works with *All trains*, *Delays only* and *Favourites only*. Re-import the blueprint
- Examples in the docs and code use York and Leeds

## 2.3.1 - 2026-11-19 (beta)
- README and install page: shorter and simpler, with a fresh screenshot instead of the animation
- Screen: if the picture slips and jitters at the left edge after a sound, the board now puts it back in step as soon as the sound ends. The screen is also fed slightly slower (14 MHz instead of 15), which leaves more room for sound and the picture at the same time
- Sound: the board, README, dashboard and automation now say announcements can play on a speaker plugged into the board or on one you already have in Home Assistant (e.g. a Google Nest Mini)
- Blueprint: the *Names on the board* option is gone; each station shows its own name
- Announcements: pick the voice from a list (Google Translate British, five Piper voices, four Home Assistant Cloud voices) instead of typing a service and voice name. Announcements now use a British voice: before, Google used its American one. Re-import the blueprint

## 2.3.0 - 2026-11-19 (beta)
- Faster and smaller: the board's drawing code was rewritten so the ten train rows share one piece of code instead of ten copies, and trains are read in place instead of being copied four times a second. The firmware is about 95 KB smaller (from 79% to 74% of the space an update can use), leaving room for future features
- With the new blueprint, all ten trains arrive in one message each minute, so the board never shows a mix of new and old trains while they come in. Older blueprints still work
- The chime is stored compressed
- Blueprint: looks up the board's settings once per run instead of a dozen times. Re-import it to get this and the one-message update

## 2.2.3 - 2026-11-19 (beta)
- Sound: *Sounds* now turns the whole sound feature on or off (off to start with, for boards without a speaker): while it's off nothing is announced, no speaker icon shows and the other Sound settings are greyed out. A new *Mute* setting silences the speaker for now; only then does the grey crossed speaker show in the footer. Your board starts with Sounds off after this update: turn it on under Settings > Sound
- Sound is marked experimental: in the README, on the board's settings page (*Sound (experimental)*) and in the automation's announcement section. It's new and only tested on one board and speaker

## 2.2.2 - 2026-11-19 (beta)
- Blueprint (already out, fixed on 19 Nov): the 2.2.1 blueprint stopped sending trains to the board; re-import it if your board shows no trains. *Favourites only* announcements now switch on too
- Announcements: a delayed train with a new time is announced again a few minutes before its new time ("The next train to depart from platform 1 will be the delayed 10:37 Northern service to Leeds, now expected at 11:25"), as well as the apology at its booked time. Before, a late train was never announced near when it actually left. Re-import the blueprint
- Screen: no more doubled or ghosted text while things move (scrolling lines, page changes, the departure slide). The board copied each new frame to the screen while the screen was mid-refresh, so for a moment part showed the old frame and part the new one. It now waits for the screen to finish a refresh first

## 2.2.1 - 2026-11-19 (beta)
- Announcement settings are now on the board (Settings > Sound) and its device page: *Announcements* (Off, All trains, Delays only, or Favourites only: just your favourite trains, whether on time, late or cancelled), *Announce before*, *Chime first* and *Quiet at night* (follows the board's night times). Only the voice and extra speakers stay in the automation, under **Announcement voice and speakers**. Re-import the blueprint, then turn Announcements on from the board
- Sound settings say they need a speaker plugged into the board
- Announcements follow the station or route the board is showing, not just the first one (Tube and DLR stations stay quiet). Re-import the blueprint
- The delay or cancellation reason on the scrolling line under the first train is orange (red when cancelled), like the rows below it. Before, only "Delayed 5 min" was orange and the reason was in the normal colour

## 2.2.0 - 2026-11-19 (beta)
- Sound: optional station-style announcements from the blueprint (new **Announcements** section, off by default). A few minutes before each train from your first station or route: "The next train to depart from platform 1 will be..." or "We are sorry to announce..." for delays and cancellations. Choose which trains, how long before, the voice and speakers, a chime first, and quiet hours. Re-import the blueprint to get it
- Sound: a new **Sound** page in the board's settings (Sounds on/off, volume, test chime), and *Sounds* and *Test sound* in Home Assistant
- Sound: a speaker icon in the footer, only while the board is speaking (amber; tap to stop) or when sound is off (grey with a cross; tap to turn it back on)
- Sound: the board's own chime, played before announcements and by *Test sound*
- Speaker starts at full volume (turn it down with the Speaker volume in Home Assistant)

## 2.1.5 - 2026-11-19 (beta)
- Speaker: the picture no longer jumps when a sound starts (the board downloaded the whole sound in one burst into a large buffer; it now uses a small one and plays uncompressed audio). Gentler volume scale, louder by default
- Screen: fixes the brief flicker where part of the picture doubled or jumped down a few lines for a moment (seen on the column headings). The screen could miss a refresh while the board saved settings; the board now runs from its larger memory so the screen keeps going, snaps straight back if it ever slips, and saves settings less often
- Speaker: no more hum after a restart. The amplifier hummed until the first sound played, so the board now plays a moment of silence as it starts

## 2.1.4 - 2026-11-19 (beta)
- Speaker test: the board's speaker socket now works as a media player (*Speaker*) in Home Assistant, for trying announcements. Nothing about sound shows on the board yet
- *Brightness* is always the daytime brightness, in Home Assistant and on the board's Screen page. It's kept through restarts, night and idle dimming no longer change it, and after a restart in the day the screen goes back to it. Before, it could show the night level (or 10% after a restart at night), and a restart at night could leave the screen dim all the next day
- *Daylight* theme removed. A board that was on Daylight switches to Split-flap; pick another under Theme
- Three new themes: *Split-flap* (white on dark grey flaps, like the old Solari boards), *Airport* (yellow on charcoal, like flight screens) and *Night red* (dim red, gentle on night vision; on time and delays keep a dim green and orange)

## 2.1.3 - 2026-11-19 (beta)
- Platform layout: the stops now show (with their times); they were missing at stations
- Platform layout: the 2nd/3rd train line uses the row-size text, so destinations like Blackpool North fit instead of being cut short
- Dashboard: Leave in, Station messages and Platform taken off the Board view
- Footer messages: one message per pass, taking turns, a little faster, and cut at about 200 characters (tap the i to read on). Before, two long messages took around 6 minutes to scroll, so the station name barely came back
- *Station messages* (in Home Assistant, replacing *Scroll station messages*): Hidden (no orange i at all), Icon only, or scroll along the footer every 2, 5 or 10 minutes. Scrolling messages are now orange, like the i
- Choosing a platform is easier: with Layout set to Platform, the row right under it on the Display page becomes *Platform* (it's *Page animation* otherwise, which the Platform layout doesn't use). Station messages moved onto the board, on the Extras page
- Long text is no longer cut off at 256 characters (it affected long messages and long stop lists)
- *Disruption banner* is now called *Disruption alert*: Minor/Major Delays shown in the footer, only when My Rail Commute reports the line as disrupted. In Home Assistant it becomes a new switch (switch.…_disruption_alert); the old one can be deleted

## 2.1.2 - 2026-11-19 (beta)
**Re-import the blueprint** to get stop times on route boards (the board's About page will say "Update available").

- "No more trains tonight" and the setup messages no longer show empty column headings and row bands behind them
- Removed the "Last train" label: it often appeared on trains that weren't the last of the evening
- Second lines: "Delayed 3 min", "Cancelled" and their reasons are dimmed like the rest of the line, instead of full brightness
- Routes (e.g. York to Leeds): the scrolling calling points now show each stop's time. My Rail Commute doesn't give times on routes, so the blueprint borrows them from a "Departures from" station for the same station if you have one, or else shows the arrival time at the route's end (blueprint)
- Long destinations: the board first uses the short forms real boards use (Manchester Picc, St Pancras Intl, Bristol Pkwy). If a name still doesn't fit, it slides along to show the rest, then back. With *Scrolling text* off it's shortened with "..." instead of being cut mid-word
- *Train numbers* (Display page): 1st, 2nd, 3rd dimmed under each time. A favourite shows its heart there instead. On Tube boards that row is *TfL line colours*, as before
- Station messages scroll once along the footer every few minutes (in place of the station name), led by an orange i. *Scroll station messages* in Home Assistant sets how often (2, 5 or 10 minutes, or Off; 5 by default). It follows *Scrolling text*; tapping the i still opens them
- **New layout: Platform**, replacing Focus mode. The next train in full, like a platform screen: time, destination and status, platform, train company, the reason if it's late, and every stop with its time ("Church Fenton (21:45), Garforth (21:51) and Leeds (21:58)"). The 2nd and 3rd trains take turns underneath. *Platform* (Extras page, and in Home Assistant) shows one platform's trains; the footer then reads "York  Platform 1". Boards that had Focus mode on go back to their layout: pick Platform under Layout
- When the top train leaves, the trains below slide up into place instead of jumping (with *Page animation* on)
- Dashboard reorganised to match the board's settings pages (Display, Trains, Screen and night, Extras). The Board view has the station switcher, Leave in, station messages and quick controls; firmware and demo mode moved to System. Settings that don't apply are hidden (e.g. Scroll speed with scrolling off, the night settings with night dimming off). Paste the new dashboard file to get it
- Home Assistant: a *Station* sensor shows what the board is showing by name ("York", "York to Leeds"), and *Next station* / *Previous station* buttons switch it. The dashboard's Station controls use them instead of the number. *Station number* is still there for your own automations

## 2.1.1 - 2026-11-18
**Re-import the blueprint** to get favourite train alerts (Settings > Automations & scenes > Blueprints > UK Departure Board > ⋮ > Re-import blueprint). Your automation keeps its settings. Without it, everything else still works.

- The board knows when the blueprint is out of date: the About page and a new *Blueprint* sensor say "Update available"
- Settings: five pages of eight (Display, Trains, Screen, Extras, About) instead of seven. Background and Panel warmth are now on the board too. Cancelled trains, scrolling text and the clock format are one row each that you tap through; night brightness goes down to screen off
- Settings: tap a setting and a line above the buttons says what it does; the row flashes when tapped; On/Off has a green light beside it; a smaller white heading like the board's column headings
- About page replaces Status; the Help page is gone (the touch controls are in the README). The footer hint now says "Tap the clock for settings" and settings always open on Display
- Settings, update and message screens follow the Background setting (LED gaps on Dot matrix, no bands on Plain)
- Footer: a walking figure and "5 min" or "Now" instead of "Leave in 5 min". It turns orange in the last 2 minutes and "Now" blinks slowly
- Settings: rows that don't apply are greyed out (night rows with night dimming off, Pin next train with paging off, idle brightness with idle dimming off), and the hint says why
- Settings: Calling at and Highlight stop open a list of today's stops to tap, instead of stepping through them one at a time
- After switching station or route, its name shows large for 2 seconds once the trains arrive
- Favourite trains show a small heart under the time instead of an underline (Compact's one-line rows keep the underline)
- Favourites are saved with their station ("07:42 York"), so they only count there. Times saved before, without a station, still count everywhere. Room for about 10 favourites with station names
- Favourite train alerts: pick phones in the blueprint to be notified when a favourite is late (5 min or more by default), cancelled or changes platform. The board sends an esphome.departure_board_favourite event you can use in your own automations too

## 2.1.0 - 2026-11-17
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
- Route boards (and the "calling at" filter): the heading reads "Destination (all call at Leeds)", since trains going beyond your destination are listed too
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
