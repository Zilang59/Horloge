#include <Arduino.h>

// Réglage IO
    #define PIN_LEDS 13
    #define NUM_LEDS 99
    #define PIN_INFRAROUGE 15
    #define PIN_LUMINOSITE 32


// Réglage des variables concernant les LEDs
/*
        8    7    6               40  39  38                   60   59   58               92  91  90
    9               5          41            37            61               57        93             89
    10              4          42            36      47    62               56        94             88
    11              3          43            35      48    63               55        95             87
    12  0    1    2   22 23 24    44  45  46 34      49    64  52   53   54  74 75 76     96  97  98 86
    13              21         25            33      50    65               73        77             85
    14              20         26            32      51    66               72        78             84
    15              19         27            31            67               71        79             83
       16   17   18               28  29  30                   68   69   70               80  81  82
*/
    // Table de segments pour les chiffres 0-9 sur ton affichage (remplace avec tes propres indices de LEDs)
        const int caracteres_unit[11][24] = {
            /*0*/ {25, 26, 27, 28, 29, 30, 31, 32, 33, 35, 36, 37, 38, 39, 40, 41, 42, 43, -1},
            /*1*/ {31, 32, 33, 35, 36, 37, -1},
            /*2*/ {28, 29, 30, 25, 26, 27, 44, 45, 46, 35, 36, 37, 38, 39, 40, -1},
            /*3*/ {40, 39, 38, 37, 36, 35, 33, 32, 31, 30, 29, 28, 46, 45, 44, -1},
            /*4*/ {41, 42, 43, 44, 45, 46, 31, 32, 33, 35, 36, 37, -1},
            /*5*/ {38, 39, 40, 41, 42, 43, 44, 45, 46, 33, 32, 31, 30, 29, 28, -1},
            /*6*/ {38, 39, 40, 41, 42, 43, 44, 45, 46, 25, 26, 27, 28, 29, 30, 31, 32, 33, -1},
            /*7*/ {40, 39, 38, 37, 36, 35, 33, 32, 31, -1},
            /*8*/ {25, 26, 27, 28, 29, 30, 31, 32, 33, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, -1},
            /*9*/ {28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, -1},
            /*rien36*/ {-1},
        };
        const int caracteres_diz[11][24] = {
            /*0*/ {3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20, 21, -1},
            /*1*/ {3, 4, 5, 19, 20, 21, -1},
            /*2*/ {8, 7, 6, 5, 4, 3, 2, 1, 0, 13, 14, 15, 16, 17, 18, -1},
            /*3*/ {8, 7, 6, 5, 4, 3, 2, 1, 0, 21, 20, 19, 18, 17, 16, -1},
            /*4*/ {9, 10, 11, 0, 1, 2, 3, 4, 5, 19, 20, 21, -1},
            /*5*/ {6, 7, 8, 9, 10, 11, 0, 1, 2, 21, 20, 19, 18, 17, 16, -1},
            /*6*/ {6, 7, 8, 9, 10, 11, 0, 1, 2, 13, 14, 15, 16, 17, 18, 19, 20, 21, -1},
            /*7*/ {8, 7, 6, 5, 4, 21, 20, 19, -1},
            /*8*/ {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20, 21, -1},
            /*9*/ {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 16, 17, 18, 19, 20, 21, -1},
            /*rien36*/ {-1},
        };

        const int deuxpoint_start = 47;
        const int deuxpoint_stop = 51;

        String HHMM_actual = "9999";
        bool update_screen = false;





void SetupPinout() {
    pinMode(PIN_LEDS, OUTPUT);
    pinMode(PIN_INFRAROUGE, INPUT);
    pinMode(PIN_LUMINOSITE, INPUT);
}


void ShowHeure() {
    String HHMM = readRTC();
    if (HHMM != HHMM_actual || update_screen) {
        HHMM_actual = HHMM;
        update_screen = false;
        if (HHMM.length() == 4)
        {
            afficherChiffre(HHMM[0] - '0', 1);
            afficherChiffre(HHMM[1] - '0', 2);
            afficherChiffre(HHMM[2] - '0', 3);
            afficherChiffre(HHMM[3] - '0', 4);
        }
        strip.show();
        DEBUG_PRINTLN("Mise a jour des LED : " + String(HHMM));
    }
}