/**
* check_root_access.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/

#include "fastboot_assistant.h"

// header that check for root access
void check_root_access(GtkWidget *root_status_label) 
{
    const char *root_access;
    const char *no_root_access;
    
    if (!is_android_device_connected()) 
    {      
        const char *no_device = _("No device detected.");
        gtk_label_set_text(GTK_LABEL(root_status_label), no_device);
        return;
    }

    root_access = _("✅ Root permissions available.");
    no_root_access = _("❌ No root permissions available.");

    // check for root
    auto_free char *root_command = adb_command();
    char command[256];
    snprintf(command, sizeof(command), "%s shell su -c id -u", root_command);
    int status = system(command);

    // set status label
    gtk_label_set_text(GTK_LABEL(root_status_label), (status == 0) ? root_access : no_root_access);
}

// header that check for root access as char
char *check_root_access_char()
{
    auto_free char *root_command = adb_command();
    char command[256];
    snprintf(command, sizeof(command), "%s shell su -c id -u", root_command);
    int status = system(command);
    return (status == 0) ? "root" : "no_root";
}
