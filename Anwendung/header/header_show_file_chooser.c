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

// Callback function to handle the dialog response
static void file_chooser_open_callback(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
    GtkFileDialog *dialog = GTK_FILE_DIALOG(source_object);
    GFile *file = gtk_file_dialog_open_finish(dialog, res, NULL);
    
    if (file) 
    {
        char *filename = g_file_get_path(file);

        if (filename) 
        {
            FileProcessorFunc process_func = (FileProcessorFunc)user_data;
            process_func(filename);  // Passes the file to the passed function for processing
            g_free(filename);
        }

        g_object_unref(file);
    }

    g_object_unref(dialog);  // Free dialog resources
}

// Function that displays the file selection dialog
void show_file_chooser(GtkWidget *widget, gpointer data) 
{
    GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_root(widget));

    // Check that the parent widget is a window
    if (!GTK_IS_WINDOW(parent_window)) 
    {
        parent_window = NULL;
    }

    // Apply language
    apply_language(); 
    
    // Set dialog text based on the current language
    const char *dialog_title = (strcmp(language, "de") == 0) ? "Datei auswählen" : "Open File";

    // Processing function
    FileProcessorFunc process_func = (FileProcessorFunc)data;

    // Create a new file dialog
    GtkFileDialog *dialog = gtk_file_dialog_new();

    // Set the title of the dialog 
    gtk_native_dialog_set_title(GTK_NATIVE_DIALOG(dialog), dialog_title);

    // Open the file dialog asynchronously
    gtk_file_dialog_open(dialog, parent_window, NULL, file_chooser_open_callback, process_func);
}

