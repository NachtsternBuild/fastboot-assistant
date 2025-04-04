#!/bin/bash
# build-fastboot-assistant.sh
# build skript for:
# - object file of the fastboot-assistant
# - Debian package
# - Snap
# - Flatpak
# this is a modified version of the bash script, for Debian package and the RPM building from the linux-assistant

# color for the output
BLUE='\033[0;34m'
CYAN='\033[0;36m'
LIGHT_BLUE='\033[1;34m'
LIGHT_CYAN='\033[1;36m'
RED='\033[0;31m'
MAGENTA='\033[0;35m'
LIGHT_RED='\033[1;31m'
GREEN='\033[0;32m'
LIGHT_GREEN='\033[1;32m'
YELLOW='\033[1;33m'
LIGHT_YELLOW='\033[1;33m'
WHITE='\033[0;37m'
NC='\033[0m' # No Color

# the version
VERSION="$(cat Build/version.txt)"
# the architecture
ARCHITECTURE="amd64"

# Directory paths
# main dirs
home_dir="$HOME"
source_dir="$(pwd)"
# dirs for code
header_dir="${source_dir}/header"
# header subdirs
h_flash_dir="${source_dir}/header/flash"
h_UI_dir="${source_dir}/header/UI"
h_commands_dir="${source_dir}/header/commands"
h_config_dir="${source_dir}/header/config"
h_directory_dir="${source_dir}/header/directory"
h_message_dir="${source_dir}/header/message"
h_spinner_dir="${source_dir}/header/spinner"
h_theme_dir="${source_dir}/header/theme"

config_dir="${source_dir}/config_projekt"
reboot_dir="${source_dir}/reboot"

flash_dir="${source_dir}/flash"
# flash subdirs
f_others_dir="${source_dir}/flash/others"

preflash_dir="${source_dir}/preflash"
# preflash subdirs
p_backup_dir="${source_dir}/preflash/backup"
p_prepare_dir="${source_dir}/preflash/prepare"

instructions_dir="${source_dir}/instructions"
updater_dir="${source_dir}/updater"
target_dir="${source_dir}/build_project"
output_dir="${source_dir}/output"
build_dir="${source_dir}/Build"

# for WSL
windows_dir="${source_dir}/Windows"
preflash_dir_win="${windows_dir}/preflash"
header_dir_win="${windows_dir}/header"
other_dir_win="${windows_dir}/Others"

# Snap build info
snapcraft_dir="${source_dir}/snap"
build_dir_snap="${source_dir}/build_snap"
snap_name="fastboot-assistant"
snapcraft_file="${snapcraft_dir}/snapcraft.yaml"

# Flatpak build info
flatpak_dir="${source_dir}/flatpak"
build_dir_flatpak="${source_dir}/build_flatpak"
flatpak_name="fastboot-assistant"
flatpak_manifest="${flatpak_dir}/io.github.nachtsternbuild.Fastboot-Assistant.yml"

# define the name of the zip-file for windows
zip_name="fastboot-assistant.zip"
unused_files=("backup_noroot.c" "header_set_main_dir_with_wsl.c" "header_get_config_dir.c" "header_get_config_file_path.c" "updater_stable.c")
zip_files=("WSL_install.bat" "Enable_WSL.bat" "README.md" "fastboot-assistant.deb")

# function that have output with color
prompt_user() {
    local prompt_msg=$1
    echo -e "${YELLOW}$prompt_msg${NC}"
}

# function for the build start and end
start_info() {
	local prompt_msg=$1
	echo -e "${CYAN}$prompt_msg${NC}"
}

# build info color
build_info() {
	local prompt_msg=$1
	echo -e "${RED}$prompt_msg${NC}"
}

# error message with color red
error_msg() {
    local error_msg=$1
    echo -e "${RED}Error: $error_msg${NC}"
}

# function that create the build-dir
create_target_dir() {
    prompt_user "Muss der Ordner 'build-project' erstellt werden? (j/n) (y/n): "
    while true; do
        read -n1 -s answer
        case "$answer" in 
            j|J|y|Y)
                echo "Erstelle Verzeichnis..."
                rm -rf "$target_dir"
                mkdir "$target_dir"
                echo "Setze ccache Speichergröße..."
                ccache -M 5G
                build_info "Fertig."
                break
                ;;
            n|N)
                prompt_user "Nicht erstellt."
                break
                ;;
            * )
                build_info "Bitte 'j', 'y' oder 'n' verwenden."
                ;;
        esac
    done
}

