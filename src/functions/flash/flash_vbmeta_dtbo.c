/**
* flash_vbmeta_dtbo.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// button handler functions
// function to flash vbmeta.img on only-a-devices
void vbmeta_on_a(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, "vbmeta_a", NULL, "vbmeta.img", "--disable-verity --disable-verification");
}

// function to flash vbmeta.img (a/b-devices)
void vbmeta_on_ab(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, "vbmeta_a", "vbmeta_b", "vbmeta.img", "--disable-verity --disable-verification");
}

// function to flash dtbo.img (only-a-devices)
void dtbo_on_a(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, "dtbo", NULL, "dtbo.img", NULL);
}

// function to flash dtbo.img (a/b-devices)
void dtbo_on_ab(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, "dtbo_a", "dtbo_b", "dtbo.img", NULL);
}

// function to flash vbmeta.img (heimdall)
void vbmeta_img_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, "VBMETA", "vbmeta.img");
}

// function to flash dtbo.img (heimdall)
void dtbo_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, "DTBO", "dtbo.img");
}

// function to set up button labels based on the language
void set_button_labels_flash_vbmeta_dtbo(char labels[][30]) 
{
    g_strlcpy(labels[0], _("vbmeta"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("vbmeta (a/b)"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("vbmeta (heimdall)"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("dtbo"), sizeof(labels[3]));
    g_strlcpy(labels[4], _("dtbo (a/b)"), sizeof(labels[4]));
    g_strlcpy(labels[5], _("dtbo (heimdall)"), sizeof(labels[5]));
    g_strlcpy(labels[6], _("Back"), sizeof(labels[6]));
}

/* main function - flash_vbmeta_dtbo */
void flash_vbmeta_dtbo(GtkWidget *widget, gpointer stack)
{
	LOGD("flash_vbmeta_dtbo");
	       
    char labels[7][30];  // labels for the button 
    set_button_labels_flash_vbmeta_dtbo(labels);  // for both languages
    
    GtkWidget *flash_vbmeta_dtbo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(flash_vbmeta_dtbo, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(flash_vbmeta_dtbo, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button(labels[0], G_CALLBACK(vbmeta_on_a), stack);
    GtkWidget *btn2 = create_button(labels[1], G_CALLBACK(vbmeta_on_ab), stack);
    GtkWidget *btn3 = create_button(labels[2], G_CALLBACK(vbmeta_img_heimdall), stack);
    GtkWidget *btn4 = create_button(labels[3], G_CALLBACK(dtbo_on_a), stack);
    GtkWidget *btn5 = create_button(labels[4], G_CALLBACK(dtbo_on_ab), stack);
    GtkWidget *btn6 = create_button(labels[5], G_CALLBACK(dtbo_heimdall), stack);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[6], G_CALLBACK(flash_GUI), stack, GTK_ALIGN_CENTER);

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
    gtk_box_append(GTK_BOX(flash_vbmeta_dtbo), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(flash_vbmeta_dtbo), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "flash_vbmeta_dtbo")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), flash_vbmeta_dtbo, "flash_vbmeta_dtbo");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "flash_vbmeta_dtbo");
        
    LOGD("end flash_vbmeta_dtbo");
}
