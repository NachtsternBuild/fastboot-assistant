#!/bin/bash
# build-rpm.sh
# thanks to @jean28518
# this is a modified version of the bash script, for RPM package building from linux-assistant
VERSION="$( cat version.txt )"

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
build_dir="${source_dir}/Build"

# set Authorisation
chmod a+x "$source_dir"
chmod a+x "$header_dir"
chmod a+x "$config_dir"
chmod a+x "$reboot_dir"
chmod a+x "$flash_dir"
chmod a+x "$preflash_dir"
chmod a+x "$instructions_dir"
chmod a+x "$build_dir"

# Check if target directory exists
while true; do
    read -p "Must build-project be created? (j/n): " answer
    if [[ "$answer" == "j" ]]; then
        echo "Create Directory."
        rm -rf "$target_dir"
        mkdir "$target_dir"
        echo "Ready."
        break
    elif [[ "$answer" == "n" ]]; then
        echo "Not created."
        break
    else
        echo "Invalid input. Please enter 'j' or 'n'."
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
find "$build_dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
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
rm -rf "$output_dir"
mkdir "$output_dir"
cp Projekt-122-l "$output_dir"
chmod a+x "$output_dir"
echo "Ready."

# Cleanup prompt
while true; do
    read -p "Do you want cleaning old files? (j/n): " answer
    if [[ "$answer" == "j" ]]; then
        echo "Start make clean."
        make clean
        rm -r "$target_dir"
        echo "Cleaning successful."
        break
    elif [[ "$answer" == "n" ]]; then
        echo "No cleaning"
        break
    else
        echo "Please use 'j' or 'n'."
    fi
done

echo "Changing to build directory."
cd "$source_dir" || { echo "Error with changing to $source_dir"; exit 1; }
# Remove files from previous build
echo "Delete old build files."
rm -r rpmbuild/SOURCES

# Prepare rpm files for packaging
mkdir -p rpmbuild/SOURCES/fastboot-assistant-$VERSION
cp -r "$output_dir/*" rpmbuild/SOURCES/fastboot-assistant-$VERSION/
chmod +x rpmbuild/SOURCES/fastboot-assistant-$VERSION/fastboot-assistant
cp "$build_dir/fastboot-assistant.desktop" rpmbuild/SOURCES/fastboot-assistant-$VERSION/
cp "$build_dir/sweet_unix.png" rpmbuild/SOURCES/fastboot-assistant-$VERSION/

# Package rpm files and build
cd rpmbuild/SOURCES/
tar -czvf fastboot-assistant-$VERSION.tar.gz fastboot-assistant-$VERSION
cd ../../
cp -r rpmbuild $HOME/
sed -i "2s/.*/Version:        $VERSION/" ./rpmbuild/SPECS/fastboot-assistant.spec 
rpmbuild -ba ./rpmbuild/SPECS/fastboot-assistant.spec 
echo "Your rpm package is now at $HOME/rpmbuild/RPMS/"
