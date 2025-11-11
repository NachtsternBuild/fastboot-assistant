#!/bin/bash
# build-fastboot-assistant.sh
#
# (C) Copyright 2025 @NachtsternBuild
#
# License: GNU GENERAL PUBLIC LICENSE Version 3
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
build_scripts="build-scripts"

source "$build_scripts/config.sh"
source "$build_scripts/compile.sh"
source "$build_scripts/build-snap-flatpak.sh"
source "$build_scripts/cleanup.sh"

DEB_BUILD_SCRIPT="${source_dir}/deb/build-deb-debuild.sh"

if [ -f "$DEB_BUILD_SCRIPT" ]; then
    source $DEB_BUILD_SCRIPT
fi

# compile files
compile

# select OS 
while true; do
    prompt_user "$(tr package)"
    echo ""
    prompt_user "╭────────────── $(tr select_os) ──────────────╮"
    echo -e "${RED}│            (d) Debian                  │${NC}"
    echo -e "${CYAN}|            (s) Snap                    |${NC}"
    echo -e "${GREEN}|            (f) Flatpak                 |${NC}"
    echo -e "${RED}|               $(tr select_exit)               |${NC}"
    prompt_user "╰────────────────────────────────────────╯"
    read -n1 -s answer
   	echo ""
    case "$answer" in 
        d|D)
        	
        	echo "[✓] End packagebuild."
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
            build_info "$(tr invalid_input)"
        ;;
    esac
done
    
# running cleanup        	
cleanup

