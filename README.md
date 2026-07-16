# fastboot-assistant
## Description
Program to facilitate the installation of custom ROMs and GSIs on Android devices. Based on GTK and Shell.

<p align="center">
  <img src="https://github.com/NachtsternBuild/fastboot-assistant/blob/main/images/sweet_unix.png" alt="sweet_unix"/>
</p>


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
- **[fastboot-assistant v.0.8.1.9](https://github.com/NachtsternBuild/fastboot-assistant/releases/tag/v.0.8.1.9)** → Linux (Ubuntu/Debian) / Linux (Snap) / Windows via WSL
---
## Notes
- Use at your own risk.
- The device may be damaged.
- Not every device supports all of the functions
- Not all operating system variants have the same range of functions.
- The programme is currently in the **test phase**. *Errors may occur in the programme.*

## Examples Images
<table>
  <tr>
    <td><img src="https://github.com/NachtsternBuild/fastboot-assistant/blob/main/images/fastboot-assistant.png"/></td>
    <td><img src="https://github.com/NachtsternBuild/fastboot-assistant/blob/main/images/Flashen.png"/></td>
    <td><img src="https://github.com/NachtsternBuild/fastboot-assistant/blob/main/images/Neustart.png"/></td>
  </tr>
  <tr>
    <td><img src="https://github.com/NachtsternBuild/fastboot-assistant/blob/main/images/Vorbereitungen.png"/></td>
    <td><img src="https://github.com/NachtsternBuild/fastboot-assistant/blob/main/images/info.png"/></td>
    <td><img src="https://github.com/NachtsternBuild/fastboot-assistant/blob/main/images/Einrichtung1.png"/></td>
  </tr>
</table>


---

## Some brownies
- *A big thank you to:*
  - **@mrrfv → [Open Android Backup](https://github.com/mrrfv/open-android-backup)**
  - **@Jean28518**
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
- `libnotify`
- `libvte-2.91-gtk4`
- `glib2.0`
- 

These are installed automatically with the Debian package.
***Root rights are required for installation.***

Install the Debian package using the PPA
---
**This method only works for the following OS:**
- `Ubuntu 24.04 Noble Numbat`
- `Ubuntu 25.04 Plucky Puffin`
- `Ubuntu 25.10 Questing Quokka`
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
*see build: <https://github.com/NachtsternBuild/fastboot-assistant/tree/main/src>*
