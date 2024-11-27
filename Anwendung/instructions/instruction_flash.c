/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_flash		 *
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
#include "instruction_header.h"

#define MAX_BUFFER_SIZE 256

extern void instruction_root();
extern void instruction_vendor();
extern void instruction_gsi();
extern void instruction_custom_rom();
extern void instruction_recovery();
extern void instruction_others();

// button 1 - inst. for root
static void inst_root(GtkWidget *widget, gpointer data)
{
    instruction_root();
}

// button 2 - inst. for vendor
static void inst_vendor(GtkWidget *widget, gpointer data)
{
	instruction_vendor();
}

// button 3 - inst. for GSI
static void inst_gsi(GtkWidget *widget, gpointer data)
{
    instruction_gsi();
}

// button 4 - inst. for custom ROMs
static void inst_custom_rom(GtkWidget *widget, gpointer data)
{
	instruction_custom_rom();
}

// button 5 - inst. for recovery
static void inst_recovery(GtkWidget *widget, gpointer data)
{
	instruction_recovery();
}

// button 6 - inst. for other images
static void inst_others(GtkWidget *widget, gpointer data)
{
	instruction_others();
}

// Function to set up button labels based on the language
void set_button_labels_instruction_flash(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Rooting");
        strcpy(labels[1], "Vendor (VNDK)");
        strcpy(labels[2], "Generic System Image (GSI)");
        strcpy(labels[3], "Custom ROMs");
        strcpy(labels[4], "Recovery");
        strcpy(labels[5], "Others");
    } 
    
    else 
    {
        strcpy(labels[0], "Rooten");
        strcpy(labels[1], "Vendor (VNDK)");
        strcpy(labels[2], "Generic System Image (GSI)");
        strcpy(labels[3], "Custom ROMs");
        strcpy(labels[4], "Recovery");
        strcpy(labels[5], "Anderes");
    }
}

/* start main programm */
void instruction_flash(int argc, char *argv[])
{
	g_print("Log: instruction_flash\n");
	GtkWidget *window, *grid, *button;
    char button_labels[6][30];
    
    gtk_init();
    apply_theme();
    apply_language();
    set_button_labels_instruction_flash(button_labels);
    
    window = gtk_window_new();
    const char *instruction_flash_window = strcmp(language, "de") == 0 ? "Anleitungen - Flashen" : "Instructions - Flashing";
    gtk_window_set_title(GTK_WINDOW(window), instruction_flash_window);
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
                g_signal_connect(button, "clicked", G_CALLBACK(inst_root), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(inst_vendor), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(inst_gsi), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(inst_custom_rom), NULL);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(inst_recovery), NULL);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(inst_others), NULL);
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
    
    g_print("Log: end instruction_flash\n");
}

