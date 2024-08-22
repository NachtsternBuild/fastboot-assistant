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
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "function_header.h"
#include "flash_function_header.h"

#define BUFFER_SIZE 255

// function to flash system.img to slot
void flash_system_to_inactive(const char *slot) 
{
    char function_command[BUFFER_SIZE];
    char image_path[512];
    set_main_dir_with_wsl(image_path, sizeof(image_path), "system.img");

    // make command to flash system.img
    snprintf(function_command, sizeof(function_command), "fastboot flash system_%s %s && exit", slot, image_path);
	
	g_print(function_command);
    // run command in the terminal
    open_terminal_by_desktop(function_command);
}


// Button handler functions
// function to flash system.img
void system_to_activ(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "system", NULL, "system.img");
}

// flash system.img (heimdall)
void system_to_activ_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "SYSTEM", "system.img");
}


// function to flash system.img to inactive (heimdall)
void system_to_inactiv(GtkWidget *widget, GtkWindow *window)
{
    system("fastboot devices");
	char active_slot[BUFFER_SIZE] = {0};
    char inactive_slot[BUFFER_SIZE] = {0};

    
    // get active slot
    check_active_slot(active_slot, sizeof(active_slot));
    g_print("Aktiver Slot: %s\n", active_slot);

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
        fprintf(stderr, "Unbekannter aktiver Slot: %s\n", active_slot);
        exit(EXIT_FAILURE);
    }

    // flash system.img to inactive slot
    flash_system_to_inactive(inactive_slot);
}

// main function
void flash_system(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    
    // create a windows
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Flash System");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // create button
    GtkWidget *button_system_to_activ = gtk_button_new_with_label("Flash System");
    GtkWidget *button_system_to_activ_heimdall = gtk_button_new_with_label("Flash System (heimdall)");
    GtkWidget *button_system_to_inactiv = gtk_button_new_with_label("Flash System (inactive)");
    
    // connection for gtk callback
	g_signal_connect(button_system_to_activ, "clicked", G_CALLBACK(system_to_activ), (gpointer) window);
	g_signal_connect(button_system_to_activ_heimdall, "clicked", G_CALLBACK(system_to_activ_heimdall), (gpointer) window);
	g_signal_connect(button_system_to_inactiv, "clicked", G_CALLBACK(system_to_inactiv), (gpointer) window);
	
    // create widget
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    gtk_box_pack_start(GTK_BOX(left_vbox), button_system_to_activ, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_system_to_activ_heimdall, TRUE, TRUE, 0);
     
    gtk_box_pack_start(GTK_BOX(right_vbox), button_system_to_inactiv, TRUE, TRUE, 0);
   
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);
	
	// add all to the container
    gtk_container_add(GTK_CONTAINER(window), hbox);
    
    // show all widgets
    gtk_widget_show_all(window);
    
    gtk_main();
}
