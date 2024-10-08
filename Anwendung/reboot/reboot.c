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
 *              reboot						 *
 *											 *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

void reboot_system(GtkWidget *widget, gpointer data)
{
    const char *message = "Neustart wird durchgeführt.\n";    
    show_message(message);
    
    // reboot from fastboot
    char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot", device_command);
    free(device_command);
}
