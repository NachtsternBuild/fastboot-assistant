/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              reboot_heimdall				 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main program */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"
#include "function_header.h"

#define MAX_BUFFER_SIZE 3072

// reboot to download from adb
static void reboot_from_adb_heimdall(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("reboot_from_adb_heimdall");
    const char *message = strcmp(language, "de") == 0 ? "Beachten sie, dass USB-Debugging aktiviert ist in den Entwickleroptionen!" : "Please note that USB debugging is activated in the developer options!";
    show_message(message);
    
    auto_free char *device_command = adb_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot download", device_command);
    command_with_spinner(command);
    LOG_INFO("end reboot_from_adb_heimdall");
}

// heimdall help
static void heimdall_help(GtkWidget *widget, gpointer stack)
{ 
    LOG_INFO("heimdall_help");
    open_terminal_by_desktop("heimdall help");
    LOG_INFO("end heimdall_help");
}
	
// get pit
static void get_pit(GtkWidget *widget, gpointer stack) 
{
	LOG_INFO("get_pit");
    const char *message = strcmp(language, "de") == 0 ? "Beachten sie, dass sich ihr Gerät im Download-Modus befindet!" : "Please note that your device is in download mode!";
    show_message(message);
    
    open_terminal_by_desktop("heimdall print-pit");
    LOG_INFO("end get_pit");
}

// Function to set up button labels based on the language
void set_button_labels_reboot_heim(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Restart in Download");
        strcpy(labels[1], "Help");
        strcpy(labels[2], "Output pit");
        strcpy(labels[3], "Back");
    } 
    
    else 
    {
        strcpy(labels[0], "In Download neustarten");
        strcpy(labels[1], "Hilfe");
        strcpy(labels[2], "Pit ausgeben");
        strcpy(labels[3], "Zurück");
    }
}

/* main function - reboot_heimdall */
void reboot_heimdall(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("reboot_heimdall");
	
	apply_language();
    
    char labels[4][30];  // labels for the button 
    set_button_labels_reboot_heim(labels);  // for both languages
    
    GtkWidget *reboot_heimdall = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(reboot_heimdall, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(reboot_heimdall, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(reboot_from_adb_heimdall), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(heimdall_help), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(get_pit), stack);
    GtkWidget *btn_back = create_icon_nav_button_with_position("pan-start-symbolic", labels[3], G_CALLBACK(reboot_GUI), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 2, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(reboot_heimdall), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(reboot_heimdall), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "reboot_heimdall")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), reboot_heimdall, "reboot_heimdall");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "reboot_heimdall");
           
    LOG_INFO("end reboot_heimdall");
}
