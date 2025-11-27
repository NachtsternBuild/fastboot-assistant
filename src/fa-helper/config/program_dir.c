/**
* get_config_file_path.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// function that save the config path to a file
void save_path_to_file(const char *path, const char *file_path) 
{
    GError *error = NULL;
    if (!g_file_set_contents(file_path, path, -1, &error)) 
    {
        LOGE("Error saving the path: %s", error->message);
        g_clear_error(&error);
    } 
    else 
    {
        LOGI("Save path: %s", file_path);
    }
}

// function to read the path from the config file
char *load_path_from_file(const char *file_path) 
{
    GError *error = NULL;
    char *content = NULL;

    if (!g_file_get_contents(file_path, &content, NULL, &error)) 
    {
        LOGE("Error loading the path: %s", error->message);
        g_clear_error(&error);
        return NULL;
    }

    // remove linebreak
    g_strchomp(content);
    LOGI("Load path: %s", content);
    return content;
}

// callback for dialog for the dialog and get the setup path
void process_selected_setup_folder(const char *folder_path)
{
    if (!folder_path)
    {
        LOGE("No folder path provided to processor.");
        return;
    }

    // expand path
    char full_path[2048];
    // use the transmitted path
    snprintf(full_path, sizeof(full_path), "%s/ROM-Install", folder_path);

    // create directory for ROM-Install
    create_directory(full_path);

    // get config file path
    char config_dir[512];
    get_config_dir(config_dir, sizeof(config_dir));

    // create config directory
    create_directory(config_dir);

    char config_file[1048];
    snprintf(config_file, sizeof(config_file), "%s/path_config.txt", config_dir);

    // save the path
    save_path_to_file(full_path, config_file);

    LOGI("Folder setup completed successfully: %s", full_path);
}
