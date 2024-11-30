#!/bin/bash
# build-fastboot-assistant.sh
# this is a modified version of the bash script, for Debian package and the RPM building from linux-assistant

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

# Directory paths
home_dir="$HOME"
source_dir="$home_dir/fastboot-assistant/Anwendung"
#source_dir="$home_dir/Dokumente/Schule/Bell/Projekt_122/Master/Projekt_122_GUI/v_0_6_3"
header_dir="${source_dir}/header"
config_dir="${source_dir}/config_projekt"
reboot_dir="${source_dir}/reboot"
flash_dir="${source_dir}/flash"
preflash_dir="${source_dir}/preflash"
instructions_dir="${source_dir}/instructions"
target_dir="${source_dir}/build_project"
output_dir="${source_dir}/output"
build_dir="${source_dir}/Build"
windows_dir="${source_dir}/Windows"
config_dir_win="${windows_dir}/config_projekt"
preflash_dir_win="${windows_dir}/preflash"
header_dir_win="${windows_dir}/header"
other_dir_win="${windows_dir}/Others"

# define the name of the zip-file for windows
zip_name="fastboot-assistant.zip"
unused_files=("make_dir.c" "remove_old.c" "flash_images.c" "flash_list_images.c" "backup_root.c" "backup_noroot.c" "unxz_files.c" "header_set_main_dir_with_wsl.c" "header_dark_theme.c" "header_language_check.c" "GUI.c" "updater.c")
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

	# Build deb package
	echo "Build package..."
	echo "Set version..."
	sed -i "2s/.*/Version: $VERSION/" deb/DEBIAN/control
	echo "Build DEBIAN package..."
	dpkg-deb --build -Zxz --root-owner-group deb
	mv deb.deb fastboot-assistant.deb
	echo "Package ready."
}

rpm_build() {
	# Prepare rpm files for packaging
	echo "Changing to build directory."
	cd "$source_dir" || { echo "Error with changing to $source_dir"; exit 1; }
	echo "Remove old build files..."
	rm -rf rpmbuild/SOURCES
	
	echo "Create required directories..."
	mkdir -p rpmbuild/SOURCES/fastboot-assistant-$VERSION
	echo "Copy files..."
	cp -r "$output_dir/fastboot-assistant" rpmbuild/SOURCES/fastboot-assistant-$VERSION/fastboot-assistant
	chmod a+x rpmbuild/SOURCES/fastboot-assistant-$VERSION/fastboot-assistant

	# Check if files exist before copying
	if [ -f "$build_dir/fastboot-assistant.desktop" ]; then
    	cp "$build_dir/fastboot-assistant.desktop" rpmbuild/SOURCES/fastboot-assistant-$VERSION/
	fi

	if [ -f "$build_dir/sweet_unix.png" ]; then
	    cp "$build_dir/sweet_unix.png" rpmbuild/SOURCES/fastboot-assistant-$VERSION/
	fi

	echo "Build RPM..."
	echo "Changing directory..."
	cd rpmbuild/SOURCES/
	echo "Create Tar..."
	tar -czvf fastboot-assistant-$VERSION.tar.gz fastboot-assistant-$VERSION
	cd ../../
	echo "Copy everything to $HOME"
	cp -r rpmbuild "$HOME/"
	echo "Set version..."
	sed -i "2s/.*/Version:        $VERSION/" ./rpmbuild/SPECS/fastboot-assistant.spec
	echo "Build package..."
	rpmbuild -ba ./rpmbuild/SPECS/fastboot-assistant.spec --without debuginfo
}

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
    	for dir in "$source_dir" "$build_dir" "$header_dir" "$config_dir" "$reboot_dir" "$flash_dir" "$preflash_dir" "$instructions_dir"; do
        	find "$dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
    	done
		echo "Alle Dateien wurden nach $target_dir kopiert."
		
		building
    else 
    	echo "Kein Kompilieren."
    fi
    
    # loop for package build
    while true; do
    prompt_user "Welches Paket soll gebaut werden?"
    start_info "Debian (d) / RPM (r) / Keines (n)"
    read -n1 -s answer
    case "$answer" in 
        d|D)
            debian_package_build
            prompt_user "Paketbau beendet."
            ;;
        r|R)
            rpm_build
            prompt_user "Paketbau beendet."
            ;;
        n|N|k|K)
            prompt_user "Kein Paketbau"
            break
            ;;
        * )
            build_info "Bitte 'd', 'r' oder 'n' verwenden."
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
    for dir in "$source_dir" "$build_dir" "$header_dir" "$config_dir" "$reboot_dir" "$flash_dir" "$preflash_dir" "$instructions_dir" "$other_dir_win"; do
        find "$dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
    done

    echo "Alle Dateien wurden nach $target_dir kopiert."
    echo "Entferne linux-spezifische Dateien in $target_dir..."

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
    	echo "Starte Build für Linux..."
    	echo "Kopiere alle Dateien nach $target_dir..."
    	for dir in "$source_dir" "$build_dir" "$header_dir" "$config_dir" "$reboot_dir" "$flash_dir" "$preflash_dir" "$instructions_dir"; do
        	find "$dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
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

