#!/bin/bash
# build-deb-simple.sh
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


# function to build the debian package
debian_package_build_simple() {
	local out_dir="$output_dir/locale/$l/LC_MESSAGES"
	echo "[⧗] Start Debian package build..."
	echo "[⧗] Build mode: simple"
	echo "[⧗] Changing to build directory..."
	cd "$source_dir" || { echo "[*] Error with changing to $source_dir"; exit 1; }
	# Remove files from previous build
	echo "[⧗] Delete old build files..."
	rm -r deb/usr/

	# Prepare deb files for packaging
	echo "[⧗] Start building..."
	echo "[⧗] Create required directories..."
	mkdir -p deb/usr/bin/fastboot-assistant
	mkdir -p deb/usr/share/icons/hicolor/256x256/apps/
	mkdir -p deb/usr/share/applications/
	mkdir -p deb/usr/share/fastboot-assistant/
	
	echo "[⧗] Adding language files..."
	for lang in "${SUPPORTED_LANGS[@]}"; do
    	mkdir -p "deb/usr/share/locale/$lang/LC_MESSAGES"
    	cp "$out_dir/$lang.mo" "deb/usr/share/locale/$lang/LC_MESSAGES/"
	done

	echo "[⧗] Copy all files to deb/usr/bin..."
	cp -r "$output_dir/fastboot-assistant" deb/usr/bin/fastboot-assistant/
	echo "[⧗] Copy all files to deb/usr/share/icons/hicolor/256x256/apps/..."
	cp "$build_dir/sweet_unix.png" deb/usr/share/icons/hicolor/256x256/apps/
	echo "[⧗] Copy all files to deb/usr/share/applications/..."
	cp "$build_dir/fastboot-assistant.desktop" deb/usr/share/applications/
	echo "[⧗] Copy all files to deb/usr/share/fastboot-assistant/..."
	cp -r "$output_dir/style_dark.css" deb/usr/share/fastboot-assistant/
	cp -r "$output_dir/style_light.css" deb/usr/share/fastboot-assistant/
	cp -r "$build_dir/sweet_unix.png" deb/usr/share/fastboot-assistant/

	# set authorisations with 'chmod'
	echo "[⧗] Set authorisations..."
	chmod a+x deb/usr/bin/fastboot-assistant
	chmod 755 deb/usr/share/fastboot-assistant/style_dark.css
	chmod 755 deb/usr/share/fastboot-assistant/style_light.css
	for lang in "${SUPPORTED_LANGS[@]}"; do
		chmod 755 "deb/usr/share/locale/$lang/LC_MESSAGES/$lang.mo"
	done
	chmod 755 deb/DEBIAN
	
	# Estimate the installed size by summing the sizes of all files in the deb directory
	echo "[⧗] Set package size..."
	SIZE=$(du -s deb | cut -f1)
	sed -i "s/Installed-Size: .*/Installed-Size: $SIZE/" deb/DEBIAN/control
	
	# Build deb package
	echo "[⧗] Build package..."
	echo "[⧗] Set version..."
	sed -i "2s/.*/Version: $VERSION/" deb/DEBIAN/control
	echo "[⧗] Build DEBIAN package..."
	dpkg-deb --build -Zxz --root-owner-group deb
	mv deb.deb "fastboot-assistant_${VERSION}_${ARCHITECTURE}.deb"
	echo "[✓] Package ready."
}

