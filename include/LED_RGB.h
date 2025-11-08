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

/**
 * Définit une ou plusieurs LEDs à une couleur avec une luminosité spécifique
 * 
 * @param hexColor Couleur RGB (format "#RRGGBB")
 * @param ledIndices Tableau contenant les indices des LEDs à définir
 * @param numLeds Nombre d'éléments dans le tableau ledIndices
 * @param brightness Luminosité de 0 à 255 (0 = éteint, 255 = luminosité max)
 * 
 * Exemple :
 *   uint16_t leds[] = {0, 5, 10, 15};
 *   setLEDsWithBrightness("#FF0000", leds, 4, 200);  // Allume les LEDs 0,5,10,15 en rouge à 200/255
*/
void setLEDsWithBrightness(String hexColor, uint16_t ledIndices[], uint16_t numLeds, uint8_t brightness) {
    // Limiter la luminosité entre 0 et 255
    brightness = constrain(brightness, 0, 255);
    
    // Convertir la couleur hexadécimale en RgbColor
    RgbColor color = hexToNeopixelbus(hexColor);
    
    // Calculer les composantes de couleur ajustées par la luminosité
    uint8_t r = (uint8_t)((color.R * brightness) / 255);
    uint8_t g = (uint8_t)((color.G * brightness) / 255);
    uint8_t b = (uint8_t)((color.B * brightness) / 255);
    
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

