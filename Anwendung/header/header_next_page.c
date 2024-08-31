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
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              Headerpart - next_page		 *
 *											 *
 *-------------------------------------------*
 */

/* headers */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

void next_page(GtkButton *button, gpointer data) 
{
    // check if 'data' are allowed
    if (!GTK_IS_NOTEBOOK(data)) 
    {
        g_warning("next_page: data is not a valid GtkNotebook pointer.");
        return;
    }

    GtkNotebook *notebook = GTK_NOTEBOOK(data);
    gint current_page = gtk_notebook_get_current_page(notebook);
    gtk_notebook_set_current_page(notebook, current_page + 1);

    g_print("Switched to page: %d\n", current_page + 1);
}

