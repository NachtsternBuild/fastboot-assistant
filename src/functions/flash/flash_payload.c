/**
* flash_payload.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

void flash_payload(GtkWidget *widget, gpointer data)
{
    LOGD("flash_payload");
    char config_file_payload[1024];  
    char payload_info[2048];
    
    // flash payload.zip via adb sideload   
    // create the path to the payload.zip
    get_config_file_path(config_file_payload, sizeof(config_file_payload));
    // load the path
    const char *payload_path = load_path_from_file(config_file_payload);
	
	const char *payload_name = "payload.zip";
	
    if (payload_path) 
    {
        LOGD("Loaded path: %s", payload_path);
    }
    
	snprintf(payload_info, sizeof(payload_info), "%s/%s", payload_path, payload_name);
    // check if the image exists
    if (access(payload_info, F_OK) == -1) 
    {
        // no payload.zip found
        char error_message[4096];
        snprintf(error_message, sizeof(error_message), _("Image file '%s' not found.\n"), payload_info);
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
        
	// create the flash command
    char function_command[4096];
    auto_free char *device_command = adb_command();
    snprintf(function_command, sizeof(function_command), "%s sideload %s", device_command, payload_info);
    LOGD("Run: %s", function_command);
    const char *title = _("Flash");
    const char *body = _("Sideloading...");
    show_progress_dialog(widget, title, body, function_command);
}
