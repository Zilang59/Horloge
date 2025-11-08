#include <Arduino.h>
#include <WebServer.h>

// Variables générales
    String Dispo_basename = "Horloge_mini"; //Pas de caractères spéciaux, espaces...
    String Dispo_version = "1.0.0"; // Version du code
    String Lien_OTA_Update = "https://github.com/Zilang59/Horloge/tree/main/release"; // Lien vers le dossier des releases de mises à jour OTA (laisser vide si pas de mise à jour)
    #define DEBUG  // Mets en commentaire cette ligne pour désactiver les Serial.print()
    // Commande pour éviter de voir des erreurs lié au fichier .h : pio init --ide vscode



// Include Généraux
  #include <DONOTTOUCH/VariablesGlobales.h>
  #include <Variables.h>
  #include "AllFunction.h" // Fichier généré automatiquement pour éviter les erreurs de "fonction non déclarées"
  #include "DONOTTOUCH/setupSPIFFS.h"   // Gestion du système de fichier SPIFFS
  #include "DONOTTOUCH/OTA_Update.h"    // Gestion des mises à jour OTA (setupWIFI.H doit etre activé)
  #include "Fonctions.h"                // Include diverses fonctions utiles
  // #include <Alexa.h>                 // Utilisation de Alexa (setupWIFI.H doit etre activé)
  #include <setupWIFI.h>             // Gestion du Wi-Fi et du Hotspot

// Include diverses
  // #include <Horloge_grande.h>   // Choisissser le type d'horloge (grande ou mini)
  #include <Horloge_Mini.h>  // Choisissser le type d'horloge (grande ou mini)
  #include <Infrarouge.h>   // Gestion du module infrarouge
  #include <RTC.h>   // Gestion du module RTC
  #include <LED_RGB.h>     // Gestion des LEDs choisir celui adapté au led (LED_RGB.h ou LED_RGBW.h) ou commenter pour ne pas utiliser

void setup() {
  // Initialisation de la communication série
    delay(100);
    #ifdef DEBUG
        Serial.begin(115200);
        delay(50);
    #endif

  // Setup des inputs outputs
      SetupPinout();
      delay(10);

  // Setup du Real Time Clock
      setupRTC();
      delay(10);

  // Paramétrage des fichiers et des paramètres mémoire
    #ifdef setupSpiffsH
      DEBUG_PRINT("\n--MONTAGE SPIFFS-------------------------\n");
      spiffs_ready = setupSPIFFS();
      if (spiffs_ready) {
        setupSPIFFS_wififile();     // Mettre en commentaire si on ne veux pas gérer de réseau wi-fi
        setupSPIFFS_parametres();   // Mettre en commentaire si on ne veux pas de paramètres
      
        if(param.Version != Dispo_version) {
          param.Version = Dispo_version;
          DEBUG_PRINTLN("Mise à jour de la version : " + Dispo_version);
          modifJson("String", "Version", Dispo_version, PARAMETRE_FILE);
        }
      }

      DEBUG_PRINT("-----------------------------------------\n");
      delay(10);
    #endif

    
  // Paramétrage de la LED
    #ifdef ledrgbH
      LED_setup();
      delay(10);
    #endif

  // Essayer de se connecter à un réseau Wi-Fi
    #ifdef setupWifiH
      if (!connectToWiFi()) {   // On n'a pas pu se connecter à un reseau local wi-fi
          setupHotspot(); // On génère la page de gestion des réseaux Wifi
          IsConnectedToWifi = false;
          delay(10);
      } else {  // Connexion à un réseau Wi-Fi réussie
          IsConnectedToWifi = true;
          // setupHotspot(); // On génère quand meme le hotspot au cas ou on aurais perdu l'ip ou des informations, il sera visible 2 minutes puis désactiver dans la fonction "loop_wifi"
          wifiConnectedTime = millis();
          #ifdef AlexaH
            SetupAlexa();
          #endif
          delay(10);
      }
      DEBUG_PRINT("-----------------------------------------\n");
      delay(10);
    #endif

  // Activation du OTA si il est défini et qu'on utilise le wifi
    #if defined(setupOTAH) && defined(setupWifiH)
      setupOTA();
    #endif

  // Ajouter ici les autres fonctions de setup si besoin
    setupRTC(); delay(10);
    #if defined(PIN_INFRAROUGE)
      setupInfrarouge(); delay(10);
    #endif

  // Finalisation du Setup
    #if defined(DEBUG) && defined(setupSpiffsH)
        printMemorySummary();
    #endif
    DEBUG_PRINTLN(" =====> Setup OK");
    ESPStarted = millis();

  delay(50);
}

void loop() {
  // Gestion des connexions
    #if defined(setupWifiH)
      loop_Wifi();
    #endif

  // Gestion de l'infrarouge
    #if defined(PIN_INFRAROUGE)
      loop_Infrarouge();
    #endif

  // Gestion de l'affichage de l'heure
  Loop_Ecran();

  delay(1);
}