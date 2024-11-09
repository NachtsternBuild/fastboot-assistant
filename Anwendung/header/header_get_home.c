/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *         Headerpart - get_home			 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

gchar* get_home(const gchar *path) 
{
    const gchar *home = getenv("HOME");
    if (home == NULL) 
    {
        g_print("Log: Error: HOME environment variable not found.\n");
        return NULL;
    }
    // for '~/'
    if (g_str_has_prefix(path, "~/")) 
    {
        gchar *short_path = g_strconcat(home, path + 1, NULL);
        return short_path;
    }
    return g_strdup(path);
}
