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
 *      (C) Copyright 2025 Elias Mörz 		 *
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

// start instruction_info-function
static void start_instruction_info(GtkWidget *widget, gpointer data) 
{
    instruction_info();
}

// Function to set up button labels based on the language
void set_button_labels_instruction_GUI(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Dealing with ADB");
        strcpy(labels[1], "Flashing Images");
        strcpy(labels[2], "Preparations");
        strcpy(labels[3], "Info");
    } 
    
    else 
    {
        strcpy(labels[0], "Umgang mit ADB");
        strcpy(labels[1], "Flash Images");
        strcpy(labels[2], "Vorbereitungen");
        strcpy(labels[3], "Info");
    }
}

/* main function of flash_GUI*/
void instruction_GUI(int argc, char *argv[]) 
{
    LOG_INFO("instruction_GUI");
    GtkWidget *window, *grid, *button;
    char button_labels[4][30];
    
    gtk_init();
    main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_instruction_GUI(button_labels);
    
    window = gtk_window_new();
    const char *instruction_GUI_window = strcmp(language, "de") == 0 ? "Anleitungen" : "Instructions";
    gtk_window_set_title(GTK_WINDOW(window), instruction_GUI_window);
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
                g_signal_connect(button, "clicked", G_CALLBACK(start_instruction_adb), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_instruction_flash), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(start_instruction_prepare_flash), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(start_instruction_info), NULL);
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
    
    LOG_INFO("end instruction_GUI");
}
