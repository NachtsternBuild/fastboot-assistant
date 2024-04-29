/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_GUI				 *
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

#define MAX_BUFFER_SIZE 256

// include all functions
extern void flash_recovery();
extern void flash_boot();
extern void flash_vendor();
extern void flash_system();
extern void flash_payload();
extern void flash_vbmeta();


// button 1 - flash recovery.img
static void start_flash_recovery_button(GtkWidget *widget, gpointer data)
{
    flash_recovery();
}

// button 2 - flash boot.img
static void start_flash_boot_button(GtkWidget *widget, gpointer data)
{
	flash_boot();
}

// button 3 - flash vendor.img
static void start_flash_vendor_button(GtkWidget *widget, gpointer data)
{
	flash_vendor();
}

// button 4 - flash system.img
static void start_flash_system_button(GtkWidget *widget, gpointer data)
{
	flash_system();
}

// button 5 - flash payload.zip
static void start_flash_payload_button(GtkWidget *widget, gpointer data)
{
	flash_payload();
}

// button 6 - flash vbmeta.img
static void start_flash_vbmeta_button(GtkWidget *widget, gpointer data)
{
	flash_vbmeta();
}

/* start main programm */
void flash_GUI(int argc, char *argv[])
{
	// int gtk
	gtk_init(&argc, &argv);
	
	// make main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Flash");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// make button for every function
    GtkWidget *button_flash_reco = gtk_button_new_with_label("Flash Recovery-Image");
    GtkWidget *button_flash_boot = gtk_button_new_with_label("Flash Boot-Image");
    GtkWidget *button_flash_vendor = gtk_button_new_with_label("Flash Vendor-Image");
    GtkWidget *button_flash_system = gtk_button_new_with_label("Flash System-Image");
    GtkWidget *button_flash_payload = gtk_button_new_with_label("Flash payload.zip");
    GtkWidget *button_flash_vbmeta = gtk_button_new_with_label("Flash vbmeta.img");        
    
    // Link the click callback function with the buttons 
    g_signal_connect(button_flash_reco, "clicked", G_CALLBACK(start_flash_recovery_button), NULL);
    g_signal_connect(button_flash_boot, "clicked", G_CALLBACK(start_flash_boot_button), NULL);
    g_signal_connect(button_flash_vendor, "clicked", G_CALLBACK(start_flash_vendor_button), NULL);
    g_signal_connect(button_flash_system, "clicked", G_CALLBACK(start_flash_system_button), NULL);
    g_signal_connect(button_flash_payload, "clicked", G_CALLBACK(start_flash_payload_button), NULL);
    g_signal_connect(button_flash_vbmeta, "clicked", G_CALLBACK(start_flash_vbmeta_button), NULL);
    
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), button_flash_reco, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_flash_boot, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_flash_vendor, TRUE, TRUE, 0);
   
    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), button_flash_system, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_flash_vbmeta, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_flash_payload, TRUE, TRUE, 0);

    // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all button
    gtk_widget_show(button_flash_reco);
    gtk_widget_show(button_flash_boot);
    gtk_widget_show(button_flash_vendor);
    gtk_widget_show(button_flash_system);
    gtk_widget_show(button_flash_payload);
    gtk_widget_show(button_flash_vbmeta);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
}
