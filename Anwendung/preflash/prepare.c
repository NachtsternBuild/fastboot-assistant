/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - prepare				 *
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
#include "language_check.h"
#include "program_functions.h"
#include "function_header.h"
#include "file_chooser_header.h"
#include "flash_function_header.h"

#define MAX_BUFFER_SIZE 256

// Function to set up button labels based on the language
void set_button_labels_prepare(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Boot.img");
        strcpy(labels[1], "Recovery.img");
        strcpy(labels[0], "Vendor.img");
        strcpy(labels[1], "System.img");
        strcpy(labels[0], "payload.zip");
        strcpy(labels[1], "Decompress (xz)");
    } 
    
    else 
    {
        strcpy(labels[0], "Boot.img");
        strcpy(labels[1], "Recovery.img");
        strcpy(labels[0], "Vendor.img");
        strcpy(labels[1], "System.img");
        strcpy(labels[0], "payload.zip");
        strcpy(labels[1], "Dekomprimieren (xz)");
    }
}

// Callback functions for each button
/* main function of prepare*/
void prepare(int argc, char *argv[]) 
{
    g_print("Log: prepare\n");
    GtkWidget *window, *grid, *button;
    char button_labels[6][30];
    
    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_prepare(button_labels);
    
    window = gtk_window_new();
    const char *prepare_window = strcmp(language, "de") == 0 ? "Vorbereiten:" : "Prepare:";
    gtk_window_set_title(GTK_WINDOW(window), prepare_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);
    
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), grid);
    
    for (int i = 0; i < 6; i++) 
    {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);
        
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(show_file_chooser), (gpointer)rename_boot);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(show_file_chooser), (gpointer)rename_recovery);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(show_file_chooser), (gpointer)rename_vendor);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(show_file_chooser), (gpointer)rename_system);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(show_file_chooser), (gpointer)rename_payload);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(show_file_chooser), (gpointer)unxz_files);
                break;            
        }
    }
    
     // free the provider
	if (provider != NULL) 
	{
	    g_object_unref(provider);
	    provider = NULL;
	}
	
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop); 
    
    g_print("Log: end prepare\n");
}
