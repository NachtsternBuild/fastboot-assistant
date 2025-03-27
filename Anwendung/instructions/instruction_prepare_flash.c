/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern 							*
 *											 * 
 *			instruction_prepare_flash		 *
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
#include "instruction_header.h"

#define MAX_BUFFER_SIZE 256

extern void instruction_backup(GtkWidget *widget, gpointer stack);
extern void instruction_preflash(GtkWidget *widget, gpointer stack);

// function to set up button labels based on the language
void set_button_labels_instruction_prepare_flash(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Backup");
        strcpy(labels[1], "Prepare images");
        strcpy(labels[2], "Back");
    } 
    
    else 
    {
        strcpy(labels[0], "Backup");
        strcpy(labels[1], "Systemabbilder vorbereiten");
        strcpy(labels[2], "Zurück");
    }
}

/* main function - instruction_prepare_flash */
void instruction_prepare_flash(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("instruction_prepare_flash");
	
    apply_language();
    
    char labels[3][30];  // labels for the button 
    set_button_labels_instruction_prepare_flash(labels);  // for both languages
    
    GtkWidget *instruction_prepare_flash = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(instruction_prepare_flash, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(instruction_prepare_flash, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(instruction_backup), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(instruction_preflash), stack);
    GtkWidget *btn_back = create_nav_button(labels[2], G_CALLBACK(instruction_GUI), stack);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(instruction_prepare_flash), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(instruction_prepare_flash), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "instruction_prepare_flash")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), instruction_prepare_flash, "instruction_prepare_flash");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "instruction_prepare_flash");
        
    LOG_INFO("end instruction_prepare_flash");
}
