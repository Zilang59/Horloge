import os
import re

# Dossiers
src_dir = "src"
include_dir = "include"
donotouch_dir = os.path.join(include_dir, "DONOTTOUCH")
output_file = os.path.join("src", "AllFunction.h")
main_file = os.path.join(src_dir, "main.cpp")

# Exclusions
excluded_files = {"web_content.h"}
excluded_functions = {"loop", "setup", "hexToNeopixelbus"}

# Regex
function_regex = re.compile(r"^\s*([a-zA-Z_][\w\s\*]+)\s+([a-zA-Z_]\w*)\s*\(([^)]*)\)\s*\{")
struct_regex = re.compile(r"^\s*struct\s+([a-zA-Z_]\w*)\s*\{")
include_regex = re.compile(r'^\s*#include\s*[<"]([^">]+)[">]')

# --- Étape 1 : récupérer les includes valides dans main.cpp
included_headers = set()
with open(main_file, "r", encoding="utf-8") as main:
    for line in main:
        if line.strip().startswith("//"):  # ligne commentée
            continue
        match = include_regex.match(line)
        if match:
            included_headers.add(match.group(1))  # ex: "LED_RGB.h" ou "DONOTTOUCH/setupSPIFFS.h"

print("Headers utilisés :", included_headers)

# --- Étape 2 : extraire structures et fonctions des fichiers inclus
structures_by_file = {}
functions_by_file = {}

def extract_from_file(file_path, header_key):
    with open(file_path, "r", encoding="utf-8") as file:
        for line in file:
            # Extraction des structures
            struct_match = struct_regex.match(line)
            if struct_match:
                struct_name = struct_match.group(1)
                if header_key not in structures_by_file:
                    structures_by_file[header_key] = set()
                structures_by_file[header_key].add(f"struct {struct_name};")
            
            # Extraction des fonctions
            func_match = function_regex.match(line)
            if func_match:
                return_type, func_name, params = func_match.groups()
                if func_name in excluded_functions:
                    continue
                if func_name in {"if", "else"}:
                    continue
                prototype = f"{return_type} {func_name}({params});"
                if header_key not in functions_by_file:
                    functions_by_file[header_key] = set()
                functions_by_file[header_key].add(prototype)

def extract_from_dir(directory, relative_prefix=""):
    for root, _, files in os.walk(directory):
        for filename in files:
            if filename in excluded_files:
                continue
            if filename.endswith(".h") or filename.endswith(".cpp"):
                # Construit le chemin relatif pour comparer avec ceux du main.cpp
                rel_path = os.path.relpath(os.path.join(root, filename), include_dir)
                rel_path = rel_path.replace("\\", "/")  # normalisation Windows/Linux

                if rel_path not in included_headers and filename not in included_headers:
                    continue  # pas inclus → on skip

                file_path = os.path.join(root, filename)
                extract_from_file(file_path, rel_path)

# Extraction (src + include + DONOTTOUCH)
extract_from_dir(include_dir)
extract_from_dir(donotouch_dir, "DONOTTOUCH")
extract_from_dir(src_dir)

# --- Étape 3 : générer le fichier
with open(output_file, "w", encoding="utf-8") as out_file:
    out_file.write("// Fichier généré automatiquement\n")
    out_file.write("// Includes nécessaires pour les types utilisés\n")
    out_file.write("#include <NeoPixelBus.h>\n")
    out_file.write("#include <ArduinoJson.h>\n\n")
    
    # Récupérer tous les fichiers uniques
    all_files = set(list(structures_by_file.keys()) + list(functions_by_file.keys()))
    
    for filename in sorted(all_files):
        out_file.write(f"// {filename}\n")
        
        # Structures d'abord
        if filename in structures_by_file:
            for struct in sorted(structures_by_file[filename]):
                out_file.write(f"    {struct}\n")
        
        # Ensuite les fonctions
        if filename in functions_by_file:
            for function in sorted(functions_by_file[filename]):
                out_file.write(f"    {function}\n")
        
        out_file.write("\n")

total_structs = sum(len(s) for s in structures_by_file.values())
total_functions = sum(len(f) for f in functions_by_file.values())
print(f"Fichier {output_file} mis à jour avec {total_structs} structures et {total_functions} fonctions.")
