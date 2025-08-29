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
// dummy
void apply_language();

// function that get the path of the language file
char *get_lang_path();
// function that get the current language
gchar *get_current_language();

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
void toggle_language();



#endif // LANGUAGE_CHECK_H

