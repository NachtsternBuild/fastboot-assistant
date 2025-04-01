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
 *              Headerpart - load_theme		 *
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

#define THEME_FILE "auto.txt" 

const char *auto_theme = "css_adw";

// function that write the auto.txt
// thanks to my book for programming for linux
void write_auto_theme_file() 
{
    char dir_path[512];
    get_config_dir(dir_path, sizeof(dir_path));
    
    // create the dir 
    create_directory_if_not_exists(dir_path);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, THEME_FILE);

    FILE *file = fopen(path, "w");
    if (file == NULL) 
    {
        LOG_ERROR("Error when opening the file for writing.");
        exit(1);
    }
    fprintf(file, "libadwaita");
    fclose(file);
    LOG_INFO("Written to the file '%s'.", path);
}

// remove them
// function that check if there are the auto.txt
void check_auto_theme() 
{
    char dir_path[512];
    get_config_dir(dir_path, sizeof(dir_path));

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, THEME_FILE);

    FILE *file = fopen(path, "r");
    if (file != NULL) 
    {
        auto_theme = "css_adw";
        fclose(file);
    }
     
    else 
    {
    	auto_theme = "css_only";
    }
}
