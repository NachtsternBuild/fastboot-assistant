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
 *              boot_recovery				 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// Function to boot into recovery
void boot_recovery_function(const char *option) 
{
    GtkWidget *dialog;
    const char *title, *message;

    if (strcmp(option, "recovery_fastboot") == 0) 
    {
        title = "Boot von Fastboot";
        message = "Neustart in Recovery\n";
        system("fastboot devices");
        system("fastboot reboot recovery");
    } 
    
    else if (strcmp(option, "recovery_adb") == 0) 
    {
        title = "Boot von der ADB";
        message = "Neustart in Recovery\n";
        system("adb devices");
        system("adb reboot recovery");
    } 
    
    else 
    {
        title = "Unbekannte Option";
        message = "Sie wissen auch nicht was sie wollen, oder?";
    }

    show_message_with_title(title, message);
}

// Callback function when the button is clicked
void button_boot_recovery_start(GtkWidget *widget, gpointer data) 
{
    const char *option = (const char *)data;
    boot_recovery_function(option);
}

void boot_recovery(int argc, char *argv[]) 
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Boot ins Recovery von:");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create buttons
    GtkWidget *button_recovery_fastboot = gtk_button_new_with_label("Fastboot");
    g_signal_connect(button_recovery_fastboot, "clicked", G_CALLBACK(button_boot_recovery_start), "recovery_fastboot");

    GtkWidget *button_recovery_adb = gtk_button_new_with_label("ADB");
    g_signal_connect(button_recovery_adb, "clicked", G_CALLBACK(button_boot_recovery_start), "recovery_adb");

    // Pack buttons into the box
    gtk_box_pack_start(GTK_BOX(vbox), button_recovery_fastboot, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_recovery_adb, TRUE, TRUE, 0);
    
    // Show all the widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}
