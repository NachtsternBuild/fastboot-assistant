/**
* post_update.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

#define OLD_CONFIG_NAME "local.conf" 
#define NEW_CONFIG_NAME "update.conf" 
#define FINAL_CONFIG_NAME "local.conf" 

// function that start after a update
int post_update_helper() 
{
    char main_config_dir[4096];
    
    get_config_dir(main_config_dir, sizeof(main_config_dir));
    
    char old_path[256];
    char new_path[256];
    char final_path[256];
    char conf_dir[128];
    get_config_dir(conf_dir, sizeof(conf_dir));
    
    snprintf(old_path, sizeof(old_path), "%s/%s", conf_dir, OLD_CONFIG_NAME);
    snprintf(new_path, sizeof(new_path), "%s/%s", conf_dir, NEW_CONFIG_NAME);
    snprintf(final_path, sizeof(final_path), "%s/%s", conf_dir, FINAL_CONFIG_NAME);

    LOGD("Checking files:");
    LOGD("- Old: %s", old_path);
    LOGD("- New: %s", new_path);
    
	// check if files exsists
    if (access(old_path, F_OK) != 0) 
    {
        LOGW("Old configuration file (‘%s’) not found.", OLD_CONFIG_NAME);
        return 1; // 1: old files missing
    }
   
    if (access(new_path, F_OK) != 0) 
    {
        LOGW("New configuration file (‘%s’) not found.", NEW_CONFIG_NAME);
        return 2; // 2: new files missing
    }
    
    // remove old file
    if (remove(old_path) == 0) 
    {
        LOGD("%s successfully deleted", OLD_CONFIG_NAME);
    } 
    
    else 
    {
        LOGE("ERROR when deleting the old file");
        perror("ERROR when deleting the old file");
        return 3; // 3: error remove old config file
    }

    // rename new file
    if (rename(new_path, final_path) == 0) 
    {
        LOGD("%s successfully renamed", NEW_CONFIG_NAME);
    } 
    
    else 
    {
        LOGE("ERROR renaming the new file");
        perror("ERROR renaming the new file");
        return 4; // 4: error with renaming
    }
    return 0; // 0: success
}

// check for old update files
void post_update() 
{
	int result = post_update_helper();
	// sucess of post update
    if (result == 0) 
    {
        LOGI("");
    }
    // no update
    else if (result == 1 || result == 2)
    {
    	LOGI("");
    }
    // error with running post update
    else
    {    
        LOGE("Error code: %d. The operation was not completed.", result);
        fprintf(stderr, "Error code: %d. The operation was not completed.\n", result);
    }
}


