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
 *              flashboot					 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main programm */
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "flashheader.h"

// function to flash boot.img
void flashbootfunction()
{
    GtkWidget *dialog;
    char message[512];

    // Show a message that the flash is starting
    snprintf(message, sizeof(message), "Starte Flash des Boot-Images...\n");
    showMessage(message);

    // Show the device list
    system("fastboot devices");

    // Erase and flash the system partition
  	// Get active slot
    const char *fastbootpart = "fastboot getvar current-slot";
    char *bootpartoutput = executeCommand(fastbootpart);
    printf("Der aktive Slot ist: %s\n", bootpartoutput);

    // Flash boot.img on a/b-devices
    if (bootpartoutput[0] == 'a' || bootpartoutput[0] == 'A' || bootpartoutput[0] == 'b' || bootpartoutput[0] == 'B') 
    {
        system("fastboot flash ~/Downloads/ROM-Install/boot_a boot.img");
        system("fastboot flash ~/Downloads/ROM-Install/boot_b boot.img");
        printf("Boot-Image wurde geflasht!\n");
    } 
    
    // flash boot.img on other devices
    else 
    {
        system("fastboot flash boot ~/Downloads/ROM-Install/boot.img");
        printf("Boot-Image wurde geflasht!\n");
    }

    // Show a message that the flash is completed
    snprintf(message, sizeof(message), "Flash beendet!\n");
    showMessage(message);
}

// button clicked callback
void buttonfb_clicked(GtkWidget *widget, gpointer data)
{
    flashbootfunction();
}

// UI for flashboot
void flashboot(int argc, char *argv[])
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Flash Boot");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create an entry for entering the filename
    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 5);

    // Create a button
    GtkWidget *button = gtk_button_new_with_label("Flash Boot-Image");
    g_signal_connect(button, "clicked", G_CALLBACK(buttonfb_clicked), entry);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);

    // Show all the widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}
