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
 *              Headerpart - changename		 *
 *											 *
 *-------------------------------------------*
 */

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256

// Function to change the filename
int changename(const char *original, const char *newname) 
{
    return rename(original, newname);
}
