/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_vendor			 *
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

// button 1 - flash vendor.img on only-a-devices
static void vendor_on_a(GtkWidget *widget, gpointer data)
{
    system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash vendor ~/Downloads/ROM-Install/vendor.img && exit");
}

// button 2 - flash vendor.img on a/b-devices
static void vendor_on_ab(GtkWidget *widget, gpointer data)
{
	system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash vendor_a ~/Downloads/ROM-Install/vendor.img && fastboot flash vendor_b ~/Downloads/ROM-Install/vendor.img && exit");
}

// button 3 - flash vendor_boot.img on only-a-devices
static void vendor_boot_on_a(GtkWidget *widget, gpointer data)
{
    system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash vendor_boot ~/Downloads/ROM-Install/vendor_boot.img && exit");
}

// button 4 - flash vendor_boot.img on a/b-devices
static void vendor_boot_on_ab(GtkWidget *widget, gpointer data)
{
	system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash vendor_boot_a ~/Downloads/ROM-Install/vendor_boot.img && fastboot flash vendor_boot_b ~/Downloads/ROM-Install/vendor_boot.img && exit");
}

/* start main programm */
void flash_vendor(int argc, char *argv[])
{
	// int gtk
	gtk_init(&argc, &argv);
	
	// make main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Flash Vendor");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// make button for every function with label
    GtkWidget *button_vendor_on_a = gtk_button_new_with_label("Flash Venodr (only-a-devices)");
    GtkWidget *button_vendor_on_ab = gtk_button_new_with_label("Flash Vendor (a/b-devices)");
    GtkWidget *button_vendor_boot_on_a = gtk_button_new_with_label("Flash vendor_boot (only-a-devices)");
    GtkWidget *button_vendor_boot_on_ab = gtk_button_new_with_label("Flash vendor_boot (a/b-devices)");
    
    // Link the click callback function with the buttons 
    g_signal_connect(button_vendor_on_a, "clicked", G_CALLBACK(vendor_on_a), NULL);
    g_signal_connect(button_vendor_on_ab, "clicked", G_CALLBACK(vendor_on_ab), NULL);
    g_signal_connect(button_vendor_boot_on_a, "clicked", G_CALLBACK(vendor_boot_on_a), NULL);
    g_signal_connect(button_vendor_boot_on_ab, "clicked", G_CALLBACK(vendor_boot_on_ab), NULL);
    
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), button_vendor_on_a, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_vendor_on_ab, TRUE, TRUE, 0);
    
    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), button_vendor_boot_on_a, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_vendor_boot_on_ab, TRUE, TRUE, 0);
    
     // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all button
    gtk_widget_show(button_vendor_on_a);
    gtk_widget_show(button_vendor_on_ab);
    gtk_widget_show(button_vendor_boot_on_a);
    gtk_widget_show(button_vendor_boot_on_ab);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
}
    
