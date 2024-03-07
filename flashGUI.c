/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - FlashGUI				 *
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
#include "flashheader.h"
#include "flashfunctionheader.h"

#define MAX_BUFFER_SIZE 256

// include all functions
extern void flashrecovery();
extern void flashboot();
extern void flashvendor();
extern void flashvendorboot();
extern void flashsystem();
extern void flashpayload();
extern void flashvbmeta();


// button 1 - flash recovery.img
static void on_buttonFr_clicked(GtkWidget *widget, gpointer data)
{
    flashrecovery();
}

// button 2 - flash boot.img
static void on_buttonFb_clicked(GtkWidget *widget, gpointer data)
{
	flashboot();
}

// button 3 - flash vendor.img
static void on_buttonFv_clicked(GtkWidget *widget, gpointer data)
{
	flashvendor();
}

// button 4 - flash vendor_boot.img
static void on_buttonFvboo_clicked(GtkWidget *widget, gpointer data)
{
	flashvendorboot();
}

// button 5 - flash system.img
static void on_buttonFs_clicked(GtkWidget *widget, gpointer data)
{
	flashsystem();
}

// button 6 - flash payload.zip
static void on_buttonFp_clicked(GtkWidget *widget, gpointer data)
{
	flashpayload();
}

// button 7 - flash vbmeta.img
static void on_buttonFvb_clicked(GtkWidget *widget, gpointer data)
{
	flashvbmeta();
}

/* start main programm */
void flashGUI(int argc, char *argv[])
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
    GtkWidget *buttonFr = gtk_button_new_with_label("Flash Recovery-Image");
    GtkWidget *buttonFb = gtk_button_new_with_label("Flash Boot-Image");
    GtkWidget *buttonFv = gtk_button_new_with_label("Flash Vendor-Image");
    GtkWidget *buttonFvboo = gtk_button_new_with_label("Flash Vendor_Boot-Image");
    GtkWidget *buttonFs = gtk_button_new_with_label("Flash System-Image");
    GtkWidget *buttonFp = gtk_button_new_with_label("Flash payload.zip");
    GtkWidget *buttonFvb = gtk_button_new_with_label("Flash vbmeta.img");        
    
    // Link the click callback function with the buttons 
    g_signal_connect(buttonFr, "clicked", G_CALLBACK(on_buttonFr_clicked), NULL);
    g_signal_connect(buttonFb, "clicked", G_CALLBACK(on_buttonFb_clicked), NULL);
    g_signal_connect(buttonFv, "clicked", G_CALLBACK(on_buttonFv_clicked), NULL);
    g_signal_connect(buttonFvboo, "clicked", G_CALLBACK(on_buttonFvboo_clicked), NULL);
    g_signal_connect(buttonFs, "clicked", G_CALLBACK(on_buttonFs_clicked), NULL);
    g_signal_connect(buttonFp, "clicked", G_CALLBACK(on_buttonFp_clicked), NULL);
    g_signal_connect(buttonFvb, "clicked", G_CALLBACK(on_buttonFvb_clicked), NULL);
    
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), buttonFr, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), buttonFv, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), buttonFs, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), buttonFvb, TRUE, TRUE, 0);
   
    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), buttonFb, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), buttonFvboo, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), buttonFp, TRUE, TRUE, 0);

    // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all button
    gtk_widget_show(buttonFr);
    gtk_widget_show(buttonFb);
    gtk_widget_show(buttonFv);
    gtk_widget_show(buttonFvboo);
    gtk_widget_show(buttonFs);
    gtk_widget_show(buttonFp);
    gtk_widget_show(buttonFvb);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
}
