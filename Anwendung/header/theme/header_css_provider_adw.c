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
#include <adwaita.h>  
#include <sys/stat.h> 
#include <sys/types.h> 
#include "program_functions.h"

GtkCssProvider *provider_adw = NULL;

char* rgba_to_hex(const GdkRGBA *color) 
{
    static char hex_color[8];  // 7 Zeichen für #RRGGBB + Nullterminierung
    snprintf(hex_color, sizeof(hex_color), "#%02X%02X%02X",
             (int)(color->red * 255),
             (int)(color->green * 255),
             (int)(color->blue * 255));
    return hex_color;
}


// function to load the css provider with adw themes
void load_css_adw() 
{
    if (provider_adw) 
    {
        g_object_unref(provider_adw);
    }
    provider_adw = create_css_provider();
	
    // get the adw styl manager
	AdwStyleManager *style_manager = adw_style_manager_get_default();

	// define the colors
	char bg_color_str[8];
	char fg_color_str[8];
	char text_color_str[8];
	// get the accent color from adw
	const GdkRGBA *accent_color = adw_style_manager_get_accent_color_rgba(style_manager);

	// get the background color → adw
	// dark theme
	if (adw_style_manager_get_dark(style_manager)) 
	{
    	snprintf(bg_color_str, sizeof(bg_color_str), "#2e3436"); // dark
    	snprintf(fg_color_str, sizeof(fg_color_str), "#E0E0E0"); // light
    	snprintf(text_color_str, sizeof(text_color_str), "#FFFFFF"); // light
	} 
	
	// light theme
	else 
	{
    	snprintf(bg_color_str, sizeof(bg_color_str), "#f0f0f0"); // light
    	snprintf(fg_color_str, sizeof(fg_color_str), "#000000"); // dark
    	snprintf(text_color_str, sizeof(text_color_str), "#000000"); // dark
	}
         
    // convert the gdkrgba to hex
    char *accent_color_str = rgba_to_hex(accent_color);
             
    // create css and add colors from libadwaita
    char css[2048];
    snprintf(css, sizeof(css),
        "window {"
        "    background-color: %s;" // bg color - 1
        "    border: 2px solid %s;" // accent color - 2
        "    border-radius: 35px;"
        "    padding: 12px 24px;"
        "    color: %s;" // fg color - 3
        "    font-size: 16px;"
        "}"
        "button {"
        "    border: 2px solid %s;" // accent color - 4
        "    border-radius: 35px;"
        "    padding: 24px 48px;"
        "    background-color: %s;" // bg color - 5
        "    color: %s;" // text / fg color - 6 
        "    font-size: 16px;"
        "}"
        "button:hover {"
        "    background-color: %s;" // fg color - 7
        "    box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);"
        "}"
        "label {"
        "    color: %s;" // text / fg color - 8
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}"
        "notebook {"
        "    background-color: %s;" // bg color - 9
        "    border: 2px solid %s;" // accent color - 10
        "    border-radius: 35px;"
        "}"
        "notebook tab {"
        "    background-color: %s;" // bg color - 11
        "    border: 2px solid %s;" // accent color - 12
        "    border-radius: 35px;"
        "}"
        "notebook tab:selected {"
        "    background-color: %s;" // bg color - 13
        "    color: %s;" // text / fg color - 14
        "}"
        "headerbar {"
        "    background-color: %s;" // bg color - 15
        "    font-weight: bold;"
        "    border: 2px solid %s;" // accent color - 16
        "    border-radius: 35px;"
        "    padding: 12px 24px;"
        "    color: %s;" // text / fg color - 17
        "    font-size: 16px;"
        "}",
        bg_color_str, accent_color_str, fg_color_str, accent_color_str, bg_color_str, fg_color_str, fg_color_str, fg_color_str, bg_color_str, accent_color_str, bg_color_str, accent_color_str, bg_color_str, fg_color_str, bg_color_str, accent_color_str, fg_color_str
    );

    // load css
    gtk_css_provider_load_from_string(provider_adw, css);

    // run css provider
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider_adw),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}

// function to load the css with libadwaita colors
void apply_theme_css_adw() 
{
    load_css_adw();
}
