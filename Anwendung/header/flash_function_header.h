/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              Headerfile					 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

#ifndef FLASH_HEADER_H
#define FLASH_HEADER_H

void flash_recovery();
void flash_boot();
void flash_vendor();
void flash_payload();
void flash_system();
void flash_vbmeta_dtbo();
void flash_preloader();
void flash_data();
void flash_others();

#endif
