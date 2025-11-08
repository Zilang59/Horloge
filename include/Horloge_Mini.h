#include <Arduino.h>

// Réglage IO
    #define PIN_LEDS 14
    #define NUM_LEDS 96
    #define LED_TYPE WS2812B  // Type de LEDs
    #define COLOR_ORDER GRB   // Ordre des couleurs

/*
    00 19 18 17 16    23 42 41 40 39          50 69 68 67 66   73 92 91 90 89
    01          15    24          38    46    51          65   74          88
    02          14    25          37    47    52          64   75          87
    03 20 21 22 13    26 43 44 45 36          53 70 71 72 63   76 93 94 95 86
    04          12    27          35    48    54          62   77          85
    05          11    28          34    49    55          61   78          84
    06 07 08 09 10    29 30 31 32 33          56 57 58 59 60   79 80 81 82 83
*/
// Constitution des LEDs pour chaque caractère
    const int caracteres[37][24] = {
      /*0*/     {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, -1},
      /*1*/     {16, 15, 14, 13, 12, 11, 10, -1},
      /*2*/     {0, 19, 18, 17, 16, 15, 14, 13, 22, 21, 20, 3, 4, 5, 6, 7, 8, 9, 10, -1},
      /*3*/     {0, 19, 18, 17, 16, 15, 14, 12, 11, 10, 9, 8, 7, 6, 22, 21, 20, 13, -1},
      /*4*/     {0, 1, 2, 3, 20, 21, 22, 10, 11, 12, 13, 14, 15, 16, -1},
      /*5*/     {0, 19, 18, 17, 16, 1, 2, 3, 20, 21, 22, 13, 12, 11, 10, 9, 8, 7, 6, -1},
      /*6*/     {16, 17, 18, 19, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 22, 21, 20, -1},
      /*7*/     {0, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, -1},
      /*8*/     {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, -1},
      /*9*/     {0, 1, 2, 3, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, -1},
      /*A10*/   {1, 2, 3, 4, 5, 6, 10, 11, 12, 13, 14, 15, 17, 18, 19, 20, 21, 22, -1},
      /*B11*/   {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 14, 15, 17, 18, 19, 20, 21, 22, -1},
      /*C12*/   {1, 2, 3, 4, 5, 7, 8, 9, 10, 16, 17, 18, 19, -1},
      /*D13*/   {0,1,2,3,4,5,6,7,8,9,11,12,13,14,15,17,18,19, -1},
      /*E14*/   {0,1,2,3,4,5,6,7,8,9,10,16,17,18,19,20,21, -1},
      /*F15*/   {0,1,2,3,4,5,6,16,17,18,19,20,21, -1},
      /*G16*/   {1,2,3,4,5,7,8,9,11,12,22,21,17,18,19, -1},
      /*H17*/   {0,1,2,3,4,5,6,10,11,12,13,14,15,16,20,21,22, -1},
      /*I18*/   {16, 15, 14, 13, 12, 11, 10, -1},
      /*J19*/   {0,19,18,17,16,15,14,13,12,11,9,8,7,5, -1},
      /*K20*/   {0,1,2,3,4,5,6,20,18,8, -1},
      /*L21*/   {0,1,2,3,4,5,6,7,8,9,10, -1},
      /*M22*/   {0,1,2,3,4,5,6,19,17,10,11,12,13,14,15,16,21, -1},
      /*N23*/   {0,1,2,3,4,5,6,10,11,12,13,14,15,16,19,9,21, -1},
      /*O24*/   {1,2,3,4,5,7,8,9,11,12,13,14,15,17,18,19, -1},
      /*P25*/   {0,1,2,3,4,5,6,19,18,17,15,14,20,21,22, -1},
      /*Q26*/   {1,2,3,4,5,7,8,9,11,12,13,14,15,17,18,19,10,21, -1},
      /*R27*/   {1, 2, 3, 4, 5, 6, 11, 12, 14, 15, 17, 18, 19, 20, 21, 22, 10, -1},
      /*S28*/   {19, 18, 17, 16, 1, 2, 20, 21, 22, 12, 11, 9, 8, 7, 6, -1},
      /*T29*/   {0,19,18,17,16,21,8, -1},
      /*U30*/   {0,1,2,3,4,5,7,8,9,11,12,13,14,15,16, -1},
      /*V31*/   {0,1,2,3,4,8,12,13,14,15,16, -1},
      /*W32*/   {0,1,2,3,4,5,6,7,9,10,11,12,13,14,15,16,21, -1},
      /*X33*/   {0,21,10,6,16, -1},
      /*Y34*/   {0,1,2,3,20,21,22,10,11,12,14,14,15,16,9,8,7, -1},
      /*Z35*/   {0,19,18,17,16,21,6,7,8,9,10, -1},
      /*rien36*/   {-1},
    };

    String HHMM_actual = "9999";
    bool update_screen = false;
    bool toggleSecondes = false; // Pour le clignotement des deux points
    int leds[NUM_LEDS];
    bool RTC_Updated = false;




