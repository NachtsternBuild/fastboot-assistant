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
 *       Headerpart - switch_page		     *
 *                                           *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

// function to switch pages in the stack 
// this replace next_page
void switch_page(GtkWidget *widget, gpointer user_data) 
{
    GtkStack *stack = GTK_STACK(g_object_get_data(G_OBJECT(widget), "stack"));
    const gchar *next_page = user_data; // next page from parameter
    gtk_stack_set_visible_child_name(stack, next_page);
}

