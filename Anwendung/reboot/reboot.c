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
 *              reboot						 *
 *											 *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "function_header.h"
#include "file_chooser_header.h"
#include "flash_function_header.h"

// reboot system
static void reboot_system(GtkWidget *widget, gpointer data)
{
    g_print("Log: reboot_system");
    const char *message = "Neustart wird durchgeführt.\n";    
    show_message(message);
    
    // reboot from fastboot
    char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot", device_command);
    free(device_command);
    g_print("Log: end reboot_system");
}

// boot to an image
static void boot_to_image(const gchar *i_filename) 
{
    g_print("Log: boot_to_image");
    gchar *target_directory_image = get_home("~/Downloads/ROM-Install/");
    if (target_directory_image == NULL) 
    {
        g_print("Fehler beim Erweitern des Verzeichnispfads.\n");
        return;
    }

    // create fastboot command
    char *device_command = fastboot_command(); 
    gchar *target_path_image = g_strdup_printf("%s boot %s", device_command, i_filename);
    g_print("Log: command: %s", target_path_image);
    command_with_spinner(target_path_image);

    // free memory
    free(device_command);
    g_free(target_directory_image);
    g_free(target_path_image);
    g_print("Log: end boot_to_image");
}

/* start main programm */
void reboot(int argc, char *argv[])
{
    g_print("Log: reboot");
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[2][30] = {"Neustart System", "Neustart Image(.img)"};

    gtk_init(&argc, &argv);
    apply_theme();

    // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Neustarten");
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
                g_signal_connect(button, "clicked", G_CALLBACK(reboot_system), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(boot_to_image), NULL);
                break;
        }
    }
	
	// clean the storage
    g_object_unref(provider);
    
    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();
    
    g_print("Log: end reboot");
}
