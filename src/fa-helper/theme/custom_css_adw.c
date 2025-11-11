/**
* custom_css_adw.c
*
* @license:
* based on custom_css_adw.c from ATL UIBase
*
* (C) Copyright 2025 AtlantisOS Project
* by @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
* Usage:
* const char *adw_css = get_custom_adw_css();
* gtk_css_provider_load_from_string(provider_adw, adw_css);
*
* Note: 
* Requires GTK4 (> 4.10), libadwaita (> 1.4)
*/
#include "atlbase.h"

const char *get_custom_adw_css(void) 
{
	return
		"window {\n"
        "    background-color: @theme_bg_color;\n"
        "    border: 2px solid @accent_bg_color;\n"
        "    border-radius: 35px;\n"
        "    padding: 12px 24px;\n"
        "    color: @theme_fg_color;\n"
        "    font-size: 16px;\n"
        "}\n"
        "button {\n"
        "    border: 2px solid @accent_bg_color;\n"
        "    border-radius: 35px;\n"
        "    padding: 24px 48px;\n"
        "    background-color: @theme_bg_color;\n"
        "    color: @theme_fg_color;\n"
        "    font-size: 16px;\n"
        "}\n"
        "button:hover {\n"
        "    background-color: @accent_color;\n"
        "    box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);\n"
        "}\n"
        "label {\n"
        "    color: @theme_fg_color;\n"
        "    font-size: 16px;\n"
        "    font-weight: bold;\n"
        "}\n"
        "notebook {\n"
        "    background-color: @theme_bg_color;\n"
        "    border: 2px solid @accent_bg_color;\n"
        "    border-radius: 35px;\n"
        "}\n"
        "headerbar {\n"
        "    background-color: @theme_bg_color;\n"
        "    font-weight: bold;\n"
        "    border: 2px solid @accent_bg_color;\n"
        "    border-radius: 35px;\n"
        "    padding: 12px 24px;\n"
        "    color: @theme_fg_color;\n"
        "    font-size: 16px;\n"
        "}\n"
        "frame {\n"
    	"	border-width: 5px;\n"
    	"	border-radius: 35px;\n"
		"   border-color: @accent_bg_color;\n"
    	"	border-style: solid;\n"
    	"	padding: 10px;\n"
		"}\n";
}
	
	
