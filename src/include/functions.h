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
void get_devices(GtkWidget *widget, gpointer stack);
void reboot_GUI(GtkWidget *widget, gpointer stack);
void config_project_GUI(GtkWidget *widget, gpointer stack);
void preflash_GUI(GtkWidget *widget, gpointer stack);
void flash_GUI(GtkWidget *widget, gpointer stack);
void instruction_GUI(GtkWidget *widget, gpointer stack);
void treble_updater(GtkWidget *widget, gpointer stack); 

// setup functions
int post_update_helper();
void post_update();
void program_dir();
void rm_rom_install();

// function for the header - other GUIs
// info functions
void info(GtkWidget *widget, gpointer stack);
void info_tools(GtkWidget *widget, gpointer stack);

// function for updater
void updater(GtkWidget *widget, gpointer stack);
void local_updater();
void ppa_updater();

// for reboot_GUI
void reboot_fastboot(GtkWidget *widget, gpointer stack);
void reboot(GtkWidget *widget, gpointer stack);
void reboot_recovery(GtkWidget *widget, gpointer stack);
void reboot_heimdall(GtkWidget *widget, gpointer stack);

// for config-projekt
void make_dir();
void remove_old(GtkWidget *widget, gpointer stack);
void wsl_config();

// for preflash_GUI
void backup_function(GtkWidget *widget, gpointer stack);
void backup_noroot(GtkWidget *widget, gpointer stack);
void backup_root(GtkWidget *widget, gpointer stack);
void prepare(GtkWidget *widget, gpointer stack);
void prepare_function(GtkWidget *widget, gpointer stack);
void erase_data(GtkWidget *widget, gpointer stack);
void lock_unlock_bootloader(GtkWidget *widget, gpointer stack);
void set_active_slot(GtkWidget *widget, gpointer stack);
void partitions(GtkWidget *widget, gpointer stack);

// other functions
void run_first_run_setup(GtkWidget *widget, gpointer stack);

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
