/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - reboot_GUI				 *
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
extern void reboot_fastboot();
extern void reboot();
extern void reboot_recovery();
extern void reboot_heimdall();

// Callback functions for each button
// start reboot_fastboot-function
static void start_reboot_fastboot(GtkWidget *widget, gpointer data) 
{
    reboot_fastboot();
}

// start reboot-function
static void start_reboot(GtkWidget *widget, gpointer data) 
{
    reboot();
}

// start reboot_recovery-function
static void start_reboot_recovery(GtkWidget *widget, gpointer data) 
{
    reboot_recovery();
}

// start reboot-function heimdall
static void start_reboot_heimdall(GtkWidget *widget, gpointer data) 
{
    reboot_heimdall();
}

// Function to set up button labels based on the language
void set_button_labels_reboot(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Reboot Fastboot");
        strcpy(labels[1], "Reboot");
        strcpy(labels[2], "Reboot Recovery");
        strcpy(labels[3], "Reboot (heimdall)");
    } 
    
    else 
    {
        strcpy(labels[0], "Neustart Fastboot");
        strcpy(labels[1], "Neustart");
        strcpy(labels[2], "Neustart in Recovery");
        strcpy(labels[3], "Neustart (heimdall)");
    }
}

void reboot_GUI(int argc, char *argv[]) 
{
	g_print("Log: reboot_GUI\n");
	GtkWidget *window, *grid, *button;
    char button_labels[4][30];
    
    gtk_init();
    apply_theme();
    apply_language();
    set_button_labels_reboot(button_labels);
    
    window = gtk_window_new();
    const char *reboot_window = strcmp(language, "de") == 0 ? "Neustart" : "Reboot";
    gtk_window_set_title(GTK_WINDOW(window), reboot_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);
    
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
                g_signal_connect(button, "clicked", G_CALLBACK(start_reboot_fastboot), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_reboot), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(start_reboot_recovery), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(start_reboot_heimdall), NULL);
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
    g_main_loop_run(loop); 
    
    g_print("Log: end reboot_GUI\n");
}
