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

// '&' that the terminal wait
void open_terminal_by_desktop() 
{
    char *desktop = getenv("XDG_CURRENT_DESKTOP");

    // check desktop
    if (desktop != NULL) 
    {
        // GNOME
        if (strstr(desktop, "GNOME") != NULL) 
        {
            system("gnome-terminal &");
        }
        
        // KDE Plasma
        else if (strstr(desktop, "KDE") != NULL) 
        {
            system("konsole &");
        }
        
        // Xfce
        else if (strstr(desktop, "X-Cinnamon") != NULL) 
        {
            system("gnome-terminal &");
        }
        
        // LXDE/LXQt
        else if (strstr(desktop, "LXDE") != NULL || strstr(desktop, "LXQt") != NULL) 
        {
            system("lxterminal &");
        }
        
        // MATE
        else if (strstr(desktop, "MATE") != NULL) 
        {
            system("mate-terminal &");
        }
    }
}
