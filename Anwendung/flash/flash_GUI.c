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
#include "language_check.h"
#include "program_functions.h"
#include "function_header.h"
#include "flash_function_header.h"
#include "loading_spinner.h"

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

// start flash_others
static void start_flash_others(GtkWidget *widget, gpointer data)
{
	flash_others();
}

// Function to set up button labels based on the language
void set_button_labels_flash_GUI(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Flash Recovery");
        strcpy(labels[1], "Flash Boot");
        strcpy(labels[2], "Flash Vendor");
        strcpy(labels[3], "Flash payload.zip");
        strcpy(labels[4], "Flash System");
        strcpy(labels[5], "Flash vbmeta/dtbo");
        strcpy(labels[6], "Flash Preloader");
        strcpy(labels[7], "Flash Nutzerdaten");
        strcpy(labels[8], "Flash Other Images");
    } 
    
    else 
    {
        strcpy(labels[0], "Flash Recovery");
        strcpy(labels[1], "Flash Boot");
        strcpy(labels[2], "Flash Vendor");
        strcpy(labels[3], "Flash payload.zip");
        strcpy(labels[4], "Flash System");
        strcpy(labels[5], "Flash vbmeta/dtbo");
        strcpy(labels[6], "Flash Preloader");
        strcpy(labels[7], "Flash Nutzerdaten");
        strcpy(labels[8], "Flash Andere Images");
    }
}


/* main function - flash_GUI*/
void flash_GUI(int argc, char *argv[]) 
{
    g_print("Log: flash_GUI\n");
    GtkWidget *window, *grid, *button;
    char button_labels[9][30];
    
    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_flash_GUI(button_labels);
    
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Flashen");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);
    
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), grid);
    
    for (int i = 0; i < 9; i++) 
    {
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
	
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop); 
	
	// free the provider
    if (provider != NULL) 
    {
    	g_object_unref(provider);
    	provider = NULL;
	}

	if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
    
    g_print("Log: end flash_GUI\n");
}
