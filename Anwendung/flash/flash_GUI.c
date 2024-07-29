/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_GUI				 *
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
#include "flash_function_header.h"

#define MAX_BUFFER_SIZE 256
// includde all functions
extern void flash_recovery();
extern void flash_boot();
extern void flash_vendor();
extern void flash_payload();
extern void flash_system();
extern void flash_vbmeta_dtbo();
extern void flash_preloader();
extern void flash_data();
extern void flash_others();

// Callback functions for each button
// start recovery_flash-function
static void start_recovery_flash(GtkWidget *widget, gpointer data) 
{
    flash_recovery();
}

// start flash_boot-function
static void start_boot_flash(GtkWidget *widget, gpointer data) 
{
    flash_boot();
}

// start flash_vendor-function
static void start_vendor_flash(GtkWidget *widget, gpointer data) 
{
    flash_vendor();
}

// start flash_payload-function
static void start_payload_flash(GtkWidget *widget, gpointer data) 
{
    flash_payload();
}

// start flash_system-function
static void start_system_flash(GtkWidget *widget, gpointer data) 
{
    flash_system();
}

// start flash_vbemta_dtbo-function
static void start_vbmeta_dtbo_flash(GtkWidget *widget, gpointer data) 
{
    flash_vbmeta_dtbo();
}

// start flash_preloader-function
static void start_flash_preloader(GtkWidget *widget, gpointer data)
{
	flash_preloader_super();
}

// start flash_preloader-function
static void start_flash_data(GtkWidget *widget, gpointer data)
{
	flash_data();
}

//no function
static void start_flash_others(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
    const char *message;
    message = "Der Prozess kann eine Weile dauern. \nIgnorien sie alle beenden erzwingen Meldungen.\n";
    show_message(message);
    
	flash_other();
	
	message = "Prozess beendet.\n";
	show_message(message);	
}

/* main function of flash_GUI*/
// i hope it works
void flash_GUI(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[9][20] = {"Flash Recovery-Image", "Flash Boot-Image", "Flash Vendor-Image", 
                                 "Flash payload.zip", "Flash System-Image", "Flash vbmeta.img/dtbo.img",
                                 "Flashen des Bootloaders", "Flashen der Nutzerdaten", "Flashen von anderen Images"};

    gtk_init(&argc, &argv);

    // create new windows
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Flash");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // create a grid
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // add buttons and connect them with callback
    for (int i = 0; i < 9; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(start_recovery_flash), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_boot_flash), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(start_vendor_flash), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(start_payload_flash), NULL);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(start_system_flash), NULL);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(start_vbmeta_dtbo_flash), NULL);
                break;
            case 6:
            	g_signal_connect(button, "clicked", G_CALLBACK(start_flash_preloader), NULL);
            	break;
            case 7:
            	g_signal_connect(button, "clicked", G_CALLBACK(start_flash_data), NULL);
            	break;
            case 8:
            	g_signal_connect(button, "clicked", G_CALLBACK(start_flash_others), NULL);
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

