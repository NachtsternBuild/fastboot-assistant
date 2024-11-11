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
#include <gtk/gtk.h>
#include "program_functions.h"
#include "file_chooser_header.h"
#include "function_header.h"

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
#include <gtk/gtk.h>
#include "program_functions.h"
#include "file_chooser_header.h"
#include "function_header.h"

// Function that displays the file selection dialog and delegates processing to a passed function
void show_file_chooser(GtkWidget *widget, gpointer data) 
{
    GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_root(widget));

    // Check that the parent widget is a window
    if (!GTK_IS_WINDOW(parent_window)) 
    {
        parent_window = NULL;
    }

    // Apply language settings
    apply_language(); 
    
    // Set dialog text based on the current language
    const char *dialog_title = (strcmp(language, "de") == 0) ? "Datei auswählen" : "Open File";
    const char *cancel_text = (strcmp(language, "de") == 0) ? "_Abbrechen" : "_Cancel";
    const char *open_text = (strcmp(language, "de") == 0) ? "_Öffnen" : "_Open";

    // Processing function
    FileProcessorFunc process_func = (FileProcessorFunc)data;

    GtkFileChooserDialog *dialog = GTK_FILE_CHOOSER_DIALOG(gtk_file_chooser_dialog_new(dialog_title,
                                                                                      parent_window,
                                                                                      GTK_FILE_CHOOSER_ACTION_OPEN,
                                                                                      cancel_text, GTK_RESPONSE_CANCEL,
                                                                                      open_text, GTK_RESPONSE_ACCEPT,
                                                                                      NULL));

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) 
    {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        if (filename) 
        {
            process_func(filename);  // Passes the file to the passed function for processing
            g_free(filename);
        }
    }

    gtk_window_destroy(GTK_WINDOW(dialog));
}

