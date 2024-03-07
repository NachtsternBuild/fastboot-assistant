/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - GUI					 *
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
#include <string.h>
#include "renamefunction.h"


#define MAX_BUFFER_SIZE 256

// include all functions
extern void renamefilerecovery();
extern void renamefileboot();
extern void renamefilevendor();
extern void renamefilesys();
extern void renamefilevbmeta();


// button 1 - rename recovery.img
static void on_buttonRr_clicked(GtkWidget *widget, gpointer data)
{
    renamefilerecovery();
}

// button 2 - rename boot.img
static void on_buttonRb_clicked(GtkWidget *widget, gpointer data)
{
	renamefileboot();
}

// button 3 - rename vendor.img
static void on_buttonRv_clicked(GtkWidget *widget, gpointer data)
{
	renamefilevendor();
}

// button 4 - rename system.img
static void on_buttonRs_clicked(GtkWidget *widget, gpointer data)
{
	renamefilesys();
}

// button 5 - rename vbmeta.img
static void on_buttonRvb_clicked(GtkWidget *widget, gpointer data)
{
	renamefilevbmeta();
}

/* start main programm */
void renameGUI(int argc, char *argv[])
{
	// int gtk
	gtk_init(&argc, &argv);
	
	// make main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Umbenennen");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// make button for every function
    GtkWidget *buttonRr = gtk_button_new_with_label("Recovery-Image");
    GtkWidget *buttonRb = gtk_button_new_with_label("Boot-Image");
    GtkWidget *buttonRv = gtk_button_new_with_label("Vendor-Image");
    GtkWidget *buttonRs = gtk_button_new_with_label("System-Image");
    GtkWidget *buttonRvb = gtk_button_new_with_label("vbmeta.img");        
    
    // Link the click callback function with the buttons 
    g_signal_connect(buttonRr, "clicked", G_CALLBACK(on_buttonRr_clicked), NULL);
    g_signal_connect(buttonRb, "clicked", G_CALLBACK(on_buttonRb_clicked), NULL);
    g_signal_connect(buttonRv, "clicked", G_CALLBACK(on_buttonRv_clicked), NULL);
    g_signal_connect(buttonRs, "clicked", G_CALLBACK(on_buttonRs_clicked), NULL);
    g_signal_connect(buttonRvb, "clicked", G_CALLBACK(on_buttonRvb_clicked), NULL);
    
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), buttonRr, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), buttonRv, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), buttonRvb, TRUE, TRUE, 0);
   
    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), buttonRb, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), buttonRs, TRUE, TRUE, 0);

    // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all button
    gtk_widget_show(buttonRr);
    gtk_widget_show(buttonRb);
    gtk_widget_show(buttonRv);
    gtk_widget_show(buttonRs);
    gtk_widget_show(buttonRvb);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
}
