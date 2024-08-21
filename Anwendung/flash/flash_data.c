/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das Installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_data				 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the program */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "flash_function_header.h"

// Button 1 - flash metadata.img
static void metadata_img(GtkWidget *widget, gpointer data)
{
    char image_path[512];
    set_main_dir_with_wsl(image_path, sizeof(image_path), "metadata.img");
    
    system("fastboot devices");
    char function_command[255];
    snprintf(function_command, sizeof(function_command), "fastboot flash metadata %s && exit", image_path);
    g_print(function_command);
    open_terminal_by_desktop(function_command);
}

// Button 2 - flash userdata.img
static void userdata_img(GtkWidget *widget, gpointer data)
{
    char image_path[512];
    set_main_dir_with_wsl(image_path, sizeof(image_path), "userdata.img");

    system("fastboot devices");
    char function_command[255];
    snprintf(function_command, sizeof(function_command), "fastboot flash userdata %s && exit", image_path);
    g_print(function_command);
    open_terminal_by_desktop(function_command);
}

// Button 3 - flash metadata.img with Heimdall
static void metadata_img_heimdall(GtkWidget *widget, gpointer data)
{
    char image_path[512];
    set_main_dir_with_wsl(image_path, sizeof(image_path), "metadata.img");

    char function_command[255];
    snprintf(function_command, sizeof(function_command), "heimdall flash --METADATA %s --no-reboot && exit", image_path);
    g_print(function_command);
    open_terminal_by_desktop(function_command);
}

// Button 4 - flash userdata.img with Heimdall
static void userdata_img_heimdall(GtkWidget *widget, gpointer data)
{
    char image_path[512];
    set_main_dir_with_wsl(image_path, sizeof(image_path), "userdata.img");

    char function_command[255];
    snprintf(function_command, sizeof(function_command), "heimdall flash --USERDATA %s --no-reboot && exit", image_path);
    g_print(function_command);
    open_terminal_by_desktop(function_command);
}


/* Start main program */
void flash_data(int argc, char *argv[])
{
	// Initialize GTK
	gtk_init(&argc, &argv);
	
	// Create main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Flash metadata/userdata");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	// Create buttons for each function with label
	GtkWidget *button_metadata_img = gtk_button_new_with_label("Flash metadata.img");
    GtkWidget *button_userdata_img = gtk_button_new_with_label("Flash userdata.img");
    GtkWidget *button_metadata_img_heimdall = gtk_button_new_with_label("Flash metadata.img (heimdall)");
    GtkWidget *button_userdata_img_heimdall = gtk_button_new_with_label("Flash userdata.img (heimdall)");
    
    // Link the click callback function with the buttons 
    g_signal_connect(button_metadata_img, "clicked", G_CALLBACK(metadata_img), NULL);
    g_signal_connect(button_userdata_img, "clicked", G_CALLBACK(userdata_img), NULL);
    g_signal_connect(button_metadata_img_heimdall, "clicked", G_CALLBACK(metadata_img_heimdall), NULL);
    g_signal_connect(button_userdata_img_heimdall, "clicked", G_CALLBACK(userdata_img_heimdall), NULL);
    
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), button_metadata_img, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_userdata_img, TRUE, TRUE, 0);
    
    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), button_metadata_img_heimdall, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_userdata_img_heimdall, TRUE, TRUE, 0);
    
    // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // Show all buttons
    gtk_widget_show(button_metadata_img);
    gtk_widget_show(button_userdata_img);
    gtk_widget_show(button_metadata_img_heimdall);
    gtk_widget_show(button_userdata_img_heimdall);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// Start GTK main loop
	gtk_main();
}

