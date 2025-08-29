#!/bin/bash
# build-fastboot-assistant.sh
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

# main script that runs all the other scripts
# error fallback
set -euo pipefail

# main dirs
home_dir="$HOME"
source_dir="$(pwd)"
build_dir="${source_dir}/Build"
build_scripts="${build_dir}/scripts"

# include the other functions
source "${build_scripts}/config.sh"
source "${build_scripts}/language.sh"
source "${build_scripts}/build-language.sh"
source "${build_scripts}/working_dir.sh"
source "${build_scripts}/compile.sh"
source "${build_scripts}/build-deb-simple.sh"
source "${build_scripts}/build-deb-debuild.sh"
source "${build_scripts}/build-deb.sh"
source "${build_scripts}/build-snap-flatpak.sh"
source "${build_scripts}/windows-zip.sh"
source "${build_scripts}/build-os.sh"

# start of the build script
start_info "╔═══════════════════════════════════════════════╗"
start_info "║                                               ║"
start_info "║   Fastboot-Assistant Build script started     ║"
start_info "║                                               ║"
start_info "╚═══════════════════════════════════════════════╝"
echo ""

create_target_dir

# get build target
while true; do
    prompt_user "$(tr build_which_os)"
    echo ""
    prompt_user "╭────────────── $(tr select_os) ──────────────╮"
    echo -e "${CYAN}│         (l) Linux                      │${NC}"
    echo -e "${GREEN}│         (w) Windows via WSL            │${NC}"
    echo -e "${RED}│          $(tr select_exit)                   │${NC}"
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
            echo "[⧗] Start Build for Windows..."
            build_program_windows
            echo -e "${GREEN}[✓] Build for Windows completed.${NC}"
            ;;
        b|B|n|N)
            echo -e "${CYAN}[x] Build script completed.${NC}"
            break
            ;;
        * )
            build_info "$(tr invalid_input)"
            ;;
    esac
done

echo ""
start_info "╔═════════════════════════════════════════════════════════╗"
start_info "║                                                         ║"
start_info "║  [✓] Build script of the Fastboot-Assistant completed!  ║"
start_info "║                                                         ║"
start_info "╚═════════════════════════════════════════════════════════╝"
echo ""
