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
 *      (C) Copyright 2024 Elias Mörz        *
 *-------------------------------------------*
 *                                           *
 *   Headerpart - header_show_file_chooser   *
 *                                           *
 *-------------------------------------------*
 */

/* headers */ 
#include <gtk/gtk.h>
#include "program_functions.h"
#include "file_chooser_header.h"
#include "function_header.h"
#include "language_check.h"

// Callback function for processing the file
static void file_dialog_response_callback(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
    g_autoptr(GFile) file = gtk_file_dialog_open_finish(GTK_FILE_DIALOG(source_object), res, NULL);
    if (file) 
    {
        g_autofree char *filename = g_file_get_path(file);
        if (filename) 
        {
            FileProcessorFunc process_func = (FileProcessorFunc)user_data;
            process_func(filename);
        }
    }
}

// Function for the file selection dialog
void show_file_chooser(GtkWidget *widget, gpointer data) 
{
    GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_root(widget));
    if (!GTK_IS_WINDOW(parent_window)) 
    {
        parent_window = NULL;
    }

    // Sprache anwenden
    apply_language(); 

    // Dialog for file selection
    GtkFileDialog *dialog = gtk_file_dialog_new();

    gtk_file_dialog_open(dialog, parent_window, NULL, (GAsyncReadyCallback)file_dialog_response_callback, data);
}
