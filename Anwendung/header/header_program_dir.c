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
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *        headerpart - program_dir			 *
 *											 *
 *-------------------------------------------*
 */

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
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

// function that save the config path to a file
void save_path_to_file(const char *path, const char *file_path) 
{
    GError *error = NULL;
    if (!g_file_set_contents(file_path, path, -1, &error)) 
    {
        LOG_ERROR("Error saving the path: %s", error->message);
        g_clear_error(&error);
    } 
    else 
    {
        LOG_INFO("Save path: %s", file_path);
    }
}

// function to read the path from the config file
char *load_path_from_file(const char *file_path) 
{
    GError *error = NULL;
    char *content = NULL;

    if (!g_file_get_contents(file_path, &content, NULL, &error)) 
    {
        LOG_ERROR("Error loading the path: %s", error->message);
        g_clear_error(&error);
        return NULL;
    }

    // remove linebreak
    g_strchomp(content);
    LOG_INFO("Load path: %s", content);
    return content;
}

// callback for dialog for dirs
void on_folder_selected(GtkFileChooser *chooser, gpointer user_data) 
{
    char *folder_path = gtk_file_chooser_get_filename(chooser);
    if (!folder_path) 
    {
        LOG_ERROR("No folder selected.");
        return;
    }

    // expand path
    char full_path[2048];
    snprintf(full_path, sizeof(full_path), "%s/ROM-Install/", folder_path);

    // create path
    create_directory(full_path);

    // get config file path
    const char *home = getenv("HOME");
    const char* user = getenv("USER");
    char config_dir[2048];
    // for linux
    snprintf(config_dir, sizeof(config_dir), "%s/.config/fastboot-assistant", home);
    // for wsl
    //snprintf(config_dir, sizeof(config_dir), "/mnt/c/Users/%s/.config/fastboot-assistant", user);
    create_directory(config_dir);

    char config_file[2048];
    snprintf(config_file, sizeof(config_file), "%s/path_config.txt", config_dir);

    // save the path
    save_path_to_file(full_path, config_file);

    g_free(folder_path);
}

/* main function - program_dir */
void program_dir(int argc, char *argv[]) 
{
    gtk_init();

    // get language and theme
    apply_theme();
    apply_language();

    // create dialog for dirs
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Ordner auswählen",
        NULL,
        GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
        "_Abbrechen", GTK_RESPONSE_CANCEL,
        "_Auswählen", GTK_RESPONSE_ACCEPT,
        NULL
    );
	
	// run dialog
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) 
    {
        on_folder_selected(GTK_FILE_CHOOSER(dialog), NULL);
    }
	
	// destroy dialog
    gtk_widget_destroy(dialog);

    // get home
    const char *home_dir = getenv("HOME");
    if (!home_dir) 
    {
        LOG_ERROR("HOME environment variable not found.");
        return EXIT_FAILURE;
    }
	
	// example way to use and get the path
	// use this in a modified way in the program
    char config_file[2048];
    snprintf(config_file, sizeof(config_file), "%s/.config/fastboot-assistant/path_config.txt", home_dir);
    char *loaded_path = load_path_from_file(config_file);

    if (loaded_path) 
    {
        LOG_INFO("Loaded path: %s", loaded_path);
        g_free(loaded_path); // free the info (because g_file_get_contents was used)
    }

    return EXIT_SUCCESS;
}

