#include <Arduino.h>

#define pinoutH true

// Définition des broches et configurations
    #define BOUTON 13

void SetupInOut() {
    pinMode(BOUTON, INPUT_PULLUP);
}