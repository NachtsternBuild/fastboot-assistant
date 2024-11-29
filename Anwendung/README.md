# fastboot-assistant 
## Application development
---
### Status:
- **v.0.5.5.2:** *stable*
- **v.0.6.2.dev:** *dev*
---
  
### Build
1. Download the source code:
```sh
git clone https://github.com/NachtsternBuild/fastboot-assistant.git
```
2. Install *GCC, GTK, ADB/Fastboot, desktop-file-utils, make, dpkg-dev, debhelper*:

```sh
# Debian / Ubuntu:
sudo apt update && sudo apt install -y gcc libgtk-4-dev adb fastboot desktop-file-utils make dpkg-dev debhelper

# Feodra / RHEL / CentOS
sudo dnf install -y gcc gtk4-devel android-tools desktop-file-utils make rpm-build


```
3. Edit the source code with an editor of your choice according to your requirements. *Note that the Makefile must also be changed if you change the name.
4. Change to the directory *Applications*:
   ```sh
   cd ~/fastboot-assistant/Anwendungen
   ```

5. Compile the code and build the Debian package or run the RPM:
```sh
bash Build/build-fastboot-assistant.sh
```
- The project can be built for the following operating systems:
	- Linux
 	- Windows (WSL)
*The following package types are available for Linux:*
- Debian package
- RPM  
*For Windows, a zip file is packed which contains the Debian package included for the WSL.
**Note:**
*→ Building the WSL package only works on **Debian/Ubuntu systems**, as the build script automatically builds a Debian package.
 
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
