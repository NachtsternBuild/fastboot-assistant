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
 *              reboot_heimdall				 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main program */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

#define MAX_BUFFER_SIZE 3072

// reboot to download from adb
static void reboot_from_adb_heimdall(GtkWidget *widget, gpointer data)
{
    g_print("Log: reboot_from_adb_heimdall\n");
    const char *message = strcmp(language, "de") == 0 ? "Beachten sie, dass USB-Debugging aktiviert ist in den Entwickleroptionen!" : "Please note that USB debugging is activated in the developer options!";
    show_message(message);
    
    char *device_command = adb_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot download", device_command);
    system(command);
    free(device_command);
    g_print("Log: end reboot_from_adb_heimdall\n");
}

// heimdall help
static void heimdall_help(GtkWidget *widget, gpointer data)
{ 
    g_print("Log: heimdall_help\n");
    open_terminal_by_desktop("heimdall help");
    g_print("Log: end heimdall_help\n");
}
	
// get pit
static void get_pit(GtkWidget *widget, gpointer data) 
{
	g_print("Log: get_pit");
    const char *message = strcmp(language, "de") == 0 ? "Beachten sie, dass sich ihr Gerät im Download-Modus befindet!" : "Please note that your device is in download mode!";
    show_message(message);
    
    open_terminal_by_desktop("heimdall print-pit");
    g_print("Log: end get_pit\n");
}

// Function to set up button labels based on the language
void set_button_labels_reboot_heim(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Restart in Download");
        strcpy(labels[1], "Help");
        strcpy(labels[2], "Output pit");
    } 
    
    else 
    {
        strcpy(labels[0], "In Download neustarten");
        strcpy(labels[1], "Hilfe");
        strcpy(labels[2], "Pit ausgeben");
    }
}

/* start main programm */
void reboot_heimdall(int argc, char *argv[])
{
	g_print("Log: reboot_heimdall\n");
	GtkWidget *window, *grid, *button;
    char button_labels[4][30];
    
    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_reboot_heim(button_labels);
    
    window = gtk_window_new();
    const char *reboot_heim_window = strcmp(language, "de") == 0 ? "Neustart (heimdall)" : "Reboot (heimdall)";
    gtk_window_set_title(GTK_WINDOW(window), reboot_heim_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);
    
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), grid);
    
    for (int i = 0; i < 3; i++) 
    {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);
        
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(reboot_from_adb_heimdall), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(heimdall_help), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(get_pit), NULL);
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
    
    g_print("Log: end reboot_heimdall\n");
}
