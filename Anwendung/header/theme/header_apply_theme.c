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
	check_adw_css_theme();
	
	// theme with adw and css
	if (g_strcmp0(auto_theme, "auto") == 0)
	{
		// theme with only libadwaita colors
		if (g_strcmp0(adw_css_theme, "adw") == 0)
		{
			apply_adw_provider();
			LOG_INFO("Theme mode: adw");
		}
		
		// theme with css and libadwaita 
		else if (g_strcmp0(adw_css_theme, "css_adw") == 0)
		{
			apply_theme_css_adw();
        	LOG_INFO("Theme mode: css_adw");
        }
	}
	
	// theme with only css
    else if (g_strcmp0(auto_theme, "css_only") == 0) 
    {
        apply_theme_css_only();
        LOG_INFO("Theme mode: css_only");
    }
    
    // theme with css and libadwaita 
    /*
    else if (g_strcmp0(auto_theme, "auto") == 0 && g_strcmp0(adw_css_theme, "css_adw") == 0) 
    {
        apply_theme_css_adw();
        LOG_INFO("Theme mode: css_adw");
    }
    */
    // errors with the theme
    else
    {
    	LOG_ERROR("Unknown theme combination: auto_theme='%s', adw_css_theme='%s'", auto_theme, adw_css_theme);
    }
}
