#!/bin/bash
# build-snap-flatpak.sh
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


# Function for building the Snap package
build_snap() {
    if [ ! -f "$snapcraft_file" ]; then
        error_msg "Snapcraft file not found: $snapcraft_file"
        exit 1
    fi
	
	chmod +x "${source_dir}/fastboot-assistant"
	
    # Create the snap package using snapcraft
    echo "[⧗] Starting snap build..."
    cd "$build_dir_snap" || { error_msg "Failed to change to $build_dir_snap"; exit 1; }
    snapcraft pack

    if [ -f "$build_dir_snap/${snap_name}_${VERSION}_${ARCHITECTURE}.snap" ]; then
        echo "[✓] Snap package built successfully: $build_dir_snap/${snap_name}_${VERSION}_${ARCHITECTURE}.snap"
    else
        error_msg "Snap build failed."
        exit 1
    fi
    while true; do
		echo ""
    	prompt_user "$(tr cleanup_snap)"
    	echo ""
    	read -n1 -s answer
    	case "$answer" in
    	    j|J|y|Y )
    	        echo "[⧗] Start make clean..."
    	        snapcraft clean
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

# Function for building the Flatpak package
build_flatpak() {
	if [ ! -f "$flatpak_manifest" ]; then
        error_msg "Flatpak manifest file not found: $flatpak_manifest"
        exit 1
    fi
	
	chmod +x "${source_dir}/fastboot-assistant"
	
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

