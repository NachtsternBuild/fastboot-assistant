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
 *              Headerpart - language_check	 *
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

#define LANGUAGE_PATH "~/Downloads/ROM-Install/config"
#define LANGUAGE_FILE "language.txt" 

const char *language = "de";

// function that create the dir
// thanks to my book for programming for linux
void create_directory_if_not_exists_lang(const char *path) 
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
            perror("Log: Error when creating the directory.\n");
            exit(EXIT_FAILURE);
        }
    }
}

// function that write the dark.txt
// thanks to my book for programming for linux
void write_language_file() 
{
    char dir_path[512];
    get_config_dir(dir_path, sizeof(dir_path));
    
    // create the dir 
    create_directory_if_not_exists_lang(dir_path);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, LANGUAGE_FILE);

    FILE *file = fopen(path, "w");
    if (file == NULL) 
    {
        perror("Log: Error when opening the file for writing.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "English");
    fclose(file);
    LOG_INFO("Written to the file '%s'.", path);
}

// thanks to my book for programming for linux
// function that delete the dark.txt
void delete_language_file() 
{
    char dir_path[512];
    get_config_dir(dir_path, sizeof(dir_path));

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, LANGUAGE_FILE);

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
void check_language_file() 
{
    char dir_path[512];
    get_config_dir(dir_path, sizeof(dir_path));

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, LANGUAGE_FILE);

    FILE *file = fopen(path, "r");
    if (file != NULL) 
    {
        LOG_INFO("English");
        language = "en";
        fclose(file);
    }
     
    else 
    {
        LOG_INFO("Deutsch");
    }
}

void check_language_file_light() 
{
    char dir_path[512];
    get_config_dir(dir_path, sizeof(dir_path));

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, LANGUAGE_FILE);

    FILE *file = fopen(path, "r");
    if (file != NULL) 
    {
        LOG_INFO("Deutsch");
        language = "de";
        delete_language_file();
        fclose(file);
    }
     
    else 
    {
        LOG_INFO("English");
    }
}

// Apply the current language when called
void apply_language() 
{
    check_language_file();  // Assuming this checks the current language state
}

// Callback to switch the language
void toggle_language(GtkWidget *button, gpointer user_data) 
{
    // Switch the theme
    if (strcmp(language, "de") == 0) 
    {
        language = "en";
        write_language_file(); 
        const char *message = "Please restart the Fastboot Assistant.";
    	show_message(message);
    } 
    
    else 
    {
        language = "de";
        check_language_file_light(); 
        const char *message = "Bitte starten sie den Fastboot-Assistant erneut.";
    	show_message(message);
    }
    apply_language();
}
