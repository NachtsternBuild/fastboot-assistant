#!/bin/bash
# build-deb.sh
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

# Function were the user choose between deb build simple and debuild
debian_package_build() {
	echo "[⧗] Start Debian package build..."
	echo "[⧗] Select package Debian build mode..."
	while true; do
		prompt_user "$(tr build_deb_which)"
		echo ""
		prompt_user "╭──────────── Debian-Package ────────────╮"
		echo -e "${CYAN}│       (s) Simple                       │${NC}"
	    echo -e "${GREEN}│      (d) Debuild                       │${NC}"
	    echo -e "${RED}│       $(tr select_exit)                      │${NC}"
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
    	        build_info "$(tr invalid_input)"
    	        ;;
    	esac
	done
}
