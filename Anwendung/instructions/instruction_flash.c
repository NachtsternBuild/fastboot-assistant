/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_flash		 *
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
#include "instruction_header.h"

#define MAX_BUFFER_SIZE 256

extern void instruction_root(GtkWidget *widget, gpointer stack);
extern void instruction_vendor(GtkWidget *widget, gpointer stack);
extern void instruction_gsi(GtkWidget *widget, gpointer stack);
extern void instruction_custom_rom(GtkWidget *widget, gpointer stack);
extern void instruction_recovery(GtkWidget *widget, gpointer stack);
extern void instruction_others(GtkWidget *widget, gpointer stack);

// function to set up button labels based on the language
void set_button_labels_instruction_flash(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Rooting");
        strcpy(labels[1], "Vendor (VNDK)");
        strcpy(labels[2], "Generic System Image (GSI)");
        strcpy(labels[3], "Custom ROMs");
        strcpy(labels[4], "Recovery");
        strcpy(labels[5], "Others");
        strcpy(labels[6], "Back");
    } 
    
    else 
    {
        strcpy(labels[0], "Rooten");
        strcpy(labels[1], "Vendor (VNDK)");
        strcpy(labels[2], "Generic System Image (GSI)");
        strcpy(labels[3], "Custom ROMs");
        strcpy(labels[4], "Recovery");
        strcpy(labels[5], "Andere");
        strcpy(labels[6], "Zurück");
    }
}

/* main function - instruction_flash */
void instruction_flash(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("instruction_flash");
	   
    apply_language();
    
    char labels[7][30];  // labels for the button 
    set_button_labels_instruction_flash(labels);  // for both languages
    
    GtkWidget *instruction_flash = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(instruction_flash, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(instruction_flash, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_icon_nav_button_with_position("security-high-symbolic", labels[0], G_CALLBACK(instruction_root), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_icon_nav_button_with_position("media-optical-dvd-symbolic", labels[1], G_CALLBACK(instruction_vendor), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn3 = create_icon_nav_button_with_position("media-optical-dvd-symbolic", labels[2], G_CALLBACK(instruction_gsi), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn4 = create_icon_nav_button_with_position("media-zip-symbolic", labels[3], G_CALLBACK(instruction_custom_rom), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn5 = create_icon_nav_button_with_position("applications-utilities-symbolic", labels[4], G_CALLBACK(instruction_recovery), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn6 = create_icon_nav_button_with_position("emblem-documents-symbolic", labels[5], G_CALLBACK(instruction_others), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_icon_nav_button_with_position("pan-start-symbolic", labels[6], G_CALLBACK(instruction_GUI), stack, GTK_ALIGN_CENTER);

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
    gtk_box_append(GTK_BOX(instruction_flash), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(instruction_flash), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "instruction_flash")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), instruction_flash, "instruction_flash");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "instruction_flash");
        
    LOG_INFO("end instruction_flash");
}

