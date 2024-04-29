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
 *              boot_fastboot				 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main program */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// Function to boot into Fastboot or display Fastboot commands
void boot_fastboot_function(const char *option) 
{
    GtkWidget *dialog;
    const char *title, *message;

    if (strcmp(option, "boot") == 0) 
    {
        title = "Boot Fastboot";
        message = "!!! Beachten sie, dass USB-Debugging aktiviert ist in den Entwickleroptionen.!!!\n Neustart in den Fastboot-Modus...\n";
        system("adb devices");
        system("adb reboot bootloader");
    } 
    
    else if (strcmp(option, "commands") == 0) 
    {
        title = "Fastboot Commands List";
        message = "Gerät im Fastboot verfügbar:\n";
        system("fastboot devices");
        system("fastboot help");
    } 
    
    else if (strcmp(option, "variables") == 0) 
    {
        title = "Auflisten aller Bootloader Variablen";
        message = "Gerät im Fastboot verfügbar:\nBefehl wird ausgeführt...\n";
        system("fastboot devices");
        system("fastboot getvar all");
    } 
    
    else 
    {
        title = "Unbekannte Option";
        message = "Sie wissen auch nicht was sie wollen, oder?";
    }

    show_message_with_title(title, message);
}

// Callback function when the button is clicked
void button_boot_fastboot_start(GtkWidget *widget, gpointer data) 
{
    const char *option = (const char *)data;
    boot_fastboot_function(option);
}

void boot_fastboot(int argc, char *argv[]) 
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Boot in Fastboot-Modus");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create buttons
    GtkWidget *button_boot = gtk_button_new_with_label("Boot Fastboot");
    g_signal_connect(button_boot, "clicked", G_CALLBACK(button_boot_fastboot_start), "boot");

    GtkWidget *button_commands = gtk_button_new_with_label("Fastboot-Kommand Liste");
    g_signal_connect(button_commands, "clicked", G_CALLBACK(button_boot_fastboot_start), "commands");

    GtkWidget *button_variables = gtk_button_new_with_label("Alle Bootloader Variablen");
    g_signal_connect(button_variables, "clicked", G_CALLBACK(button_boot_fastboot_start), "variables");

    // Pack buttons into the box
    gtk_box_pack_start(GTK_BOX(vbox), button_boot, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_commands, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_variables, TRUE, TRUE, 0);

    // Show all the widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}

