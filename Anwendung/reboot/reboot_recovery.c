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
 *              reboot_recovery				 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

#define MAX_BUFFER_SIZE 256

// Callback functions for each button
// start reboot_recovery adb-function
static void start_recovery_adb(GtkWidget *widget, gpointer data) 
{
    LOG_INFO("start_recovery_adb");
    const char *message = strcmp(language, "de") == 0 ? "Beachten sie, dass USB-Debugging aktiviert ist in den Entwickleroptionen!" : "Please note that USB debugging is activated in the developer options!";    
    show_message(message);
    
    auto_free char *device_command = adb_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot recovery", device_command);
    command_with_spinner(command);
    LOG_INFO("end start_recovery_adb");
}

// start reboot_recovery fastboot
static void start_recovery_fastboot(GtkWidget *widget, gpointer data) 
{
    LOG_INFO("start_recovery_fastboot");
    const char *message = strcmp(language, "de") == 0 ? "Beachten sie, dass sich ihr Gerät im Fastboot-Modus befindet!" : "Please note that your device is in fastboot mode!";
    show_message(message);
    
    auto_free char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot recovery", device_command);
    command_with_spinner(command);
    LOG_INFO("end start_recovery_fastboot");
}

// Function to set up button labels based on the language
void set_button_labels_reboot_recovery(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Restart ADB");
        strcpy(labels[1], "Restarting Fastboot");
    }
    
    else
    {
    	strcpy(labels[0], "Neustart von ADB");
    	strcpy(labels[1], "Neustart von Fastboot");
    }
} 


/* main function of reboot*/
void reboot_recovery(int argc, char *argv[]) 
{
    LOG_INFO("reboot_recovery");
    GtkWidget *window, *grid, *button;
    char button_labels[2][30];
    
    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_reboot_recovery(button_labels);
    
    window = gtk_window_new();
    const char *reboot_reco_window = strcmp(language, "de") == 0 ? "Neustart Recovery" : "Reboot Recovery";
    gtk_window_set_title(GTK_WINDOW(window), reboot_reco_window);
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
                g_signal_connect(button, "clicked", G_CALLBACK(start_recovery_adb), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_recovery_fastboot), NULL);
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
    
    LOG_INFO("end reboot_recovery");
}
