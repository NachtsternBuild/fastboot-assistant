/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - prepare				 *
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
#include "file_chooser_header.h"
#include "flash_function_header.h"

#define MAX_BUFFER_SIZE 256

// Function to set up button labels based on the language
void set_button_labels_prepare(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Boot.img");
        strcpy(labels[1], "Recovery.img");
        strcpy(labels[2], "Vendor.img");
        strcpy(labels[3], "System.img");
        strcpy(labels[4], "payload.zip");
        strcpy(labels[5], "Decompress (xz)");
        strcpy(labels[6], "Back");
    } 
    
    else 
    {
        strcpy(labels[0], "Boot.img");
        strcpy(labels[1], "Recovery.img");
        strcpy(labels[2], "Vendor.img");
        strcpy(labels[3], "System.img");
        strcpy(labels[4], "payload.zip");
        strcpy(labels[5], "Dekomprimieren (xz)");
        strcpy(labels[6], "Zurück");
    }
}

/* main function - prepare */
void prepare(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("prepare");
    apply_language();
    
    char button_labels[7][30];  // labels for the button 
    set_button_labels_preflash(labels);  // for both languages
    
    GtkWidget *prepare = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(prepare, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(prepare, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(show_file_chooser), (gpointer)rename_boot);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(show_file_chooser), (gpointer)rename_recovery);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(show_file_chooser), (gpointer)rename_vendor);
    GtkWidget *btn4 = create_nav_button(labels[3], G_CALLBACK(show_file_chooser), (gpointer)rename_system);
    GtkWidget *btn5 = create_nav_button(labels[4], G_CALLBACK(show_file_chooser), (gpointer)rename_payload);
    GtkWidget *btn6 = create_nav_button(labels[5], G_CALLBACK(show_file_chooser), (gpointer)unxz_files);
    GtkWidget *btn_back = create_nav_button(labels[6], G_CALLBACK(preflash_GUI), stack);

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
    gtk_box_append(GTK_BOX(prepare), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(prepare), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "prepare")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), prepare, "prepare");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "prepare");
    
    LOG_INFO("end prepare");
}
