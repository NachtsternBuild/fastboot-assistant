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
#include "language_check.h"
#include "program_functions.h"
#include "function_header.h"
#include "file_chooser_header.h"
#include "flash_function_header.h"

// reboot system
static void reboot_system(GtkWidget *widget, gpointer data)
{
    g_print("Log: reboot_system\n");
    const char *message = strcmp(language, "de") == 0 ? "Neustart wird durchgeführt." : "Restart is performed.";    
    show_message(message);
    
    // reboot from fastboot
    char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot", device_command);
    command_with_spinner(command);
    free(device_command);
    g_print("Log: end reboot_system\n");
}

// boot to an image
static void boot_to_image(const gchar *i_filename) 
{
    g_print("Log: boot_to_image\n");
    gchar *target_directory_image = get_home("~/Downloads/ROM-Install/");
    if (target_directory_image == NULL) 
    {
        g_print("Log: Error when expanding the directory path.\n");
        return;
    }

    // create fastboot command
    char *device_command = fastboot_command(); 
    gchar *target_path_image = g_strdup_printf("%s boot %s", device_command, i_filename);
    g_print("Log: command: %s \n", target_path_image);
    command_with_spinner(target_path_image);

    // free memory
    free(device_command);
    g_free(target_directory_image);
    g_free(target_path_image);
    g_print("Log: end boot_to_image\n");
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
	g_print("Log: reboot\n");
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
    
    g_print("Log: end reboot\n");
}
