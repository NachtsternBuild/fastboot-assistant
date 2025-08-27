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
 *              Headerpart - next_page       *
 *                                           *
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
    // check data are okay
    if (!GTK_IS_NOTEBOOK(data)) 
    {
        LOG_ERROR("next_page: data is not a valid GtkNotebook pointer.");
        return;
    }

    GtkNotebook *notebook = GTK_NOTEBOOK(data);
    int current_page = gtk_notebook_get_current_page(notebook);
    gtk_notebook_set_current_page(notebook, current_page + 1);

    LOG_INFO("Switched to page: %d", current_page + 1);
}

