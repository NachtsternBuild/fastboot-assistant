/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das Installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              toggle_theme				 *
 *											 *
 *-------------------------------------------*
 */

#include <glib.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include "language_check.h"
#include "program_functions.h"

// names of the config files
#define AUTO_FILE "auto.txt"
#define DARK_FILE "dark.txt"
#define ADW_EXTRA_FILE "adw_css.txt"

char dir_path[512];
char dark_path[2048];
char auto_path[2048];
char adw_path[2048];

static GtkWidget *adw_switch, *css_adw_switch, *css_dark_switch, *css_light_switch, *back_to_home;
static char *current_switch = NULL;

// function to check for a file, using g_file_test
gboolean file_exists_theme(const char *filename)
{
    return g_file_test(filename, G_FILE_TEST_EXISTS);
}

// get the config path
char *config_path_theme()
{
    get_config_dir(dir_path, sizeof(dir_path));
    return dir_path;
}

// get the full path of the auto.txt
char *auto_path_theme()
{
	char *build_path = config_path_theme();
	snprintf(auto_path, sizeof(auto_path), "%s/%s", build_path, AUTO_FILE);
	return auto_path;
}

// get the full path of the adw_css.txt
char *adw_path_theme()
{
	char *build_path = config_path_theme();
	snprintf(adw_path, sizeof(adw_path), "%s/%s", build_path, ADW_EXTRA_FILE);
	return adw_path;
}

// get the full path of the dark.txt
char *dark_path_theme()
{
	char *build_path = config_path_theme();
	snprintf(dark_path, sizeof(dark_path), "%s/%s", build_path, DARK_FILE);
	return dark_path;
}

// function to set the active switch
void set_current_switch()
{
    const char *auto_theme = auto_path_theme();
    const char *dark_theme = dark_path_theme();
    const char *adw_css_theme = adw_path_theme();
    
    // for auto.txt
    if (file_exists_theme(auto_theme))
    {
        current_switch = "Switch 1";
        gtk_switch_set_active(GTK_SWITCH(adw_switch), TRUE);
    }
    // for adw_css.txt
    else if(file_exists_theme(adw_css_theme))
    {
    	current_switch = "Switch 2";
    	gtk_switch_set_active(GTK_SWITCH(css_adw_switch), TRUE);
    }
    // for dark.txt
    else if (file_exists_theme(dark_theme))
    {
        current_switch = "Switch 3";
        gtk_switch_set_active(GTK_SWITCH(css_dark_switch), TRUE);
    }
    // no config files
    else
    {
        current_switch = "Switch 4";
        gtk_switch_set_active(GTK_SWITCH(css_light_switch), TRUE);
    }
}

// function to update the config files
void update_config_files(const char *active_switch)
{
    const char *auto_theme = auto_path_theme();
    const char *dark_theme = dark_path_theme();
    const char *adw_css_theme = adw_path_theme();
    
    // auto theme (adw only)
    if (strcmp(active_switch, "Switch 1") == 0)
    {
    	g_file_set_contents(auto_theme, "libadwaita", -1, NULL);
    	remove(dark_theme);
    	remove(adw_css_theme);
    }
    // auto theme (css + adw)
    else if (strcmp(active_switch, "Switch 2") == 0)
    {
        g_file_set_contents(adw_css_theme, "css_libadwaita", -1, NULL);
        remove(dark_theme);
    }
    // css only (dark)
    else if (strcmp(active_switch, "Switch 3") == 0)
    {
        g_file_set_contents(dark_theme, "css_only", -1, NULL);
        remove(auto_theme);
    	remove(adw_css_theme);
    }
    // css only (light)
    else if (strcmp(active_switch, "Switch 4") == 0)
    {
        remove(auto_theme);
        remove(dark_theme);
    	remove(adw_css_theme);
    }
}

// callback for the first switch
// adw only
void switch1_action()
{
    apply_adw_provider();
    LOG_INFO("Theme mode: adw");
}
// css + adw
void switch2_action()
{
    apply_theme_css_adw();
    LOG_INFO("Theme mode: css_adw");
}

// callback for the second switch
// css only (dark)
void switch3_action()
{
    current_theme = "dark";
    write_dark_file(); // Assuming this saves the theme state
    // Reload the theme
    load_css(current_theme);
    LOG_INFO("Theme mode: css_only (dark)");
}

// callback for the third switch
// css only (light)
void switch4_action()
{
    current_theme = "light";
    check_dark_file_light(); // Assuming this resets the theme state
    // Reload the theme
    load_css(current_theme);
    LOG_INFO("Theme mode: css_only (light)");
}

