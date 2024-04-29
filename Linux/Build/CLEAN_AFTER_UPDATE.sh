#!/bin/bash
# CLEAN_AFTER_UPDATE.sh

echo "Delete old files..."
cd ~/Downloads/Projekt-122/
rm changelog_old.md
rm README_old.md
rm sweet_unix_old.png
rm setup_old.sh
rm update_old.sh
rm CLEAN_old.sh
rm CLEAN_AFTER_UPDATE_old.sh
rm Projekt-122-l_old.desktop
rm old_projekt-122

cd ~/Downloads/
echo "Delete the Update dircetory..."
rm -r UpdateProjekt122
echo "---------------------------------------------------"
echo "                 CLEAN_AFTER_UPDATE 			 "
echo "---------------------------------------------------"
echo "  https://github.com/NachtsternBuild/Projekt-122	 "
echo "---------------------------------------------------"
echo "You can delete the CLEAN_AFTER_UPDATE.sh at ~/Downloads/"
