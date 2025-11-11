/**
* backup_function.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// function to set up button labels based on the language
void set_button_labels_backup(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Backup with root"), sizeof(labels[0]));
    g_strlcpy(labels[0], _("Backup without root"), sizeof(labels[1]));
    g_strlcpy(labels[0], _("Back"), sizeof(labels[2]));
} 

/* main function - backup_function */
void backup_function(GtkWidget *widget, gpointer stack) 
{
    LOGD("backup_function");
    
    char labels[3][30];  // labels for the button 
    set_button_labels_backup(labels);  // for both languages
    
    GtkWidget *backup_function = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(backup_function, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(backup_function, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button_icon_position("security-high-symbolic", labels[0], G_CALLBACK(backup_root), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_button_icon_position("avatar-default-symbolic", labels[1], G_CALLBACK(backup_noroot), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[2], G_CALLBACK(preflash_GUI), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(backup_function), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(backup_function), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "backup_function")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), backup_function, "backup_function");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "backup_function");

    LOGD("end backup_function");
}
