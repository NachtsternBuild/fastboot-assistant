/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_recovery			 *
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
#include "flash_function_header.h"

// Button handler functions
// function to flash recovery.img on only-a-devices
void recovery_img(GtkWidget *widget, gpointer stack))
{
    flash_image(widget, window, "recovery", NULL, "recovery.img", NULL);
}

// function to flash recovery.img (heimdall)
void recovery_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, window, "RECOVERY", "recovery.img");
}

// Function to set up button labels based on the language
void set_button_labels_flash_recovery(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Recovery");
        strcpy(labels[1], "Recovery (heimdall)");
        strcpy(labels[2], "Back");
    } 
    
    else 
    {
        strcpy(labels[0], "Recovery");
        strcpy(labels[1], "Recovery (heimdall)");
        strcpy(labels[2], "Zurück");
    }
}

/* main function - flash_recovery */
void flash_recovery(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("flash_recovery");
    
    apply_language();
    
    char labels[3][30];  // labels for the button 
    set_button_labels_flash_recovery(labels);  // for both languages
    
    GtkWidget *flash_recovery = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(flash_recovery, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(flash_recovery, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(recovery_img), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(recovery_heimdall), stack);
    GtkWidget *btn_back = create_nav_button(labels[2], G_CALLBACK(flash_GUI), stack);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(flash_recovery), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(flash_recovery), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "flash_recovery")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), flash_recovery, "flash_recovery");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "flash_recovery");
	
	LOG_INFO("end flash_recovery");
}
