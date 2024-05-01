#!/bin/sh
# setup.sh
# setup Projekt-122-l

set -e
SCRIPTPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

# install depends
install_depends() {
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
        echo "Unkown packagemanager." >&2
        exit 1
    fi

    # Install neofetch
    case $package_manager in
        apt-get)
            sudo apt-get update
            sudo apt-get install neofetch
            sudo apt-get install -y desktop-file-utils
            sudo apt-get install adb
            sudo apt-get install fastboot
            ;;
        dnf)
            sudo dnf install neofetch
            sudo dnf install -y desktop-file-utils
            sudo dnf install -y android-tools
            ;;
        yum)
            sudo yum install epel-release # only if EPEL-repo isn't installed
			sudo yum install neofetch
			sudo yum install -y desktop-file-utils
			sudo yum install android-tools
            ;;
        pacman)
            sudo pacman -S neofetch
            sudo pacman -S --noconfirm desktop-file-utils
            sudo pacman -S --noconfirm android-tools
            ;;
    esac
}

# install depends
echo "Get depends..."
echo "projekt-122-l: desktop-file-utils adb fastboot"
echo "Installing desktop-file-utils..."
echo "Installing ADB/Fastboot..."
install_depends
echo "Installation complete."

# add desktop entry
echo "Add desktop entry for Projekt-122..."
if ! command -v desktop-file-edit >/dev/null 2>&1 ; then
  echo "If you would like to create a desktop entry for Projekt-122, please install the desktop-file-utils package and run this script again"

else
  DESKTOPFILE=$SCRIPTPATH/Projekt-122-l.desktop
  desktop-file-edit --set-key=Exec --set-value=$SCRIPTPATH/Projekt-122-l $DESKTOPFILE
  desktop-file-edit --set-key=Icon --set-value=$SCRIPTPATH/sweet_unix.png $DESKTOPFILE
  #sudo desktop-file-install $DESKTOPFILE  # to install for all users
  desktop-file-install --dir=$HOME/.local/share/applications $DESKTOPFILE
  echo "Created desktop entry for Projekt-122"
fi

neofetch
echo "-------------------------------------------------------"
echo "              Setup for Projekt-122   			 "
echo "-------------------------------------------------------"
echo "  https://github.com/NachtsternBuild/Projekt-122	 "
echo "-------------------------------------------------------"
echo "           ***Projekt-122 is ready***"
echo "***Do not delete the directory of the of Projekt-122***"
