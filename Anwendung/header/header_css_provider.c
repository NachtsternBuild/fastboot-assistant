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
#include <unistd.h>  
#include <sys/stat.h> 
#include <sys/types.h> 
#include "program_functions.h"

GtkCssProvider *provider = NULL;
GtkCssProvider *darkblue_provider = NULL;

void load_css(const char *theme) 
{
    // Create a new CSS provider if it doesn't exist
    if (!provider) 
    {
        provider = gtk_css_provider_new();
    }

    // Define CSS for the light theme, without universal selectors
    //"    background-color: #8B0000;"
    const char *light_css =
        "button {"
        "    border: 2px solid #8B0000;"
        "    border-radius: 15px;"
        "    padding: 24px 48px;"
        "    color: #ffffff;"
        "    font-size: 16px;"
        "    font-weight: 500;"
        "    text-align: center;"
        "}"
        "button:hover {"
        "    background-color: #A52A2A;"
        "    box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);"
        "}"
        "label {"
        "    color: #000000;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}";

    // Define CSS for the dark theme
    // "    background-color: #8B0000;"
    const char *dark_css =
        "button {"
        "    border: 2px solid #8B0000;"
        "    border-radius: 15px;"
        "    padding: 24px 48px;"
        "    color: #ffffff;"
        "    font-size: 16px;"
        "    font-weight: 500;"
        "    text-align: center;"
        "}"
        "button:hover {"
        "    background-color: #A52A2A;"
        "    box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);"
        "}"
        "label {"
        "    color: #FFFFFF;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}";

    // Load the appropriate CSS based on the selected theme
    if (strcmp(theme, "dark") == 0) 
    {
        gtk_css_provider_load_from_data(provider, dark_css, -1, NULL);
    } 
    else 
    {
        gtk_css_provider_load_from_data(provider, light_css, -1, NULL);
    }

    // Apply the CSS provider to the entire screen but only to user-defined styles
    GtkStyleContext *context = gtk_style_context_new();
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    g_object_unref(context);  // Free the context when done
}

void load_css_blue(const char *theme) 
{
    // Create a new CSS provider if it doesn't exist
    if (!darkblue_provider) 
    {
        darkblue_provider = gtk_css_provider_new();
    }

    // Define CSS for the light theme, without universal selectors
    //"    background-color: #00008B;"
    const char *light_css =
        "button {"
        "    border: 2px solid #00008B;"
        "    border-radius: 15px;"
        "    padding: 24px 48px;"
        "    color: #ffffff;"
        "    font-size: 16px;"
        "    font-weight: 500;"
        "    text-align: center;"
        "}"
        "button:hover {"
        "    background-color: #A52A2A;"
        "    box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);"
        "}"
        "label {"
        "    color: #000000;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}";

    // Define CSS for the dark theme
    // "    background-color: #00008B;"
    const char *dark_css =
        "button {"
        "    border: 2px solid #00008B;"
        "    border-radius: 15px;"
        "    padding: 24px 48px;"
        "    color: #ffffff;"
        "    font-size: 16px;"
        "    font-weight: 500;"
        "    text-align: center;"
        "}"
        "button:hover {"
        "    background-color: #A52A2A;"
        "    box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);"
        "}"
        "label {"
        "    color: #FFFFFF;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}";

    // Load the appropriate CSS based on the selected theme
    if (strcmp(theme, "dark") == 0) 
    {
        gtk_css_provider_load_from_data(darkblue_provider, dark_css, -1, NULL);
    } 
    else 
    {
        gtk_css_provider_load_from_data(darkblue_provider, light_css, -1, NULL);
    }

    // Apply the CSS provider to the entire screen but only to user-defined styles
    GtkStyleContext *context = gtk_style_context_new();
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(darkblue_provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    g_object_unref(context);  // Free the context when done
}

// callback to switch the theme
void toggle_theme(GtkWidget *button, gpointer user_data) 
{
    // change the theme
    // dark
    if (strcmp(current_theme, "light") == 0) 
    {
        current_theme = "dark";
        write_dark_file();
    } 
    
    // light
    else 
    {
        current_theme = "light";
        check_dark_file_light();
    }

    // run the theme
    load_css(current_theme);
}

// Apply the current theme when called
void apply_theme() 
{
    check_dark_file();
    load_css(current_theme);
}

// Apply the blue theme when called
void apply_theme_blue() 
{
    check_dark_file();
    load_css_blue(current_theme);
}


// load the css provider (main)
void add_css_provider(GtkWidget *widget, GtkCssProvider *provider) 
{
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

// load the css provider (darkblue)
void add_css_provider_blue(GtkWidget *widget, GtkCssProvider *darkblue_provider) 
{
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(darkblue_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}
// darkblue #00008B
