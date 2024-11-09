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

// Funktion, um den Spinner zu starten
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

// Funktion, um den Spinner zu stoppen
void stop_loading_spinner() 
{
    if (GTK_IS_SPINNER(spinner)) 
    {
        gtk_spinner_stop(GTK_SPINNER(spinner));
    }
    if (spinner_window) 
    {
        gtk_window_destroy(GTK_WINDOW(spinner_window));  // Fenster schließen
        spinner_window = NULL;  // Nach dem Schließen auf NULL setzen
    }
}

// Funktion, um das Fenster zu erstellen
GtkWidget* create_spinner_window() 
{    
    // Neues Fenster erstellen
    spinner_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(spinner_window), " ");
    gtk_window_set_default_size(GTK_WINDOW(spinner_window), 200, 100);
    
    // "destroy"-Signal verbinden
    g_signal_connect(spinner_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Spinner hinzufügen
    spinner = gtk_spinner_new();
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(vbox), spinner);
    gtk_window_set_child(GTK_WINDOW(spinner_window), vbox);

    // Fenster anzeigen
    gtk_widget_show(spinner_window);

    // Spinner starten
    start_loading_spinner();
    
    return spinner_window;
}

// Funktion, um den Spinner in einem anderen Thread zu starten
void run_with_spinner(void *(*thread_function)(void *)) 
{ 
    pthread_t thread;

    // Spinner-Fenster erstellen
    create_spinner_window();

    // Neuen Thread erstellen
    int result = pthread_create(&thread, NULL, thread_function, NULL);
    if (result != 0) 
    {
        g_print("Failed to create thread: %d\n", result);
        return;
    }

    pthread_detach(thread);
    
    // GTK-Hauptschleife ausführen
    gtk_main();
}

