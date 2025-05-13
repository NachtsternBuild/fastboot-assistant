# fastboot-assistant
## Description
Program to facilitate the installation of custom ROMs and GSIs on Android devices. Based on GTK and Shell.

![sweet_unix](https://github.com/NachtsternBuild/fastboot-assistant/blob/main/images/sweet_unix.png)

## Functions
- Check the `ADB`/`Fastboot` connection
- Create a working directory
- change to the working directory
- boot into `fastboot` mode
- Reboot from `fastboot` mode
- Reboot into `download` mode
- boot into `recovery`
- boot to an image
- lock/unlock the bootloader 
- delete user data
- backup your full system with root or use the [Open Android Backup](https://github.com/mrrfv/open-android-backup) → ***thanks to @mrrfv***
- Rename files (`recovery.img`, `boot.img`, `vendor.img`, `system.img`, `payload.zip`)
- flashing `recovery.img`, `boot.img`, `init_boot.img`, `vendor_boot.img`, `vendor.img`, `system.img`, `vbmeta.img`, `dtbo.img`, `userdata.img`, `metadata.img`, `preloader.img`, `preloader.bin`, `super.img` and many others
- flashing all images in a directory
- get device infos
- some instructions for the program
- set active slot
- resize/remove/create boot/vendor/system partition

## Versions
*<https://github.com/NachtsternBuild/fastboot-assistant/releases>*
- ***see [CHANGELOG](https://github.com/NachtsternBuild/fastboot-assistant/tree/main/CHANGELOG) for all changes.***
- ***see the [SECURTIY.md](https://github.com/NachtsternBuild/fastboot-assistant/blob/main/SECURITY.md)***
- ***see the [VERSIONS.md](https://github.com/NachtsternBuild/fastboot-assistant/blob/main/VERSIONS.md)***
- ***see the [BUILDLOG.md](https://github.com/NachtsternBuild/fastboot-assistant/blob/main/BUILDLOG.md) for more information about future versions.***
- 
### Latest
- **[fastboot-assistant v.0.8.1.5](https://github.com/NachtsternBuild/fastboot-assistant/releases/tag/v.0.8.1.5)** → Linux (Ubuntu/Debian) / Linux (Snap) / Windows via WSL
- *[fastboot-assistant v.0.7.2.1](https://github.com/NachtsternBuild/fastboot-assistant/releases/tag/v.0.7.2.1)* → Linux (Ubuntu/Debian) / Linux (Snap) / Windows via WSL
---
### Important Notes
- **With `v.0.6.2.1` and `v.0.7.x` the support for RPM based Linux distributions is discontinued, because there are many missing tools, like `pkexec` or `heimdall`. Hopefully `Snap` and `Flatpak` will be a suitable replacement for the `RPMs`.**
- **It is recommended to run the Fastboot-Assistant natively under Linux, because the WSL does not provide the same amount of tools as the real Ubuntu. *This version should only be used if there is no other option.***
- **The possibility of building the Fastboot Assistant as a `Snap` and `Flatpak` is experimental and has not yet been fully tested. Especially for the construction of the `Flatpak. The dependencies are missing here.**

## Notes
- Use at your own risk.
- The device may be damaged.
- Not every device supports all of the functions
- Not all operating system variants have the same range of functions.
- The programme is currently in the **test phase**. *Errors may occur in the programme.*

## Examples Images
![fastboot-assistant](https://github.com/NachtsternBuild/fastboot-assistant/blob/main/images/fastboot-assistant.png)
![Flashen](https://github.com/NachtsternBuild/fastboot-assistant/blob/main/images/Flashen.png)
![Vorbereitungen](https://github.com/NachtsternBuild/fastboot-assistant/blob/main/images/Vorbereitungen.png)
![Neustart](https://github.com/NachtsternBuild/fastboot-assistant/blob/main/images/info.png)

---

## Some brownies
- *A big thank you to:*
  - **@mrrfv → [Open Android Backup](https://github.com/mrrfv/open-android-backup)**
  - **@Jean28518 → my [build-fastboot-assistant.sh](https://github.com/NachtsternBuild/fastboot-assistant/blob/main/Anwendung/Build/build-fastboot-assistant.sh) is a modified version of *@Jean28518s* version.**
  
## Installation of the programme
Linux
---
The following tools are required to run the programme.
- Android Debug Bridge (`adb`) and `fastboot` 
- `XZ-utils`
- `unzip`
- `zip`
- `wget`
- `curl`
- `pkexec`
- `heimdall`
- `> GTK 4.10`
- `> Libadwaita 1.6`
- `coreutils`
- `libc6`
- `xdg-desktop-portal`
- `xdg-desktop-portal-gtk`
- `xdg-utils`

These are installed automatically with the Debian package.
***Root rights are required for installation.***

Install the Debian package using the PPA
---
**This method only works for the following OS:**
- `Ubuntu 24.04 Noble Numbat`
- `Ubuntu 24.10 Oracular Oriole`
- `Ubuntu 25.04 Plucky Puffin`
**Add the PPA to your device:**
```sh
sudo add-apt-repository ppa:nachtstern12/fastboot-assistant
sudo apt update
```
**Now install the package via `APT`:**
```sh
sudo apt install fastboot-assistant
```
Install the Debian package manuell in the terminal with
---
```sh
sudo apt install /PATH/to/fastboot-assistant.deb
```
***or via a graphical user interface.***

Install the Snap
---
```sh
sudo snap install ~/path/to/the/snap/fastboot-assistant.snap --devmode
```
[![Get it from the Snap Store](https://snapcraft.io/en/dark/install.svg)](https://snapcraft.io/fastboot-assistant)

Windows
---
1. unzip the zip file
2. Follow the steps in the README.md from the Zip

##  Removing fastboot-assistant
1. open terminal
2. Execute the following command:
```sh
# Debian/Ubuntu
sudo apt remove fastboot-assistant
# or if you use snap
sudo snap remove fastboot-assistant
```

## Further information
- see instructions in the applications themselves
- or the dokumentation

## In case of errors
- Don't be shy, just complain. 
- Or do it better (*see **Build***)
  
## Build
*see build: <https://github.com/NachtsternBuild/fastboot-assistant/tree/main/Anwendung>*
