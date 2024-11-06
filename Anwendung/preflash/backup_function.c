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

/* main function of the backup_function */
void backup_function(int argc, char *argv[]) 
{
    g_print("Log: backup_function\n");
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[2][30] = {"Backup mit Root", "Backup ohne Root"};

    gtk_init(&argc, &argv);
    apply_theme();

    // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Backup");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create the grid and center it
    grid = gtk_grid_new();
    
    // Set the grid to homogeneous mode (same width/height for all cells)
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);

    // Set alignment of the grid within the window
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    // Add the grid to the window
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Initialize the spinner and add it to the grid
    spinner_backup = gtk_spinner_new();  // Initialize the spinner
    gtk_grid_attach(GTK_GRID(grid), spinner_backup, 0, 1, 2, 1);  // Attach spinner to grid (span 2 columns)
    gtk_widget_set_halign(spinner_backup, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(spinner_backup, GTK_ALIGN_CENTER);

    // Add and center all buttons
    for (int i = 0; i < 2; i++) 
    {
        button = gtk_button_new_with_label(button_labels[i]);

        // Attach each button to grid, one in each column
        gtk_grid_attach(GTK_GRID(grid), button, i, 0, 1, 1);

        // Set horizontal and vertical alignment for the button
        gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
        gtk_widget_set_valign(button, GTK_ALIGN_CENTER);

        // Apply CSS providerw
        add_css_provider(button, provider);

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

    // clean the storage 
    if (provider != NULL) 
    {
        g_object_unref(provider);
    }
    
    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();
    g_print("Log: end backup_function\n");
}
