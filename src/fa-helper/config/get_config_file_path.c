/**
* get_config_file_path.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
* function, that get the path of the config file
*
* get_config_file_path(config_file, sizeof(config_file));
* printf("Config file path: %s\n", config_file);
*/

#include "fastboot_assistant.h"

void get_config_file_path(char *config_file, size_t size) 
{
    // for wsl
    if (directory_exists("/mnt/c/Users")) 
    {
        const char* user = getenv("USER");
        if (user && config_file && size > 0) 
        {
            snprintf(config_file, size, "/mnt/c/Users/%s/.config/fastboot-assistant/path_config.txt", user);
            return;
        } 
        
        else if (!user) 
        {
            LOGE("Could not determine the user name.");
        } 
        
        else 
        {
            LOGE("Invalid arguments provided to get_config_file_path.");
        }
        return;
    }
    
    // standard linux
    const char *home_dir = getenv("HOME");
    if (home_dir && config_file && size > 0) 
    {
        snprintf(config_file, size, "%s/.config/fastboot-assistant/path_config.txt", home_dir);
    } 
    
    else if (!home_dir) 
    {
        LOGE("HOME environment variable is not set.");
    } 
    
    else 
    {
        LOGE("Invalid arguments provided to get_config_file_path.");
    }
}
