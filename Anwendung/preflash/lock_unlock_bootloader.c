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
 *      (C) Copyright 2024 Elias Mörz 		 *
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

#define MAX_BUFFER_SIZE 256

char bootloader_lock_command[2048];

// button 1 - unlock bootloader new
static void bootloader_new(GtkWidget *widget, gpointer data)
{
    const char *title, *message;
    
    title = "Unlock bootloader new";
    message = "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n\nStarte Vorgang um den Bootloader zu öffnen.\n";
    show_message_with_title(title, message);
    
    snprintf(bootloader_lock_command, sizeof(bootloader_lock_command), "fastboot flashing unlock");
    g_print("Führe aus: %s", bootloader_lock_command);
    command_with_spinner(bootloader_lock_command);
}

// button 2 - unlock bootloader old
static void bootloader_old(GtkWidget *widget, gpointer data)
{
    const char *title, *message;
    
    title = "Unlock bootloader old";
    message = "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n\nStarte Vorgang um den Bootloader zu öffnen.";
    show_message_with_title(title, message);
    
    snprintf(bootloader_lock_command, sizeof(bootloader_lock_command), "fastboot oem unlock");
    g_print("Führe aus: %s", bootloader_lock_command);
    command_with_spinner(bootloader_lock_command);
}

// button 3 - lock bootloader
static void bootloader_lock(GtkWidget *widget, gpointer data)
{
    const char *title, *message;
    
    title = "Lock bootloader";
    message = "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n\nStarte Vorgang um den Bootloader zu schließen.";
    show_message_with_title(title, message);
    
    snprintf(bootloader_lock_command, sizeof(bootloader_lock_command), "fastboot flashing lock");
    g_print("Führe aus: %s", bootloader_lock_command);
    command_with_spinner(bootloader_lock_command);
}


/* start main programm */
void lock_unlock_bootloader(int argc, char *argv[])
{
	GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    
    char button_labels[3][30] = {"Öffnen (neu)", "Öffnen (alt)", "Schließen"};

    gtk_init(&argc, &argv);
    apply_theme();
    
    // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Bootloader:");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // create the grid and centre it
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    // add the grid to the window
    gtk_container_add(GTK_CONTAINER(window), grid);

    // add and centre all button
    for (int i = 0; i < 3; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);

        // execute css-provider for all buttons
        add_css_provider(button, provider);
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(bootloader_new), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(bootloader_old), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(bootloader_lock), NULL);
                break;
        }
    }
    
    // clean the storage
    g_object_unref(provider);

    // show window
    gtk_widget_show_all(window);

    // run main gtk loop
    gtk_main();
}

