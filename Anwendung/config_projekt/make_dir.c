/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das Installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              make_dir					 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that are used in the main program */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "program_functions.h"

// Function to construct a directory path and create the directory
void create_directory(const char *base_dir, const char *sub_dir) 
{
    char path[2048];
    snprintf(path, sizeof(path), "%s/%s", base_dir, sub_dir);
    
    char command[2048];
    snprintf(command, sizeof(command), "mkdir -p %s", path);
    
    if (system(command) == -1) 
    {
        g_print("Fehler beim Erstellen des Verzeichnisses: %s\n", path);
    } 
    
    else 
    {
        g_print("Verzeichnis erstellt: %s\n", path);
    }
}

// make dir function
void make_dir() 
{
    const char *home_dir = getenv("HOME");
    if (home_dir == NULL) 
    {
        g_print("Fehler: Konnte das Home-Verzeichnis nicht ermitteln.\n");
        return;
    }

    // standard linux paths
    create_directory(home_dir, "Downloads/ROM-Install");
    create_directory(home_dir, "Downloads/ROM-Install/Backup");
    create_directory(home_dir, "Downloads/ROM-Install/Images");
    create_directory(home_dir, "Downloads/ROM-Install/config");
	
	/*
    // the wsl logic
    const char *user = getenv("USER");
    if (user == NULL) 
    {
        g_print("Fehler: Konnte den Benutzernamen nicht ermitteln.\n");
        return;
    }

    char wsl_base_dir[512];
    snprintf(wsl_base_dir, sizeof(wsl_base_dir), "/mnt/c/Users/%s/Downloads/ROM-Install", user);

    create_directory(wsl_base_dir, "");
    create_directory(wsl_base_dir, "Backup");
    create_directory(wsl_base_dir, "Images");
    create_directory(wsl_base_dir, "config");
	*/
	
    g_print("Alle Verzeichnisse erfolgreich erstellt.\n");
}

