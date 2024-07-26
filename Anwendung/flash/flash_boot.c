/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_boot				 *
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

// button 1 - flash boot.img on only-a-devices
static void boot_on_a(GtkWidget *widget, gpointer data)
{
    system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash boot ~/Downloads/ROM-Install/boot.img && exit");
}

// button 2 - flash boot.img on a/b-devices
static void boot_on_ab(GtkWidget *widget, gpointer data)
{
	system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash boot_a ~/Downloads/ROM-Install/boot.img && fastboot flash boot_b ~/Downloads/ROM-Install/boot.img && exit");
}

// button 3 - flash init_boot.img on only-a-devices
static void init_boot_on_a(GtkWidget *widget, gpointer data)
{
    system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash init_boot ~/Downloads/ROM-Install/init_boot.img && exit");
}

// button 4 - flash init_boot.img on a/b-devices
static void init_boot_on_ab(GtkWidget *widget, gpointer data)
{
	system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash init_boot_a ~/Downloads/ROM-Install/init_boot.img && fastboot flash init_boot_b ~/Downloads/ROM-Install/init_boot.img && exit");
}

// button 5 - flash boot.img heimdall
static void boot_heimdall(GtkWidget *widget, gpointer data)
{
	char function_command[255];
	open_terminal_by_desktop("heimall flash --BOOT ~/Downloads/ROM-Install/boot.img --no-reboot && exit");
}

// button 6 - flash init_boot.img heimdall
static void init_boot_heimdall(GtkWidget *widget, gpointer data)
{
	char function_command[255];
	open_terminal_by_desktop("heimdall flash --INIT_BOOT ~/Downloads/ROM-Install/init_boot.img --no-reboot && exit");
}

/* start main programm */
void flash_boot(int argc, char *argv[])
{
	// int gtk
	gtk_init(&argc, &argv);
	
	// make main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Flash Boot");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// make button for every function with label
    GtkWidget *button_boot_on_a = gtk_button_new_with_label("Flash Boot (only-a-devices)");
    GtkWidget *button_boot_on_ab = gtk_button_new_with_label("Flash Boot (a/b-devices)");
    GtkWidget *button_init_boot_on_a = gtk_button_new_with_label("Flash init_boot (only-a-devices)");
    GtkWidget *button_init_boot_on_ab = gtk_button_new_with_label("Flash init_boot (a/b-devices)");
    GtkWidget *button_init_boot_on_a = gtk_button_new_with_label("Flash boot (heimdall)");
    GtkWidget *button_init_boot_on_ab = gtk_button_new_with_label("Flash init_boot (heimdall)");
    
    // Link the click callback function with the buttons 
    g_signal_connect(button_boot_on_a, "clicked", G_CALLBACK(boot_on_a), NULL);
    g_signal_connect(button_boot_on_ab, "clicked", G_CALLBACK(boot_on_ab), NULL);
    g_signal_connect(button_init_boot_on_a, "clicked", G_CALLBACK(init_boot_on_a), NULL);
    g_signal_connect(button_init_boot_on_ab, "clicked", G_CALLBACK(init_boot_on_ab), NULL);
    g_signal_connect(button_boot_heimdall, "clicked", G_CALLBACK(boot_heimdall), NULL);
    g_signal_connect(button_init_boot_heimdall, "clicked", G_CALLBACK(init_boot_heimdall), NULL);
    
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), button_boot_on_a, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_boot_on_ab, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_boot_heimdall, TRUE, TRUE, 0);
    
    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), button_init_boot_on_a, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_init_boot_on_ab, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_init_boot_heimdall, TRUE, TRUE, 0);
    
     // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all button
    gtk_widget_show(button_boot_on_a);
    gtk_widget_show(button_boot_on_ab);
    gtk_widget_show(button_init_boot_on_a);
    gtk_widget_show(button_init_boot_on_ab);
    gtk_widget_show(button_boot_heimdall);
    gtk_widget_show(button_init_boot_heimdall);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
}
    
