/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_preloader_super	 *
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

// button 1 - flash preloader.bin on only-a-devices
static void preloader_bin_on_a(GtkWidget *widget, gpointer data)
{
    system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash preloader ~/Downloads/ROM-Install/preloader.bin && exit");
}

// button 2 - flash preloader.bin on a/b-devices
static void preloader_bin_on_ab(GtkWidget *widget, gpointer data)
{
	system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash preloader_a ~/Downloads/ROM-Install/preloader.bin && fastboot flash preloader_b ~/Downloads/ROM-Install/preloader.bin && exit");
}

// button 3 - flash preloader.img on only-a-devices
static void preloader_img_on_a(GtkWidget *widget, gpointer data)
{
    system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash preloader ~/Downloads/ROM-Install/preloader.img && exit");
}

// button 4 - flash preloader.img on a/b-devices
static void preloader_img_on_ab(GtkWidget *widget, gpointer data)
{
	system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash preloader_a ~/Downloads/ROM-Install/preloader.img && fastboot flash preloader_b ~/Downloads/ROM-Install/preloader.img && exit");
}

// button 5 - flash super.img on a/b-devices
static void super_img(GtkWidget *widget, gpointer data)
{
	system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash super ~/Downloads/ROM-Install/super.img && exit");
}

/* start main programm */
void flash_preloader_super(int argc, char *argv[])
{
	// int gtk
	gtk_init(&argc, &argv);
	
	// make main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Flash Preloader/Super");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// make button for every function with label
    GtkWidget *button_preloader_bin_on_a = gtk_button_new_with_label("Flashen preloader.bin (only-a-devices)");
    GtkWidget *button_preloader_bin_on_ab = gtk_button_new_with_label("Flashen preloader.bin (a/b-devices)");
    GtkWidget *button_preloader_img_on_a = gtk_button_new_with_label("Flashen preloader.img (only-a-devices)");
    GtkWidget *button_preloader_img_on_ab = gtk_button_new_with_label("Flashen preloader.img (a/b-devices)");
    GtkWidget *button_super_img = gtk_button_new_with_label("Flashen super.img (a/b-devices)");
    
    // Link the click callback function with the buttons 
    g_signal_connect(button_preloader_bin_on_a, "clicked", G_CALLBACK(preloader_bin_on_a), NULL);
    g_signal_connect(button_preloader_bin_on_ab, "clicked", G_CALLBACK(preloader_bin_on_ab), NULL);
    g_signal_connect(button_preloader_img_on_a, "clicked", G_CALLBACK(preloader_img_on_a), NULL);
    g_signal_connect(button_preloader_img_on_ab, "clicked", G_CALLBACK(preloader_img_on_ab), NULL);
    g_signal_connect(button_super_img, "clicked", G_CALLBACK(super_img), NULL);
    
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), button_preloader_bin_on_a, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_preloader_bin_on_ab, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_super_img, TRUE, TRUE, 0);
    
    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), button_preloader_img_on_a, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_preloader_img_on_ab, TRUE, TRUE, 0);
    
     // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all button
    gtk_widget_show(button_preloader_bin_on_a);
    gtk_widget_show(button_preloader_bin_on_ab);
    gtk_widget_show(button_preloader_img_on_a);
    gtk_widget_show(button_preloader_img_on_ab);
    gtk_widget_show(super_img);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
}
    
