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
 *         Headerpart - flash_image          *
 *                                           *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include "program_functions.h"
#include "language_check.h"

// global vars
GtkWidget *spinner_window_flash;
GtkWidget *spinner_flash;

// run the command
void *run_flash_command(void *command)
{
    char *function_command = (char *)command;

    // run the command
    g_print("Log: Run: %s\n", function_command);
    system(function_command);

    // end the spinner
    gtk_spinner_stop(GTK_SPINNER(spinner_flash));
    gtk_window_destroy(GTK_WINDOW(spinner_window_flash));

    free(function_command);  // free memory
    return NULL;
}

// function to flash an image
void flash_image(GtkWidget *widget, GtkWindow *parent_window, const char *partition1, const char *partition2, const char *image_name)
{
    char image_path[3072];
    apply_theme();
    apply_language();

    // create the path for the image
    set_main_dir_with_wsl(image_path, sizeof(image_path), image_name);
    
    char *function_command = malloc(8192);  // Increase buffer size

    // check if the image exists
    if (access(image_path, F_OK) == -1)
    {
        char error_message[3072];
        snprintf(error_message, sizeof(error_message), "Log: Error: Image file '%s' not found.\n", image_path);
        show_error_message(GTK_WIDGET(parent_window), error_message);
        free(function_command);  // Free allocated memory
        return;
    }

    // create the command
    const char *device_command = fastboot_command();

    // for a/b-devices
    if (partition2)
    {
        snprintf(function_command, 8192, "%s flash %s %s && %s flash %s %s && exit",
                 device_command, partition1, image_path, device_command, partition2, image_path);
    }
    // for only-a-devices
    else
    {
        snprintf(function_command, 8192, "%s flash %s %s && exit", device_command, partition1, image_path);
    }

    // create a new window
    spinner_window_flash = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(spinner_window_flash), " ");
    gtk_window_set_default_size(GTK_WINDOW(spinner_window_flash), 200, 100);

    // create spinner
    spinner_flash = gtk_spinner_new();
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(vbox), spinner_flash);
    gtk_window_set_child(GTK_WINDOW(spinner_window_flash), vbox);

    // start the spinner
    gtk_spinner_start(GTK_SPINNER(spinner_flash));

    // show the window
    gtk_widget_set_visible(spinner_window_flash, TRUE);  // Replaced gtk_widget_show

    // run command in a new thread
    pthread_t thread;
    pthread_create(&thread, NULL, run_flash_command, function_command);
    pthread_detach(thread);  // thread in the background
}

