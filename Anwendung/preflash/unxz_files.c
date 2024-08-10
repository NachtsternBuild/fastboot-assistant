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
#include "file_chooser_header.h"
#include "flash_function_header.h"

// use 'unxz' to decompress .xz files
void unxz_files(const gchar *xz_filename) 
{
    gchar *command = g_strdup_printf("unxz \"%s\"", xz_filename);
    int result = system(command);
    if (result == 0) 
    {
        g_print("Entpacken abgeschlossen: %s\n", xz_filename);
    }
     
    else 
    {
        g_print("Fehler beim Entpacken der Datei: %s\n", xz_filename);
    }
    g_free(command);
}
