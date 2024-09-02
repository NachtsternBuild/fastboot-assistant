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
 *      (C) Copyright 2024 Elias Mörz 		 *
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

#define BUFFER_SIZE 2048
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

// function to flash system.img to slot
// start by system_to_inactive
void flash_system_inactive(const char *slot) 
{
    char function_command[BUFFER_SIZE];
    char image_path[2048];
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
    flash_system_inactive(inactive_slot);
}

// main function
void flash_system(int argc, char *argv[])
{
	GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    
    char button_labels[3][30] = {"System", "System (heimdall)", "System (inactive)"};

    gtk_init(&argc, &argv);
	
	css_provider(); // load css-provider
	
    // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Flash:");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // create the grid and centre it
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    // add the grid to the window
    gtk_container_add(GTK_CONTAINER(window), grid);

    // add and centre all button
    for (int i = 0; i < 3; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);

        // execute css-provider for all buttons
        add_css_provider(button, provider);
        
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
    
    // clean the storage
    g_object_unref(provider);

    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();
}

