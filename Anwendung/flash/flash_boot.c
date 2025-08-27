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

// Button handler functions
// function to flash boot.img on only-a-devices
void boot_on_a(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, main_window, "boot", NULL, "boot.img", NULL);
}

// function to flash boot.img (a/b-devices)
void boot_on_ab(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, main_window, "boot_a", "boot_b", "boot.img", NULL);
}

// function to flash init_boot.img (only-a-devices)
void init_boot_on_a(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, main_window, "init_boot", NULL, "init_boot.img", NULL);
}

// function to flash init_boot.img (a/b-devices)
void init_boot_on_ab(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, main_window, "init_boot_a", "init_boot_b", "init_boot.img", NULL);  
}

// function to flash boot.img (heimdall)
void boot_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, main_window, "BOOT", "boot.img");
}

// function to flash init_boot.img (heimdall)
void init_boot_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, main_window, "INIT_BOOT", "init_boot.img");
}

// function to set up button labels based on the language
void set_button_labels_flash_boot(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Boot (only-a)"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Boot (a/b)"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Boot (heimdall)"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("init_boot (only-a)"), sizeof(labels[3]));
    g_strlcpy(labels[4], _("init_boot (a/b)"), sizeof(labels[4]));
    g_strlcpy(labels[5], _("init_boot (heimdall)"), sizeof(labels[5]));
    g_strlcpy(labels[6], _("Back"), sizeof(labels[6]));
}

/* main function - flash_boot */
void flash_boot(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("flash_boot");
	   
    apply_language();
    
    char labels[7][30];  // labels for the button 
    set_button_labels_flash_boot(labels);  // for both languages
    
    GtkWidget *flash_boot = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(flash_boot, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(flash_boot, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(boot_on_a), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(boot_on_ab), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(boot_heimdall), stack);
    GtkWidget *btn4 = create_nav_button(labels[3], G_CALLBACK(init_boot_on_a), stack);
    GtkWidget *btn5 = create_nav_button(labels[4], G_CALLBACK(init_boot_on_ab), stack);
    GtkWidget *btn6 = create_nav_button(labels[5], G_CALLBACK(init_boot_heimdall), stack);
    GtkWidget *btn_back = create_icon_nav_button_with_position("pan-start-symbolic", labels[6], G_CALLBACK(flash_GUI), stack, GTK_ALIGN_CENTER);

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
    gtk_box_append(GTK_BOX(flash_boot), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(flash_boot), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "flash_boot")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), flash_boot, "flash_boot");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "flash_boot");
    
    LOG_INFO("end flash_boot");
}

