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

void load_css(const char *theme) 
{
    // Create a new CSS provider if it doesn't exist
    if (!provider) 
    {
        provider = create_css_provider();
        if (!provider) 
        {
            fprintf(stderr, "Fehler: CSS-Provider konnte nicht initialisiert werden, CSS wird nicht angewendet.\n");
            exit(1);
        }
    }

    // Define CSS for the light theme, without universal selectors
    //"    background-color: #8B0000;"
    //        "    font-weight: 500;"
    const char *light_css =
        "window {"
        "  	 background-color: #f0f0f0;"
    	"  	 border: 2px solid #8B0000;"
    	"	 border-radius: 35px;"
        "    padding: 12px 24px;"
        "    color: #000000;"
        "    font-size: 16px;"
    	"}"
        "headerbar {"
        "  	 background-color: #f0f0f0;"
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
        "GtkNotebook {"
        "    background-color: #f0f0f0;"
        "    border: 2px solid #8B0000;"  
        "    border-radius: 35px;"  
        "}"
        "GtkNotebook tab {"
        "    background-color: #f0f0f0;" 
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"  
        "}"
        "GtkNotebook tab:checked {"
        "    background-color: #FF0000;" 
        "    color: black;"              
        "}"
         "GtkDialog {"
        "    background-color: #f0f0f0;"
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"         
        "    padding: 24px;"             
        "}"
        "GtkDialog .content_area {"
        "    background-color: #f0f0f0;"
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"     
        "}"
        "GtkDialog .button_area {"
        "    background-color: #f0f0f0;"  
        "    padding: 10px;"
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"              
        "}";

    // Define CSS for the dark theme
    // "    background-color: #8B0000;"
    // "    font-weight: 500;"
    const char *dark_css =
        "window {"
        "  	 background-color: #2e3436;"
    	"  	 border: 2px solid #8B0000;"
    	"	 border-radius: 35px;"
        "    padding: 12px 24px;"
        "    color: #FFFFFF;"
        "    font-size: 16px;"
    	"}"
        "headerbar {"
        "  	 background-color: #2e3436;"
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
        "GtkNotebook {"
        "    background-color: #2e3436;"
        "    border: 2px solid #8B0000;"  
        "    border-radius: 35px;"  
        "}"
        "GtkNotebook tab {"
        "    background-color: #2e3436;" 
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"  
        "}"
        "GtkNotebook tab:checked {"
        "    background-color: #FF0000;" 
        "    color: white;"              
        "}"
         "GtkDialog {"
        "    background-color: #2e3436;"
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"         
        "    padding: 24px;"             
        "}"
        "GtkDialog .content_area {"
        "    background-color: #2e3436;"
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"     
        "}"
        "GtkDialog .button_area {"
        "    background-color: #2e3436;"  
        "    padding: 10px;"
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"              
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
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
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
    //      "    text-align: center;"
    //        "    font-weight: 500;"
    const char *light_css =
        "window {"
        "  	 background-color: #f0f0f0;"
    	"  	 border: 2px solid #00008B;"
    	"	 border-radius: 35px;"
        "    padding: 12px 24px;"
        "    color: #000000;"
        "    font-size: 16px;"
    	"}"
        "headerbar {"
        "  	 background-color: #f0f0f0;"
        "    font-weight: bold;"
        "    border: 2px solid #00008B;"
        "    border-radius: 35px;"
        "    padding: 12px 24px;"
        "    color: #ffffff;"
        "    font-size: 16px;"
        "}"
        "button {"
        "    border: 2px solid #00008B;"
        "    border-radius: 35px;"
        "    padding: 24px 48px;"
        "    color: #ffffff;"
        "    font-size: 16px;"
        "    font-weight: 500;"
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
        "GtkNotebook {"
        "    background-color: #2e3436;"
        "    border: 2px solid #00008B;"  
        "    border-radius: 35px;"  
        "}"
        "GtkNotebook tab {"
        "    background-color: #2e3436;" 
        "    border: 2px solid #00008B;"
        "    border-radius: 35px;"  
        "}"
        "GtkNotebook tab:checked {"
        "    background-color: #FF0000;" 
        "    color: white;"              
        "}"
         "GtkDialog {"
        "    background-color: #2e3436;"
        "    border: 2px solid #00008B;"
        "    border-radius: 35px;"         
        "    padding: 24px;"             
        "}"
        "GtkDialog .content_area {"
        "    background-color: #2e3436;"
        "    border: 2px solid #00008B;"
        "    border-radius: 35px;"     
        "}"
        "GtkDialog .button_area {"
        "    background-color: #2e3436;"  
        "    padding: 10px;"
        "    border: 2px solid #00008B;"
        "    border-radius: 35px;"              
        "}";

    // Define CSS for the dark theme
    // "    background-color: #00008B;"
    //        "    text-align: center;"
    //        "    font-weight: 500;"
    const char *dark_css =
        "window {"
        "  	 background-color: #f0f0f0;"
    	"  	 border: 2px solid #00008B;"
    	"	 border-radius: 35px;"
        "    padding: 12px 24px;"
        "    color: #000000;"
        "    font-size: 16px;"
    	"}"
        "headerbar {"
        "  	 background-color: #f0f0f0;"
        "    font-weight: bold;"
        "    border: 2px solid #00008B;"
        "    border-radius: 35px;"
        "    padding: 12px 24px;"
        "    color: #ffffff;"
        "    font-size: 16px;"
        "}"
        "button {"
        "    border: 2px solid #00008B;"
        "    border-radius: 15px;"
        "    padding: 24px 48px;"
        "    color: #ffffff;"
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
        "GtkNotebook {"
        "    background-color: #2e3436;"
        "    border: 2px solid #00008B;"  
        "    border-radius: 15px;"  
        "}"
        "GtkNotebook tab {"
        "    background-color: #2e3436;" 
        "    border: 2px solid #8B0000;"
        "    border-radius: 35px;"  
        "}"
        "GtkNotebook tab:checked {"
        "    background-color: #FF0000;" 
        "    color: white;"              
        "}"
         "GtkDialog {"
        "    background-color: #2e3436;"
        "    border: 2px solid #00008B;"
        "    border-radius: 35px;"         
        "    padding: 24px;"             
        "}"
        "GtkDialog .content_area {"
        "    background-color: #2e3436;"
        "    border: 2px solid #00008B;"
        "    border-radius: 35px;"     
        "}"
        "GtkDialog .button_area {"
        "    background-color: #2e3436;"  
        "    padding: 10px;"
        "    border: 2px solid #00008B;"
        "    border-radius: 35px;"              
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
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(darkblue_provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
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
