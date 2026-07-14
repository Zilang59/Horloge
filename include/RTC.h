#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>
#include <time.h>
#include <HTTPClient.h>

RTC_DS3231 rtc;

int lastSundayOfMonth(int year, int month) {
    DateTime lastDay(year, month, 31, 0, 0, 0);
    return 31 - lastDay.dayOfTheWeek();
}

bool isFrenchSummerTime(const DateTime& dateTime) {
    int year = dateTime.year();
    int summerStartDay = lastSundayOfMonth(year, 3);
    int winterStartDay = lastSundayOfMonth(year, 10);

    DateTime summerStart(year, 3, summerStartDay, 3, 0, 0);
    DateTime winterStart(year, 10, winterStartDay, 3, 0, 0);

    return dateTime.unixtime() >= summerStart.unixtime() && dateTime.unixtime() < winterStart.unixtime();
}

void syncSummerTimeFlag() {
    if (!RTCok || !param.HeureEteAuto) return;

    DateTime now = rtc.now();
    bool shouldBeSummerTime = isFrenchSummerTime(now);

    if (param.HeureEte != shouldBeSummerTime) {
        param.HeureEte = shouldBeSummerTime;
        modifJson("bool", "HeureEte", param.HeureEte ? "true" : "false", PARAMETRE_FILE);
        DEBUG_PRINTLN(String("Heure ete : ") + (param.HeureEte ? "active" : "inactive"));
    }
}

void handleFrenchSummerTimeChange() {
    if (!RTCok || !param.HeureEteAuto) return;

    DateTime now = rtc.now();
    int year = now.year();
    int month = now.month();
    int day = now.day();
    int hour = now.hour();

    if (month == 3 && day == lastSundayOfMonth(year, 3) && hour >= 2 && !param.HeureEte) {
        rtc.adjust(now + TimeSpan(0, 1, 0, 0));
        param.HeureEte = true;
        modifJson("bool", "HeureEte", "true", PARAMETRE_FILE);
        DEBUG_PRINTLN("Passage automatique a l'heure d'ete");
        return;
    }

    if (month == 10 && day == lastSundayOfMonth(year, 10) && hour >= 3 && param.HeureEte) {
        rtc.adjust(now - TimeSpan(0, 1, 0, 0));
        param.HeureEte = false;
        modifJson("bool", "HeureEte", "false", PARAMETRE_FILE);
        DEBUG_PRINTLN("Passage automatique a l'heure d'hiver");
    }
}

void setupRTC() {
    DEBUG_PRINT("\n--MONTAGE RTC----------------------------\n");
    if (!rtc.begin()) {
        DEBUG_PRINTLN("RTC             : Erreur");
        while (1);
    } else {
        DEBUG_PRINTLN("RTC             : Ok");
        RTCok = true;
        syncSummerTimeFlag();
    }
    DEBUG_PRINT("-----------------------------------------\n");
}

String readRTC() {
    if(!RTCok) { return ""; }
    handleFrenchSummerTimeChange();
    DateTime now = rtc.now();
    // Serial.print("Date et Heure (RTC) : ");
    // Serial.print(now.year(), DEC);
    // Serial.print('/');
    // Serial.print(now.month(), DEC);
    // Serial.print('/');
    // Serial.print(now.day(), DEC);
    // Serial.print(" ");
    // Serial.print(now.hour(), DEC);
    // Serial.print(':');
    // Serial.print(now.minute(), DEC);
    // Serial.print(':');
    // Serial.print(now.second(), DEC);
    // Serial.println();
    // Récupérer l'heure et les minutes avec un formatage à 2 chiffres
    String hh = String(now.hour());
    if (hh.length() == 1) hh = "0" + hh;

    String mm = String(now.minute());
    if (mm.length() == 1) mm = "0" + mm;

    // Retourner l'heure au format HHMM
    return hh + mm;
}
int extractInt(String json, const char* key) { // Fonction pour extraire un entier à partir d'un champ JSON
  int index = json.indexOf(key);
  if (index >= 0) {
    int start = index + String(key).length();
    int end = json.indexOf(',', start);
    if (end < 0) end = json.indexOf('}', start); // Si c'est le dernier champ
    return json.substring(start, end).toInt();
  }
  return 0;
}


int monthIndexFromEnglishName(const String& monthName) {
  const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  for (int i = 0; i < 12; i++) {
    if (monthName == months[i]) return i + 1;
  }
  return 0;
}

