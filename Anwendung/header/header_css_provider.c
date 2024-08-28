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
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              Headerpart - css_provider	 *
 *											 *
 *-------------------------------------------*
 */

/* headers */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

GtkCssProvider *provider = NULL;

// the main css-provider
void css_provider()
{
    // Initialising and loading the CSS provider in the style of android 12 qs
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "button {\n"
        "    background-color: #8B0000;\n"
        "    border: 2px solid #8B0000;\n"
        "    border-radius: 12px;\n"
        "    padding: 24px 48px;\n"
        "    color: #ffffff;\n"
        "    font-size: 16px;\n"
        "    font-weight: 500;\n"
        "    text-align: center;\n"
        "}\n"
        "button:hover {\n"
        "    background-color: #A52A2A;\n"
        "    box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);\n"
        "}\n"
        "label {\n"
        "    color: #FFFFFF;\n"
        "    font-size: 16px;\n"
        "    font-weight: bold;\n"
        "}\n",
        -1,
        NULL);
}

// function that load the css provider
void add_css_provider(GtkWidget *widget, GtkCssProvider *provider) 
{
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}
