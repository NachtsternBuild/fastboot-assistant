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
 *         Headerpart - open_url			 *
 *											 *
 *-------------------------------------------*
 */

#include <stdlib.h>
#include <gtk/gtk.h>

void open_url(const char *url)
{
    char url_command[256];

    // use the command 'start' and 'xdg-open' to open the website in the browser    
#if defined(_WIN32)
    sprintf(url_command, "start %s", url);
#elif defined(__linux__)
    sprintf(url_command, "xdg-open %s", url);
#endif

    // run command
    system(url_command);
}
