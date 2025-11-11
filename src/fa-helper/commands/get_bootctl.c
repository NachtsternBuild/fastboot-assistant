/**
* get_bootctl.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/

#include "fastboot_assistant.h"

// function detect the android bootctl
void get_bootctl(GtkWidget *bootctl_status_label) 
{
    const char *detected_bootctl;
    const char *not_detected_bootctl;
    
    if (!is_android_device_connected()) 
    {      
        const char *no_device = _("No device detected.");
        gtk_label_set_text(GTK_LABEL(bootctl_status_label), no_device);
        return;
    }
    
    detected_bootctl = _("✅ Bootctl detected.");
    not_detected_bootctl = _("❌ Bootctl not detected.");

    // check for bootctl
    auto_free char *bootctl_command = adb_command();
    char command[256];
    snprintf(command, sizeof(command), "%s shell su -c command -v bootctl", bootctl_command);
    int status = system(command);

    // set status label
    gtk_label_set_text(GTK_LABEL(bootctl_status_label), (status == 0) ? detected_bootctl : not_detected_bootctl);
}

// function detect the android bootctl as char
char *get_bootctl_char()
{
    // check for bootctl
    auto_free char *bootctl_command = adb_command();
    char command[256];
    snprintf(command, sizeof(command), "%s shell su -c command -v bootctl", bootctl_command);
    int status = system(command);
    return (status == 0) ? "bootctl" : "no_bootctl";
}
