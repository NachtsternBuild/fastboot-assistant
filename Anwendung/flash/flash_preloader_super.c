/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_preloader_super	 *
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
#include "flash_function_header.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

// Button handler functions
// function to flash preloader.bin on only-a-devices
void preloader_bin_on_a(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "preloader", NULL, "preloader.bin");
}

// function to flash preloader.bin (a/b-devices)
void preloader_bin_on_ab(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "preloader_a", "preloader_b", "preloader.bin");
}

// function to flash preloader.img (only-a-devices)
void preloader_img_on_a(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "preloader", NULL, "preloader.img");
}

// function to flash preloader.img (a/b-devices)
void preloader_img_on_ab(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "preloader_a", "preloader_b", "preloader.img");
}

// function to flash super.img
void super_img(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "super", NULL, "super.img");
}

// function to flash preloader.bin (heimdall)
void preloader_bin_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "PRELOADER", "preloader.bin");
}

// function to flash preloader.img (heimdall)
void preloader_img_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "PRELOADER", "preloader.img");
}

// function to flash super.img (heimdall)
void super_img_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "SUPER", "super.img");
}

// main function
void flash_preloader_super(int argc, char *argv[])
{
	GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[9][30] = {"preloader.bin (only-a)", "preloader.bin (a/b)", "preloader.img (only-a)", "preloader.img (a/b)", 
                                 "preloader.bin (heimdall)", "preloader.img (heimdall)", "super.img", "super.img (heimdall)"};

    gtk_init(&argc, &argv);
    css_provider(); // load css-provider

    // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Flash:");
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
    for (int i = 0; i < 8; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 2, i / 2, 1, 1);

        // execute css-provider for all buttons
        add_css_provider(button, provider);

        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(preloader_bin_on_a), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(preloader_bin_on_ab), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(preloader_img_on_a), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(preloader_img_on_ab), NULL);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(preloader_bin_heimdall), NULL);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(preloader_img_heimdall), NULL);
                break;
            case 6:
            	g_signal_connect(button, "clicked", G_CALLBACK(super_img), NULL);
            	break;
            case 7:
            	g_signal_connect(button, "clicked", G_CALLBACK(super_img_heimdall), NULL);
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
