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
 *      Headerpart - set_main_dir_with_wsl	 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// Function to set the main directory for the image path
void set_main_dir_with_wsl(char *path, size_t size, const char *filename) 
{
    const char *home_dir = get_home_directory_flash();
    char wsl_dir[512];
    get_wsl_directory(wsl_dir, sizeof(wsl_dir));
    
    // Use the Linux path if available, otherwise use the WSL path
    if (access(home_dir, F_OK) != -1) 
    {
        snprintf(path, size, "%s/Downloads/ROM-Install/%s", home_dir, filename);
    } 
    
    else 
    {
        snprintf(path, size, "%s/%s", wsl_dir, filename);
    }
}

