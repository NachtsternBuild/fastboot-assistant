#!/bin/bash
# build-rpm.sh
# thanks to @jean28518
# this is a modified version of the bash script, for RPM package building from linux-assistant

VERSION="$(cat Build/version.txt)"

# Define directory paths
home_dir="$HOME"
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

# Set Authorization for directories if they exist
for dir in "$source_dir" "$header_dir" "$config_dir" "$reboot_dir" "$flash_dir" "$preflash_dir" "$instructions_dir" "$build_dir"; do
    if [ -d "$dir" ]; then
        chmod a+x "$dir"
    fi
done

# Check if target directory needs to be created
while true; do
    read -p "Must build-project be created? (j/n): " answer
    case "$answer" in
        j|J )
            echo "Creating Directory."
            rm -rf "$target_dir"
            mkdir -p "$target_dir"
            echo "Ready."
            break
            ;;
        n|N )
            echo "Not created."
            break
            ;;
        * )
            echo "Invalid input. Please enter 'j' or 'n'."
            ;;
    esac
done

# Copy all files in the source directory, but no subdirectories
for dir in "$source_dir" "$header_dir" "$config_dir" "$reboot_dir" "$flash_dir" "$preflash_dir" "$instructions_dir" "$build_dir"; do
    find "$dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
done

echo "Copied all files to $target_dir."

# Set Authorization for target directory
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

# Copy output to output-dir
echo "Copy package."
rm -rf "$output_dir"
mkdir -p "$output_dir"
cp Projekt-122-l "$output_dir"
chmod a+x "$output_dir"
echo "Ready."

# Cleanup prompt
while true; do
    read -p "Do you want cleaning old files? (j/n): " answer
    case "$answer" in
        j|J )
            echo "Start make clean."
            make clean
            rm -r "$target_dir"
            echo "Cleaning successful."
            break
            ;;
        n|N )
            echo "No cleaning."
            break
            ;;
        * )
            echo "Please use 'j' or 'n'."
            ;;
    esac
done

echo "Changing to build directory."
cd "$source_dir" || { echo "Error with changing to $source_dir"; exit 1; }
# Remove files from previous build
echo "Delete old build files."
rm -rf rpmbuild/SOURCES

# Prepare rpm files for packaging
mkdir -p rpmbuild/SOURCES/fastboot-assistant-$VERSION
cp -r "$output_dir/"* rpmbuild/SOURCES/fastboot-assistant-$VERSION/fastboot-assistant
chmod a+x rpmbuild/SOURCES/fastboot-assistant-$VERSION/fastboot-assistant

# Check if files exist before copying
if [ -f "$build_dir/fastboot-assistant.desktop" ]; then
    cp "$build_dir/fastboot-assistant.desktop" rpmbuild/SOURCES/fastboot-assistant-$VERSION/
fi

if [ -f "$build_dir/sweet_unix.png" ]; then
    cp "$build_dir/sweet_unix.png" rpmbuild/SOURCES/fastboot-assistant-$VERSION/
fi

# Package rpm files and build
cd rpmbuild/SOURCES/
tar -czvf fastboot-assistant-$VERSION.tar.gz fastboot-assistant-$VERSION
cd ../../
cp -r rpmbuild "$HOME/"
sed -i "2s/.*/Version:        $VERSION/" ./rpmbuild/SPECS/fastboot-assistant.spec 
rpmbuild -ba ./rpmbuild/SPECS/fastboot-assistant.spec 
echo "Your rpm package is now at $HOME/rpmbuild/RPMS/"

