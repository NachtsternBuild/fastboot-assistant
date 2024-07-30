/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - backup_function		 *
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

// the root backup skript in c need a little test
// extern void backup_root();

// button 1 - backup with root
static void get_backup_root(GtkWidget *widget, gpointer data)
{
    // backup_root();
    // this is if the c-code not work
    char function_command[255];
    open_terminal_by_desktop("bash /usr/bin/projekt-122/backup_root.sh");
}

// button 3 - backup without root
static void get_backup_noroot(GtkWidget *widget, gpointer data)
{
	
	// char function_command[255];
	/* thanks to @mrrfv for the backup-skripts */
	// open_terminal_by_desktop("bash backup.sh");
	backup_noroot();
}

void backup_function(int argc, char *argv[])
{
	// int gtk
	gtk_init(&argc, &argv);
	
	// make main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Backup");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// make button for every function
    GtkWidget *button_get_backup_root = gtk_button_new_with_label("Root Backups");
    GtkWidget *button_get_backup_noroot = gtk_button_new_with_label("Backup ohne Root");     
    
    // Link the click callback function with the buttons 
    g_signal_connect(button_get_backup_root, "clicked", G_CALLBACK(get_backup_root), NULL);
    g_signal_connect(button_get_backup_noroot, "clicked", G_CALLBACK(get_backup_noroot), NULL);
   
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), button_get_backup_root, TRUE, TRUE, 0);
   
    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), button_get_backup_noroot, TRUE, TRUE, 0);

    // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all button
    gtk_widget_show(button_get_backup_root);
    gtk_widget_show(button_get_backup_noroot);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
}
