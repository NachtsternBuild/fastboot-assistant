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
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              make_dir					 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that are used in the main program */
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

// function to create dirs
// this use g_mkdir_with_parents
void create_directory(const char *path) 
{
    if (g_mkdir_with_parents(path, 0755) != 0) 
    {
        LOG_ERROR("Error when creating the directory: %s", path);
    } 
    else 
    {
        LOG_INFO("Directory created: %s", path);
    }
}

/* main function - make_dir */
void make_dir() 
{
    gtk_init();
    char rom_install_dirs_file[4096];
    char main_path[4096];
    char backup_path[4096];
    char path_images[4096];
    
    get_config_file_path(rom_install_dirs_file, sizeof(rom_install_dirs_file));
    // load the path
    const char *rom_install_dirs = load_path_from_file(rom_install_dirs_file);

    if (rom_install_dirs) 
    {
        LOG_INFO("Loaded path: %s", rom_install_dirs);
    }
	
    // create the full path 
    snprintf(main_path, sizeof(main_path), "%s", rom_install_dirs);
    snprintf(backup_path, sizeof(backup_path), "%s/Backup", rom_install_dirs);
    snprintf(path_images, sizeof(path_images), "%s/Images", rom_install_dirs);

    // create path
    create_directory(main_path);
    create_directory(backup_path);
    create_directory(path_images);
		
    LOG_INFO("all directories successfully created.");
}

