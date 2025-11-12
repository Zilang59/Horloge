#!/usr/bin/env python3
"""
Script pour générer la partition mémoire automatiquement
Lit les variables de configuration depuis platformio.ini
Génère le contenu du fichier memory.csv en fonction de la configuration
"""

import re
import os
import time
from pathlib import Path

# Import pour PlatformIO
try:
    Import("env")
    project_dir = env.get("PROJECT_DIR")
except:
    # Fallback si exécuté en standalone
    project_dir = os.getcwd()

def read_memory_config():
    """Lit la configuration mémoire depuis platformio.ini"""
    platformio_path = os.path.join(project_dir, "platformio.ini")
    
    config = {
        'memory': 4,
        'ota': True,
        'spiffs': 0  # En Ko
    }
    
    try:
        with open(platformio_path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # Lire esp_memory
        match = re.search(r'esp_memory\s*=\s*(\d+)', content)
        if match:
            config['memory'] = int(match.group(1))
        
        # Lire esp_ota
        match = re.search(r'esp_ota\s*=\s*(true|false)', content, re.IGNORECASE)
        if match:
            config['ota'] = match.group(1).lower() == 'true'
        
        # Lire esp_spiffs (en Ko)
        match = re.search(r'esp_spiffs\s*=\s*(\d+)', content)
        if match:
            config['spiffs'] = int(match.group(1))
        
        print(f"[generate_memory] Config: {config['memory']}Mo, OTA={config['ota']}, SPIFFS={config['spiffs']}Ko")
        return config
    except Exception as e:
        print(f"[generate_memory] ERREUR lors de la lecture de platformio.ini: {e}")
        return config

def generate_partition_csv(memory_mo, ota_enabled, spiffs_ko):
    """Génère le contenu du fichier partition CSV dynamiquement"""
    
    # Convertir en bytes
    total_memory_bytes = memory_mo * 1024 * 1024
    spiffs_size_bytes = spiffs_ko * 1024
    
    # Offset de départ pour app (après NVS et OTA metadata)
    app_start_offset = 0x10000
    
    # Calculer la taille disponible pour l'app
    if ota_enabled:
        # Avec OTA : NVS (0x5000) + OTA data (0x2000)
        reserved_bytes = 0x7000
        overhead_bytes = int(0.1 * 1024 * 1024)  # 0.1 Mo de marge
        available_for_apps = total_memory_bytes - reserved_bytes - spiffs_size_bytes - overhead_bytes
        app_size_bytes = available_for_apps // 2  # Diviser par 2 pour deux apps
    else:
        # Sans OTA : NVS seulement (0x5000)
        reserved_bytes = 0x5000
        overhead_bytes = int(0.1 * 1024 * 1024)  # 0.1 Mo de marge
        available_for_app = total_memory_bytes - reserved_bytes - spiffs_size_bytes - overhead_bytes
        app_size_bytes = available_for_app
    
    # Aligner à 0x10000 (64 Ko) pour les partitions, requis par ESP32
    ALIGNMENT = 0x10000
    app_size_bytes = (app_size_bytes // ALIGNMENT) * ALIGNMENT
    
    # Conversion en hex
    app_size_hex = hex(app_size_bytes)
    spiffs_size_hex = hex(spiffs_size_bytes)
    
    # Déterminer la description SPIFFS
    if spiffs_ko == 0:
        spiffs_desc = "no SPIFFS"
    else:
        spiffs_desc = f"SPIFFS {spiffs_ko}KB"
    
    csv_lines = []
    
    if ota_enabled:
        # Avec OTA
        csv_lines = [
            f"# ESP32 Partition Table ({memory_mo}MB total, OTA enabled, {spiffs_desc})",
            "# Name,   Type, SubType, Offset,  Size, Flags",
            "nvs,      data, nvs,     0x9000,  0x5000,",
            "otadata,  data, ota,     0xe000,  0x2000,",
        ]
        
        app0_offset = app_start_offset
        app1_offset = app_start_offset + app_size_bytes
        # Aligner app1_offset à 0x1000
        app1_offset = ((app1_offset + ALIGNMENT - 1) // ALIGNMENT) * ALIGNMENT
        
        csv_lines.append(f"app0,     app,  ota_0,   {hex(app0_offset)},  {app_size_hex},")
        csv_lines.append(f"app1,     app,  ota_1,   {hex(app1_offset)},  {app_size_hex},")
        
        if spiffs_ko > 0:
            spiffs_offset = app1_offset + app_size_bytes
            # Aligner spiffs_offset à 0x1000
            spiffs_offset = ((spiffs_offset + ALIGNMENT - 1) // ALIGNMENT) * ALIGNMENT
            csv_lines.append(f"spiffs,   data, spiffs,  {hex(spiffs_offset)},  {spiffs_size_hex},")
    else:
        # Sans OTA
        csv_lines = [
            f"# ESP32 Partition Table ({memory_mo}MB total, no OTA, {spiffs_desc})",
            "# Name,   Type, SubType, Offset,  Size, Flags",
            "nvs,      data, nvs,     0x9000,  0x5000,",
        ]
        
        app_offset = app_start_offset
        csv_lines.append(f"app,      app,  factory, {hex(app_offset)},  {app_size_hex},")
        
        if spiffs_ko > 0:
            spiffs_offset = app_offset + app_size_bytes
            # Aligner spiffs_offset à 0x1000
            spiffs_offset = ((spiffs_offset + ALIGNMENT - 1) // ALIGNMENT) * ALIGNMENT
            csv_lines.append(f"spiffs,   data, spiffs,  {hex(spiffs_offset)},  {spiffs_size_hex},")
    
    csv_lines.append("")  # Ligne vide à la fin
    
    return "\n".join(csv_lines)

def get_current_memory_csv_content():
    """Lit le contenu actuel de memory.csv"""
    memory_csv_path = os.path.join(project_dir, "memory", "memory.csv")
    
    if not os.path.exists(memory_csv_path):
        print(f"[generate_memory] Pas de memory.csv existant")
        return None
    
    try:
        with open(memory_csv_path, 'r', encoding='utf-8') as f:
            return f.read()
    except Exception as e:
        print(f"[generate_memory] ERREUR lors de la lecture de memory.csv: {e}")
        return None

def write_memory_csv(csv_content):
    """Écrit le contenu dans memory.csv"""
    memory_csv_path = os.path.join(project_dir, "memory", "memory.csv")
    
    try:
        with open(memory_csv_path, 'w', encoding='utf-8') as f:
            f.write(csv_content)
        print(f"[generate_memory] memory.csv créé/remplacé")
        return True
    except Exception as e:
        print(f"[generate_memory] ERREUR lors de l'écriture de memory.csv: {e}")
        return False

def ensure_platformio_ini_correct():
    """Vérifie que platformio.ini pointe vers memory/memory.csv"""
    platformio_path = os.path.join(project_dir, "platformio.ini")
    
    try:
        with open(platformio_path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
        
        modified = False
        for i, line in enumerate(lines):
            if line.startswith('board_build.partitions = '):
                if line.strip() != "board_build.partitions = memory/memory.csv":
                    lines[i] = "board_build.partitions = memory/memory.csv\n"
                    modified = True
                    print(f"[generate_memory] platformio.ini mis à jour vers memory/memory.csv")
                break
        
        if modified:
            with open(platformio_path, 'w', encoding='utf-8') as f:
                f.writelines(lines)
            return True
        
        return False
            
    except Exception as e:
        print(f"[generate_memory] ERREUR lors de la mise à jour de platformio.ini: {e}")
        return False

def main():
    """Fonction principale"""
    print("\n[generate_memory] ========== GÉNÉRATION PARTITION MÉMOIRE ==========")
    
    # Lire la configuration
    config = read_memory_config()
    
    # Générer le contenu CSV
    new_csv_content = generate_partition_csv(config['memory'], config['ota'], config['spiffs'])
    
    if not new_csv_content:
        print("[generate_memory] ❌ Configuration non supportée")
        print("[generate_memory] ========== ÉCHEC ==========\n")
        return
    
    # Lire le contenu actuel
    current_csv_content = get_current_memory_csv_content()
    
    # Comparer et mettre à jour si nécessaire
    if current_csv_content != new_csv_content:
        print(f"[generate_memory] Changement détecté, mise à jour de memory.csv")
        
        # Écrire le nouveau fichier
        if write_memory_csv(new_csv_content):
            # Vérifier platformio.ini
            if ensure_platformio_ini_correct():
                print("[generate_memory] ⏳ Pause de 2 secondes pour que PlatformIO relise...")
                time.sleep(2)
                print("[generate_memory] ✅ Prêt à continuer")
            
            print("[generate_memory] ========== PARTITION MISE À JOUR ==========\n")
        else:
            print("[generate_memory] ❌ Impossible de créer memory.csv")
            print("[generate_memory] ========== ÉCHEC ==========\n")
    else:
        print(f"[generate_memory] memory.csv déjà correct, aucune modification")
        ensure_platformio_ini_correct()
        print("[generate_memory] ========== AUCUNE MODIFICATION ==========\n")

# Exécution
main()
