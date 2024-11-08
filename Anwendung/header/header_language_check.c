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
            perror("Fehler beim Erstellen des Verzeichnisses");
            exit(EXIT_FAILURE);
        }
    }
}

// function that write the dark.txt
// thanks to my book for programming for linux
void write_language_file() 
{
    // use the full path
    char *home = getenv("HOME");
    if (home == NULL) 
    {
        perror("Fehler beim Abrufen des Home-Verzeichnisses");
        exit(EXIT_FAILURE);
    }
    
    // WSL Logik
	const char *user = getenv("USER");
	if (user == NULL) 
	{	
    	g_print("Fehler: Konnte den Benutzernamen nicht ermitteln.\n");
    	exit(1);  // close the program if there are errors
	}


    char dir_path[512];
    //char wsl_dir[512];
    // for windows
	//snprintf(wsl_dir, sizeof(wsl_dir), "/mnt/c/Users/%s", user);
	//snprintf(dir_path, sizeof(dir_path), "%s/Downloads/ROM-Install/config", wsl_dir);
    snprintf(dir_path, sizeof(dir_path), "%s/Downloads/ROM-Install/config", home);
    
    // create the dir 
    create_directory_if_not_exists_lang(dir_path);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, CONFIG_FILE);

    FILE *file = fopen(path, "w");
    if (file == NULL) 
    {
        perror("Fehler beim Öffnen der Datei zum Schreiben");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "English");
    fclose(file);
    g_print("Log: In die Datei '%s' geschrieben.\n", path);
}

// thanks to my book for programming for linux
// function that delete the dark.txt
void delete_language_file() 
{
    // use the full path
    char *home = getenv("HOME");
    if (home == NULL) 
    {
        perror("Fehler beim Abrufen des Home-Verzeichnisses");
        exit(EXIT_FAILURE);
    }
    
    // WSL logic
	const char *user = getenv("USER");
	if (user == NULL) 
	{	
    	g_print("Fehler: Konnte den Benutzernamen nicht ermitteln.\n");
    	exit(1);  // close the program if there are errors
	}

    char dir_path[512];
    //char wsl_dir[512];
    // for windows
	//snprintf(wsl_dir, sizeof(wsl_dir), "/mnt/c/Users/%s", user);
	//snprintf(dir_path, sizeof(dir_path), "%s/Downloads/ROM-Install/config", wsl_dir);
    snprintf(dir_path, sizeof(dir_path), "%s/Downloads/ROM-Install/config", home);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, LANGUAGE_FILE);

    // try to remove the file
    if (remove(path) == 0) 
    {
        g_print("Log: Datei '%s' erfolgreich gelöscht.\n", path);
    } 
    else 
    {
        perror("Fehler beim Löschen der Datei");
    }
}

// function that check if there are the dark.txt
void check_language_file() 
{
    // use the full path
    char *home = getenv("HOME");
    if (home == NULL) 
    {
        perror("Fehler beim Abrufen des Home-Verzeichnisses");
        exit(EXIT_FAILURE);
    }

    char dir_path[512];
    //char wsl_dir[512];
    // for windows
	//snprintf(wsl_dir, sizeof(wsl_dir), "/mnt/c/Users/%s", user);
	//snprintf(dir_path, sizeof(dir_path), "%s/Downloads/ROM-Install/config", wsl_dir);
    snprintf(dir_path, sizeof(dir_path), "%s/Downloads/ROM-Install/config", home);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, LANGUAGE_FILE);

    FILE *file = fopen(path, "r");
    if (file != NULL) 
    {
        g_print("Log: English\n");
        language = "en";
        fclose(file);
    }
     
    else 
    {
        g_print("Log: Deutsch\n");
    }
}

void check_language_file_light() 
{
    // use the full path
    char *home = getenv("HOME");
    if (home == NULL) 
    {
        perror("Fehler beim Abrufen des Home-Verzeichnisses");
        exit(EXIT_FAILURE);
    }

    char dir_path[512];
    //char wsl_dir[512];
    // for windows
	//snprintf(wsl_dir, sizeof(wsl_dir), "/mnt/c/Users/%s", user);
	//snprintf(dir_path, sizeof(dir_path), "%s/Downloads/ROM-Install/config", wsl_dir);
    snprintf(dir_path, sizeof(dir_path), "%s/Downloads/ROM-Install/config", home);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, LANGUAGE_FILE);

    FILE *file = fopen(path, "r");
    if (file != NULL) 
    {
        g_print("Log: Deutsch\n");
        language = "de";
        delete_language_file();
        fclose(file);
    }
     
    else 
    {
        g_print("Log: English\n");
    }
}

// Callback to switch the language
void toggle_language(GtkWidget *button, gpointer user_data) 
{
    // Switch the theme
    if (strcmp(language, "de") == 0) 
    {
        language = "en";
        write_language_file(); // Assuming this saves the theme state
    } 
    else 
    {
        language = "de";
        check_language_file_light(); // Assuming this resets the theme state
    }
}

// Apply the current language when called
void apply_language() 
{
    check_language_file();  // Assuming this checks the current language state
}
