/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - rename_boot			 *
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

// rename a file to boot.img
void rename_boot(const gchar *bo_filename) 
{
    gchar *target_directory_boot = get_home("~/Downloads/ROM-Install/");
    if (target_directory_boot == NULL) 
    {
        g_print("Fehler beim Erweitern des Verzeichnispfads.\n");
        return;
    }
    
    const gchar *boot_filename = "boot.img"; 
    gchar *target_path_boot = g_strconcat(target_directory_boot, boot_filename, NULL);
    
    if (rename(bo_filename, target_path_boot) == 0) 
    {
        g_print("Datei erfolgreich umbenannt: %s -> %s\n", bo_filename, boot_filename);
    } 
    
    else 
    {
        g_print("Fehler beim Umbenennen der Datei: %s\n", bo_filename);
    }
    g_free(target_directory_boot);
    g_free(target_path_boot);
}
