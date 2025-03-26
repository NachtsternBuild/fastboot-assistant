/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_vbmeta_dtbo		 *
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
// function to flash vbmeta.img on only-a-devices
void vbmeta_on_a(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, window, "vbmeta_a", NULL, "vbmeta.img", "--disable-verity --disable-verification");
}

// function to flash vbmeta.img (a/b-devices)
void vbmeta_on_ab(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, window, "vbmeta_a", "vbmeta_b", "vbmeta.img", "--disable-verity --disable-verification");
}

// function to flash dtbo.img (only-a-devices)
void dtbo_on_a(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, window, "dtbo", NULL, "dtbo.img", NULL);
}

// function to flash dtbo.img (a/b-devices)
void dtbo_on_ab(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, window, "dtbo_a", "dtbo_b", "dtbo.img", NULL);
}

// function to flash vbmeta.img (heimdall)
void vbmeta_img_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, window, "VBMETA", "vbmeta.img");
}

// function to flash dtbo.img (heimdall)
void dtbo_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, window, "DTBO", "dtbo.img");
}

// function to set up button labels based on the language
void set_button_labels_flash_vbmeta_dtbo(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "vbmeta (only-a)");
        strcpy(labels[1], "vbmeta (a/b)");
        strcpy(labels[2], "vbmeta (heimdall)");
        strcpy(labels[3], "dtbo (only-a)");
        strcpy(labels[4], "dtbo (a/b)");
        strcpy(labels[5], "dtbo (heimdall)");
        strcpy(labels[6], "Back");
    } 
    
    else 
    {
        strcpy(labels[0], "vbmeta (only-a)");
        strcpy(labels[1], "vbmeta (a/b)");
        strcpy(labels[2], "vbmeta (heimdall)");
        strcpy(labels[3], "dtbo (only-a)");
        strcpy(labels[4], "dtbo (a/b)");
        strcpy(labels[5], "dtbo (heimdall)");
        strcpy(labels[6], "Zurück");
    }
}

/* main function - flash_vbmeta_dtbo */
void flash_vbmeta_dtbo(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("flash_vbmeta_dtbo");
	   
    apply_language();
    
    char button_labels[7][30];  // labels for the button 
    set_button_labels_flash_vbmeta_dtbo(labels);  // for both languages
    
    GtkWidget *flash_vbmeta_dtbo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(flash_vbmeta_dtbo, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(flash_vbmeta_dtbo, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(vbmeta_on_a), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(vbmeta_on_ab), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(vbmeta_img_heimdall), stack);
    GtkWidget *btn4 = create_nav_button(labels[3], G_CALLBACK(dtbo_on_a), stack);
    GtkWidget *btn5 = create_nav_button(labels[4], G_CALLBACK(dtbo_on_ab), stack);
    GtkWidget *btn6 = create_nav_button(labels[5], G_CALLBACK(dtbo_heimdall), stack);
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
    gtk_box_append(GTK_BOX(flash_vbmeta_dtbo), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(flash_vbmeta_dtbo), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "flash_vbmeta_dtbo")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), flash_vbmeta_dtbo, "flash_vbmeta_dtbo");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "flash_vbmeta_dtbo");
        
    LOG_INFO("end flash_vbmeta_dtbo");
}
