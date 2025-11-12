/**
* fa_helper.h
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
* Usage:
* #include "fa_helper.h"
*/

#ifndef FA_HELPER_H
#define FA_HELPER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "atlbase.h"

extern GtkWidget *main_window;
extern const char *detected_device;
extern GtkWidget *bootctl_status_label;
extern GtkWidget *root_status_label;
extern bool debug_mode;

/** 
* function, that get the path of the config file
*
* get_config_file_path(config_file, sizeof(config_file));
* printf("Config file path: %s\n", config_file);
*/
void get_config_file_path(char *config_file, size_t size);
/** function that get the config dir
*
* Usage:
* get_config_dir(config_folder, sizeof(config_folder));
* g_print("Config folder path: %s\n", config_folder);
*/
void get_config_dir(char *config_folder, size_t size);


// function that save the config path to a file
void save_path_to_file(const char *path, const char *file_path);
// function to read the path from the config file
char *load_path_from_file(const char *file_path);
// callback for dialog for the dialog and get the setup path
void process_selected_setup_folder(const char *folder_path);


// function that use adb or adb.exe
char* adb_command();
// function that use fastboot or fastboot.exe
char* fastboot_command();


// function that check the device for a/b partition or not
void ab_partition_info();
// function that check if the device are a/b-device
int get_slot_of_device();
// function that get the active slot
void check_active_slot(char *active_slot, size_t size);
// get the active slot with adb
char *get_inactive_slot();


// function to check for connected devices
void connected_devices(const char *command, const char *label);
// check if device are connected
int is_android_device_connected();
// check for device in fastboot
int is_android_device_connected_fastboot();
// check for device in adb
int is_android_device_connected_adb();


// function that create a partition
void create_partition(const char *partition);
// function that remove a partition
void remove_partition(const char *partition);
// function resize the partition
void resize_partition(const char *partition);


// function to flash with heimdall
void flash_heimdall(GtkWidget *widget, const char *partition, const char *image_name);
// function to flash an image
void flash_image(GtkWidget *widget, const char *partition1, const char *partition2, const char *image_name, const char *optional_flags);


// function that write the ab_device.txt
void write_ab_file();
// function that delete the ab_device.txt
void delete_ab_file();
// function that check if there are the ab_device.txt
void check_ab_file();
// function to check for the ab_device.txt and remove this file
void check_ab_file_light();
// function that apply the device typ
void apply_device();


// header that check for root access
void check_root_access(GtkWidget *root_status_label);
// header that check for root access as char
char *check_root_access_char();


// function detect the android bootctl
void get_bootctl(GtkWidget *bootctl_status_label);
// function detect the android bootctl as char
char *get_bootctl_char();


// download the update.conf from the GitHub API
bool download_update_conf();
// create a new child process, that run the update
void spawn_updater_helper(const char *pkg_cmd);

#ifdef __cplusplus
}
#endif

#endif // FA_HELPER_H
