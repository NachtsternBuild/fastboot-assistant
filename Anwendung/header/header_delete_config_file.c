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
    // use the full path
    char *home = getenv("HOME");
    if (home == NULL) 
    {
        perror("Log: Error when retrieving the home directory.\n");
        exit(EXIT_FAILURE);
    }
    
    // WSL logic
	const char *user = getenv("USER");
	if (user == NULL) 
	{	
    	g_print("Log: Error: Could not determine the user name.\n");
    	exit(1);  // close the program if there are errors
	}

    char dir_path[512];
    //char wsl_dir[512];
    // for windows
	//snprintf(wsl_dir, sizeof(wsl_dir), "/mnt/c/Users/%s", user);
	//snprintf(dir_path, sizeof(dir_path), "%s/Downloads/ROM-Install/config", wsl_dir);
    snprintf(dir_path, sizeof(dir_path), "%s/Downloads/ROM-Install/config", home);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, CONFIG_SETUP_FILE);

    // try to remove the file
    if (remove(path) == 0) 
    {
        g_print("Log: File '%s' successfully deleted.\n", path);
    } 
    else 
    {
        perror("Log: Error deleting the file.\n");
    }
}

