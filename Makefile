# Makefile
# Sprudelnde PC-Kühlung

CC = gcc
CFLAGS = -Wall `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
HEADERS =	flash_function_header.h \
			program_functions.h \
			function_header.h 

# update engine need
SRCS =	header_connected_devices.c \
		header_delete_files_in_dir.c \
		header_execute_command.c \
		header_open_terminal_by_desktop.c \
		header_show_message.c \
		header_show_message_with_title.c \
		adb_check.c \
		make_dir.c \
		change_dir.c \
		boot_recovery.c \
		boot_fastboot.c \
		reboot_fastboot.c \
		lock_unlock_bootloader.c \
		erase_data.c \
		rename_function.c \
		flash_recovery.c \
		flash_boot.c \
		flash_vendor.c \
		flash_system.c \
		flash_payload.c \
		flash_vbmeta.c \
		flash_GUI.c \
		update_function.c \
		remove_old.c \
		info.c \
		about.c \
		GUI.c \
		
OBJS = $(SRCS:.c=.o)
TARGET = Projekt-122-l

all: $(TARGET)

$(TARGET): $(OBJS) $(HEADERS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o 

