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
 *              reboot_fastboot				 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main program */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

#define MAX_BUFFER_SIZE 256

// reboot to bootloader from adb
static void reboot_from_adb(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
    const char *title, *message;
    
    title = "Reboot from ADB";
    message = "Beachten sie, dass USB-Debugging aktiviert ist in den Entwickleroptionen!\n";
    
    show_message_with_title(title, message);
    system("adb -d reboot bootloader");
}

// reboot to bootloader from fastboot
static void reboot_from_fastboot(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
    const char *message;
    
    message = "Beachten sie, dass sich ihr Gerät im Fastboot-Modus befindet!\n";
    
    show_message(message);
    system("fastboot reboot bootloader");
}
	
// start help-function
static void fastboot_help(GtkWidget *widget, gpointer data) 
{
    GtkWidget *dialog;
    const char *message = "Beachten sie, dass sich ihr Gerät im Fastboot-Modus befindet!\n";
    
    show_message(message);
    char function_command[255];
    open_terminal_by_desktop("fastboot help");
}

// get bootloader variablen-function
static void list_bootloader_var(GtkWidget *widget, gpointer data) 
{
    GtkWidget *dialog;
    const char *message = "Beachten sie, dass sich ihr Gerät im Fastboot-Modus befindet!\n";
    
    show_message(message);
    char function_command[255];
    open_terminal_by_desktop("fastboot getvar all");
}

/* start main programm */
void reboot_fastboot(int argc, char *argv[])
{
	// int gtk
	gtk_init(&argc, &argv);
	
	// make main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Neustart");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// make button for every function
    GtkWidget *button_reboot_from_adb = gtk_button_new_with_label("Neustart in Fastboot");
    GtkWidget *button_reboot_from_fastboot = gtk_button_new_with_label("Neustart in Fastboot (von Fastboot)");
    GtkWidget *button_fastboot_help = gtk_button_new_with_label("Fastboot Hilfe");
    GtkWidget *button_fastboot_var = gtk_button_new_with_label("Bootloader Variablen anzeigen");
    
    
    // Link the click callback function with the buttons 
    g_signal_connect(button_reboot_from_adb, "clicked", G_CALLBACK(reboot_from_adb), NULL);
    g_signal_connect(button_reboot_from_fastboot, "clicked", G_CALLBACK(reboot_from_fastboot), NULL);
    g_signal_connect(button_fastboot_help, "clicked", G_CALLBACK(fastboot_help), NULL);
    g_signal_connect(button_fastboot_var, "clicked", G_CALLBACK(list_bootloader_var), NULL);

    
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), button_reboot_from_adb, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_fastboot_help, TRUE, TRUE, 0);
   
    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), button_reboot_from_fastboot, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_fastboot_var, TRUE, TRUE, 0);

    // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all button
    gtk_widget_show(button_reboot_from_adb);
    gtk_widget_show(button_reboot_from_fastboot);
    gtk_widget_show(button_fastboot_help);
    gtk_widget_show(button_fastboot_var);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
}
