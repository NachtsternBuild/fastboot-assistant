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
// rework flashheader
#include "flash_function_header.h"

// function to flash system.img to slot
void flash_system_to_inactive(const char *slot) 
{
    char command[BUFFER_SIZE];

    // make command to flash system.img
    snprintf(command, sizeof(command), "fastboot flash system_%s ~/Downloads/ROM-Install/system.img", slot);

    // run command
    int result = system(command);
    if (result == -1) 
    {
        fprintf(stderr, "Fehler mit dem Befehls: %s\n", command);
        exit(EXIT_FAILURE);
    } 
    
    else 
    {
        printf("Befehl funktioniert: %s\n", command);
    }
}

// button 1 - flash system.img to activ slot
static void system_to_activ(GtkWidget *widget, gpointer data)
{
    system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot erase system && fastboot flash system ~/Downloads/ROM-Install/system.img && exit");
}

// button 2 - flash system.img to inactive slot
static void system_to_inactiv(GtkWidget *widget, gpointer data)
{
	system("fastboot devices");
	char active_slot[BUFFER_SIZE] = {0};
    char inactive_slot[BUFFER_SIZE] = {0};

    
    // get active slot
    check_active_slot(active_slot, sizeof(active_slot));
    printf("Aktiver Slot: %s\n", active_slot);

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
    flash_system_img(inactive_slot);
}

// button 3 - flash system.img heimdall
static void system_heimdall(GtkWidget *widget, gpointer data)
{
	char function_command[255];
	open_terminal_by_desktop("heimdall flash --SYSTEM ~/Downloads/ROM-Install/system.img && exit");
}

/* start main programm */
void flash_system(int argc, char *argv[])
{
	// int gtk
	gtk_init(&argc, &argv);
	
	// make main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Flash System");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// make button for every function
    GtkWidget *button_system_to_activ = gtk_button_new_with_label("Flashen in aktiven Slot (auch für only-a-devices)");
    GtkWidget *button_system_to_inactiv = gtk_button_new_with_label("Flashen in inaktiven Slot");
    GtkWidget *button_system_heimdall = gtk_button_new_with_label("Flashen system.img (heimdall)");
    
    // Link the click callback function with the buttons 
    g_signal_connect(button_system_to_activ, "clicked", G_CALLBACK(system_to_activ), NULL);
    g_signal_connect(button_system_to_inactiv, "clicked", G_CALLBACK(system_to_inactiv), NULL);
    g_signal_connect(button_system_heimdall, "clicked", G_CALLBACK(system_heimdall), NULL);
    
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), button_system_to_activ, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_system_heimdall, TRUE, TRUE, 0);
    
    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), button_system_to_inactiv, TRUE, TRUE, 0);
    
    // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all button
    gtk_widget_show(button_system_to_activ);
    gtk_widget_show(button_system_to_inactiv);
    gtk_widget_show(button_system_heimdall);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
}
