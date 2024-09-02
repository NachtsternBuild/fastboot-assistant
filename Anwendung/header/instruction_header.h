/*
 *-------------------------------------------*
 *            Projekt 122 - Header 	         *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  - instruction_header	 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// header guards
#ifndef INSTRUCTION_HEADER_H
#define INSTRUCTION_HEADER_H

void instruction_adb();
void instruction_flash();
void instruction_prepare_flash();
void instruction_info();

// function for instruction_flash
void instruction_recovery();
void instruction_root();
void instruction_vendor();
void instruction_gsi();
void instruction_custom_rom();
void instruction_others();

//function for instruction_preflash-function
void instruction_backup();
void instruction_preflash();

#endif
