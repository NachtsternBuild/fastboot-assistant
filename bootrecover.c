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
 *              bootrecover					 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main programm */
#include <gtk/gtk.h>
#include <stdlib.h>

// Function to boot into recovery
void bootrecoverfunction(const char *option) 
{
    GtkWidget *dialog;
    const char *title, *message;

    if (strcmp(option, "Fastboot") == 0) 
    {
        title = "Boot von Fastboot";
        message = "Neustart ins Recovery...\n";
        system("fastboot devices");
        system("fastboot reboot recovery");
    } 
    
    else if (strcmp(option, "ADB") == 0) 
    {
        title = "Boot von der ADB";
        message = "Neustart ins Recovery...\n";
        system("adb devices");
        system("adb reboot recovery");
    } 
    
    else 
    {
        title = "Unbekannte Option";
        message = "Sie wissen auch nicht was sie wollen, oder?";
    }

    dialog = gtk_message_dialog_new(NULL,
                                     GTK_DIALOG_MODAL,
                                     GTK_MESSAGE_INFO,
                                     GTK_BUTTONS_OK,
                                     "%s\n\n%s", title, message);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Callback function when the button is clicked
void buttonbr_clicked(GtkWidget *widget, gpointer data) 
{
    const char *option = (const char *)data;
    bootrecoverfunction(option);
}

void bootrecover(int argc, char *argv[]) 
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Boot ins Recovery von:");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create buttons
    GtkWidget *button_boot = gtk_button_new_with_label("Fastboot");
    g_signal_connect(button_boot, "clicked", G_CALLBACK(buttonbr_clicked), "Fastboot");

    GtkWidget *button_commands = gtk_button_new_with_label("ADB");
    g_signal_connect(button_commands, "clicked", G_CALLBACK(buttonbr_clicked), "ADB");

    // Pack buttons into the box
    gtk_box_pack_start(GTK_BOX(vbox), button_boot, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_commands, TRUE, TRUE, 0);
    
    // Show all the widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}
