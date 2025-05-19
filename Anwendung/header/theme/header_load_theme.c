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
#define ADW_FILE "adw_css.txt"


const char *auto_theme = "auto";
const char *adw_css_theme = "adw";

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

// function that write the adw_css.txt
// thanks to my book for programming for linux
void write_adw_css_theme_file() 
{
    char dir_path[512];
    get_config_dir(dir_path, sizeof(dir_path));
    
    // create the dir 
    create_directory_if_not_exists(dir_path);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, ADW_FILE);

    FILE *file = fopen(path, "w");
    if (file == NULL) 
    {
        LOG_ERROR("Error when opening the file for writing.");
        exit(1);
    }
    fprintf(file, "css_libadwaita");
    fclose(file);
    LOG_INFO("Written to the file '%s'.", path);
}

// function that check if there are the auto.txt
void check_auto_theme() 
{
    LOG_INFO("Check for auto theme file.");
    char dir_path[512];
    get_config_dir(dir_path, sizeof(dir_path));

    char path[512];
    char path_adw_file[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, THEME_FILE);
	snprintf(path_adw_file, sizeof(path_adw_file), "%s/%s", dir_path, ADW_FILE);

	// open the theme file
    FILE *file = fopen(path, "r");
    if (file != NULL) 
    {
        // close the file
        fclose(file);
        // mode: adw / adw_css
        auto_theme = "auto";
    }
    
    else 
    {
    	// mode: css only
    	auto_theme = "css_only";
    }
}

// function that check if there are the adw_css.txt
void check_adw_css_theme() 
{
    LOG_INFO("Check for adw_css file");
    char dir_path[512];
    get_config_dir(dir_path, sizeof(dir_path));

    char path_adw_file[512];
	snprintf(path_adw_file, sizeof(path_adw_file), "%s/%s", dir_path, ADW_FILE);

    // open the adw_css file
    FILE *file = fopen(path_adw_file, "r");
    if (file != NULL)
    {
      	// mode: css and adw
       	adw_css_theme = "css_adw";
       	fclose(file);
    }
        
    else
    {
     	// mode: adw only
      	adw_css_theme = "adw";
    }
}
