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
 *              checkadb					 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "flashheader.h"

void showConnectedDevices(const char *command, const char *label) 
{
    char message[512];
    FILE *fp;

    // Execute the command and capture the output
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Fehler beim Öffnen des Prozesses!");
        exit(EXIT_FAILURE);
    }

    // Read the output and display it in the message
    snprintf(message, sizeof(message), "%s:\n", label);
    while (fgets(message + strlen(message), sizeof(message) - strlen(message), fp) != NULL) {}

    // Show the message
    showMessage(message);

    // Close the process
    pclose(fp);
}

void ADBButton() 
{
    showConnectedDevices("adb devices", "Verbundene Geräte über ADB");
}

void FastbootButton() 
{
    showConnectedDevices("fastboot devices", "Verbundene Geräte über Fastboot");
}

// Callback function when the ADB button is clicked
void buttonACa_clicked(GtkWidget *widget, gpointer data) 
{
    ADBButton();
}

// Callback function when the Fastboot button is clicked
void buttonACf_clicked(GtkWidget *widget, gpointer data) 
{
    FastbootButton();
}

void adbcheck(int argc, char *argv[]) 
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
    GtkWidget *buttonACa = gtk_button_new_with_label("ADB");
    GtkWidget *buttonACf = gtk_button_new_with_label("Fastboot");

    g_signal_connect(buttonACa, "clicked", G_CALLBACK(buttonACa_clicked), NULL);
    g_signal_connect(buttonACf, "clicked", G_CALLBACK(buttonACf_clicked), NULL);

    gtk_box_pack_start(GTK_BOX(vbox), buttonACa, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), buttonACf, FALSE, FALSE, 5);

    // Show all the widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}

