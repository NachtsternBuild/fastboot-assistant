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
 *    Headerpart - show_dialog_with_entry    *
 *                                           *
 *-------------------------------------------*
 */

/* headers */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// define set the call to NULL
static NumberCallback global_callback = NULL;

// callback for ok button
void on_ok_clicked(GtkButton *button, gpointer user_data) 
{
    // get the data from the entry and the window
    GtkEntry *entry = GTK_ENTRY(g_object_get_data(G_OBJECT(button), "entry"));
    GtkWindow *dialog = GTK_WINDOW(user_data);
	// convert the text to a int
    const char *text = gtk_editable_get_text(GTK_EDITABLE(entry));
    int number = atoi(text);
	
    if (global_callback != NULL) 
    {
        // set the number to the var
        global_callback(number);
    }
	// destroy the dialog
    gtk_window_destroy(dialog);
}

/* main function - show_dialog_with_entry */
void show_dialog_with_entry(const char *title, const char *placeholder, NumberCallback callback) 
{
    GtkWidget *dialog;
    GtkWidget *box;
    GtkWidget *entry;
    GtkWidget *ok_button;
    
    // set the input from the entry to the callback
    global_callback = callback;
	
	// create a new dialog
    dialog = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(dialog), title != NULL ? title : "Input Number");
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
	
	// create a box
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(dialog), box);
	
	// create a new entry
    entry = gtk_entry_new();
    // add text as the placeholder
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), placeholder != NULL ? placeholder : "Enter a number:");
    gtk_box_append(GTK_BOX(box), entry);
	
	// create the ok-button
    ok_button = gtk_button_new_with_label("OK");
    gtk_box_append(GTK_BOX(box), ok_button);
	
	// connect the button and the entry
    g_object_set_data(G_OBJECT(ok_button), "entry", entry);
    g_signal_connect(ok_button, "clicked", G_CALLBACK(on_ok_clicked), dialog);
    // show the dialog
    gtk_widget_set_visible(dialog, TRUE);
}

