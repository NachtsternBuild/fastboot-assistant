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

#define MAX_BUFFER_SIZE 256
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

// include all functions
extern void backup_root();
extern void backup_noroot();

// Callback functions for each button
// function without any function
static void start_zero_function_20(GtkWidget *widget, gpointer data) 
{
    g_print("Keine Funktion!\n");
}

// function backup via root
static void start_backup_root(GtkWidget *widget, gpointer data) 
{
    const char *message;
    message = "Der Prozess kann eine Weile dauern. \nIgnorien sie alle beenden erzwingen Meldungen.\n";
    show_message(message);
    
    backup_root();
    
    message = "Prozess beendet.\n";
	show_message(message);
}

// no function
static void start_zero_function_21(GtkWidget *widget, gpointer data) 
{
    g_print("Keine Funktion!\n");
}

// function without any function
static void start_zero_function_22(GtkWidget *widget, gpointer data) 
{
    g_print("Keine Funktion!\n");
}

// function backup with no root
static void start_backup_noroot(GtkWidget *widget, gpointer data) 
{
    backup_noroot();
}

// function without any function
static void start_zero_function_23(GtkWidget *widget, gpointer data) 
{
    g_print("Keine Funktion!\n");
}

/* main function of preflash_GUI*/
void backup_function(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[6][30] = {" ", "Backup mit Root", " ", 
                                 " ", "Backup ohne Root", " "};

    gtk_init(&argc, &argv);
    css_provider(); // load css-provider

    // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Fastboot-Assistant - Backup");
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
                g_signal_connect(button, "clicked", G_CALLBACK(start_zero_function_20), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_backup_root), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(start_zero_function_21), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(start_zero_function_22), NULL);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(start_backup_root), NULL);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(start_zero_function_23), NULL);
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

