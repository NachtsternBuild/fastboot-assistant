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
 *              change_dir					 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main program */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gtk/gtk.h>

// Function to change directory
void change_dir_function() 
{
    // set download as main dir
    const char *downloads_dir = getenv("HOME");
    if (downloads_dir == NULL) 
    {
        fprintf(stderr, "Fehler beim Abrufen des Heimatverzeichnisses.\n");
        return;
    }

    // get specified dir
    const char *folder_name = "ROM-Install";
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/Downloads/%s", downloads_dir, folder_name);

    // change to specified dir
    if (chdir(full_path) == 0) 
    {
        printf("In das Verzeichnis gewechselt: %s\n", full_path);
    }
     
    else 
    {
        perror("Fehler beim Wechseln des Verzeichnisses");
    }
}

// Callback function when the button is clicked
void button_cd_start(GtkWidget *widget, gpointer data)
{
    change_dir_function();
}

void change_dir(int argc, char *argv[]) 
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Directory Changer");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create a button
    GtkWidget *button = gtk_button_new_with_label("Change Directory");
    g_signal_connect(button, "clicked", G_CALLBACK(button_cd_start), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    // Show all the widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}
