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
 *         Headerpart - directory_exists	 *
 *											 *
 *-------------------------------------------*
 */

#include <stdlib.h> 
#include <gtk/gtk.h>
#include "program_functions.h"

// Check if directory exists
int directory_exists(const char *path) 
{
    char command[2048];
    snprintf(command, sizeof(command), "test -d %s", path);
    return system(command) == 0;
}
