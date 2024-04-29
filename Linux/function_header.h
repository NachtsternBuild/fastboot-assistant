/*
 *-------------------------------------------*
 *            Projekt 122 - Header 	         *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  - functionheader		 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "flash_function_header.h"

#ifndef FUNCTION_HEADER_H
#define FUNCTION_HEADER_H

void adb_check();
void make_dir();
void change_dir();
void boot_recovery();
void boot_fastboot();
void reboot_fastboot();
void lock_unlock_bootloader();
void erase_data();
void rename_function();
void flash_GUI();
void flash_recovery();
void flash_boot();
void flash_vendor();
void flash_system();
void flash_payload();
void flash_vbmeta();
void update_function();
void remove_old();
void info();
void about(); 

#endif
