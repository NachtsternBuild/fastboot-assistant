/**
* functions.h
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
* Usage:
* #include "functions.h"
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "atlbase.h"
#include "flash.h"
#include "fa_helper.h"
#include "instructions.h"

// main function
void activate_fastboot_assistant(GtkApplication* app, gpointer user_data);


// function for the header - GUI
void get_devices();
void reboot_GUI();
void config_projekt_GUI();
void preflash_GUI();
void flash_GUI();
void instruction_GUI();
void treble_updater(); 

// setup functions
int post_update_helper();
void post_update();
void program_dir();
void rm_rom_install();

// function for the header - other GUIs
// info functions
void info();
void info_tools();

// function for updater
void updater(GtkWidget *widget, gpointer stack);
void local_updater();
void ppa_updater();

// for reboot_GUI
void reboot_fastboot();
void reboot();
void reboot_recovery();
void reboot_heimdall();

// for config-projekt
void make_dir();
void remove_old();
void wsl_config();

// for preflash_GUI
void backup_function();
void backup_noroot();
void backup_root();
void prepare();
void prepare_function();
void erase_data();
void lock_unlock_bootloader();
void set_active_slot();
void partitions();

// other functions
void run_first_run_setup();

// functions for the filechooser
void rename_boot(const gchar *bo_filename);
void rename_recovery(const gchar *rec_filename);
void rename_vendor(const gchar *ven_filename);
void rename_system(const gchar *sys_filename);
void rename_payload(const gchar *pay_filename);
void unxz_files(const gchar *xz_filename);


#ifdef __cplusplus
}
#endif

#endif // FUNCTIONS_H
