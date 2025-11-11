/**
* preflash_GUI.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// Function to set up button labels based on the language
void set_button_labels_preflash(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Backup"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Prepare files"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Delete user data"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("Set active slot"), sizeof(labels[3]));
    g_strlcpy(labels[4], _("Bootloader"), sizeof(labels[4]));
    g_strlcpy(labels[5], _("Partitioning"), sizeof(labels[5]));
    g_strlcpy(labels[6], _("Back to Home"), sizeof(labels[6]));
}

/* main function - preflash_GUI*/
void preflash_GUI(GtkWidget *widget, gpointer stack) 
{
    LOGD("preflash_GUI");
    
    char labels[7][30];  // labels for the button 
    set_button_labels_preflash(labels);  // for both languages
    
    GtkWidget *preflash_GUI = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(preflash_GUI, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(preflash_GUI, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button_icon_position("folder-remote-symbolic", labels[0], G_CALLBACK(backup_function), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_button_icon_position("system-file-manager-symbolic", labels[1], G_CALLBACK(prepare), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn3 = create_button_icon_position("user-trash-symbolic", labels[2], G_CALLBACK(erase_data), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn4 = create_button_icon_position("object-flip-horizontal-symbolic", labels[3], G_CALLBACK(set_active_slot), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn5 = create_button_icon_position("rotation-locked-symbolic", labels[4], G_CALLBACK(lock_unlock_bootloader), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn6 = create_button_icon_position("drive-harddisk-system-symbolic", labels[5], G_CALLBACK(partitions), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[6], G_CALLBACK(show_home_page), stack, GTK_ALIGN_CENTER);

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
    gtk_box_append(GTK_BOX(preflash_GUI), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(preflash_GUI), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "preflash_GUI")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), preflash_GUI, "preflash_GUI");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "preflash_GUI");
    
    LOGD("end preflash_GUI");
}

