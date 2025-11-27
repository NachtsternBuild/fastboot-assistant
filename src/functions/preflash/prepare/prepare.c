/**
* prepare.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// Function to set up button labels based on the language
void set_button_labels_prepare(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Boot.img"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Recovery.img"), sizeof(labels[0]));
    g_strlcpy(labels[2], _("Vendor.img"), sizeof(labels[0]));
    g_strlcpy(labels[3], _("System.img"), sizeof(labels[0]));
    g_strlcpy(labels[4], _("payload.zip"), sizeof(labels[0]));
    g_strlcpy(labels[5], _("Decompress (xz)"), sizeof(labels[0]));
    g_strlcpy(labels[6], _("Back"), sizeof(labels[0]));
}

/* main function - prepare */
void prepare(GtkWidget *widget, gpointer stack) 
{
    LOGD("prepare");
    
    char labels[7][30];  // labels for the button 
    set_button_labels_prepare(labels);  // for both languages
    
    GtkWidget *prepare = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(prepare, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(prepare, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button_icon_position("x-office-document-symbolic", labels[0], G_CALLBACK(show_file_chooser), (gpointer)rename_boot, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_button_icon_position("x-office-document-symbolic", labels[1], G_CALLBACK(show_file_chooser), (gpointer)rename_recovery, GTK_ALIGN_CENTER);
    GtkWidget *btn3 = create_button_icon_position("x-office-document-symbolic", labels[2], G_CALLBACK(show_file_chooser), (gpointer)rename_vendor, GTK_ALIGN_CENTER);
    GtkWidget *btn4 = create_button_icon_position("x-office-document-symbolic", labels[3], G_CALLBACK(show_file_chooser), (gpointer)rename_system, GTK_ALIGN_CENTER);
    GtkWidget *btn5 = create_button_icon_position("x-office-document-symbolic", labels[4], G_CALLBACK(show_file_chooser), (gpointer)rename_payload, GTK_ALIGN_CENTER);
    GtkWidget *btn6 = create_button_icon_position("network-server-symbolic", labels[5], G_CALLBACK(show_file_chooser), (gpointer)unxz_files, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[6], G_CALLBACK(preflash_GUI), stack, GTK_ALIGN_CENTER);

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
    gtk_box_append(GTK_BOX(prepare), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(prepare), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "prepare")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), prepare, "prepare");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "prepare");
    
    LOGD("end prepare");
}
