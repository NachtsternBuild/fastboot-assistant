#!/bin/bash
#
# ╔═══════════════════════════════════════════════╗
# ║              Fastboot-Assistant               ║
# ║               Build Environment               ║
# ╚═══════════════════════════════════════════════╝
# ╔═══════════════════════════════════════════════╗
# ║                                               ║
# ║                   License:                    ║ 
# ║          GNU GENERAL PUBLIC LICENSE           ║
# ║                  Version 3                    ║
# ║                                               ║
# ╚═══════════════════════════════════════════════╝
# 
# build skript for:
# - object file of the fastboot-assistant
# - Debian package
# 	- simple mode
# 	- debuild
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

# main dirs
home_dir="$HOME"
source_dir="$(pwd)"

# infos from the other files
build_dir="${source_dir}/Build"
build_info_dir="${build_dir}/info"

# the version
VERSION="$(cat ${build_info_dir}/version.txt)"
# the patch
PATCH="$(cat ${build_info_dir}/patch.txt)"
# changelog content
CONTENT="$(cat ${build_info_dir}/content.txt)"
# branch → Ubuntu Version (noble, oracular)
BRANCH="$(cat ${build_info_dir}/branch.txt)"

# the architecture
ARCHITECTURE="amd64"

# Directory paths
# dirs for code
header_dir="${source_dir}/header"
# header subdirs
h_flash_dir="${header_dir}/flash"
h_UI_dir="${header_dir}/UI"
h_commands_dir="${header_dir}/commands"
h_config_dir="${header_dir}/config"
h_directory_dir="${header_dir}/directory"
h_message_dir="${header_dir}/message"
h_spinner_dir="${header_dir}/spinner"
h_theme_dir="${header_dir}/theme"
h_partition_dir="${header_dir}/partition"

config_dir="${source_dir}/config_projekt"
reboot_dir="${source_dir}/reboot"

flash_dir="${source_dir}/flash"
# flash subdirs
f_others_dir="${flash_dir}/others"

preflash_dir="${source_dir}/preflash"
# preflash subdirs
p_backup_dir="${preflash_dir}/backup"
p_prepare_dir="${preflash_dir}/prepare"

instructions_dir="${source_dir}/instructions"
updater_dir="${source_dir}/updater"
target_dir="${source_dir}/build_project"
output_dir="${source_dir}/output"
main_dir="${source_dir}/main"
style_dir="${source_dir}/style"

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
    echo -e "${RED}[x][⚠]Error: $error_msg${NC}"
}

# function that create the build-dir
create_target_dir() {
    prompt_user "[?] Muss der Ordner 'build-project' erstellt werden? (j/n) (y/n): "
    while true; do
        read -n1 -s answer
        case "$answer" in 
            j|J|y|Y)
                echo "[⧗] Create dirctories..."
                rm -rf "$target_dir"
                mkdir "$target_dir"
                echo "[⧗] Set ccache size..."
                ccache -M 5G
                build_info "[✓] Completed."
                break
                ;;
            n|N)
                prompt_user "[x] Not created."
                break
                ;;
            * )
                build_info "[⚠] Bitte 'j', 'y' oder 'n' verwenden."
                ;;
        esac
    done
}

# function that compile the program
building() {
	echo "[⧗] Start Build..."
    chmod a+x "$target_dir"
    cd "$target_dir" || { error_msg "Error with changing to $target_dir"; exit 1; }
    
    if make; then
        echo "[✓] Build completed."
    else
        error_msg "Error with building."
        exit 1
    fi
    
    echo "[✓] Build completed."
    echo "[⧗] Starting postbuild..."
	echo "[⧗] Remove old builds..."
    rm -rf "$output_dir"
    mkdir -p "$output_dir"
    echo "[⧗] Coping new builds..."
    cp fastboot-assistant "$output_dir"
    echo "[⧗] Style files..."
    cp style_dark.css "$output_dir"
    cp style_light.css "$output_dir"
    cp style_dark.css "$style_dir"
    cp style_light.css "$style_dir"
    cp sweet_unix.png "$output_dir"
    echo "[⧗] Set authorisations..."
    chmod a+x "$output_dir"
    echo "[✓] Application are at $output_dir."

    # cleaning after the build
    clean_build
}
	