// callback for the switches
static void switch_toggled(GtkSwitch *widget, GParamSpec *pspec, gpointer user_data)
{
    const gchar *switch_name = (const gchar *) user_data;

    if (gtk_switch_get_active(GTK_SWITCH(widget)))
    {
        // disable the other switches
        // S1
        if (widget != GTK_SWITCH(adw_switch))
        {
        	gtk_switch_set_active(GTK_SWITCH(adw_switch), FALSE);
        }
        // S2
        if (widget != GTK_SWITCH(css_adw_switch))
        {
            gtk_switch_set_active(GTK_SWITCH(css_adw_switch), FALSE);
		}
		// S3
        if (widget != GTK_SWITCH(css_dark_switch))
        {
            gtk_switch_set_active(GTK_SWITCH(css_dark_switch), FALSE);
		}
		// S4
        if (widget != GTK_SWITCH(css_light_switch))
        {
            gtk_switch_set_active(GTK_SWITCH(css_light_switch), FALSE);
		}
		
        // save the active switch
        current_switch = g_strdup(switch_name);

        // update the config files
        update_config_files(current_switch);
			
        LOG_INFO("Active switch: %s", current_switch);
        
        // start the function based on the active switch
        // S1
        if (strcmp(current_switch, "Switch 1") == 0)
        {
            switch1_action();
        }
        // S2
        else if (strcmp(current_switch, "Switch 2") == 0)
        {
            switch2_action();
        }
        // S3
        else if (strcmp(current_switch, "Switch 3") == 0)
        {
            switch3_action();
       	}
       	// S4
        else if (strcmp(current_switch, "Switch 4") == 0)
        {    
        	switch4_action();
        }
    }
    
    LOG_INFO("%s is now %s.", switch_name, gtk_switch_get_active(GTK_SWITCH(widget)) ? "ON" : "OFF");
}

/* function that switch themes → css_only / css_adw / adw */
void toggle_theme(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("toggle_theme");
	
	apply_language();
    
    // create box for get_devices
    GtkWidget *toggle_theme = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(toggle_theme, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(toggle_theme, GTK_ALIGN_CENTER);
    
    // create the switches
    // S1
    adw_switch = gtk_switch_new();
    gtk_switch_set_active(GTK_SWITCH(adw_switch), TRUE); // active by default
    // S2
    css_adw_switch = gtk_switch_new();  
    gtk_switch_set_active(GTK_SWITCH(css_adw_switch), FALSE);
    // S3
    css_dark_switch = gtk_switch_new();
    gtk_switch_set_active(GTK_SWITCH(css_dark_switch), FALSE);
    // S4
    css_light_switch = gtk_switch_new();
    gtk_switch_set_active(GTK_SWITCH(css_light_switch), FALSE);

    // create the labels for the switches
    GtkWidget *adw_label = gtk_label_new(_("Use system colors"));
    GtkWidget *css_adw_label = gtk_label_new(_("Custom colors"));
    GtkWidget *css_dark_label = gtk_label_new(_("Manual theme (dark)"));
    GtkWidget *css_light_label = gtk_label_new(_("Manual theme (light)"));

    // add the switches and the label to the box
    // S1
    gtk_box_append(GTK_BOX(toggle_theme), adw_label);
    gtk_box_append(GTK_BOX(toggle_theme), adw_switch);
    // S2
    gtk_box_append(GTK_BOX(toggle_theme), css_adw_label);
    gtk_box_append(GTK_BOX(toggle_theme), css_adw_switch);
    // S3    
    gtk_box_append(GTK_BOX(toggle_theme), css_dark_label);
    gtk_box_append(GTK_BOX(toggle_theme), css_dark_switch);
    // S4    
    gtk_box_append(GTK_BOX(toggle_theme), css_light_label);
    gtk_box_append(GTK_BOX(toggle_theme), css_light_switch);
        
    // set alignment and expansion for the switches and labels
    gtk_widget_set_halign(adw_switch, GTK_ALIGN_CENTER); 
    gtk_widget_set_halign(css_adw_switch, GTK_ALIGN_CENTER); 
    gtk_widget_set_halign(css_dark_switch, GTK_ALIGN_CENTER); 
    gtk_widget_set_halign(css_light_switch, GTK_ALIGN_CENTER);  
    
    gtk_widget_set_valign(adw_switch, GTK_ALIGN_CENTER);    
    gtk_widget_set_valign(css_adw_switch, GTK_ALIGN_CENTER);  
    gtk_widget_set_valign(css_dark_switch, GTK_ALIGN_CENTER); 
    gtk_widget_set_valign(css_light_switch, GTK_ALIGN_CENTER);   
	
	gtk_widget_set_hexpand(adw_switch, TRUE); 
    gtk_widget_set_hexpand(css_adw_switch, TRUE); 
    gtk_widget_set_hexpand(css_dark_switch, TRUE);
    gtk_widget_set_hexpand(css_light_switch, TRUE);
	
	gtk_widget_set_vexpand(adw_switch, TRUE);
    gtk_widget_set_vexpand(css_adw_switch, TRUE);
    gtk_widget_set_vexpand(css_dark_switch, TRUE);
    gtk_widget_set_vexpand(css_light_switch, TRUE);

    // connect the switches
    g_signal_connect(adw_switch, "notify::active", G_CALLBACK(switch_toggled), "Switch 1");
    g_signal_connect(css_adw_switch, "notify::active", G_CALLBACK(switch_toggled), "Switch 2");
    g_signal_connect(css_dark_switch, "notify::active", G_CALLBACK(switch_toggled), "Switch 3");
    g_signal_connect(css_light_switch, "notify::active", G_CALLBACK(switch_toggled), "Switch 4");
	
    // set the current switch
    set_current_switch();
    
    // function to show the home page
	const char *back_to_home_char = _("Back to Home");
	back_to_home = create_icon_nav_button_with_position("pan-start-symbolic", back_to_home_char, G_CALLBACK(show_home_page), stack, GTK_ALIGN_CENTER);
	gtk_box_append(GTK_BOX(toggle_theme), back_to_home);
    
	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "toggle_theme")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), toggle_theme, "toggle_theme");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "toggle_theme");
	
	LOG_INFO("end toggle_theme");
}
