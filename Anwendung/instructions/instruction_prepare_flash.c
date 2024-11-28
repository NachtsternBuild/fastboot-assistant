/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern 							*
 *											 * 
 *			instruction_prepare_flash		 *
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
#include "instruction_header.h"

#define MAX_BUFFER_SIZE 256

extern void instruction_backup();
extern void instruction_preflash();

// button 1 - inst. for root
static void inst_backup(GtkWidget *widget, gpointer data)
{
    instruction_backup();
}

// button 2 - inst. for vendor
static void inst_preflash(GtkWidget *widget, gpointer data)
{
	instruction_preflash();
}

// Function to set up button labels based on the language
void set_button_labels_instruction_prepare_flash(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Backup");
        strcpy(labels[1], "Prepare images");
    } 
    
    else 
    {
        strcpy(labels[0], "Backup");
        strcpy(labels[1], "Systemabbilder vorbereiten");
    }
}

/* start main programm - instruction_prepare_flash */
void instruction_prepare_flash(int argc, char *argv[])
{
	g_print("Log: instruction_prepare_flash\n");
	GtkWidget *window, *grid, *button;
    char button_labels[2][30];
    
    gtk_init();
    main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_instruction_prepare_flash(button_labels);
    
    window = gtk_window_new();
    const char *instruction_prepare_flash_window = strcmp(language, "de") == 0 ? "Anleitungen - Vorbereitung" : "Instructions - Preparation";
    gtk_window_set_title(GTK_WINDOW(window), instruction_prepare_flash_window);
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
                g_signal_connect(button, "clicked", G_CALLBACK(inst_backup), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(inst_preflash), NULL);
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
    
    g_print("Log: End of instruction_prepare_flash\n");
}
