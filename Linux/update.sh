#!/bin/sh
# update.sh

REPO_URL="https://github.com/NachtsternBuild/Projekt-122"

set -e
SCRIPTPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

# install neofetch
install_neofetch() {
    local package_manager

    # check packagemanager
    if command -v apt-get &>/dev/null; then
        package_manager="apt-get"
    elif command -v dnf &>/dev/null; then
        package_manager="dnf"
    elif command -v yum &>/dev/null; then
        package_manager="yum"
    elif command -v pacman &>/dev/null; then
        package_manager="pacman"
    else
        echo "Unkown packagemanager. Please install neofetch" >&2
        exit 1
    fi

    # Install neofetch
    case $package_manager in
        apt-get)
            sudo apt-get update
            sudo apt-get install neofetch
            ;;
        dnf)
            sudo dnf install neofetch
            ;;
        yum)
            sudo yum install epel-release # only if EPEL-repo isn't installed
			sudo yum install neofetch
            ;;
        pacman)
            sudo pacman -S neofetch
            ;;
    esac
}

# install desktop file utils
install_desktop_file_utils() {
    local package_manager

    # check packagemanager
    if command -v apt-get &>/dev/null; then
        package_manager="apt-get"
    elif command -v dnf &>/dev/null; then
        package_manager="dnf"
    elif command -v yum &>/dev/null; then
        package_manager="yum"
    elif command -v pacman &>/dev/null; then
        package_manager="pacman"
    else
        echo "Unkown packagemanager. Please install desktop-file-utils." >&2
        exit 1
    fi

    # Install desktop-file-utils
    case $package_manager in
        apt-get)
            sudo apt-get update
            sudo apt-get install -y desktop-file-utils
            ;;
        dnf)
            sudo dnf install -y desktop-file-utils
            ;;
        yum)
            sudo yum install -y desktop-file-utils
            ;;
        pacman)
            sudo pacman -S --noconfirm desktop-file-utils
            ;;
    esac
}

# install adb/fastboot
install_adb_fastboot() {
    local package_manager

    # check packagemanager
    if command -v apt-get &>/dev/null; then
        package_manager="apt-get"
    elif command -v dnf &>/dev/null; then
        package_manager="dnf"
    elif command -v yum &>/dev/null; then
        package_manager="yum"
    elif command -v pacman &>/dev/null; then
        package_manager="pacman"
    else
        echo "Unkown packagemanager. Please install adb and fastboot" >&2
        exit 1
    fi

    # Install adb/fastboot
    case $package_manager in
        apt-get)
            sudo apt-get update
            sudo apt-get install adb
            sudo apt-get install fastboot
            ;;
        dnf)
            sudo dnf install -y android-tools
            ;;
        yum)
            sudo yum install android-tools
            ;;
        pacman)
            sudo pacman -S --noconfirm android-tools
            ;;
    esac
}

# update part
update_part() {
	# rename old files
	echo "Get old files..."
	# add the following path if you need 🖋️👇️
	cd ~/Downloads/Projekt-122/
	mv changelog.md changelog_old.md
	mv README.md README_old.md
	mv sweet_unix.png sweet_unix_old.png 
	mv setup.sh setup_old.sh
	mv update.sh update_old.sh
	mv CLEAN.sh cp CLEAN_old.sh
	mv CLEAN_AFTER_UPDATE.sh CLEAN_AFTER_UPDATE_old.sh
	mv Projekt-122-l.desktop Projekt-122-l_old.desktop
	mv Projekt-122-l old_Projekt-122-l
	
	# delete old desktop entry
	rm ~/.local/share/applications/Projekt-122-l.desktop
		
	# copie new files to working dir
	cd ~/Downloads/UpdateProjekt122/Projekt-122/
		
	# add the following path if you need 🖋️👇️
	echo "Copie files to old path..."
	cp changelog.md ~/Downloads/Projekt-122/
	cp README.md ~/Downloads/Projekt-122/
	cp sweet_unix.png ~/Downloads/Projekt-122/
	cp setup.sh ~/Downloads/Projekt-122/
	cp update.sh ~/Downloads/Projekt-122/
	cp CLEAN.sh ~/Downloads/Projekt-122/
	cp CLEAN_AFTER_UPDATE.sh ~/Downloads/Projekt-122/
	cp Projekt-122-l.desktop ~/Downloads/Projekt-122/
	cp Projekt-122 ~/Downloads/Projekt-122/
	
	# add desktop entry
	echo "Add desktop entry for Projekt-122..."
	if ! command -v desktop-file-edit >/dev/null 2>&1 ; then
  		echo "If you would like to create a desktop entry for Projekt-122, please install the desktop-file-utils package and run this script again"

	else
  		# thanks to the developer of write 
  		DESKTOPFILE=$SCRIPTPATH/Projekt-122-l.desktop
  		desktop-file-edit --set-key=Exec --set-value=$SCRIPTPATH/Projekt-122-l $DESKTOPFILE
  		desktop-file-edit --set-key=Icon --set-value=$SCRIPTPATH/sweet_unix.png $DESKTOPFILE
  		#sudo desktop-file-install $DESKTOPFILE   to install for all users
  		desktop-file-install --dir=$HOME/.local/share/applications $DESKTOPFILE
  		
  		neofetch
		echo "---------------------------------------------------"
		echo "              Updater for Projekt-122   			 "
		echo "---------------------------------------------------"
		echo "  https://github.com/NachtsternBuild/Projekt-122	 "
		echo "---------------------------------------------------"
  		echo "  ***Created desktop entry for Projekt-122***"
	fi

	# clean old files
	cp CLEAN_AFTER_UPDATE.sh ~/Downloads/
	echo "Delete the update-dircetory and old files..."
	echo "Running CLEAN_AFTER_UPDATE.sh..."
	bash CLEAN_AFTER_UPDATE.sh
}

