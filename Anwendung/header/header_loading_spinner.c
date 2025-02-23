/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *      Apache License, Version 2.0          *
 *-------------------------------------------*
 *                                           *
 *  Programm um das Installieren von         *
 *  Custom-ROM und GSIs auf Android-Geräte   *
 *  zu erleichtern                           *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz        *
 *-------------------------------------------*
 *                                           *
 *       Headerpart - loading_spinner        *
 *                                           *
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
        LOG_INFO("Spinner is not initialized.");
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
        gtk_window_destroy(GTK_WINDOW(spinner_window));  // close the window
        spinner_window = NULL;  // set spinner_window NULL
    }
}

// create a window for a spinner
GtkWidget* create_spinner_window() 
{    
    // create new window
    spinner_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(spinner_window), " ");
    gtk_window_set_default_size(GTK_WINDOW(spinner_window), 200, 200);
    
    // connect destroy event
    g_signal_connect(spinner_window, "destroy", G_CALLBACK(on_window_destroy), main_loop);

    // add spinner
    spinner = gtk_spinner_new();
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(vbox), spinner);
    gtk_widget_set_size_request(spinner, 150, 150);
    gtk_window_set_child(GTK_WINDOW(spinner_window), vbox);
	

    // make the window visible using gtk_widget_set_visible
    gtk_widget_set_visible(spinner_window, TRUE);

    // start spinner
    start_loading_spinner();
    
    return spinner_window;
}

// function to start spinner in another thread
void run_with_spinner(void *(*thread_function)(void *)) 
{ 
    setenv("GSK_RENDERER", "cairo", 1);
    pthread_t thread;
	
	gtk_init();
	main_loop = g_main_loop_new(NULL, FALSE);
    // create the spinner window
    create_spinner_window();

    // create new thread
    int result = pthread_create(&thread, NULL, thread_function, NULL);
    if (result != 0) 
    {
        LOG_ERROR("Failed to create thread: %d", result);
        return;
    }

    pthread_detach(thread);
    
    // run GTK main loop
    g_main_loop_run(main_loop);
    
    if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
}

