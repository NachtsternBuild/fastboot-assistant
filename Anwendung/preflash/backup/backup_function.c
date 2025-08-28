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
#include "loading_spinner.h"

#define MAX_BUFFER_SIZE 256

// include all functions
extern void backup_root();
extern void backup_noroot(GtkWidget *widget, gpointer stack);

// function to run the backup and stop the spinner
// for pthread 
void *backup_root_thread(void *arg) 
{
    // run the backup
    backup_root();
    stop_loading_spinner(); // stop the spinner, after the backup
    return NULL;
}

// Callback functions for each button
// function backup via root
static void start_backup_root(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("start_backup_root");
    run_with_spinner(backup_root_thread);
}

// function to set up button labels based on the language
void set_button_labels_backup(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Backup with root"), sizeof(labels[0]));
    g_strlcpy(labels[0], _("Backup without root"), sizeof(labels[1]));
    g_strlcpy(labels[0], _("Back"), sizeof(labels[2]));
} 

/* main function - backup_function */
void backup_function(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("backup_function");
    
    apply_language();
    
    char labels[3][30];  // labels for the button 
    set_button_labels_backup(labels);  // for both languages
    
    GtkWidget *backup_function = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(backup_function, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(backup_function, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_icon_nav_button_with_position("security-high-symbolic", labels[0], G_CALLBACK(start_backup_root), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_icon_nav_button_with_position("avatar-default-symbolic", labels[1], G_CALLBACK(backup_noroot), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_icon_nav_button_with_position("pan-start-symbolic", labels[2], G_CALLBACK(preflash_GUI), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(backup_function), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(backup_function), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "backup_function")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), backup_function, "backup_function");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "backup_function");

    LOG_INFO("end backup_function");
}
