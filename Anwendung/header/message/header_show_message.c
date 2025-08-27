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
 *              Headerpart - gtk_message     *
 *                                           *
 *-------------------------------------------*
 */

/* headers */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// Function to display a message
void show_message(const char *message) 
{
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *label;
    GtkWidget *ok_button;

    // Create formatted message
    const char *formatted_message = g_strdup_printf("\n\n %s \n\n", message);

    // Create dialog window
    dialog = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(dialog), _("Information"));
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);

    // Vertical container for the contents of the dialog
    content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(dialog), content_area);

    // Create and add a label with the message
    label = gtk_label_new(NULL);
    gtk_label_set_wrap(GTK_LABEL(label), TRUE);
    gtk_label_set_markup(GTK_LABEL(label), formatted_message);
    gtk_box_append(GTK_BOX(content_area), label);

    // Create an OK button and link it to the close function
    ok_button = gtk_button_new_with_label("OK");
    gtk_box_append(GTK_BOX(content_area), ok_button);
    // Connect signal handler and pass dialog as `user_data`.
    g_signal_connect(ok_button, "clicked", G_CALLBACK(close_dialog), dialog);

    // Display the dialog and all its components
    gtk_widget_set_visible(dialog, TRUE);
    
    g_free((char *)formatted_message);
}
