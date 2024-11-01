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
 *              reboot_recovery				 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

#define MAX_BUFFER_SIZE 256

// Callback functions for each button
// start reboot_recovery adb-function
static void start_recovery_adb(GtkWidget *widget, gpointer data) 
{
    g_print("Log: start_recovery_adb\n");
    const char *title, *message;
    title = "Reboot Recovery";
    message = "Beachten sie, dass USB-Debugging aktiviert ist in den Entwickleroptionen!\n";    
    show_message_with_title(title, message);
    
    char *device_command = adb_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot recovery", device_command);
    system(command);
    free(device_command);  
    g_print("Log: end start_recovery_adb\n");
}

// start reboot_recovery fastboot
static void start_recovery_fastboot(GtkWidget *widget, gpointer data) 
{
    g_print("Log: start_recovery_fastboot\n");
    const char *message = "Beachten sie, dass sich ihr Gerät im Fastboot-Modus befindet!\n";
    show_message(message);
    
    char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot recovery", device_command);
    system(command);
    free(device_command);
    g_print("Log: end start_recovery_fastboot\n");
}

/* main function of reboot*/
void reboot_recovery(int argc, char *argv[]) 
{
    g_print("Log: reboot_recovery\n");
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[2][30] = {"Neustart von ADB", "Neustart von Fastboot"};

    gtk_init(&argc, &argv);

    gtk_init(&argc, &argv);
    apply_theme();

     // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Neustart Recovery");
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
                g_signal_connect(button, "clicked", G_CALLBACK(start_recovery_adb), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_recovery_fastboot), NULL);
                break;
        }
    }
	// cleaing the provider
    g_object_unref(provider);

    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();
    g_print("Log: end reboot_recovery\n");
}
