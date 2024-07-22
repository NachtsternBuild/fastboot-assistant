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
void erase_data_start(GtkWidget *widget, gpointer data) 
{
    GtkWidget *dialog;
    const char *message = "!!!Achtung!!!\nBenutzung auf eigene Gefahr!\n!!!Achtung!!!:\nManche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n\nStarte Vorgang um Nutzerdaten zu löschen.";

    // show message
    show_message(message);
    
    // Erase user data and metadata
    system("fastboot erase userdata");
    // I don't now if you need this command
    // system("fastboot erase metadata");
}

// main function for erase data
void erase_data(int argc, char *argv[]) 
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Löschen Nutzerdaten");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create a button
    GtkWidget *button = gtk_button_new_with_label("Löschen");
    g_signal_connect(button, "clicked", G_CALLBACK(erase_data_start), NULL);

    // Pack the button into the box
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    // Show all the widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}

