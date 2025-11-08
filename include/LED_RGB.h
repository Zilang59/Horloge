#include <Arduino.h>
#include <NeoPixelBus.h>

#define ledrgbH true


NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(NUM_LEDS, PIN_LEDS); // RGB avec NeoPixelBus

RgbColor currentColor;

int brightness = 128;
int brightness_min = 10;
int brightness_max = 255;
int fadeAmount = 5;
unsigned long previousMillis = 0;
int base_interval = 10; // Intervalle de base pour la respiration
int base_brightness = 128;

// Variables pour la transition de luminosité lisse
int currentBrightness = 128;      // Luminosité actuelle affichée
int targetBrightness = 128;       // Luminosité cible
int startBrightness = 128;        // Luminosité au début de la transition
unsigned long brightnessTransitionStart = 0;
const unsigned long BRIGHTNESS_TRANSITION_TIME = 2000; // Durée de transition en ms (2 secondes)
// inTransition est défini dans Variables.h

RgbColor hexToNeopixelbus(String hex) {
    if (hex.charAt(0) == '#') {
        hex.remove(0, 1);
    }

    if (hex.length() == 8) {
        hex = hex.substring(0, 6);  // Ignore la composante W
    }

    if (hex.length() != 6) {
        return RgbColor(0, 0, 0);
    }

    long number = strtoul(hex.c_str(), NULL, 16);

    byte r = (number >> 16) & 0xFF;
    byte g = (number >> 8) & 0xFF;
    byte b = number & 0xFF;

    return RgbColor(r, g, b);
}
void LED_setup() {
    strip.Begin();
    strip.Show();

    // Allumer chaque LED en rouge par exemple
    for (int i = 0; i < NUM_LEDS; i++) {
        strip.SetPixelColor(i, hexToNeopixelbus("#000000")); // Éteint les LEDs au démarrage
    }

    strip.Show(); // Met à jour les LEDs

    
    ShowHeure();
}


void setLEDsWithBrightness(String hexColor, uint16_t ledIndices[], uint16_t numLeds, uint8_t brightness) { // setLEDsWithBrightness("#FF0000", {0, 5, 10, 15}, 4, 200);
    // Limiter la luminosité entre 0 et 255
    brightness = constrain(brightness, 0, 255);
    
    // Convertir la couleur hexadécimale en RgbColor
    RgbColor color = hexToNeopixelbus(hexColor);
    
    // Calculer les composantes de couleur ajustées par la luminosité actuelle (lissée)
    uint8_t r = (uint8_t)((color.R * currentBrightness) / 255);
    uint8_t g = (uint8_t)((color.G * currentBrightness) / 255);
    uint8_t b = (uint8_t)((color.B * currentBrightness) / 255);
    
    RgbColor adjustedColor(r, g, b);
    
    // Appliquer la couleur à chaque LED du tableau
    for (uint16_t i = 0; i < numLeds; i++) {
        if (ledIndices[i] < NUM_LEDS) {  // Vérifier que l'indice est valide
            strip.SetPixelColor(ledIndices[i], adjustedColor);
        }
    }
    
    // Mettre à jour l'affichage
    strip.Show();
}

void updateBrightnessTransition() {
    // Vérifier si la luminosité cible a changé
    if (targetBrightness != param.luminosite) {
        startBrightness = currentBrightness;  // Sauvegarder la luminosité actuelle
        targetBrightness = param.luminosite;
        brightnessTransitionStart = millis();
        inTransition = true;
    }
    
    // Si on a atteint la cible, terminer la transition
    if (currentBrightness == targetBrightness) {
        inTransition = false;
        return;
    }
    
    // Calculer le temps écoulé depuis le début de la transition
    unsigned long elapsedTime = millis() - brightnessTransitionStart;
    
    // Si le temps de transition est dépassé, on a atteint la cible
    if (elapsedTime >= BRIGHTNESS_TRANSITION_TIME) {
        currentBrightness = targetBrightness;
        inTransition = false;
    } else {
        // Interpolation linéaire de startBrightness vers targetBrightness
        float progress = (float)elapsedTime / BRIGHTNESS_TRANSITION_TIME;
        int newBrightness = (int)(startBrightness + (targetBrightness - startBrightness) * progress);
        
        // Seulement rafraîchir si la luminosité a vraiment changé
        if (newBrightness != currentBrightness) {
            currentBrightness = newBrightness;
            update_screen = true;
            ShowHeure();
        }
    }
}

