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
 *         Headerpart - open_url			 *
 *											 *
 *-------------------------------------------*
 */

#include <stdlib.h>
#include <gtk/gtk.h>
// function that open the browser 
void open_url(const char *url)
{
    char url_command[256];

    // check if the program run via wsl
    if (system("grep -q Microsoft /proc/version") == 0) 
    {
        // use the cmd.exe and close it at the end
        sprintf(url_command, "cmd.exe /C start %s", url);
    } 
    
    else 
    {
        // use xdg-open on native linux
        sprintf(url_command, "xdg-open %s", url);
    }

    // run command
    system(url_command);
}

