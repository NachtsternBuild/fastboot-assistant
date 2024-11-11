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
            perror("Log: Error when creating the directory.\n");
            exit(EXIT_FAILURE);
        }
    }
}

// function that write the dark.txt
// thanks to my book for programming for linux
void write_dark_file() 
{
    // use the full path
    char *home = getenv("HOME");
    if (home == NULL) 
    {
        perror("Log: Error when retrieving the home directory\n");
        exit(EXIT_FAILURE);
    }
    
    // WSL Logik
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
    
    // create the dir 
    create_directory_if_not_exists(dir_path);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, CONFIG_FILE);

    FILE *file = fopen(path, "w");
    if (file == NULL) 
    {
        perror("Log: Error when opening the file for writing.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "dunkel");
    fclose(file);
    g_print("Log: Written to the file '%s'.\n", path);
}

// thanks to my book for programming for linux
// function that delete the dark.txt
void delete_dark_file() 
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
    snprintf(path, sizeof(path), "%s/%s", dir_path, CONFIG_FILE);

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

// function that check if there are the dark.txt
void check_dark_file() 
{
    // use the full path
    char *home = getenv("HOME");
    if (home == NULL) 
    {
        perror("Log: Error when retrieving the home directory.\n");
        exit(EXIT_FAILURE);
    }

    char dir_path[512];
    //char wsl_dir[512];
    // for windows
	//snprintf(wsl_dir, sizeof(wsl_dir), "/mnt/c/Users/%s", user);
	//snprintf(dir_path, sizeof(dir_path), "%s/Downloads/ROM-Install/config", wsl_dir);
    snprintf(dir_path, sizeof(dir_path), "%s/Downloads/ROM-Install/config", home);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, CONFIG_FILE);

    FILE *file = fopen(path, "r");
    if (file != NULL) 
    {
        g_print("Log: Dunkelheit\n");
        current_theme = "dark";
        fclose(file);
    }
     
    else 
    {
        g_print("Log: Tag\n");
    }
}

void check_dark_file_light() 
{
    // use the full path
    char *home = getenv("HOME");
    if (home == NULL) 
    {
        perror("Log: Error when retrieving the home directory.\n");
        exit(EXIT_FAILURE);
    }

    char dir_path[512];
    //char wsl_dir[512];
    // for windows
	//snprintf(wsl_dir, sizeof(wsl_dir), "/mnt/c/Users/%s", user);
	//snprintf(dir_path, sizeof(dir_path), "%s/Downloads/ROM-Install/config", wsl_dir);
    snprintf(dir_path, sizeof(dir_path), "%s/Downloads/ROM-Install/config", home);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, CONFIG_FILE);

    FILE *file = fopen(path, "r");
    if (file != NULL) 
    {
        g_print("Log: Tag\n");
        current_theme = "light";
        delete_dark_file();
        fclose(file);
    }
     
    else 
    {
        g_print("Log: Dunkelheit\n");
    }
}
