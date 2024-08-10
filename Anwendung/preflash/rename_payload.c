/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - rename_payload			 *
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

// rename a file to payload.zip
void rename_payload(const gchar *pay_filename) 
{
    const gchar *payload_filename = "payload.zip"; 
    if (rename(pay_filename, payload_filename) == 0) 
    {
        g_print("Datei erfolgreich umbenannt: %s -> %s\n", pay_filename, payload_filename);
    } 
    
    else 
    {
        g_print("Fehler beim Umbenennen der Datei: %s\n", pay_filename);
    }
}