# function that compile the program
building() {
	echo "Starte Build..."
    chmod a+x "$target_dir"
    cd "$target_dir" || { error_msg "Fehler beim Wechsel nach $target_dir"; exit 1; }
    
    if make; then
        echo "Build erfolgreich."
    else
        error_msg "Fehler beim Build-Prozess."
        exit 1
    fi
    
    echo "Build abgeschlossen."
    echo "Starte Nachbearbeitung..."

    rm -rf "$output_dir"
    mkdir -p "$output_dir"
    cp fastboot-assistant "$output_dir"
    chmod a+x "$output_dir"
    echo "Die Anwendung ist im Verzeichnis $output_dir bereit."

    # cleaning after the build
    clean_build
}
	
# function for clean after build
clean_build() {
	while true; do
        prompt_user "Möchten Sie alte Dateien bereinigen? (j/n) (y/n): "
        read -n1 -s answer
        case "$answer" in
            j|J|y|Y )
                echo "Starte make clean..."
                make clean
                rm -rf "$target_dir"
                prompt_user "Bereinigung erfolgreich."
                break
                ;;
            n|N )
                prompt_user "Keine Bereinigung."
                break
                ;;
            * )
                build_info "Bitte 'j', 'y' oder 'n' verwenden."
                ;;
        esac
    done
}

# function to build the debian package
debian_package_build() {
	echo "Start Debian package build..."
	echo "Changing to build directory."
	cd "$source_dir" || { echo "Error with changing to $source_dir"; exit 1; }
	# Remove files from previous build
	echo "Delete old build files."
	rm -r deb/usr/

	# Prepare deb files for packaging
	echo "Start building..."
	echo "Create required directories..."
	mkdir -p deb/usr/bin/fastboot-assistant
	mkdir -p deb/usr/share/icons/hicolor/256x256/apps/
	mkdir -p deb/usr/share/applications/
	echo "Copy all files to deb/usr/bin..."
	cp -r  "$output_dir/fastboot-assistant" deb/usr/bin/fastboot-assistant/
	cp "$build_dir/sweet_unix.png" deb/usr/share/icons/hicolor/256x256/apps/
	cp "$build_dir/fastboot-assistant.desktop" deb/usr/share/applications/

	# set authorisations with 'chmod'
	echo "Set authorisations..."
	chmod a+x deb/usr/bin/fastboot-assistant
	chmod 755 deb/DEBIAN
	chmod 755 deb/postinst
	chmod 755 deb/postrm
	
	# Estimate the installed size by summing the sizes of all files in the deb directory
	SIZE=$(du -s deb | cut -f1)
	sed -i "s/Installed-Size: .*/Installed-Size: $SIZE/" deb/DEBIAN/control
	
	# Build deb package
	echo "Build package..."
	echo "Set version..."
	sed -i "2s/.*/Version: $VERSION/" deb/DEBIAN/control
	echo "Build DEBIAN package..."
	dpkg-deb --build -Zxz --root-owner-group deb
	mv deb.deb "fastboot-assistant_${VERSION}_${ARCHITECTURE}.deb"
	echo "Package ready."
}

# Function for building the Snap package
build_snap() {
    start_info "Building Snap package..."
    echo "Remove old builds..."
	rm -r "$build_dir_snap"
	snapcraft clean
	
	echo "Create required directories..."
	mkdir -p "$build_dir_snap"
	echo "Copy all files to $build_dir_snap..."
	for dir in "$snapcraft_dir" "$output_dir" "$build_dir"; do
        	# find "$dir" -maxdepth 1 -type f -exec cp {} "$build_dir_snap" \;
        	rsync -av --update --exclude '.git/' "$dir/" "$build_dir_snap/"
    	done
		echo "Alle Dateien wurden nach $build_dir_snap kopiert."
	chmod a+x "$build_dir_snap"
	
    if [ ! -f "$snapcraft_file" ]; then
        error_msg "Snapcraft file not found: $snapcraft_file"
        exit 1
    fi

    # Create the snap package using snapcraft
    echo "Starting snap build..."
    cd "$build_dir_snap" || { error_msg "Failed to change to $build_dir_snap"; exit 1; }
    snapcraft

    if [ -f "$build_dir_snap/${snap_name}_${VERSION}_${ARCHITECTURE}.snap" ]; then
        echo "Snap package built successfully: $build_dir_snap/${snap_name}_${VERSION}_${ARCHITECTURE}.snap"
    else
        error_msg "Snap build failed."
        exit 1
    fi
}

