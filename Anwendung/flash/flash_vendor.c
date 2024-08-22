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

// Button handler functions
// function to flash vendor.img on only-a-devices
void vendor_on_a(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "vendor", NULL, "vendor.img");
}

// function to flash vendor.img (a/b-devices)
void vendor_on_ab(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "vendor_a", "vendor_b", "vendor.img");
}

// function to flash vendor_boot.img (only-a-devices)
void vendor_boot_on_a(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "vendor_boot", NULL, "vendor_boot.img");
}

// function to flash vendor_boot.img (a/b-devices)
void vendor_boot_on_ab(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "vendor_boot_a", "vendor_boot_b", "vendor_boot.img");
}

// function to flash boot.img (heimdall)
void vendor_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "VENDOR", "vendor.img");
}

// function to flash init_boot.img (heimdall)
void vendor_boot_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "VENDOR_BOOT", "vendor_boot.img");
}

// main function
void flash_vendor(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    
    // create a windows
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Flash Vendor");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // create button
    GtkWidget *button_vendor_on_a = gtk_button_new_with_label("Flash Vendor (only-a-devices)");
    GtkWidget *button_vendor_on_ab = gtk_button_new_with_label("Flash Vendor (a/b-devices)");
    GtkWidget *button_vendor_boot_on_a = gtk_button_new_with_label("Flash vendor_boot (only-a-devices)");
    GtkWidget *button_vendor_boot_on_ab = gtk_button_new_with_label("Flash vendor_boot (a/b-devices)");
    GtkWidget *button_vendor_heimdall = gtk_button_new_with_label("Flash Vendor (heimdall)");
    GtkWidget *button_vendor_boot_heimdall = gtk_button_new_with_label("Flash vendor_boot (heimdall)");
    
    // connection for gtk callback
	g_signal_connect(button_vendor_on_a, "clicked", G_CALLBACK(vendor_on_a), (gpointer) window);
	g_signal_connect(button_vendor_on_ab, "clicked", G_CALLBACK(vendor_on_ab), (gpointer) window);
	g_signal_connect(button_vendor_boot_on_a, "clicked", G_CALLBACK(vendor_boot_on_a), (gpointer) window);
	g_signal_connect(button_vendor_boot_on_ab, "clicked", G_CALLBACK(vendor_boot_on_ab), (gpointer) window);
	g_signal_connect(button_vendor_heimdall, "clicked", G_CALLBACK(vendor_heimdall), (gpointer) window);
	g_signal_connect(button_vendor_boot_heimdall, "clicked", G_CALLBACK(vendor_boot_heimdall), (gpointer) window);

    // create widget
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    gtk_box_pack_start(GTK_BOX(left_vbox), button_vendor_on_a, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_vendor_on_ab, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_vendor_heimdall, TRUE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(right_vbox), button_vendor_boot_on_a, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_vendor_boot_on_ab, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_vendor_boot_heimdall, TRUE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

	// add all to the container
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all widgets
    gtk_widget_show_all(window);
    
    gtk_main();
}

