/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_GUI				 *
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
#include "function_header.h"
#include "flash_function_header.h"
#include "loading_spinner.h"

#define MAX_BUFFER_SIZE 256

// includde all functions
extern void flash_recovery(GtkWidget *widget, gpointer stack);
extern void flash_boot(GtkWidget *widget, gpointer stack);
extern void flash_vendor(GtkWidget *widget, gpointer stack);
extern void flash_payload(GtkWidget *widget, gpointer stack);
extern void flash_system(GtkWidget *widget, gpointer stack);
extern void flash_vbmeta_dtbo(GtkWidget *widget, gpointer stack);
extern void flash_preloader(GtkWidget *widget, gpointer stack);
extern void flash_data(GtkWidget *widget, gpointer stack);
extern void flash_others(GtkWidget *widget, gpointer stack);

// function to set up button labels based on the language
void set_button_labels_flash_GUI(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Flash Recovery");
        strcpy(labels[1], "Flash Boot");
        strcpy(labels[2], "Flash Vendor");
        strcpy(labels[3], "Flash payload.zip");
        strcpy(labels[4], "Flash System");
        strcpy(labels[5], "Flash vbmeta/dtbo");
        strcpy(labels[6], "Flash Preloader");
        strcpy(labels[7], "Flash Nutzerdaten");
        strcpy(labels[8], "Flash Other Images");
        strcpy(labels[9], "Back to Home");
    } 
    
    else 
    {
        strcpy(labels[0], "Flash Recovery");
        strcpy(labels[1], "Flash Boot");
        strcpy(labels[2], "Flash Vendor");
        strcpy(labels[3], "Flash payload.zip");
        strcpy(labels[4], "Flash System");
        strcpy(labels[5], "Flash vbmeta/dtbo");
        strcpy(labels[6], "Flash Preloader");
        strcpy(labels[7], "Flash Nutzerdaten");
        strcpy(labels[8], "Flash Andere Images");
        strcpy(labels[9], "Zurück zur Startseite");
    }
}


/* main function - flash_GUI*/
void flash_GUI(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("flash_GUI");
    
    apply_theme();
    apply_language();
    
    char button_labels[10][30];  // labels for the button 
    set_button_labels_flash_GUI(labels);  // for both languages
    
    GtkWidget *flash_GUI = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(flash_GUI, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(flash_GUI, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(flash_recovery), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(flash_boot), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(flash_vendor), stack);
    GtkWidget *btn4 = create_nav_button(labels[3], G_CALLBACK(flash_payload), stack);
    GtkWidget *btn5 = create_nav_button(labels[4], G_CALLBACK(flash_system), stack);
    GtkWidget *btn6 = create_nav_button(labels[5], G_CALLBACK(flash_vbmeta_dtbo), stack);
    GtkWidget *btn7 = create_nav_button(labels[6], G_CALLBACK(flash_preloader_super), stack);
    GtkWidget *btn8 = create_nav_button(labels[7], G_CALLBACK(flash_data), stack);
    GtkWidget *btn9 = create_nav_button(labels[8], G_CALLBACK(flash_others), stack);
    GtkWidget *btn_back = create_nav_button(labels[9], G_CALLBACK(show_home_page), stack);

    // add the button to the grid
    // line 1
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 2, 0, 1, 1);
    // line 2 (1)
    gtk_grid_attach(GTK_GRID(grid), btn4, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn5, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn6, 2, 1, 1, 1);
    // line 3 (2)
    gtk_grid_attach(GTK_GRID(grid), btn7, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn8, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn9, 2, 2, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(flash_GUI), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(flash_GUI), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "flash_GUI")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), flash_GUI, "flash_GUI");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "flash_GUI");
    
    LOG_INFO("end flash_GUI");
}
