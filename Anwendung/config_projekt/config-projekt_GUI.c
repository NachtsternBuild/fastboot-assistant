/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - config-projekt_GUI 	 *
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

// include all functions
extern void make_dir();
extern void remove_old();
extern void wsl_config();

// Callback functions for each button
// function that start make_dir
static void start_make_dir_function(GtkWidget *widget, gpointer data) 
{
    const char *message = strcmp(language, "de") == 0 ? "Fertig!": "Ready!";
    make_dir();
    show_message(message);
}

// function that start remove_old
static void start_remove_old(GtkWidget *widget, gpointer data) 
{
    remove_old();
}

// function that start wsl_config
static void start_wsl_config(GtkWidget *widget, gpointer data) 
{
    wsl_config();
}

// function that start toggle_language
static void start_toggle_language(GtkWidget *widget, gpointer data)
{
	toggle_language();
}

// Function to set up button labels based on the language
void set_button_labels_config_projekt(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Create folder");
        strcpy(labels[1], "Clean up");
        strcpy(labels[2], "Configure");
        strcpy(labels[3], "Change language");
    } 
    
    else 
    {
        strcpy(labels[0], "Anlegen Ordner");
        strcpy(labels[1], "Aufräumen");
        strcpy(labels[2], "Konfigurieren");
        strcpy(labels[3], "Sprache wechseln");
    }
}

/* main function of config-projekt_GUI*/
void config_projekt_GUI(int argc, char *argv[]) 
{
	g_print("Log: config_projekt_GUI\n");
	GtkWidget *window, *grid, *button;
    char button_labels[4][30];
    
    gtk_init();
    apply_theme();
    apply_language();
    set_button_labels_config_projekt(button_labels);
    
    window = gtk_window_new();
    const char *config_projekt_window = strcmp(language, "de") == 0 ? "Zusätze" : "Additions";
    gtk_window_set_title(GTK_WINDOW(window), config_projekt_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);
    
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), grid);
    
    for (int i = 0; i < 4; i++) 
    {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 2, i / 2, 1, 1);
        
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
            case 3;
            	g_signal_connect(button, "clicked", G_CALLBACK(start_toggle_language); NULL);
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
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop); 
    
    g_print("Log: end config_projekt_GUI\n");
}
