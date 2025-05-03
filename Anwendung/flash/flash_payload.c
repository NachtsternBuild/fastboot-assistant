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
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              flash_payload				 *
 *											 *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

void flash_payload(GtkWidget *widget, gpointer data)
{
    LOG_INFO("flash_payload");
    apply_language();
    char config_file_payload[4096];  
    char payload_info[4096];
    
    // flash payload.zip via adb sideload   
    // create the path to the payload.zip
    get_config_file_path(config_file_payload, sizeof(config_file_payload));
    // load the path
    const char *payload_path = load_path_from_file(config_file_payload);
	
	const char *payload_name = "payload.zip";
	
    if (payload_path) 
    {
        LOG_INFO("Loaded path: %s", payload_path);
    }
    
	snprintf(payload_info, sizeof(payload_info), "%s/%s", payload_path, payload_name);
    // check if the image exists
    if (access(payload_info, F_OK) == -1) 
    {
        // no payload.zip found
        char error_message[4096];
        snprintf(error_message, sizeof(error_message), g_strcmp0(language, "de") == 0 ? "Image in '%s' nicht gefunden.\n" : "Image file '%s' not found.\n", payload_info);
        show_message(error_message);
        return;
    }
    
    // first dialog
    const char *message = strcmp(language, "de") == 0 ? "Der Prozess zum flashen des payload.zip geht davon aus, \ndass sie sich im Recovery befinden und 'Updates über ADB erlauben' aktiviert haben." : "The process for flashing the payload.zip assumes that \nyou are in Recovery and have activated 'Allow updates via ADB'.";
    show_message(message);
    
	// create the flash command
    char function_command[4096];
    auto_free char *device_command = adb_command();
    snprintf(function_command, sizeof(function_command), "%s sideload %s", device_command, payload_info);
    LOG_INFO("Run: %s", function_command);
    command_with_spinner(function_command);
}
