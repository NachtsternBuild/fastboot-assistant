/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_others			 *
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
#include "function_header.h"
#include "loading_spinner.h"
#include "program_functions.h"
#include "flash_function_header.h"

extern void flash_list_images();
extern void flash_images();

/* function to run flash_images with spinner */
// for pthread 
void *flash_images_thread(void *arg) 
{
    // run the backup
    flash_images();
    stop_loading_spinner(); // stop the spinner, after the backup
    return NULL;
}

// Callback functions for each button
// function to flash_images
static void start_flash_images_dir(GtkWidget *widget, gpointer stack) 
{
     LOG_INFO("start_flash_images_dir");
    run_with_spinner(flash_images_thread);
}

/* function to run flash_images_list with spinner */
// for pthread 
void *flash_list_images_thread(void *arg) 
{
    // run the backup
    flash_list_images();
    stop_loading_spinner(); // stop the spinner, after the backup
    return NULL;
}

// functio to flash_images_list
static void start_flash_list(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("start_flash_list");
    run_with_spinner(flash_list_images_thread);
}

// Function to set up button labels based on the language
void set_button_labels_flash_others(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Predefined images"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Images in the directory"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Back"), sizeof(labels[2]));
}

/* main function - flash_others */
void flash_others(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("flash_others");
   
    apply_language();
    
    char labels[3][30];  // labels for the button 
    set_button_labels_flash_others(labels);  // for both languages
    
    GtkWidget *flash_others = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(flash_others, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(flash_others, GTK_ALIGN_CENTER);
    
    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_icon_nav_button_with_position("emblem-documents-symbolic", labels[0], G_CALLBACK(start_flash_list), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_icon_nav_button_with_position("folder-visiting-symbolic", labels[1], G_CALLBACK(start_flash_images_dir), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_icon_nav_button_with_position("pan-start-symbolic", labels[2], G_CALLBACK(flash_GUI), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(flash_others), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(flash_others), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "flash_others")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), flash_others, "flash_others");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "flash_others");
           
    LOG_INFO("end flash_others");
}
