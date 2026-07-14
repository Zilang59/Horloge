#pragma once

const char SiteWeb_Accueil[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>%DISPO_NAME%</title>
    <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
    <link href="https://fonts.googleapis.com/css2?family=Orbitron:wght@400;700&display=swap" rel="stylesheet">
    <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
    <style>
* {margin: 0; padding: 0; box-sizing: border-box;}

body {
  display: flex;
  height: 100vh;
  font-family: sans-serif;
  background: #f3f3f3;
}

/* --- MENU LATÉRAL --- */
.sidebar {
  background: #222;
  color: #fff;
  width: 250px;
  transition: width 0.3s;
  display: flex;
  flex-direction: column;
  align-items: stretch; /* prend toute la largeur */
  height: 100%;
  overflow: hidden;
  justify-content: flex-start; /* tout en haut */
  padding-bottom: 20px; /* pour laisser un peu d'espace pour le bas */
}

.menu-top {
  display: flex;
  flex-direction: column;
  width: 100%; /* prend toute la largeur */
  margin-top: 0; /* en haut */
}

.menu-bottom-container {
  display: flex;
  flex-direction: column;
  gap: 10px;
  margin-top: auto; /* pousse tout vers le bas */
}


.sidebar.collapsed {
  width: 70px;
}

.logo {
  font-size: 1.8em;
  margin: 20px 0;
  cursor: pointer;
  user-select: none;
  transition: transform 0.3s;
  transform-origin: center;
  display: flex;
  justify-content: center;
  height: 50px; /* fixe pour éviter le déplacement */
}
.logo:hover { transform: scale(1.1); }

.menu-item {
  width: 100%;
  padding: 15px 20px;
  display: flex;
  align-items: center;
  gap: 10px;
  cursor: pointer;
  transition: background 0.2s;
}

.menu-item-bottom {
  width: 100%;
  padding: 2px 20px;
  display: flex;
  align-items: center;
  gap: 10px;
  cursor: pointer;
  transition: background 0.2s;
}
.menu-item:hover,
.menu-item-bottom:hover {
    background: #333;
}


.menu-item a,
.menu-item-bottom a {
  display: flex;
  align-items: center;
  gap: 10px;
  width: 100%;
  color: inherit;
  text-decoration: none;
}

.menu-item a:hover,
.menu-item-bottom a:hover {
    background: #333;
}

.menu-item-bottom {
  margin-top: auto;
}

.menu-item i, .menu-item-bottom i { font-size: 1.2em; }
.menu-item span, .menu-item-bottom span { transition: opacity 0.3s; }

/* cache le texte des menus normaux et bas quand menu rétracté */
.sidebar.collapsed .menu-item span:not(.material-icons),
.sidebar.collapsed .menu-item-bottom span:not(.material-icons) {
  opacity: 0;
  pointer-events: none;
}

/* --- CONTENU PRINCIPAL --- */
.main {
    flex: 1;
    padding: 30px;
    overflow-y: auto;
    transition: margin-left 0.3s;
}

.main h1 {
  text-align: center;
  margin-bottom: 20px;
}

/* --- RESPONSIVE --- */
@media (max-width: 768px) {
    .sidebar {
        width: 70px; /* étroit par défaut */
    }

    .sidebar.expanded {
        width: 250px; /* s’étend quand on clique sur le logo */
    }

    .sidebar .menu-item span:not(.material-icons),
    .sidebar .menu-item-bottom span:not(.material-icons) {
        opacity: 0;
        pointer-events: none;
    }

    .sidebar.expanded .menu-item span:not(.material-icons),
    .sidebar.expanded .menu-item-bottom span:not(.material-icons) {
        opacity: 1;
        pointer-events: auto;
    }
}










.bouton {
  cursor: pointer;
  color: #888888;
  transition: all 0.3s ease;
}
.bouton:hover {
  color: #2e2e2e;
  font-size: 30px;
}

.wait-light {
  margin-top: -20px;
  margin-left: 30px;
  color: #000000;
  animation: spin 2s linear infinite;
  font-size: 20px;
  opacity: 0;              /* invisible au départ */
  transition: opacity 0.7s ease;
  transform-origin: center;
  pointer-events: none;
  display:block;
}

.wait-light.visible {
  opacity: 1;
}
.wait-light.error {
  color: red;
}

@keyframes spin {
  from { transform: rotate(0deg); }
  to { transform: rotate(-360deg); }
}



.section {
  border: 1px solid #ccc;
  border-radius: 10px;
  padding: 15px;
  background-color: #f9f9f9;
  display: flex;
  flex-direction: column;
  gap: 10px;
  width: 100%;
  max-width: 400px; /* limite largeur sur tablette/desktop */
  margin: 0 auto;   /* centre sur grand écran */
  margin-bottom: 10px;
}
.section h2 {
    margin: 0;
    font-size: 1.2em;
    text-align: center;
}
.color-picker-container {
  display: flex;       /* utilise flexbox pour aligner horizontalement */
  gap: 5px;            /* espace entre les icônes */
  flex-wrap: nowrap;   /* empêche le retour à la ligne */
  align-items: center; /* aligne verticalement */
  width:100%;
  justify-content: center;
}
.color-picker-icon {
  margin-left : 10px;
  margin-right : 10px;
  cursor: pointer;
}
.sub-icon {
  position:relative;
  margin-top:30px;
  margin-left:-25px;
  color : #858585;
}
.icon-on { color: gold; }
.icon-off { color: rgb(39, 39, 39); }

.icon-small { font-size: 13px; }
.icon-medium { font-size: 24px; }
.icon-large { font-size: 48px; }
input.color-input {
  position: absolute;
  width: 1px;
  height: 1px;
  opacity: 0;
  pointer-events: none;
}






.toggle-container {
    margin-top: 0px;
    text-align: center;
}

.toggle {
    display: flex;
    align-items: center;
    justify-content: center;
    gap: 10px;
}

.toggle input[type="checkbox"] {
    appearance: none;
    width: 50px;
    height: 25px;
    background: #ddd;
    border-radius: 20px;
    position: relative;
    cursor: pointer;
    transition: background 0.3s;
}



.toggle input[type="checkbox"]::before {
    content: "";
    position: absolute;
    width: 20px;
    height: 20px;
    background: white;
    border-radius: 50%;
    top: 2.5px;
    left: 3px;
    transition: transform 0.3s;
}

.toggle input[type="checkbox"]:checked::before {
    transform: translateX(25px);
}


.line {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin: 8px 0;
}

.luminosite-section {
  flex-direction: column;
  justify-content: center;
  align-items: center;
  gap: 12px;
}

.luminosite-section .label {
  margin-bottom: 5px;
}

.luminosite-section input[type="range"] {
  width: 100%;
  max-width: 250px;
}

.luminosity-control {
  width: 100%;
  flex-direction: column;
  align-items: center;
  gap: 10px;
}

.sensor-range-control {
  max-width: 320px;
}

.sensor-current,
.dual-range-values {
  display: flex;
  justify-content: space-between;
  width: 100%;
  font-size: 0.85em;
  font-variant-numeric: tabular-nums;
}

.sensor-current {
  justify-content: center;
}

.dual-range {
  position: relative;
  width: 100%;
  height: 34px;
}

.dual-range-track,
.dual-range-selection {
  position: absolute;
  left: 0;
  right: 0;
  top: 14px;
  height: 6px;
  border-radius: 6px;
}

.dual-range-track {
  background: #d2d2d2;
}

.dual-range-selection {
  background: #4CAF50;
}

.dual-range-current {
  position: absolute;
  top: 6px;
  width: 2px;
  height: 22px;
  background: #111;
  transform: translateX(-1px);
  pointer-events: none;
  display: none;
}

.dual-range-current.visible {
  display: block;
}

.saved-feedback {
  animation: savedPulse 0.55s ease;
}

.dual-range.saved-feedback .dual-range-selection,
input.saved-feedback::-webkit-slider-thumb,
input.saved-feedback::-moz-range-thumb,
.toggle input.saved-feedback[type="checkbox"] {
  animation: savedPulse 0.55s ease;
}

@keyframes savedPulse {
  0%, 100% { box-shadow: none; }
  35% { box-shadow: 0 0 0 5px rgba(76, 175, 80, 0.35); }
}

.dual-range input[type="range"] {
  position: absolute;
  inset: 0;
  width: 100%;
  max-width: none;
  margin: 0;
  background: transparent;
  pointer-events: none;
  appearance: none;
}

.dual-range input[type="range"]::-webkit-slider-thumb {
  appearance: none;
  width: 18px;
  height: 18px;
  border-radius: 50%;
  background: #222;
  border: 2px solid #fff;
  box-shadow: 0 1px 4px rgba(0,0,0,0.35);
  pointer-events: auto;
  cursor: pointer;
}

.dual-range input[type="range"]::-moz-range-thumb {
  width: 18px;
  height: 18px;
  border-radius: 50%;
  background: #222;
  border: 2px solid #fff;
  box-shadow: 0 1px 4px rgba(0,0,0,0.35);
  pointer-events: auto;
  cursor: pointer;
}

.dual-range input[type="range"]::-webkit-slider-runnable-track {
  background: transparent;
}

.dual-range input[type="range"]::-moz-range-track {
  background: transparent;
}

.label {
  color : black;
}

.sublabel {
  font-size: 10px;
  text-align: right;
  margin-left: auto;
  margin-right: 10px;
}

.sublabel.off {
  color: rgb(160, 160, 160);
}

.sublabel.on {
  color: black;
}

.switch {
  position: relative;
  display: inline-block;
  width: 42px;
  height: 24px;
}
.switch input {
  opacity: 0;
  width: 0;
  height: 0;
}
.slider {
  position: absolute;
  cursor: pointer;
  top: 0; left: 0;
  right: 0; bottom: 0;
  background-color: #ccc;
  transition: .3s;
  border-radius: 24px;
}
.slider:before {
  position: absolute;
  content: "";
  height: 18px; width: 18px;
  left: 3px; bottom: 3px;
  background-color: white;
  transition: .3s;
  border-radius: 50%;
}
input:checked + .slider {
  background-color: #4CAF50;
}
input:checked + .slider:before {
  transform: translateX(18px);
}


.spoiler-btn {
  background-color: #eee;
  border: 1px solid #ccc;
  padding: 1px 12px;
  cursor: pointer;
  border-radius: 4px;
  margin-top: 2px;
  width:100%;
  font-size:12px;
}

.spoiler-btn:hover {
  background-color: #ddd;
}

.spoiler-block {
  display: none;
  border: 1px solid #ccc;
  border-radius: 4px;
  padding: 10px;
  margin-top: 5px;
  background-color: #f9f9f9;
  font-size: 0.9em;
  color: #333;
}

/* Afficheur 7 segments */
.seven-segment-display {
  display: flex;
  align-items: center;
  justify-content: center;
  gap: 0px;
  margin: -10px 0;
  font-family: 'Orbitron', monospace;
  font-weight: bold;
  cursor: pointer;
}

.digit {
  font-size: 35px;
  color: #00ff00;
  padding: 3px 3px;
  border-radius: 8px;
  min-width: 10px;
  text-align: center;
  text-shadow: 0 0 5px #000000;
  transition: color 0.3s ease;
}

.separator {
  font-size: 35px;
  color: #00ff00;
  text-shadow: 0 0 5px #000000;
  animation: blink 1s infinite;
  transition: color 0.3s ease;
}

@keyframes blink {
  0%, 50% { opacity: 1; }
  51%, 100% { opacity: 0.3; }
}


</style> <!-- Sera remplacé automatique par la page style.css de ce même répertoire -->
</head>
<body>
    <!-- Menu lateral -->
    <div class="sidebar" id="sidebar">
        <div class="logo" id="logo"><span class="material-icons">apps</span></div>

        <!-- menu du haut -->
        <div class="menu-top">
            <div class="menu-item"><a href="/accueil"><span class="material-icons">home</span><span>Accueil</span></a></div>
            <div class="menu-item"><a href="/wifi"><span class="material-icons">wifi</span><span>Connexion</span></a></div>
            <div class="menu-item"><a href="/informations"><span class="material-icons">info</span><span>Informations</span></a></div>
        </div>

        <!-- menu du bas -->
        <div class="menu-bottom-container">
            <div class="menu-item-bottom" style="display:block;%DISPLAY_MENU_ADMIN%"><a href="/parametres.json"><span class="material-icons">data_object</span><span>Parametres.json</span></a></div>
            <div class="menu-item-bottom" style="display:block;%DISPLAY_MENU_ADMIN%"><a href="/wifi.json"><span class="material-icons">data_object</span><span>Wifi.json</span></a></div>
            <div class="menu-item-bottom" style="display:block;%DISPLAY_MENU_ADMIN%"><a href="/restart"><span class="material-icons">restart_alt</span><span>Redémarrer</span></a></div>
            <div class="menu-item-bottom" style="display:block;%DISPLAY_MENU_ADMIN%"><a href="/reset"><span class="material-icons">credit_card_off</span><span>Remise a zero</span></a></div>
        </div>
    </div>

    <div class="main">
        <h1>Paramètrages</h1>

        
        <div class="section">
            <h2>Couleur de l'affichage</h2>
            <div class="color-picker-container">
                <!-- Afficheur 7 segments pour simuler l'horloge -->
                <div class="seven-segment-display">
                    <div class="digit" style="color:#%COULEUR%;" id="hour1">0</div>
                    <div class="digit" style="color:#%COULEUR%;" id="hour2">0</div>
                    <div class="separator" style="color:#%COULEUR%;" id="separator">:</div>
                    <div class="digit" style="color:#%COULEUR%;" id="min1">0</div>
                    <div class="digit" style="color:#%COULEUR%;" id="min2">0</div>
                </div>

                <!-- inputs de couleur invisibles -->
                <input type="color" id="inputOn" value="#%COULEUR%" class="color-input" style="display:block;">

                <span class="material-icons bouton icon-medium" title="synchroniser" id="synchronize_clock">upload</span>
            </div>
        </div>
        <div class="section">
            <h2>Intensité lumineuse</h2>
            <div class="line luminosite-section">
                <div class="toggle-container" style="display:none;%SENSORLIGHT%;">
                    <div class="toggle">
                        <span>Manuelle</span>
                        <input type="checkbox" id="toggleSwitch" %LUMAUTO% onchange="Changebouton();">
                        <span>Automatique</span>
                    </div>
                </div>
                <div id="manualLuminosityControl" class="luminosity-control" style="%LUMAUTO_DISPLAY%">
                    <input type="range" id="luminosite" min="2" max="150" value="%LUMINOSITE%">
                </div>
                <div id="sensorLuminosityControl" class="luminosity-control sensor-range-control" style="%LUMSENSOR_DISPLAY%">
                    <div class="sensor-current">Actuel : <span id="luminositeSensorValue">--</span></div>
                    <div class="dual-range" id="luminosityDetectionRange">
                        <div class="dual-range-track"></div>
                        <div class="dual-range-selection" id="luminosityDetectionSelection"></div>
                        <div class="dual-range-current" id="luminositySensorMarker"></div>
                        <input type="range" id="luminositeDetectionMin" min="0" max="4096" value="%LUMINOSITE_DETECTION_MIN%" aria-label="Detection min">
                        <input type="range" id="luminositeDetectionMax" min="0" max="4096" value="%LUMINOSITE_DETECTION_MAX%" aria-label="Detection max">
                    </div>
                    <div class="dual-range-values">
                        <span>Min <b id="luminositeDetectionMinValue">%LUMINOSITE_DETECTION_MIN%</b></span>
                        <span>Max <b id="luminositeDetectionMaxValue">%LUMINOSITE_DETECTION_MAX%</b></span>
                    </div>
                </div>
            </div>
        </div>
        <div class="section">
            <h2>Heure ete / hiver</h2>
            <div class="line luminosite-section">
                <div class="toggle-container">
                    <div class="toggle">
                        <span>Manuelle</span>
                        <input type="checkbox" id="heureEteAutoSwitch" %HEURE_ETE_AUTO% onchange="ChangeHeureEteAuto();">
                        <span>Automatique</span>
                    </div>
                </div>
            </div>
        </div>
        <div class="section">
            <h2>Affichage</h2>
            <div class="line luminosite-section">
                <div class="toggle-container">
                    <div class="toggle">
                        <span>Normal</span>
                        <input type="checkbox" id="affichageInverseSwitch" %AFFICHAGE_INVERSE% onchange="ChangeAffichageInverse();">
                        <span>Inverse</span>
                    </div>
                </div>
            </div>
        </div>
    </div>

    
    <script>
window.onload = function() {
  RefreshInfo();
  updateClock(); // Mettre à jour l'horloge au chargement
  setInterval(updateClock, 1000); // Mettre à jour toutes les secondes
};





const sidebar = document.getElementById('sidebar');
const logo = document.getElementById('logo');

function initSidebar() {
  if (window.innerWidth <= 768) {
    sidebar.classList.remove('collapsed');
    sidebar.classList.remove('expanded'); // étroit par défaut sur petit écran
  } else {
    sidebar.classList.remove('expanded');
    sidebar.classList.remove('collapsed'); // étendu par défaut sur grand écran
  }
}

logo.addEventListener('click', () => {
  if (window.innerWidth <= 768) {
    sidebar.classList.toggle('expanded'); // mobile : élargir/réduire
  } else {
    sidebar.classList.toggle('collapsed'); // desktop : réduire/élargir
  }
});

window.addEventListener('resize', initSidebar);
window.addEventListener('load', initSidebar);

function RefreshInfo() {
  // Fonction pour faire la requête
  const fetchData = () => {
    fetch("/parameter_info")
      .then(res => res.json())
      .then(data => {
        if('%MENU_ADMIN%') { console.log(JSON.stringify(data)); }
      })
      .catch(() => {
        console.log("impossible de contacter le serveur");
      });
  };

  // Exécuter immédiatement
  fetchData();
}


function showSavedFeedback(element) {
  if (!element) return;
  element.classList.remove("saved-feedback");
  void element.offsetWidth;
  element.classList.add("saved-feedback");
  setTimeout(() => element.classList.remove("saved-feedback"), 650);
}
// Fonction pour mettre à jour l'affichage de l'heure
  function updateClock() {
    const now = new Date();
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    
    document.getElementById('hour1').textContent = hours[0];
    document.getElementById('hour2').textContent = hours[1];
    document.getElementById('min1').textContent = minutes[0];
    document.getElementById('min2').textContent = minutes[1];
  }
// Fonction pour synchroniser l'horloge
  const synchronize_clock = document.getElementById("synchronize_clock");
  synchronize_clock.addEventListener('click', () => {
    const date = new Date();
    const hours = String(date.getHours()).padStart(2, '0');
    const minutes = String(date.getMinutes()).padStart(2, '0');
    const seconds = String(date.getSeconds()).padStart(2, '0');
    const day = String(date.getDate()).padStart(2, '0');
    const month = String(date.getMonth() + 1).padStart(2, '0');
    const year = date.getFullYear();

    const formattedTime = `${year}-${month}-${day}T${hours}:${minutes}:${seconds}`;
    fetch(`/option?parametre=3&time=${encodeURIComponent(formattedTime)}`)
      .then(response => response.json())
      .then(data => {
        console.log(data);
      })
      .catch(error => {
        console.error("Erreur lors de la mise à jour de l'heure:", error);
      });
  });
// Gestion du choix de la couleur
  const inputOn = document.getElementById('inputOn');
  const sevenSegmentDisplay = document.querySelector('.seven-segment-display');

  // Clic sur l'afficheur pour ouvrir le sélecteur de couleur
  sevenSegmentDisplay.addEventListener('click', () => inputOn.click());
  
  // Mise à jour en temps réel de la couleur de tous les éléments
  inputOn.addEventListener('input', () => { 
    const elements = document.querySelectorAll('#hour1, #hour2, #separator, #min1, #min2');
    elements.forEach(element => {
      element.style.color = inputOn.value;
    });
  });
  
  inputOn.addEventListener('change', () => { submitColors(); });

  function submitColors() {
    const colorOn = document.getElementById("inputOn").value.slice(1);
    fetch("/option?parametre=1&color=" + colorOn)
        .then(response => response.json())
        .then(data => {
          console.log(data);
        })
        .catch(error => {
          console.error("Erreur lors de la mise à jour des couleurs:", error);
        });
  }


// Gestion du choix de la luminosité
  const sens = document.getElementById("luminosite");
  const manualLuminosityControl = document.getElementById("manualLuminosityControl");
  const sensorLuminosityControl = document.getElementById("sensorLuminosityControl");
  const luminositeDetectionMin = document.getElementById("luminositeDetectionMin");
  const luminositeDetectionMax = document.getElementById("luminositeDetectionMax");
  const luminositeDetectionMinValue = document.getElementById("luminositeDetectionMinValue");
  const luminositeDetectionMaxValue = document.getElementById("luminositeDetectionMaxValue");
  const luminositeSensorValue = document.getElementById("luminositeSensorValue");
  const luminosityDetectionSelection = document.getElementById("luminosityDetectionSelection");
  const luminositySensorMarker = document.getElementById("luminositySensorMarker");
  let luminositySensorRefreshTimer = null;
  let debounceTimer;
  let initialValue = sens.value; // valeur initiale
  sens.addEventListener("input", () => {
    clearTimeout(debounceTimer);
    debounceTimer = setTimeout(() => {
      const newValue = sens.value;
      console.log("Envoi au serveur :", newValue);

      fetch("/option?parametre=2&luminosite=" + newValue)
        .then(response => response.json())
        .then(data => {
          if (data.status !== "success") {
            sens.value = initialValue; // revert si pas succès
          } else {
            initialValue = newValue; // mise à jour de la valeur initiale
            showSavedFeedback(sens);
          }
        })
        .catch(error => {
          sens.value = initialValue; // revert en cas d'erreur réseau
        });
    }, 500);
  });

  function refreshLuminosityModeControls() {
    const isAuto = document.getElementById("toggleSwitch").checked;
    const hasSensorControl = sensorLuminosityControl && sensorLuminosityControl.dataset.enabled === "1";
    manualLuminosityControl.style.display = isAuto ? "none" : "flex";
    if (sensorLuminosityControl) {
      sensorLuminosityControl.style.display = (isAuto && hasSensorControl) ? "flex" : "none";
    }
    updateLuminositySensorRefresh();
  }

  if (sensorLuminosityControl) {
    sensorLuminosityControl.dataset.enabled = sensorLuminosityControl.style.display !== "none" ? "1" : "0";
  }

  function updateDualRangeVisuals() {
    const minLimit = parseInt(luminositeDetectionMin.min, 10);
    const maxLimit = parseInt(luminositeDetectionMax.max, 10);
    const range = maxLimit - minLimit;
    const minPercent = ((parseInt(luminositeDetectionMin.value, 10) - minLimit) / range) * 100;
    const maxPercent = ((parseInt(luminositeDetectionMax.value, 10) - minLimit) / range) * 100;

    luminosityDetectionSelection.style.left = `${minPercent}%`;
    luminosityDetectionSelection.style.right = `${100 - maxPercent}%`;
  }

  function clampLuminosityDetectionValues(changedInput) {
    let minValue = parseInt(luminositeDetectionMin.value, 10);
    let maxValue = parseInt(luminositeDetectionMax.value, 10);

    if (changedInput === luminositeDetectionMin && minValue >= maxValue) {
      minValue = maxValue - 1;
      luminositeDetectionMin.value = minValue;
    }
    if (changedInput === luminositeDetectionMax && maxValue <= minValue) {
      maxValue = minValue + 1;
      luminositeDetectionMax.value = maxValue;
    }

    luminositeDetectionMinValue.textContent = luminositeDetectionMin.value;
    luminositeDetectionMaxValue.textContent = luminositeDetectionMax.value;
    updateDualRangeVisuals();
  }

  function submitLuminosityDetection() {
    clearTimeout(debounceTimer);
    debounceTimer = setTimeout(() => {
      const minValue = luminositeDetectionMin.value;
      const maxValue = luminositeDetectionMax.value;
      fetch(`/option?parametre=7&min=${minValue}&max=${maxValue}`)
        .then(response => response.json())
        .then(data => {
          if (data.status !== "success") {
            console.log("Erreur lors de la mise a jour des seuils de luminosite");
          } else {
            showSavedFeedback(document.getElementById("luminosityDetectionRange"));
          }
        })
        .catch(() => {
          console.log("Erreur reseau lors de la mise a jour des seuils de luminosite");
        });
    }, 500);
  }

  if (luminositeDetectionMin && luminositeDetectionMax) {
    [luminositeDetectionMin, luminositeDetectionMax].forEach(input => {
      input.addEventListener("input", () => {
        clampLuminosityDetectionValues(input);
        submitLuminosityDetection();
      });
    });
    clampLuminosityDetectionValues(null);
  }

  function updateLuminositySensorMarker(value) {
    const minLimit = parseInt(luminositeDetectionMin.min, 10);
    const maxLimit = parseInt(luminositeDetectionMax.max, 10);
    const boundedValue = Math.max(minLimit, Math.min(maxLimit, value));
    const percent = ((boundedValue - minLimit) / (maxLimit - minLimit)) * 100;

    luminositeSensorValue.textContent = value;
    luminositySensorMarker.style.left = `${percent}%`;
    luminositySensorMarker.classList.add("visible");
  }

  function refreshLuminositySensorValue() {
    if (!sensorLuminosityControl || sensorLuminosityControl.style.display === "none") return;

    fetch("/luminosity_sensor")
      .then(response => response.json())
      .then(data => {
        if (data.status === "success") {
          updateLuminositySensorMarker(data.value);
        } else {
          luminositeSensorValue.textContent = "--";
          luminositySensorMarker.classList.remove("visible");
        }
      })
      .catch(() => {
        luminositeSensorValue.textContent = "--";
        luminositySensorMarker.classList.remove("visible");
      });
  }

  function updateLuminositySensorRefresh() {
    const shouldRefresh = sensorLuminosityControl && sensorLuminosityControl.style.display !== "none";

    if (shouldRefresh && !luminositySensorRefreshTimer) {
      refreshLuminositySensorValue();
      luminositySensorRefreshTimer = setInterval(refreshLuminositySensorValue, 2000);
    } else if (!shouldRefresh && luminositySensorRefreshTimer) {
      clearInterval(luminositySensorRefreshTimer);
      luminositySensorRefreshTimer = null;
    }
  }

// Choix de la gestion de la luminosité auto ou manuelle
let toggleSwitch_initialValue = document.getElementById("toggleSwitch").checked;
function Changebouton() {
  const lumauto = document.getElementById("toggleSwitch").checked ? 1 : 0;
  fetch("/option?parametre=4&lumauto="+ lumauto)
    .then(response => response.json())
    .then(data => {
        if(data.status !== "success") {
          setTimeout(() => { document.getElementById("toggleSwitch").checked = toggleSwitch_initialValue; }, 100);
        } else {
          toggleSwitch_initialValue = lumauto;
          showSavedFeedback(document.getElementById("toggleSwitch"));
          refreshLuminosityModeControls();
        }
    })
    .catch(error => {
        setTimeout(() => { document.getElementById("toggleSwitch").checked = toggleSwitch_initialValue; }, 100);
    });
}
refreshLuminosityModeControls();

let heureEteAuto_initialValue = document.getElementById("heureEteAutoSwitch").checked;
function ChangeHeureEteAuto() {
  const heureeteauto = document.getElementById("heureEteAutoSwitch").checked ? 1 : 0;
  fetch("/option?parametre=5&heureeteauto="+ heureeteauto)
    .then(response => response.json())
    .then(data => {
        if(data.status !== "success") {
          setTimeout(() => { document.getElementById("heureEteAutoSwitch").checked = heureEteAuto_initialValue; }, 100);
        } else {
          heureEteAuto_initialValue = document.getElementById("heureEteAutoSwitch").checked;
          showSavedFeedback(document.getElementById("heureEteAutoSwitch"));
        }
    })
    .catch(error => {
        setTimeout(() => { document.getElementById("heureEteAutoSwitch").checked = heureEteAuto_initialValue; }, 100);
    });
}

let affichageInverse_initialValue = document.getElementById("affichageInverseSwitch").checked;
function ChangeAffichageInverse() {
  const affichageinverse = document.getElementById("affichageInverseSwitch").checked ? 1 : 0;
  fetch("/option?parametre=6&affichageinverse="+ affichageinverse)
    .then(response => response.json())
    .then(data => {
        if(data.status !== "success") {
          setTimeout(() => { document.getElementById("affichageInverseSwitch").checked = affichageInverse_initialValue; }, 100);
        } else {
          affichageInverse_initialValue = document.getElementById("affichageInverseSwitch").checked;
          showSavedFeedback(document.getElementById("affichageInverseSwitch"));
        }
    })
    .catch(error => {
        setTimeout(() => { document.getElementById("affichageInverseSwitch").checked = affichageInverse_initialValue; }, 100);
    });
}


</script> <!-- Sera remplacé automatique par la page script.js de ce même répertoire -->
</body>
</html>

)rawliteral";

