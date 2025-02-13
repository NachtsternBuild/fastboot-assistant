# Makefile - fastboot-assistant
# Sweet Unix

# compiler
CC = ccache gcc

# compiler flags
CFLAGS = -Wall `pkg-config --cflags gtk4 libsecret-1`

# linker flags
LIBS = `pkg-config --libs gtk4 libsecret-1`

# header files
HEADERS = \
	flash_function_header.h \
	language_check.h \
	file_chooser_header.h \
	instruction_header.h \
	loading_spinner.h \
	program_functions.h \
	function_header.h 

# source files
SRCS = \
	header_connected_devices.c \
	header_delete_files_in_dir.c \
	header_execute_command.c \
	header_open_terminal_by_desktop.c \
	header_show_file_chooser.c \
	header_show_message.c \
	header_show_message_with_title.c \
	header_check_active_slot.c \
	header_get_slot.c \
	header_get_home.c \
	header_open_url.c \
	header_set_main_dir.c \
	header_get_home_dir_flash.c \
	header_get_wsl_directory.c \
	header_set_main_dir_with_wsl.c \
	header_show_error_message.c \
	header_flash_image.c \
	header_flash_heimdall.c \
	header_css_provider.c \
	header_dark_theme.c \
	header_next_page.c \
	header_convert_wsl_path.c \
	header_loading_spinner.c \
	header_command_with_spinner.c \
	header_directory_exists.c \
	header_command_adb_fastboot.c \
	header_language_check.c \
	header_install_with_pkexec.c \
	header_on_window_destroy.c \
	header_close_window.c \
	header_delete_config_file.c \
	header_get_config_dir.c \
	header_get_config_file_path.c \
	header_program_dir.c \
	header_download_file.c \
	header_write_log.c \
	header_verify_package_type.c \
	header_check_root_access.c \
	treble_updater.c \
	get_devices.c \
	wsl_config.c \
	post_update.c \
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
	partitions.c \
	flash_recovery.c \
	flash_boot.c \
	flash_vendor.c \
	flash_system.c \
	flash_payload.c \
	flash_vbmeta_dtbo.c \
	flash_preloader_super.c \
	flash_data.c \
	flash_list_images.c \
	flash_images.c \
	flash_others.c \
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
	instruction_others.c \
	instruction_info.c \
	instruction_GUI.c \
	run_first_run_setup.c \
	info.c \
	info_tools.c \
	updater.c \
	updater_devmode.c \
	updater_stable.c \
	about.c \
	GUI.c 

# object files
OBJS = $(SRCS:.c=.o)

# target
TARGET = fastboot-assistant

# standard target
all: $(TARGET)

# create the target
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

# create the object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# clean
clean:
	rm -f $(OBJS) $(TARGET)

