/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - erase_data				 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

char erase_data_command[2048];

// Function to erase user data
void erase_data(GtkWidget *widget, gpointer data) 
{
    g_print("Log: erase_data\n");
    apply_language();
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";

    // show message
    show_message(message);
    
    // Erase user data and metadata
    char *device_command = fastboot_command();
    snprintf(erase_data_command, sizeof(erase_data_command), "%s erase userdata", device_command);
    // I don't now if you need this command
    // system("fastboot erase metadata");
    g_print("Log: Run: %s", erase_data_command);
    command_with_spinner(erase_data_command);
    free(device_command);
    g_print("Log: end erase_data\n");
}

