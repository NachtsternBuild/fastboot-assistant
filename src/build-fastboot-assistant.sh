#!/bin/bash
# build-fastboot-assistant.sh
#
# (C) Copyright 2025 @NachtsternBuild
#
# License: GNU GENERAL PUBLIC LICENSE Version 3
# 
# build script to generate debian build dateien
# this is a modified version of the bash script, for Debian package and the RPM building from the linux-assistant

# main script that runs all the other scripts
# error fallback
set -euo pipefail

# main dirs
home_dir="$HOME"
source_dir="$(pwd)"
DEB="deb"
BUILD_DEBIAN="$DEB/build-debian-debuild.sh"

"$BUILD_DEBIAN"

