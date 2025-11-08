# 🕐 Horloge Connectée LED

Une horloge numérique connectée affichant l'heure sur des LED RGB, compatible avec WiFi, serveur web intégré et synchronisation en direct.

**Disponible en deux versions :**
- 📱 **Version Portable** : Batterie intégrée, compacte, rechargeable USB-C 5V
- 🖥️ **Version Bureau** : Alimentation USB 5V, plus grande, pour affichage permanent

---

## ✨ Fonctionnalités

### 📡 Connectivité
- ✅ **WiFi intégré** : Synchronisation automatique via API HTTP
- ✅ **Serveur web embarqué** : Interface de configuration accessible depuis n'importe quel appareil
- ✅ **API JSON** : Récupération de l'heure via HTTP pour intégration tierce
- ✅ **Synchronisation locale** : Appairage direct avec un appareil sans réseau
- ✅ **Commande Alexa** : Support intégré pour appareils Amazon Alexa

### 🎨 Affichage
- 🔴 **LED RGB** : Affichage coloré de l'heure avec support multicolore
- 🌈 **Customisation** : Choix des couleurs d'affichage
- 🔆 **Ajustement de luminosité** : Adaptation automatique à la lumière ambiante

### ⚙️ Mise à jour
- 🔄 **OTA (Over-The-Air)** : Mise à jour du firmware via WiFi sans accès direct à l'appareil
- 📦 **SPIFFS intégré** : Stockage de fichiers pour les configurations

### 🔋 Alimentation
- 🪫 **Batterie rechargeable** (version portable)
- 🔌 **USB 5V** pour alimentation externe
- ⚡ **Gestion d'énergie** optimisée

---

## 📸 Galerie

- 🖥️ **Version bureau** : Horloge grande, fonctionnement 24/7
- 📱 **Version portable** : Mini horloge compacte, batterie intégrée

---

## 🛠️ Matériel

### Électronique
- **Microcontrôleur** : ESP32
- **Affichage** : LED RGB ou LED RGB+W (adressables)
- **Batterie** (version portable) : LiPo 3.7V rechargeable
- **Module WiFi** : Intégré à l'ESP32

### Architecture mémoire
Configuration flexible avec support OTA :
- **4 Mo** : Configuration standard avec SPIFFS 500Ko

### Fichiers Gerber (a venir)
Les fichiers de circuit imprimé (PCB) sont disponibles dans le dossier "PCB".

### Fichiers 3D (a venir)
Les fichiers 3D pour l'impression 3D des support sont disponible dans le dossier du projet "fichiers 3D".

---

## 🚀 Démarrage rapide

### 1. Installation des dépendances

```bash
# Cloner le repository
git clone https://github.com/Zilang59/Horloge.git
cd Horloge

# Installer PlatformIO (si ce n'est pas déjà fait)
pip install platformio
```

### 2. Configuration matériel

Éditer `platformio.ini` pour sélectionner votre configuration :

```ini
[env:esp32]
board = esp32-c3-devkitm-1                          # ou esp32dev, esp32-s3-devkitm-1
board_build.partitions = memory/4Mo_OTA_avec_SPIFFS_500Ko.csv
```


### 3. Compilation et téléversement

```bash
# Compiler et téléverser via USB
pio run -t upload

# Ou avec OTA (après le premier téléversement)
pio run -t upload -o '--upload_port=192.168.1.XX'
```

---

## 💻 Interface Web

Une fois l'horloge connectée au WiFi, accédez à l'interface web :

```
http://horloge_IDESP.local/  (si mDNS activé)
ou
http://192.168.1.XX/   (adresse IP de l'horloge)
```

### Fonctionnalités disponibles :
- 📊 **Tableau de bord** : État actuel et statut WiFi
- ⚙️ **Configuration** : Paramètres WiFi, fuseau horaire, couleurs
- 🔐 **Accueil** : Page d'accueil du serveur
- 🛜 **Gestion WiFi** : Connexion à différents réseaux

---


### Synchronisation sans WiFi

La synchronisation locale est disponible pour :
- Appareils Bluetooth/WebSocket
- Communication directe via API locale
- Interface web sur réseau local

---


## 🔧 Configuration avancée

### Sélectionner la partition mémoire

Pour les ESP32 avec 8 Mo, débloquez plus d'espace SPIFFS :

```ini
# Actuellement (4 Mo)
board_build.partitions = memory/4Mo_OTA_avec_SPIFFS_500Ko.csv

# Ou pour 8 Mo
board_build.partitions = memory/8Mo_OTA_avec_SPIFFS_3Mo.csv
```

### OTA (Mise à jour en ligne)

Une fois l'appareil configuré, mettez à jour le firmware sans câble USB :

```bash
pio run -t upload --upload-port=horloge.local
```


## 📦 Dépendances

Le projet utilise les bibliothèques suivantes :

- **ArduinoJson** : Parsing JSON pour configuration
- **FauxmoESP** v3.4.1 : Intégration Alexa
- **NeoPixelBus** : Contrôle LED RGB adressables

Toutes sont gérées automatiquement par PlatformIO.

---

## 🐛 Dépannage

### L'horloge ne se connecte pas au WiFi
- ✅ Vérifier les identifiants WiFi dans `include/setupWIFI.h`
- ✅ Vérifier la puissance du signal WiFi
- ✅ Réinitialiser l'appareil (appui long sur le bouton de reset)

### L'interface web n'est pas accessible
- ✅ Vérifier que l'horloge est connectée au WiFi
- ✅ Essayer l'adresse IP directement au lieu du mDNS
- ✅ Vérifier le pare-feu local

---

## 📋 Prochaines étapes

Les ressources suivantes seront ajoutées :

- 📄 **Guide d'assemblage** : Instructions pour monter les deux versions
- 🔧 **Fichiers Gerber** : Pour fabrication PCB professionnelle
- 📖 **Documentation technique** : Schéma électrique et pinout détaillé
- 🎨 **Exemples d'intégration** : Utilisation avec domotique (Home Assistant, etc.)

---

## 📄 Licence

Ce projet est publié sous licence libre. Consultez le fichier `LICENSE` pour les détails.

---

## 👨‍💻 Contributions

Les contributions sont bienvenues ! 

Pour contribuer :
1. Fork le repository
2. Créez une branche feature (`git checkout -b feature/AmazingFeature`)
3. Commit vos changements (`git commit -m 'Add AmazingFeature'`)
4. Push vers la branche (`git push origin feature/AmazingFeature`)
5. Ouvrez une Pull Request

---

## 📞 Support

Pour les questions ou problèmes :
- 📧 Ouvrir une issue sur GitHub
- 💬 Discussion dans les discussions du projet
- 🔍 Consulter la documentation du projet

---

## 🎯 Roadmap

- [ ] Interface web améliorée avec thème sombre
- [ ] Support Bluetooth Low Energy (BLE)
- [ ] Application mobile (iOS/Android)
- [ ] Integration avec Home Assistant
- [ ] Mode économie d'énergie avancé
- [ ] Support multi-zones horaires
- [ ] Historique de synchronisation

---

## 🙏 Remerciements

Merci à tous les contributeurs et à la communauté ESP32 pour les ressources et les bibliothèques utilisées.

---

**Créé avec ❤️ pour les amateurs d'électronique et de domotique.**

*Dernière mise à jour : Novembre 2025*
