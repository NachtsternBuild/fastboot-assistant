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

// button 1 - flash vbmeta.img on only-a-devices
static void vbmeta_on_a(GtkWidget *widget, gpointer data)
{
    system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash --disable-verity --disable-verification vbmeta ~/Downloads/ROM-Install/vbmeta.img && exit");
}

// button 2 - flash vbmeta.img on a/b-devices
static void vbmeta_on_ab(GtkWidget *widget, gpointer data)
{
	system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash --disable-verity --disable-verification vbmeta_a ~/Downloads/ROM-Install/vbmeta.img && fastboot flash --disable-verity --disable-verification vbmeta_b ~/Downloads/ROM-Install/vbmeta.img && exit");
}

// button 3 - flash dtbo.img on only-a-devices
static void dtbo_on_a(GtkWidget *widget, gpointer data)
{
    system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash dtbo ~/Downloads/ROM-Install/dtbo.img && exit");
}

// button 4 - flash dtbo.img on a/b-devices
static void dtbo_on_ab(GtkWidget *widget, gpointer data)
{
	system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash dtbo_a ~/Downloads/ROM-Install/dtbo.img && fastboot flash dtbo_b ~/Downloads/ROM-Install/dtbo.img && exit");
}

// button 5 - flash metadata.img
static void metadata_img(GtkWidget *widget, gpointer data)
{
    system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash metadata ~/Downloads/ROM-Install/metadata.img && exit");
}

// button 6 - flash userdata.img
static void userdata_img(GtkWidget *widget, gpointer data)
{
	system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("fastboot flash userdata ~/Downloads/ROM-Install/userdata.img && exit");
}

// button 7 - flash vbmeta.img heimdall
static void vbmeta_img_heimdall(GtkWidget *widget, gpointer data)
{
	char function_command[255];
	open_terminal_by_desktop("heimdall flash --VBMETA ~/Downloads/ROM-Install/vbmeta.img && exit");
}

// button 8 - flash metadata.img heimdall
static void metadata_img_heimdall(GtkWidget *widget, gpointer data)
{
	char function_command[255];
	open_terminal_by_desktop("heimdall flash --METADATA ~/Downloads/ROM-Install/metadata.img && exit");
}

// button 9 - flash userdata.img heimdall
static void userdata_img_heimdall(GtkWidget *widget, gpointer data)
{
	char function_command[255];
	open_terminal_by_desktop("heimdall flash --USERDATA ~/Downloads/ROM-Install/userdata.img && exit");
}

/* start main programm */
void flash_vbmeta_dtbo(int argc, char *argv[])
{
	// int gtk
	gtk_init(&argc, &argv);
	
	// make main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Flash vbmeta/dtbo/metadata/userdata");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// make button for every function with label
    GtkWidget *button_vbmeta_on_a = gtk_button_new_with_label("Flash vbmeta.img (only-a-devices)");
    GtkWidget *button_vbmeta_on_ab = gtk_button_new_with_label("Flash vbmeta.img (a/b-devices)");
    GtkWidget *button_dtbo_on_a = gtk_button_new_with_label("Flash dtbo.img (only-a-devices)");
    GtkWidget *button_dtbo_on_ab = gtk_button_new_with_label("Flash dtbo.img (a/b-devices)");
    GtkWidget *button_metadata_img = gtk_button_new_with_label("Flash metadata.img");
    GtkWidget *button_userdata_img = gtk_button_new_with_label("Flash userdata.img");
    GtkWidget *button_vbmeta_img_heimdall = gtk_button_new_with_label("Flash vbmeta.img (heimdall)");
    GtkWidget *button_metadata_img_heimdall = gtk_button_new_with_label("Flash metadata.img (heimdall)");
    GtkWidget *button_userdata_img_heimdall = gtk_button_new_with_label("Flash userdata.img (heimdall)");
    
    // Link the click callback function with the buttons 
    g_signal_connect(button_vbmeta_on_a, "clicked", G_CALLBACK(vbmeta_on_a), NULL);
    g_signal_connect(button_vbmeta_on_ab, "clicked", G_CALLBACK(vbmeta_on_ab), NULL);
    g_signal_connect(button_dtbo_on_a, "clicked", G_CALLBACK(dtbo_on_a), NULL);
    g_signal_connect(button_dtbo_on_ab, "clicked", G_CALLBACK(dtbo_on_ab), NULL);
    g_signal_connect(button_metadata_img, "clicked", G_CALLBACK(metadata_img), NULL);
    g_signal_connect(button_userdata_img, "clicked", G_CALLBACK(userdata_img), NULL);
    g_signal_connect(button_vbmeta_img_heimdall, "clicked", G_CALLBACK(vbmeta_img_heimdall), NULL);
    g_signal_connect(button_metadata_img_heimdall, "clicked", G_CALLBACK(metadata_img_heimdall), NULL);
    g_signal_connect(button_userdata_img_heimdall, "clicked", G_CALLBACK(userdata_img_heimdall), NULL);
    
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), button_vbmeta_on_a, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_vbmeta_on_ab, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_metadata_img, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_userdata_img, TRUE, TRUE, 0);
    
    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), button_dtbo_on_a, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_dtbo_on_ab, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_vbmeta_img_heimdall, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_metadata_img_heimdall, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_userdata_img_heimdall, TRUE, TRUE, 0);
    
        
     // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all button
    gtk_widget_show(button_vbmeta_on_a);
    gtk_widget_show(button_vbmeta_on_ab);
    gtk_widget_show(button_dtbo_on_a);
    gtk_widget_show(button_dtbo_on_ab);
    gtk_widget_show(button_metadata_img);
    gtk_widget_show(button_userdata_img);
    gtk_widget_show(button_vbmeta_img_heimdall);
    gtk_widget_show(button_metadata_img_heimdall);
    gtk_widget_show(button_userdata_img_heimdall);    
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
}
    
