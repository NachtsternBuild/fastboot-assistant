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


// Button handler functions
// function to flash preloader.bin on only-a-devices
void preloader_bin_on_a(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "preloader", NULL, "preloader.bin");
}

// function to flash preloader.bin (a/b-devices)
void preloader_bin_on_ab(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "preloader_a", "preloader_b", "preloader.bin");
}

// function to flash preloader.img (only-a-devices)
void preloader_img_on_a(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "preloader", NULL, "preloader.img");
}

// function to flash preloader.img (a/b-devices)
void preloader_img_on_ab(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "preloader_a", "preloader_b", "preloader.img");
}

// function to flash super.img
void super_img(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "super", NULL, "super.img");
}

// function to flash preloader.bin (heimdall)
void preloader_bin_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "PRELOADER", "preloader.bin");
}

// function to flash preloader.img (heimdall)
void preloader_img_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "PRELOADER", "preloader.img");
}

// function to flash super.img (heimdall)
void super_img_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "SUPER", "super.img");
}

// main function
void flash_preloader_super(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    
    // create a windows
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Flash Preloader/Super");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // create button
    GtkWidget *button_preloader_bin_on_a = gtk_button_new_with_label("Flashen preloader.bin (only-a-devices)");
    GtkWidget *button_preloader_bin_on_ab = gtk_button_new_with_label("Flashen preloader.bin (a/b-devices)");
    GtkWidget *button_preloader_img_on_a = gtk_button_new_with_label("Flashen preloader.img (only-a-devices)");
    GtkWidget *button_preloader_img_on_ab = gtk_button_new_with_label("Flashen preloader.img (a/b-devices)");
    GtkWidget *button_super_img = gtk_button_new_with_label("Flashen super.img");
    GtkWidget *button_preloader_bin_heimdall= gtk_button_new_with_label("Flashen preloader.bin (heimdall)");
    GtkWidget *button_preloader_img_heimdall = gtk_button_new_with_label("Flashen preloader.img (heimdall)");
    GtkWidget *button_super_img_heimdall= gtk_button_new_with_label("Flashen super.img (heimdall)");
    
    // connection for gtk callback
	g_signal_connect(button_preloader_bin_on_a, "clicked", G_CALLBACK(preloader_bin_on_a), (gpointer) window);
	g_signal_connect(button_preloader_bin_on_ab, "clicked", G_CALLBACK(preloader_bin_on_ab), (gpointer) window);
	g_signal_connect(button_preloader_img_on_a, "clicked", G_CALLBACK(preloader_img_on_a), (gpointer) window);
	g_signal_connect(button_preloader_img_on_ab, "clicked", G_CALLBACK(preloader_img_on_ab), (gpointer) window);
	g_signal_connect(button_super_img, "clicked", G_CALLBACK(super_img), (gpointer) window);
	g_signal_connect(button_preloader_bin_heimdall, "clicked", G_CALLBACK(preloader_bin_heimdall), (gpointer) window);
	g_signal_connect(button_preloader_img_heimdall, "clicked", G_CALLBACK(preloader_img_heimdall), (gpointer) window);
	g_signal_connect(button_super_img_heimdall, "clicked", G_CALLBACK(super_img_heimdall), (gpointer) window);
	
    // create widget
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    gtk_box_pack_start(GTK_BOX(left_vbox), button_preloader_bin_on_a, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_preloader_bin_on_ab, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_preloader_img_on_a, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_preloader_img_on_ab, TRUE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(right_vbox), button_super_img, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_super_img_heimdall, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_preloader_bin_heimdall, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_preloader_img_heimdall, TRUE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

	// add all to the container
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all widgets
    gtk_widget_show_all(window);
    
    gtk_main();
}
