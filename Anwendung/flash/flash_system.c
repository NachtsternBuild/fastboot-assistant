/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_system			 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"
#include "function_header.h"
#include "flash_function_header.h"

#define BUFFER_SIZE 2048

// function to flash system.img to slot
// start by system_to_inactive
void flash_system_inactive(const char *slot) 
{
    LOG_INFO("flash_system_inactive");
    char function_command[BUFFER_SIZE];
    char image_path[3072];
    set_main_dir_with_wsl(image_path, sizeof(image_path), "system.img");
	
	// function to erase the system partition
	char function_command_erase[3072];
    char *device_command_erase = fastboot_command();
    snprintf(function_command_erase, sizeof(function_command_erase), "%s erase system", device_command_erase);
    LOG_INFO("Run: %s", function_command_erase);
    system(function_command_erase);
    free(device_command_erase);
    
    // create command to flash system.img
    char *device_command = fastboot_command();
    snprintf(function_command, sizeof(function_command), "%s flash system_%s %s && %s set_active %s", device_command, slot, image_path, device_command, slot);
	
	LOG_INFO("Run: %s", function_command);
    // run command in the terminal
    command_with_spinner(function_command);
    free(device_command);
    LOG_INFO("end flash_system_inactive");
}


// button handler functions
// function to flash system.img to inactive 
void system_to_inactiv(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("system_to_inactiv");
	char active_slot[BUFFER_SIZE] = {0};
    char inactive_slot[BUFFER_SIZE] = {0};

    
    // get active slot
    check_active_slot(active_slot, sizeof(active_slot));
    LOG_INFO("active slot: %s", active_slot);

    // get inactive slot
    if (strcmp(active_slot, "a") == 0) 
    {
        strncpy(inactive_slot, "b", sizeof(inactive_slot) - 1);
    } 
    
    else if (strcmp(active_slot, "b") == 0) 
    {
        strncpy(inactive_slot, "a", sizeof(inactive_slot) - 1);
    } 
    
    else 
    {
        LOG_ERROR("Unknown active slot: %s", active_slot);
        exit(1);
    }
	char function_command[3072];
    char *device_command = fastboot_command();
    snprintf(function_command, sizeof(function_command), "%s erase system_%s", device_command, inactive_slot);
    LOG_INFO("Run: %s", function_command);
    system(function_command);
    free(device_command);
    
    // flash system.img to inactive slot
    flash_system_inactive(inactive_slot);
    LOG_INFO("system_to_inactiv");
}

// function to flash system.img
void system_to_activ(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("system_to_activ");
    char function_command[3072];
    char *device_command = fastboot_command();
    snprintf(function_command, sizeof(function_command), "%s erase system", device_command);
    LOG_INFO("Run: %s", function_command);
    system(function_command);
    free(device_command);
    
    flash_image(widget, main_window, "system", NULL, "system.img", NULL);
    LOG_INFO("end system_to_activ");
}

// flash system.img (heimdall)
void system_to_activ_heimdall(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("system_to_activ_heimdall");
    flash_heimdall(widget, main_window, "SYSTEM", "system.img");
    LOG_INFO("end system_to_activ_heimdall");
}

// function to set up button labels based on the language
void set_button_labels_flash_system(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "System");
        strcpy(labels[1], "System (heimdall)");
        strcpy(labels[2], "System (inactive)");
        strcpy(labels[3], "Back");
    } 
    
    else 
    {
        strcpy(labels[0], "System");
        strcpy(labels[1], "System (heimdall)");
        strcpy(labels[2], "System (inactive)");
        strcpy(labels[3], "Zurück");
    }
}

/* main function - flash_system */
void flash_system(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("flash_system");
	
	apply_language();
    
    char labels[4][30];  // labels for the button 
    set_button_labels_flash_system(labels);  // for both languages
    
    GtkWidget *flash_system = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(flash_system, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(flash_system, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(system_to_activ), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(system_to_activ_heimdall), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(system_to_inactiv), stack);
    GtkWidget *btn_back = create_nav_button(labels[3], G_CALLBACK(flash_GUI), stack);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 2, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(flash_system), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(flash_system), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "flash_system")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), flash_system, "flash_system");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "flash_system");
    
    LOG_INFO("end flash_system");
}
