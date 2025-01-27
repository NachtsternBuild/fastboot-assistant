/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - rename_recovery		 *
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

// rename a file to recovery.img
void rename_recovery(const gchar *re_filename) 
{
    char rename_recovery_path[4096];
    get_config_file_path(rename_recovery_path, sizeof(rename_recovery_path));
    // load the path
    const char *target_directory_recovery = load_path_from_file(rename_recovery_path);

    if (target_directory_recovery) 
    {
        LOG_INFO("Loaded path: %s", target_directory_recovery);
    }
    
    const gchar *recovery_filename = "recovery.img"; 
    gchar *target_path_recovery = g_strconcat(target_directory_recovery, recovery_filename, NULL);
    
    if (rename(re_filename, target_path_recovery) == 0) 
    {
        LOG_INFO("File renamed successfully: %s → %s", re_filename, recovery_filename);
    } 
    
    else 
    {
        LOG_ERROR("Error renaming the file: %s", re_filename);
    }
    
    if (target_directory_recovery != NULL) 
	{
    	g_free((gpointer)target_directory_recovery); // free the info (because g_file_get_contents was used)
	}
    g_free(target_path_recovery);
}


