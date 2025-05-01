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
 *         Headerpart - create_label_icon	 *
 *											 *
 *-------------------------------------------*
 */

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// create a label with icon 
GtkWidget *create_label_with_icon(const char *icon_name, const char *label_text)
{
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    GtkWidget *image = gtk_image_new_from_icon_name(icon_name);
    GtkWidget *label = gtk_label_new(label_text);

    gtk_box_append(GTK_BOX(box), image);
    gtk_box_append(GTK_BOX(box), label);

    return box;
}

// create a label with icon and special position
GtkWidget *create_label_with_icon_and_position(const char *icon_name, const char *label_text, GtkAlign alignment)
{
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    GtkWidget *image = gtk_image_new_from_icon_name(icon_name);
    GtkWidget *label = gtk_label_new(label_text);

    gtk_box_append(GTK_BOX(box), image);
    gtk_box_append(GTK_BOX(box), label);
    
    gtk_widget_set_halign(box, alignment);

    return box;
} 
