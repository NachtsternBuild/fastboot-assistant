/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              lock_unlock_bootloader		 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

#define MAX_BUFFER_SIZE 256

// button 1 - unlock bootloader new
static void bootloader_new(GtkWidget *widget, gpointer data)
{
    GtkWidget *dialog;
    const char *title, *message;
    
    title = "Unlock bootloader new";
    message = "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n\nStarte Vorgang um den Bootloader zu öffnen.\n";
    show_message_with_title(title, message);
    
    system("fastboot flashing unlock");
}

// button 2 - unlock bootloader old
static void bootloader_old(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
    const char *title, *message;
    
    title = "Unlock bootloader old";
    message = "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n\nStarte Vorgang um den Bootloader zu öffnen.";
    show_message_with_title(title, message);
    
    system("fastboot oem unlock");
}

// button 3 - lock bootloader
static void bootloader_lock(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
    const char *title, *message;
    
    title = "Lock bootloader";
    message = "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n\nStarte Vorgang um den Bootloader zu schließen.";
    show_message_with_title(title, message);
    
    system("fastboot flashing lock");
}


/* start main programm */
void lock_unlock_bootloader(int argc, char *argv[])
{
	// int gtk
	gtk_init(&argc, &argv);
	
	// make main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - öffnen/schließen Bootloader");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// make button for every function
    GtkWidget *button_bootloader_new = gtk_button_new_with_label("Öffnen Booloader neue Methode");
    GtkWidget *button_bootloader_old = gtk_button_new_with_label("Öffnen Bootlader alte Methode");
    GtkWidget *button_bootloader_lock = gtk_button_new_with_label("Schließen des Bootloaders");     
    
    // Link the click callback function with the buttons 
    g_signal_connect(button_bootloader_new, "clicked", G_CALLBACK(bootloader_new), NULL);
    g_signal_connect(button_bootloader_old, "clicked", G_CALLBACK(bootloader_old), NULL);
    g_signal_connect(button_bootloader_lock, "clicked", G_CALLBACK(bootloader_lock), NULL);
    
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), button_bootloader_new, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_bootloader_old, TRUE, TRUE, 0);
   
    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), button_bootloader_lock, TRUE, TRUE, 0);

    // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all button
    gtk_widget_show(button_bootloader_new);
    gtk_widget_show(button_bootloader_old);
    gtk_widget_show(button_bootloader_lock);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
}
