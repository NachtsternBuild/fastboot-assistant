#!/bin/bash
# build.sh

# Define directory
# home directory
home_dir="$HOME"

# the other directory
source_dir="$home_dir/fastboot-assistant/Anwendung"
header_dir="${source_dir}/header"
config_dir="${source_dir}/config_projekt"
reboot_dir="${source_dir}/reboot"
flash_dir="${source_dir}/flash"
preflash_dir="${source_dir}/preflash"
instructions_dir="${source_dir}/instructions"
target_dir="${source_dir}/build_project"
output_dir="${source_dir}/output"

# set Authorisation
chmod a+x "$source_dir"
chmod a+x "$header_dir"
chmod a+x "$config_dir"
chmod a+x "$reboot_dir"
chmod a+x "$flash_dir"
chmod a+x "$preflash_dir"
chmod a+x "$instructions_dir"

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
# set Authorisation
chmod a+x "$target_dir"
cd "$target_dir" || { echo "Fehler beim Wechseln ins Verzeichnis $target_dir"; exit 1; }

# Build files
echo "Starte Build."
if make; then
    echo "Build erfolgreich."
else
    echo "Build fehlgeschlagen."
    exit 1
fi

# copy output to output-dir
echo "Kopieren des Paketes."
rm -r "$output_dir"
mkdir "$output_dir"
cp Projekt-122-l "$output_dir"
chmod a+x "$output_dir"
echo "Fertig kopiert."

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
