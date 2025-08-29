/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - toggle_language	 	 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"
#include "function_header.h"

// config file
#define LANGUAGE_FILE "language.txt"

GtkWidget *en_switch, *de_switch, *ru_switch, *es_switch, *pt_switch, *fr_switch, *back_to_home;
static char *current_lang = NULL;
static char lang_path[1024];

// get the path of the language file
char *get_lang_path()
{
    get_config_dir(lang_path, sizeof(lang_path));
    snprintf(lang_path, sizeof(lang_path), "%s/%s", lang_path, LANGUAGE_FILE);
    return lang_path;
}

// function that get the current language
gchar *get_current_language()
{
    gchar *content = NULL;
    if (!g_file_get_contents(get_lang_path(), &content, NULL, NULL) || !content) 
    {
        // fallback to english
        content = g_strdup("en");
    }
    // trim newline
    if (content) 
    {
        content[strcspn(content, "\n")] = '\0';
    }
    return content;
}

// read the content from the language file and set based on this the active switch
static void set_current_switch_language()
{
    gchar *content = NULL;
	
	// read the content from the language file
    if (g_file_get_contents(get_lang_path(), &content, NULL, NULL))
    {
        // en
        if (g_strcmp0(content, "en") == 0) 
        {
            current_lang = "en";
            gtk_switch_set_active(GTK_SWITCH(en_switch), TRUE);
        } 
        
        // de
        else if (g_strcmp0(content, "de") == 0) 
        {
            current_lang = "de";
            gtk_switch_set_active(GTK_SWITCH(de_switch), TRUE);
        } 
        
        // ru
        else if (g_strcmp0(content, "ru") == 0) 
        {
            current_lang = "ru";
            gtk_switch_set_active(GTK_SWITCH(ru_switch), TRUE);
        } 
        void toggle_language(GtkWidget *widget, gpointer stack)
        // es
        else if (g_strcmp0(content, "es") == 0) 
        {
            current_lang = "es";
            gtk_switch_set_active(GTK_SWITCH(es_switch), TRUE);
        } 
        
        // pt
        else if (g_strcmp0(content, "pt") == 0) 
        {
            current_lang = "pt";
            gtk_switch_set_active(GTK_SWITCH(pt_switch), TRUE);
        } 
        
        // fr
        else if (g_strcmp0(content, "fr") == 0) 
        {
            current_lang = "fr";
            gtk_switch_set_active(GTK_SWITCH(fr_switch), TRUE);
        }
        // free the content
        g_free(content);
    }
    else
    {
        // use en as fallback
        current_lang = "en";
        gtk_switch_set_active(GTK_SWITCH(en_switch), TRUE);
        set_language("en");
    }
}

// the callback of the toggles
static void switch_toggled_language(GtkSwitch *widget, GParamSpec *pspec, gpointer user_data)
{
    const char *lang_code = (const char *) user_data;
	
	// disable the other switches
    if (gtk_switch_get_active(widget))
    {
        // en
        if (widget != GTK_SWITCH(en_switch)) 
        {
        	gtk_switch_set_active(GTK_SWITCH(en_switch), FALSE);
        }
        // de
        if (widget != GTK_SWITCH(de_switch)) 
        {
        	gtk_switch_set_active(GTK_SWITCH(de_switch), FALSE);
        }
        // ru
        if (widget != GTK_SWITCH(ru_switch)) 
        {
        	gtk_switch_set_active(GTK_SWITCH(ru_switch), FALSE);
        }
        // es
        if (widget != GTK_SWITCH(es_switch)) 
        {
        	gtk_switch_set_active(GTK_SWITCH(es_switch), FALSE);
        }
        // pt
        if (widget != GTK_SWITCH(pt_switch)) 
        {
        	gtk_switch_set_active(GTK_SWITCH(pt_switch), FALSE);
        }
        // fr
        if (widget != GTK_SWITCH(fr_switch)) 
        {
        	gtk_switch_set_active(GTK_SWITCH(fr_switch), FALSE);
		}
		
        // save the current language
        current_lang = g_strdup(lang_code);

        // set the current language
        set_language(current_lang);

        LOG_INFO("Language switched to: %s", current_lang);
    }
}


