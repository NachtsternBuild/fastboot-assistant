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
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *label;
    GtkWidget *ok_button;

    // Create the dialog window without using deprecated functions
    dialog = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(dialog), title);
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);

    // Create a vertical box for the dialog content and add it to the dialog
    content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(dialog), content_area);

    // Create the label with the message and add it to the content area
    label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), message);
    gtk_box_append(GTK_BOX(content_area), label);

    // Create an OK button and connect it to close the dialog
    ok_button = gtk_button_new_with_label("OK");
    g_signal_connect(ok_button, "clicked", G_CALLBACK(gtk_window_destroy), dialog);
    gtk_box_append(GTK_BOX(content_area), ok_button);

    // Display the dialog and all its components
    gtk_widget_set_visible(dialog, TRUE);
}
