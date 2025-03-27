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
#include "flash_function_header.h"

// button handler functions
// function to flash vendor.img on only-a-devices
void vendor_on_a(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, window, "vendor", NULL, "vendor.img", NULL);
}

// function to flash vendor.img (a/b-devices)
void vendor_on_ab(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, window, "vendor_a", "vendor_b", "vendor.img", NULL);
}

// function to flash vendor_boot.img (only-a-devices)
void vendor_boot_on_a(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, window, "vendor_boot", NULL, "vendor_boot.img", NULL);
}

// function to flash vendor_boot.img (a/b-devices)
void vendor_boot_on_ab(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, window, "vendor_boot_a", "vendor_boot_b", "vendor_boot.img", NULL);
}

// function to flash boot.img (heimdall)
void vendor_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, window, "VENDOR", "vendor.img");
}

// function to flash init_boot.img (heimdall)
void vendor_boot_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, window, "VENDOR_BOOT", "vendor_boot.img");
}

// function to set up button labels based on the language
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
        strcpy(labels[6], "Back");
    } 
    
    else 
    {
        strcpy(labels[0], "Vendor (only-a)");
        strcpy(labels[1], "Vendor (a/b");
        strcpy(labels[2], "Vendor (heimdall)");
        strcpy(labels[3], "vendor_boot (only-a)");
        strcpy(labels[4], "vendor_boot (a/b)");
        strcpy(labels[5], "vendor_boot (heimdall)");
        strcpy(labels[6], "Zurück");
    }
}

// main function
void flash_vendor(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("flash_vendor");
	apply_language();
    
    char button_labels[7][30];  // labels for the button 
    set_button_labels_flash_vendor(labels);  // for both languages
    
    GtkWidget *flash_vendor = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(flash_vendor, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(flash_vendor, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(vendor_on_a), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(vendor_on_ab), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(vendor_heimdall), stack);
    GtkWidget *btn4 = create_nav_button(labels[3], G_CALLBACK(vendor_boot_on_a), stack);
    GtkWidget *btn5 = create_nav_button(labels[4], G_CALLBACK(vendor_boot_on_ab), stack);
    GtkWidget *btn6 = create_nav_button(labels[5], G_CALLBACK(vendor_boot_heimdall), stack);
    GtkWidget *btn_back = create_nav_button(labels[6], G_CALLBACK(flash_GUI), stack);

    // add the button to the grid
    // line 1
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 2, 0, 1, 1);
    // line 2 (1)
    gtk_grid_attach(GTK_GRID(grid), btn4, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn5, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn6, 2, 1, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(flash_vendor), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(flash_vendor), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "flash_vendor")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), flash_vendor, "flash_vendor");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "flash_vendor");
        
    LOG_INFO("end flash_vendor");
}
