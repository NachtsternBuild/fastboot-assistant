/*
 *-------------------------------------------*
 *            Projekt 122 - Header 	         *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  - function_header		 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "flash_function_header.h"
#include "instruction_header.h"

// header guards
#ifndef FUNCTION_HEADER_H
#define FUNCTION_HEADER_H

// function for the header - GUI
void get_devices();
void reboot_GUI();
void config_projekt_GUI();
void preflash_GUI();
void flash_GUI();
void instruction_GUI();
void about();
void treble_updater(); 

// setup functions
void wsl_config();
void post_update();
void program_dir();
void write_log();
void rm_rom_install();

// function for the header - other GUIs

// info functions
void info();
void info_tools();

// function for updater
void updater();
void updater_devmode();
void updater_stable();

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

#endif
