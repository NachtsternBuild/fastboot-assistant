/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - get_devices			 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h> 
#include "program_functions.h"
#include "function_header.h"

#define MAX_BUFFER_SIZE 256

// Callback functions for each button
// check connected adb devices
static void get_adb(GtkWidget *widget, gpointer data) 
{
    const char *device_command = adb_command();
    char command[MAX_BUFFER_SIZE];
    snprintf(command, MAX_BUFFER_SIZE, "%s devices", device_command);
    connected_devices(command, "Verbundene Geräte über ADB");
    free(device_command);
}

// check connected fastboot devices
static void get_fastboot(GtkWidget *widget, gpointer data) 
{
    const char *device_command = fastboot_command();
    char command[MAX_BUFFER_SIZE];
    snprintf(command, MAX_BUFFER_SIZE, "%s devices", device_command);
    connected_devices(command, "Verbundene Geräte über Fastboot");
    free(device_command);
}

/* main function of get_devices*/
void get_devices(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[2][20] = {"ADB", "Fastboot"};

    gtk_init(&argc, &argv);
    apply_theme();

    // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Geräte:");
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
    for (int i = 0; i < 2; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);

        // execute css-provider for all buttons
        add_css_provider(button, provider);
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(get_adb), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(get_fastboot), NULL);
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
