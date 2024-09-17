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

// Callback functions for each button
// function backup via root
static void start_backup_root(GtkWidget *widget, gpointer data) 
{
    GtkSpinner *spinner = GTK_SPINNER(data);  // Get the spinner from the callback data

    start_loading_spinner(spinner);  // Start the spinner
    
    // Run the backup process with a spinner in a separate thread
    run_with_spinner((void *)backup_root);
    
    stop_loading_spinner(spinner);  // Stop the spinner when the process finishes
}

// function backup with no root
static void start_backup_noroot(GtkWidget *widget, gpointer data) 
{
    backup_noroot();
}

/* main function of preflash_GUI */
void backup_function(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *spinner;
    char button_labels[2][30] = {"Backup mit Root", "Backup ohne Root"};

    gtk_init(&argc, &argv);
    apply_theme();

    // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Backup");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // create the grid and center it
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    // add the grid to the window
    gtk_container_add(GTK_CONTAINER(window), grid);
    
    // Initialize the spinner and add it to the grid
    spinner = gtk_spinner_new();  // Initialize the spinner
    gtk_grid_attach(GTK_GRID(grid), spinner, 0, 2, 3, 1);  // Attach spinner to grid
    gtk_widget_set_halign(spinner, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(spinner, GTK_ALIGN_CENTER);

    // add and center all buttons
    for (int i = 0; i < 2; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);

        // execute css-provider for all buttons
        add_css_provider(button, provider);
        
        // Connect buttons to corresponding backup functions, passing spinner as callback data
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(start_backup_root), spinner);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_backup_noroot), spinner);
                break;
        }
    }

    // clean the storage
    g_object_unref(provider);
    
    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();
}

