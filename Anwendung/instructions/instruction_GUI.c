/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_GUI		 *
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
#include "instruction_header.h"

#define MAX_BUFFER_SIZE 256
// include all functions
extern void instruction_adb();
extern void instruction_flash();
extern void instruction_prepare_flash();
extern void instruction_info();

// Callback functions for each button
// start instruction_adb-function
static void start_instruction_adb(GtkWidget *widget, gpointer data) 
{
    instruction_adb();
}

// start instruction_flash-function
static void start_instruction_flash(GtkWidget *widget, gpointer data) 
{
    instruction_flash();
}

// start instruction_prepare_flash-function
static void start_instruction_prepare_flash(GtkWidget *widget, gpointer data) 
{
    instruction_prepare_flash();
}

// function without any function
static void start_zero_function_3(GtkWidget *widget, gpointer data) 
{
    printf("Keine Funktion!\n");
}

// start instruction_info-function
static void start_instruction_info(GtkWidget *widget, gpointer data) 
{
    instruction_info();
}

// function without any function
static void start_zero_function_4(GtkWidget *widget, gpointer data) 
{
    printf("Keine Funktion!\n");
}

/* main function of flash_GUI*/
void instruction_GUI(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[6][20] = {"Umgang mit ADB", "Flashen von Systemabbildern", "Vorbereitungen", 
                                 " ", "Info", " "};

    gtk_init(&argc, &argv);

    // create new windows
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Anleitungen");
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
                g_signal_connect(button, "clicked", G_CALLBACK(start_instruction_adb), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_instruction_flash), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(start_instruction_prepare_flash), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(start_zero_function_3), NULL);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(start_instruction_info), NULL);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(start_zero_function_4), NULL);
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