# function for clean after build
clean_build() {
	while true; do
        prompt_user "[?] Möchten Sie alte Dateien bereinigen? (j/n) (y/n): "
        read -n1 -s answer
        case "$answer" in
            j|J|y|Y )
                echo "[⧗] Start make clean..."
                make clean
                rm -rf "$target_dir"
                prompt_user "[✓] Cleanup successful."
                break
                ;;
            n|N )
                prompt_user "[x] No Cleanup."
                break
                ;;
            * )
                build_info "[⚠] Bitte 'j', 'y' oder 'n' verwenden."
                ;;
        esac
    done
}

# function to build the debian package
debian_package_build_simple() {
	echo "[⧗] Start Debian package build..."
	echo "[⧗] Build mode: simple"
	echo "[⧗] Changing to build directory..."
	cd "$source_dir" || { echo "[*] Error with changing to $source_dir"; exit 1; }
	# Remove files from previous build
	echo "[⧗] Delete old build files..."
	rm -r deb/usr/

	# Prepare deb files for packaging
	echo "[⧗] Start building..."
	echo "[⧗] Create required directories..."
	mkdir -p deb/usr/bin/fastboot-assistant
	mkdir -p deb/usr/share/icons/hicolor/256x256/apps/
	mkdir -p deb/usr/share/applications/
	mkdir -p deb/usr/share/fastboot-assistant/
	echo "[⧗] Copy all files to deb/usr/bin..."
	cp -r "$output_dir/fastboot-assistant" deb/usr/bin/fastboot-assistant/
	echo "[⧗] Copy all files to deb/usr/share/icons/hicolor/256x256/apps/..."
	cp "$build_dir/sweet_unix.png" deb/usr/share/icons/hicolor/256x256/apps/
	echo "[⧗] Copy all files to deb/usr/share/applications/..."
	cp "$build_dir/fastboot-assistant.desktop" deb/usr/share/applications/
	echo "[⧗] Copy all files to deb/usr/share/fastboot-assistant/..."
	cp -r "$output_dir/style_dark.css" deb/usr/share/fastboot-assistant/
	cp -r "$output_dir/style_light.css" deb/usr/share/fastboot-assistant/
	cp -r "$build_dir/sweet_unix.png" deb/usr/share/fastboot-assistant/

	# set authorisations with 'chmod'
	echo "[⧗] Set authorisations..."
	chmod a+x deb/usr/bin/fastboot-assistant
	chmod 755 deb/usr/share/fastboot-assistant/style_dark.css
	chmod 755 deb/usr/share/fastboot-assistant/style_light.css
	chmod 755 deb/DEBIAN
	
	# Estimate the installed size by summing the sizes of all files in the deb directory
	echo "[⧗] Set package size..."
	SIZE=$(du -s deb | cut -f1)
	sed -i "s/Installed-Size: .*/Installed-Size: $SIZE/" deb/DEBIAN/control
	
	# Build deb package
	echo "[⧗] Build package..."
	echo "[⧗] Set version..."
	sed -i "2s/.*/Version: $VERSION/" deb/DEBIAN/control
	echo "[⧗] Build DEBIAN package..."
	dpkg-deb --build -Zxz --root-owner-group deb
	mv deb.deb "fastboot-assistant_${VERSION}_${ARCHITECTURE}.deb"
	echo "[✓] Package ready."
}

