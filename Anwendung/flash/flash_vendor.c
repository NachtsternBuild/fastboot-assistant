/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_vendor			 *
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
// function to flash vendor.img on only-a-devices
void vendor_on_a(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "vendor", NULL, "vendor.img");
}

// function to flash vendor.img (a/b-devices)
void vendor_on_ab(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "vendor_a", "vendor_b", "vendor.img");
}

// function to flash vendor_boot.img (only-a-devices)
void vendor_boot_on_a(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "vendor_boot", NULL, "vendor_boot.img");
}

// function to flash vendor_boot.img (a/b-devices)
void vendor_boot_on_ab(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "vendor_boot_a", "vendor_boot_b", "vendor_boot.img");
}

// function to flash boot.img (heimdall)
void vendor_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "VENDOR", "vendor.img");
}

// function to flash init_boot.img (heimdall)
void vendor_boot_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "VENDOR_BOOT", "vendor_boot.img");
}

// Function to set up button labels based on the language
void set_button_labels_flash_vendor(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Vendor (only-a)");
        strcpy(labels[1], "Vendor (a/b");
        strcpy(labels[2], "Vendor (heimdall)");
        strcpy(labels[3], "vendor_boot (only-a)");
        strcpy(labels[4], "vendor_boot (a/b)");
        strcpy(labels[5], "vendor_boot (heimdall)");
    } 
    
    else 
    {
        strcpy(labels[0], "Vendor (only-a)");
        strcpy(labels[1], "Vendor (a/b");
        strcpy(labels[2], "Vendor (heimdall)");
        strcpy(labels[3], "vendor_boot (only-a)");
        strcpy(labels[4], "vendor_boot (a/b)");
        strcpy(labels[5], "vendor_boot (heimdall)");
    }
}

// main function
void flash_vendor(int argc, char *argv[])
{
	g_print("Log: flash_vendor\n");
	GtkWidget *window, *grid, *button;
    char button_labels[6][30];
    
    gtk_init();
    apply_theme();
    apply_language();
    set_button_labels_flash_vendor(button_labels);
    
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Flashen:");
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
                g_signal_connect(button, "clicked", G_CALLBACK(vendor_on_a), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(vendor_on_ab), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(vendor_heimdall), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(vendor_boot_on_a), NULL);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(vendor_boot_on_ab), NULL);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(vendor_boot_heimdall), NULL);
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
    
    g_print("Log: end flash_vendor\n");
}
