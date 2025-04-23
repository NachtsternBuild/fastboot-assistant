/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - updater				 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
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

#define MAX_BUFFER_SIZE 256

// Callback functions for each button
// function to start the normal updater 
static void start_updater_stable(GtkWidget *widget, gpointer stack) 
{
    updater_stable();
}

// function to start the updater with devmode
static void start_updater_devmode(GtkWidget *widget, gpointer stack) 
{
    updater_devmode();
}

// Function to set up button labels based on the language
void set_button_labels_updater(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Updater");
        strcpy(labels[1], "Updater (for development)");
        strcpy(labels[2], "Back to Home");
    }
    
    else
    {
    	strcpy(labels[0], "Updater");
    	strcpy(labels[1], "Updater (für Entwicklung)");
    	strcpy(labels[2], "Zurück zur Startseite");
    }
} 

/* main function - updater */
void updater(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("updater");
    apply_language();
    
    char labels[3][30];  // labels for the button 
    set_button_labels_updater(labels);  // for both languages
    
    GtkWidget *updater = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(updater, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(updater, GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(updater, TRUE);
	gtk_widget_set_vexpand(updater, TRUE);


    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(grid, TRUE);
	gtk_widget_set_vexpand(grid, TRUE);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(start_updater_stable), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(start_updater_devmode), stack);
    GtkWidget *btn_back = create_nav_button(labels[2], G_CALLBACK(show_home_page), stack);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(updater), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(updater), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "updater")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), updater, "updater");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "updater");
	LOG_INFO("end updater");
}
