/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_others			 *
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
#include "loading_spinner.h"
#include "program_functions.h"
#include "flash_function_header.h"

extern void flash_list_images();
extern void flash_images();

// start flash_list_images with spinner
static void start_flash_list(GtkWidget *widget, gpointer data)
{
    g_print("Log: start_flash_list\n");
	const char *message = strcmp(language, "de") == 0 ? "Der Prozess kann eine Weile dauern. \nIgnorieren sie alle beenden erzwingen Meldungen." : "“The process may take a while. \nIgnore them all end forcing messages.";
    show_message(message);
    
    GtkSpinner *spinner_flash = GTK_SPINNER(data);  // Get the spinner_backup from the callback data

    start_loading_spinner(spinner_flash);  // Start the spinner
    
	 // Run the backup process with a spinner in a separate thread
    run_with_spinner((void *)flash_list_images);
    
    stop_loading_spinner(spinner_flash);  // Stop the spinner when the process finishesflash_other();
	
	g_print("Log: end start_flash_list\n");
}

// start flash_images with spinner
static void start_flash_images_dir(GtkWidget *widget, gpointer data)
{
    g_print("Log: start_flash_images_dir\n");
	const char *message = strcmp(language, "de") == 0 ? "Der Prozess kann eine Weile dauern. \nIgnorieren sie alle beenden erzwingen Meldungen." : "“The process may take a while. \nIgnore them all end forcing messages.";
    show_message(message);
    
    GtkSpinner *spinner_flash = GTK_SPINNER(data);  // Get the spinner_backup from the callback data

    start_loading_spinner(spinner_flash);  // Start the spinner
    
	 // Run the backup process with a spinner in a separate thread
    run_with_spinner((void *)flash_images);
    
    stop_loading_spinner(spinner_flash);  // Stop the spinner when the process finishesflash_other();
	
	g_print("Log: end start_flash_images_dir\n");
}

// Function to set up button labels based on the language
void set_button_labels_flash_others(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Predefined images");
        strcpy(labels[1], "Images in the directory");
    } 
    
    else 
    {
        strcpy(labels[0], "Vorbestimmte Images");
        strcpy(labels[1], "Images im Verzeichnis");
    }
}

/* start main programm */
void flash_others(int argc, char *argv[])
{
    g_print("Log: flash_others\n");
    GtkWidget *window, *grid, *button;
    char button_labels[2][30];
    
    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_flash_others(button_labels);
    
    window = gtk_window_new();
    const char *others_window = strcmp(language, "de") == 0 ? "Andere Images" : "Other images";
    gtk_window_set_title(GTK_WINDOW(window), others_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);
    
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), grid);
    
    for (int i = 0; i < 2; i++) 
    {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 2, i / 2, 1, 1);
        
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(start_flash_list), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_flash_images_dir), NULL);
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
    
    if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
    
    g_print("Log: end flash_others\n");
}
