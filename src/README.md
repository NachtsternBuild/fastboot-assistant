# fastboot-assistant 
## Application development
---
### Status:
- **v.0.9.1:** *dev*
---
  
### Build
1. Install *GCC, GTK, ADB/Fastboot, desktop-file-utils, make, dpkg-dev, debhelper, ccache, git, libadwaita-1-dev, rsync*:

```sh
# Debian / Ubuntu:
sudo apt update && sudo apt install xz-utils unzip zip wget curl pkexec adb fastboot heimdall-flash heimdall-flash-frontend desktop-file-utils libglib2.0-0t64 libgtk-4-1 xdg-desktop-portal xdg-desktop-portal-gtk xdg-utils libadwaita-1-0 libvte2.91-gtk4-0 libnotify-bin debhelper rsync libgtk-4-dev libadwaita-1-dev libsecret-1-dev git libglib2.0-dev libnotify-dev pkgconf gcc make libvte-2.91-gtk4-dev
```

2. Download the source code:
```sh
git clone https://github.com/NachtsternBuild/fastboot-assistant.git
```

3. For the Snap build you need this tools: *qtbase5-dev, qtchooser, qt5-qmake, qtbase5-dev-tools, snapcraft, lxd*
```sh
# Debian / Ubuntu:
sudo apt update && sudo apt install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
# 1. Install snapcraft:
sudo snap install snapcraft --classic
# 2. Install lxd:
sudo snap install lxd
# 3. Add yourself to the group for lxd
sudo usermod -a -G lxd $USER
# 4. Reboot your system
sudo reboot
# 5. Run this command to init lxd
lxd init --minimal
```

4. Edit the source code with an editor of your choice according to your requirements. *Note that the Makefile must also be changed if you change the name.*
5. Change to the directory *Applications*:
```sh
cd ~/fastboot-assistant/Anwendung
```

6. Compile the code use:
```sh
make
```
- Before running the first build:
```sh
make -f Dependencies.mk
```

7. Clean after the build:
```sh
make clean
```

8. Test the app:
```sh
./fastboot-assistant
# for debugging:
./fastboot-assistant -d
# debugging as snap
./fastboot-assistant -d -snp
# debugging as flatpak
./fastboot-assistant -d -flp
# show version
./fastboot-assistant -v
# show help
./fastboot-assistant -h
```

9. Build Snap package:
```sh
snapcraft pack
```

10. Build Debian Package:
```sh
./build-fastboot-assistant.sh
debuild -us -uc
``` 

**Note:**
- *Building the WSL package only works on **Debian/Ubuntu systems**, as the build script automatically builds a Debian package.*
- **Some features are not yet fully functional, as this version is still under development.**

