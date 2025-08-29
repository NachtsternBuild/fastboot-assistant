#!/bin/bash
# compile.sh
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
    # building the .po files to .mo files
	echo "[⧗] Building language files..."
	language_build

    # cleaning after the build
    clean_build
    
}

# function for clean after build
clean_build() {
	while true; do
        prompt_user "$(tr cleanup_prompt)"
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
                build_info "$(tr invalid_input)"
                ;;
        esac
    done
}


