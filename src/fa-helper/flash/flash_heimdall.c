/**
* flash_heimdall.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/

#include "fastboot_assistant.h"

// function to flash with heimdall
void flash_heimdall(GtkWidget *widget, const char *partition, const char *image_name) 
{
    // let's see if we still need that with the new adw dialog
    //setenv("GSK_RENDERER", "cairo", 1);
    
    char config_file[4096]; 
    char image_info[4096];
    
    get_config_file_path(config_file, sizeof(config_file));
    // load the path
    const char *image_path = load_path_from_file(config_file);

    if (image_path) 
    {
        LOGI("Loaded path: %s", image_path);
    }
    
    snprintf(image_info, sizeof(image_info), "%s/%s", image_path, image_name);
    
    // check if the image exists
    if (access(image_info, F_OK) == -1) 
    {
        char error_message[4096];
        snprintf(error_message, sizeof(error_message), _("Image file '%s' not found.\n"), image_info); 	
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {   	
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    // create the command
    char *function_command = malloc(4096); // bigger buffer for bigger commands
    snprintf(function_command, 4096, "heimdall flash --%s %s --no-reboot", partition, image_info);
    
    const char *title = _("Heimdall running");
    char message[256]; // Korrigiert: Jetzt ein char Array, kein Array von Pointern
    snprintf(message, sizeof(message), _("Flashing %s ..."), partition);
    
    // run the command with dialog spinner
    //show_spinner_dialog(GTK_WIDGET(main_window), title, message, function_command);
    // option:
    // use the porgress bar
    show_progress_dialog(GTK_WIDGET(main_window), title, message, function_command);
    
    if (image_path != NULL) 
    {
        g_free((gpointer)image_path); // free the info (because g_file_get_contents was used)
    }
}
