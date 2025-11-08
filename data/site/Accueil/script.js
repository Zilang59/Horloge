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
          }
        })
        .catch(error => {
          sens.value = initialValue; // revert en cas d'erreur réseau
        });
    }, 500);
  });

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
        }
    })
    .catch(error => {
        setTimeout(() => { document.getElementById("toggleSwitch").checked = toggleSwitch_initialValue; }, 100);
    });
}

