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
void check_root_access() 
{
	apply_language();
    const char *root_access;
    const char *no_root_access;

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
    int status = system("adb shell su -c 'whoami' > /dev/null 2>&1");

    // set status label
    gtk_label_set_text(GTK_LABEL(root_status_label), (status == 0) ? root_access : no_root_access);
}
