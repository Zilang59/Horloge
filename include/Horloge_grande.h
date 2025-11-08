#include <Arduino.h>

// Réglage IO
    #define PIN_LEDS 13
    #define NUM_LEDS 99
    #define PIN_INFRAROUGE 15
    #define PIN_LUMINOSITE 32
    #define LED_TYPE WS2812B  // Type de LEDs
    #define COLOR_ORDER GRB   // Ordre des couleurs

/* Numérotation des LEDs
    8    7    6               40  39  38                   60   59   58                  92  91  90
9               5          41            37            61               57           93             89
10              4          42            36      47    62               56           94             88
11              3          43            35      48    63               55           95             87
12  0    1    2   22 23 24    44  45  46 34      49    64  52   53   54     74 75 76     96  97  98 86
13              21         25            33      50    65               73           77             85
14              20         26            32      51    66               72           78             84
15              19         27            31            67               71           79             83
   16   17   18               28  29  30                   68   69   70                  80  81  82
  
    8    7    6               40  39  38                   60   59   58                  92  91  90
9               5          41            37            61               57           93             89
10              4          42            36      47    62               56           94             88
11              3          43            35      48    63               55           95             87
    0    1    2               44  45  46                   52   53   54                 96  97  98   
13              21         25            33      50    65               73           77             85
14              20         26            32      51    66               72           78             84
15              19         27            31            67               71           79             83
   16   17   18               28  29  30                   68   69   70                  80  81  82

LEDs cachées : 12, 22, 23, 24, 34, 49, 64, 74, 75, 76, 86 (jamais allumées)
*/

// Constitution des LEDs pour chaque caractère (adaptées à la grande horloge)
// Digit 1 : LEDs 0-21 (dizaines heures)
// Digit 2 : LEDs 25-46 (unités heures) 
// Digit 3 : LEDs 52-73 (dizaines minutes) - éviter 74,75,76
// Digit 4 : LEDs 77-98 (unités minutes)
// Deux points : LEDs 47, 48, 50, 51

const int caracteres_digit1[11][24] = {
    /*0*/ {3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20, 21, -1},
    /*1*/ {3, 4, 5, 19, 20, 21, -1},
    /*2*/ {0, 1, 2, 3, 4, 5, 6, 7, 8, 13, 14, 15, 16, 17, 18, -1},
    /*3*/ {0, 1, 2, 3, 4, 5, 6, 7, 8, 16, 17, 18, 19, 20, 21, -1},
    /*4*/ {0, 1, 2, 3, 4, 5, 9, 10, 11, 19, 20, 21, -1},
    /*5*/ {0, 1, 2, 6, 7, 8, 9, 10, 11, 16, 17, 18, 19, 20, 21, -1},
    /*6*/ {0, 1, 2, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20, 21, -1},
    /*7*/ {3, 4, 5, 6, 7, 8, 19, 20, 21, -1},
    /*8*/ {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20, 21, -1},
    /*9*/ {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 16, 17, 18, 19, 20, 21, -1},
    /*rien*/ {-1}
};

const int caracteres_digit2[11][24] = {
    /*0*/ {25, 26, 27, 28, 29, 30, 31, 32, 33, 35, 36, 37, 38, 39, 40, 41, 42, 43, -1},
    /*1*/ {31, 32, 33, 35, 36, 37, -1},
    /*2*/ {25, 26, 27, 28, 29, 30, 35, 36, 37, 38, 39, 40, 44, 45, 46, -1},
    /*3*/ {28,29,30,31,32,33,35,36,37,38,39,40,44,45,46, -1},
    /*4*/ {31,32,33,35,36,37,41,42,43,44,45,46, -1},
    /*5*/ {28,29,30,31,32,33,38,39,40,41,42,43,44,45,46, -1},
    /*6*/ {25,26,27,28,29,30,31,32,33,38,39,40,41,42,43,44,45,46, -1},
    /*7*/ {31, 32, 33, 35, 36, 37, 38, 39, 40, -1},
    /*8*/ {25, 26, 27, 28, 29, 30, 31, 32, 33, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, -1},
    /*9*/ {28, 29, 30, 31, 32, 33, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46 -1},
    /*rien*/ {-1}
};

