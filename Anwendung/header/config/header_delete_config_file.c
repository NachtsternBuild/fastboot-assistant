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
 *      Headerpart - delete_config_file		 *
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

#define CONFIG_SETUP_FILE "config.txt" 

// thanks to my book for programming for linux
// function that delete the dark.txt
void delete_config_file() 
{
    char dir_path[512];
    get_config_dir(dir_path, sizeof(dir_path));

    char path[512];
    snprintf(path, sizeof(path), "%s/config/%s", dir_path, CONFIG_SETUP_FILE);

    // try to remove the file
    if (remove(path) == 0) 
    {
        LOG_INFO("File '%s' successfully deleted.", path);
    } 
    
    else 
    {
        LOG_ERROR("Error deleting the file.");
    }
}

