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
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              Headerpart - language_check  *
 *											 *
 *-------------------------------------------*
 */
 
#ifndef LANGUAGE_CHECK_H
#define LANGUAGE_CHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <unistd.h>  
#include <sys/stat.h> 
#include <sys/types.h> 
#include "program_functions.h"

void create_directory_if_not_exists_lang(const char *path);
void write_language_file();
void delete_language_file();
void check_language_file();
void check_language_file_light();
void apply_language();
void toggle_language(GtkWidget *button, gpointer user_data);
void toggle_language_setup(GtkWidget *button, gpointer user_data);

#endif // LANGUAGE_CHECK_H

