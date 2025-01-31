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
 *       Headerpart - command_with_spinner   *
 *                                           *
 *-------------------------------------------*
 */

/* headers */ 
#include <stdlib.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include "language_check.h"
#include "program_functions.h"

GtkWidget *spinner_command = NULL;
GtkWidget *spinner_command_window = NULL;

// function to run command in the background
void *run_command_spinner(void *command)
{
    char *full_command = (char *)command;

    // run command
    LOG_INFO("Run: %s", full_command);
    system(full_command);

    // stop the spinner
    gtk_spinner_stop(GTK_SPINNER(spinner_command));
    gtk_window_destroy(GTK_WINDOW(spinner_command_window));
    free(full_command);  // free memory
    return NULL;
}

// function to start the spinner and the command
void command_with_spinner(const gchar *command) 
{
    setenv("GSK_RENDERER", "cairo", 1);
    gtk_init();  // Initialize GTK without command-line arguments
    apply_theme();

    gchar *full_command = g_strdup_printf("%s", command);
	
    // create a new window
    spinner_command_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(spinner_command_window), " ");
    gtk_window_set_default_size(GTK_WINDOW(spinner_command_window), 200, 200);

    // create a spinner
    spinner_command = gtk_spinner_new();
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(vbox), spinner_command);
    gtk_widget_set_size_request(spinner_command, 150, 150);
    gtk_window_set_child(GTK_WINDOW(spinner_command_window), vbox);
	
    // start the spinner
    gtk_spinner_start(GTK_SPINNER(spinner_command));

    // make the window visible using gtk_window_present
    gtk_window_present(GTK_WINDOW(spinner_command_window));

    // run command in a new thread
    pthread_t thread;
    pthread_create(&thread, NULL, run_command_spinner, full_command);
    pthread_detach(thread);  // run thread in the background
}

