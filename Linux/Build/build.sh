#!/bin/bash
# build.sh

rm -r ~/Projekt-122-Build
mkdir ~/Projekt-122-Build

cd ~/Projekt-122/Linux/
# get version for github
# create version.txt
# content
inhalt="0.4"
# name
dateiname="version.txt"

# write content to file
echo "write file..."
echo "$inhalt" > "$dateiname"

echo "File '$dateiname' created with content '$inhalt'."

make
make clean

cp Projekt-122-l ~/Projekt-122-Build/
cp update.sh ~/Projekt-122-Build/
cp rename.sh ~/Projekt-122-Build/
cp version.txt ~/Projekt-122-Build/

cd ~/Projekt-122/Linux/Build/
cp build.sh ~/Projekt-122-Build/
cp setup.sh ~/Projekt-122-Build/
cp README.md ~/Projekt-122-Build/
cp Changelog.md ~/Projekt-122-Build/
cp INSTALL.md ~/Projekt-122-Build/
cp UNINSTALL.md ~/Projekt-122-Build/
cp CLEAN.sh ~/Projekt-122-Build/
cp CLEAN_AFTER_UPDATE.sh ~/Projekt-122-Build/
cp sweet_unix.png ~/Projekt-122-Build/
cp Projekt-122-l.desktop ~/Projekt-122-Build/

# create tar
tar -cJvf ~/Projekt-122.tar.xz -C ~/Projekt-122-Build .

