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
#include <dirent.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "function_header.h"

// headerguards
#ifndef FILE_CHOOSER_HEADER
#define FILE_CHOOSER_HEADER

// Type definition for a function that processes a file
typedef void (*FileProcessorFunc)(const gchar *filename);

// the functions
void prepare_boot(const gchar *boo_filename);
void prepare_recovery(const gchar *rec_filename);
void prepare_vendor(const gchar *ven_filename);
void prepare_system(const gchar *sys_filename);
void prepare_payload(const gchar *pay_filename);
void unxz_files(const gchar *xz_filename);

#endif
