/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_preloader_super	 *
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
#include "function_header.h"
#include "program_functions.h"
#include "flash_function_header.h"

// button handler functions
// function to flash preloader.bin on only-a-devices
void preloader_bin_on_a(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, main_window, "preloader", NULL, "preloader.bin", NULL);
}

// function to flash preloader.bin (a/b-devices)
void preloader_bin_on_ab(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, main_window, "preloader_a", "preloader_b", "preloader.bin", NULL);
}

// function to flash preloader.img (only-a-devices)
void preloader_img_on_a(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, main_window, "preloader", NULL, "preloader.img", NULL);
}

// function to flash preloader.img (a/b-devices)
void preloader_img_on_ab(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, main_window, "preloader_a", "preloader_b", "preloader.img", NULL);
}

// function to flash super.img
void super_img(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, main_window, "super", NULL, "super.img", NULL);
}

// function to flash preloader.bin (heimdall)
void preloader_bin_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, main_window, "PRELOADER", "preloader.bin");
}

// function to flash preloader.img (heimdall)
void preloader_img_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, main_window, "PRELOADER", "preloader.img");
}

// function to flash super.img (heimdall)
void super_img_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, main_window, "SUPER", "super.img");
}

// function to set up button labels based on the language
void set_button_labels_flash_preloader_super(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "preloader.bin (only-a)");
        strcpy(labels[1], "preloader.bin (a/b)");
        strcpy(labels[2], "preloader.img (only-a)");
        strcpy(labels[3], "preloader.img (a/b)");
        strcpy(labels[4], "preloader.bin (heimdall)");
        strcpy(labels[5], "preloader.img (heimdall)");
        strcpy(labels[6], "super.img");
        strcpy(labels[7], "super.img (heimdall)");
        strcpy(labels[8], "Back");
    } 
    
    else 
    {
        strcpy(labels[0], "preloader.bin (only-a)");
        strcpy(labels[1], "preloader.bin (a/b)");
        strcpy(labels[2], "preloader.img (only-a)");
        strcpy(labels[3], "preloader.img (a/b)");
        strcpy(labels[4], "preloader.bin (heimdall)");
        strcpy(labels[5], "preloader.img (heimdall)");
        strcpy(labels[6], "super.img");
        strcpy(labels[7], "super.img (heimdall)");
        strcpy(labels[8], "Zurück");
    }
}

/* main function - flash_preloader_super */
void flash_preloader_super(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("flash_preloader_super");
	
	apply_language();
    
    char labels[9][30];  // labels for the button 
    set_button_labels_flash_preloader_super(labels);  // for both languages
    
    GtkWidget *flash_preloader_super = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(flash_preloader_super, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(flash_preloader_super, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(preloader_bin_on_a), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(preloader_bin_on_ab), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(preloader_img_on_a), stack);
    GtkWidget *btn4 = create_nav_button(labels[3], G_CALLBACK(preloader_img_on_ab), stack);
    GtkWidget *btn5 = create_nav_button(labels[4], G_CALLBACK(preloader_bin_heimdall), stack);
    GtkWidget *btn6 = create_nav_button(labels[5], G_CALLBACK(preloader_img_heimdall), stack);
    GtkWidget *btn7 = create_nav_button(labels[6], G_CALLBACK(super_img), stack);
    GtkWidget *btn8 = create_nav_button(labels[7], G_CALLBACK(super_img_heimdall), stack);
    GtkWidget *btn_back = create_nav_button(labels[8], G_CALLBACK(flash_GUI), stack);

    // add the button to the grid
    // line 1
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    // line 2
    gtk_grid_attach(GTK_GRID(grid), btn3, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn4, 1, 1, 1, 1);
    // line 3
    gtk_grid_attach(GTK_GRID(grid), btn5, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn6, 1, 2, 1, 1);
    // line 4 
    gtk_grid_attach(GTK_GRID(grid), btn7, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn8, 1, 3, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(flash_preloader_super), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(flash_preloader_super), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "flash_preloader_super")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), flash_preloader_super, "flash_preloader_super");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "flash_preloader_super");
         
    LOG_INFO("end flash_preloader_super");
}
