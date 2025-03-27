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

// include all functions
extern void backup_function(GtkWidget *widget, gpointer stack);
extern void prepare(GtkWidget *widget, gpointer stack);
extern void erase_data();
extern void lock_unlock_bootloader(GtkWidget *widget, gpointer stack);
extern void set_active_slot(GtkWidget *widget, gpointer stack);
extern void partitions(GtkWidget *widget, gpointer stack);

// Callback functions for each button
// start erase_data-function
static void start_erase_data(GtkWidget *widget, gpointer stack) 
{
    erase_data();
}

// Function to set up button labels based on the language
void set_button_labels_preflash(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Backup");
        strcpy(labels[1], "Prepare files");
        strcpy(labels[2], "Delete user data");
        strcpy(labels[3], "Set active slot");
        strcpy(labels[4], "Bootloader");
        strcpy(labels[5], "Partitioning");
        strcpy(labels[6], "Back to Home");
    } 
    
    else 
    {
        strcpy(labels[0], "Backup");
        strcpy(labels[1], "Dateien vorbereiten");
        strcpy(labels[2], "Lösche Nutzerdaten");
        strcpy(labels[3], "Setze aktiven Slot");
        strcpy(labels[4], "Bootloader");
        strcpy(labels[5], "Partitionierung");
        strcpy(labels[6], "Zurück zur Startseite");
    }
}


/* main function - preflash_GUI*/
void preflash_GUI(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("preflash_GUI");
       
    apply_language();
    
    char labels[7][30];  // labels for the button 
    set_button_labels_preflash(labels);  // for both languages
    
    GtkWidget *preflash_GUI = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(preflash_GUI, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(preflash_GUI, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(backup_function), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(prepare), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(start_erase_data), stack);
    GtkWidget *btn4 = create_nav_button(labels[3], G_CALLBACK(set_active_slot), stack);
    GtkWidget *btn5 = create_nav_button(labels[4], G_CALLBACK(lock_unlock_bootloader), stack);
    GtkWidget *btn6 = create_nav_button(labels[5], G_CALLBACK(partitions), stack);
    GtkWidget *btn_back = create_nav_button(labels[6], G_CALLBACK(show_home_page), stack);

    // add the button to the grid
    // line 1
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 2, 0, 1, 1);
    // line 2 (1)
    gtk_grid_attach(GTK_GRID(grid), btn4, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn5, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn6, 2, 1, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(preflash_GUI), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(preflash_GUI), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "preflash_GUI")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), preflash_GUI, "preflash_GUI");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "preflash_GUI");
    
    LOG_INFO("end preflash_GUI");
}