# Function that build the DEB using debuild
debian_package_build_debuild() {
	echo "[⧗] Start Debian package build..."
	echo "[⧗] Build mode: debuild"
	echo "[⧗] Define vars for the DEB..."
	# debian dir
	debian_dir="${source_dir}/debian"
	# vars for deb debuild
	PKG_NAME="fastboot-assistant"
	MAINTAINER="Elias Mörz <elias.moerz@mail.de>"
	MAINTAINER_NAME="Elias Mörz"
	DESCRIPTION=" Program to facilitate the installation of custom ROMs and GSIs on Android devices."
	SECTION="utils"
	PRIORITY="optional"
	echo "[⧗] Set time format..."
	export LC_TIME=C
	DATE=$(date --date='today' +"%a, %d %b %Y %H:%M:%S %z")
	echo "[⧗] Set desktop and icon..."
	ICON="sweet_unix"
	DESKTOP="fastboot-assistant"
	
	echo "[⧗] Create /debian structure..."
	mkdir -p "$debian_dir"
	echo "[⧗] Create control..."
	# control file
	# depends of the control
	DEPENDS="adb, fastboot, xz-utils, unzip, zip, wget, curl, pkexec, libgtk-4-1 (>= 4.10), heimdall-flash, heimdall-flash-frontend, coreutils, libc6 (>= 2.15), xdg-desktop-portal, xdg-desktop-portal-gtk, xdg-utils, libadwaita-1-0 (>= 1.6)"
	BUILD_DEPENDS="debhelper-compat (= 13), rsync, make, libgtk-4-dev (>= 4.10), libadwaita-1-dev, libsecret-1-dev, pkg-config, gcc"

# control
cat > "${debian_dir}/control" <<EOF
Source: $PKG_NAME
Section: $SECTION
Priority: $PRIORITY
Maintainer: $MAINTAINER
Build-Depends: $BUILD_DEPENDS
Standards-Version: $VERSION

Package: $PKG_NAME
Architecture: $ARCHITECTURE
Depends: $DEPENDS
Description: $DESCRIPTION
EOF
	
	echo "[⧗] Create changelog..."
	# changelog file
	URGENCY="medium"

# changelog
cat > "${debian_dir}/changelog" <<EOF
$PKG_NAME (${VERSION}ubuntu${PATCH}) $BRANCH; urgency=$URGENCY

  * $CONTENT

 -- $MAINTAINER  $DATE
EOF
	
	echo "[⧗] Create copyright..."
	# copyright file
	# content for the copyright
	LICENSE="Apache 2.0"

# copyright
cat > "${debian_dir}/copyright" <<EOF
Copyright (C) $(date +%Y) $MAINTAINER_NAME

License: $LICENSE
EOF

	echo "[⧗] Create install..."
# install file
cat > debian/install <<EOF
build_project/fastboot-assistant usr/bin/fastboot-assistant/
desktop/fastboot-assistant.desktop usr/share/applications/
icons/sweet_unix.png usr/share/icons/hicolor/256x256/apps/
style/style_dark.css usr/share/fastboot-assistant/
style/style_light.css usr/share/fastboot-assistant/
icons/sweet_unix.png usr/share/fastboot-assistant/

EOF

	echo "[⧗] Create rules..."
# rules file
cat > "${debian_dir}/rules" <<'EOF'
#!/usr/bin/make -f

%:
	dh $@
	
override_dh_auto_build:
	export CCACHE_DISABLE=1 
	rm -rf build_project
	mkdir -p build_project
	for dir in header Build config_projekt reboot flash preflash instructions updater \
	           header/flash header/UI header/commands header/config header/directory \
	           header/message header/spinner header/theme  header/partition flash/others main \
	           preflash/backup preflash/prepare; do \
		rsync -av --update --exclude '.git/' --exclude='*/' --exclude='*.md' "$$dir/" build_project/ ; \
	done
	$(MAKE) -C build_project

EOF
	echo "[⧗] Set authorization for debian/rules..."
	chmod +x debian/rules
	echo "[✓] All files are created."
	
	prompt_user "[?] Bauen des Debian-Package mit 'debuild -us -uc'? (j/n): "
	read -p " " answer
	if [ "$answer" == "j" ] || [ "$answer" == "J" ] || [ "$answer" == "y" ] || [ "$answer" == "Y" ]; 
 	then
    	echo "[⧗] Start build..."
    	if debuild -us -uc; then
        	echo "[✓] Build Debian-Package completed."
    	else
        	error_msg "Error with building."
        	exit 1
    	fi
    	
    else 
    	echo "[x] No build."
    fi
	echo "[✓] Build completed."
}

