#! /bin/bash
# build.sh

make
make clean

rm -r ~/Projekt-122
mkdir ~/Projekt-122
cp Projekt-122-l ~/Projekt-122/
cp setup.sh ~/Projekt-122/
cp update.sh ~/Projekt-122/
cp README.md ~/Projekt-122/
cp Changelog.md ~/Projekt-122/
cp INSTALL.md ~/Projekt-122/
cp UNINSTALL.md ~/Projekt-122/
cp CLEAN.sh ~/Projekt-122/
cp CLEAN_AFTER_UPDATE.sh ~/Projekt-122/
cp sweet_unix.png ~/Projekt-122/
cp Projekt-122-l.desktop ~/Projekt-122/
tar -cJvf Projekt-122.tar.xz ~/Projekt-122
