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
 *      (C) Copyright 2025 Elias Mörz        *
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

// function that create a css provider
GtkCssProvider* create_css_provider() 
{
    GtkCssProvider *new_provider = gtk_css_provider_new();
    if (!new_provider) 
    {
        LOG_ERROR("Could not create the CSS provider.");
        exit(1);
    }
    return new_provider;
}

// function to unload the css provider
void unload_css_provider(GtkCssProvider *provider) 
{
    if (provider) 
    {
        g_object_unref(provider);
    }
}
      
// function for load css
void load_css(const char *theme) 
{
    if (provider) 
    {
        g_object_unref(provider);
    }
    provider = create_css_provider();

    // CSS for light and dark theme
    // for dark theme
    if (strcmp(theme, "dark") == 0)
    {
    	const char *css_paths[] = {
    		"./style_dark.css",
    		"/usr/share/fastboot-assistant/style_dark.css"
		};

		for (int i = 0; i < 2; ++i) 
		{
            if (g_file_test(css_paths[i], G_FILE_TEST_EXISTS)) 
            {
                gtk_css_provider_load_from_path(provider, css_paths[i]);
                break;
            }
        }
	}
	
	// for light theme
	else
	{
		const char *css_paths[] = {
    		"./style_light.css",
    		"/usr/share/fastboot-assistant/style_light.css"
		};

		for (int i = 0; i < 2; ++i) 
		{
    		if (g_file_test(css_paths[i], G_FILE_TEST_EXISTS)) 
    		{
        		gtk_css_provider_load_from_path(provider, css_paths[i]);
        		break;
    		}
		}
	}
	
    // run css for gtk4
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}


// Callback to switch the theme
void toggle_theme_css(GtkWidget *button, gpointer user_data) 
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

// apply the current theme when called
void apply_theme_css_only() 
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

