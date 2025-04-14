# fastboot-assistant 
## Application development
---
### Status:
- **v.0.8.1:** **beta**
- **v.0.7.2:** *stable*
- **v.0.7.1:** *beta* 
- **v.0.6.2.2:** *stable*
- **v.0.5.5.2:** *stable*
---
  
### Build
1. Install *GCC, GTK, ADB/Fastboot, desktop-file-utils, make, dpkg-dev, debhelper, ccache, git, libadwaita-1-dev, rsync*:

```sh
# Debian / Ubuntu:
sudo apt update && sudo apt install gcc libgtk-4-dev adb fastboot desktop-file-utils make dpkg-dev debhelper ccache libsecret-1-dev build-essential libadwaita-1-dev rsync git
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

6. Compile the code:
```sh
bash Build/build-fastboot-assistant.sh
```
- The project can be built for the following operating systems:
	- Linux
 	- Windows (WSL)
  
*The following package types are available for Linux:*
- Debian package
- Snap

*For Windows, a zip file is packed which contains the Debian package included for the WSL.*

**Note:**
*→ Building the WSL package only works on **Debian/Ubuntu systems**, as the build script automatically builds a Debian package.*

