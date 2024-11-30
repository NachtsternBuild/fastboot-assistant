/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_boot				 *
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
// function to flash boot.img on only-a-devices
void boot_on_a(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "boot", NULL, "boot.img");
}

// function to flash boot.img (a/b-devices)
void boot_on_ab(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "boot_a", "boot_b", "boot.img");
}

// function to flash init_boot.img (only-a-devices)
void init_boot_on_a(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "init_boot", NULL, "init_boot.img");
}

// function to flash init_boot.img (a/b-devices)
void init_boot_on_ab(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "init_boot_a", "init_boot_b", "init_boot.img");
}

// function to flash boot.img (heimdall)
void boot_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "BOOT", "boot.img");
}

// function to flash init_boot.img (heimdall)
void init_boot_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "INIT_BOOT", "init_boot.img");
}

// Function to set up button labels based on the language
void set_button_labels_flash_boot(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Boot (only-a)");
        strcpy(labels[1], "Boot (a/b)");
        strcpy(labels[2], "Boot (heimdall)");
        strcpy(labels[3], "init_boot (only-a)");
        strcpy(labels[4], "init_boot (a/b)");
        strcpy(labels[5], "init_boot (heimdall)");
    } 
    
    else 
    {
        strcpy(labels[0], "Boot (only-a)");
        strcpy(labels[1], "Boot (a/b)");
        strcpy(labels[2], "Boot (heimdall)");
        strcpy(labels[3], "init_boot (only-a)");
        strcpy(labels[4], "init_boot (a/b)");
        strcpy(labels[5], "init_boot (heimdall)");
    }
}

// main function
void flash_boot(int argc, char *argv[])
{
	g_print("Log: flash_boot\n");
	GtkWidget *window, *grid, *button;
    char button_labels[6][30];
    
    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_flash_boot(button_labels);
    
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
    
    for (int i = 0; i < 6; i++) 
    {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);
        
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(boot_on_a), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(boot_on_ab), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(boot_heimdall), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(init_boot_on_a), NULL);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(init_boot_on_ab), NULL);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(init_boot_heimdall), NULL);
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
    
    g_print("Log: end flash_boot\n");
}

