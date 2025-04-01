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
 *         Headerpart - open_url			 *
 *											 *
 *-------------------------------------------*
 */

#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// Function that opens the browser
void open_url(const char *url)
{
    char url_command[2048];

    // Check if the program is running in WSL by looking for the /mnt/c/Users directory
    if (directory_exists("/mnt/c/Users")) 
    {
        // Use cmd.exe in WSL and close it at the end
        snprintf(url_command, sizeof(url_command), "cmd.exe /C start %s", url);
    } 
    else 
    {
        // Use xdg-open on native Linux
        snprintf(url_command, sizeof(url_command), "xdg-open %s", url);
    }

    // Run the command
    system(url_command);
}


