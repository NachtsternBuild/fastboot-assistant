/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - preflash_GUI			 *
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

#define MAX_BUFFER_SIZE 256

// include all functions
extern void make_dir();
extern void remove_old();
extern void wsl_config();

// Callback functions for each button
// function without any function
static void start_make_dir_function(GtkWidget *widget, gpointer data) 
{
    const char *message;
    message = "Fertig!\n";
    make_dir();
    show_message(message);
}

// function without any function
static void start_remove_old(GtkWidget *widget, gpointer data) 
{
    remove_old();
}

// start make_dir-function
static void start_wsl_config(GtkWidget *widget, gpointer data) 
{
    const char *message;
    message = "Fertig!\n";
    wsl_config();
    show_message(message);
}

/* main function of preflash_GUI*/
void config_projekt_GUI(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    
    char button_labels[3][30] = {"Anlegen Ordner", "Aufräumen", "Konfigurieren"};

    gtk_init(&argc, &argv);
	
	css_provider(); // load css-provider
	
    // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Fastboot-Assistant - Zusätze");
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
    for (int i = 0; i < 3; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);

        // execute css-provider for all buttons
        add_css_provider(button, provider);
        
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(start_make_dir_function), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_remove_old), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(start_wsl_config), NULL);
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

