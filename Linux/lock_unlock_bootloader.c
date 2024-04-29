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
 *              lock_unlock_bootloader		 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// Function to lock or unlock the bootloader
void lock_unlock_bootloader_function(const char *option) 
{
    GtkWidget *dialog;
    const char *title, *message;

    if (strcmp(option, "bootloader_new") == 0) 
    {
        title = "Unlock bootloader new";
        message = "Starte Vorgang um den Bootloader zu öffnen...\nGerät im Fastboot verfügbar:";
        system("fastboot devices");
        printf("Bootloader wird geöffnet...\n");
        system("fastboot flashing unlock");
    } 
    
    else if (strcmp(option, "bootloader_old") == 0) 
    {
        title = "Unlock bootloader old";
        message = "Starte Vorgang um den Bootloader zu öffnen...\nGerät im Fastboot verfügbar:";
        system("fastboot devices");
        printf("Bootloader wird geöffnet...\n");
        system("fastboot oem unlock");
    } 
    
    else if (strcmp(option, "bootloader_lock") == 0) 
    {
        title = "Lock bootloader";
        message = "!!!Achtung!!! Benutzung auf eigene Gefahr!\n!!!Achtung!!!:\nManche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n\nStarte Vorgang um den Bootloader zu schließen...\nGerät im Fastboot verfügbar:";
        system("fastboot devices");
        printf("Bootloader wird geschlossen...\n");
        system("fastboot flashing lock");
    } 
    
    else 
    {
        message = "Und was jetzt?";
    }

    show_message_with_title(title, message);
}

// Callback function when the button is clicked
void button_lock_unlock_bootloader_start(GtkWidget *widget, gpointer data) 
{
    const char *option = (const char *)data;
    lock_unlock_bootloader_function(option);
}

void lock_unlock_bootloader(int argc, char *argv[]) 
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Bootloader Lock/Unlock");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create buttons
    GtkWidget *button_unlock_new = gtk_button_new_with_label("Unlock Bootloader - neue Geräte");
    g_signal_connect(button_unlock_new, "clicked", G_CALLBACK(button_lock_unlock_bootloader_start), "bootloader_new");

    GtkWidget *button_unlock_old = gtk_button_new_with_label("Unlock Bootloader - alte Geräte");
    g_signal_connect(button_unlock_old, "clicked", G_CALLBACK(button_lock_unlock_bootloader_start), "bootloader_old");

    GtkWidget *button_lock = gtk_button_new_with_label("Lock Bootloader");
    g_signal_connect(button_lock, "clicked", G_CALLBACK(button_lock_unlock_bootloader_start), "bootloader_lock");

    // Pack buttons into the box
    gtk_box_pack_start(GTK_BOX(vbox), button_unlock_new, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_unlock_old, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_lock, TRUE, TRUE, 0);

    // Show all the widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}

