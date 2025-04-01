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
 *      Headerpart - get_config_file_path	 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// function, that get the path of the config file
// this replace set_main_dir_with_wsl
/*
* get_config_file_path(config_file, sizeof(config_file));
* printf("Config file path: %s\n", config_file);
*/
// for linux
void get_config_file_path(char *config_file, size_t size) 
{
    const char *home_dir = getenv("HOME");
    if (home_dir && config_file && size > 0) 
    {
        snprintf(config_file, size, "%s/.config/fastboot-assistant/path_config.txt", home_dir);
    } 
    
    else if (!home_dir) 
    {
        LOG_ERROR("HOME environment variable is not set.");
    } 
    
    else 
    {
        LOG_ERROR("Invalid arguments provided to get_config_file_path.");
    }
}

// for wsl
/*
void get_config_file_path(char *config_file, size_t size) 
{
    const char* user = getenv("USER");
    if (user && config_file && size > 0) 
    {
        snprintf(config_file, size, "/mnt/c/Users/%s/.config/fastboot-assistant/path_config.txt", user);
    } 
    
    else if (!user) 
    {
        LOG_ERROR("Could not determine the user name.");
    } 
    
    else 
    {
        LOG_ERROR("Invalid arguments provided to get_config_file_path.");
    }
}
*/
