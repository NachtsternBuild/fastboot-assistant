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
#include "language_check.h"

// global vars
GtkWidget *spinner_heimdall;
GtkWidget *spinner_window_heimdall;

// function to run the command
void *run_heimdall_command(void *command) 
{
    char *function_command = (char *)command;

    // run command
    LOG_INFO("Run: %s", function_command);
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
    if (!parent_window) parent_window = main_window;
    
    setenv("GSK_RENDERER", "cairo", 1);
    
    char config_file[4096];  
    char image_info[4096];
    // set_main_dir_with_wsl(image_path, sizeof(image_path), image_name);
    apply_theme();
    apply_language();
    
    get_config_file_path(config_file, sizeof(config_file));
    // load the path
    const char *image_path = load_path_from_file(config_file);

    if (image_path) 
    {
        LOG_INFO("Loaded path: %s", image_path);
    }
    
	snprintf(image_info, sizeof(image_info), "%s/%s", image_path, image_name);
    // check if the image exists
    if (access(image_info, F_OK) == -1) 
    {
        char error_message[4096];
        snprintf(error_message, sizeof(error_message), g_strcmp0(language, "de") == 0 ? "Image nicht '%s' gefunden.\n" : "Image file '%s' not found.\n", image_info);
        show_error_message(GTK_WIDGET(parent_window), error_message);
        return;
    }
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = strcmp(language, "de") == 0 ? "Kein Gerät erkannt." : "No device detected.";
        show_error_message(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    // create the command
    char *function_command = malloc(4096); // bigger buffer for bigger commands
    snprintf(function_command, 4096, "heimdall flash --%s %s --no-reboot", partition, image_info);

    // create new window
    spinner_window_heimdall = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(spinner_window_heimdall), " ");
    gtk_window_set_default_size(GTK_WINDOW(spinner_window_heimdall), 200, 200);

    // create the spinner
    spinner_heimdall = gtk_spinner_new();
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(vbox), spinner_heimdall);
    gtk_widget_set_size_request(spinner_heimdall, 150, 150);
    gtk_window_set_child(GTK_WINDOW(spinner_window_heimdall), vbox);

    // start the spinner
    gtk_spinner_start(GTK_SPINNER(spinner_heimdall));

    // show new window (using gtk_widget_set_visible instead of deprecated gtk_widget_show)
    gtk_widget_set_visible(spinner_window_heimdall, TRUE);

    // run the command in a new thread
    pthread_t thread;
    pthread_create(&thread, NULL, run_heimdall_command, function_command);
    pthread_detach(thread);  // thread in the background
    
    if (image_path != NULL) 
	{
    	g_free((gpointer)image_path); // free the info (because g_file_get_contents was used)
	}
}
