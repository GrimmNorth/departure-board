#pragma once
// UK Departure Board helpers: CrowPanel USB-pin workaround + train data helper functions.

// Workaround for I2C timeouts on the CrowPanel 7" touch bus (GPIO19/20).
// On ESP32-S3 these pins double as the USB-Serial-JTAG D-/D+ lines, so the
// USB PHY pad must be released before the I2C driver starts.
//

#include "soc/usb_serial_jtag_reg.h"
#include "soc/io_mux_reg.h"
#include "soc/soc.h"
#include "esp_heap_caps.h"
#include <map>
#include <array>
#include <string>

__attribute__((constructor)) static void crowpanel_usb_disable() {
  // Turn off the USB PHY pad and its D+ pull-up.
  CLEAR_PERI_REG_MASK(USB_SERIAL_JTAG_CONF0_REG,
                      USB_SERIAL_JTAG_USB_PAD_ENABLE | USB_SERIAL_JTAG_DP_PULLUP);

  // GPIO19 / GPIO20: plain GPIO function, input enabled, pull-up on, pull-down off.
  PIN_FUNC_SELECT(IO_MUX_GPIO19_REG, PIN_FUNC_GPIO);
  PIN_FUNC_SELECT(IO_MUX_GPIO20_REG, PIN_FUNC_GPIO);
  PIN_INPUT_ENABLE(IO_MUX_GPIO19_REG);
  PIN_INPUT_ENABLE(IO_MUX_GPIO20_REG);
  REG_SET_BIT(IO_MUX_GPIO19_REG, FUN_PU);
  REG_SET_BIT(IO_MUX_GPIO20_REG, FUN_PU);
  REG_CLR_BIT(IO_MUX_GPIO19_REG, FUN_PD);
  REG_CLR_BIT(IO_MUX_GPIO20_REG, FUN_PD);
}

#include <string>
#include <cctype>
#include <vector>
#include <cstring>