void SetupPinout() {
    pinMode(PIN_LEDS, OUTPUT);
}

void ShowHeure() {
    String HHMM = readRTC();
    if(HHMM != HHMM_actual || update_screen) {
        HHMM_actual = HHMM;
        update_screen = false;
        if (HHMM.length() == 4) {
            afficherChiffre(HHMM[0] - '0', 1);
            afficherChiffre(HHMM[1] - '0', 2);
            afficherChiffre(HHMM[2] - '0', 3);
            afficherChiffre(HHMM[3] - '0', 4);
        } else {
            afficherChiffre(14, 1);
            afficherChiffre(27, 2);
            afficherChiffre(27, 3);
            afficherChiffre(36, 4);
        }
    }
}

void afficherChiffre(int chiffre, int digit) {
    if (chiffre < 0 || chiffre > 35 || digit < 1 || digit > 4) return;
  
    // Déterminer l'intervalle de LEDs pour le digit donné
    int debut = 0, fin = 0;
    switch (digit) {
      case 1: debut = 0; fin = 22; break;
      case 2: debut = 23; fin = 45; break;
      case 3: debut = 50; fin = 72; break;
      case 4: debut = 73; fin = 95; break;
      default: return; // Digit invalide
    }
  
    // Effacer les LEDs du digit spécifié (dans son intervalle)
    uint16_t ledsToErase[fin - debut + 2];
    int eraseCount = 0;
    for (int i = debut; i <= fin; i++) {
      ledsToErase[eraseCount++] = i;
    }
    setLEDsWithBrightness("#000000", ledsToErase, eraseCount, 0);
  
    // Allumer les LEDs correspondant au chiffre dans ce digit
    uint16_t ledsToLight[24]; // Tableau pour les LEDs à allumer
    int ledCount = 0;
    for (int i = 0; caracteres[chiffre][i] != -1 && ledCount < 24; i++) {
      int ledIndex = caracteres[chiffre][i] + debut; // Décaler selon le digit
      if (ledIndex >= debut && ledIndex <= fin) {  // Vérifier que l'index est dans l'intervalle
        ledsToLight[ledCount++] = ledIndex;
      }
    }
  
    // Allumer les LEDs avec la couleur et luminosité configurées
    if (ledCount > 0) {
      setLEDsWithBrightness(param.couleur, ledsToLight, ledCount, param.luminosite);
    }
  }

void afficherSecondes(int pourcentage) {
    int ledsAllumees = map(pourcentage, 0, 100, 0, 4); // Mapper de 0 à 100% sur 0-4 LEDs
    
    uint16_t ledsToControl[4];
    for (int i = 0; i < 4; i++) {
        ledsToControl[i] = 46 + i;
    }
    
    if (ledsAllumees > 0) {
        // Allumer les LEDs correspondant au pourcentage
        uint16_t ledsToLight[ledsAllumees];
        for (int i = 0; i < ledsAllumees; i++) {
            ledsToLight[i] = 46 + i;
        }
        setLEDsWithBrightness(param.couleur, ledsToLight, ledsAllumees, param.luminosite);  // Luminosité fixe à 10
        
        // Éteindre les autres LEDs
        if (ledsAllumees < 4) {
            uint16_t ledsToOff[4 - ledsAllumees];
            int offCount = 0;
            for (int i = ledsAllumees; i < 4; i++) {
                ledsToOff[offCount++] = 46 + i;
            }
            setLEDsWithBrightness("#000000", ledsToOff, offCount, 0);
        }
    } else {
        // Éteindre toutes les LEDs des secondes
        setLEDsWithBrightness("#000000", ledsToControl, 4, 0);
    }
}

void Loop_Ecran() {
    static unsigned long lastRefresh = 0;
    static unsigned long lastBlink = 0;
    unsigned long currentMillis = millis();
    
    // Rafraîchir l'heure toutes les secondes
    if (currentMillis - lastRefresh >= 1000) {
        lastRefresh = currentMillis;
        ShowHeure();
    }

    // Faire clignoter les deux points toutes les 1000ms
    if (currentMillis - lastBlink >= 1000) {
        lastBlink = currentMillis;
        toggleSecondes = !toggleSecondes;
        
        // Alterner entre afficherSecondes(100) et afficherSecondes(0)
        if (toggleSecondes) {
            afficherSecondes(100); // Affiche les deux points
        } else {
            afficherSecondes(0); // Éteint les deux points
        }
    }



    // Mise a jour du RTC tous les jour à la même heure
    #if defined(setupWifiH)
        if(IsConnectedToWifi && RTCok) {
            if(HHMM_actual == "0400" && !RTC_Updated) {
                UpdateHeure();
                RTC_Updated = true;
            }
            if(HHMM_actual == "0402" && RTC_Updated) { RTC_Updated = false; }
        }
    #endif
}

