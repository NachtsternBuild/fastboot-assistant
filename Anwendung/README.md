# fastboot-assistant 
## Anwendungsentwicklung
### Status
- ***noch in der Entwicklung***
- ***Es ist noch nicht alles vollständig***
### Build

1. Laden sie den Quellcode herunter:
```sh
git clone https://github.com/NachtsternBuild/fastboot-assistant.git
```
2. Installieren sie *GCC, GTK, ADB/Fastboot, desktop-file-utils, make, dpkg-dev, debhelper, fakeroot, linitian, pbuilder, devscripts*:

```sh
# Debian / Ubuntu:
sudo apt update
sudo apt upgrade
sudo apt-get install build-essential gcc libgtk-3-dev adb fastboot desktop-file-utils make dpkg-dev debhelper fakeroot lintian pbuilder devscripts libsecret-1-dev

# Feodra / RHEL / CentOS
sudo dnf install -y \
    @development-tools \
    gcc \
    gtk3-devel \
    adb \
    fastboot \
    desktop-file-utils \
    rpm-build \
    rpmdevtools \
    make \
    libsecret-devel

```
3. bearbeiten sie den Quellcode mit einem Editor ihrer Wahl nach ihren Vorstellungen. *Beachten sie, dass das Makefile auch bei Namensänderungen geändert werden muss*
4. wechseln sie in das Verzeichnis *Anwendungen*
   ```sh
   cd ~/fastboot-assistant
   ```

5. Kompilieren sie den Code und bauen sie das Debian-Paket oder RPM ausführen:
```sh
bash Build/build-fastboot-assistant.sh
```
**fastboot-assistant kann auch für die WSL als Zip-Datei gepackt werden.**
- Dafür wählen sie nach dem sie den Build-Ordner angelegt haben:
```sh
For which operating system (OS) should the fastboot-assistant be built?
Linux (l) / Windows via WSL (w):
w
```
- Und geben nach dem erfolgreichem Build-Prozess an, dass sie die Zip-Datei bauen möchten.
*→ Das funktioniert nur auf **Debian/Ubuntu-Systemen**, da der Build-Skript automatisch ein Debian-Packet für das Zip baut.*
 
## Programmstruktur
- *Ein Blick auf die Programmstruktur lohnt sich.*
```
GUI.c ––––|
	  |
	  |– get_device.c
	  |
	  |– reboot_GUI.c ––––––––––––––|
	  |				|– reboot_fastboot.c 
	  |				|– reboot.c 
	  |				|– reboot_recovery.c
	  |				|– reboot_heimdall.c
	  |
	  |
	  |– config_projekt_GUI.c ––––––|
	  |				|– make_dir.c
	  |				|– remove_old.c
	  |
	  |  --------------------------------------------------------------------------------------------------
	  |
	  |– preflash_GUI.c ––––––––––––|
	  |				|– backup_function.c –––|
	  |				|			|––––––––– backup_root.c
	  |				|			|––––––––– backup_noroot.c
	  |				|
	  |				|– prepare.c –––––––––––|
	  |				|			|––--––––– rename_boot.c
	  |				|			|––––––––– rename_recovery.c
	  |				|			|––––––––– rename_vendor.c
	  |				|			|––––––––– rename_system.c
	  |				|			|––––––––– rename_payload.c
	  |				|			|––––––––– unxz_files.c
	  |				|– erase_data.c
	  |				|– lock_unlock_bootloader.c
	  |				|– set_active_slot.c
	  |
	  |– flash_GUI.c –––––––––––––––|
	  |				|– flash_recovery.c 
	  |				|– flash_boot.c 
	  |				|– flash_vendor.c 
	  |				|– flash_system.c  
	  |				|– flash_payload.c 
	  |				|– flash_vbmeta_dtbo.c 
	  |				|– flash_preloader_super.c
	  |				|– flash_data.c
	  |				|– flash_others.c
	  |
	  |– instructions_GUI.c ––––––––|
	  |				|– instruction_adb.c
	  |				|– instruction_flash.c –––––––––––––––––|
	  |				|					|– instruction_recovery.c
	  |				|					|– instruction_root.c
	  |				|					|– instruction_vendor.c
	  |				|					|– instruction_gsi.c
	  |				|					|– instruction_custom_rom.c
	  |				|
	  |				|– instruction_prepare_flash.c –––––––––|
	  |				|					|– instruction_backup.c
	  |				|					|– instruction_preflash.c
	  |				|
	  |				|– instruction_info.c
	  |
	  |  ---------------------------------------------------------------------------------------------------
	  |
	  |– info.c
	  |
	  |– updater.c
	  |
	  |– about.c
	  
	  |– /header –––––––––––––––––––| 
	  |				|– header_connected_devices.c
	  |				|– header_delete_files_in_dir.c
	  |				|– header_execute_command.c
	  |				|– header_open_terminal_by_desktop.c
	  |				|– header_show_message.c
	  |				|– header_show_message_with_title.c
	  |				|– header_get_info.c
	  |				|– header_check_active_slot.c
	  |				|– header_get_slot.c
	  |				|– header_get_home.c
	  |				|– header_show_file_chooser.c
	  |				|– header_flash_heimdall.c
	  |				|– header_flash_image.c
	  |				|– header_get_home_dir_flash.c
	  |				|– header_get_wsl_directory.c
	  |				|– header_open_url.c
	  |				|– header_set_main_dir.c
	  |				|– header_set_main_dir_with_wsl.c
	  |				|– header_show_error_message.c
	  |				|
	  |				|– function_header.h
	  |				|– flash_function_header.h
	  |				|– program_functions.h
	  |				|– instruction_header.h
	  |				|– file_chooser_header.h
	  |
	  |  
	  + Build/Makefile
	  + Build/build-fastboot-assistant.sh ← by @Jean28518, thank you
	  
	  + Enable_WSL.bat
	  + WSL_install.bat
	  
	  + fastboot-assistent.desktop ← by @Jean28518, thank you
	  + /deb/DEBIAN/control ← by @Jean28518, thank you
	  + /deb/DEBIAN/install ← by @Jean28518, thank you
	  + version.txt
	  + icon.png
	  + /rpmbuild/SPECS/fastboot-assistant.spec
	  						
```
