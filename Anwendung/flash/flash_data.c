/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_vbmeta_dtbo		 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "flash_function_header.h"

// button 1 - flash metadata.img
static void metadata_img(GtkWidget *widget, gpointer data)
{
    system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash metadata ~/Downloads/ROM-Install/metadata.img && exit");
}

// button 2 - flash userdata.img
static void userdata_img(GtkWidget *widget, gpointer data)
{
	system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash userdata ~/Downloads/ROM-Install/userdata.img && exit");
}

// button 3 - flash metadata.img heimdall
static void metadata_img_heimdall(GtkWidget *widget, gpointer data)
{
	char function_command[255];
	open_terminal_by_desktop("heimdall flash --METADATA ~/Downloads/ROM-Install/metadata.img --no-reboot && exit");
}

// button 4 - flash userdata.img heimdall
static void userdata_img_heimdall(GtkWidget *widget, gpointer data)
{
	char function_command[255];
	open_terminal_by_desktop("heimdall flash --USERDATA ~/Downloads/ROM-Install/userdata.img --no-reboot && exit");
}

/* start main programm */
void flash_vbmeta_dtbo(int argc, char *argv[])
{
	// int gtk
	gtk_init(&argc, &argv);
	
	// make main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Flash metadata/userdata");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// make button for every function with label
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

    // show all button
    gtk_widget_show(button_metadata_img);
    gtk_widget_show(button_userdata_img);
    gtk_widget_show(button_metadata_img_heimdall);
    gtk_widget_show(button_userdata_img_heimdall);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
}
