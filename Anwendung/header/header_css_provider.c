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
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              Headerpart - css_provider	 *
 *											 *
 *-------------------------------------------*
 */

/* headers */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <unistd.h>  // Für getcwd()
#include <sys/stat.h> // Für mkdir
#include <sys/types.h> // Für mkdir
#include "program_functions.h"

#define CONFIG_DIR "~/Downloads/ROM-Install/config"
#define CONFIG_FILE "dark.txt"

GtkCssProvider *provider = NULL;
GtkCssProvider *darkblue_provider = NULL;
const char *current_theme = "light";
// function that create the dark.txt
// thanks to my book for programming for linux
void create_directory_if_not_exists(const char *path) 
{
    char expanded_path[512];
    snprintf(expanded_path, sizeof(expanded_path), "%s", path);
    char *home = getenv("HOME");
    if (home != NULL) 
    {
        // Ersetze ~ durch den absoluten Pfad des Home-Verzeichnisses
        char *tilde_pos = strchr(expanded_path, '~');
        if (tilde_pos != NULL) 
        {
            memmove(expanded_path + strlen(home), tilde_pos + 1, strlen(tilde_pos));
            memcpy(expanded_path, home, strlen(home));
        }
    }

    struct stat st = {0};
    if (stat(expanded_path, &st) == -1) 
    {
        if (mkdir(expanded_path, 0700) == -1) 
        {
            perror("Fehler beim Erstellen des Verzeichnisses");
            exit(EXIT_FAILURE);
        }
    }
}

// Funktion zum Schreiben in die Datei dark.txt
// thanks to my book for programming for linux
void write_dark_file() 
{
    // Ersetze ~ durch den absoluten Pfad des Home-Verzeichnisses
    char *home = getenv("HOME");
    if (home == NULL) 
    {
        perror("Fehler beim Abrufen des Home-Verzeichnisses");
        exit(EXIT_FAILURE);
    }

    char dir_path[512];
    snprintf(dir_path, sizeof(dir_path), "%s/Downloads/ROM-Install/config", home);
    
    // Erstelle das Verzeichnis, falls es nicht existiert
    create_directory_if_not_exists(dir_path);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, CONFIG_FILE);

    FILE *file = fopen(path, "w");
    if (file == NULL) 
    {
        perror("Fehler beim Öffnen der Datei zum Schreiben");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "dunkel");
    fclose(file);
    printf("In die Datei '%s' geschrieben.\n", path);
}

// Funktion zum Überprüfen der Datei und Ausgabe
void check_dark_file() 
{
    // Ersetze ~ durch den absoluten Pfad des Home-Verzeichnisses
    char *home = getenv("HOME");
    if (home == NULL) 
    {
        perror("Fehler beim Abrufen des Home-Verzeichnisses");
        exit(EXIT_FAILURE);
    }

    char dir_path[512];
    snprintf(dir_path, sizeof(dir_path), "%s/Downloads/ROM-Install/config", home);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, CONFIG_FILE);

    FILE *file = fopen(path, "r");
    if (file != NULL) 
    {
        g_print("Dunkelheit\n");
        current_theme = "dark";
        fclose(file);
    }
     
    else 
    {
        g_print("Tag\n");
    }
}

void load_css(const char *theme) 
{
    // Create a new CSS provider if it doesn't exist
    if (!provider) 
    {
        provider = gtk_css_provider_new();
    }

    // Define CSS for the light theme, without universal selectors
    //"    background-color: #8B0000;"
    const char *light_css =
        "button {"
        "    border: 2px solid #8B0000;"
        "    border-radius: 15px;"
        "    padding: 12px 24px;"
        "    color: #ffffff;"
        "    font-size: 16px;"
        "    font-weight: 500;"
        "    text-align: center;"
        "}"
        "button:hover {"
        "    background-color: #A52A2A;"
        "    box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);"
        "}"
        "label {"
        "    color: #000000;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}";

    // Define CSS for the dark theme
    // "    background-color: #8B0000;"
    const char *dark_css =
        "button {"
        "    border: 2px solid #8B0000;"
        "    border-radius: 15px;"
        "    padding: 24px 48px;"
        "    color: #ffffff;"
        "    font-size: 16px;"
        "    font-weight: 500;"
        "    text-align: center;"
        "}"
        "button:hover {"
        "    background-color: #A52A2A;"
        "    box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);"
        "}"
        "label {"
        "    color: #FFFFFF;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}";

    // Load the appropriate CSS based on the selected theme
    if (strcmp(theme, "dark") == 0) 
    {
        gtk_css_provider_load_from_data(provider, dark_css, -1, NULL);
    } 
    else 
    {
        gtk_css_provider_load_from_data(provider, light_css, -1, NULL);
    }

    // Apply the CSS provider to the entire screen but only to user-defined styles
    GtkStyleContext *context = gtk_style_context_new();
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    g_object_unref(context);  // Free the context when done
}

void load_css_blue(const char *theme) 
{
    // Create a new CSS provider if it doesn't exist
    if (!darkblue_provider) 
    {
        darkblue_provider = gtk_css_provider_new();
    }

    // Define CSS for the light theme, without universal selectors
    //"    background-color: #00008B;"
    const char *light_css =
        "button {"
        "    border: 2px solid #00008B;"
        "    border-radius: 15px;"
        "    padding: 24px 48px;"
        "    color: #ffffff;"
        "    font-size: 16px;"
        "    font-weight: 500;"
        "    text-align: center;"
        "}"
        "button:hover {"
        "    background-color: #A52A2A;"
        "    box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);"
        "}"
        "label {"
        "    color: #000000;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}";

    // Define CSS for the dark theme
    // "    background-color: #00008B;"
    const char *dark_css =
        "button {"
        "    border: 2px solid #00008B;"
        "    border-radius: 15px;"
        "    padding: 24px 48px;"
        "    color: #ffffff;"
        "    font-size: 16px;"
        "    font-weight: 500;"
        "    text-align: center;"
        "}"
        "button:hover {"
        "    background-color: #A52A2A;"
        "    box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);"
        "}"
        "label {"
        "    color: #FFFFFF;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}";

    // Load the appropriate CSS based on the selected theme
    if (strcmp(theme, "dark") == 0) 
    {
        gtk_css_provider_load_from_data(darkblue_provider, dark_css, -1, NULL);
    } 
    else 
    {
        gtk_css_provider_load_from_data(darkblue_provider, light_css, -1, NULL);
    }

    // Apply the CSS provider to the entire screen but only to user-defined styles
    GtkStyleContext *context = gtk_style_context_new();
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(darkblue_provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    g_object_unref(context);  // Free the context when done
}

// callback to switch the theme
void toggle_theme(GtkWidget *button, gpointer user_data) 
{
    // change the theme
    // dark
    if (strcmp(current_theme, "light") == 0) 
    {
        current_theme = "dark";
        write_dark_file();
    } 
    
    // light
    else 
    {
        current_theme = "light";
    }

    // run the theme
    load_css(current_theme);
}

// Apply the current theme when called
void apply_theme() 
{
    check_dark_file();
    load_css(current_theme);
}

// Apply the blue theme when called
void apply_theme_blue() 
{
    check_dark_file();
    load_css_blue(current_theme);
}


// load the css provider (main)
void add_css_provider(GtkWidget *widget, GtkCssProvider *provider) 
{
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

// load the css provider (darkblue)
void add_css_provider_blue(GtkWidget *widget, GtkCssProvider *darkblue_provider) 
{
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(darkblue_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}
// darkblue #00008B
