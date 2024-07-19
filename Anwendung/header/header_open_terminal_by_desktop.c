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
 *              Headerpart - start_terminal	 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// run a command in terminal via system()
void run_command(const char *command) 
{
    if (command != NULL) 
    {
        // use system()
        system(command);
    }
}

// function 'open-terminal-by-desktop'
void open_terminal_by_desktop(const char *function_command) 
{
    char *desktop = getenv("XDG_CURRENT_DESKTOP");
    char command[512];

    // get desktop
    if (desktop != NULL) 
    {
        // GNOME
        if (strstr(desktop, "GNOME") != NULL) 
        {
            snprintf(command, sizeof(command), "gnome-terminal -- bash -c '%s; exec bash'", function_command);
        }
        // KDE Plasma
        else if (strstr(desktop, "KDE") != NULL) 
        {
            snprintf(command, sizeof(command), "konsole -e bash -c '%s; exec bash'", function_command);
        }
        // Xfce
        else if (strstr(desktop, "X-Cinnamon") != NULL) 
        {
            snprintf(command, sizeof(command), "gnome-terminal -- bash -c '%s; exec bash'", function_command);
        }
        // LXDE/LXQt
        else if (strstr(desktop, "LXDE") != NULL || strstr(desktop, "LXQt") != NULL) 
        {
            snprintf(command, sizeof(command), "lxterminal -e bash -c '%s; exec bash'", function_command);
        }
        // MATE
        else if (strstr(desktop, "MATE") != NULL) 
        {
            snprintf(command, sizeof(command), "mate-terminal -- bash -c '%s; exec bash'", function_command);
        }
        else 
        {
            fprintf(stderr, "Unsupported desktop environment: %s\n", desktop);
            return;
        }

        // run command
        run_command(command);
    }
    else 
    {
        fprintf(stderr, "Desktop environment not found.\n");
    }
}
