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
 *        		post_update					 *
 *											 *
 *-------------------------------------------*
 */

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

// function to delete directory
void delete_directory(const char *path) 
{
    char command[2048];
    snprintf(command, sizeof(command), "rm -rf %s", path);
    if (system(command) != 0) 
    {
        LOG_ERROR("Error deleting directory: %s", path);
    } 
    
    else 
    {
        LOG_INFO("Directory deleted: %s", path);
    }
}

// function that start after a update
void post_update() 
{
    char main_config_dir[4096];
    apply_theme();
    apply_language();
    
    get_config_dir(main_config_dir, sizeof(main_config_dir));
    
    char config_dir[2048];
    char updater_dir[2048];
    char version_file[2048];

    snprintf(config_dir, sizeof(config_dir), "%s/config", main_config_dir);
    snprintf(updater_dir, sizeof(updater_dir), "%s/updater", main_config_dir);
    snprintf(version_file, sizeof(version_file), "%s/version.txt", config_dir);
	
	// if updater dir not exsits
    if (!directory_exists(updater_dir)) 
    {
        LOG_INFO("Updater directory does not exist.");
        create_directory(config_dir);

        FILE *file = fopen(version_file, "w");
        if (!file) 
        {
            LOG_ERROR("Failed to create version file: %s", version_file);
            exit(1);
        }

        const char *initial_version = "v.0.8.1.5";
        fprintf(file, "%s\n", initial_version);
        fclose(file);
        LOG_INFO("Version file created with version: %s", initial_version);
    }
    
    // if updater dir exsists
    else 
    {
        LOG_INFO("Updater directory exists.");
        
		// function to open version file
        FILE *file = fopen(version_file, "r");
        if (!file) 
        {
            LOG_ERROR("Failed to open version file: %s", version_file);
            exit(1);
        }
		
		// get the current version
        char current_version[128];
        if (fgets(current_version, sizeof(current_version), file)) 
        {
            current_version[strcspn(current_version, "\n")] = '\0'; // Remove newline
            LOG_INFO("Current version: %s", current_version);
        } 
        
        else 
        {
            LOG_ERROR("Failed to read version from file.");
            fclose(file);
            exit(1);
        }
        fclose(file);
        
        /* this are the new version */
        // set a new version before build
        const char *new_version = "v.0.8.1.5"; 
        char version_message[4096];
        // user information
        snprintf(version_message, sizeof(version_message), g_strcmp0(language, "de") == 0 ? "Alte Version: %s\n\nNeue Version: %s\n\n" : "Old version: %s\n\nNew Version %s\n\n", current_version, new_version);
        
		show_message(version_message);
		
		// write a new version to version file
		FILE *new_file = fopen(version_file, "w");
		if (!new_file) 
		{
    		LOG_ERROR("Failed to write new version to file: %s", version_file);
    		exit(1);
		}

		fprintf(new_file, "%s\n", new_version);
		fclose(new_file);
		LOG_INFO("Version file updated with new version: %s", new_version);

		// remove the updater dir
		delete_directory(updater_dir);
	}
}