# Function for building the Flatpak package
build_flatpak() {
    start_info "Building Flatpak package..."
	
	for dir in "$flatpak_dir" "$output_dir" "$build_dir"; do
        	# find "$dir" -maxdepth 1 -type f -exec cp {} "$build_dir_flatpak" \;
        	rsync -av --update --exclude '.git/' "$dir/" "$build_dir_flatpak/"
    	done
		echo "Alle Dateien wurden nach $build_dir_flatpak kopiert."
	
    if [ ! -f "$flatpak_manifest" ]; then
        error_msg "Flatpak manifest file not found: $flatpak_manifest"
        exit 1
    fi
    chmod a+x "$build_dir_flatpak"
	cd "$build_dir_flatpak" || { error_msg "Error with changing to $build_dir_snap"; exit 1; }
    # Build the flatpak package using flatpak-builder
    echo "Starting flatpak build..."
    flatpak-builder --user --install --force-clean "$build_dir_flatpak/fastboot-assistant" "$flatpak_manifest"

    if [ -d "$build_dir_flatpak/fastboot-assistant" ]; then
        echo "Flatpak package built successfully."
    else
        error_msg "Flatpak build failed."
        exit 1
    fi
}

# build windows zip
windows_zip_build() {
	echo "Start building zip-file..."
	echo "Changing to $windows_dir"
	cd "$windows_dir"
	echo "Copy files..."
	cp "$source_dir/fastboot-assistant.deb" "$windows_dir"
	# create zip-file
	echo "Build zip-file..."
	zip -r "$zip_name" "${zip_files[@]}"
	echo "Files were successfully packed in $zip_name."
}

# build the program for linux
build_program_linux() {
	start_info "Build für Linux"
	prompt_user "Kompilieren des Programmes? (j/n): "
	read -p " " answer
	if [ "$answer" == "j" ] || [ "$answer" == "J" ] || [ "$answer" == "y" ] || [ "$answer" == "Y" ]; 
 	then
    	echo "Starte Build für Linux..."
    	echo "Kopiere alle Dateien nach $target_dir..."
    	for dir in "$source_dir" "$build_dir" "$header_dir" "$config_dir" "$reboot_dir" "$flash_dir" "$preflash_dir" "$instructions_dir" "$h_flash_dir" "$h_UI_dir" "$h_commands_dir" "$h_config_dir" "$h_directory_dir" "$h_message_dir" "$h_spinner_dir" "$h_theme_dir" "$f_others_dir" "$p_backup_dir" "$p_prepare_dir" "$updater_dir"; do
        	# find "$dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
        	rsync -av --update --exclude '.git/' --exclude='*/' "$dir/" "$target_dir/"
    	done
		echo "Alle Dateien wurden nach $target_dir kopiert."
		
		building
    else 
    	echo "Kein Kompilieren."
    fi
    
    # loop for package build
    while true; do
    prompt_user "Für welches Betriebssystem soll der Fastboot-Assistant gebaut werden?"
    prompt_user "************************"
    echo -e "$RED    Debian (d) $NC"
    prompt_user "************************"
    echo -e "$CYAN   Snap (s) $NC"
    prompt_user "************************"
    echo -e "$GREEN  Flatpak (f) $NC"
    prompt_user "************************"
    echo -e "$RED    Beenden (b/n) $NC"
    prompt_user "************************"
    read -n1 -s answer
    case "$answer" in 
        d|D)
            debian_package_build
            prompt_user "Paketbau beendet."
            ;;
        s|S)
            build_snap
            echo "Build des Snaps abgeschlossen."
            ;;
        f|F)
            build_flatpak
            echo "Build des Flatpaks abgeschlossen."
            ;;
        b|B|n|N)
            echo "Build-Skript beendet."
            break
            ;;
        * )
            build_info "Bitte 'l', 'w', 'b' oder 'n' verwenden."
            ;;
    esac
