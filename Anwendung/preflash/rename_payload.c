/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - rename_payload			 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "function_header.h"
#include "file_chooser_header.h"
#include "flash_function_header.h"

// rename a file to payload.zip
void rename_payload(const gchar *py_filename) 
{
    char rename_payload_path[4096];
    get_config_file_path(rename_payload_path, sizeof(rename_payload_path));
    // load the path
    const char *target_directory_payload = load_path_from_file(rename_payload_path);

    if (target_directory_payload) 
    {
        LOG_INFO("Loaded path: %s", target_directory_payload);
    }
    
    const gchar *payload_filename = "payload.zip"; 
    gchar *target_path_payload = g_strconcat(target_directory_payload, payload_filename, NULL);
    
    if (rename(py_filename, target_path_payload) == 0) 
    {
        LOG_INFO("File renamed successfully: %s → %s", py_filename, payload_filename);
    } 
    
    else 
    {
        LOG_ERROR("Error renaming the file: %s", py_filename);
    }
    
    if (target_directory_payload != NULL) 
	{
    	g_free((gpointer)target_directory_payload); // free the info (because g_file_get_contents was used)
	}
    g_free(target_path_payload);
}
