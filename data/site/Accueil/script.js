window.onload = function() {
  RefreshInfo();
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
        if(%MENU_ADMIN%) { console.log(JSON.stringify(data)); }
      })
      .catch(() => {
        console.log("impossible de contacter le serveur");
      });
  };

  // Exécuter immédiatement
  fetchData();
}


