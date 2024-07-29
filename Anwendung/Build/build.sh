#!/bin/bash
# build.sh

# Define directory
source_dir="/Anwendung"
target_dir="${source_dir}/build_project"

# make target dir
mkdir -p "$target_dir"

# Copy all files in the source directory, but no subdirectories
find "$source_dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;

echo "All files have been copied to $target_dir."

cd "$target_dir" || { echo "Failed to change directory to $target_dir"; exit 1; }

# Build files
if make; then
    echo "Build succeeded."
else
    echo "Build failed."
    exit 1
fi


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
