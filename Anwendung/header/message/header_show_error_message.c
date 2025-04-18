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
 *         Headerpart - show_error_message   *
 *                                           *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

void show_error_message(GtkWindow *parent_window, const char *message)
{
     // Format the message
    const char *formatted_message = g_strdup_printf("\n\n%s\n\n", message);
    
    // Create a new dialog window
    GtkWidget *dialog = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Error");
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    if (parent_window) 
    {
        gtk_window_set_transient_for(GTK_WINDOW(dialog), parent_window);
        gtk_window_set_destroy_with_parent(GTK_WINDOW(dialog), TRUE);
    }

    // Create a vertical box container for dialog content
    GtkWidget *content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(dialog), content_area);

    // Create a label for the error message and add it to the content area
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), formatted_message);
    gtk_box_append(GTK_BOX(content_area), label);

    // Create a "Close" button and connect it to destroy the dialog
    GtkWidget *close_button = gtk_button_new_with_label("Close");
    g_signal_connect(close_button, "clicked", G_CALLBACK(close_dialog), dialog);
    gtk_box_append(GTK_BOX(content_area), close_button);

    // Display the dialog
    gtk_widget_set_visible(dialog, TRUE);
    
    g_free((char *)formatted_message);
}

