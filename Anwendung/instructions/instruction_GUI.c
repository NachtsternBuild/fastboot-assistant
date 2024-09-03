/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_GUI		 *
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
#include "instruction_header.h"

#define MAX_BUFFER_SIZE 256

// include all functions
extern void instruction_adb();
extern void instruction_flash();
extern void instruction_prepare_flash();
extern void instruction_info();

// Callback functions for each button
// start instruction_adb-function
static void start_instruction_adb(GtkWidget *widget, gpointer data) 
{
    instruction_adb();
}

// start instruction_flash-function
static void start_instruction_flash(GtkWidget *widget, gpointer data) 
{
    instruction_flash();
}

// start instruction_prepare_flash-function
static void start_instruction_prepare_flash(GtkWidget *widget, gpointer data) 
{
    instruction_prepare_flash();
}

// start instruction_info-function
static void start_instruction_info(GtkWidget *widget, gpointer data) 
{
    instruction_info();
}

/* main function of flash_GUI*/
void instruction_GUI(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[4][20] = {"Umgang mit ADB", "Flash Images", "Vorbereitungen", "Info"};

    gtk_init(&argc, &argv);
    css_provider(); // load css-provider

     // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Fastboot-Assistant - Anleitungen");
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
                g_signal_connect(button, "clicked", G_CALLBACK(start_instruction_adb), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_instruction_flash), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(start_instruction_prepare_flash), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(start_instruction_info), NULL);
                break;
        }
    }
	// clean the provider
    g_object_unref(provider);

    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();
}

