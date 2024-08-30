/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - reboot_GUI				 *
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
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

// include all functions
extern void reboot_fastboot();
extern void reboot();
extern void reboot_recovery();
extern void reboot_heimdall();

// Callback functions for each button
// start reboot_fastboot-function
static void start_reboot_fastboot(GtkWidget *widget, gpointer data) 
{
    reboot_fastboot();
}

// start reboot-function
static void start_reboot(GtkWidget *widget, gpointer data) 
{
    reboot();
}

// start reboot_recovery-function
static void start_reboot_recovery(GtkWidget *widget, gpointer data) 
{
    reboot_recovery();
}

// start reboot-function heimdall
static void start_reboot_heimdall(GtkWidget *widget, gpointer data) 
{
    reboot_heimdall();
}

void reboot_GUI(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[4][30] = {"Neustart Fastboot", "Neustart", "Neustart in Recovery", "Neustart Heimdall"};

    gtk_init(&argc, &argv);
    css_provider(); // load css-provider

     // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Fastboot-Assistant - Neustart");
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
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);

        // execute css-provider for all buttons
        add_css_provider(button, provider);
        
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(start_reboot_fastboot), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_reboot), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(start_reboot_recovery), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(start_reboot_heimdall), NULL);
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

