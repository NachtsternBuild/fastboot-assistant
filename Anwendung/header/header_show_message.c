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

void show_message(const char *message) 
{
    GtkWidget *dialog;

    // Create a message dialog with markup
    dialog = gtk_message_dialog_new_with_markup(NULL, 
                                                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "%s", message);  // Sets the main message directly

    // Connect signal to destroy dialog after response
    g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_destroy), NULL);

    // Display the dialog
    gtk_window_present(GTK_WINDOW(dialog));
}   

