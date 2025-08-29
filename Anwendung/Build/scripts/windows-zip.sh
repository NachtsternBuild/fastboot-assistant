#!/bin/bash
# windows-zip.sh
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

# build windows zip
windows_zip_build() {
	echo "[⧗] Start building zip-file..."
	echo "[⧗] Changing to $windows_dir..."
	cd "$windows_dir"
	echo "[⧗] Copy files..."
	cp "$source_dir/fastboot-assistant_${VERSION}_${ARCHITECTURE}.deb" "$windows_dir"
	# create zip-file
	echo "[⧗] Build zip-file..."
	zip -r "$zip_name" "${zip_files[@]}"
	echo "[✓] Files were successfully packed in $zip_name."
}
