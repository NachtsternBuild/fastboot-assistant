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
 *              Headerpart - start_terminal	 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <gtk/gtk.h>

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
    char command[2048];

    // check if run as wsl
    if (system("grep -q Microsoft /proc/version") == 0) 
    {
        // use the cmd.exe 
        snprintf(command, sizeof(command), "cmd.exe /C start cmd.exe /K \"%s\"", function_command);
        run_command(command);
        return;
    }

    // use the linux desktop
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
        // Xfce oder Cinnamon
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

        // debugging
        g_print(command);
        // run the command
        run_command(command);
    } 
    
    else 
    {
        fprintf(stderr, "Desktop environment not found.\n");
    }
}
