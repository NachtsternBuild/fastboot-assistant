/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_recovery			 *
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
#include "function_header.h"
#include "flash_function_header.h"

// Button handler functions
// function to flash recovery.img on only-a-devices
void recovery_img(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "recovery", NULL, "recovery.img");
}

// function to flash recovery.img (heimdall)
void recovery_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "RECOVERY", "recovery.img");
}

// main function
void flash_recovery(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    
    // create a windows
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Flash Recovery");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // create button
    GtkWidget *button_recovery_img = gtk_button_new_with_label("Flash Recovery");
    GtkWidget *button_recovery_heimdall = gtk_button_new_with_label("Flash Recovery (heimdall)");
    
    // connection for gtk callback
	g_signal_connect(button_recovery_img, "clicked", G_CALLBACK(recovery_img), (gpointer) window);
	g_signal_connect(button_recovery_heimdall, "clicked", G_CALLBACK(recovery_heimdall), (gpointer) window);
	
    // create widget
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    gtk_box_pack_start(GTK_BOX(left_vbox), button_recovery_img, TRUE, TRUE, 0);
     
    gtk_box_pack_start(GTK_BOX(right_vbox), button_recovery_heimdall, TRUE, TRUE, 0);
   
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);
	
	// add all to the container
    gtk_container_add(GTK_CONTAINER(window), hbox);
    
    // show all widgets
    gtk_widget_show_all(window);
    
    gtk_main();
}
