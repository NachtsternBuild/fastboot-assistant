/**
* flash_data.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// function to flash metadata.img
void metadata_img(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, "metadata", NULL, "metadata.img", NULL);
}

// function to flash metadata.img (heimdall)
void metadata_img_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, "METADATA", "metadata.img");
}

// function to flash userdata.img
void userdata_img(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, "userdata", NULL, "userdata.img", NULL);
}

// function to flash userdata.img (heimdall)
void userdata_img_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, "userdata", "userdata.img");
}

// function to set up button labels based on the language
void set_button_labels_flash_data(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Metadata"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Metadata (heimdall)"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Userdata"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("Userdata (heimdall)"), sizeof(labels[3]));
    g_strlcpy(labels[4], _("Back"), sizeof(labels[4]));
}

/* main function - flash_data */
void flash_data(GtkWidget *widget, gpointer stack)
{
	LOGD("flash_data");
	    
    char labels[5][30];  // labels for the button 
    set_button_labels_flash_data(labels);  // for both languages
    
    GtkWidget *flash_data = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(flash_data, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(flash_data, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button_icon_position("drive-harddisk-system-symbolic", labels[0], G_CALLBACK(metadata_img), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_button_icon_position("drive-harddisk-system-symbolic", labels[1], G_CALLBACK(metadata_img_heimdall), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn3 = create_button_icon_position("drive-harddisk-system-symbolic", labels[2], G_CALLBACK(userdata_img), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn4 = create_button_icon_position("drive-harddisk-system-symbolic", labels[3], G_CALLBACK(userdata_img_heimdall), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[4], G_CALLBACK(flash_GUI), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    // line 1
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    // line 2
    gtk_grid_attach(GTK_GRID(grid), btn3, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn4, 1, 1, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(flash_data), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(flash_data), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "flash_data")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), flash_data, "flash_data");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "flash_data");
            
    LOGD("end flash_data");
}
