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
 *              erase_data					 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// Function to erase user data
void erase_data_function() 
{
    GtkWidget *dialog;
    const char *message = "!!!Achtung!!!\nBenutzung auf eigene Gefahr!\n!!!Achtung!!!:\nManche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n\nStarte Vorgang um Nutzerdaten zu löschen.\nGerät im Fastboot verfügbar:";

    // Show the device list
    system("fastboot devices");

    // Erase user data
    system("fastboot erase -w");
	
	// show message
    show_message(message);
}

// Callback function when the button is clicked
void button_erase_data_start(GtkWidget *widget, gpointer data) 
{
    erase_data_function();
}

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
    g_signal_connect(button, "clicked", G_CALLBACK(button_erase_data_start), NULL);

    // Pack the button into the box
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    // Show all the widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}

