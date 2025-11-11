/**
* rename_system.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// rename a file to system.img
void rename_system(const gchar *sys_filename) 
{
    char rename_system_path[4096];
    get_config_file_path(rename_system_path, sizeof(rename_system_path));
    // load the path
    const char *target_directory_system = load_path_from_file(rename_system_path);

    if (target_directory_system) 
    {
        LOGD("Loaded path: %s", target_directory_system);
    }
    
    const gchar *system_filename = "system.img"; 
    gchar *target_path_system = g_build_filename(target_directory_system, system_filename, NULL);
    
    if (rename(sys_filename, target_path_system) == 0) 
    {
        LOGD("File renamed successfully: %s → %s", sys_filename, system_filename);
    } 
    
    else 
    {
        LOGE("Error renaming the file: %s", sys_filename);
    }
    
    if (target_directory_system != NULL) 
	{
    	g_free((gpointer)target_directory_system); // free the info (because g_file_get_contents was used)
	}
    g_free(target_path_system);
}
