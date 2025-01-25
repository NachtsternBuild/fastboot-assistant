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

// callback for dialog for the dialog and get the setup path
static void on_folder_selected(GtkFileDialog *dialog, GAsyncResult *res, gpointer user_data) 
{
    g_autoptr(GFile) folder = gtk_file_dialog_select_folder_finish(dialog, res, NULL);
    if (!folder) 
    {
        LOG_ERROR("No folder selected.");
        return;
    }

    g_autofree char *folder_path = g_file_get_path(folder);
    if (!folder_path) 
    {
        LOG_ERROR("Failed to get folder path.");
        return;
    }

    // expand path
    char full_path[2048];
    snprintf(full_path, sizeof(full_path), "%s/ROM-Install", folder_path);

    // create directory for ROM-Install
    create_directory(full_path);

    // get config file path
    char config_dir[2048];
    get_config_dir(config_dir, sizeof(config_dir));

    // create config directory
    create_directory(config_dir);

    char config_file[2048];
    snprintf(config_file, sizeof(config_file), "%s/path_config.txt", config_dir);

    // save the path
    save_path_to_file(full_path, config_file);

    LOG_INFO("Folder setup completed successfully: %s", full_path);
}


// function to show file chooser
void show_folder_chooser(GtkWidget *widget, gpointer data) 
{
    GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_root(widget));
    if (!GTK_IS_WINDOW(parent_window)) 
    {
        parent_window = NULL;
    }

    apply_language();

    // create folder chooser dialog
    GtkFileDialog *dialog = gtk_file_dialog_new();

    // show dialog for folder selection and connect callback
    gtk_file_dialog_select_folder(dialog, parent_window, NULL, (GAsyncReadyCallback)on_folder_selected, data);
}