# Function were the user choose between deb build simple and debuild
debian_package_build() {
	echo "[⧗] Start Debian package build..."
	echo "[⧗] Select package Debian build mode..."
	while true; do
		prompt_user "[?] Auf welche Art soll das Debian-Paket gebaut werden? (j/n): "
		echo ""
		prompt_user "╭──────────── Debian-Package ────────────╮"
		echo -e "${CYAN}│       (s) Simple                       │${NC}"
	    echo -e "${GREEN}│      (d) Debuild                       │${NC}"
	    echo -e "${RED}│       (b) Beenden                      │${NC}"
	    prompt_user "╰────────────────────────────────────────╯"
		echo ""
    	read -n1 -s answer
    	case "$answer" in 
    	    s|S)
    	        echo "[⧗] Seleted build mode: simple"
    	        debian_package_build_simple
    	        echo "[✓] Build completed. Mode: simple."
    	        ;;
    	    d|D)
    	        echo "[⧗] Seleted build mode: debuild"
    	        debian_package_build_debuild
    	        echo "[✓] Build completed. Mode: debuild."
    	        ;;
    	    b|B|n|N)
    	        echo "[✗] Build script completed."
    	        break
    	        ;;
    	    * )
    	        build_info "[⚠] Ungültige Eingabe! Bitte 'l', 'w', 'b' oder 'n' verwenden."
    	        ;;
    	esac
	done
}

# Function for building the Snap package
build_snap() {
    echo "[⧗] Building Snap package..."
    echo "[⧗] Remove old builds..."
	rm -r "$build_dir_snap"
	snapcraft clean
	
	echo "[⧗] Create required directories..."
	mkdir -p "$build_dir_snap"
	echo "[⧗] Copy all files to $build_dir_snap..."
	for dir in "$snapcraft_dir" "$output_dir" "$build_dir"; do
        	# find "$dir" -maxdepth 1 -type f -exec cp {} "$build_dir_snap" \;
        	rsync -av --update --exclude '.git/' "$dir/" "$build_dir_snap/"
    	done
		echo "[✓] Copied all files to $build_dir_snap."
	chmod a+x "$build_dir_snap"
	
    if [ ! -f "$snapcraft_file" ]; then
        error_msg "Snapcraft file not found: $snapcraft_file"
        exit 1
    fi

    # Create the snap package using snapcraft
    echo "[⧗] Starting snap build..."
    cd "$build_dir_snap" || { error_msg "Failed to change to $build_dir_snap"; exit 1; }
    snapcraft

    if [ -f "$build_dir_snap/${snap_name}_${VERSION}_${ARCHITECTURE}.snap" ]; then
        echo "[✓] Snap package built successfully: $build_dir_snap/${snap_name}_${VERSION}_${ARCHITECTURE}.snap"
    else
        error_msg "Snap build failed."
        exit 1
    fi
}

# Function for building the Flatpak package
build_flatpak() {
    echo "[⧗] Building Flatpak package..."
	
	for dir in "$flatpak_dir" "$output_dir" "$build_dir"; do
        	# find "$dir" -maxdepth 1 -type f -exec cp {} "$build_dir_flatpak" \;
        	rsync -av --update --exclude '.git/' "$dir/" "$build_dir_flatpak/"
    	done
		echo "[✓] Copied all files to $build_dir_flatpak."
	
    if [ ! -f "$flatpak_manifest" ]; then
        error_msg "Flatpak manifest file not found: $flatpak_manifest"
        exit 1
    fi
    chmod a+x "$build_dir_flatpak"
	cd "$build_dir_flatpak" || { error_msg "Error with changing to $build_dir_snap"; exit 1; }
    # Build the flatpak package using flatpak-builder
    echo "[⧗] Starting flatpak build..."
    flatpak-builder --user --install --force-clean "$build_dir_flatpak/fastboot-assistant" "$flatpak_manifest"

    if [ -d "$build_dir_flatpak/fastboot-assistant" ]; then
        echo "[✓] Flatpak package built successfully."
    else
        error_msg "Flatpak build failed."
        exit 1
    fi
}

