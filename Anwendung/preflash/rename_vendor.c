/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - rename_vendor			 *
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

// rename a file to vendor.img
void rename_vendor(const gchar *ve_filename) 
{
    char rename_vendor_path[4096];
    get_config_file_path(rename_vendor_path, sizeof(rename_vendor_path));
    // load the path
    const char *target_directory_vendor = load_path_from_file(rename_vendor_path);

    if (target_directory_vendor) 
    {
        LOG_INFO("Loaded path: %s", target_directory_vendor);
    }
    
    const gchar *vendor_filename = "vendor.img"; 
    gchar *target_path_vendor = g_strconcat(target_directory_vendor, vendor_filename, NULL);
    
    if (rename(ve_filename, target_path_vendor) == 0) 
    {
        LOG_INFO("File renamed successfully: %s → %s", ve_filename, vendor_filename);
    } 
    
    else 
    {
        LOG_ERROR("Error renaming the file: %s", ve_filename);
    }
    
    if (target_directory_vendor != NULL) 
	{
    	g_free((gpointer)target_directory_vendor); // free the info (because g_file_get_contents was used)
	}
    g_free(target_path_vendor);
}
