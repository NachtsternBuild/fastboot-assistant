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
#include "program_functions.h"
#include "flash_function_header.h"

#define MAX_BUFFER_SIZE 256
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

// button 1 - set slot a
static void set_slot_a(GtkWidget *widget, gpointer data)
{
    system("fastboot devices");
	open_terminal_by_desktop("fastboot set_active a && fastboot getvar current-slot && exit");
}

// button 2 - set slot b
static void set_slot_b(GtkWidget *widget, gpointer data)
{
	system("fastboot devices");
	open_terminal_by_desktop("fastboot set_active b && fastboot getvar current-slot && exit");
}

/* start main programm */
void set_active_slot(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[2][30] = {"Setze 'a'", "Setze 'b'"};

    gtk_init(&argc, &argv);
    css_provider(); // load css-provider

    // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Setzen des aktiven Slots:");
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
    for (int i = 0; i < 2; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);

        // execute css-provider for all buttons
        add_css_provider(button, provider);
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(set_slot_a), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(set_slot_b), NULL);
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

