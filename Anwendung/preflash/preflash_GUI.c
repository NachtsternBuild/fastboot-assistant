/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - preflash_GUI			 *
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

#define MAX_BUFFER_SIZE 256

// include all functions
extern void backup_function();
extern void prepare_function();
extern void erase_data();
extern void lock_unlock_bootloader();
extern void set_active_slot();
extern void partitions();

// Callback functions for each button
// start backup_function-function
static void start_backup_function(GtkWidget *widget, gpointer data) 
{
    backup_function();
}

// start start_prepare-function
static void start_prepare_function(GtkWidget *widget, gpointer data) 
{
    prepare();
}

// start erase_data-function
static void start_erase_data(GtkWidget *widget, gpointer data) 
{
    erase_data();
}

// function without any function
static void start_set_active_slot(GtkWidget *widget, gpointer data) 
{
    set_active_slot();
}

// start lock_unlock_bootloader-function
static void start_lock_unlock_bootloader(GtkWidget *widget, gpointer data) 
{
    lock_unlock_bootloader();
}

// function without any function
static void start_partitions(GtkWidget *widget, gpointer data) 
{
    partitions();
}

// Function to set up button labels based on the language
void set_button_labels_preflash(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Backup");
        strcpy(labels[1], "Prepare files");
        strcpy(labels[2], "Delete user data");
        strcpy(labels[3], "Set active slot");
        strcpy(labels[4], "Bootloader");
        strcpy(labels[5], "Partitioning");
    } 
    
    else 
    {
        strcpy(labels[0], "Backup");
        strcpy(labels[1], "Dateien vorbereiten");
        strcpy(labels[2], "Lösche Nutzerdaten");
        strcpy(labels[3], "Setze aktiven Slot");
        strcpy(labels[4], "Bootloader");
        strcpy(labels[5], "Partitionierung");
    }
}


/* main function of preflash_GUI*/
void preflash_GUI(int argc, char *argv[]) 
{
    g_print("Log: preflash_GUI\n");
    GtkWidget *window, *grid, *button;
    char button_labels[6][30];
    
    gtk_init();
    apply_theme();
    apply_language();
    set_button_labels_preflash(button_labels);
    
    window = gtk_window_new();
    const char *preflash_window = strcmp(language, "de") == 0 ? "Vorbereitung" : "Preparation";
    gtk_window_set_title(GTK_WINDOW(window), preflash_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);
    
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
                g_signal_connect(button, "clicked", G_CALLBACK(start_backup_function), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_prepare_function), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(start_erase_data), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(start_set_active_slot), NULL);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(start_lock_unlock_bootloader), NULL);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(start_partitions), NULL);
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
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop); // GTK-Hauptschleife starten
    
    g_print("Log: end preflash_GUI\n");
}

