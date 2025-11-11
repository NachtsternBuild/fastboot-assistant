/**
* get_config_dir.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

/** function that get the config dir
*
* Usage:
* get_config_dir(config_folder, sizeof(config_folder));
* g_print("Config folder path: %s\n", config_folder);
*/
void get_config_dir(char *config_folder, size_t size) 
{
    // for wsl
    if (directory_exists("/mnt/c/Users")) 
    {
    	const char* user = getenv("USER");
    	if (user && config_folder && size > 0) 
    	{
        	snprintf(config_folder, size, "/mnt/c/Users/%s/.config/fastboot-assistant", user);
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
    if (home_dir && config_folder && size > 0) 
    {
        snprintf(config_folder, size, "%s/.config/fastboot-assistant", home_dir);
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
