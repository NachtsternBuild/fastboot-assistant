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
 *         Headerpart - get_wsl_directory	 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// Function to get the WSL equivalent path
void get_wsl_directory(char* wsl_dir, size_t size) 
{
    const char* user = getenv("USER");
    if (!user) 
    {
        g_print("Log: Error: Could not determine the user name.\n");
        exit(1);
    }
    snprintf(wsl_dir, size, "/mnt/c/Users/%s", user);
}
