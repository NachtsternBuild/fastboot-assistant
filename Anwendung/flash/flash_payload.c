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
 *              flash_payload				 *
 *											 *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

static void button_flash_payload(GtkWidget *widget, gpointer data)
{
    // flash payload.zip via adb sideload
    GtkWidget *dialog;
    const char *title, *message;
    
    // first dialog called 'Hinweis'
    title = "Hinweis";
    message = "Der Prozess zum flashen des payload.zip geht davon aus, dass sie sich im Recovery befinden und 'Updates über ADB erlauben' aktiviert haben.\n";
    show_message_with_title(title, message);
    
    // Show a message that the flash is starting
    snprintf(message, sizeof(message), "Sideload payload.zip.\n");
    show_message(message);
    
    char image_path[512];
    set_main_dir_with_wsl(image_path, sizeof(image_path), "payload.zip");

    char function_command[255];
    snprintf(function_command, sizeof(function_command), "adb sideload %s && exit", image_path);
    g_print(function_command);
    open_terminal_by_desktop(function_command);

    // Show a message that the flash is completed
    snprintf(message, sizeof(message), "Sideload beendet!\n");
    show_message(message);
}

// UI for flashsystem
void flash_payload(int argc, char *argv[])
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Flash payload.zip");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create an entry for entering the filename
    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 5);

    // Create a button
    GtkWidget *button_payload = gtk_button_new_with_label("Flash starten");
    g_signal_connect(button_payload, "clicked", G_CALLBACK(button_flash_payload), entry);
    gtk_box_pack_start(GTK_BOX(vbox), button_payload, FALSE, FALSE, 5);

    // Show all the widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}
