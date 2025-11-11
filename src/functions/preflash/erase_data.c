/**
* erase_data.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

char erase_data_command[2048];

// Function to erase user data
void erase_data(GtkWidget *widget, gpointer stack) 
{
    LOGD("erase_data");
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(widget, error_message);
        return;
    }
        
    // Erase user data and metadata
    auto_free char *device_command = fastboot_command();
    snprintf(erase_data_command, sizeof(erase_data_command), "%s erase userdata", device_command);

    LOGD("Run: %s", erase_data_command);
    show_spinner_dialog(GTK_WIDGET(widget), _("Erasing Userdata"), _("Please wait..."), erase_data_command);
    LOGD("end erase_data");
}

