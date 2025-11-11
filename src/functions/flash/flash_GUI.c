/**
* flash_GUI.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// function to set up button labels based on the language
void set_button_labels_flash_GUI(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Flash Recovery"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Flash Boot"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Flash Vendor"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("Flash payload.zip"), sizeof(labels[3]));
    g_strlcpy(labels[4], _("Flash System"), sizeof(labels[4]));
    g_strlcpy(labels[5], _("Flash vbmeta/dtbo"), sizeof(labels[5]));
    g_strlcpy(labels[6], _("Flash Preloader"), sizeof(labels[6]));
    g_strlcpy(labels[7], _("Flash Nutzerdaten"), sizeof(labels[7]));
    g_strlcpy(labels[8], _("Flash Other Images"), sizeof(labels[8]));
    g_strlcpy(labels[9], _("Back to Home"), sizeof(labels[9]));
}


/* main function - flash_GUI*/
void flash_GUI(GtkWidget *widget, gpointer stack) 
{   
    LOGD("flash_GUI");
    char labels[10][30];  // labels for the button 
    set_button_labels_flash_GUI(labels);  // for both languages
    
    GtkWidget *flash_GUI = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(flash_GUI, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(flash_GUI, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button(labels[0], G_CALLBACK(flash_recovery), stack);
    GtkWidget *btn2 = create_button(labels[1], G_CALLBACK(flash_boot), stack);
    GtkWidget *btn3 = create_button(labels[2], G_CALLBACK(flash_vendor), stack);
    GtkWidget *btn4 = create_button(labels[3], G_CALLBACK(flash_payload), stack);
    GtkWidget *btn5 = create_button(labels[4], G_CALLBACK(flash_system), stack);
    GtkWidget *btn6 = create_button(labels[5], G_CALLBACK(flash_vbmeta_dtbo), stack);
    GtkWidget *btn7 = create_button(labels[6], G_CALLBACK(flash_preloader_super), stack);
    GtkWidget *btn8 = create_button(labels[7], G_CALLBACK(flash_data), stack);
    GtkWidget *btn9 = create_button(labels[8], G_CALLBACK(flash_others), stack);
	GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[9], G_CALLBACK(show_home_page), stack, GTK_ALIGN_CENTER);

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
    
    LOGD("end flash_GUI");
}
