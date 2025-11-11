/**
* instruction_flash.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// function to set up button labels based on the language
void set_button_labels_instruction_flash(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Rooting"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Vendor (VNDK)"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Generic System Image (GSI)"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("Custom ROMs"), sizeof(labels[3]));
    g_strlcpy(labels[4], _("Recovery"), sizeof(labels[4]));
    g_strlcpy(labels[5], _("Others"), sizeof(labels[5]));
    g_strlcpy(labels[6], _("Back"), sizeof(labels[6]));
}

/* main function - instruction_flash */
void instruction_flash(GtkWidget *widget, gpointer stack)
{
	LOGD("instruction_flash");
    
    char labels[7][30];  // labels for the button 
    set_button_labels_instruction_flash(labels);  // for both languages
    
    GtkWidget *instruction_flash = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(instruction_flash, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(instruction_flash, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button_icon_position("security-high-symbolic", labels[0], G_CALLBACK(instruction_root), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_button_icon_position("media-optical-dvd-symbolic", labels[1], G_CALLBACK(instruction_vendor), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn3 = create_button_icon_position("media-optical-dvd-symbolic", labels[2], G_CALLBACK(instruction_gsi), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn4 = create_button_icon_position("media-zip-symbolic", labels[3], G_CALLBACK(instruction_custom_rom), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn5 = create_button_icon_position("applications-utilities-symbolic", labels[4], G_CALLBACK(instruction_recovery), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn6 = create_button_icon_position("emblem-documents-symbolic", labels[5], G_CALLBACK(instruction_others), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[6], G_CALLBACK(instruction_GUI), stack, GTK_ALIGN_CENTER);

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
    gtk_box_append(GTK_BOX(instruction_flash), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(instruction_flash), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "instruction_flash")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), instruction_flash, "instruction_flash");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "instruction_flash");
        
    LOGD("end instruction_flash");
}

