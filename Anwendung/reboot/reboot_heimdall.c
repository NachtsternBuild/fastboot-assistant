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
 *              reboot_heimdall				 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main program */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

#define MAX_BUFFER_SIZE 256

// reboot to download from adb
static void reboot_from_adb_heimdall(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
    const char *title, *message;
    
    title = "Reboot from ADB";
    message = "Beachten sie, dass USB-Debugging aktiviert ist in den Entwickleroptionen!\n";
    
    show_message_with_title(title, message);
    system("adb reboot download");
}

// heimdall help
static void heimdall_help(GtkWidget *widget, gpointer data)
{ 
    char function_command[255];
    open_terminal_by_desktop("heimdall help");
}
	
// get pit
static void get_pit(GtkWidget *widget, gpointer data) 
{
    GtkWidget *dialog;
    const char *message = "Beachten sie, dass sich ihr Gerät im Download-Modus befindet!\n";
    
    show_message(message);
    char function_command[255];
    open_terminal_by_desktop("heimdall print-pit");
}

/* start main programm */
void reboot_heimdall(int argc, char *argv[])
{
	// int gtk
	gtk_init(&argc, &argv);
	
	// make main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Neustart Heimdall");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	// make button for every function
    GtkWidget *button_reboot_from_adb_heimdall = gtk_button_new_with_label("Neustart Download Modus (von der ADB)");
    GtkWidget *button_heimdall_help = gtk_button_new_with_label("Heimdall Hilfe");
    GtkWidget *button_get_pit = gtk_button_new_with_label("Pit ausgeben");
    
    
    // Link the click callback function with the buttons 
    g_signal_connect(button_reboot_from_adb_heimdall, "clicked", G_CALLBACK(reboot_from_adb_heimdall), NULL);
    g_signal_connect(button_heimdall_help, "clicked", G_CALLBACK(heimdall_help), NULL);
    g_signal_connect(button_get_pit, "clicked", G_CALLBACK(get_pit), NULL);

    
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), button_reboot_from_adb_heimdall, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_heimdall_help, TRUE, TRUE, 0);
   
    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), button_get_pit, TRUE, TRUE, 0);

    // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all button
    gtk_widget_show(button_reboot_from_adb_heimdall);
    gtk_widget_show(button_heimdall_help);
    gtk_widget_show(button_get_pit);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
}
