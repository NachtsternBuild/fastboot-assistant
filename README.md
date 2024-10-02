# fastboot-assistant
## Description
Program to facilitate the installation of custom ROMs and GSIs on Android devices. Based on GTK and Shell.

## Functions
- Check the ADB/Fastboot connection
- Create a working directory
- change to the working directory
- boot into fastboot mode
- Reboot from fastboot mode
- Reboot into download mode
- boot into recovery
- lock/unlock the bootloader 
- delete user data
- backup your full system (root) or use the [Open Android Backup](https://github.com/mrrfv/open-android-backup) → ***thanks to @mrrfv***
- Rename files (recovery.img, boot.img, vendor.img, system.img, payload.zip)
- flashing recovery.img, boot.img, init_boot.img, vendor_boot.img, vendor.img, system.img, vbmeta.img, dtbo.img, userdata.img, metadata.img, preloader.img, preloader.bin, super.img and many others
- get device infos
- some instructions for the program
- set active slot
- resize/remove/create boot/vendor/system partition

## Versions
*<https://github.com/NachtsternBuild/fastboot-assistant/releases>*
- ***see [Changelog.md](https://github.com/NachtsternBuild/fastboot-assistant/blob/main/changelog.md) for all changes or just GitHub.***
- ***see the [SECURTIY.md](https://github.com/NachtsternBuild/fastboot-assistant/blob/main/SECURITY.md)***

### Sweet Unix v.0.5.x
- **fastboot-assistant v0.5.5.2** → Linux (Ubuntu/Debain/Fedora/RHEL/CentOS) / Windows via WSL 

## Notes
- Use at your own risk.
- The device may be damaged.
- Not every device supports all of the functions
- Not all operating system variants have the same range of functions.
- The programme is currently in the **test phase**. *Errors may occur in the programme.*

### Some brownies
- *A big thank you to:*
  - **@mrrfv → [Open Android Backup](https://github.com/mrrfv/open-android-backup)**
  - **@Jean28518 → my [build-deb.sh](https://github.com/NachtsternBuild/fastboot-assistant/blob/main/Anwendung/Build/build-fastboot-assistant.sh) is a modified version of *@Jean28518s* version.**
  
## Installation of the programme
### Linux
The following tools are required to run the programme.
- *Android Debug Bridge (adb)* 
- *Fastboot*
- *xz-utils*
- *unzip*
- *wget*
- *heimdall → heimdall must be installed manually on all distributions that use RPMs*

These are installed automatically with the Debian package.
*Root rights are required for installation.*
- **Install the Debian package in the terminal with:** 
```sh
sudo apt-get install /PATH/to/fastboot-assistant.deb 
```
***or via a graphical user interface.***
- **Install the RPM:**
```sh
sudo rpm -i /PATH/to/fastboot-assistant-0.5.5.2-1.fc40.x86_64.rpm
```
### Windows
1. unzip the zip file
2. Follow the steps in the README.md from the Zip

##  Removing fastboot-assistant
1. open terminal
2. Execute the following command:
```sh
# Debian/Ubuntu
sudo dpkg -r --force-all fastboot-assistant
# Fedora/RHEL/CentOS
sudo rpm -e fastboot-assistant
```

## Further information
- see instructions in the applications themselves
- or the dokumentation

## In case of errors
- Don't be shy, just complain. 
- Or do it better (*see build*)
## build
*see build: <https://github.com/NachtsternBuild/fastboot-assistant/tree/main/Anwendung>*
