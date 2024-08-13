/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_recovery			 *
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

// button 1 - flash recovery.img
static void recovery_img(GtkWidget *widget, gpointer data)
{
    system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash recovery ~/Downloads/ROM-Install/recovery.img && exit");
}

// button 2 - flash recovery.img heimdall
static void recovery_heimdall(GtkWidget *widget, gpointer data)
{
	system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("heimdall flash --RECOVERY ~/Downloads/ROM-Install/recovery.img --no-reboot && exit");
}


void flash_recovery(int argc, char *argv[])
{
	// int gtk
	gtk_init(&argc, &argv);
	
	// make main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Flash Recovery");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	// make button for every function with label
    GtkWidget *button_recovery_img = gtk_button_new_with_label("Flash Recovery");
    GtkWidget *button_recovery_heimdall = gtk_button_new_with_label("Flash Recovery (heimdall)");
    
    // Link the click callback function with the buttons 
    g_signal_connect(button_recovery_img, "clicked", G_CALLBACK(recovery_img), NULL);
    g_signal_connect(button_recovery_heimdall, "clicked", G_CALLBACK(recovery_heimdall), NULL);
    
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), button_recovery_img, TRUE, TRUE, 0);
    
    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), button_recovery_heimdall, TRUE, TRUE, 0);
    
     // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all button
    gtk_widget_show(button_recovery_img);
    gtk_widget_show(button_recovery_heimdall);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
}
    
