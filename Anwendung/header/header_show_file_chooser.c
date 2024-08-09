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
 *   Headerpart - header_show_file_chooser	 *
 *											 *
 *-------------------------------------------*
 */

/* headers */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "file_chooser_header.h"
#include "function_header.h"

/*
*** A example for use this function ***
*** the functions should define in the header: file_chosser_header.h (decompress_xz_file or rename_file)
	// Signal-Handler für die Buttons
    g_signal_connect(button_xz, "clicked", G_CALLBACK(show_file_chooser), (gpointer)decompress_xz_file);
    g_signal_connect(button_rename, "clicked", G_CALLBACK(show_file_chooser), (gpointer)rename_file);
*/

// Function that displays the file selection dialogue and delegates processing to a passed function
void show_file_chooser(GtkWidget *widget, gpointer data) 
{
    GtkWidget *parent_window = gtk_widget_get_toplevel(widget);

    // Ensure that the parent widget is actually a GtkWindow
    if (!GTK_IS_WINDOW(parent_window)) 
    {
        parent_window = NULL;
    }

    // Processing function
    FileProcessorFunc process_func = (FileProcessorFunc)data;

    GtkWidget *dialog = gtk_file_chooser_dialog_new("Datei auswählen",
                                                    GTK_WINDOW(parent_window),
                                                    GTK_FILE_CHOOSER_ACTION_OPEN,
                                                    "_Abbrechen", GTK_RESPONSE_CANCEL,
                                                    "_Öffnen", GTK_RESPONSE_ACCEPT,
                                                    NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) 
    {
        gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        if (filename) 
        {
            process_func(filename);  // Passes the file to the passed function for processing
            g_free(filename);
        }
    }

    gtk_widget_destroy(dialog);
}


