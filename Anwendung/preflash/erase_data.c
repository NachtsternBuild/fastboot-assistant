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
 *      (C) Copyright 2025 Elias Mörz 		 *
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
    LOG_INFO("erase_data");
    apply_language();
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = strcmp(language, "de") == 0 ? "Kein Gerät erkannt." : "No device detected.";
        show_error_message(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";

    // show message
    show_message(message);
    
    // Erase user data and metadata
    auto_free char *device_command = fastboot_command();
    snprintf(erase_data_command, sizeof(erase_data_command), "%s erase userdata", device_command);
    // I don't now if you need this command
    // system("fastboot erase metadata");
    LOG_INFO("Run: %s", erase_data_command);
    command_with_spinner(erase_data_command);
    LOG_INFO("end erase_data");
}

