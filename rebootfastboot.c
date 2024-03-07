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
 *              rebootfastboot				 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main programm */
#include <gtk/gtk.h>
#include <stdlib.h>

// Function to reboot into Fastboot
void rebootfastbootfunction() 
{
    GtkWidget *dialog;
    const char *message = "Neustart wird durchgeführt...\nGerät im Fastboot verfügbar:";

    dialog = gtk_message_dialog_new(NULL,
                                     GTK_DIALOG_MODAL,
                                     GTK_MESSAGE_INFO,
                                     GTK_BUTTONS_OK,
                                     "%s\n", message);

    // Show the device list
    system("fastboot devices");

    // Reboot into Fastboot
    system("fastboot reboot");

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Callback function when the button is clicked
void buttonrbf_clicked(GtkWidget *widget, gpointer data) 
{
    rebootfastbootfunction();
}

void rebootfastboot(int argc, char *argv[]) 
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Neustart von Fastboot");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create a button
    GtkWidget *button = gtk_button_new_with_label("Neustart");
    g_signal_connect(button, "clicked", G_CALLBACK(buttonrbf_clicked), NULL);

    // Pack the button into the box
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    // Show all the widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}