# build windows zip
windows_zip_build() {
	echo "[⧗] Start building zip-file..."
	echo "[⧗] Changing to $windows_dir..."
	cd "$windows_dir"
	echo "[⧗] Copy files..."
	cp "$source_dir/fastboot-assistant.deb" "$windows_dir"
	# create zip-file
	echo "[⧗] Build zip-file..."
	zip -r "$zip_name" "${zip_files[@]}"
	echo "[✓] Files were successfully packed in $zip_name."
}

# build the program for linux
build_program_linux() {
	echo "[⧗] Build for Linux..."
	prompt_user "[?] Kompilieren des Programmes? (j/n): "
	read -p " " answer
	if [ "$answer" == "j" ] || [ "$answer" == "J" ] || [ "$answer" == "y" ] || [ "$answer" == "Y" ]; 
 	then
    	echo "[⧗] Start Build for Linux..."
    	echo "[⧗] Copy all files to $target_dir..."
    	for dir in "$source_dir" "$build_dir" "$header_dir" "$config_dir" "$reboot_dir" "$flash_dir" "$preflash_dir" "$instructions_dir" "$h_flash_dir" "$h_UI_dir" "$h_commands_dir" "$h_config_dir" "$h_directory_dir" "$h_message_dir" "$h_spinner_dir" "$h_theme_dir" "$h_partition_dir" "$f_others_dir" "$p_backup_dir" "$p_prepare_dir" "$updater_dir" "$main_dir"; do
        	# find "$dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
        	rsync -av --update --exclude '.git/' --exclude='*/' --exclude='*.md' "$dir/" "$target_dir/"
    	done
		echo "[✓] Copied all files to $target_dir."
		
		building
    else 
    	echo "[x] No compilation."
    fi
    
    # loop for package build
    while true; do
    	prompt_user "[?] Für welches Betriebssystem soll der Fastboot-Assistant gebaut werden?"
    	echo ""
    	prompt_user "╭────────────── OS-Auswahl ──────────────╮"
    	echo -e "${RED}│            (d) Debian                  │${NC}"
    	echo -e "${CYAN}|            (s) Snap                    |${NC}"
    	echo -e "${GREEN}|            (f) Flatpak                 |${NC}"
    	echo -e "${RED}|            (b/n) Beenden               |${NC}"
    	prompt_user "╰────────────────────────────────────────╯"
    	read -n1 -s answer
   		echo ""
    	case "$answer" in 
        	d|D)
        	    debian_package_build
        	    prompt_user "[✓] End packagebuild."
        	    ;;
        	s|S)
        	    build_snap
        	    echo "[✓] End Snap build."
        	    ;;
        	f|F)
        	    build_flatpak
        	    echo "[✓] End Flatpak build."
        	    ;;
        	b|B|n|N)
        	    echo "[✓] End package build script."
        	    break
        	    ;;
        	* )
        	    build_info "[⚠] Bitte 'l', 'w', 'b' oder 'n' verwenden."
        	    ;;
    	esac
	done
}

