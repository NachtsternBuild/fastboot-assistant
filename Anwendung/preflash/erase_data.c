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
#include "program_functions.h"

char erase_data_command[2048];

// Function to erase user data
void erase_data(GtkWidget *widget, gpointer data) 
{
    const char *message = "Achtung:\nManche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n";

    // show message
    show_message(message);
    
    // Erase user data and metadata
    snprintf(erase_data_command, sizeof(erase_data_command), "fastboot erase userdata && exit");
    // I don't now if you need this command
    // system("fastboot erase metadata");
    g_print("Führe aus: %s", erase_data_command);
    command_with_spinner(erase_data_command);
}

