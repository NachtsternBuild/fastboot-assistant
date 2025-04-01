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
 *         Headerpart - apply_theme			 *
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

// choose the theme 
void apply_theme()
{
	check_auto_theme();
	
	// theme with only css
    if (g_strcmp0(auto_theme, "css_only") == 0) 
    {
        apply_theme_css_only();
        LOG_INFO("Theme mode: css_only");
    }
    
    // theme with css and libadwaita 
    else if (g_strcmp0(auto_theme, "css_adw") == 0) 
    {
        apply_theme_css_adw();
        LOG_INFO("Theme mode: css_adw");
    }
    
    // errors with the theme
    else
    {
    	LOG_ERROR("Theme mode: %s", auto_theme);
    }
}
