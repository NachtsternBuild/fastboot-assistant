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

GtkCssProvider *provider = NULL;

// function to load the css provider with adw themes
void load_css_adw() 
{
    if (provider) 
    {
        g_object_unref(provider);
    }
    provider = create_css_provider();

    // get the adw styl manager
    AdwStyleManager *style_manager = adw_style_manager_get_default();
    
    // get the colors
    GdkRGBA bg_color, fg_color, button_color, accent_color;
    adw_style_manager_get_color(style_manager, "window_bg_color", &bg_color); // get window bg color
    adw_style_manager_get_color(style_manager, "window_fg_color", &fg_color); // get window fg color
    adw_style_manager_get_color(style_manager, "button_bg_color", &button_color); // get button color
    adw_style_manager_get_accent_color(style_manager, &accent_color);  // get accent color
    adw_style_manager_get_color(style_manager, "text_color", &text_color); // get text color → option

    // convert gtkrgba to hex
    char bg_color_str[8], fg_color_str[8], button_color_str[8], accent_color_str[8];
    snprintf(bg_color_str, sizeof(bg_color_str), "#%02X%02X%02X", (int)(bg_color.red * 255), (int)(bg_color.green * 255), (int)(bg_color.blue * 255));
    snprintf(fg_color_str, sizeof(fg_color_str), "#%02X%02X%02X", (int)(fg_color.red * 255), (int)(fg_color.green * 255), (int)(fg_color.blue * 255));
    snprintf(button_color_str, sizeof(button_color_str), "#%02X%02X%02X", (int)(button_color.red * 255), (int)(button_color.green * 255), (int)(button_color.blue * 255));
    snprintf(accent_color_str, sizeof(accent_color_str), "#%02X%02X%02X", (int)(accent_color.red * 255), (int)(accent_color.green * 255), (int)(accent_color.blue * 255));
    snprintf(text_color_str, sizeof(text_color_str), "#%02X%02X%02X", (int)(text_color.red * 255), (int)(text_color.green * 255), (int)(text_color.blue * 255));

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
        "    background-color: %s;" // bg / button color - 5
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
        "}",
        bg_color_str, accent_color_str, fg_color_str, accent_color_str, button_color_str, fg_color_str, fg_color_str, fg_color_str, bg_color_str, accent_color_str, bg_color_str, accent_color_str, bg_color_str, fg_color_str
    );

    // CSS aus dem String laden
    gtk_css_provider_load_from_data(provider, css, -1, NULL);

    // CSS-Provider auf das Display anwenden
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}

// function to load the css with libadwaita colors
void apply_theme_css_adw() 
{
    load_css_adw();
}
