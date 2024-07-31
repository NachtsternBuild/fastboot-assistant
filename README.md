# fastboot-assistant
## Description
Programme to facilitate the installation of custom ROMs and GSIs on Android devices. Based on GTK and Shell.

## Functions
- Check the ADB/Fastboot connection
- Create a working directory
- change to the working directory
- boot into fastboot mode
- Reboot from fastboot mode
- Reboot into download mode
- boot into recovery
- open/wipe the bootloader 
- delete user data
- Rename files (recovery.img, boot.img, vendor.img, system.img, vbmeta.img)
- flashing recovery.img, boot.img, init_boot.img, vendor_boot.img, vendor.img, system.img, vbmeta.img, dtbo.img, preloader.img, preloader.bin, super.img and many others

## Versions
*<https://github.com/NachtsternBuild/fastboot-assistant/releases>*
- ***see Changelog.md for all changes or just GitHub.***

### Sweet Unix v.0.5.x
- **fastboot-assistant (noch Projekt-122-l) v.0.5.1.dev** → Linux (Ubuntu/Debian) / Windows via WSL (still experimental)

### Effervescent PC cooling v.0.4.x
- *Projekt-122-l v.0.4.1.beta* → Linux
- *Projekt-122-l v.0.4.beta* → Linux

### Sparkling data crystals v.0.3.x
- *Projekt-122-l v.0.3.beta* → für Linux Debian/Ubuntu

## Notes
- Use at your own risk.
- The device may be damaged.
- Not every device supports all of the functions
- Not all operating system variants have the same range of functions.
- The programme is currently in the **test phase**. *Errors may occur in the programme.*

## Installation of the programme
The following tools are required to run the programme.
- *Android Debug Bridge (adb)* 
- *Fastboot*
- *xz-utils*
- *unzip*
- *wget*
- *heimdall*

These are installed automatically with the Debian package.
*Root rights are required for installation.*
- **Install the Debian package in the terminal with:** 
```sh
sudo apt-get install /PATH/to/fastboot-assistant.deb 
```
***or via a graphical user interface.***

##  Removing fastboot-assistant
1. open terminal
2. Execute the following command:
```sh
sudo dpkg -r --force-all Projekt-122-l
```

## Further information
- see instructions in the applications themselves

## In case of errors
- Don't be shy, just complain. 
- Or do it better (*see build*)
## build
*see build: <https://github.com/NachtsternBuild/fastboot-assistant/tree/main/Anwendung>*
