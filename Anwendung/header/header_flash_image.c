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
 *         Headerpart - flash_image			 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include "program_functions.h"

// global var for spinner
GtkWidget *spinner_window_flash;
GtkWidget *spinner_flash;

// function that run flash command
void *run_flash_command(void *command)
{
    char *function_command = (char *)command;

    // run the command
    g_print("Executing: %s\n", function_command);
    system(function_command);

    // close the spinner and the window
    gtk_spinner_stop(GTK_SPINNER(spinner_flash));
    gtk_widget_destroy(spinner_window_flash);
    
    const char *message = "Fertig\n";
    // show message
    show_message(message);

    free(function_command);  // free memory
    return NULL;
}

// function to flash images with spinner
void flash_image(GtkWidget *widget, GtkWindow *parent_window, const char *partition1, const char *partition2, const char *image_name)
{
    char image_path[3072];
    char windows_image_path[3072];
    apply_theme();  // runing css

    // path for the image
    set_main_dir_with_wsl(image_path, sizeof(image_path), image_name);
	
	char *function_command = malloc(4096);
	 
    // check if the image exsists
    if (access(image_path, F_OK) == -1)
    {
        char error_message[3072];
        snprintf(error_message, sizeof(error_message), "Fehler: Image-Datei '%s' nicht gefunden.", image_path);
        show_error_message(GTK_WIDGET(parent_window), error_message);
        return;
    }
        
    if (partition2)
    {
         const char *device_command = fastboot_command();
         snprintf(function_command, 4096,
         "%s flash %s %s && fastboot flash %s %s && exit", device_command, partition1, image_path, partition2, image_path);
         free(device_command);
    }
    else
    {
          const char *device_command = fastboot_command();
          snprintf(function_command, 4096,
          "%s flash %s %s && exit", device_command, partition1, image_path);
          free(device_command);
    }

    // new windows with the spinner
    spinner_window_flash= gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(spinner_window_flash), " ");
    gtk_window_set_default_size(GTK_WINDOW(spinner_window_flash), 200, 100);

    // create spinner 
    spinner_flash = gtk_spinner_new();
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), spinner_flash, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(spinner_window_flash), vbox);

    // run spinner
    gtk_spinner_start(GTK_SPINNER(spinner_flash));

    // show new window
    gtk_widget_show_all(spinner_window_flash);

    // flash the image in new thread
    pthread_t thread;
    pthread_create(&thread, NULL, run_flash_command, function_command);
    pthread_detach(thread);  // thread in the background 
}

