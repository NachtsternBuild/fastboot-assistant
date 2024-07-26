/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - reboot_GUI				 *
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

// include all functions
extern void reboot_fastboot();
extern void reboot();
extern void reboot_recovery();
extern void reboot_heimdall();

// Callback functions for each button
// start reboot_fastboot-function
static void start_reboot_fastboot(GtkWidget *widget, gpointer data) 
{
    reboot_fastboot();
}

// start reboot-function
static void start_reboot(GtkWidget *widget, gpointer data) 
{
    reboot();
}

// start reboot_recovery-function
static void start_reboot_recovery(GtkWidget *widget, gpointer data) 
{
    reboot_recovery();
}

// start no function
static void start_no_function1(GtkWidget *widget, gpointer data) 
{
    printf("Nix zu sehen!\n");
}

// start reboot-function heimdall
static void start_reboot_heimdall(GtkWidget *widget, gpointer data) 
{
    reboot_heimdall();
}

// start no function
static void start_no_function2(GtkWidget *widget, gpointer data) 
{
    printf("Nix zu sehen!\n");
}

void reboot_GUI(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[6][20] = {"Neustart in Fastboot-Modus", "Neustart", "Neustart in Recovery", 
                                 " ", "Neustart Heimdall", " "};

    gtk_init(&argc, &argv);

    // create new windows
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Neustart");
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
                g_signal_connect(button, "clicked", G_CALLBACK(start_reboot_fastboot), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_reboot), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(start_reboot_recovery), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(start_no_function1), NULL);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(start_reboot_heimdall), NULL);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(start_no_function2), NULL);
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
            						"	 box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);\n" /* Amplify shadows */"
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

