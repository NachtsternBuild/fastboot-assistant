/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *      Apache License, Version 2.0          *
 *-------------------------------------------*
 *                                           *
 *  Programm um das Installieren von         *
 *  Custom-ROM und GSIs auf Android-Geräte   *
 *  zu erleichtern                           *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz        *
 *-------------------------------------------*
 *                                           *
 *       Headerpart - get_bootctl		     *
 *                                           *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

// function detect the android bootctl
void get_bootctl(GtkWidget *bootctl_status_label) 
{
	apply_language();
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
