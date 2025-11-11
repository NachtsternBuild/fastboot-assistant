#!/bin/bash
# cleanup.sh
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

cleanup() {
	while true; do
	echo ""
    prompt_user "$(tr cleanup)"
    echo ""
    read -n1 -s answer
    case "$answer" in
        j|J|y|Y )
            echo "[⧗] Start make clean..."
            make clean
            echo "[✓] Cleanup successful."
            break
            ;;
        n|N )
            echo "[x] No Cleanup."
            break
            ;;
        * )
            build_info "$(tr invalid_input)"
            ;;
    esac
done
}
