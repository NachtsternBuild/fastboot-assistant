# Makefile - fastboot-assistant
# Sweet Unix

# to compile use gcc
CC = gcc
# with some extras
CFLAGS = -Wall `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
# the headers
HEADERS =	flash_function_header.h \
			file_chooser_header.h \
			instruction_header.h \
			program_functions.h \
			function_header.h 

# the source files
# this is an experimental file
# header_get_info.c \
# all prepare functions
SRCS =	header_connected_devices.c \
		header_delete_files_in_dir.c \
		header_execute_command.c \
		header_open_terminal_by_desktop.c \
		header_show_file_chooser.c \
		header_show_message.c \
		header_show_message_with_title.c \
		header_check_active_slot.c \
		header_get_slot.c \
		header_get_home.c \
		get_devices.c \
		reboot_fastboot.c \
		reboot.c \
		reboot_recovery.c \
		reboot_heimdall.c \
		reboot_GUI.c \
		config-projekt_GUI.c \
		make_dir.c \
		remove_old.c \
		preflash_GUI.c \
		backup_function.c \
		backup_root.c \
		backup_noroot.c \
		prepare.c \
		rename_boot.c \
		rename_recovery.c \
		rename_vendor.c \
		rename_system.c \
		rename_payload.c \
		unxz_files.c \
		erase_data.c \
		lock_unlock_bootloader.c \
		set_active_slot.c \
		flash_recovery.c \
		flash_boot.c \
		flash_vendor.c \
		flash_system.c \
		flash_payload.c \
		flash_vbmeta_dtbo.c \
		flash_preloader_super.c \
		flash_data.c \
		flash_other.c \
		flash_GUI.c \
		instruction_adb.c \
		instruction_recovery.c \
		instruction_root.c \
		instruction_vendor.c \
		instruction_gsi.c \
		instruction_custom_rom.c \
		instruction_flash.c \
		instruction_backup.c \
		instruction_preflash.c \
		instruction_prepare_flash.c \
		instruction_info.c \
		instruction_GUI.c \
		info.c \
		updater.c \
		about.c \
		GUI.c \
		
OBJS = $(SRCS:.c=.o)
TARGET = Projekt-122-l

all: $(TARGET)

$(TARGET): $(OBJS) $(HEADERS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

# make clean
clean:
	rm -f *.o 

