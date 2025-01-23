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
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "file_chooser_header.h"
#include "function_header.h"
#include "language_check.h"

// function for work with the file
static void file_dialog_response_callback(GtkFileDialog *dialog, GAsyncResult *res, gpointer user_data) 
{
    g_autoptr(GFile) file = gtk_file_dialog_open_finish(dialog, res, NULL);
    if (file) 
    {
        g_autofree char *filename = g_file_get_path(file);
        if (filename) 
        {
            // the user work with the function
            FileProcessorFunc process_func = (FileProcessorFunc)user_data;
            process_func(filename);
        }
    }
}

// function for the filechooser dialog
void show_file_chooser(GtkWidget *widget, gpointer data) 
{
    GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_root(widget));
    if (!GTK_IS_WINDOW(parent_window)) 
    {
        parent_window = NULL;
    }

    apply_language();

    // create filechooser
    GtkFileDialog *dialog = gtk_file_dialog_new();

    // create filter list
    GListStore *filter_list = g_list_store_new(GTK_TYPE_FILE_FILTER);
	
	// filter for all files
    GtkFileFilter *filter_all = gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter_all, "*");
    const char *filter_1_name = strcmp(language, "de") == 0 ? "Alle Dateien" : "All files";
    gtk_file_filter_set_name(filter_all, filter_1_name);
    g_list_store_append(filter_list, filter_all);
    
    // filter for .img-files
    GtkFileFilter *filter_img = gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter_img, "*.img");
    const char *filter_2_name = strcmp(language, "de") == 0 ? "Image-Dateien" : "Image files";
    gtk_file_filter_set_name(filter_img, filter_2_name);
    g_list_store_append(filter_list, filter_img);
    
    // filter for .img.xz-files
    GtkFileFilter *filter_img_xz = gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter_img_xz, "*.img.xz");
    const char *filter_3_name = strcmp(language, "de") == 0 ? "Komprimierte Image-Dateien (xz)" : "Compressed image files (xz)";
    gtk_file_filter_set_name(filter_img_xz, filter_3_name);
    g_list_store_append(filter_list, filter_img_xz);
    
    // filter for .zip-files
    GtkFileFilter *filter_zip = gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter_zip, "*.zip");
    const char *filter_4_name = strcmp(language, "de") == 0 ? "Zip-Dateien" : "Zip files";
    gtk_file_filter_set_name(filter_zip, filter_4_name);
    g_list_store_append(filter_list, filter_zip);

    // apply filter
    gtk_file_dialog_set_filters(dialog, G_LIST_MODEL(filter_list));

    // show dialog and connect callback
    gtk_file_dialog_open(dialog, parent_window, NULL, (GAsyncReadyCallback)file_dialog_response_callback, data);
}

