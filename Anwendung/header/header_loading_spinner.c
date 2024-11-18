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
 *      (C) Copyright 2024 Elias Mörz        *
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
        g_print("Log: Spinner is not initialized.\n");
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
    gtk_window_set_default_size(GTK_WINDOW(spinner_window), 200, 100);
    
    // connect destroy event
    g_signal_connect(spinner_window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);

    // add spinner
    spinner = gtk_spinner_new();
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(vbox), spinner);
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
    pthread_t thread;
	
	gtk_init();
    // create the spinner window
    create_spinner_window();

    // create new thread
    int result = pthread_create(&thread, NULL, thread_function, NULL);
    if (result != 0) 
    {
        g_print("Log: Failed to create thread: %d\n", result);
        return;
    }

    pthread_detach(thread);
    
    // run GTK main loop
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);
}

