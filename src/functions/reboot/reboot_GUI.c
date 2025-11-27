/**
* reboot_GUI.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"


// Function to set up button labels based on the language
void set_button_labels_reboot_GUI(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Reboot Fastboot"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Reboot"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Reboot Recovery"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("Reboot (heimdall)"), sizeof(labels[3]));
    g_strlcpy(labels[4], _("Back to Home"), sizeof(labels[4]));
}

/* main function - reboot_GUI */
void reboot_GUI(GtkWidget *widget, gpointer stack) 
{
	LOGD("reboot_GUI");
	    
    char labels[5][30];  // labels for the button 
    set_button_labels_reboot_GUI(labels);  // for both languages
    
    GtkWidget *reboot_GUI = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(reboot_GUI, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(reboot_GUI, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button_icon_position("system-reboot-symbolic", labels[0], G_CALLBACK(reboot_fastboot), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_button_icon_position("system-reboot-symbolic", labels[1], G_CALLBACK(reboot), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn3 = create_button_icon_position("system-reboot-symbolic", labels[2], G_CALLBACK(reboot_recovery), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn4 = create_button_icon_position("system-reboot-symbolic", labels[3], G_CALLBACK(reboot_heimdall), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[4], G_CALLBACK(show_home_page), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    // line 1
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    // line 2
    gtk_grid_attach(GTK_GRID(grid), btn3, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn4, 1, 1, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(reboot_GUI), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(reboot_GUI), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "reboot_GUI")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), reboot_GUI, "reboot_GUI");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "reboot_GUI");
    
    LOGD("end reboot_GUI");
}
