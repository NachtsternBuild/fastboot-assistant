/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das Installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_data				 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the program */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"
#include "flash_function_header.h"

// Button handler functions
// function to flash metadata.img
void metadata_img(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "metadata", NULL, "metadata.img", NULL);
}

// function to flash metadata.img (heimdall)
void metadata_img_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "METADATA", "metadata.img");
}

// function to flash userdata.img
void userdata_img(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "userdata", NULL, "userdata.img", NULL);
}

// function to flash userdata.img (heimdall)
void userdata_img_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "userdata", "userdata.img");
}

// Function to set up button labels based on the language
void set_button_labels_flash_data(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Metadata");
        strcpy(labels[1], "Metadata (heimdall)");
        strcpy(labels[2], "Userdata");
        strcpy(labels[3], "Userdata (heimdall)");
    } 
    
    else 
    {
        strcpy(labels[0], "Metadata");
        strcpy(labels[1], "Metadata (heimdall");
        strcpy(labels[2], "Userdata");
        strcpy(labels[3], "Userdata (heimdall)");
    }
}

/* main function - flash_data */
void flash_data(int argc, char *argv[])
{
	LOG_INFO("flash_data");
	GtkWidget *window, *grid, *button;
    char button_labels[4][30];
    
    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_flash_data(button_labels);
    
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

    for (int i = 0; i < 4; i++) 
    {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 2, i / 2, 1, 1);
        
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(metadata_img), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(metadata_img_heimdall), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(userdata_img), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(userdata_img_heimdall), NULL);
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
    
    LOG_INFO("end flash_data");
}
