/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - set_active_slot		 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"
#include "flash_function_header.h"

#define MAX_BUFFER_SIZE 256

char slot_command[2048];

// button 1 - set slot a
static void set_slot_a(GtkWidget *widget, gpointer data)
{
    g_print("Log: set_slot_a\n");
    char *device_command = fastboot_command();
	snprintf(slot_command, sizeof(slot_command), "%s set_active a && %s getvar current-slot", device_command, device_command);
	g_print("Log: run: %s \n", slot_command);
    command_with_spinner(slot_command);
    free(device_command);
    g_print("Log: end set_slot_a\n");
}

// button 2 - set slot b
static void set_slot_b(GtkWidget *widget, gpointer data)
{
    g_print("Log: set_slot_b\n");
    char *device_command = fastboot_command();
	snprintf(slot_command, sizeof(slot_command), "%s set_active b && %s getvar current-slot", device_command, device_command);
	g_print("Log: run:%s \n", slot_command);
    command_with_spinner(slot_command);
    free(device_command);
    g_print("Log: end set_slot_b\n");
}

// Function to set up button labels based on the language
void set_button_labels_slot(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Set 'a'");
        strcpy(labels[1], "Set 'b'");
    } 
    
    else 
    {
        strcpy(labels[0], "Setze 'a'");
        strcpy(labels[1], "Setze 'b'");
    }
}

/* start main programm */
void set_active_slot(int argc, char *argv[])
{
    g_print("Log: set_active_slot\n");
    GtkWidget *window, *grid, *button;
    char button_labels[2][30];
    
    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_slot(button_labels);
    
    window = gtk_window_new();
    const char *slot_window = strcmp(language, "de") == 0 ? "Setzen des aktiven Slots:" : "Set the active slot:";
    gtk_window_set_title(GTK_WINDOW(window), slot_window);
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
                g_signal_connect(button, "clicked", G_CALLBACK(set_slot_a), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(set_slot_b), NULL);
                break;
        }
    }
    
    // free the provider
	if (provider != NULL) 
	{
	    g_object_unref(provider);
	    provider = NULL;
	}
	
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop); 
    
    g_print("Log: end set_active_slot\n");
}
    
