/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
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
 *              Headerpart - css_provider    *
 *                                           *
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

GtkCssProvider* create_css_provider() 
{
    GtkCssProvider *new_provider = gtk_css_provider_new();
    if (!new_provider) 
    {
        fprintf(stderr, "Fehler: Konnte den CSS-Provider nicht erstellen.\n");
        exit(1);
    }
    return new_provider;
}

void unload_css_provider(GtkCssProvider *provider) 
{
    if (provider) 
    {
        g_object_unref(provider);
    }
}
    
void load_css(const char *theme) 
{
    if (provider) 
    {
        g_object_unref(provider);
    }
    provider = create_css_provider();

    // CSS für das helle und dunkle Theme definieren
    const char *light_css =
        "window {"
        "    background-color: #f0f0f0;"
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"
        "    padding: 12px 24px;"
        "    color: #000000;"
        "    font-size: 16px;"
        "}"
        "headerbar {"
        "    background-color: #f0f0f0;"
        "    font-weight: bold;"
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"
        "    padding: 12px 24px;"
        "    color: #ffffff;"
        "    font-size: 16px;"
        "}"
        "button {"
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"
        "    padding: 24px 48px;"
        "    color: #FFFFFF;"
        "    font-size: 16px;"
        "}"
        "button:hover {"
        "    background-color: #A52A2A;"
        "    box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);"
        "}"
        "label {"
        "    color: #000000;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}"
        "notebook {"
        "    background-color: #f0f0f0;"
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"
        "}"
        "notebook tab {"
        "    background-color: #f0f0f0;"
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"
        "}"
        "notebook tab:selected {"
        "    background-color: #FF0000;"
        "    color: black;"
        "}";

    const char *dark_css =
        "window {"
        "    background-color: #2e3436;"
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"
        "    padding: 12px 24px;"
        "    color: #FFFFFF;"
        "    font-size: 16px;"
        "}"
        "headerbar {"
        "    background-color: #2e3436;"
        "    font-weight: bold;"
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"
        "    padding: 12px 24px;"
        "    color: #FFFFFF;"
        "    font-size: 16px;"
        "}"
        "button {"
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"
        "    padding: 24px 48px;"
        "    color: #FFFFFF;"
        "    font-size: 16px;"
        "}"
        "button:hover {"
        "    background-color: #A52A2A;"
        "    box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);"
        "}"
        "label {"
        "    color: #FFFFFF;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}"
        "notebook {"
        "    background-color: #2e3436;"
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"
        "}"
        "notebook tab {"
        "    background-color: #2e3436;"
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"
        "}"
        "notebook tab:selected {"
        "    background-color: #FF0000;"
        "    color: white;"
        "}";

    // CSS für das gewählte Theme laden
    if (strcmp(theme, "dark") == 0) 
    {
        gtk_css_provider_load_from_string(provider, dark_css);
    } 
    else 
    {
        gtk_css_provider_load_from_string(provider, light_css);
    }

    // CSS auf das GTK4-Display anwenden
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}


// Callback to switch the theme
void toggle_theme(GtkWidget *button, gpointer user_data) 
{
    // Switch the theme
    if (strcmp(current_theme, "light") == 0) 
    {
        current_theme = "dark";
        write_dark_file(); // Assuming this saves the theme state
    } 
    else 
    {
        current_theme = "light";
        check_dark_file_light(); // Assuming this resets the theme state
    }

    // Reload the theme
    load_css(current_theme);
}

// Apply the current theme when called
void apply_theme() 
{
    check_dark_file();  // Assuming this checks the current theme state
    load_css(current_theme);
}

// add css to widget
void add_css_provider(GtkWidget *widget, GtkCssProvider *provider) 
{
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );
}

