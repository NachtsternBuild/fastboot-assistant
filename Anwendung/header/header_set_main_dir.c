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
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *         Headerpart - set_main_dir		 *
 *											 *
 *-------------------------------------------*
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

// Function to construct the full path for an image file in the Downloads directory
void set_main_dir(char *buffer, size_t buffer_size, const char *filename) 
{
    const char *home_dir = getenv("HOME");  // Get the HOME directory
    if (home_dir != NULL) 
    {
        snprintf(buffer, buffer_size, "%s/Downloads/ROM-Install/%s", home_dir, filename);
    } 
    
    else 
    {
        LOG_ERROR("Could not determine the home directory.");
    }
}

