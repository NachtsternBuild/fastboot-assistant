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
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// Function to erase user data
void erase_data(GtkWidget *widget, gpointer data) 
{
    GtkWidget *dialog;
    const char *message = "!!!Achtung!!!\nBenutzung auf eigene Gefahr!\n!!!Achtung!!!:\nManche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n\nStarte Vorgang um Nutzerdaten zu löschen.";

    // show message
    show_message(message);
    
    // Erase user data and metadata
    system("fastboot erase userdata");
    // I don't now if you need this command
    // system("fastboot erase metadata");
    const char *message2 = "Fertig!\n";
    // show message
    show_message(message2);
}

