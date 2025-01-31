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
 *       Headerpart - install_with_pkexec    *
 *                                           *
 *-------------------------------------------*
 */

/* headers */ 
#include <glib.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include "program_functions.h"

GtkWidget *spinner_install = NULL;
GtkWidget *spinner_install_window = NULL;

// function to run command in the background
void *run_install_with_pkexec(void *command)
{
    char *full_command = (char *)command;

    // run command
    LOG_INFO("Run: %s", full_command);
    system(full_command);

    // stop the spinner and close the window
    gtk_spinner_stop(GTK_SPINNER(spinner_install));
    gtk_window_destroy(GTK_WINDOW(spinner_install_window));

    free(full_command);  // free memory
    return NULL;
}

// function to run a command via root use pkexec
void install_with_pkexec(const gchar *command) 
{
    gtk_init();
    apply_theme();

    gchar *full_command = g_strdup_printf("pkexec %s", command);
	
    // create a new window
    spinner_install_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(spinner_install_window), " ");
    gtk_window_set_default_size(GTK_WINDOW(spinner_install_window), 200, 200);

    // create a spinner
    spinner_install = gtk_spinner_new();
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(vbox), spinner_install);
    gtk_widget_set_size_request(spinner_install, 150, 150);
    gtk_window_set_child(GTK_WINDOW(spinner_install_window), vbox);
	
    // start the spinner
    gtk_spinner_start(GTK_SPINNER(spinner_install));

    // make the window visible using gtk_window_present
    gtk_window_present(GTK_WINDOW(spinner_install_window));

    // run command in a new thread
    pthread_t thread;
    pthread_create(&thread, NULL, run_install_with_pkexec, full_command);
    pthread_detach(thread);  // run thread in the background
}
