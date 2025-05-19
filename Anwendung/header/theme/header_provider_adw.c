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
 *              Headerpart - provider_adw    *
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
AdwStyleManager *style_manager;

// function to load the css provider with adw themes
void load_adw_provider(void) 
{
    gtk_css_provider_load_from_string(provider_adw,       
        "window {\n"
        "    background-color: @theme_bg_color;\n" // bg color - 1
        "    border: 2px solid @accent_bg_color;\n" // accent color - 2
        "    border-radius: 35px;\n"
        "    padding: 12px 24px;\n"
        "    color: @theme_fg_color;\n" // fg color - 3
        "    font-size: 16px;\n"
        "}\n"
        "button {\n"
        "    border: 2px solid @accent_bg_color;\n" // accent color - 4
        "    border-radius: 35px;\n"
        "    padding: 24px 48px;\n"
        "    background-color: @theme_bg_color;\n" // bg color - 5
        "    color: @theme_fg_color;\n" // text / fg color - 6 
        "    font-size: 16px;\n"
        "}\n"
        "button:hover {\n"
  		"	background-color: @accent_color;\n"
  		"	color: @accent_fg_color;\n"
  		"	transition: background-color 150ms ease;\n"
		"}\n"
        "label {\n"
        "    color: @theme_fg_color;\n" // text / fg color - 8
        "    font-size: 16px;\n"
        "    font-weight: bold;\n"
        "}\n"
        "notebook {\n"
        "    background-color: @theme_bg_color;\n" // bg color - 9
        "    border: 2px solid @accent_bg_color;\n" // accent color - 10
        "    border-radius: 35px;\n"
        "}\n"
        "notebook tab {\n"
        "    background-color: @theme_bg_color;\n" // bg color - 11
        "    border: 2px solid @accent_bg_color;\n" // accent color - 12
        "    border-radius: 35px;\n"
        "}\n"
        "notebook tab:selected {\n"
        "    background-color: @theme_bg_color;\n" // bg color - 13
        "    color: @theme_fg_color;\n" // text / fg color - 14
        "}\n"
        "headerbar {\n"
        "    background-color: @theme_bg_color;\n" // bg color - 15
        "    font-weight: bold;\n"
        "    border: 2px solid @accent_bg_color;\n" // accent color - 16
        "    border-radius: 35px;\n"
        "    padding: 12px 24px;\n"
        "    color: @theme_fg_color;\n" // text / fg color - 17
        "    font-size: 16px;\n"
        "}\n"
        "frame {\n"
    	"	border-width: 5px;\n"
    	"	border-radius: 35px;\n"
		"   border-color: @accent_bg_color;\n" // accent color - 18
    	"	border-style: solid;\n"
    	"	padding: 10px;\n"
		"}\n");
        
}

// function that reload the adw theme
void adw_theme_changed(AdwStyleManager *style_manager, GParamSpec *pspec, gpointer user_data) 
{
    load_adw_provider();  // reload the adw provider
}

// function that load the adw provider and check for changed theme
void apply_adw_provider() 
{
    // check for the adw provider
    if (provider_adw) 
    {
        g_object_unref(provider_adw);
    }
    // create a new adw provider
    provider_adw = create_css_provider();

	// load the adw provider
    load_adw_provider();
	
	// add the provider to the app
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider_adw),
        GTK_STYLE_PROVIDER_PRIORITY_USER);

    // check for theme change
    AdwStyleManager *style_manager = adw_style_manager_get_default();
    g_signal_connect(style_manager, "notify::dark", G_CALLBACK(adw_theme_changed), NULL);
}

