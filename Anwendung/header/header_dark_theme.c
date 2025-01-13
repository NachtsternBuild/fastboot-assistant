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
 *              Headerpart - dark_theme		 *
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

#define CONFIG_DIR "~/Downloads/ROM-Install/config"
#define CONFIG_FILE "dark.txt" 

const char *current_theme = "light";

// function that create the dir
// thanks to my book for programming for linux
void create_directory_if_not_exists(const char *path) 
{
    char expanded_path[512];
    snprintf(expanded_path, sizeof(expanded_path), "%s", path);
    char *home = getenv("HOME");
    if (home != NULL) 
    {
        // use the full path
        char *tilde_pos = strchr(expanded_path, '~');
        if (tilde_pos != NULL) 
        {
            memmove(expanded_path + strlen(home), tilde_pos + 1, strlen(tilde_pos));
            memcpy(expanded_path, home, strlen(home));
        }
    }

    struct stat st = {0};
    if (stat(expanded_path, &st) == -1) 
    {
        if (mkdir(expanded_path, 0700) == -1) 
        {
            LOG_ERROR("Error when creating the directory.");
            exit(1);
        }
    }
}

// function that write the dark.txt
// thanks to my book for programming for linux
void write_dark_file() 
{
    char dir_path[512];
    get_config_dir(dir_path, sizeof(dir_path));
    
    // create the dir 
    create_directory_if_not_exists(dir_path);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, CONFIG_FILE);

    FILE *file = fopen(path, "w");
    if (file == NULL) 
    {
        LOG_ERROR("Error when opening the file for writing.");
        exit(1);
    }
    fprintf(file, "dunkel");
    fclose(file);
    LOG_INFO("Written to the file '%s'.", path);
}

// thanks to my book for programming for linux
// function that delete the dark.txt
void delete_dark_file() 
{
    char dir_path[512];
    get_config_dir(dir_path, sizeof(dir_path));

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, CONFIG_FILE);

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

// function that check if there are the dark.txt
void check_dark_file() 
{
    char dir_path[512];
    get_config_dir(dir_path, sizeof(dir_path));

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, CONFIG_FILE);

    FILE *file = fopen(path, "r");
    if (file != NULL) 
    {
        LOG_INFO("Dunkelheit");
        current_theme = "dark";
        fclose(file);
    }
     
    else 
    {
        LOG_INFO("Tag");
    }
}

void check_dark_file_light() 
{
    char dir_path[512];
    get_config_dir(dir_path, sizeof(dir_path));

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, CONFIG_FILE);

    FILE *file = fopen(path, "r");
    if (file != NULL) 
    {
        LOG_INFO("Tag");
        current_theme = "light";
        delete_dark_file();
        fclose(file);
    }
     
    else 
    {
        LOG_INFO("Dunkelheit");
    }
}
