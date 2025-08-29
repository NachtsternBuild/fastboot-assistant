#!/bin/bash
# working_dir.sh
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


# function that create the build-dir
create_target_dir() {
    prompt_user "$(tr create_target)"
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
                build_info "$(tr invalid_input)"
                ;;
        esac
    done
}

