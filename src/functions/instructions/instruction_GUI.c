/**
* instruction_GUI.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// function to set up button labels based on the language
void set_button_labels_instruction_GUI(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Dealing with ADB"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Flashing Images"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Preparations"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("Info"), sizeof(labels[3]));
    g_strlcpy(labels[4], _("Back to Home"), sizeof(labels[4]));
}

/* main function - instruction_GUI */
void instruction_GUI(GtkWidget *widget, gpointer stack) 
{
    LOGD("instruction_GUI");
    
    char labels[5][30];  // labels for the button 
    set_button_labels_instruction_GUI(labels);  // for both languages
    
    GtkWidget *instruction_GUI = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(instruction_GUI, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(instruction_GUI, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
	GtkWidget *btn1 = create_button_icon_position("phone-apple-iphone-symbolic", labels[0], G_CALLBACK(instruction_adb), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_button_icon_position("drive-multidisk-symbolic", labels[1], G_CALLBACK(instruction_flash), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn3 = create_button_icon_position("applications-engineering-symbolic", labels[2], G_CALLBACK(instruction_prepare_flash), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn4 = create_button_icon_position("help-about-symbolic", labels[3], G_CALLBACK(instruction_info), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[4], G_CALLBACK(show_home_page), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    // line 1
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    // line 2
    gtk_grid_attach(GTK_GRID(grid), btn3, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn4, 1, 1, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(instruction_GUI), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(instruction_GUI), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "instruction_GUI")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), instruction_GUI, "instruction_GUI");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "instruction_GUI");
           
    LOGD("end instruction_GUI");
}
