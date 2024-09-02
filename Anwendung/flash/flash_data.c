/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das Installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_data				 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the program */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "flash_function_header.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

// Button handler functions
// function to flash metadata.img
void metadata_img(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "metadata", NULL, "metadata.img");
}

// function to flash metadata.img (heimdall)
void metadata_img_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "METADATA", "metadata.img");
}

// function to flash userdata.img
void userdata_img(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "userdata", NULL, "userdata.img");
}

// function to flash userdata.img (heimdall)
void userdata_img_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "userdata", "userdata.img");
}

// main function
void flash_data(int argc, char *argv[])
{
	GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[4][30] = {"Metadata", "Metadata (heimdall)", "Userdata", "Userdata (heimdall)"};

    gtk_init(&argc, &argv);
    css_provider(); // load css-provider

     // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Flash:");
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
    for (int i = 0; i < 4; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 2, i / 2, 1, 1);

        // execute css-provider for all buttons
        add_css_provider(button, provider);
        
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(metadata_img), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(metadata_img_heimdall), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(userdata_img), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(userdata_img_heimdall), NULL);
                break;          
        }
    }
	// cleaning the provider
    g_object_unref(provider);

    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();
}