/* function that switch the language */
void toggle_language(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("toggle_language");

    // create box for get_devices
    GtkWidget *toggle_language = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(toggle_language, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(toggle_language, GTK_ALIGN_CENTER);

    // create the switches
    en_switch = gtk_switch_new();
    de_switch = gtk_switch_new();
    ru_switch = gtk_switch_new();
    es_switch = gtk_switch_new();
    pt_switch = gtk_switch_new();
    fr_switch = gtk_switch_new();

    // create the labels
    GtkWidget *en_label = gtk_label_new("English");
    GtkWidget *de_label = gtk_label_new("Deutsch");
    GtkWidget *ru_label = gtk_label_new("Русский");
    GtkWidget *es_label = gtk_label_new("Español");
    GtkWidget *pt_label = gtk_label_new("Português");
    GtkWidget *fr_label = gtk_label_new("Français");

    // add the switches/labels to the box
    // en
    gtk_box_append(GTK_BOX(toggle_language), en_label);
    gtk_box_append(GTK_BOX(toggle_language), en_switch);
    // de
    gtk_box_append(GTK_BOX(toggle_language), de_label);
    gtk_box_append(GTK_BOX(toggle_language), de_switch);
    // ru
    gtk_box_append(GTK_BOX(toggle_language), ru_label);
    gtk_box_append(GTK_BOX(toggle_language), ru_switch);
    // es
    gtk_box_append(GTK_BOX(toggle_language), es_label);
    gtk_box_append(GTK_BOX(toggle_language), es_switch);
    // pt
    gtk_box_append(GTK_BOX(toggle_language), pt_label);
    gtk_box_append(GTK_BOX(toggle_language), pt_switch);
    // fr
    gtk_box_append(GTK_BOX(toggle_language), fr_label);
    gtk_box_append(GTK_BOX(toggle_language), fr_switch);
	
	// set alignment and expansion for the switches and labels
    gtk_widget_set_halign(en_switch, GTK_ALIGN_CENTER); 
    gtk_widget_set_halign(de_switch, GTK_ALIGN_CENTER); 
    gtk_widget_set_halign(ru_switch, GTK_ALIGN_CENTER); 
    gtk_widget_set_halign(es_switch, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(pt_switch, GTK_ALIGN_CENTER); 
    gtk_widget_set_halign(fr_switch, GTK_ALIGN_CENTER);   
    
    gtk_widget_set_valign(en_switch, GTK_ALIGN_CENTER);    
    gtk_widget_set_valign(de_switch, GTK_ALIGN_CENTER);  
    gtk_widget_set_valign(ru_switch, GTK_ALIGN_CENTER); 
    gtk_widget_set_valign(es_switch, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(pt_switch, GTK_ALIGN_CENTER); 
    gtk_widget_set_valign(fr_switch, GTK_ALIGN_CENTER);   
	
	gtk_widget_set_hexpand(en_switch, TRUE); 
    gtk_widget_set_hexpand(de_switch, TRUE); 
    gtk_widget_set_hexpand(ru_switch, TRUE);
    gtk_widget_set_hexpand(es_switch, TRUE);
    gtk_widget_set_hexpand(pt_switch, TRUE);
    gtk_widget_set_hexpand(fr_switch, TRUE);
	
	gtk_widget_set_vexpand(en_switch, TRUE);
    gtk_widget_set_vexpand(de_switch, TRUE);
    gtk_widget_set_vexpand(ru_switch, TRUE);
    gtk_widget_set_vexpand(es_switch, TRUE);
    gtk_widget_set_vexpand(pt_switch, TRUE);
    gtk_widget_set_vexpand(fr_switch, TRUE);
	
	// connect the switches
    g_signal_connect(en_switch, "notify::active", G_CALLBACK(switch_toggled_language), "en");
    g_signal_connect(de_switch, "notify::active", G_CALLBACK(switch_toggled_language), "de");
    g_signal_connect(ru_switch, "notify::active", G_CALLBACK(switch_toggled_language), "ru");
    g_signal_connect(es_switch, "notify::active", G_CALLBACK(switch_toggled_language), "es");
    g_signal_connect(pt_switch, "notify::active", G_CALLBACK(switch_toggled_language), "pt");
    g_signal_connect(fr_switch, "notify::active", G_CALLBACK(switch_toggled_language), "fr");

    // set the current language
    set_current_switch_language();
	
    // function to show the home page
    const char *back_to_home_char = _("Back to Home");
    back_to_home = create_icon_nav_button_with_position("pan-start-symbolic", back_to_home_char, G_CALLBACK(show_home_page), stack, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(toggle_language), back_to_home);

    // is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "toggle_language"))
    {
        gtk_stack_add_named(GTK_STACK(stack), toggle_language, "toggle_language");
    }
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "toggle_language");

    LOG_INFO("end toggle_language");
}
