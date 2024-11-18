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
    // Create the error dialog
    GtkWidget *dialog = gtk_message_dialog_new(
        parent_window,
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_ERROR,
        GTK_BUTTONS_CLOSE,
        "%s",  // Message format
        message
    );

    gtk_window_set_title(GTK_WINDOW(dialog), "Error");

    // Connect the response signal to destroy the dialog on user interaction
    g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_destroy), dialog);

    // Display the dialog
    gtk_window_present(GTK_WINDOW(dialog));
}

