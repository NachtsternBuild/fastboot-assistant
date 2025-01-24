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
 *        headerpart - program_dir			 *
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
    GFile *file = gtk_file_chooser_get_file(chooser);
    if (!file) 
    {
        LOG_ERROR("No folder selected.");
        return;
    }

    char *folder_path = g_file_get_path(file);
    g_object_unref(file); // GFile freigeben

    if (!folder_path) 
    {
        LOG_ERROR("Failed to get folder path.");
        return;
    }

    // expand path
    char full_path[2048];
    snprintf(full_path, sizeof(full_path), "%s/ROM-Install", folder_path);

    // create path
    create_directory(full_path);

    // get config file path
    char config_dir[2048];
    get_config_dir(config_dir, sizeof(config_dir));
    // mkdir
    create_directory(config_dir);

    char config_file[2048];
    snprintf(config_file, sizeof(config_file), "%s/path_config.txt", config_dir);

    // save the path
    save_path_to_file(full_path, config_file);

    g_free(folder_path);
}

// Callback zum Öffnen des Dialogs
void on_open_folder_dialog(GtkWidget *button, gpointer user_data) 
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Select Folder",
        NULL, // Kein Parent
        GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Select", GTK_RESPONSE_ACCEPT,
        NULL);

    g_signal_connect(dialog, "response", G_CALLBACK(on_folder_selected), NULL);

    gtk_widget_show(dialog); // Statt veralteter Methoden
}

// Hauptfunktion ersetzt durch program_dir
void program_dir(int argc, char *argv[]) 
{
    gtk_init();

    // get language and theme
    apply_theme();
    apply_language();

    char config_file[2048];
    get_config_file_path(config_file, sizeof(config_file));

    // load the path
    char *loaded_path = load_path_from_file(config_file);

    if (loaded_path) 
    {
        g_print("Loaded path: %s\n", loaded_path);
        g_free(loaded_path); // Typ-Korrektur
    }

    GtkWidget *button = gtk_button_new_with_label("Select Folder");
    g_signal_connect(button, "clicked", G_CALLBACK(on_open_folder_dialog), NULL);

    gtk_widget_set_visible(button, TRUE); // Statt gtk_widget_show
    // run GTK main loop
    g_main_loop_run(main_loop); 
    
    // free the provider
    if (provider != NULL) 
    {
    	g_object_unref(provider);
    	provider = NULL;
	}

	if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
}

