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


// Button handler functions
// function to flash system.img
void system_to_activ(GtkWidget *widget, GtkWindow *window)
{
    LOG_INFO("system_to_activ");
    char function_command[3072];
    char *device_command = fastboot_command();
    snprintf(function_command, sizeof(function_command), "%s erase system", device_command);
    LOG_INFO("Run: %s", function_command);
    system(function_command);
    free(device_command);
    
    flash_image(widget, window, "system", NULL, "system.img", NULL);
    LOG_INFO("end system_to_activ");
}

// flash system.img (heimdall)
void system_to_activ_heimdall(GtkWidget *widget, GtkWindow *window)
{
    LOG_INFO("system_to_activ_heimdall");
    flash_heimdall(widget, window, "SYSTEM", "system.img");
    LOG_INFO("end system_to_activ_heimdall");
}


// function to flash system.img to inactive 
void system_to_inactiv(GtkWidget *widget, GtkWindow *window)
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


// Function to set up button labels based on the language
void set_button_labels_flash_system(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "System");
        strcpy(labels[1], "System (heimdall)");
        strcpy(labels[2], "System (inactive)");
    } 
    
    else 
    {
        strcpy(labels[0], "System");
        strcpy(labels[1], "System (heimdall)");
        strcpy(labels[2], "System (inactive)");
    }
}

/* main function - flash_system */
void flash_system(int argc, char *argv[])
{
	LOG_INFO("flash_system");
	GtkWidget *window, *grid, *button;
    char button_labels[3][30];
    
    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_flash_system(button_labels);
    
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Flashen:");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);
    
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), grid);

    for (int i = 0; i < 3; i++) 
    {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);
        
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(system_to_activ), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(system_to_activ_heimdall), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(system_to_inactiv), NULL);
                break;
        }
    }
	
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop); 
    
    // free the provider
    if (provider != NULL) 
    {
    	g_object_unref(provider);
    	provider = NULL;
	}

	if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
    
    LOG_INFO("end flash_system");
}
