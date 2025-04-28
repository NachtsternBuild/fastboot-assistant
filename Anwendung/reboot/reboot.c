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
 *              reboot						 *
 *											 *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"
#include "function_header.h"
#include "file_chooser_header.h"
#include "flash_function_header.h"

// reboot system
static void reboot_system(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("reboot_system");
    const char *message = strcmp(language, "de") == 0 ? "Neustart wird durchgeführt." : "Restart is performed.";    
    show_message(message);
    
    // reboot from fastboot
    auto_free char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot", device_command);
    command_with_spinner(command);
    LOG_INFO("end reboot_system");
}

// boot to an image
static void boot_to_image(const gchar *i_filename) 
{
    LOG_INFO("boot_to_image");
    char boot_image[4096];
    char boot_command[4096];
    get_config_file_path(boot_image, sizeof(boot_image));
    // load the path
    const char *boot_image_path = load_path_from_file(boot_image);

    if (boot_image_path) 
    {
        LOG_INFO("Loaded path: %s", boot_image_path);
    }

    // create fastboot command
    auto_free char *device_command = fastboot_command(); 
    snprintf(boot_command, sizeof(boot_command), "%s boot %s/%s", device_command, boot_image_path, i_filename);
    LOG_INFO("Run: %s \n", boot_command);
    command_with_spinner(boot_command);

    LOG_INFO("end boot_to_image");
}

// function to set up button labels based on the language
void set_button_labels_reboot(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Reboot System");
        strcpy(labels[1], "Reboot Image(.img)");
        strcpy(labels[2], "Back");
    }
    
    else
    {
    	strcpy(labels[0], "Neustart System");
    	strcpy(labels[1], "Neustart Image(.img)");
    	strcpy(labels[2], "Zurück");
    }
} 

/* main function - reboot */
void reboot(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("reboot");

    apply_language();
    
    char labels[3][30];  // labels for the button 
    set_button_labels_reboot(labels);  // for both languages
    
    GtkWidget *reboot = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(reboot, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(reboot, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(reboot_system), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(boot_to_image), stack);
    GtkWidget *btn_back = create_icon_nav_button_with_position("pan-start-symbolic", labels[2], G_CALLBACK(reboot_GUI), stack, GTK_ALIGN_CENTER);


    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(reboot), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(reboot), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "reboot")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), reboot, "reboot");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "reboot");
        
    LOG_INFO("end reboot");
}
