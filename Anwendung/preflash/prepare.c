/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - prepare				 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "function_header.h"
#include "file_chooser_header.h"
#include "flash_function_header.h"

#define MAX_BUFFER_SIZE 256

// Callback functions for each button
/* main function of prepare*/
void prepare(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[6][30] = {"Boot.img", "Recovery.img", "Vendor.img", 
                                 "System.img", "payload.zip", "Dekomprimieren (xz)"};

    gtk_init(&argc, &argv);
    css_provider(); // load css-provider

     // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Vorbereiten:");
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
    for (int i = 0; i < 6; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);

        // execute css-provider for all buttons
        add_css_provider(button, provider);
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(show_file_chooser), (gpointer)rename_boot);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(show_file_chooser), (gpointer)rename_recovery);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(show_file_chooser), (gpointer)rename_vendor);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(show_file_chooser), (gpointer)rename_system);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(show_file_chooser), (gpointer)rename_payload);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(show_file_chooser), (gpointer)unxz_files);
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