done
}

# build the program for Windows
build_program_windows() {
    start_info "Build für Windows"
    build_info "Dies ist keine native Windows-Version, sondern läuft nur über WSL."
    echo "Starte Build für Windows..."
    echo "Kopiere alle Dateien nach $target_dir..."
    for dir in "$source_dir" "$build_dir" "$header_dir" "$config_dir" "$reboot_dir" "$flash_dir" "$preflash_dir" "$instructions_dir" "$h_flash_dir" "$h_UI_dir" "$h_commands_dir" "$h_config_dir" "$h_directory_dir" "$h_message_dir" "$h_spinner_dir" "$h_theme_dir" "$f_others_dir" "$p_backup_dir" "$p_prepare_dir" "$updater_dir"; do
        # find "$dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
        rsync -av --update --exclude '.git/' --exclude='*/' "$dir/" "$target_dir/"
    done

    echo "Alle Dateien wurden nach $target_dir kopiert."
    echo "Entferne Linux spezifische Dateien in $target_dir..."

    # remove unused files
    for unused in "${unused_files[@]}"; do
        unused_path="$target_dir/$unused"
        if [ -f "$unused_path" ]; then
            rm -rf "$unused_path"
            echo "Entfernt $unused_path"
        else
            echo "Datei nicht gefunden: $unused_path"
        fi
    done
    
    prompt_user "Kompilieren des Programmes? (j/n): "
	read -p " " answer
	if [ "$answer" == "j" ] || [ "$answer" == "J" ] || [ "$answer" == "y" ] || [ "$answer" == "Y" ]; 
 	then
    	echo "Starte Build für WSL..."
    	echo "Kopiere alle Dateien nach $target_dir..."
    	for dir in "$preflash_dir_win" "$header_dir_win" "$windows_dir" "$other_dir_win"; do
        	# find "$dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
        	rsync -av --update --exclude '.git/' "$dir/" "$target_dir/"
    	done
		echo "Alle Dateien wurden nach $target_dir kopiert."
		
		building
    else 
    	echo "Kein Kompilieren."
    fi
 	
 	prompt_user "Soll eine Datei für die WSL gebaut werden? (j/n): "
 	read -n1 -s answer
 	if [ "$answer" == "j" ] || [ "$answer" == "J" ] || [ "$answer" == "y" ] || [ "$answer" == "Y" ]; 
 	then
  		debian_package_build
		echo "Build finished."
  		prompt_user "The package are at the $source_dir"
  		windows_zip_build
  		echo "Build finished."
  		prompt_user "The package are at the $source_dir"
	else
  		prompt_user "Kein Paketbau."
	fi
}

# main program
start_info "***********************************"
start_info "*                                 *"
start_info "* Fastboot-Assistant Build Script *"
start_info "*                                 *"
start_info "***********************************"
echo " "
create_target_dir

# choice for build in a loop
while true; do
    prompt_user "Für welches Betriebssystem soll der Fastboot-Assistant gebaut werden?"
    # read -p "Linux (l) / Windows via WSL (w) / Beenden (b): " answer
    prompt_user "************************"
    echo -e "$CYAN    Linux (l) $NC"
    prompt_user "************************"
    echo -e "$GREEN    Windows (w) $NC"
    prompt_user "************************"
    echo -e "$RED    Beenden (b) $NC"
    prompt_user "************************"
    read -n1 -s answer
    case "$answer" in 
        l|L)
            build_program_linux
            echo "Build für Linux abgeschlossen."
            ;;
        w|W)
            build_program_windows
            echo "Build für Windows abgeschlossen."
            ;;
        b|B)
            echo "Build-Skript beendet."
            break
            ;;
        * )
            build_info "Bitte 'l', 'w' oder 'b' verwenden."
            ;;
    esac
done

echo " "
start_info "******************************************************"
start_info "*                                                    *"
start_info "* Build Script des Fastboot-Assistant abgeschlossen! *"
start_info "*                                                    *"
start_info "******************************************************"