namespace departure {

// true if an HA attribute came through as a real value
inline bool valid(const std::string &s) {
  return !(s.empty() || s == "unknown" || s == "unavailable" || s == "None" || s == "none");
}

// calling_points arrives from HA as a stringified list, e.g. ['Selby', 'Leeds']
// or ["Selby", "Leeds"]. Returns all names in order.
inline std::vector<std::string> points(const std::string &s) {
  std::vector<std::string> out;
  size_t i = 0;
  while (i < s.size()) {
    size_t a = s.find_first_of("'\"", i);
    if (a == std::string::npos) break;
    char q = s[a];
    // closing quote: the quote char followed by ',' or ']'
    size_t b = a + 1;
    while (true) {
      b = s.find(q, b);
      if (b == std::string::npos) return out;
      size_t nx = b + 1;
      if (nx >= s.size() || s[nx] == ',' || s[nx] == ']') break;
      b++;
    }
    out.push_back(s.substr(a + 1, b - a - 1));
    i = b + 1;
  }
  return out;
}

// destination = last calling point, truncated
inline std::string destination(const std::string &s, size_t max_len) {
  auto p = points(s);
  if (p.empty()) return "";
  std::string d = p.back();
  if (d.size() > max_len) d.resize(max_len);
  return d;
}

// Short forms used on real boards, tried one at a time (whole words only) until a long destination fits.
static const char *const ABBR[][2] = {
    {"International", "Intl"}, {"Parkway", "Pkwy"}, {"Piccadilly", "Picc"}, {"Junction", "Jn"},
    {"Interchange", "Int"}, {"Central", "Ctl"}, {"Street", "St"}, {"Road", "Rd"}, {"Square", "Sq"},
    {"Airport", "Apt"}};
static const size_t ABBR_N = sizeof(ABBR) / sizeof(ABBR[0]);
inline bool abbrev_word(std::string &s, size_t i) {
  if (i >= ABBR_N) return false;
  const std::string w = ABBR[i][0];
  size_t p = 0;
  bool done = false;
  while ((p = s.find(w, p)) != std::string::npos) {
    const bool l = p == 0 || !isalpha((unsigned char) s[p - 1]);
    const bool r = p + w.size() >= s.size() || !isalpha((unsigned char) s[p + w.size()]);
    if (l && r) { s.replace(p, w.size(), ABBR[i][1]); done = true; p += strlen(ABBR[i][1]); }
    else p += w.size();
  }
  return done;
}

// "Selby, Leeds, York" truncated to max_len
inline std::string calling_list(const std::string &s, size_t max_len) {
  auto p = points(s);
  std::string out;
  for (size_t i = 0; i < p.size(); i++) {
    if (i) out += ", ";
    out += p[i];
  }
  if (out.size() > max_len) out.resize(max_len);
  return out;
}

// true if an "HH:MM" time is already in the past by more than `grace` minutes.
// Handles midnight wrap: anything up to 12h behind now counts as departed.
inline bool departed(const std::string &hhmm, int nowmin, int grace = 1) {
  if (nowmin < 0 || hhmm.size() < 5) return false;
  int h = atoi(hhmm.substr(0, 2).c_str()), m = atoi(hhmm.substr(3, 2).c_str());
  int diff = ((nowmin - (h * 60 + m)) % 1440 + 1440) % 1440;
  return diff > grace && diff < 720;
}

// true if any calling point contains `filter` (case-insensitive)
inline bool calls_at(const std::string &calls, const std::string &filter) {
  if (filter.empty()) return true;
  auto low = [](std::string s) { for (auto &c : s) c = tolower((unsigned char) c); return s; };
  std::string f = low(filter);
  for (auto &p : points(calls))
    if (low(p).find(f) != std::string::npos) return true;
  return false;
}

// minutes from now until an "HH:MM" time. 0 if it is already past, -1 if unknown.
inline int minutes_until(const std::string &hhmm, int nowmin) {
  if (nowmin < 0 || hhmm.size() < 5) return -1;
  int h = atoi(hhmm.substr(0, 2).c_str()), m = atoi(hhmm.substr(3, 2).c_str());
  int diff = ((h * 60 + m - nowmin) % 1440 + 1440) % 1440;
  return diff > 720 ? 0 : diff;
}

// true if `hhmm` appears in a comma/space separated list such as "07:42, 08:15"
inline bool in_list(const std::string &list, const std::string &hhmm) {
  return !list.empty() && hhmm.size() >= 5 && list.find(hhmm) != std::string::npos;
}

// HA boolean attributes arrive as "True"/"False" (or true/false/on/1)
inline bool truthy(const std::string &s) {
  return s == "True" || s == "true" || s == "on" || s == "1";
}


// case-insensitive equality
inline bool ieq(const std::string &a, const std::string &b) {
  if (a.size() != b.size()) return false;
  for (size_t i = 0; i < a.size(); i++)
    if (tolower((unsigned char) a[i]) != tolower((unsigned char) b[i])) return false;
  return true;
}

// Favourite trains, e.g. "07:42 Brough, 08:15": a time followed by a station only counts at that
// station; a time on its own counts everywhere. Times can also be separated by spaces ("07:42 08:15").
struct Fav { std::string hhmm, station; };
inline bool is_hhmm(const std::string &s) {
  return s.size() == 5 && isdigit((unsigned char) s[0]) && isdigit((unsigned char) s[1]) && s[2] == ':' &&
         isdigit((unsigned char) s[3]) && isdigit((unsigned char) s[4]);
}
inline std::vector<Fav> favs(const std::string &list) {
  std::vector<Fav> out;
  std::string tok;
  auto flush = [&]() {
    if (tok.empty()) return;
    if (is_hhmm(tok)) out.push_back({tok, ""});
    else if (!out.empty()) out.back().station += (out.back().station.empty() ? "" : " ") + tok;
    tok.clear();
  };
  for (char ch : list + ",") {
    if (ch == ',') { flush(); if (!out.empty() && !out.back().station.empty()) out.push_back({"", ""}); }
    else if (ch == ' ') flush();
    else tok += ch;
  }
  std::vector<Fav> clean;                       // drop the separators added above
  for (auto &f : out) if (!f.hhmm.empty()) clean.push_back(f);
  return clean;
}
inline bool fav_match(const std::string &list, const std::string &hhmm, const std::string &station) {
  if (list.empty() || hhmm.size() < 5) return false;
  const std::string t = hhmm.substr(0, 5);
  for (auto &f : favs(list))
    if (f.hhmm == t && (f.station.empty() || ieq(f.station, station))) return true;
  return false;
}
// Press and hold: removes the favourite that matches this train, or adds "HH:MM Station".
// Returns false (and leaves `out` alone) when there's no room.
inline bool fav_toggle(const std::string &list, const std::string &hhmm, const std::string &station,
                       size_t maxlen, std::string &out, bool &added) {
  const std::string t = hhmm.substr(0, 5);
  std::string res;
  bool removed = false;
  for (auto &f : favs(list)) {
    if (f.hhmm == t && (f.station.empty() || ieq(f.station, station))) { removed = true; continue; }
    if (!res.empty()) res += ", ";
    res += f.hhmm + (f.station.empty() ? "" : " " + f.station);
  }
  if (!removed) {
    std::string e = station.empty() ? t : t + " " + station;
    if (res.size() + 2 + e.size() > maxlen) return false;
    if (!res.empty()) res += ", ";
    res += e;
  }
  out = res;
  added = !removed;
  return true;
}

// Finds the stop `fav` inside a scrolling "Calling at A 10:00, B 10:10" string.
// Returns the start index and sets `end` to one past the end of that stop's entry
// (name and time), or returns -1 if the stop is not there.
inline int find_stop(const std::string &s, const std::string &fav, int &end) {
  if (fav.empty()) return -1;
  std::string ls = s, lf = fav;
  for (auto &c : ls) c = tolower((unsigned char) c);
  for (auto &c : lf) c = tolower((unsigned char) c);
  size_t pos = 0;
  while ((pos = ls.find(lf, pos)) != std::string::npos) {
    bool start_ok = pos == 0 || (pos >= 2 && ls.compare(pos - 2, 2, ", ") == 0) ||
                    (pos >= 11 && ls.compare(pos - 11, 11, "calling at ") == 0);
    size_t a = pos + lf.size();
    bool end_ok = a >= ls.size() || ls[a] == ',' || (ls[a] == ' ' && a + 1 < ls.size() && isdigit((unsigned char) ls[a + 1]));
    if (start_ok && end_ok) {
      size_t e = ls.find(", ", a);
      end = (int) (e == std::string::npos ? s.size() : e);
      return (int) pos;
    }
    pos++;
  }
  return -1;
}

// ---- the trains the board shows: filled by Home Assistant (or the demo), read when drawing ----
struct Train {
  std::string sched, exp, plat, pchg, stat, dreason, creason, oper, delaym, sarr, earr, pprev, stops, calls;
};
inline std::array<Train, 10> &trains() { static std::array<Train, 10> t; return t; }
inline Train &train(int n) { return trains()[(n >= 1 && n <= 10) ? n - 1 : 0]; }   // n counts from 1

}  // namespace departure
