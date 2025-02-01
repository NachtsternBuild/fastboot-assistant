# fastboot-assistant 
## Application development
---
### Status:
- **v.0.7.2:** *dev* → on work
- **v.0.7.1:** *beta* → testing
- **v.0.6.2.1:** *stable*
- **v.0.5.5.2:** *stable*
---
  
### Build
1. Download the source code:
```sh
git clone https://github.com/NachtsternBuild/fastboot-assistant.git
```
2. Install *GCC, GTK, ADB/Fastboot, desktop-file-utils, make, dpkg-dev, debhelper, ccache*:

```sh
# Debian / Ubuntu:
sudo apt update && sudo apt install gcc libgtk-4-dev adb fastboot desktop-file-utils make dpkg-dev debhelper ccache
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
4. Edit the source code with an editor of your choice according to your requirements. *Note that the Makefile must also be changed if you change the name.
5. Change to the directory *Applications*:
   ```sh
   cd ~/fastboot-assistant/Anwendungen
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
 
## Program structure
- It is worth taking a look at the program structure.
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
	  |				|– flash_others.c ----------------------|
	  |				 					|– flash_list_images.c
	  |				 					|– flash_images.c			
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
	  |– updater.c –––––––––––––––––|
          |                             |– updater_stable.c
          |                             |– updater_devmode.c
	  |
	  |– post_update.c
	  |– info_tools.c
	  |– about.c
	  |– run_first_setup.c
	  |
	  |– /header –––––––––––––––––––| 
	  |				|– header_connected_devices.c
	  |				|– header_delete_files_in_dir.c
	  |				|– header_execute_command.c
	  |				|– header_open_terminal_by_desktop.c
	  |				|– header_show_message.c
	  |				|– header_show_message_with_title.c
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
	  |				|– header_on_window_destroy.c
	  |				|– header_loading_spinner.c
	  |				|– header_next_page.c
	  |				|– header_show_file_chooser.c
	  |				|– header_install_with_pkexec.c
	  |				|– header_language_check.c
	  |				|– header_command_adb_fastboot.c
          |                             |– header_write_log.c
          |                             |– header_program_dir.c
          |                             |– header_get_config_dir.c
          |                             |– header_get_config_file_path.c
	  |				|
	  |				|– function_header.h
	  |				|– flash_function_header.h
	  |				|– program_functions.h
	  |				|– instruction_header.h
	  |				|– file_chooser_header.h
	  |				|– loading_spinner.h
	  |				|– language_check.h
	  |
	  |  
	  + Build/Makefile
	  + Build/build-fastboot-assistant.sh ← by @Jean28518, thank you
	  |
	  + /deb/DEBIAN/control ← by @Jean28518, thank you
	  + /deb/DEBIAN/install ← by @Jean28518, thank you
	  |
	  + /snap/snapcraft.yaml
	  + /snap/io.github.nachtsternbuild.Fastboot-Assistant.appdata.xml
	  |
	  + /flatpak/io.github.nachtsternbuild.Fastboot-Assistant.desktop
	  + /flatpak/io.github.nachtsternbuild.Fastboot-Assistant.metainfo.xml
	  + /flatpak/io.github.nachtsternbuild.Fastboot-Assistant.yml
	  |
	  + /Windows/Enable_WSL.bat
	  + /Windows/WSL_install.bat
	  + /Windows/Adaptations of some program parts for WSL
	  |
	  + fastboot-assistent.desktop ← by @Jean28518, thank you
	  + version.txt
	  + sweet_unix.png
	  |
	  + /rpmbuild/SPECS/fastboot-assistant.spec

	  						
```
