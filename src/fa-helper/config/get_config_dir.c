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
    if (config_folder && size > 0)
    {
        config_folder[0] = '\0';
    }

    // for wsl
    if (directory_exists("/mnt/c/Users")) 
    {
    	const char* user = getenv("USER");
    	if (user && config_folder && size > 0) 
    	{
            /* basic validation for USER: must not contain path separators or ".." */
            if (strchr(user, '/') || strchr(user, '\\') || strstr(user, ".."))
            {
                LOGE("Invalid USER environment value.");
                return;
            }

            char tmp[PATH_MAX];
            int written = snprintf(tmp, sizeof(tmp), "/mnt/c/Users/%s/.config/fastboot-assistant", user);
            if (written <= 0 || (size_t)written >= sizeof(tmp))
            {
                LOGE("Config path too long.");
                return;
            }

            /* ensure the resulting path is absolute and does not contain '/../' */
            if (tmp[0] != '/' || strstr(tmp, "/../") != NULL)
            {
                LOGE("Resolved config path is invalid.");
                return;
            }

        	snprintf(config_folder, size, "%s", tmp);
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
        /* HOME should normally be an absolute path */
        if (home_dir[0] != '/')
        {
            LOGE("Invalid HOME environment value.");
            return;
        }

        char tmp[PATH_MAX];
        int written = snprintf(tmp, sizeof(tmp), "%s/.config/fastboot-assistant", home_dir);
        if (written <= 0 || (size_t)written >= sizeof(tmp))
        {
            LOGE("Config path too long.");
            return;
        }

        if (tmp[0] != '/' || strstr(tmp, "/../") != NULL)
        {
            LOGE("Resolved config path is invalid.");
            return;
        }

        snprintf(config_folder, size, "%s", tmp);
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
