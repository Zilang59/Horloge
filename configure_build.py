#!/usr/bin/env python3
"""
Script de configuration automatique avant la compilation
Lit Dispo_basename dans main.cpp et configure les include et platformio.ini en conséquence
Ce script s'exécute AVANT la compilation
"""

import re
import os
import sys
import time
from pathlib import Path

# Import pour PlatformIO - accessible quand le script est appelé par PlatformIO
try:
    Import("env")
    project_dir = env.get("PROJECT_DIR")
except:
    # Fallback si exécuté en standalone
    project_dir = os.getcwd()

def read_dispo_basename():
    """Lit la valeur de Dispo_basename depuis main.cpp"""
    main_cpp_path = os.path.join(project_dir, "src", "main.cpp")
    
    print(f"[configure_build] Lecture de {main_cpp_path}")
    
    try:
        with open(main_cpp_path, 'r', encoding='utf-8') as f:
            content = f.read()
            
        # Rechercher la ligne avec Dispo_basename
        match = re.search(r'String\s+Dispo_basename\s*=\s*"([^"]+)"', content)
        if match:
            basename = match.group(1).lower()
            print(f"[configure_build] Dispo_basename trouvé: {basename}")
            return basename
    except Exception as e:
        print(f"[configure_build] ERREUR lors de la lecture de main.cpp: {e}")
    
    print("[configure_build] AVERTISSEMENT: Impossible de lire Dispo_basename")
    return None

def update_main_cpp(dispo_basename):
    """Met à jour main.cpp selon la valeur de Dispo_basename"""
    main_cpp_path = os.path.join(project_dir, "src", "main.cpp")
    
    try:
        with open(main_cpp_path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
        
        is_horloge = "horloge" in dispo_basename and "mini" not in dispo_basename
        modified = False
        
        for i, line in enumerate(lines):
            # Chercher les lignes avec Horloge_Mini.h
            if 'Horloge_Mini.h' in line:
                if is_horloge:
                    # Doit être commentée pour Horloge_grande
                    if not line.strip().startswith('//'):
                        # Ajouter // seulement si pas déjà commentée
                        lines[i] = line.replace('#include <Horloge_Mini.h>', '// #include <Horloge_Mini.h>')
                        modified = True
                        print("[configure_build] Commentée: Horloge_Mini.h")
                else:
                    # Doit être décommentée pour Horloge_mini
                    if line.strip().startswith('//'):
                        # Enlever le // si c'est commenté
                        lines[i] = line.replace('// #include <Horloge_Mini.h>', '#include <Horloge_Mini.h>')
                        modified = True
                        print("[configure_build] Décommentée: Horloge_Mini.h")
            
            # Chercher les lignes avec Horloge_grande.h
            elif 'Horloge_grande.h' in line:
                if is_horloge:
                    # Doit être décommentée pour Horloge_grande
                    if line.strip().startswith('//'):
                        # Enlever le // si c'est commenté
                        lines[i] = line.replace('// #include <Horloge_grande.h>', '#include <Horloge_grande.h>')
                        modified = True
                        print("[configure_build] Décommentée: Horloge_grande.h")
                else:
                    # Doit être commentée pour Horloge_mini
                    if not line.strip().startswith('//'):
                        # Ajouter // seulement si pas déjà commentée
                        lines[i] = line.replace('#include <Horloge_grande.h>', '// #include <Horloge_grande.h>')
                        modified = True
                        print("[configure_build] Commentée: Horloge_grande.h")
        
        if modified:
            with open(main_cpp_path, 'w', encoding='utf-8') as f:
                f.writelines(lines)
            print("[configure_build] Configuration pour: Horloge_" + ("grande" if is_horloge else "mini"))
        else:
            print("[configure_build] main.cpp déjà correct, aucune modification")
            
    except Exception as e:
        print(f"[configure_build] ERREUR lors de la mise à jour de main.cpp: {e}")

def update_platformio_ini(dispo_basename):
    """Met à jour platformio.ini selon la valeur de Dispo_basename"""
    platformio_path = os.path.join(project_dir, "platformio.ini")
    
    try:
        with open(platformio_path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
        
        is_horloge = "horloge" in dispo_basename and "mini" not in dispo_basename
        modified = False
        
        for i, line in enumerate(lines):
            # Chercher la ligne avec esp32-s3-devkitm-1
            if line.startswith('board = esp32-s3-devkitm-1') or line.startswith('; board = esp32-s3-devkitm-1'):
                if is_horloge:
                    # Doit être commentée pour Horloge_grande
                    if not line.startswith(';'):
                        lines[i] = '; board = esp32-s3-devkitm-1\n'
                        modified = True
                        print("[configure_build] Commentée: board = esp32-s3-devkitm-1")
                else:
                    # Doit être décommentée pour Horloge_mini
                    if line.startswith(';'):
                        lines[i] = 'board = esp32-s3-devkitm-1\n'
                        modified = True
                        print("[configure_build] Décommentée: board = esp32-s3-devkitm-1")
            
            # Chercher la ligne avec esp32dev
            elif line.startswith('board = esp32dev') or line.startswith('; board = esp32dev'):
                if is_horloge:
                    # Doit être décommentée pour Horloge_grande
                    if line.startswith(';'):
                        lines[i] = 'board = esp32dev\n'
                        modified = True
                        print("[configure_build] Décommentée: board = esp32dev")
                else:
                    # Doit être commentée pour Horloge_mini
                    if not line.startswith(';'):
                        lines[i] = '; board = esp32dev\n'
                        modified = True
                        print("[configure_build] Commentée: board = esp32dev")
        
        if modified:
            with open(platformio_path, 'w', encoding='utf-8') as f:
                f.writelines(lines)
            print("[configure_build] platformio.ini mis à jour")
            print("[configure_build] ⏳ Pause de 2 secondes pour que PlatformIO relise la configuration...")
            time.sleep(2)
            print("[configure_build] ✅ Prêt à continuer")
        else:
            print("[configure_build] platformio.ini déjà correct, aucune modification")
            
    except Exception as e:
        print(f"[configure_build] ERREUR lors de la mise à jour de platformio.ini: {e}")

def main():
    """Fonction principale"""
    print("\n[configure_build] ========== DÉBUT CONFIGURATION BUILD ==========")
    dispo_basename = read_dispo_basename()
    
    if dispo_basename:
        update_main_cpp(dispo_basename)
        update_platformio_ini(dispo_basename)
        print("[configure_build] ========== CONFIGURATION TERMINÉE ==========\n")
    else:
        print("[configure_build] ========== ÉCHEC DE LA CONFIGURATION ==========\n")

# Exécution
main()
