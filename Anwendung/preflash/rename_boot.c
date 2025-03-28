/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - rename_boot			 *
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

void rename_boot(const gchar *bo_filename) 
{
    char rename_boot_path[4096];
    get_config_file_path(rename_boot_path, sizeof(rename_boot_path));
    // load the path
    const char *target_directory_boot = load_path_from_file(rename_boot_path);

    if (target_directory_boot) 
    {
        LOG_INFO("Loaded path: %s", target_directory_boot);
    }
    
    const gchar *boot_filename = "boot.img"; 
    gchar *target_path_boot = g_build_filename(target_directory_boot, boot_filename, NULL);
    
    if (rename(bo_filename, target_path_boot) == 0) 
    {
        LOG_INFO("File renamed successfully: %s → %s", bo_filename, target_path_boot);
    } 
    
    else 
    {
        LOG_ERROR("Error renaming the file: %s", bo_filename);
    }
    
    if (target_directory_boot != NULL) 
    {
        g_free((gpointer)target_directory_boot); // free the info (because g_file_get_contents was used)
    }
    g_free(target_path_boot);
}

