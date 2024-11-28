/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - backup_function		 *
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
#include "language_check.h"
#include "program_functions.h"
#include "function_header.h"
#include "loading_spinner.h"

#define MAX_BUFFER_SIZE 256

// include all functions
extern void backup_root();
extern void backup_noroot();
GtkWidget *spinner_backup = NULL;
GtkWidget *spinner_backup_window = NULL;

// Callback functions for each button
// function backup via root
static void start_backup_root(GtkWidget *widget, gpointer data) 
{
    GtkSpinner *spinner_backup = GTK_SPINNER(data);  // Get the spinner_backup from the callback data

    start_loading_spinner(spinner_backup);  // Start the spinner
    
    // Run the backup process with a spinner in a separate thread
    run_with_spinner((void *)backup_root);
    
    stop_loading_spinner(spinner_backup);  // Stop the spinner when the process finishes
}

// function backup with no root
static void start_backup_noroot(GtkWidget *widget, gpointer data) 
{
    backup_noroot();
}

// Function to set up button labels based on the language
void set_button_labels_backup(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Backup with root");
        strcpy(labels[1], "Backup without root");
    }
    
    else
    {
    	strcpy(labels[0], "Backup mit Root");
    	strcpy(labels[1], "Backup ohne Root");
    }
} 

/* main function of the backup_function */
void backup_function(int argc, char *argv[]) 
{
    g_print("Log: backup_function\n");
    GtkWidget *window, *grid, *button;
    char button_labels[2][30];
    
    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_backup(button_labels);
    
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Backup");
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
                g_signal_connect(button, "clicked", G_CALLBACK(start_backup_root), spinner_backup);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_backup_noroot), NULL);
                break;
        }
    }
    
     // free the provider
	if (provider != NULL) 
	{
	    g_object_unref(provider);
	}
	
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop); 
    
    g_print("Log: end backup_function\n");
}
