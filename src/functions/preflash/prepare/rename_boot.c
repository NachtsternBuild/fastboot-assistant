/**
* rename_boot.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

void rename_boot(const gchar *bo_filename) 
{
    char rename_boot_path[4096];
    get_config_file_path(rename_boot_path, sizeof(rename_boot_path));
    // load the path
    const char *target_directory_boot = load_path_from_file(rename_boot_path);

    if (target_directory_boot) 
    {
        LOGD("Loaded path: %s", target_directory_boot);
    }
    
    const gchar *boot_filename = "boot.img"; 
    gchar *target_path_boot = g_build_filename(target_directory_boot, boot_filename, NULL);
    
    if (rename(bo_filename, target_path_boot) == 0) 
    {
        LOGD("File renamed successfully: %s → %s", bo_filename, target_path_boot);
    } 
    
    else 
    {
        LOGE("Error renaming the file: %s", bo_filename);
    }
    
    if (target_directory_boot != NULL) 
    {
        g_free((gpointer)target_directory_boot); // free the info (because g_file_get_contents was used)
    }
    g_free(target_path_boot);
}

