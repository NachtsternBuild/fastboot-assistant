/**
* rename_vendor.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// rename a file to vendor.img
void rename_vendor(const gchar *ve_filename) 
{
    char rename_vendor_path[4096];
    get_config_file_path(rename_vendor_path, sizeof(rename_vendor_path));
    // load the path
    const char *target_directory_vendor = load_path_from_file(rename_vendor_path);

    if (target_directory_vendor) 
    {
        LOGD("Loaded path: %s", target_directory_vendor);
    }
    
    const gchar *vendor_filename = "vendor.img"; 
    gchar *target_path_vendor = g_build_filename(target_directory_vendor, vendor_filename, NULL);
    
    if (rename(ve_filename, target_path_vendor) == 0) 
    {
        LOGD("File renamed successfully: %s → %s", ve_filename, vendor_filename);
    } 
    
    else 
    {
        LOGE("Error renaming the file: %s", ve_filename);
    }
    
    if (target_directory_vendor != NULL) 
	{
    	g_free((gpointer)target_directory_vendor); // free the info (because g_file_get_contents was used)
	}
    g_free(target_path_vendor);
}