const int caracteres_digit3[11][24] = {
    /*0*/ {55, 56, 57, 58, 59, 60, 61, 62, 63, 65, 66, 67, 68, 69, 70, 71, 72, 73, -1},
    /*1*/ {55, 56, 57, 71, 72, 73, -1},
    /*2*/ {52, 53, 54, 55, 56, 57, 58, 59, 60, 65, 66, 67, 68, 69, 70, -1},
    /*3*/ {52,53,54,55,56,57,58,59,60,68,69,70,71,72,73, -1},
    /*4*/ {52,53,54,55,56,57,61,62,63,71,72,73, -1},
    /*5*/ {52,53,54,58,59,60,61,62,63,68,69,70,71,72,73, -1},
    /*6*/ {52,53,54,58,59,60,61,62,63,65,66,67,68,69,70,71,72,73, -1},
    /*7*/ {55, 56, 57, 58, 59, 60, 71, 72, 73, -1},
    /*8*/ {52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 65, 66, 67, 68, 69, 70, 71, 72, 73, -1},
    /*9*/ {52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 68, 69, 70, 71, 72, 73 -1},
    /*rien*/ {-1}
};

const int caracteres_digit4[11][24] = {
    /*0*/ {77, 78, 79, 80, 81, 82, 83, 84, 85, 87, 88, 89, 90, 91, 92, 93, 94, 95, -1},
    /*1*/ {83, 84, 85, 87, 88, 89, -1},
    /*2*/ {77, 78, 79, 80, 81, 82, 87, 88, 89, 90, 91, 92, 96, 97, 98, -1},
    /*3*/ {80,81,82,83,84,85,87,88,89,90,91,92,96,97,98, -1},
    /*4*/ {83,84,85,87,88,89,93,94,95,96,97,98, -1},
    /*5*/ {80,81,82,83,84,85,90,91,92,93,94,95,96,97,98, -1},
    /*6*/ {77,78,79,80,81,82,83,84,85,90,91,92,93,94,95,96,97,98, -1},
    /*7*/ {83, 84, 85, 87, 88, 89, 90, 91, 92, -1},
    /*8*/ {77, 78, 79, 80, 81, 82, 83, 84, 85, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, -1},
    /*9*/ {80, 81, 82, 83, 84, 85, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, -1},
    /*rien*/ {-1}
};

String HHMM_actual = "9999";
bool toggleSecondes = false; // Pour le clignotement des deux points
int leds[NUM_LEDS];
bool RTC_Updated = false;

void SetupPinout() {
    pinMode(PIN_LEDS, OUTPUT);
    pinMode(PIN_INFRAROUGE, INPUT);
    pinMode(PIN_LUMINOSITE, INPUT);
}

void ShowHeure() {
    String HHMM = readRTC();
    if(HHMM != HHMM_actual || update_screen) {
        HHMM_actual = HHMM;
        update_screen = false;
        if (HHMM.length() == 4) {
            afficherChiffre(HHMM[0] - '0', 1); // Dizaines heures
            afficherChiffre(HHMM[1] - '0', 2); // Unités heures  
            afficherChiffre(HHMM[2] - '0', 3); // Dizaines minutes
            afficherChiffre(HHMM[3] - '0', 4); // Unités minutes
        } else {
            afficherChiffre(10, 1); // rien
            afficherChiffre(10, 2); // rien
            afficherChiffre(10, 3); // rien
            afficherChiffre(10, 4); // rien
        }
    }
}

