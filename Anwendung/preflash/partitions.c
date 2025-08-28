/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - partitions				 *
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

#define MAX_BUFFER_SIZE 256

char partition_command[2048];

// callback functions for each button
// remove the boot partition
static void remove_boot(GtkWidget *widget, gpointer stack) 
{
	LOG_INFO("remove_boot");
	remove_partition("boot");
	LOG_INFO("end remove_boot");
}

// remove the vendor partition
static void remove_vendor(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("remove_vendor");
    remove_partition("vendor");
    LOG_INFO("end remove_vendor");
}

// remove the system partition
static void remove_system(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("remove_system");
    remove_partition("system");
    LOG_INFO("end remove_system");
}

// resize of the boot partition
static void resize_boot(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("resize_boot");
    resize_partition("boot");
    LOG_INFO("end resize_boot");
}

// resize of the vendor partition
static void resize_vendor(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("resize_vendor");
    resize_partition("vendor");
    LOG_INFO("end resize_vendor");
}

// resize of the system partition
static void resize_system(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("resize_system");
    resize_partition("system");
    LOG_INFO("end resize_system");
}

// create boot partition
static void create_boot(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("create_boot");
    create_partition("boot");
    LOG_INFO("end create_boot");
}

// create vendor partition
static void create_vendor(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("create_vendor");
    create_partition("vendor");
    LOG_INFO("end create_vendor");
}

// create system partition
static void create_system(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("create_system");
    create_partition("system");
    LOG_INFO("end create_system");
}

// function to set up button labels based on the language
void set_button_labels_partitions(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Delete Boot"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Delete Vendor"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Delete System"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("Resize Boot"), sizeof(labels[3]));
    g_strlcpy(labels[4], _("Resize Vendor"), sizeof(labels[4]));
    g_strlcpy(labels[5], _("Resize System"), sizeof(labels[5]));
    g_strlcpy(labels[6], _("Create Boot"), sizeof(labels[6]));
    g_strlcpy(labels[7], _("Create Vendor"), sizeof(labels[7]));
    g_strlcpy(labels[8], _("Create System"), sizeof(labels[8]));
    g_strlcpy(labels[9], _("Back"), sizeof(labels[9]));
}

/* main function - partitions*/
void partitions(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("partitions");
       
    apply_language();
    
    char labels[10][30];  // labels for the button 
    set_button_labels_partitions(labels);  // for both languages
    
    GtkWidget *partitions = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(partitions, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(partitions, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(remove_boot), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(remove_vendor), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(remove_system), stack);
    GtkWidget *btn4 = create_nav_button(labels[3], G_CALLBACK(resize_boot), stack);
    GtkWidget *btn5 = create_nav_button(labels[4], G_CALLBACK(resize_vendor), stack);
    GtkWidget *btn6 = create_nav_button(labels[5], G_CALLBACK(resize_system), stack);
    GtkWidget *btn7 = create_nav_button(labels[6], G_CALLBACK(create_boot), stack);
    GtkWidget *btn8 = create_nav_button(labels[7], G_CALLBACK(create_vendor), stack);
    GtkWidget *btn9 = create_nav_button(labels[8], G_CALLBACK(create_system), stack);
    GtkWidget *btn_back = create_icon_nav_button_with_position("pan-start-symbolic", labels[9], G_CALLBACK(preflash_GUI), stack, GTK_ALIGN_CENTER);

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
    gtk_box_append(GTK_BOX(partitions), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(partitions), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "partitions")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), partitions, "partitions");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "partitions");
        
    LOG_INFO("end partitions");
}

