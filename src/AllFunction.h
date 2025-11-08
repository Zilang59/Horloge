// Fichier généré automatiquement
// Includes nécessaires pour les types utilisés
#include <NeoPixelBus.h>
#include <ArduinoJson.h>

// DONOTTOUCH/OTA_Update.h
    void handleOTA();
    void setupOTA();

// DONOTTOUCH/setupSPIFFS.h
    String ReadParametreFile();
    bool setupSPIFFS();
    void deleteFile(const char* fileName);
    void modifJson(String type, String key, String newValue, String fileName);
    void printMemorySummary();
    void setupSPIFFS_parametres();
    void setupSPIFFS_wififile();

// Fonctions.h
    String decryptPassword(const String& encryptedPassword);
    String encryptPassword(const String& password);
    String formatTime(uint16_t totalSeconds);
    String getDeviceKey();

// Horloge_Mini.h
    void Loop_Ecran();
    void SetupPinout();
    void ShowHeure();
    void afficherChiffre(int chiffre, int digit);
    void afficherSecondes(int pourcentage);

// Infrarouge.h
    void loop_Infrarouge();
    void setupInfrarouge();

// LED_RGB.h
    void LED_setup();
    void setLEDsWithBrightness(String hexColor, uint16_t ledIndices[], uint16_t numLeds, uint8_t brightness);

// RTC.h
    String readRTC();
    int extractInt(String json, const char* key);
    void UpdateHeure();
    void setupRTC();

// Variables.h
    struct Parametres;
    void fromJson(JsonDocument& doc);
    void toJson(JsonDocument& doc);

// setupWIFI.h
    String getUniqueESP32ID();
    bool compareVersions(String newVersion, String currentVersion);
    bool connectToWiFi();
    bool loop_Wifi();
    void accueil(WebServer* activeServer);
    void admin_site(WebServer* activeServer);
    void check_firmware_updates(WebServer* activeServer);
    void gestion_wifi(WebServer* activeServer);
    void informations(WebServer* activeServer);
    void parameter_info(WebServer* activeServer);
    void parametres(WebServer* clientServer);
    void resetESP();
    void resetPARAMETRE();
    void setupHotspot();
    void startWebServer();
    void update_firmware(WebServer* activeServer);

