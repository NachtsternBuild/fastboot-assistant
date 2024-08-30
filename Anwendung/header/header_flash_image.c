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
#include "program_functions.h"

// function to flash images
void flash_image(GtkWidget *widget, GtkWindow *parent_window, const char *partition1, const char *partition2, const char *image_name) {
    char image_path[512];
    // Set the path to the image file taking into account the WSL environment
    set_main_dir_with_wsl(image_path, sizeof(image_path), image_name);

    // check if image exsists
    if (access(image_path, F_OK) == -1) 
    {
        char error_message[256];
        snprintf(error_message, sizeof(error_message), "Fehler: Image-Datei '%s' nicht gefunden.", image_path);
        show_error_message(GTK_WIDGET(parent_window), error_message);
        return;
    }
    
    // get fastboot devices
    system("fastboot devices");
    
    char function_command[512];
    
    // create a command for wsl
    if (system("grep -q Microsoft /proc/version") == 0) 
    {
        // use the cmd.exe to flash
        if (partition2) 
        {
            snprintf(function_command, sizeof(function_command), 
                     "cmd.exe /C start cmd.exe /K \"fastboot flash %s %s && fastboot flash %s %s\"", 
                     partition1, image_path, partition2, image_path);
        } 
        
        else 
        {
            snprintf(function_command, sizeof(function_command), 
                     "cmd.exe /C start cmd.exe /K \"fastboot flash %s %s\"", 
                     partition1, image_path);
        }
    } 
    
    else 
    {
        // for native linux
        if (partition2) 
        {
            snprintf(function_command, sizeof(function_command), 
                     "fastboot flash %s %s && fastboot flash %s %s && exit", 
                     partition1, image_path, partition2, image_path);
        } 
        
        else 
        {
            snprintf(function_command, sizeof(function_command), 
                     "fastboot flash %s %s && exit", partition1, image_path);
        }
    }

    // debuggins
    g_print("Executing: %s\n", function_command);
    // run the command
    open_terminal_by_desktop(function_command);
}

