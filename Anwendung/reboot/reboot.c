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
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              reboot						 *
 *											 *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"
#include "function_header.h"
#include "file_chooser_header.h"
#include "flash_function_header.h"

// reboot system
static void reboot_system(GtkWidget *widget, gpointer data)
{
    LOG_INFO("reboot_system");
    const char *message = strcmp(language, "de") == 0 ? "Neustart wird durchgeführt." : "Restart is performed.";    
    show_message(message);
    
    // reboot from fastboot
    auto_free char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot", device_command);
    command_with_spinner(command);
    LOG_INFO("end reboot_system");
}

// boot to an image
static void boot_to_image(const gchar *i_filename) 
{
    LOG_INFO("boot_to_image");
    char boot_image[4096];
    char boot_command[4096];
    get_config_file_path(boot_image, sizeof(boot_image));
    // load the path
    const char *boot_image_path = load_path_from_file(boot_image);

    if (boot_image_path) 
    {
        LOG_INFO("Loaded path: %s", boot_image_path);
    }

    // create fastboot command
    auto_free char *device_command = fastboot_command(); 
    snprintf(boot_command, sizeof(boot_command), "%s boot %s/%s", device_command, boot_image_path, i_filename);
    LOG_INFO("Run: %s \n", boot_command);
    command_with_spinner(boot_command);

    LOG_INFO("end boot_to_image");
}

// Function to set up button labels based on the language
void set_button_labels_reboot(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Reboot System");
        strcpy(labels[1], "Reboot Image(.img)");
    }
    
    else
    {
    	strcpy(labels[0], "Neustart System");
    	strcpy(labels[1], "Neustart Image(.img)");
    }
} 

/* start main programm - reboot*/
void reboot(int argc, char *argv[])
{
	LOG_INFO("reboot");
	GtkWidget *window, *grid, *button;
    char button_labels[2][30];
    
    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_reboot(button_labels);
    
    window = gtk_window_new();
    const char *reboot_window = strcmp(language, "de") == 0 ? "Neustarten" : "Reboot";
    gtk_window_set_title(GTK_WINDOW(window), reboot_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);
    
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), grid);
    
    for (int i = 0; i < 2; i++) 
    {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 2, i / 2, 1, 1);
        
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(reboot_system), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(boot_to_image), NULL);
                break;
        }
    }
	
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop); 
    
    // free the provider
    if (provider != NULL) 
    {
    	g_object_unref(provider);
    	provider = NULL;
	}

	if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
    
    LOG_INFO("end reboot");
}