# only a thing for the eyes
install_neofetch

# install depends
echo "Get depends..."
echo "projekt-122-l: desktop-file-utils adb fastboot"
echo "Installing desktop-file-utils..."
install_desktop_file_utils
echo "Installation complete."
echo "Installing ADB/Fastboot..."
install_adb_fastboot
echo "Installation complete."

# get version for github
# create oldversion.txt
# content
inhalt="0.3"
# name
dateiname="oldversion.txt"

# write content to file
echo "Check update-details..."
echo "$inhalt" > "$dateiname"

echo "File '$dateiname' created with content '$inhalt'."

echo "Get update dir..."
echo "Move version to ~/Downloads/UpdateProjekt122/..."
# mkdir are in the Updatefunction of Projekt-122
# and copie the update.sh
mv oldversion.txt ~/Downloads/UpdateProjekt122/
echo "Get version..."
wget -P ~/Downloads/UpdateProjekt122/ "$REPO_URL/releases/latest/download/version.txt" 


# function to compare the version
# path to the files
datei1="~/Downloads/UpdateProjekt122/oldversion.txt"
datei2="~/Downloads/UpdateProjekt122/version.txt"

# get numbers for the file
nummer1=$(cat "$datei1")
nummer2=$(cat "$datei2")

# compare numbers
if [ "$nummer1" == "$nummer2" ]; then
	echo "No update available."
	cd ~/Downloads/
	# add the following path if you need 🖋️👇️
	cp ~/Downloads/Projekt-122/CLEAN.sh ~/Downloads/
	echo "Delete the update dircetory."
	echo "Run CLEAN.sh"
	bash CLEAN.sh
else
	echo "New version found."
	echo "version: $nummer1"
	echo "new version: $nummer2"
	echo "Starting update..."
	
	# kill Projekt-122-l
	# check for the programm
	if [ $# -ne 1 ]; then
    	echo "Programm run: $0 <programmname>"
    	exit 1
	fi

	programmname="Projekt-122-l"

	# check if programm run
	if pgrep -x "$programmname" >/dev/null; then
    	# kill programm
    	pkill -x "$programmname"
    	echo "'$programmname' killed."
	else
    	echo "'$programmname' isn't active."
	fi
	
	echo "Which language do you speak? (Type 'de' for German or 'en' for English)"
	read language

	# select as german language
	if [ "$language" == "de" ]; then
    	echo "de"
    	# download package
		echo "Get Projekt-122-de package..."
		wget -P ~/Downloads/UpdateProjekt122/ "$REPO_URL/releases/latest/download/Projekt-122-de.tar.xz"
	
		# unpack package 
		echo "Unpack file..."
		tar -xvf Projekt-122-de.tar.xz -C ~/Downloads/UpdateProjekt122/
		
		# do update
		update_part()
	
		
    # select as english language
	elif [ "$language" == "en" ]; then
    	echo "en"
    	# download package
		echo "Get projekt-122-en package..."
		wget -P ~/Downloads/UpdateProjekt122/ "$REPO_URL/releases/latest/download/Projekt-122-en.tar.xz"
	
		# unpack package 
		echo "Unpack file..."
		tar -xvf Projekt-122-en.tar.xz -C ~/Downloads/UpdateProjekt122/
	
    	# do update
    	update_part()
    	
	else
    	echo "Invalid language selection"
	fi
fi
