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
2. bearbeiten sie diesen nach ihren Vorstellungen. *Beachten sie, dass das Makefile auch bei Namensänderungen geändert werden muss*
3. Nutzen von der ***build.sh*** oder ***build_deb.sh*** via:
```sh
bash build.sh
# oder
bash build_deb.sh
```

*oder manuell:*

1. Installieren sie GCC, ADB/Fastboot, desktop-file-utils :

```sh
# Debian / Ubuntu:
sudo apt update
sudo apt install build-essential
sudo apt-get install adb
sudo apt-get install fastboot
sudo apt-get install -y desktop-file-utils
```
```sh
# Fedora:
sudo dnf install gcc
sudo dnf install -y android-tools
sudo dnf install -y desktop-file-utils
```
```sh
# Arch:
sudo pacman -Syyu
sudo pacman -S gcc
sudo pacman -S --noconfirm android-tools
sudo pacman -S --noconfirm desktop-file-utils
```
```sh
# Open SUSE:
sudo zypper refresh
sudo zypper install gcc
sudo zypper install android-tools
sudo zypper install desktop-file-utils
```
```sh
# Fedora/SUSE
sudo yum install gcc
sudo yum install android-tools
sudo yum install -y desktop-file-utils
```

2. Kompilieren sie den Code indem sie das Makefile ausführen:
```sh
make
```
3. Ausführbar machen mit:
```sh
chmod +x Projekt-122-l-meineVersion
```
oder mit:
```sh
sudo chmod +x Projekt-122-l-meineVersion
```
4. Aufräumen:
```sh
make clean
```

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
	  |				|			|––––––––– backup_root.sh
	  |				|			|––––––––– backup_noroot.c
	  |				|
	  |				|– prepare_function.c –––––––––––– prepare.sh
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
	  |				|– flash_vbmeta.c 
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
	  |				|
	  |				|– function_header.h
	  |				|– flash_function_header.h
	  |				|– program_functions.h
	  |				|– instruction_header.h
	  |
	  |  
	  + makefile
	  + build.sh
	  + build_deb.sh ← by @Jean28518, thank you
	  
	  + setup_win.bat
	  
	  + fastboot-assistent.desktop ← by @Jean28518, thank you
	  + control ← by @Jean28518, thank you
	  + version.txt
	  + icon.png
	  						
```
