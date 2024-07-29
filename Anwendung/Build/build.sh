#!/bin/bash
# build.sh

# Define directory

home_dir="$HOME"

source_dir="$home_dir/Anwendung"
header_dir="${source_dir}/header"
config_dir="${source_dir}/config_projekt"
reboot_dir="${source_dir}/reboot"
flash_dir="${source_dir}/flash"
preflash_dir="${source_dir}/preflash"
instructions_dir="${source_dir}/instructions"
target_dir="${source_dir}/build_project"
output_dir="${source_dir}/output"

# Check if target directory exists
while true; do
    read -p "Muss der Ordner build-project erstellt werden? (j/n): " answer
    if [[ "$answer" == "j" ]]; then
        echo "Erstelle Verzeichnis."
        rm -r "$target_dir"
        mkdir "$target_dir"
        echo "Fertig"
        break
    elif [[ "$answer" == "n" ]]; then
        echo "Wird nicht erstellt."
        break
    else
        echo "Ungültige Eingabe. Bitte 'j' oder 'n' eingeben."
    fi
done
    
# Copy all files in the source directory, but no subdirectories
find "$source_dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
find "$header_dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
find "$config_dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
find "$reboot_dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
find "$flash_dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
find "$preflash_dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
find "$instructions_dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
echo "Alle Dateien wurden nach $target_dir kopiert."

cd "$target_dir" || { echo "Fehler beim Wechseln ins Verzeichnis $target_dir"; exit 1; }

# Build files
if make; then
    echo "Build erfolgreich."
else
    echo "Build fehlgeschlagen."
    exit 1
fi

rm -r "$output_dir"
mkdir "$output_dir"
cp Projekt-122-l "$output_dir"

# Cleanup prompt
while true; do
    read -p "Möchten Sie aufräumen? (j/n): " answer
    if [[ "$answer" == "j" ]]; then
        echo "Starte make clean"
        make clean
        rm -r "$target_dir"
        echo "Aufräumen abgeschlossen."
        break
    elif [[ "$answer" == "n" ]]; then
        echo "Wird nicht aufgeräumt."
        break
    else
        echo "Ungültige Eingabe. Bitte 'j' oder 'n' eingeben."
    fi
done
