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
 *              reboot_fastboot				 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// Callback function when the button is clicked
void button_reboot_fastboot_start(GtkWidget *widget, gpointer data) 
{
    GtkWidget *dialog;
    const char *message = "Neustart wird durchgeführt...\n";

    // Show the device list
    system("fastboot devices");

    // Reboot into Fastboot
    system("fastboot reboot");
	
	show_message(message);
}

void reboot_fastboot(int argc, char *argv[]) 
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Neustart von Fastboot");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create a button
    GtkWidget *button_reboot_fastboot = gtk_button_new_with_label("Neustart");
    g_signal_connect(button_reboot_fastboot, "clicked", G_CALLBACK(button_reboot_fastboot_start), NULL);

    // Pack the button into the box
    gtk_box_pack_start(GTK_BOX(vbox), button_reboot_fastboot, TRUE, TRUE, 0);

    // Show all the widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}

