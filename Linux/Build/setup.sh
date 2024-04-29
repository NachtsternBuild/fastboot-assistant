#!/bin/sh
# setup.sh
# setup Projekt-122-l

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
    elif command -v zypper &>/dev/null; then
        package_manager="zypper"
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
        zypper)
        	sudo zypper install neofetch
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
    elif command -v zypper &>/dev/null; then
        package_manager="zypper"
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
        zypper)
        	sudo zypper install desktop-file-utils
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
    elif command -v zypper &>/dev/null; then
        package_manager="zypper"
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
        zypper)
        	sudo zypper install android-tools
        	;;
    esac
}

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