# build the program for Windows
build_program_windows() {
    echo "[⧗] Build für Windows (WSL)..."
    build_info "[⚠] Warnung: Dies ist keine native Windows-Version, sondern läuft nur über WSL."
    echo "[⧗] Start Build for Windows (WSL)..."
    echo "[⧗] Copy all files to $target_dir..."
    for dir in "$source_dir" "$build_dir" "$header_dir" "$config_dir" "$reboot_dir" "$flash_dir" "$preflash_dir" "$instructions_dir" "$h_flash_dir" "$h_UI_dir" "$h_commands_dir" "$h_config_dir" "$h_directory_dir" "$h_message_dir" "$h_spinner_dir" "$h_theme_dir" "$h_partition_dir" "$f_others_dir" "$p_backup_dir" "$p_prepare_dir" "$updater_dir" "$main_dir"; do
        # find "$dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
        rsync -av --update --exclude '.git/' --exclude='*/' --exclude='*.md' "$dir/" "$target_dir/"
    done

    echo "[✓] Copied all files to $target_dir."
    echo "[⧗] Remove Linux spezific files $target_dir..."

    # remove unused files
    for unused in "${unused_files[@]}"; do
        unused_path="$target_dir/$unused"
        if [ -f "$unused_path" ]; then
            rm -rf "$unused_path"
            echo "[⧗] Remove $unused_path..."
        else
            echo "[⚠] Cannot found: $unused_path"
        fi
    done
    
    prompt_user "[?]Kompilieren des Programmes? (j/n): "
	read -p " " answer
	if [ "$answer" == "j" ] || [ "$answer" == "J" ] || [ "$answer" == "y" ] || [ "$answer" == "Y" ]; 
 	then
    	echo "[⧗] Start Build for WSL..."
    	echo "[⧗] Copy all files to $target_dir..."
    	for dir in "$preflash_dir_win" "$header_dir_win" "$windows_dir" "$other_dir_win"; do
        	# find "$dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
        	rsync -av --update --exclude '.git/' --exclude='*.md' "$dir/" "$target_dir/"
    	done
		echo "[✓] Copied all files to $target_dir."
		
		building
    else 
    	echo "[x] No compilation."
    fi
 	
 	prompt_user "[?] Soll eine Paket für die WSL gebaut werden? (j/n): "
 	read -n1 -s answer
 	if [ "$answer" == "j" ] || [ "$answer" == "J" ] || [ "$answer" == "y" ] || [ "$answer" == "Y" ]; 
 	then
  		debian_package_build
		echo "[✓] Build finished."
  		prompt_user "[✓] The package are at the $source_dir"
  		windows_zip_build
  		echo "[✓] Build finished."
  		prompt_user "[✓] The package are at the $source_dir"
	else
  		prompt_user "[x] No package build."
	fi
}


# start of the build script
start_info "╔═══════════════════════════════════════════════╗"
start_info "║                                               ║"
start_info "║   Fastboot-Assistant Build Script gestartet   ║"
start_info "║                                               ║"
start_info "╚═══════════════════════════════════════════════╝"
echo ""

create_target_dir

# get build target
while true; do
    prompt_user "[?] Für welches Betriebssystem soll der Fastboot-Assistant gebaut werden?"
    echo ""
    prompt_user "╭────────────── OS-Auswahl ──────────────╮"
    echo -e "${CYAN}│         (l) Linux                      │${NC}"
    echo -e "${GREEN}│         (w) Windows via WSL            │${NC}"
    echo -e "${RED}│          (b) Beenden                   │${NC}"
    prompt_user "╰────────────────────────────────────────╯"
    echo ""
    read -n1 -s answer
    case "$answer" in 
        l|L)
            echo "[⧗] Start Build for Linux..."
            build_program_linux
            echo -e "${GREEN}[✓] Build for Linux completed.${NC}"
            ;;
        w|W)
            echo "[⧗] Start Build foe Windows..."
            build_program_windows
            echo -e "${GREEN}[✓] Build for Windows completed.${NC}"
            ;;
        b|B|n|N)
            echo -e "${CYAN}[x] Build script completed.${NC}"
            break
            ;;
        * )
            build_info "[⚠] Ungültige Eingabe! Bitte 'l', 'w', 'b' oder 'n' verwenden."
            ;;
    esac
done

echo ""
start_info "╔═════════════════════════════════════════════════════════╗"
start_info "║                                                         ║"
start_info "║  [✓] Build Script des Fastboot-Assistant abgeschlossen! ║"
start_info "║                                                         ║"
start_info "╚═════════════════════════════════════════════════════════╝"
echo ""
