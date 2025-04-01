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
 *      Headerpart - delete_config_files	 *
 *											 *
 *-------------------------------------------*
 */

/* headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <unistd.h>  
#include <sys/stat.h> 
#include <sys/types.h> 
#include "program_functions.h"

// thanks to my book for programming for linux
// function that delete a config file from the fastboot-assistant
// all files in ~/.config/fastboot-assistant/
void delete_config_files(const char *path) 
{
    char dir_path[512];
    get_config_dir(dir_path, sizeof(dir_path));

    char new_path[512];
    snprintf(new_path, sizeof(new_path), "%s/%s", dir_path, path);

    // try to remove the file
    if (remove(new_path) == 0) 
    {
        LOG_INFO("File '%s' successfully deleted.", new_path);
    } 
    
    else 
    {
        LOG_ERROR("Error deleting the file.");
    }
}

