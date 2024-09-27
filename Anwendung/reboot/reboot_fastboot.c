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
 *              reboot_fastboot				 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main program */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

#define MAX_BUFFER_SIZE 256

// reboot to bootloader from adb
static void reboot_from_adb(GtkWidget *widget, gpointer data)
{
    const char *title, *message;
    
    title = "Reboot from ADB";
    message = "Beachten sie, dass USB-Debugging aktiviert ist in den Entwickleroptionen!\n";
    show_message_with_title(title, message);
    
    char *device_command = adb_command();
    char command[256];
    snprintf(command, sizeof(command), "%s -d reboot bootloader", device_command);
    open_terminal_by_desktop(command);
    free(device_command);
    // this is the old command
    // system("adb reboot bootloader");
}

// reboot to bootloader from fastboot
static void reboot_from_fastboot(GtkWidget *widget, gpointer data)
{
    const char *message = "Beachten sie, dass sich ihr Gerät im Fastboot-Modus befindet!\n";
    show_message(message);
    
    char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot bootloader", device_command);
    open_terminal_by_desktop(command);
    free(device_command);
}
	
// start help-function
static void fastboot_help(GtkWidget *widget, gpointer data) 
{
    const char *message = "Beachten sie, dass sich ihr Gerät im Fastboot-Modus befindet!\n";
    show_message(message);
    
    char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s help", device_command);
    open_terminal_by_desktop(command);
    free(device_command);
}

// get bootloader variablen-function
static void list_bootloader_var(GtkWidget *widget, gpointer data) 
{
    const char *message = "Beachten sie, dass sich ihr Gerät im Fastboot-Modus befindet!\n";
    show_message(message);
    
    char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s getvar all", device_command);
    open_terminal_by_desktop(command);
    free(device_command);
}

/* start main programm */
void reboot_fastboot(int argc, char *argv[])
{
	GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[4][30] = {"Neustart von ADB", "Neustart von Fastboot", "Fastboot Hilfe", "Bootloader Variablen"};

    gtk_init(&argc, &argv);
    apply_theme();

     // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Neustart Fastboot");
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
    for (int i = 0; i < 4; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 2, i / 2, 1, 1);

        // execute css-provider for all buttons
        add_css_provider(button, provider);
        
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(reboot_from_adb), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(reboot_from_fastboot), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(fastboot_help), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(list_bootloader_var), NULL);
                break;          
        }
    }
	// cleaning the provider
    g_object_unref(provider);

    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();
}

