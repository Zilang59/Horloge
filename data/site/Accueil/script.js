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

