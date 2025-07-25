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
 *       Headerpart - check_root_access	     *
 *                                           *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

// header that check for root access
void check_root_access(GtkWidget *root_status_label) 
{
	apply_language();
    const char *root_access;
    const char *no_root_access;
    
    if (!is_android_device_connected()) 
    {      
        const char *no_device = strcmp(language, "de") == 0 ? "Kein Gerät erkannt." : "No device detected.";
        gtk_label_set_text(GTK_LABEL(root_status_label), no_device);
        return;
    }

    if (strcmp(language, "de") == 0) 
    {
        root_access = "✅ Root-Rechte verfügbar.";
        no_root_access = "❌ Keine Root-Rechte verfügbar.";
    } 
    else 
    {
        root_access = "✅ Root permissions available.";
        no_root_access = "❌ No root permissions available.";
    }

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
