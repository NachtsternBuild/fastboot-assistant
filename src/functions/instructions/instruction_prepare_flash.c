/**
* instruction_prepare_flash.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// function to set up button labels based on the language
void set_button_labels_instruction_prepare_flash(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Backup"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Prepare images"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Back"), sizeof(labels[2]));
}

/* main function - instruction_prepare_flash */
void instruction_prepare_flash(GtkWidget *widget, gpointer stack)
{
	LOGD("instruction_prepare_flash");
    
    char labels[3][30];  // labels for the button 
    set_button_labels_instruction_prepare_flash(labels);  // for both languages
    
    GtkWidget *instruction_prepare_flash = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(instruction_prepare_flash, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(instruction_prepare_flash, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
	GtkWidget *btn1 = create_button_icon_position("folder-remote-symbolic", labels[0], G_CALLBACK(instruction_backup), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_button_icon_position("applications-engineering-symbolic", labels[1], G_CALLBACK(instruction_preflash), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[2], G_CALLBACK(instruction_GUI), stack, GTK_ALIGN_CENTER);
    
    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(instruction_prepare_flash), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(instruction_prepare_flash), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "instruction_prepare_flash")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), instruction_prepare_flash, "instruction_prepare_flash");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "instruction_prepare_flash");
        
    LOGD("end instruction_prepare_flash");
}
