#!/bin/bash
# build-deb-debuild.sh
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

# Function that build the debian package with debuild
debian_package_build_debuild() {
	echo "[⧗] Start Debian package build..."
	echo "[⧗] Build mode: debuild"
	echo "[⧗] Define vars for the DEB..."
	debian_dir="${source_dir}/debian"
	PKG_NAME="fastboot-assistant"
	MAINTAINER="Elias Mörz <elias.moerz@mail.de>"
	MAINTAINER_NAME="Elias Mörz"
	DESCRIPTION="GUI for flashing Android devices using Fastboot or Heimdall."
	LONG_DESCRIPTION=" Fastboot Assistant provides a graphical interface for flashing devices,\n installing recoveries, and managing partitions using Android Fastboot or Samsung Heimdall protocols."
	SECTION="utils"
	PRIORITY="optional"
	ICON="sweet_unix"
	DESKTOP="fastboot-assistant"
	export LC_TIME=C
	DATE=$(date --date='today' +"%a, %d %b %Y %H:%M:%S %z")

	echo "[⧗] Create /debian structure..."
	mkdir -p "$debian_dir"

	echo "[⧗] Create control..."
	DEPENDS="adb, fastboot, xz-utils, unzip, zip, wget, curl, pkexec, libgtk-4-1 (>= 4.10), heimdall-flash, heimdall-flash-frontend, xdg-desktop-portal, xdg-desktop-portal-gtk, xdg-utils, libadwaita-1-0 (>= 1.6), \${misc:Depends}"
	BUILD_DEPENDS="debhelper-compat (= 13), rsync, libgtk-4-dev (>= 4.10), libadwaita-1-dev, libsecret-1-dev, pkgconf, gcc (>= 14), make (>= 4.0)"

	# correct standard version
	STANDARD_VERSION_DEBUILD="4.6.2"
	ARCHITECTURE="amd64"
	HOMEPAGE="https://github.com/NachtsternBuild/fastboot-assistant"

# control
cat > "${debian_dir}/control" <<EOF
Source: $PKG_NAME
Section: $SECTION
Priority: $PRIORITY
Maintainer: $MAINTAINER
Build-Depends: $BUILD_DEPENDS
Standards-Version: $STANDARD_VERSION_DEBUILD
Homepage: $HOMEPAGE

Package: $PKG_NAME
Architecture: $ARCHITECTURE
Depends: $DEPENDS
Description: $DESCRIPTION
$LONG_DESCRIPTION
EOF

	echo "[⧗] Create changelog..."
	URGENCY="medium"

cat > "${debian_dir}/changelog" <<EOF
$PKG_NAME (${VERSION_DEBUILD}ubuntu${PATCH}) $BRANCH; urgency=$URGENCY

  * $CONTENT

 -- $MAINTAINER  $DATE
EOF

	echo "[⧗] Create copyright..."
cat > "${debian_dir}/copyright" <<EOF
Copyright (C) $(date +%Y) $MAINTAINER_NAME

License: Apache 2.0
EOF
	# create source/format
	echo "[⧗] Create source/format..."
	mkdir -p "${debian_dir}/source"
	echo "3.0 (native)" > "${debian_dir}/source/format"
	
	# create manpage
	echo "[⧗] Create manpage..."
	MANPAGE_DIR="${debian_dir}/manpages"
	mkdir -p "$MANPAGE_DIR"

	# ENGLISH manpage (fastboot-assistant.1)
	echo "[⧗] Create EN manpage..."
cat > "${debian_dir}/fastboot-assistant.1" <<'EOF'
.TH fastboot-assistant 1 "May 2025" "Version 0.8.1.5" "User Manual"
.SH NAME
fastboot-assistant \- assists in flashing custom ROMs on Android devices
.SH SYNOPSIS
.B fastboot-assistant
.SH DESCRIPTION
This program simplifies the installation of custom ROMs, GSIs, and firmware on Android devices.
It provides a modern GTK interface and supports tools like ADB, Fastboot, and Heimdall.
.SH AUTHOR
Elias Mörz <elias.moerz@mail.de>
.SH LICENSE
Apache License 2.0
.SH FILES
~/.config/fastboot-assistant/auto.txt
.RS
Indicates whether dark mode is enabled automatically (libadwaita).
.RE
~/.config/fastboot-assistant/dark.txt
.RS
Explicit dark mode override setting.
.RE
~/.config/fastboot-assistant/config.txt
.RS
Used for first-time setup and general configuration.
.RE
~/.config/fastboot-assistant/version.txt
.RS
Stores the current installed version.
.RE
~/.config/fastboot-assistant/path_config.txt
.RS
Specifies the path from which ROMs or firmware files are flashed.
.RE
~/.config/fastboot-assistant/log.txt
.RS
Contains logs of all actions performed by Fastboot-Assistant.
.RE

EOF

	# GERMAN manpage (fastboot-assistant.de.1)
	echo "[⧗] Create DE manpage..."
cat > "${debian_dir}/fastboot-assistant.de.1" <<'EOF'
.TH fastboot-assistant 1 "Mai 2025" "Version 0.8.1.5" "Benutzerhandbuch"
.SH NAME
fastboot-assistant \- assistiert beim Flashen von Custom-ROMs auf Android-Geräten
.SH SYNOPSIS
.B fastboot-assistant
.SH BESCHREIBUNG
Dieses Programm erleichtert die Installation von Custom-ROMs, GSIs und Firmware auf Android-Geräten.
Es bietet eine moderne GTK-Oberfläche und unterstützt Tools wie ADB, Fastboot und Heimdall.
.SH AUTOR
Elias Mörz <elias.moerz@mail.de>
.SH LIZENZ
Apache License 2.0
.SH KONFIGURATIONSDATEIEN
~/.config/fastboot-assistant/auto.txt
.RS
Gibt an, ob der Dunkelmodus automatisch aktiviert wird (libadwaita).
.RE
~/.config/fastboot-assistant/dark.txt
.RS
Explizite Einstellung für den Dunkelmodus.
.RE
~/.config/fastboot-assistant/config.txt
.RS
Dient für die Ersteinrichtung und allgemeine Konfiguration.
.RE
~/.config/fastboot-assistant/version.txt
.RS
Speichert die aktuell installierte Version.
.RE
~/.config/fastboot-assistant/path_config.txt
.RS
Legt den Pfad fest, von dem ROMs oder Firmware-Dateien geflasht werden.
.RE
~/.config/fastboot-assistant/log.txt
.RS
Enthält alle Protokolleinträge des Fastboot-Assistants.
.RE

EOF

	# create install
	echo "[⧗] Create install..."
cat > "${debian_dir}/install" <<EOF
build_project/fastboot-assistant usr/bin/
desktop/fastboot-assistant.desktop usr/share/applications/
icons/sweet_unix.png usr/share/icons/hicolor/256x256/apps/
style/style_dark.css usr/share/fastboot-assistant/
style/style_light.css usr/share/fastboot-assistant/
icons/sweet_unix.png usr/share/fastboot-assistant/
build_project/po/LC_MESSAGES/en.mo /usr/share/locale/en/LC_MESSAGES/en.mo
build_project/po/LC_MESSAGES/de.mo /usr/share/locale/de/LC_MESSAGES/de.mo
build_project/po/LC_MESSAGES/ru.mo /usr/share/locale/ru/LC_MESSAGES/ru.mo
build_project/po/LC_MESSAGES/sp.mo /usr/share/locale/sp/LC_MESSAGES/sp.mo
build_project/po/LC_MESSAGES/pt.mo /usr/share/locale/pt/LC_MESSAGES/pt.mo
build_project/po/LC_MESSAGES/fr.mo /usr/share/locale/fr/LC_MESSAGES/fr.mo
debian/fastboot-assistant.1 usr/share/man/man1/
debian/fastboot-assistant.de.1 usr/share/man/de/man1/
EOF

	echo "[⧗] Create rules..."
cat > "${debian_dir}/rules" <<'EOF'
#!/usr/bin/make -f

%:
	dh $@

override_dh_auto_build:
	export CCACHE_DISABLE=1 
	rm -rf build_project
	mkdir -p build_project
	for dir in header Build config_projekt reboot flash preflash instructions updater \
	           header/flash header/UI header/commands header/config header/directory \
	           header/message header/spinner header/theme header/partition header/language \
	           flash/others main preflash/backup preflash/prepare po; do \
		rsync -av --update --exclude '.git/' --exclude='*/' --exclude='*.md' "$$dir/" build_project/ ; \
	done
	$(MAKE) -C build_project
	$(MAKE) -C build_project mo-all
EOF

	chmod +x "${debian_dir}/rules"
	echo "[✓] All files are created."

	prompt_user "$(tr build_debuild)"
	read -p " " answer
	if [[ "$answer" =~ ^[jJyY]$ ]]; then
    	echo "[⧗] Start build..."
    	if debuild -us -uc; then
        	echo "[✓] Build Debian-Package completed."
    	else
        	error_msg "Error with building."
        	exit 1
    	fi
    else 
    	echo "[x] No build."
    fi
	echo "[✓] Build completed."
}

