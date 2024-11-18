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
 *       Headerpart - install_with_root      *
 *                                           *
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

// function to run command
void *run_install_command(void *command)
{
    char *full_command = (char *)command;

    // run command
    system(full_command);

    // close the spinner 
    g_idle_add((GSourceFunc)gtk_spinner_stop, spinner_install);
    g_idle_add((GSourceFunc)gtk_window_destroy, spinner_install_window);

    free(full_command);  // free memory
    return NULL;
}

// run the command with spinner
void install_with_root(GtkButton *button, GtkEntry *password_entry, const gchar *command) 
{
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(password_entry));
    gchar *full_command = g_strdup_printf("echo %s | sudo -S %s", password, command);
    
    // create new window for the spinner
    spinner_install_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(spinner_install_window), "Installation");
    gtk_window_set_default_size(GTK_WINDOW(spinner_install_window), 200, 100);
    
    // destroy event for the window
    g_signal_connect(spinner_install_window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);

    // create the spinner
    spinner_install = gtk_spinner_new();
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(vbox), spinner_install);
    gtk_window_set_child(GTK_WINDOW(spinner_install_window), vbox);
    
    // start spinner
    gtk_spinner_start(GTK_SPINNER(spinner_install));

    // show window with GTK4 alternative
    gtk_widget_set_visible(spinner_install_window, TRUE);

    // run command in a new thread
    pthread_t thread;
    pthread_create(&thread, NULL, run_install_command, full_command);
    pthread_detach(thread);  // thread in the background 
}

