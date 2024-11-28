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
#include "language_check.h"
#include "program_functions.h"
#include "flash_function_header.h"

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

// Function to set up button labels based on the language
void set_button_labels_flash_preloader_super(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "preloader.bin (only-a)");
        strcpy(labels[1], "preloader.bin (a/b)");
        strcpy(labels[2], "preloader.img (only-a)");
        strcpy(labels[3], "preloader.img (a/b)");
        strcpy(labels[4], "preloader.bin (heimdall)");
        strcpy(labels[5], "preloader.img (heimdall)");
        strcpy(labels[6], "super.img");
        strcpy(labels[7], "super.img (heimdall)");
    } 
    
    else 
    {
        strcpy(labels[0], "preloader.bin (only-a)");
        strcpy(labels[1], "preloader.bin (a/b)");
        strcpy(labels[2], "preloader.img (only-a)");
        strcpy(labels[3], "preloader.img (a/b)");
        strcpy(labels[4], "preloader.bin (heimdall)");
        strcpy(labels[5], "preloader.img (heimdall)");
        strcpy(labels[6], "super.img");
        strcpy(labels[7], "super.img (heimdall)");
    }
}

/* main function - flash_preloader_super */
void flash_preloader_super(int argc, char *argv[])
{
	g_print("Log: flash_preloader_super\n");
	GtkWidget *window, *grid, *button;
    char button_labels[8][30];
    
    gtk_init();
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_flash_preloader_super(button_labels);
    
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Flashen:");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);
    
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), grid);
    
    for (int i = 0; i < 8; i++) 
    {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 4, i / 4, 1, 1);
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
    
    // free the provider
	if (provider != NULL) 
	{
	    g_object_unref(provider);
	}
	
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop); 
    
    g_print("Log: end flash_preloader_super\n");
}
