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
 *       Headerfile - file_chooser_header	 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "function_header.h"

// headerguards
#ifndef FILE_CHOOSER_HEADER
#define FILE_CHOOSER_HEADER

// Type definition for a function that processes a file
typedef void (*FileProcessorFunc)(const gchar *filename);

// the functions
void rename_boot(const gchar *bo_filename);
void rename_recovery(const gchar *rec_filename);
void rename_vendor(const gchar *ven_filename);
void rename_system(const gchar *sys_filename);
void rename_payload(const gchar *pay_filename);
void unxz_files(const gchar *xz_filename);

#endif
