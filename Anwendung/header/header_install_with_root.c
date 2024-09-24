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
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *       Headerpart - install_with_root		 *
 *											 *
 *-------------------------------------------*
 */

/* headers */ 
#include <stdlib.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include "program_functions.h"
#include "loading_spinner.h"

GtkWidget *spinner_install = NULL;
GtkWidget *spinner_install_window = NULL;
/*
// function that run flash command
void *run_install_command(void *command)
{
    char *full_command = (char *)command;

    // run the command
    system(full_command);

    // close the spinner and the window
    gtk_spinner_stop(GTK_SPINNER(spinner_install));
    gtk_widget_destroy(spinner_install_window);
    
    const char *message = "Fertig\n";
    // show message
    show_message(message);

    free(full_command);  // free memory
    return NULL;
}

// function to start the command and run the spinner
void install_with_root(GtkButton *button, GtkEntry *password_entry, const gchar *command) 
{
    int argc = 0;
    char **argv = NULL;
    
    gtk_init(&argc, &argv);
    apply_theme();
	
	const gchar *password = gtk_entry_get_text(password_entry);
    gchar *full_command = g_strdup_printf("echo %s | sudo -S %s", password, command);
	
    // new windows with the spinner
    spinner_install_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(spinner_install_window), " ");
    gtk_window_set_default_size(GTK_WINDOW(spinner_install_window), 200, 100);
    
    // the "destroy" signal to gtk_main_quit
    g_signal_connect(spinner_install_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // create spinner 
    spinner_install = gtk_spinner_new();
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), spinner_install, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(spinner_install_window), vbox);
	
    // run spinner
    gtk_spinner_start(GTK_SPINNER(spinner_install));

    // show new window
    gtk_widget_show_all(spinner_install_window);
	
    // flash the image in new thread
    pthread_t thread;
    pthread_create(&thread, NULL, run_install_command, full_command);
    pthread_detach(thread);  // thread in the background

    gtk_main();
}
*/
// Function that runs the flash command in a separate thread
// Function that runs the flash command in a separate thread
void *run_install_command(void *command)
{
    char *full_command = (char *)command;

    // Run the command
    system(full_command);

    // Stop the spinner and close the spinner window safely from the main thread
    gdk_threads_add_idle((GSourceFunc)gtk_spinner_stop, spinner_install);
    gdk_threads_add_idle((GSourceFunc)gtk_widget_destroy, spinner_install_window);

    const char *message = "Fertig\n";
    // Show message (again safely from the main thread)
    gdk_threads_add_idle((GSourceFunc)show_message, (gpointer)message);

    free(full_command);  // Free memory
    return NULL;
}

// Function to start the command and run the spinner
void install_with_root(GtkButton *button, GtkEntry *password_entry, const gchar *command) 
{
    const gchar *password = gtk_entry_get_text(password_entry);
    gchar *full_command = g_strdup_printf("echo %s | sudo -S %s", password, command);
    
    // Create a new window with the spinner
    spinner_install_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(spinner_install_window), "Installation läuft...");
    gtk_window_set_default_size(GTK_WINDOW(spinner_install_window), 200, 100);
    
    // No `gtk_main_quit` signal on window destroy to avoid quitting the main program
    g_signal_connect(spinner_install_window, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

    // Create spinner and add it to the window
    spinner_install = gtk_spinner_new();
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), spinner_install, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(spinner_install_window), vbox);
    
    // Start the spinner
    gtk_spinner_start(GTK_SPINNER(spinner_install));

    // Show the spinner window
    gtk_widget_show_all(spinner_install_window);

    // Flash the image in a new thread
    pthread_t thread;
    pthread_create(&thread, NULL, run_install_command, full_command);
    pthread_detach(thread);  // Detach thread to run in the background
}