const char SiteWeb_GestionWifi[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>%DISPO_NAME%</title>
    <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
    <link href="https://fonts.googleapis.com/css2?family=Orbitron:wght@400;700&display=swap" rel="stylesheet">
    <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
    <style>
* {margin: 0; padding: 0; box-sizing: border-box;}

body {
  display: flex;
  height: 100vh;
  font-family: sans-serif;
  background: #f3f3f3;
}

/* --- MENU LATÉRAL --- */
.sidebar {
  background: #222;
  color: #fff;
  width: 250px;
  transition: width 0.3s;
  display: flex;
  flex-direction: column;
  align-items: stretch; /* prend toute la largeur */
  height: 100%;
  overflow: hidden;
  justify-content: flex-start; /* tout en haut */
  padding-bottom: 20px; /* pour laisser un peu d'espace pour le bas */
}

.menu-top {
  display: flex;
  flex-direction: column;
  width: 100%; /* prend toute la largeur */
  margin-top: 0; /* en haut */
}

.menu-bottom-container {
  display: flex;
  flex-direction: column;
  gap: 10px;
  margin-top: auto; /* pousse tout vers le bas */
}


.sidebar.collapsed {
  width: 70px;
}

.logo {
  font-size: 1.8em;
  margin: 20px 0;
  cursor: pointer;
  user-select: none;
  transition: transform 0.3s;
  transform-origin: center;
  display: flex;
  justify-content: center;
  height: 50px; /* fixe pour éviter le déplacement */
}
.logo:hover { transform: scale(1.1); }

.menu-item {
  width: 100%;
  padding: 15px 20px;
  display: flex;
  align-items: center;
  gap: 10px;
  cursor: pointer;
  transition: background 0.2s;
}

.menu-item-bottom {
  width: 100%;
  padding: 2px 20px;
  display: flex;
  align-items: center;
  gap: 10px;
  cursor: pointer;
  transition: background 0.2s;
}
.menu-item:hover,
.menu-item-bottom:hover {
    background: #333;
}


.menu-item a,
.menu-item-bottom a {
  display: flex;
  align-items: center;
  gap: 10px;
  width: 100%;
  color: inherit;
  text-decoration: none;
}

.menu-item a:hover,
.menu-item-bottom a:hover {
    background: #333;
}

.menu-item-bottom {
  margin-top: auto;
}

.menu-item i, .menu-item-bottom i { font-size: 1.2em; }
.menu-item span, .menu-item-bottom span { transition: opacity 0.3s; }

/* cache le texte des menus normaux et bas quand menu rétracté */
.sidebar.collapsed .menu-item span:not(.material-icons),
.sidebar.collapsed .menu-item-bottom span:not(.material-icons) {
  opacity: 0;
  pointer-events: none;
}

/* --- CONTENU PRINCIPAL --- */
.main {
    flex: 1;
    padding: 30px;
    overflow-y: auto;
    transition: margin-left 0.3s;
}

.main h1 {
  text-align: center;
  margin-bottom: 20px;
}

/* --- RESPONSIVE --- */
@media (max-width: 768px) {
    .sidebar {
        width: 70px; /* étroit par défaut */
    }

    .sidebar.expanded {
        width: 250px; /* s’étend quand on clique sur le logo */
    }

    .sidebar .menu-item span:not(.material-icons),
    .sidebar .menu-item-bottom span:not(.material-icons) {
        opacity: 0;
        pointer-events: none;
    }

    .sidebar.expanded .menu-item span:not(.material-icons),
    .sidebar.expanded .menu-item-bottom span:not(.material-icons) {
        opacity: 1;
        pointer-events: auto;
    }
}


.icon-on { color: gold; }
.icon-off { color: gray; }

.icon-small { font-size: 16px; }
.icon-medium { font-size: 24px; }
.icon-large { font-size: 48px; }















.wifi-add-form {
    border: 1px solid #ccc;
    border-radius: 10px;
    padding: 15px;
    background-color: #f9f9f9;
    display: flex;
    flex-direction: column;
    gap: 10px;
    width: 100%;
    max-width: 400px; /* limite largeur sur tablette/desktop */
    margin: 0 auto;   /* centre sur grand écran */
}

.wifi-add-form h2 {
    margin: 0;
    font-size: 1.2em;
    text-align: center;
}

.wifi-add-form input {
    padding: 10px;
    font-size: 1em;
    border-radius: 5px;
    border: 1px solid #ccc;
    width: 100%;
    box-sizing: border-box;
}

.wifi-add-form button {
    padding: 10px;
    font-size: 1em;
    border-radius: 5px;
    border: none;
    background-color: #222;
    color: white;
    cursor: pointer;
}

.wifi-add-form button:hover {
    background-color: #444;
}

.password-container {
  position: relative;
  display: flex;
  align-items: center;
}

.password-container input {
  flex: 1;
  padding-right: 35px;
}

.toggle-mdp {
  position: absolute;
  right: 10px;
  cursor: pointer;
  color: #666;
  user-select: none;
  font-size: 20px;
}

.toggle-mdp:hover {
  color: #000;
}

/* Mobile portrait */
@media (max-width: 480px) {
    .wifi-add-form {
        padding: 10px;
        gap: 8px;
    }

    .wifi-add-form input,
    .wifi-add-form button {
        font-size: 1em;
        padding: 8px;
    }
}

















.wifi-list-section {
  margin-top: 25px;
  border: 1px solid #ccc;
  border-radius: 10px;
  background-color: #f9f9f9;
  padding: 15px;
  max-width: 500px;
  margin-left: auto;
  margin-right: auto;
}

.wifi-list-section h2 {
    margin: 0;
    font-size: 1.2em;
    text-align: center;
}

.wifi-list {
  display: flex;
  flex-direction: column;
  gap: 10px;
}

.wifi-card {
  border: 1px solid #ddd;
  border-radius: 8px;
  padding: 10px;
  background: white;
  display: flex;
  flex-direction: column;
  gap: 5px;
}

.wifi-card-header {
  font-weight: bold;
  color: #222;
}

.wifi-card-info {
  font-size: 0.9em;
  color: #555;
}

.wifi-card-buttons {
  display: flex;
  justify-content: space-between;
  margin-top: 8px;
}

.wifi-card-buttons button {
  flex: 1;
  margin: 0 3px;
  padding: 6px;
  border: none;
  border-radius: 5px;
  cursor: pointer;
  font-size: 0.9em;
}

button.connect { background-color: #222; color: #fff; }
button.modify { background-color: #222; color: #fff; }
button.delete { background-color: #222; color: #fff; }

button.connect:hover { background-color: #444; }
button.modify:hover { background-color: #444; }
button.delete:hover { background-color: #444; }

/* Harmonise la largeur avec le formulaire d’ajout */
.wifi-list-section {
  width: 100%;
  max-width: 400px; /* même largeur que le formulaire */
}

/* Ajoute un léger effet au survol pour les cartes */
.wifi-card:hover {
  background-color: #f3f3f3;
  transition: background 0.2s;
}

.wifi-status-icon {
  float: right;
  font-size: 1.2em;
  vertical-align: middle;
}

.wifi-status-icon.connected { color: rgb(0, 255, 0); }
.wifi-status-icon.disconnected { color: rgb(235, 235, 235); }
.wifi-status-icon.error { color: rgb(255, 0, 0); }

/* Améliore la lisibilité sur mobile */
@media (max-width: 480px) {
  .wifi-card-buttons {
    flex-direction: column;
    gap: 5px;
  }

  .wifi-card-buttons button {
    margin: 0;
    width: 100%;
  }
}
</style> <!-- Sera remplacé automatique par la page style.css de ce même répertoire -->
</head>
<body>
    <!-- Menu lateral -->
    <div class="sidebar" id="sidebar">
        <div class="logo" id="logo"><span class="material-icons">apps</span></div>

        <!-- menu du haut -->
        <div class="menu-top">
            <div class="menu-item"><a href="/accueil"><span class="material-icons">home</span><span>Accueil</span></a></div>
            <div class="menu-item"><a href="/wifi"><span class="material-icons">wifi</span><span>Connexion</span></a></div>
            <div class="menu-item"><a href="/informations"><span class="material-icons">info</span><span>Informations</span></a></div>
        </div>

        <!-- menu du bas -->
        <div class="menu-bottom-container">
            <div class="menu-item-bottom" style="display:block;%DISPLAY_MENU_ADMIN%"><a href="/parametres.json"><span class="material-icons">data_object</span><span>Parametres.json</span></a></div>
            <div class="menu-item-bottom" style="display:block;%DISPLAY_MENU_ADMIN%"><a href="/wifi.json"><span class="material-icons">data_object</span><span>Wifi.json</span></a></div>
            <div class="menu-item-bottom" style="display:block;%DISPLAY_MENU_ADMIN%"><a href="/restart"><span class="material-icons">restart_alt</span><span>Redémarrer</span></a></div>
            <div class="menu-item-bottom" style="display:block;%DISPLAY_MENU_ADMIN%"><a href="/reset"><span class="material-icons">credit_card_off</span><span>Remise a zero</span></a></div>
        </div>
    </div>

    <div class="main">
        <h1>Paramètres Wi-Fi</h1>

        <!-- Formulaire pour ajouter un réseau -->
        <div class="wifi-add-form">
            <h2>Ajouter un réseau</h2>
            <input type="text" id="new-ssid" placeholder="SSID">
            <div class="password-container">
                <input type="password" id="new-mdp" placeholder="Mot de passe">
                <span class="toggle-mdp material-icons">visibility_off</span>
            </div>
            <button id="add-wifi-btn">Ajouter</button>
        </div>

        <!-- Table des réseaux enregistrés -->
        <div class="wifi-list-section">
            <h2>Réseaux enregistrés</h2>
            <div id="wifi-list" class="wifi-list">
                <!-- Les réseaux seront générés ici en JS -->
            </div>
        </div>
    </div>
    
    <script>
const sidebar = document.getElementById('sidebar');
const logo = document.getElementById('logo');

function initSidebar() {
  if (window.innerWidth <= 768) {
    sidebar.classList.remove('collapsed');
    sidebar.classList.remove('expanded'); // étroit par défaut sur petit écran
  } else {
    sidebar.classList.remove('expanded');
    sidebar.classList.remove('collapsed'); // étendu par défaut sur grand écran
  }
}

logo.addEventListener('click', () => {
  if (window.innerWidth <= 768) {
    sidebar.classList.toggle('expanded'); // mobile : élargir/réduire
  } else {
    sidebar.classList.toggle('collapsed'); // desktop : réduire/élargir
  }
});

window.addEventListener('resize', initSidebar);
window.addEventListener('load', initSidebar);



// Ajouter un reseaux un wifi
  const ssidInput = document.getElementById('new-ssid');
  const mdpInput = document.getElementById('new-mdp');
  const addButton = document.getElementById('add-wifi-btn');
  const toggleBtn = document.querySelector('.toggle-mdp');

  toggleBtn.addEventListener('click', () => {
    const isPassword = mdpInput.type === 'password';
    mdpInput.type = isPassword ? 'text' : 'password';
    toggleBtn.textContent = isPassword ? 'visibility' : 'visibility_off';
  });

  addButton.addEventListener('click', () => {
      const newSSID = ssidInput.value.trim();
      const newMDP = mdpInput.value.trim();

      if (newSSID && newMDP) {
          // Envoyer les données au serveur ESP32
          fetch(`/parametres?ssid=${encodeURIComponent(newSSID)}&modifymdp=${encodeURIComponent(newMDP)}`)
              .then(response => response.text())
              .then(data => {
                  console.log('Wifi ajouté :', newSSID);
                  ssidInput.value = '';
                  mdpInput.value = '';
                  loadWifiNetworks(); // recharge la liste après ajout
                  setTimeout(() => {
                      loadWifiNetworks();
                  }, 2000); // attend 2000 ms = 2 secondes
              })
              .catch(error => console.error('Erreur lors de l\'envoi de la commande de modification:', error));
      } else {
          alert('Veuillez remplir les deux champs (SSID et mot de passe).');
      }
  });


// Affichage des resaux wifi enregistrés
  let wifiNetworks = [];
  const ssidConnected = "%SSID_CONNECTED%";
  const ssidRSSI = "%SSID_RSSI%";

  window.onload = function() {
      loadWifiNetworks();
  };

  function loadWifiNetworks() {
      fetch('wifi.json')
      .then(response => response.json())
      .then(data => {
          wifiNetworks = data.wifi_networks;
          displayWifiList();
      });
  }

  function displayWifiList() {
    const section = document.querySelector('.wifi-list-section');
    const wifiListContainer = document.querySelector('.wifi-list');

    wifiListContainer.innerHTML = '';

    const validNetworks = wifiNetworks.filter(net => net.ssid && net.ssid !== "0");

    if (validNetworks.length === 0) {
      section.style.display = 'none';
      return;
    }

    section.style.display = 'block';

    validNetworks.forEach((network, index) => {
      const card = document.createElement('div');
      card.classList.add('wifi-card');

      // Vérifie si ce réseau est celui connecté
      const isConnected = (network.ssid === ssidConnected);
      const IPDisplay = network.IP_local ? network.IP_local + (network.port && network.port !== "80" ? `:${network.port}` : '') : '';
      const DNSDisplay = network.DNS ? network.DNS + (network.port && network.port !== "80" ? `:${network.port}` : '') : '';
      const mDNSDisplay = network.mDNS ? network.mDNS + (network.port && network.port !== "80" ? `:${network.port}` : '') : '';
      
      let logo = "wifi";
      if(ssidRSSI <= -90) { logo = "wifi_1_bar"; }
      else if(ssidRSSI <= -60) { logo = "wifi_2_bar"; }
      else { logo = "wifi"; }

      card.innerHTML = `
        <div class="wifi-card-header">
          ${network.ssid}
          <span class="material-icons wifi-status-icon ${isConnected ? 'connected' : 'disconnected'}">
            ${isConnected ? logo : 'wifi'}
          </span>
        </div>
        <div class="wifi-card-info">
          Nom d'hôte : ${network.hostname || ''}<br>
          Adresse MAC : ${network.MAC_ADRESS || ''}<br>
          Adresse IP : <a href="http://${IPDisplay}" style="text-decoration:none;">${network.IP_local || ''}</a><br>
          DNS (box) : <a href="http://${DNSDisplay}" style="text-decoration:none;">${network.DNS || ''}</a><br>
          mDNS (esp) : <a href="http://${mDNSDisplay}" style="text-decoration:none;">${network.mDNS || ''}</a><br>
          Port : ${network.port || ''}
        </div>
        <div class="wifi-card-buttons">
          <button class="connect">Connexion</button>
          <button class="modify">Modifier</button>
          <button class="delete">Supprimer</button>
        </div>
      `;

      card.querySelector('.connect').onclick = () => ConnectNetwork(index);
      card.querySelector('.modify').onclick = () => modifyPassword(index);
      card.querySelector('.delete').onclick = () => deleteNetwork(index);

      wifiListContainer.appendChild(card);
    });
  }

  function modifyPassword(index) {
    const newPassword = prompt("Entrez le nouveau mot de passe pour le réseau " + wifiNetworks[index].ssid);
    if (newPassword) {
        // Mettre à jour le mot de passe dans le tableau
        fetch(`/parametres?ssid=${wifiNetworks[index].ssid}&modifymdp=${newPassword}`) // Envoie du reseau via une requête HTTP GET
          .then(response => response.text())
          .then(data => console.log('Wifi modifié :', wifiNetworks[index].ssid))
          .catch(error => console.error('Erreur lors de l\'envoi de la commande de modification:', error));

        loadWifiNetworks();
    }
  }
  function deleteNetwork(index) {
    if (confirm("Êtes-vous sûr de vouloir supprimer ce réseau?")) {
        fetch(`/parametres?ssid=${wifiNetworks[index].ssid}&delete=1`) // Envoie la luminosité via une requête HTTP GET
          .then(response => response.text())
          .then(data => console.log('Wifi supprimé :', wifiNetworks[index].ssid))
          .catch(error => console.error('Erreur lors de l\'envoi de la commande de suppression:', error));

        loadWifiNetworks();
    }
  }
  function ConnectNetwork(index) {
      location.reload();
  }
</script> <!-- Sera remplacé automatique par la page script.js de ce même répertoire -->
</body>
</html>
)rawliteral";

const char SiteWeb_Informations[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>%DISPO_NAME%</title>
    <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
    <link href="https://fonts.googleapis.com/css2?family=Orbitron:wght@400;700&display=swap" rel="stylesheet">
    <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
    <style>
* {margin: 0; padding: 0; box-sizing: border-box;}

body {
  display: flex;
  height: 100vh;
  font-family: sans-serif;
  background: #f3f3f3;
}

/* --- MENU LATÉRAL --- */
.sidebar {
  background: #222;
  color: #fff;
  width: 250px;
  transition: width 0.3s;
  display: flex;
  flex-direction: column;
  align-items: stretch; /* prend toute la largeur */
  height: 100%;
  overflow: hidden;
  justify-content: flex-start; /* tout en haut */
  padding-bottom: 20px; /* pour laisser un peu d'espace pour le bas */
}

.menu-top {
  display: flex;
  flex-direction: column;
  width: 100%; /* prend toute la largeur */
  margin-top: 0; /* en haut */
}

.menu-bottom-container {
  display: flex;
  flex-direction: column;
  gap: 10px;
  margin-top: auto; /* pousse tout vers le bas */
}


.sidebar.collapsed {
  width: 70px;
}

.logo {
  font-size: 1.8em;
  margin: 20px 0;
  cursor: pointer;
  user-select: none;
  transition: transform 0.3s;
  transform-origin: center;
  display: flex;
  justify-content: center;
  height: 50px; /* fixe pour éviter le déplacement */
}
.logo:hover { transform: scale(1.1); }

.menu-item {
  width: 100%;
  padding: 15px 20px;
  display: flex;
  align-items: center;
  gap: 10px;
  cursor: pointer;
  transition: background 0.2s;
}

.menu-item-bottom {
  width: 100%;
  padding: 2px 20px;
  display: flex;
  align-items: center;
  gap: 10px;
  cursor: pointer;
  transition: background 0.2s;
}
.menu-item:hover,
.menu-item-bottom:hover {
    background: #333;
}


.menu-item a,
.menu-item-bottom a {
  display: flex;
  align-items: center;
  gap: 10px;
  width: 100%;
  color: inherit;
  text-decoration: none;
}

.menu-item a:hover,
.menu-item-bottom a:hover {
    background: #333;
}

.menu-item-bottom {
  margin-top: auto;
}

.menu-item i, .menu-item-bottom i { font-size: 1.2em; }
.menu-item span, .menu-item-bottom span { transition: opacity 0.3s; }

/* cache le texte des menus normaux et bas quand menu rétracté */
.sidebar.collapsed .menu-item span:not(.material-icons),
.sidebar.collapsed .menu-item-bottom span:not(.material-icons) {
  opacity: 0;
  pointer-events: none;
}

/* --- CONTENU PRINCIPAL --- */
.main {
    flex: 1;
    padding: 30px;
    overflow-y: auto;
    transition: margin-left 0.3s;
}

.main h1 {
  text-align: center;
  margin-bottom: 20px;
}

/* --- RESPONSIVE --- */
@media (max-width: 768px) {
    .sidebar {
        width: 70px; /* étroit par défaut */
    }

    .sidebar.expanded {
        width: 250px; /* s’étend quand on clique sur le logo */
    }

    .sidebar .menu-item span:not(.material-icons),
    .sidebar .menu-item-bottom span:not(.material-icons) {
        opacity: 0;
        pointer-events: none;
    }

    .sidebar.expanded .menu-item span:not(.material-icons),
    .sidebar.expanded .menu-item-bottom span:not(.material-icons) {
        opacity: 1;
        pointer-events: auto;
    }
}














.section {
  border: 1px solid #ccc;
  border-radius: 10px;
  padding: 15px;
  background-color: #f9f9f9;
  display: flex;
  flex-direction: column;
  gap: 10px;
  width: 100%;
  max-width: 400px; /* limite largeur sur tablette/desktop */
  margin: 0 auto;   /* centre sur grand écran */
  margin-bottom: 10px;
  position: relative;
}
.section h2 {
    margin: 0;
    font-size: 1.2em;
    text-align: center;
}
.user-select-none {
  user-select: none;
}

.icon-small { font-size: 13px; }
.icon-medium { font-size: 24px; }
.icon-large { font-size: 48px; }
.bouton { cursor:pointer; }

.top-right-section {
  position: absolute;
  top: 50%;
  transform: translateY(-50%);
  right: 10px;
  color: #858585;
}

.loading-gradient {
  background: linear-gradient(to top, #4caf50 0%, transparent 0%);
  -webkit-background-clip: text;
  -webkit-text-fill-color: transparent;
  transition: background 0.1s linear;
}


.line {
  display: flex;
  justify-content: space-between;
  font-family: monospace;
}

.label {
  flex: 0 0 auto;
}

.dots {
  flex: 1;
  border-bottom: 1px dotted #000;
  margin: 0 5px;
}

.value {
  flex: 0 0 auto;
}

@keyframes blinkRed {
  0%, 100% { color: inherit; }
  50% { color: red; }
}

.blink-red {
  animation: blinkRed 0.2s 5;
}
</style> <!-- Sera remplacé automatique par la page style.css de ce même répertoire -->
</head>
<body>
    <!-- Menu lateral -->
    <div class="sidebar" id="sidebar">
        <div class="logo" id="logo"><span class="material-icons">apps</span></div>

        <!-- menu du haut -->
        <div class="menu-top">
            <div class="menu-item"><a href="/accueil"><span class="material-icons">home</span><span>Accueil</span></a></div>
            <div class="menu-item"><a href="/wifi"><span class="material-icons">wifi</span><span>Connexion</span></a></div>
            <div class="menu-item"><a href="/informations"><span class="material-icons">info</span><span>Informations</span></a></div>
        </div>

        <!-- menu du bas -->
        <div class="menu-bottom-container">
            <div class="menu-item-bottom" style="display:block;%DISPLAY_MENU_ADMIN%"><a href="/parametres.json"><span class="material-icons">data_object</span><span>Parametres.json</span></a></div>
            <div class="menu-item-bottom" style="display:block;%DISPLAY_MENU_ADMIN%"><a href="/wifi.json"><span class="material-icons">data_object</span><span>Wifi.json</span></a></div>
            <div class="menu-item-bottom" style="display:block;%DISPLAY_MENU_ADMIN%"><a href="/restart"><span class="material-icons">restart_alt</span><span>Redémarrer</span></a></div>
            <div class="menu-item-bottom" style="display:block;%DISPLAY_MENU_ADMIN%"><a href="/reset"><span class="material-icons">credit_card_off</span><span>Remise a zero</span></a></div>
        </div>
    </div>

    <div class="main">
        <h1>Informations</h1>

        <div class="section">
            <h2>Version du Firmware</h2>
            <center><span id="version_num" class="user-select-none">%VERSION_FIRMWARE%</span> <span id="bouton_update" style="display:none;" class="material-icons icon-large top-right-section bouton">security_update</span></center>
        </div>

        <div class="section" style="%DISPLAY_MENU_ADMIN%">
            <h2>Informations Mémoires</h2>
            %MEMORY_SUMMARY%
        </div>

    </div>
    
    <script>
window.onload = function () {
  checkNewFirmware();
  
  // Vérifier les mises à jour toutes les 5 minutes
  setInterval(checkNewFirmware, 5 * 60 * 1000);
};

const sidebar = document.getElementById('sidebar');
const logo = document.getElementById('logo');

function initSidebar() {
  if (window.innerWidth <= 768) {
    sidebar.classList.remove('collapsed');
    sidebar.classList.remove('expanded'); // étroit par défaut sur petit écran
  } else {
    sidebar.classList.remove('expanded');
    sidebar.classList.remove('collapsed'); // étendu par défaut sur grand écran
  }
}

logo.addEventListener('click', () => {
  if (window.innerWidth <= 768) {
    sidebar.classList.toggle('expanded'); // mobile : élargir/réduire
  } else {
    sidebar.classList.toggle('collapsed'); // desktop : réduire/élargir
  }
});

window.addEventListener('resize', initSidebar);
window.addEventListener('load', initSidebar);


// Permet de passer en mode administrateur et de changer les paramètres
  document.addEventListener("DOMContentLoaded", () => {
    const textElement = document.getElementById("version_num");

    let clickCount = 0;
    let lastClickTime = 0;
    const elements = [
      {el: textElement, clicks: 5, url: "/admin_site?admin=1"}
    ];

    elements.forEach(item => {
      if (!item.el) return; // sécurité si un élément n'existe pas
      item.el.addEventListener("click", () => {
        const now = Date.now();
        if (now - lastClickTime > 400) clickCount = 0;
        clickCount++;
        lastClickTime = now;

        if (clickCount >= item.clicks) {
          clickCount = 0;
          fetch(item.url)
            .then(res => res.json())
            .then(data => {
              if (data.status === "success") {
                setTimeout(() => location.reload(), 2000);
              } else {
                console.log("Action interdite ou non autorisée");
                item.el.classList.add("blink-red");
                setTimeout(() => item.el.classList.remove("blink-red"), 1800); // 3 x 0.6s
              }
            })
            .catch(() => console.log("Pas de reponse du serveur"));
        }
      });
    });
  });


// Permet de lancer la mise a jour du firmware
  const boutonUpdate = document.getElementById("bouton_update");
  let loadingInterval = null;

    
function checkNewFirmware() {
  const boutonUpdate = document.getElementById("bouton_update");
  const currentVersion = document.getElementById("version_num").textContent.trim();

  console.log("🔍 Vérification des mises à jour en cours...");

  // Utilise le nouveau endpoint local qui vérifie GitHub
  fetch("/check_updates")
      .then(resp => {
        console.log(`📡 Réponse HTTP: ${resp.status} ${resp.statusText}`);
        if (!resp.ok) {
          throw new Error(`HTTP ${resp.status}: ${resp.statusText}`);
        }
        return resp.json();
      })
      .then(data => {
        console.log("✅ Vérification des mises à jour:", data);
        
        if (data.status === "success" && data.update_available) {
          // Une mise à jour est disponible
          boutonUpdate.dataset.file = data.download_url;
          boutonUpdate.dataset.version = data.latest_version;
          boutonUpdate.style.display = "inline-block";
          
          // Met à jour le texte du bouton avec la nouvelle version
          const icon = boutonUpdate.querySelector('.material-icons');
          if (icon) {
            boutonUpdate.title = `Mise à jour vers v${data.latest_version} disponible (actuelle: v${data.current_version})`;
          }
          
          console.log(`🆕 Nouvelle version disponible: ${data.latest_version} (actuelle: ${data.current_version})`);
        } else if (data.status === "success") {
          // Pas de mise à jour disponible
          boutonUpdate.style.display = "none";
          console.log(`✅ Firmware à jour (version ${data.current_version})`);
        } else {
          // Erreur dans la réponse
          console.log("❌ Erreur serveur:", data.message || "Réponse inattendue");
          boutonUpdate.style.display = "none";
        }
      })
      .catch(error => {
        console.log("❌ Erreur lors de la vérification des mises à jour:", error.message);
        boutonUpdate.style.display = "none";
        
        // En cas d'erreur réseau, on peut essayer de fallback sur une vérification locale
        if (error.message.includes('Failed to fetch')) {
          console.log("💡 Vérification réseau échouée - mode hors ligne");
        } else if (error.message.includes('500')) {
          console.log("🔧 Erreur serveur - vérifiez la connexion WiFi de l'ESP32");
        }
      });
}


  boutonUpdate.addEventListener("click", () => {
    const fileName = boutonUpdate.dataset.file; // le .bin détecté
    const version = boutonUpdate.dataset.version; // la version détectée
    
    if(!confirm(`Confirmer la mise à jour vers la version ${version} ?`)) return;

    boutonUpdate.style.pointerEvents = "none"; // bloque le bouton
    animateIcon(boutonUpdate);

    fetch(`/update_firmware?file=${encodeURIComponent(fileName)}`)
      .then(response => response.json())
      .then(data => {
        console.log("Mise à jour du firmware lancée depuis GitHub");
        // après envoi OTA, on commence à checker si le serveur répond
        setTimeout(() => checkServerAndRefresh(window.location.origin, boutonUpdate), 30000); 
        // 30s de délai pour laisser l'OTA démarrer
      })
      .catch(error => {
        console.log("Erreur lors de la mise à jour du firmware:", error);
        boutonUpdate.style.pointerEvents = "auto";
        resetIcon(boutonUpdate);
      });
  });

  function checkServerAndRefresh(url, icon) {
    console.log("verrification si le serveur est de nouveau joignable");
    fetch(url) // méthode GET par défaut
      .then(resp => {
        if(resp.ok){
          console.log("c'est tout bon, restart de la page");
          resetIcon(icon);
          location.reload(); // page rafraîchie
        } else {
          console.log("pas joignable, on reanime l'icone");
          animateIcon(icon);
          setTimeout(() => checkServerAndRefresh(url, icon), 2000);
        }
      })
      .catch(() => {
        console.log("pas joignable, on reanime l'icone");
        animateIcon(icon);
        setTimeout(() => checkServerAndRefresh(url, icon), 2000);
      });
  }


  function animateIcon(icon) {
    let progress = 0;
    const steps = 100;           // nombre d'étapes
    const duration = 30000;      // durée totale en ms
    const interval = duration / steps; // temps entre chaque étape

    loadingInterval = setInterval(() => {
      progress += 1; // incrémente de 1% à chaque étape
      if (progress > 100) progress = 100;
      icon.style.background = `linear-gradient(to top, #4caf50 ${progress}%, transparent ${progress}%)`;
    }, interval);
  }

  function resetIcon(icon) {
    clearInterval(loadingInterval);
    icon.style.background = "";
  }
</script> <!-- Sera remplacé automatique par la page script.js de ce même répertoire -->
</body>
</html>
)rawliteral";

