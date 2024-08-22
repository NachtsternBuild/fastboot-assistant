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

// Button handler functions
// function to flash metadata.img
void metadata_img(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "metadata", NULL, "metadata.img");
}

// function to flash metadata.img (heimdall)
void metadata_img_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "METADATA", "metadata.img");
}

// function to flash userdata.img
void userdata_img(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "userdata", NULL, "userdata.img");
}

// function to flash userdata.img (heimdall)
void userdata_img_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "userdata", "userdata.img");
}

// main function
void flash_data(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    
    // create a windows
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Metadaten/Userdaten");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // create button
    GtkWidget *button_metadata_img = gtk_button_new_with_label("Flash Metadaten");
    GtkWidget *button_metadata_img_heimdall = gtk_button_new_with_label("Flash Metadaten (heimdall)");
    GtkWidget *button_userdata_img = gtk_button_new_with_label("Flash Userdaten");
    GtkWidget *button_init_boot_on_ab = gtk_button_new_with_label("Flash Userdaten (heimdall)");
    
    // connection for gtk callback
	g_signal_connect(button_metadata_img, "clicked", G_CALLBACK(metadata_img), (gpointer) window);
	g_signal_connect(button_metadata_img_heimdall, "clicked", G_CALLBACK(metadata_img_heimdall), (gpointer) window);
	g_signal_connect(button_userdata_img, "clicked", G_CALLBACK(userdata_img), (gpointer) window);
	g_signal_connect(button_userdata_img_heimdall, "clicked", G_CALLBACK(userdata_img_heimdall), (gpointer) window);
	
    // create widget
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    gtk_box_pack_start(GTK_BOX(left_vbox), button_metadata_img, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_metadata_img_heimdall, TRUE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(right_vbox), button_userdata_img, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_userdata_img_heimdall, TRUE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

	// add all to the container
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all widgets
    gtk_widget_show_all(window);
    
    gtk_main();
}

