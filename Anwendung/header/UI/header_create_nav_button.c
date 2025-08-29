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
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *         Headerpart - create_nav_button	 *
 *											 *
 *-------------------------------------------*
 */

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// create a button for navigation
GtkWidget *create_nav_button(const char *label, GCallback callback, gpointer data) 
{
    GtkWidget *button = gtk_button_new_with_label(label);
    g_signal_connect(button, "clicked", callback, data);
    return button;
}

// create a button with icon
GtkWidget* create_icon_nav_button(const char *icon_name, const char *label_text, GCallback callback, gpointer data) 
{
    GtkWidget *button = gtk_button_new();
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    GtkWidget *image = gtk_image_new_from_icon_name(icon_name);
    GtkWidget *label = gtk_label_new(label_text);

    gtk_box_append(GTK_BOX(box), image);
    gtk_box_append(GTK_BOX(box), label);
    gtk_button_set_child(GTK_BUTTON(button), box);
    g_signal_connect(button, "clicked", callback, data);

    return button;
}

// create a button with icon, but without callback
GtkWidget* create_icon_nav_button_no_callback(const char *icon_name, const char *label_text) 
{
    GtkWidget *button = gtk_button_new();
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    GtkWidget *image = gtk_image_new_from_icon_name(icon_name);
    GtkWidget *label = gtk_label_new(label_text);

    gtk_box_append(GTK_BOX(box), image);
    gtk_box_append(GTK_BOX(box), label);
    gtk_button_set_child(GTK_BUTTON(button), box);
    
    return button;
}

// create a button with two icons
GtkWidget* create_icon_nav_button_with_header(const char *main_icon, const char *header_icon, const char *label_text, GCallback callback, gpointer data) 
{
    GtkWidget *button = gtk_button_new();
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    if (header_icon != NULL) 
    {
        GtkWidget *header_img = gtk_image_new_from_icon_name(header_icon);
        gtk_box_append(GTK_BOX(box), header_img);
    }

    GtkWidget *main_img = gtk_image_new_from_icon_name(main_icon);
    GtkWidget *label = gtk_label_new(label_text);

    gtk_box_append(GTK_BOX(box), main_img);
    gtk_box_append(GTK_BOX(box), label);
    gtk_button_set_child(GTK_BUTTON(button), box);
    g_signal_connect(button, "clicked", callback, data);

    return button;
}

// create a button with an icon and set special position
GtkWidget* create_icon_nav_button_with_position(const char *icon_name, const char *label_text, GCallback callback, gpointer data, GtkAlign alignment)
{
    GtkWidget *button = gtk_button_new();
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    GtkWidget *image = gtk_image_new_from_icon_name(icon_name);
    GtkWidget *label = gtk_label_new(label_text);

    gtk_box_append(GTK_BOX(box), image);
    gtk_box_append(GTK_BOX(box), label);

    gtk_widget_set_halign(box, alignment);

    gtk_button_set_child(GTK_BUTTON(button), box);
    g_signal_connect(button, "clicked", callback, data);

    return button;
}
