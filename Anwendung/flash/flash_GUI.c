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
 *      (C) Copyright 2024 Elias Mörz 		 *
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
    char button_labels[9][30] = {"Flash Recovery", "Flash Boot", "Flash Vendor", 
                                 "Flash payload.zip", "Flash System", "Flash vbmeta/dtbo",
                                 "Flash Preloader", "Flash Nutzerdaten", "Flash Andere Images"};

    gtk_init(&argc, &argv);
    css_provider(); // load css-provider

    // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Fastboot-Assistant - Flash");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
    // create the grid and centre it
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    // add the grid to the window
    gtk_container_add(GTK_CONTAINER(window), grid);

    // add and centre all button
    for (int i = 0; i < 9; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);

        // execute css-provider for all buttons
        add_css_provider(button, provider);

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
    // cleaning the provider
    g_object_unref(provider);

    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();
}

