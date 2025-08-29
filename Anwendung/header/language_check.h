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
#include <libintl.h>
#include <locale.h>
#include "program_functions.h"

// define gettext macros and the domain
#define _(STRING) gettext(STRING)
#define LOCALE_DOMAIN "fastboot-assistant"

// TODO: replace the old langauge system with the new
// old langauge function, only as backup
// remain in the program until everything has been completely replaced
void create_directory_if_not_exists_lang(const char *path);
void write_language_file();
void delete_language_file();
void check_language_file();
void check_language_file_light();
void apply_language();
//void toggle_language(GtkWidget *button, gpointer user_data);
void toggle_language_setup(GtkWidget *button, gpointer user_data);

// new function that init the language
// this usage the system language or fallback to english
void init_language(void);
// function that set the language manuell
// use: 
// set_language("de");
void set_language(const char *lang);

// additional functions for the language managment
// // function that reads the language from the file
int read_language_file(char *langbuf, size_t size);
// function that writes the language to the file
void write_language_file(const char *lang);
// try to bind local dir and .mo files
void bind_language(const char *lang);
// function that switch the language
void toggle_language(GtkWidget *widget, gpointer stack);

#endif // LANGUAGE_CHECK_H

