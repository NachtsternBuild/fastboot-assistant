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
 *  Headerpart - show_message_with_title     *
 *                                           *
 *-------------------------------------------*
 */

/* headers */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

void show_message_with_title(const char *title, const char *message) 
{
    // Create a new GtkMessageDialog with the title and message
    GtkWidget *dialog = gtk_message_dialog_new_with_markup(
        NULL,  // Parent window (NULL if no parent)
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,  // Message type
        GTK_BUTTONS_OK,    // Buttons
        "<b>%s</b>\n%s", title, message);  // Format string for title and message
    
    // Connect the dialog's response signal to destroy it after user interaction
    g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_destroy), dialog);

    // Display the dialog
    gtk_window_present(GTK_WINDOW(dialog));
}

