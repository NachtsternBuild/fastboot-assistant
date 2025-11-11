/**
* rename_payload.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// rename a file to payload.zip
void rename_payload(const gchar *py_filename) 
{
    char rename_payload_path[4096];
    get_config_file_path(rename_payload_path, sizeof(rename_payload_path));
    // load the path
    const char *target_directory_payload = load_path_from_file(rename_payload_path);

    if (target_directory_payload) 
    {
        LOGD("Loaded path: %s", target_directory_payload);
    }
    
    const gchar *payload_filename = "payload.zip"; 
    gchar *target_path_payload = g_build_filename(target_directory_payload, payload_filename, NULL);
    
    if (rename(py_filename, target_path_payload) == 0) 
    {
        LOGD("File renamed successfully: %s → %s", py_filename, payload_filename);
    } 
    
    else 
    {
        LOGE("Error renaming the file: %s", py_filename);
    }
    
    if (target_directory_payload != NULL) 
	{
    	g_free((gpointer)target_directory_payload); // free the info (because g_file_get_contents was used)
	}
    g_free(target_path_payload);
}
