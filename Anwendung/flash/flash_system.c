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

GtkWidget *system_spinner;
GtkWidget *system_spinner_window;

// function to flash system.img to inactive slot
void *flash_inactive_system(void *command)
{   
	char *function_command = (char *)command;
	
	LOG_INFO("Run: %s", function_command);
    // run command in the terminal
    system(function_command);
    
    
    // stop the spinner
    gtk_spinner_stop(GTK_SPINNER(system_spinner));
    gtk_window_destroy(GTK_WINDOW(system_spinner_window));
    
    free(function_command);  // free memory
    
    return NULL;
}

// button handler functions
void system_to_inactiv(GtkWidget *widget, gpointer stack)
{
	setenv("GSK_RENDERER", "cairo", 1);
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
        
    char config_file[4096];
    char erase_command[BUFFER_SIZE];
	char function_command[4096];
	char image_info[BUFFER_SIZE];
    auto_free char *device_command = fastboot_command();
    
    // get the path of the image
    //set_main_dir_with_wsl(image_path, sizeof(image_path), "system.img");
    get_config_file_path(config_file, sizeof(config_file));
    // load the path
    const char *image_path = load_path_from_file(config_file);
    const char *image_name = "system.img";

    if (image_path) 
    {
        LOG_INFO("Loaded path: %s", image_path);
    }
	
	// create the image path
	snprintf(image_info, sizeof(image_info), "%s/%s", image_path, image_name);
    
    // create command for erase inactive system
    snprintf(erase_command, sizeof(erase_command), "%s erase system_%s", device_command, inactive_slot);
        
    // create command to flash system.img and add erase command
    snprintf(function_command, sizeof(function_command), "%s && %s flash system_%s %s && %s set_active %s", erase_command, device_command, inactive_slot, image_info, device_command, inactive_slot);
	
	// check if the image not exists
    if (access(image_info, F_OK) == -1)
    {      
        const char *error_message = _("Image file not found.");
        show_error_message(GTK_WIDGET(main_window), error_message);
        LOG_ERROR("%s", error_message);
        return;
    }
	    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_message(GTK_WIDGET(main_window), error_message);
        return;
    }
	
	// window for the spinner
    system_spinner_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(system_spinner_window), " ");
    gtk_window_set_default_size(GTK_WINDOW(system_spinner_window), 200, 200);

    // create a spinner
    system_spinner = gtk_spinner_new();
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(vbox), system_spinner);
    gtk_widget_set_size_request(system_spinner, 150, 150);
    gtk_window_set_child(GTK_WINDOW(system_spinner_window), vbox);
	
    // start the spinner
    gtk_spinner_start(GTK_SPINNER(system_spinner));

    // make the window visible using gtk_window_present
    gtk_window_present(GTK_WINDOW(system_spinner_window));

    // use new thread to flash the images
    pthread_t flash_system_thread;
    pthread_create(&flash_system_thread, NULL, flash_inactive_system, function_command);
    pthread_detach(flash_system_thread);
	
	if (image_path != NULL) 
	{
    	g_free((gpointer)image_path); // free the info (because g_file_get_contents was used)
	}
	
	
	LOG_INFO("end system_to_inactiv");
}

// function to flash system.img
void system_to_activ(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("system_to_activ");
    char function_command[3072];
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_message(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    auto_free char *device_command = fastboot_command();
    snprintf(function_command, sizeof(function_command), "%s erase system", device_command);
    LOG_INFO("Run: %s", function_command);
    command_with_spinner(function_command);
    
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
    g_strlcpy(labels[0], _("System"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("System (heimdall)"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("System (inactive)"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("Back"), sizeof(labels[3]));
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
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(system_to_activ), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(system_to_activ_heimdall), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(system_to_inactiv), stack);
    GtkWidget *btn_back = create_icon_nav_button_with_position("pan-start-symbolic", labels[3], G_CALLBACK(flash_GUI), stack, GTK_ALIGN_CENTER);

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
