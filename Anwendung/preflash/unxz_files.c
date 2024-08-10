/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - unxz_files			 	 *
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

// use 'unxz' to decompress .xz files
void unxz_files(const gchar *xz_filename) 
{
    gchar *target_directory = get_home("~/Downloads/ROM-Install/");
    if (target_directory == NULL) 
    {
        g_print("Fehler beim Erweitern des Verzeichnispfads.\n");
        return;
    }
    
    gchar *output_path = g_strconcat(target_directory, xz_filename, NULL);
    gchar *command = g_strdup_printf("unxz -c \"%s\" > \"%s\"", xz_filename, output_path);
    int result = system(command);
    if (result == 0) 
    {
        g_print("Entpacken abgeschlossen: %s\n", xz_filename);
    }
    else 
    {
        g_print("Fehler beim Entpacken der Datei: %s\n", xz_filename);
    }
    g_free(output_path);
    g_free(command);
}
