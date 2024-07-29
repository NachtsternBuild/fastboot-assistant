/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - preflash_GUI			 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "function_header.h"

#define MAX_BUFFER_SIZE 256
// include all functions
extern void backup_function();
extern void prepare_function();
extern void erase_data();
extern void lock_unlock_bootloader();
extern void set_active_slot();

// Callback functions for each button
// start backup_function-function
static void start_backup_function(GtkWidget *widget, gpointer data) 
{
    backup_function();
}

// start start_prepare-function
static void start_prepare_function(GtkWidget *widget, gpointer data) 
{
    prepare_function();
}

// start erase_data-function
static void start_erase_data(GtkWidget *widget, gpointer data) 
{
    erase_data();
}

// function without any function
static void start_set_active_slot(GtkWidget *widget, gpointer data) 
{
    set_active_slot();
}

// start lock_unlock_bootloader-function
static void start_lock_unlock_bootloader(GtkWidget *widget, gpointer data) 
{
    lock_unlock_bootloader();
}

// function without any function
static void start_zero_function_6(GtkWidget *widget, gpointer data) 
{
    printf("Keine Funktion!\n");
}

/* main function of preflash_GUI*/
void preflash_GUI(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[6][20] = {"Backup", "Dateien vorbereiten", "Lösche Nutzerdaten", 
                                 "Setzen des aktiven Slots", "Lock/Unlock Bootloader", " "};

    gtk_init(&argc, &argv);

    // create new windows
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Vorbereitung");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // create a grid
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // add buttons and connect them with callback
    for (int i = 0; i < 6; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(start_backup_function), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_prepare_function), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(start_erase_data), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(start_set_active_slot), NULL);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(start_lock_unlock_bootloader), NULL);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(start_zero_function_6), NULL);
                break;
        }
    }

    /* change the style of the buttons to quick settings buttons from android 12 - css is used for this*/
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "button {\n"
                                    "    background-color: #8B0000;\n" /* darkred */
            						"	 border: none;\n"
            						"	 border-radius: 12px;\n" /* round corners */
            						"	 padding: 12px 24px;\n" /* inside distance */
            						"	 color: #ffffff;\n" /* White text */
            						"	 font-size: 16px;\n" /* Font size */
            						"	 font-weight: 500;\n" /* Medium font */
            						"	 text-align: center;\n" /* Centre text */
            						"	 box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);\n" /* Light shade */
            						"	 transition: background-color 0.3s ease, box-shadow 0.3s ease;\n" /* Animation */
                                    "}\n"
                                    "button:hover {\n"
                                    "    background-color: #A52A2A;\n" /* Brighter red on hover */
            						"	 box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);\n" /* Amplify shadows */
                                    "}\n",
                                    -1,
                                    NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);

    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();
}

