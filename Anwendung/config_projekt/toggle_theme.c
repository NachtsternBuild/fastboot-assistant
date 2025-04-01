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

char dir_path[512];
char dark_path[2048];
char auto_path[2048];

// function to check for a file, using g_file_test
gboolean file_exists(const char *filename)
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
    // for auto.txt
    if (file_exists(auto_path_theme))
    {
        current_switch = "Switch 1";
        gtk_switch_set_active(GTK_SWITCH(switch1), TRUE);
    }
    // for dark.txt
    else if (file_exists(dark_path_theme))
    {
        current_switch = "Switch 2";
        gtk_switch_set_active(GTK_SWITCH(switch2), TRUE);
    }
    // no config files
    else
    {
        current_switch = "Switch 3";
        gtk_switch_set_active(GTK_SWITCH(switch3), TRUE);
    }
}

// function to update the config files
void update_config_files(const char *active_switch)
{
    // auto theme (css + adw)
    if (strcmp(active_switch, "Switch 1") == 0)
    {
        g_file_set_contents(AUTO_FILE, "", -1, NULL);
        remove(DARK_FILE);
    }
    // css only (dark)
    else if (strcmp(active_switch, "Switch 2") == 0)
    {
        g_file_set_contents(DARK_FILE, "", -1, NULL);
        remove(AUTO_FILE);
    }
    // css only (light)
    else if (strcmp(active_switch, "Switch 3") == 0)
    {
        remove(AUTO_FILE);
        remove(DARK_FILE);
    }
}

// callback for the first switch
// css + adw
void switch1_action()
{
    apply_theme_css_adw();
    LOG_INFO("Theme mode: css_adw");
}

// callback for the second switch
// css only (dark)
void switch2_action()
{
    current_theme = "dark";
    write_dark_file(); // Assuming this saves the theme state
    // Reload the theme
    load_css(current_theme);
    LOG_INFO("Theme mode: css_only (dark)");
}

// callback for the third switch
// css only (light)
void switch3_action()
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
        if (widget != GTK_SWITCH(css_adw_switch))
            gtk_switch_set_active(GTK_SWITCH(css_adw_switch), FALSE);
		// S2
        if (widget != GTK_SWITCH(css_dark_switch))
            gtk_switch_set_active(GTK_SWITCH(css_dark_switch), FALSE);
		// S3
        if (widget != GTK_SWITCH(css_light_switch))
            gtk_switch_set_active(GTK_SWITCH(css_light_switch), FALSE);

        // save the active switch
        current_switch = g_strdup(switch_name);

        // update the config files
        update_config_files(current_switch);
			
        LOG_INFO("active switch: %s", current_switch);
        
        // start the function based on the active switch
        // S1
        if (strcmp(current_switch, "Switch 1") == 0)
            switch1_action();
        // S2
        else if (strcmp(current_switch, "Switch 2") == 0)
            switch2_action();
        // S3
        else if (strcmp(current_switch, "Switch 3") == 0)
            switch3_action();
    }
    
    LOG_INFO("%s is now %s.", switch_name, gtk_switch_get_active(GTK_SWITCH(widget)) ? "ON" : "OFF");
}

/* function that switch themes → css_only / css_adw */
void toggle_theme(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("toggle_theme");
	
	apply_language();
    
    // create box for get_devices
    GtkWidget *toggle_theme = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(toggle_theme, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(toggle_theme, GTK_ALIGN_CENTER);
    
    // create the switches
    css_adw_switch = gtk_switch_new();  
    gtk_switch_set_active(GTK_SWITCH(css_adw_switch), TRUE); // active by standard
    
    css_dark_switch = gtk_switch_new();
    gtk_switch_set_active(GTK_SWITCH(css_dark_switch), FALSE);
    
    css_light_switch = gtk_switch_new();
    gtk_switch_set_active(GTK_SWITCH(css_light_switch), FALSE);

    // create the labels for the switches
    GtkWidget *css_adw_label = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Automatisches Thema" : "Automatic theme");
    GtkWidget *css_dark_label = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Manuelles Thema (Dunkel)" : "Manual theme (dark)");
    GtkWidget *css_light_label = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Manuelles Thema (Hell)": "Manual theme (light)");

    // add the switches and the label to the box
    // S1
    gtk_box_append(GTK_BOX(toggle_theme), css_adw_label);
    gtk_box_append(GTK_BOX(toggle_theme), css_adw_switch);
    // S2    
    gtk_box_append(GTK_BOX(toggle_theme), css_dark_label);
    gtk_box_append(GTK_BOX(toggle_theme), css_dark_switch);
    // S3    
    gtk_box_append(GTK_BOX(toggle_theme), css_light_label);
    gtk_box_append(GTK_BOX(toggle_theme), css_light_switch);
        
    // set alignment and expansion for the switches and labels
    gtk_widget_set_halign(css_adw_switch, GTK_ALIGN_CENTER); 
    gtk_widget_set_halign(css_dark_switch, GTK_ALIGN_CENTER); 
    gtk_widget_set_halign(css_light_switch, GTK_ALIGN_CENTER);  
        
    gtk_widget_set_valign(css_adw_switch, GTK_ALIGN_CENTER);  
    gtk_widget_set_valign(css_dark_switch, GTK_ALIGN_CENTER); 
    gtk_widget_set_valign(css_light_switch, GTK_ALIGN_CENTER);   

    gtk_widget_set_hexpand(css_adw_switch, TRUE); 
    gtk_widget_set_hexpand(css_dark_switch, TRUE);
    gtk_widget_set_hexpand(css_light_switch, TRUE);

    gtk_widget_set_vexpand(css_adw_switch, TRUE);
    gtk_widget_set_vexpand(css_dark_switch, TRUE);
    gtk_widget_set_vexpand(css_light_switch, TRUE);

    // connect the switches
    g_signal_connect(css_adw_switch, "notify::active", G_CALLBACK(switch_toggled), "Switch 1");
    g_signal_connect(css_dark_switch, "notify::active", G_CALLBACK(switch_toggled), "Switch 2");
    g_signal_connect(css_light_switch, "notify::active", G_CALLBACK(switch_toggled), "Switch 3");
	
    // set the current switch
    set_current_switch();
    
    // function to show the home page
	back_to_home = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Zurück zur Startseite" : "Back to Home");
	gtk_box_append(GTK_BOX(toggle_theme), back_to_home);
	g_signal_connect(back_to_home, "clicked", G_CALLBACK(show_home_page), stack);
    
	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "toggle_theme")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), toggle_theme, "toggle_theme");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "toggle_theme");
	
	LOG_INFO("end toggle_theme");
}
