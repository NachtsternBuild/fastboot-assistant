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
 *         Headerpart - flash_heimdall		 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// function to flash images via heimdall
void flash_heimdall(GtkWidget *widget, GtkWindow *parent_window, const char *partition, const char *image_name)
{
    char image_path[512];
    set_main_dir_with_wsl(image_path, sizeof(image_path), image_name);

    if (access(image_path, F_OK) == -1) 
    {
        char error_message[256];
        snprintf(error_message, sizeof(error_message), "Fehler: Image-Datei '%s' nicht gefunden.", image_path);
        show_error_message(GTK_WIDGET(parent_window), error_message);
        return;
    }

    char function_command[512];
    snprintf(function_command, sizeof(function_command), 
             "heimdall flash --%s %s --no-reboot && exit", partition, image_path);

    g_print("Executing: %s\n", function_command);
    open_terminal_by_desktop(function_command);
}