int64_t daysFromCivil(int year, unsigned month, unsigned day) {
  year -= month <= 2;
  const int era = (year >= 0 ? year : year - 399) / 400;
  const unsigned yoe = static_cast<unsigned>(year - era * 400);
  const unsigned doy = (153 * (month + (month > 2 ? -3 : 9)) + 2) / 5 + day - 1;
  const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
  return era * 146097 + static_cast<int>(doe) - 719468;
}

bool parseHttpDateHeader(const String& dateHeader, DateTime& localDateTime) {
  char weekday[4] = {0};
  char monthName[4] = {0};
  int day = 0, year = 0, hour = 0, minute = 0, second = 0;

  if (sscanf(dateHeader.c_str(), "%3s, %d %3s %d %d:%d:%d GMT", weekday, &day, monthName, &year, &hour, &minute, &second) != 7) {
    return false;
  }

  int month = monthIndexFromEnglishName(String(monthName));
  if (month == 0) return false;

  time_t utcEpoch = daysFromCivil(year, month, day) * 86400 + hour * 3600 + minute * 60 + second;
  setenv("TZ", "CET-1CEST,M3.5.0/2,M10.5.0/3", 1);
  tzset();

  struct tm localTime;
  if (!localtime_r(&utcEpoch, &localTime)) return false;

  localDateTime = DateTime(
    localTime.tm_year + 1900,
    localTime.tm_mon + 1,
    localTime.tm_mday,
    localTime.tm_hour,
    localTime.tm_min,
    localTime.tm_sec
  );

  return true;
}

bool fetchHttpDateTime(DateTime& localDateTime) {
  const char* dateHeaderKeys[] = {"Date"};
  const char* urls[] = {
    "http://www.google.com/generate_204",
    "http://clients3.google.com/generate_204",
    "http://example.com/"
  };

  for (int i = 0; i < 3; i++) {
    HTTPClient http;
    http.setTimeout(8000);
    http.begin(urls[i]);
    http.collectHeaders(dateHeaderKeys, 1);

    int httpCode = http.GET();
    String dateHeader = http.header("Date");
    http.end();

    if (httpCode > 0 && dateHeader.length() > 0 && parseHttpDateHeader(dateHeader, localDateTime)) {
      DEBUG_PRINT("RTC        : Heure recuperee via HTTP Date depuis ");
      DEBUG_PRINTLN(urls[i]);
      return true;
    }
  }

  return false;
}

void applyInternetDateTime(const DateTime& internetTime, const char* sourceName) {
  rtc.adjust(internetTime);
  param.HeureEte = isFrenchSummerTime(internetTime);
  modifJson("bool", "HeureEte", param.HeureEte ? "true" : "false", PARAMETRE_FILE);
  DEBUG_PRINT("RTC        : Mise a jour reussie via ");
  DEBUG_PRINTLN(sourceName);
}

void UpdateHeure() {
    if (WiFi.status() == WL_CONNECTED) {
      const char* timeZone = "CET-1CEST,M3.5.0/2,M10.5.0/3";
      configTzTime(timeZone, "pool.ntp.org", "time.google.com", "time.cloudflare.com");

      struct tm timeInfo;
      if (getLocalTime(&timeInfo, 10000)) {
        DateTime ntpTime(
          timeInfo.tm_year + 1900,
          timeInfo.tm_mon + 1,
          timeInfo.tm_mday,
          timeInfo.tm_hour,
          timeInfo.tm_min,
          timeInfo.tm_sec
        );

        applyInternetDateTime(ntpTime, "NTP");
      } else {
        DEBUG_PRINT("RTC        : Erreur NTP\n");
        DateTime httpTime;
        if (fetchHttpDateTime(httpTime)) {
          applyInternetDateTime(httpTime, "HTTP");
        } else {
          DEBUG_PRINT("RTC        : Erreur HTTP Date\n");
        }
      }
    } else {
      DEBUG_PRINT("RTC        : Pas d'acces a internet\n");
    }
}

bool updateRTC(String timeParam) {
    if(!RTCok) { return false; }
    
    int update_year, update_month, update_day, update_hour, update_minute, update_second;
    DEBUG_PRINTLN("Données reçues : " + timeParam);

    if (sscanf(timeParam.c_str(), "%d-%d-%dT%d:%d:%d", &update_year, &update_month, &update_day, &update_hour, &update_minute, &update_second) == 6) {
      DateTime newTime(update_year, update_month, update_day, update_hour, update_minute, update_second);
      rtc.adjust(newTime);
      param.HeureEte = isFrenchSummerTime(newTime);
      modifJson("bool", "HeureEte", param.HeureEte ? "true" : "false", PARAMETRE_FILE);
      return true;
    } else {
      return false;
    }
}
