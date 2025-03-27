/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - reboot_GUI				 *
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
extern void reboot_fastboot(GtkWidget *widget, gpointer stack);
extern void reboot(GtkWidget *widget, gpointer stack);
extern void reboot_recovery(GtkWidget *widget, gpointer stack);
extern void reboot_heimdall(GtkWidget *widget, gpointer stack);


// Function to set up button labels based on the language
void set_button_labels_reboot_GUI(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Reboot Fastboot");
        strcpy(labels[1], "Reboot");
        strcpy(labels[2], "Reboot Recovery");
        strcpy(labels[3], "Reboot (heimdall)");
        strcpy(labels[4], "Back to Home");
    } 
    
    else 
    {
        strcpy(labels[0], "Neustart Fastboot");
        strcpy(labels[1], "Neustart");
        strcpy(labels[2], "Neustart in Recovery");
        strcpy(labels[3], "Neustart (heimdall)");
        strcpy(labels[4], "Zurück zur Startseite");
    }
}

/* main function - reboot_GUI */
void reboot_GUI(GtkWidget *widget, gpointer stack) 
{
	LOG_INFO("reboot_GUI");
	
    apply_language();
    
    char labels[5][30];  // labels for the button 
    set_button_labels_reboot_GUI(labels);  // for both languages
    
    GtkWidget *reboot_GUI = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(reboot_GUI, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(reboot_GUI, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(reboot_fastboot), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(reboot), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(reboot_recovery), stack);
    GtkWidget *btn4 = create_nav_button(labels[3], G_CALLBACK(reboot_heimdall), stack);
    GtkWidget *btn_back = create_nav_button(labels[4], G_CALLBACK(show_home_page), stack);

    // add the button to the grid
    // line 1
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    // line 2
    gtk_grid_attach(GTK_GRID(grid), btn3, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn4, 1, 1, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(reboot_GUI), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(reboot_GUI), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "reboot_fastboot")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), reboot_GUI, "reboot_fastboot");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "reboot_fastboot");
    
    LOG_INFO("end reboot_GUI");
}
