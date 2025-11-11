/**
* flash_others.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// Function to set up button labels based on the language
void set_button_labels_flash_others(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Predefined images"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Images in the directory"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Back"), sizeof(labels[2]));
}

/* main function - flash_others */
void flash_others(GtkWidget *widget, gpointer stack)
{
    LOGI("flash_others");
    
    char labels[3][30];  // labels for the button 
    set_button_labels_flash_others(labels);  // for both languages
    
    GtkWidget *flash_others = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(flash_others, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(flash_others, GTK_ALIGN_CENTER);
    
    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button_icon_position("emblem-documents-symbolic", labels[0], G_CALLBACK(flash_list_images), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_button_icon_position("folder-visiting-symbolic", labels[1], G_CALLBACK(flash_images), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[2], G_CALLBACK(flash_GUI), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(flash_others), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(flash_others), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "flash_others")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), flash_others, "flash_others");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "flash_others");
           
    LOGI("end flash_others");
}
