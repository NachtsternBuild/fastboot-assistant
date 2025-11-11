/**
* flash_recovery.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// Button handler functions
// function to flash recovery.img on only-a-devices
void recovery_img(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, "recovery", NULL, "recovery.img", NULL);
}

// function to flash recovery.img (heimdall)
void recovery_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, "RECOVERY", "recovery.img");
}

// Function to set up button labels based on the language
void set_button_labels_flash_recovery(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Recovery"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Recovery (heimdall)"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Back"), sizeof(labels[2]));
}

/* main function - flash_recovery */
void flash_recovery(GtkWidget *widget, gpointer stack)
{
    LOGD("flash_recovery");
        
    char labels[3][30];  // labels for the button 
    set_button_labels_flash_recovery(labels);  // for both languages
    
    GtkWidget *flash_recovery = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(flash_recovery, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(flash_recovery, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button(labels[0], G_CALLBACK(recovery_img), stack);
    GtkWidget *btn2 = create_button(labels[1], G_CALLBACK(recovery_heimdall), stack);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[2], G_CALLBACK(flash_GUI), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(flash_recovery), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(flash_recovery), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "flash_recovery")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), flash_recovery, "flash_recovery");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "flash_recovery");
	
	LOGD("end flash_recovery");
}
