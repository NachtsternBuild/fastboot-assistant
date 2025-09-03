#!/bin/bash
# build-snap-flatpak.sh
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

	rm -f "$build_dir_snap/fastboot-assistant.desktop"
	cp -r "$desktop_snap_dir/fastboot-assistant.desktop" "$build_dir_snap/"
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

