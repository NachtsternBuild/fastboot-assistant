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

// Button handler functions
// function to flash vbmeta.img on only-a-devices
void vbmeta_on_a(GtkWidget *widget, GtkWindow *window)
{
    char image_path[512];
    set_main_dir_with_wsl(image_path, sizeof(image_path), "vbmeta.img");

    char function_command[255];
    snprintf(function_command, sizeof(function_command), "fastboot flash --disable-verity --disable-verification vbmeta %s && exit", image_path);
    g_print(function_command);
    open_terminal_by_desktop(function_command);
}

// function to flash vbmeta.img (a/b-devices)
void vbmeta_on_ab(GtkWidget *widget, GtkWindow *window)
{
    char image_path[512];
    set_main_dir_with_wsl(image_path, sizeof(image_path), "vbmeta.img");

    char function_command[255];
    snprintf(function_command, sizeof(function_command), "fastboot flash --disable-verity --disable-verification vbmeta_a %s && fastboot flash --disable-verity --disable-verification vbmeta_b %s && exit", image_path, image_path);
    g_print(function_command);
    open_terminal_by_desktop(function_command);
}

// function to flash dtbo.img (only-a-devices)
void dtbo_on_a(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "dtbo", NULL, "dtbo.img");
}

// function to flash dtbo.img (a/b-devices)
void dtbo_on_ab(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "dtbo_a", "dtbo_b", "dtbo.img");
}

// function to flash vbmeta.img (heimdall)
void vbmeta_img_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "VBMETA", "vbmeta.img");
}

// function to flash dtbo.img (heimdall)
void dtbo_on_ab_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "DTBO", "dtbo.img");
}

// main function
void flash_vbmeta_dtbo(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    
    // create a windows
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Flash vbmeta/dtbo");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // create button
    GtkWidget *button_vbmeta_on_a = gtk_button_new_with_label("Flash vbmeta (only-a-devices)");
    GtkWidget *button_vbmeta_on_ab = gtk_button_new_with_label("Flash vbmeta (a/b-devices)");
    GtkWidget *button_dtbo_on_a = gtk_button_new_with_label("Flash dtbo (only-a-devices)");
    GtkWidget *button_dtbo_on_ab = gtk_button_new_with_label("Flash dtbo (a/b-devices)");
    GtkWidget *button_vbmeta_img_heimdall = gtk_button_new_with_label("Flash vbmeta (heimdall)");
    GtkWidget *button_dtbo_on_ab_heimdall = gtk_button_new_with_label("Flash dtbo (heimdall)");
    
    // connection for gtk callback
	g_signal_connect(button_vbmeta_on_a, "clicked", G_CALLBACK(vbmeta_on_a), (gpointer) window);
	g_signal_connect(button_vbmeta_on_ab, "clicked", G_CALLBACK(vbmeta_on_ab), (gpointer) window);
	g_signal_connect(button_dtbo_on_a, "clicked", G_CALLBACK(dtbo_on_a), (gpointer) window);
	g_signal_connect(button_dtbo_on_ab, "clicked", G_CALLBACK(dtbo_on_ab), (gpointer) window);
	g_signal_connect(button_vbmeta_img_heimdall, "clicked", G_CALLBACK(vbmeta_img_heimdall), (gpointer) window);
	g_signal_connect(button_dtbo_on_ab_heimdall, "clicked", G_CALLBACK(dtbo_on_ab_heimdall), (gpointer) window);

    // create widget
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    gtk_box_pack_start(GTK_BOX(left_vbox), button_vbmeta_on_a, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_vbmeta_on_ab, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_vbmeta_img_heimdall, TRUE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(right_vbox), button_dtbo_on_a, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_dtbo_on_ab, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_dtbo_on_ab_heimdall, TRUE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

	// add all to the container
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all widgets
    gtk_widget_show_all(window);
    
    gtk_main();
}

