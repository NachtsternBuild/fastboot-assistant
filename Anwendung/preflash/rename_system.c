/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - rename_system			 *
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

// rename a file to system.img
void rename_system(const gchar *sys_filename) 
{
    gchar *target_directory = get_home("~/Downloads/ROM-Install/");
    if (target_directory == NULL) 
    {
        g_print("Fehler beim Erweitern des Verzeichnispfads.\n");
        return;
    }

    const gchar *system_filename = "system.img";
    
    gchar *target_path = g_strconcat(target_directory, system_filename, NULL);
    
    if (rename(sys_filename, target_path) == 0) 
    {
        g_print("Datei erfolgreich umbenannt: %s -> %s\n", sys_filename, system_filename);
    } 
    
    else 
    {
        g_print("Fehler beim Umbenennen der Datei: %s\n", sys_filename);
    }
    
    g_free(target_directory);
    g_free(target_path);
}
