#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

String readRTC() {
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


