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
 *              reboot_recovery				 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"
#include "function_header.h"

#define MAX_BUFFER_SIZE 256

// Callback functions for each button
// start reboot_recovery adb-function
static void start_recovery_adb(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("start_recovery_adb");
    const char *message = strcmp(language, "de") == 0 ? "Beachten sie, dass USB-Debugging aktiviert ist in den Entwickleroptionen!" : "Please note that USB debugging is activated in the developer options!";    
    show_message(message);
    
    auto_free char *device_command = adb_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot recovery", device_command);
    command_with_spinner(command);
    LOG_INFO("end start_recovery_adb");
}

// start reboot_recovery fastboot
static void start_recovery_fastboot(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("start_recovery_fastboot");
    const char *message = strcmp(language, "de") == 0 ? "Beachten sie, dass sich ihr Gerät im Fastboot-Modus befindet!" : "Please note that your device is in fastboot mode!";
    show_message(message);
    
    auto_free char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot recovery", device_command);
    command_with_spinner(command);
    LOG_INFO("end start_recovery_fastboot");
}

// function to set up button labels based on the language
void set_button_labels_reboot_recovery(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Restart ADB");
        strcpy(labels[1], "Restarting Fastboot");
        strcpy(labels[2], "Back");
    }
    
    else
    {
    	strcpy(labels[0], "Neustart von ADB");
    	strcpy(labels[1], "Neustart von Fastboot");
    	strcpy(labels[2], "Zurück");
    }
} 


/* main function - reboot_recovery */
void reboot_recovery(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("reboot_recovery");
    
    apply_language();
    
    char labels[3][30];  // labels for the button 
    set_button_labels_reboot_recovery(labels);  // for both languages
    
    GtkWidget *reboot_recovery = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(reboot_recovery, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(reboot_recovery, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(start_recovery_adb), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(start_recovery_fastboot), stack);
    GtkWidget *btn_back = create_nav_button(labels[2], G_CALLBACK(reboot_GUI), stack);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(reboot_recovery), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(reboot_recovery), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "reboot_recovery")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), reboot_recovery, "reboot_recovery");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "reboot_recovery");
    
    LOG_INFO("end reboot_recovery");
}