void afficherChiffre(int chiffre, int digit) {
    if (chiffre < 0 || chiffre > 10 || digit < 1 || digit > 4) return;
  
    // Déterminer l'intervalle de LEDs et le tableau de segments pour le digit donné
    int debut = 0, fin = 0;
    const int* segments = nullptr;
    
    switch (digit) {
        case 1: // Dizaines heures (LEDs 0-21)
            debut = 0; fin = 21;
            segments = caracteres_digit1[chiffre];
            break;
        case 2: // Unités heures (LEDs 25-46)  
            debut = 25; fin = 46;
            segments = caracteres_digit2[chiffre];
            break;
        case 3: // Dizaines minutes (LEDs 52-73, éviter 74-76)
            debut = 52; fin = 73;
            segments = caracteres_digit3[chiffre];
            break;
        case 4: // Unités minutes (LEDs 77-98)
            debut = 77; fin = 98;
            segments = caracteres_digit4[chiffre];
            break;
        default: return;
    }
  
    // Effacer les LEDs du digit spécifié (dans son intervalle)
    uint16_t ledsToErase[fin - debut + 2];
    int eraseCount = 0;
    for (int i = debut; i <= fin; i++) {
        // Éviter les LEDs cachées et les LEDs des deux points
        if (i != 12 && i != 22 && i != 23 && i != 24 && i != 34 && 
            i != 47 && i != 48 && i != 49 && i != 50 && i != 51 && 
            i != 64 && i != 74 && i != 75 && i != 76 && i != 86) {
            ledsToErase[eraseCount++] = i;
        }
    }
    setLEDsWithBrightness("#000000", ledsToErase, eraseCount, 0);
  
    // Allumer les LEDs correspondant au chiffre dans ce digit
    uint16_t ledsToLight[24];
    int ledCount = 0;
    for (int i = 0; segments[i] != -1 && ledCount < 24; i++) {
        int ledIndex = segments[i];
        // Vérifier que l'index est dans l'intervalle et n'est pas une LED cachée ou des deux points
        if (ledIndex >= debut && ledIndex <= fin && 
            ledIndex != 12 && ledIndex != 22 && ledIndex != 23 && ledIndex != 24 && 
            ledIndex != 34 && ledIndex != 47 && ledIndex != 48 && ledIndex != 49 && 
            ledIndex != 50 && ledIndex != 51 && ledIndex != 64 && ledIndex != 74 && 
            ledIndex != 75 && ledIndex != 76 && ledIndex != 86) {
            ledsToLight[ledCount++] = ledIndex;
        }
    }
  
    // Allumer les LEDs avec la couleur et luminosité configurées
    if (ledCount > 0) {
        setLEDsWithBrightness(param.couleur, ledsToLight, ledCount, param.luminosite);
    }
}

void afficherSecondes(int pourcentage) {
    // Pour la grande horloge, utiliser les LEDs des deux points (47, 48, 50, 51)
    int ledsAllumees = map(pourcentage, 0, 100, 0, 4); // Mapper sur 4 LEDs
    
    uint16_t ledsToControl[4] = {47, 48, 50, 51}; // LEDs des deux points
    
    if (ledsAllumees > 0) {
        // Allumer les LEDs correspondant au pourcentage
        uint16_t ledsToLight[ledsAllumees];
        for (int i = 0; i < ledsAllumees; i++) {
            ledsToLight[i] = ledsToControl[i];
        }
        setLEDsWithBrightness(param.couleur, ledsToLight, ledsAllumees, param.luminosite);
        
        // Éteindre les autres LEDs
        if (ledsAllumees < 4) {
            uint16_t ledsToOff[4 - ledsAllumees];
            int offCount = 0;
            for (int i = ledsAllumees; i < 4; i++) {
                ledsToOff[offCount++] = ledsToControl[i];
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

    // Mise a jour du RTC toutes les heures
    #if defined(setupWifiH)
        if(IsConnectedToWifi && RTCok) {
            // Extraire les minutes de HHMM_actual (ex: "1435" -> "35")
            String minutes = HHMM_actual.substring(2, 4);
            
            if(minutes == "05" && !RTC_Updated) {
                UpdateHeure();
                RTC_Updated = true;
            }
            if(minutes == "07" && RTC_Updated) { RTC_Updated = false; }
        }
    #endif
}
