#include <Arduino.h>

// Définition centralisée des paramètres enregistrées dans le SPIFFS (utiliser dans le script param.nomdelavariable)
    #define PARAM_LIST \
    X(String, Version, "1.0.0") \
    X(bool, Admin_site, false)

// Ne pas toucher, sert au variable du PARAM_LIST
    struct Parametres {
        #define X(type, name, defaultValue) type name = defaultValue;
        PARAM_LIST
        #undef X

        void toJson(JsonDocument& doc) {
            #define X(type, name, defaultValue) doc[#name] = name;
            PARAM_LIST
            #undef X
        }

        void fromJson(JsonDocument& doc) {
            #define X(type, name, defaultValue) if (doc.containsKey(#name)) name = doc[#name].as<type>();
            PARAM_LIST
            #undef X
        }
    };
    Parametres param;

// Variables de setup
    bool Alexa_Setuped = false;
    bool OTA_Setuped = false;
    bool spiffs_ready = false;

// Ajout d'autre variable globales ici si besoin