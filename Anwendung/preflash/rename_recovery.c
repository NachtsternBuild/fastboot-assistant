/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - rename_recovery		 *
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

// rename a file to recovery.img
void rename_recovery(const gchar *rec_filename) 
{
    gchar *target_directory_recovery = get_home("~/Downloads/ROM-Install/");
    if (target_directory_recovery == NULL) 
    {
        g_print("Fehler beim Erweitern des Verzeichnispfads.\n");
        return;
    }
    
    const gchar *recovery_filename = "recovery.img";
    gchar *target_path_recovery = g_strconcat(target_directory_recovery, recovery_filename, NULL);
     
    if (rename(rec_filename, target_path_recovery) == 0) 
    {
        g_print("Datei erfolgreich umbenannt: %s -> %s\n", rec_filename, recovery_filename);
    } 
    
    else 
    {
        g_print("Fehler beim Umbenennen der Datei: %s\n", rec_filename);
    }
    g_free(target_directory_recovery);
    g_free(target_path_recovery);
}


