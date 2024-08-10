#!/bin/bash
# build-deb.sh
# thanks to @jean28518
# this is a modified version of the bash script, for Debian package building from linux-assistant
VERSION="$( cat version.txt )"

# Define directory
# home directory
home_dir="$HOME"

# the other directory
source_dir="$home_dir/Dokumente/Schule/Bell/Projekt_122/Master/Projekt_122_GUI/v_0_5"
header_dir="${source_dir}/header"
config_dir="${source_dir}/config_projekt"
reboot_dir="${source_dir}/reboot"
flash_dir="${source_dir}/flash"
preflash_dir="${source_dir}/preflash"
instructions_dir="${source_dir}/instructions"
target_dir="${source_dir}/build_project"
output_dir="${source_dir}/output"
build_dir="${source_dir}/Build"

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
    read -p "Must build-project be created? (y/n): " answer
    if [[ "$answer" == "y" ]]; then
        echo "Create Directory."
        rm -r "$target_dir"
        mkdir "$target_dir"
        echo "Ready."
        break
    elif [[ "$answer" == "n" ]]; then
        echo "Not created."
        break
    else
        echo "Invalid input. Please enter 'y' or 'n'."
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
echo "Copy all files to $target_dir."
# set Authorisation
chmod a+x "$target_dir"
cd "$target_dir" || { echo "Error with changing to $target_dir"; exit 1; }

# Build files
echo "Start building application."
if make; then
    echo "Build successful."
else
    echo "Error in the build process."
    exit 1
fi

# copy output to output-dir
echo "Copy package."
rm -r "$output_dir"
mkdir "$output_dir"
cp Projekt-122-l "$output_dir"
chmod a+x "$output_dir"
echo "Ready."

# Cleanup prompt
while true; do
    read -p "Do you want cleaning old files? (y/n): " answer
    if [[ "$answer" == "y" ]]; then
        echo "Start make clean."
        make clean
        rm -r "$target_dir"
        echo "Cleaning successful."
        break
    elif [[ "$answer" == "n" ]]; then
        echo "No cleaning"
        break
    else
        echo "Please use 'y' or 'n'."
    fi
done

echo "Changing to build directory."
cd "$source_dir" || { echo "Error with changing to $source_dir"; exit 1; }
# Remove files from previous build
echo "Delete old build files."
rm -r deb/usr/

# Prepare deb files for packaging
echo "Start build..."
mkdir -p deb/usr/bin/projekt-122
echo "Copy all files..."
cp -r  "$output_dir/Projekt-122-l" deb/usr/bin/projekt-122/
cp -r "$preflash_dir/backup_root.sh" deb/usr/bin/projekt-122/
cp -r "$preflash_dir/prepare.sh" deb/usr/bin/projekt-122/
mkdir -p deb/usr/share/icons/hicolor/256x256/apps/
cp "$build_dir/sweet_unix.png" deb/usr/share/icons/hicolor/256x256/apps/
mkdir -p deb/usr/share/applications/
cp "$build_dir/fastboot-assistant.desktop" deb/usr/share/applications/

echo "Set authorisations..."
chmod a+x deb/usr/bin/projekt-122
chmod 755 deb/DEBIAN

# Build deb package
echo "Build package..."
sed -i "2s/.*/Version: $VERSION/" deb/DEBIAN/control
dpkg-deb --build -Zxz --root-owner-group deb
mv deb.deb Projekt-122-l-de.deb
echo "Package ready."
