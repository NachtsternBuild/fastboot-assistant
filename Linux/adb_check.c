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
 *              adb_check					 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main program */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// Callback function when the ADB button is clicked
void button_check_adb_start(GtkWidget *widget, gpointer data) 
{
    connected_devices("adb devices", "Verbundene Geräte über ADB");
}

// Callback function when the Fastboot button is clicked
void button_check_fastb_start(GtkWidget *widget, gpointer data) 
{
    connected_devices("fastboot devices", "Verbundene Geräte über Fastboot");
}

void adb_check(int argc, char *argv[]) 
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Gerät Verbindung");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create buttons
    GtkWidget *button_check_adb = gtk_button_new_with_label("ADB");
    GtkWidget *button_check_fastb = gtk_button_new_with_label("Fastboot");

    g_signal_connect(button_check_adb, "clicked", G_CALLBACK(button_check_adb_start), NULL);
    g_signal_connect(button_check_fastb, "clicked", G_CALLBACK(button_check_fastb_start), NULL);

    gtk_box_pack_start(GTK_BOX(vbox), button_check_adb, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), button_check_fastb, FALSE, FALSE, 5);

    // Show all the widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}

