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
 *         Headerpart - flash_heimdall       *
 *                                           *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include "program_functions.h"

// global vars
GtkWidget *spinner_heimdall;
GtkWidget *spinner_window_heimdall;

// function to run the command
void *run_heimdall_command(void *command)
{
    char *function_command = (char *)command;

    // run command
    g_print("Log: Run: %s\n", function_command);
    system(function_command);

    // close spinner and window
    gtk_spinner_stop(GTK_SPINNER(spinner_heimdall));
    gtk_window_destroy(GTK_WINDOW(spinner_window_heimdall));

    free(function_command);  // free memory
    return NULL;
}

// function to flash with heimdall
void flash_heimdall(GtkWidget *widget, GtkWindow *parent_window, const char *partition, const char *image_name)
{
    char image_path[3072];
    set_main_dir_with_wsl(image_path, sizeof(image_path), image_name);
    apply_theme();
    apply_language();

    // check if the image exsists
    if (access(image_path, F_OK) == -1)
    {
        char error_message[3072];
        snprintf(error_message, sizeof(error_message), "Fehler: Image-Datei '%s' nicht gefunden.", image_path);
        show_error_message(GTK_WIDGET(parent_window), error_message);
        return;
    }

    // create the command
    char *function_command = malloc(3072);
    snprintf(function_command, 3072, "heimdall flash --%s %s --no-reboot && exit", partition, image_path);

    // create new window
    spinner_window_heimdall = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(spinner_window_heimdall), " ");
    gtk_window_set_default_size(GTK_WINDOW(spinner_window_heimdall), 200, 100);

    // create the spinner
    spinner_heimdall = gtk_spinner_new();
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(vbox), spinner_heimdall);
    gtk_window_set_child(GTK_WINDOW(spinner_window_heimdall), vbox);

    // start the spinner
    gtk_spinner_start(GTK_SPINNER(spinner_heimdall));

    // show new window
    gtk_widget_show(spinner_window_heimdall);

    // run the command in a new thread
    pthread_t thread;
    pthread_create(&thread, NULL, run_heimdall_command, function_command);
    pthread_detach(thread);  // thread in the background
}

