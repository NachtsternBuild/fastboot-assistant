# fastboot-assistant 
## Anwendungsentwicklung
### Status
- **stabil**
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
4. wechseln sie in das Verzeichnis *Anwendungen*:
   ```sh
   cd ~/fastboot-assistant/Anwendungen
   ```

5. Kompilieren sie den Code und bauen sie das Debian-Paket oder RPM ausführen:
```sh
bash Build/build-fastboot-assistant.sh
```
- Das Projekt kann für folgende Betriebsysteme gebaut werden:
	- Linux
 	- Windows (WSL)
*Für Linux stehen folgende Paketarten zur Verfügung:*
- Debian-Paket
- RPM  
*Für Windows wird ein Zip-Datei gepackt, die das für die WSL enthaltene Debian-Paket enthält.**
**Hinweis:**
*→ Das WSL Paket bauen funktioniert nur auf **Debian/Ubuntu-Systemen**, da der Build-Skript automatisch ein Debian-Packet baut.*
 
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
	  |				|– wsl_config.c
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
	  |				|– partitions.c
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
	  |– run_first_setup.c
	  
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
	  |				|– header_button_finish.c
	  |				|– header_flash_heimdall.c
	  |				|– header_flash_image.c
	  |				|– header_command_adb_fastboot.c
	  |				|– header_command_with_spinner.c
	  |				|– header_convert_wsl_path.c
	  |				|– header_css_provider.c
	  |				|– header_dark_theme.c
	  |				|– header_directory_exists.c
	  |				|– header_get_home_dir_flash.c
	  |				|– header_show_error_message.c
	  |				|– header_install_with_root.c
	  |				|– header_loading_spinner.c
	  |				|– header_next_page.c
	  |				|– header_show_file_chooser.c
	  |				|
	  |				|– function_header.h
	  |				|– flash_function_header.h
	  |				|– program_functions.h
	  |				|– instruction_header.h
	  |				|– file_chooser_header.h
	  |				|– loading_spinner.h
	  |
	  |  
	  + Build/Makefile
	  + Build/build-fastboot-assistant.sh ← by @Jean28518, thank you
	  
	  + Enable_WSL.bat
	  + WSL_install.bat
	  + Anpassungen einiger Programmteile für Windows
	  
	  + fastboot-assistent.desktop ← by @Jean28518, thank you
	  + /deb/DEBIAN/control ← by @Jean28518, thank you
	  + /deb/DEBIAN/install ← by @Jean28518, thank you
	  + version.txt
	  + sweet_unix.png
	  + /rpmbuild/SPECS/fastboot-assistant.spec
	  						
```
