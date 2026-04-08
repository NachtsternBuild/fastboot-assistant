/**
* get_config_dir.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"
#include <ctype.h>

/** function that get the config dir
*
* Usage:
* get_config_dir(config_folder, sizeof(config_folder));
* g_print("Config folder path: %s\n", config_folder);
*/

// Allow only a conservative set of characters in the USER name to avoid
// directory traversal or injection of path separators.
static int is_safe_username(const char *user)
{
    if (user == NULL || *user == '\0')
    {
        return 0;
    }

    for (const char *p = user; *p != '\0'; ++p)
    {
        if (!(isalnum((unsigned char)*p) || *p == '_' || *p == '-' || *p == '.'))
        {
            return 0;
        }
    }

    return 1;
}

void get_config_dir(char *config_folder, size_t size) 
{
    // for wsl
    if (directory_exists("/mnt/c/Users")) 
    {
    	const char* user = getenv("USER");
    	if (user && is_safe_username(user) && config_folder && size > 0) 
    	{
        	snprintf(config_folder, size, "/mnt/c/Users/%s/.config/fastboot-assistant", user);
    	} 
    
    	else if (!user) 
    	{
        	LOGE("Could not determine the user name.");
    	} 
    	else if (!is_safe_username(user))
    	{
        	LOGE("Unsafe USER environment variable value.");
    	}
    	else 
    	{
        	LOGE("Invalid arguments provided to get_config_file_path.");
    	}
    	return;
    }
    
    // standard linux
    const char *home_dir = getenv("HOME"); 
    if (home_dir && home_dir[0] == '/' && config_folder && size > 0) 
    {
        snprintf(config_folder, size, "%s/.config/fastboot-assistant", home_dir);
    } 
    
    else if (!home_dir) 
    {
        LOGE("HOME environment variable is not set.");
    } 
    else if (home_dir[0] != '/')
    {
        LOGE("HOME environment variable has an unsafe value.");
    }
    else 
    {
        LOGE("Invalid arguments provided to get_config_file_path.");
    }
}
