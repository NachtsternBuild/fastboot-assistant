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
 *       Headerpart - loading_spinner		 *
 *											 *
 *-------------------------------------------*
 */
 
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <unistd.h>  
#include <sys/stat.h> 
#include <sys/types.h> 
#include <pthread.h>
#include "program_functions.h"
#include "loading_spinner.h"

GtkWidget *spinner = NULL;
GtkWidget *spinner_window = NULL;

// function to start the spinner
void start_loading_spinner() 
{
    if (GTK_IS_SPINNER(spinner)) 
    {
        gtk_spinner_start(GTK_SPINNER(spinner));
    } 
    else 
    {
        g_print("Spinner is not initialized.\n");
    }
}

// function to stop the spinner
void stop_loading_spinner() 
{
    if (GTK_IS_SPINNER(spinner)) 
    {
        gtk_spinner_stop(GTK_SPINNER(spinner));
    }
    if (spinner_window) 
    {
        gtk_widget_destroy(spinner_window);  // close the window
        spinner_window = NULL;  // Set to NULL after destroying
    }
}

// function to create the window
GtkWidget* create_spinner_window() 
{    
    // create a new window
    spinner_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(spinner_window), " ");
    gtk_window_set_default_size(GTK_WINDOW(spinner_window), 200, 100);

    // add the spinner
    spinner = gtk_spinner_new();
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), spinner, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(spinner_window), vbox);

    // show the window
    gtk_widget_show_all(spinner_window);  // Ensure all widgets are shown

    // start the spinner
    start_loading_spinner();
    
    return spinner_window;
}

// function to run spinner in another thread
void run_with_spinner(void *(*thread_function)(void *)) 
{ 
    pthread_t thread;

    // create the spinner window
    create_spinner_window();

    // create a new thread
    int result = pthread_create(&thread, NULL, thread_function, NULL);
    if (result != 0) 
    {
        g_print("Failed to create thread: %d\n", result);
        return;
    }

    pthread_detach(thread);
    
     // Run the GTK main loop
    gtk_main();
}
