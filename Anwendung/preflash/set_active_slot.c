/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - set_active_slot		 *
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
#include "flash_function_header.h"

// button 1 - set slot a
static void set_slot_a(GtkWidget *widget, gpointer data)
{
    system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot set_active a && fastboot getvar current-slot && exit");
}

// button 2 - set slot b
static void set_slot_b(GtkWidget *widget, gpointer data)
{
	system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot set_active b && fastboot getvar current-slot && exit");
}

/* start main programm */
void set_active_slot(int argc, char *argv[])
{
	// int gtk
	gtk_init(&argc, &argv);
	
	// make main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Setzen aktiven  des Slots");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// make button for every function with label
    GtkWidget *button_set_slot_a = gtk_button_new_with_label("neuer aktiver Slot 'a'");
    GtkWidget *button_set_slot_b = gtk_button_new_with_label("neuer aktiver Slot 'b'");
    
    // Link the click callback function with the buttons 
    g_signal_connect(button_set_slot_a, "clicked", G_CALLBACK(set_slot_a), NULL);
    g_signal_connect(button_set_slot_b, "clicked", G_CALLBACK(set_slot_b), NULL);
    
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), button_set_slot_a, TRUE, TRUE, 0);
    
    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), button_set_slot_b, TRUE, TRUE, 0);
    
     // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all button
    gtk_widget_show(button_set_slot_a);
    gtk_widget_show(button_set_slot_b);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
}
    
