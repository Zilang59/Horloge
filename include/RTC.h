#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setupRTC() {
    DEBUG_PRINT("\n--MONTAGE RTC----------------------------\n");
    if (!rtc.begin()) {
        DEBUG_PRINTLN("RTC             : Erreur");
        while (1);
    } else {
        DEBUG_PRINTLN("RTC             : Ok");
        RTCok = true;
    }
    DEBUG_PRINT("-----------------------------------------\n");
}

String readRTC() {
    if(!RTCok) { return ""; }
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

void UpdateHeure() {
    const char* apiUrl = "https://timeapi.io/api/Time/current/zone?timeZone=Europe/Paris";
  
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(apiUrl); // Initialisation de la requête HTTP
      int httpCode = http.GET();
  
      if (httpCode == 200) { // Si la requête réussit
        String payload = http.getString();
        // Serial.println("Réponse API : ");
        // Serial.println(payload);
  
        // Extraction des valeurs JSON
        int year = extractInt(payload, "\"year\":");
        int month = extractInt(payload, "\"month\":");
        int day = extractInt(payload, "\"day\":");
        int hour = extractInt(payload, "\"hour\":");
        int minute = extractInt(payload, "\"minute\":");
        int second = extractInt(payload, "\"seconds\":");
  
        // Mise à jour du RTC
        rtc.adjust(DateTime(year, month, day, hour, minute, second));
        DEBUG_PRINT("RTC        : Mise a jour réussie\n");
      } else {
        DEBUG_PRINT("RTC        : Erreur ");
        DEBUG_PRINT(httpCode);
      }
      http.end();
    } else {
      DEBUG_PRINT("RTC        : Pas d'accès à internet\n");
    }
}


