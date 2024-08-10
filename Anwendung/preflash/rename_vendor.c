/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - rename_vendor			 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "function_header.h"
#include "file_chooser_header.h"
#include "flash_function_header.h"

// rename a file to vendor.img
void rename_vendor(const gchar *ven_filename) 
{
    gchar *target_directory_vendor = get_home("~/Downloads/ROM-Install/");
    if (target_directory_vendor == NULL) 
    {
        g_print("Fehler beim Erweitern des Verzeichnispfads.\n");
        return;
    }
    
    const gchar *vendor_filename = "vendor.img";
    gchar *target_path_vendor = g_strconcat(target_directory_vendor, vendor_filename, NULL);
     
    if (rename(ven_filename, target_path_vendor) == 0) 
    {
        g_print("Datei erfolgreich umbenannt: %s -> %s\n", ven_filename, vendor_filename);
    } 
    
    else 
    {
        g_print("Fehler beim Umbenennen der Datei: %s\n", ven_filename);
    }
    g_free(target_directory_vendor);
    g_free(target_path_vendor);
}
