#!/bin/bash
# config.sh
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

# detecte the language
LANGUAGE=$(echo "${LANG:-en}" | cut -d_ -f1)
[[ "$LANGUAGE" != "de" ]] && LANGUAGE="en"

# texts
declare -A TEXTS

# all texts for the choices
# German
TEXTS[cleanup_snap]="[?] Soll Snapcraft aufräumen? (j/n): "
TEXTS[cleanup]="[?] Möchten Sie alte Dateien bereinigen? (j/n): "
TEXTS[package]="[?] Für welches OS soll der Fastboot-Assistant gebaut werden?"
TEXTS[build_package]="[?] Welches Paket soll gebaut werden?"

TEXTS[compile]="[?] Kompilieren des Programmes? (j/n): "
TEXTS[select_os]="OS-Auswahl"
TEXTS[invalid_input]="[⚠] Ungültige Eingabe! Bitte 'l', 'w', 'b' oder 'n' verwenden."
TEXTS[select_exit]="(b/n) Beenden"

# English
TEXTS[cleanup_snap_en]="[?] Should Snapcraft clean up? (j/n): "
TEXTS[cleanup_en]="[?] Do you want to clean old files? (y/n): "
TEXTS[package_en]="[?] Which OS should Fastboot Assistant be built for?"
TEXTS[build_package_en]="[?] Which package format should be built?"

TEXTS[compile_en]="[?] Compile the program? (y/n): "
TEXTS[select_os_en]="OS Selection"
TEXTS[invalid_input_en]="[⚠] Invalid input! Please use 'l', 'w', 'b', or 'n'."
TEXTS[select_exit_en]="(b/n) Exit"

# function for language choice
tr() {
    local key="$1"
    [[ "$LANGUAGE" == "de" ]] && echo "${TEXTS[$key]}" || echo "${TEXTS[${key}_en]}"
}


# main dirs
home_dir="$HOME"
source_dir="$(pwd)"

# infos from the other files
build_dir="${source_dir}/Build"

# the architecture
ARCHITECTURE="amd64"

# Snap build info
snapcraft_dir="${source_dir}/snap"
snap_name="fastboot-assistant"
snapcraft_file="${snapcraft_dir}/snapcraft.yaml"

# Flatpak build info
flatpak_dir="${source_dir}/flatpak"
flatpak_name="fastboot-assistant"
flatpak_manifest="${flatpak_dir}/io.github.nachtsternbuild.Fastboot-Assistant.yml"

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


