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
 *       Headerpart - command_with_spinner	 *
 *											 *
 *-------------------------------------------*
 */

/* headers */ 
#include <stdlib.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include "program_functions.h"

GtkWidget *spinner_command = NULL;
GtkWidget *spinner_command_window = NULL;

// function that run flash command
void *run_command_spinner(void *command)
{
    char *full_command = (char *)command;

    // run the command
    g_print("Executing: %s\n", full_command);
    system(full_command);

    // close the spinner and the window
    gtk_spinner_stop(GTK_SPINNER(spinner_command));
    gtk_widget_destroy(spinner_command_window);
    
    const char *message = "Fertig\n";
    // show message
    show_message(message);

    free(full_command);  // free memory
    return NULL;
}

// function to start the command and run the spinner
void command_with_spinner(const gchar *command) 
{
    int argc = 0;
    char **argv = NULL;
    
    gtk_init(&argc, &argv);
    apply_theme();

    gchar *full_command = g_strdup_printf("%s", command);
	
    // new windows with the spinner
    spinner_command_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(spinner_command_window), " ");
    gtk_window_set_default_size(GTK_WINDOW(spinner_command_window), 200, 100);

    // create spinner 
    spinner_command = gtk_spinner_new();
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), spinner_command, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(spinner_command_window), vbox);
	
    // run spinner
    gtk_spinner_start(GTK_SPINNER(spinner_command));

    // show new window
    gtk_widget_show_all(spinner_command_window);
	
    // flash the image in new thread
    pthread_t thread;
    pthread_create(&thread, NULL, run_command_spinner, full_command);
    pthread_detach(thread);  // thread in the background

    gtk_main();
}


