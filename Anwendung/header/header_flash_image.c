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

// Function to flash images, utilizing the modified path handling for WSL
void flash_image(GtkWidget *widget, GtkWindow *parent_window, const char *partition1, const char *partition2, const char *image_name) 
{
    char image_path[3072];
    char windows_image_path[3072];
    
    // Set the path to the image file considering WSL
    set_main_dir_with_wsl(image_path, sizeof(image_path), image_name);

    // Check if the image exists
    if (access(image_path, F_OK) == -1) 
    {
        char error_message[3072];
        snprintf(error_message, sizeof(error_message), "Fehler: Image-Datei '%s' nicht gefunden.", image_path);
        show_error_message(GTK_WIDGET(parent_window), error_message);
        return;
    }

    // Convert the WSL path to Windows path
    convert_wsl_path(windows_image_path, sizeof(windows_image_path), image_path);

    // Get fastboot devices
    system("fastboot devices");

    char function_command[3072];

    // Check if running inside WSL
    if (system("grep -q Microsoft /proc/version") == 0) 
    {
        // Use cmd.exe to execute fastboot commands from WSL with converted Windows path
        if (partition2) 
        {
            snprintf(function_command, sizeof(function_command),
                     "cmd.exe /C start cmd.exe /K \"fastboot flash %s %s && fastboot flash %s %s\"",
                     partition1, windows_image_path, partition2, windows_image_path);
        } 
        
        else 
        {
            snprintf(function_command, sizeof(function_command),
                     "cmd.exe /C start cmd.exe /K \"fastboot flash %s %s\"",
                     partition1, windows_image_path);
        }
    } 
    
    else 
    {
        // For native Linux environment
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

    // Debug output
    g_print("Executing: %s\n", function_command);
    // Run the command using the appropriate terminal
    open_terminal_by_desktop(function_command);
}



