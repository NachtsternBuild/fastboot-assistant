/**
* rename_recovery.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// rename a file to recovery.img
void rename_recovery(const gchar *re_filename) 
{
    char rename_recovery_path[4096];
    get_config_file_path(rename_recovery_path, sizeof(rename_recovery_path));
    // load the path
    const char *target_directory_recovery = load_path_from_file(rename_recovery_path);

    if (target_directory_recovery) 
    {
        LOGD("Loaded path: %s", target_directory_recovery);
    }
    
    const gchar *recovery_filename = "recovery.img"; 
    gchar *target_path_recovery = g_build_filename(target_directory_recovery, recovery_filename, NULL);
    
    if (rename(re_filename, target_path_recovery) == 0) 
    {
        LOGD("File renamed successfully: %s → %s", re_filename, recovery_filename);
    } 
    
    else 
    {
        LOGE("Error renaming the file: %s", re_filename);
    }
    
    if (target_directory_recovery != NULL) 
	{
    	g_free((gpointer)target_directory_recovery); // free the info (because g_file_get_contents was used)
	}
    g_free(target_path_recovery);
}


