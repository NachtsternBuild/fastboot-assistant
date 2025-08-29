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
TEXTS[create_po]="[?] Müssen neue Übersetzungsdateien erstellt werden? (j/n)"
TEXTS[manuell_po]="[?] Soll Dateien manuell gebaut werden? (j/n)"
TEXTS[use_po]="[?] Für welche Übersetzungsdateien sollen gebaut werden?"
TEXTS[create_target]="[?] Muss der Ordner 'build-project' erstellt werden? (j/n): "
TEXTS[cleanup_prompt]="[?] Möchten Sie alte Dateien bereinigen? (j/n): "
TEXTS[build_debuild]="[?] Soll ein Debian-Paket mit 'debuild -us -uc' gebaut werden?"
TEXTS[build_deb_which]="[?] Auf welche Art soll das Debian-Paket gebaut werden?"
TEXTS[build_wsl_info]="[⚠] Warnung: Dies ist keine native Windows-Version, sondern läuft nur über WSL."
TEXTS[package_wsl]="[?] Soll eine Paket für die WSL gebaut werden? (j/n): "
TEXTS[build_which_os]="[?] Für welches OS soll der Fastboot-Assistant gebaut werden?"
TEXTS[build_package]="[?] Welches Paket soll gebaut werden?"

TEXTS[compile]="[?] Kompilieren des Programmes? (j/n): "
TEXTS[select_os]="OS-Auswahl"
TEXTS[invalid_input]="[⚠] Ungültige Eingabe! Bitte 'l', 'w', 'b' oder 'n' verwenden."
TEXTS[select_exit]="(b/n) Beenden"

# English
TEXTS[create_po]="[?] Do new translation files need to be created? (y/n)"
TEXTS[manuell_po]="[?] Should files be built manually? (y/n)"
TEXTS[use_po]="[?] Which translation files should be built?"
TEXTS[create_target_en]="[?] Should the 'build-project' folder be created? (y/n): "
TEXTS[cleanup_prompt_en]="[?] Do you want to clean old files? (y/n): "
TEXTS[build_debuild_en]="[?] Should a Debian package be built using 'debuild -us -uc'? "
TEXTS[build_deb_which_en]="[?] How should the Debian package be built?"
TEXTS[build_wsl_info_en]="[⚠] Warning: This is not a native Windows version – it runs under WSL only."
TEXTS[package_wsl_en]="[?] Should a package for WSL be built? (y/n): "
TEXTS[build_which_os_en]="[?] Which OS should Fastboot Assistant be built for?"
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
build_info_dir="${build_dir}/info"

# the version
VERSION="$(cat ${build_info_dir}/version.txt)"
VERSION_DEBUILD="$(cat ${build_info_dir}/version_deb.txt)"
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
h_language_dir="${header_dir}/language"

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

# for the po files
po_dir="${source_dir}/po"

# for the new language logic
MAKEFILE_DIR="${target_dir}"
PO_FILE_DIR="$MAKEFILE_DIR/po"
MO_DIR="$PO_FILE_DIR/LC_MESSAGES"
TARGET="fastboot-assistant"
OUTPUT_DIR_PO="${output_dir}/local"
SUPPORTED_LANGS=("de" "en" "es" "pt" "ru" "fr")

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
desktop_snap_dir="${source_dir}/desktop_snap"

# Flatpak build info
flatpak_dir="${source_dir}/flatpak"
build_dir_flatpak="${source_dir}/build_flatpak"
flatpak_name="fastboot-assistant"
flatpak_manifest="${flatpak_dir}/io.github.nachtsternbuild.Fastboot-Assistant.yml"

# define the name of the zip-file for windows
zip_name="fastboot-assistant.zip"
unused_files=("backup_noroot.c" "header_set_main_dir_with_wsl.c" "header_get_config_dir.c" "header_get_config_file_path.c" "updater_stable.c")
zip_files=("WSL_install.bat" "Enable_WSL.bat" "README.md" "fastboot-assistant_${VERSION}_${ARCHITECTURE}.deb")

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


