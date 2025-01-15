/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - updater				 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"
#include "function_header.h"

#define MAX_BUFFER_SIZE 256

// include all functions
extern void backup_root();
extern void backup_noroot();

// Callback functions for each button
// function to start the normal updater 
static void start_updater_stable(GtkWidget *widget, gpointer data) 
{
    updater_stable();
}

// function to start the updater with devmode
static void start_updater_devmode(GtkWidget *widget, gpointer data) 
{
    updater_devmode();
}

// Function to set up button labels based on the language
void set_button_labels_updater(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Updater");
        strcpy(labels[1], "Updater (for development)");
    }
    
    else
    {
    	strcpy(labels[0], "Updater");
    	strcpy(labels[1], "Updater (für Entwicklung)");
    }
} 

/* main function of the backup_function */
void updater(int argc, char *argv[]) 
{
    LOG_INFO("updater");
    GtkWidget *window, *grid, *button;
    char button_labels[2][30];
    
    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_updater(button_labels);
    
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Updater");
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
        
         // Connect buttons to corresponding functions
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(start_updater_stable), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_updater_devmode), NULL);
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
    
    LOG_INFO("end updater");
}
