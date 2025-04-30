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

// include all functions
/*
old UI
extern void instruction_adb(GtkWidget *widget, gpointer stack);
extern void instruction_flash(GtkWidget *widget, gpointer stack);
extern void instruction_prepare_flash(GtkWidget *widget, gpointer stack);
extern void instruction_info(GtkWidget *widget, gpointer stack);
*/
extern void instruction_flash();
extern void instruction_prepare_flash(GtkWidget *widget, gpointer stack);
extern void instruction_adb();
extern void instruction_info();

// Callback functions for each button
// start instruction_adb-function
static void start_instruction_adb(GtkWidget *widget, gpointer stack) 
{
    instruction_adb();
}

// start instruction_info-function
static void start_instruction_info(GtkWidget *widget, gpointer stack) 
{
    instruction_info();
}


// function to set up button labels based on the language
void set_button_labels_instruction_GUI(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Dealing with ADB");
        strcpy(labels[1], "Flashing Images");
        strcpy(labels[2], "Preparations");
        strcpy(labels[3], "Info");
        strcpy(labels[4], "Back to Home");
    } 
    
    else 
    {
        strcpy(labels[0], "Umgang mit ADB");
        strcpy(labels[1], "Flash Images");
        strcpy(labels[2], "Vorbereitungen");
        strcpy(labels[3], "Info");
        strcpy(labels[4], "Zurück zur Startseite");
    }
}

/* main function - instruction_GUI */
void instruction_GUI(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("instruction_GUI");
    
    apply_language();
    
    char labels[5][30];  // labels for the button 
    set_button_labels_instruction_GUI(labels);  // for both languages
    
    GtkWidget *instruction_GUI = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(instruction_GUI, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(instruction_GUI, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
	GtkWidget *btn1 = create_icon_nav_button_with_position("phone-apple-iphone-symbolic", labels[0], G_CALLBACK(start_instruction_adb), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_icon_nav_button_with_position("drive-multidisk-symbolic", labels[1], G_CALLBACK(instruction_flash), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn3 = create_icon_nav_button_with_position("applications-engineering-symbolic", labels[2], G_CALLBACK(instruction_prepare_flash), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn4 = create_icon_nav_button_with_position("help-about-symbolic", labels[3], G_CALLBACK(start_instruction_info), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_icon_nav_button_with_position("pan-start-symbolic", labels[4], G_CALLBACK(show_home_page), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    // line 1
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    // line 2
    gtk_grid_attach(GTK_GRID(grid), btn3, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn4, 1, 1, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(instruction_GUI), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(instruction_GUI), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "instruction_GUI")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), instruction_GUI, "instruction_GUI");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "instruction_GUI");
           
    LOG_INFO("end instruction_GUI");
}
