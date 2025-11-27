/**
* flash_preloader_super.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// function to flash preloader.bin on only-a-devices
void preloader_bin_on_a(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, "preloader", NULL, "preloader.bin", NULL);
}

// function to flash preloader.bin (a/b-devices)
void preloader_bin_on_ab(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, "preloader_a", "preloader_b", "preloader.bin", NULL);
}

// function to flash preloader.img (only-a-devices)
void preloader_img_on_a(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, "preloader", NULL, "preloader.img", NULL);
}

// function to flash preloader.img (a/b-devices)
void preloader_img_on_ab(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, "preloader_a", "preloader_b", "preloader.img", NULL);
}

// function to flash super.img
void super_img(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, "super", NULL, "super.img", NULL);
}

// function to flash preloader.bin (heimdall)
void preloader_bin_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, "PRELOADER", "preloader.bin");
}

// function to flash preloader.img (heimdall)
void preloader_img_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, "PRELOADER", "preloader.img");
}

// function to flash super.img (heimdall)
void super_img_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, "SUPER", "super.img");
}

// function to set up button labels based on the language
void set_button_labels_flash_preloader_super(char labels[][30]) 
{
    g_strlcpy(labels[0], _("preloader.bin (only-a)"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("preloader.bin (a/b)"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("preloader.img (only-a)"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("preloader.img (a/b)"), sizeof(labels[3]));
    g_strlcpy(labels[4], _("preloader.bin (heimdall)"), sizeof(labels[4]));
    g_strlcpy(labels[5], _("preloader.img (heimdall)"), sizeof(labels[5]));
    g_strlcpy(labels[6], _("super.img"), sizeof(labels[6]));
    g_strlcpy(labels[7], _("super.img (heimdall)"), sizeof(labels[7]));
    g_strlcpy(labels[8], _("Back"), sizeof(labels[8]));
}

/* main function - flash_preloader_super */
void flash_preloader_super(GtkWidget *widget, gpointer stack)
{
	LOGD("flash_preloader_super");
	    
    char labels[9][30];  // labels for the button 
    set_button_labels_flash_preloader_super(labels);  // for both languages
    
    GtkWidget *flash_preloader_super = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(flash_preloader_super, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(flash_preloader_super, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button_icon_position("drive-harddisk-system-symbolic", labels[0], G_CALLBACK(preloader_bin_on_a), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_button_icon_position("drive-harddisk-system-symbolic", labels[1], G_CALLBACK(preloader_bin_on_ab), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn3 = create_button_icon_position("drive-harddisk-system-symbolic", labels[2], G_CALLBACK(preloader_img_on_a), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn4 = create_button_icon_position("drive-harddisk-system-symbolic", labels[3], G_CALLBACK(preloader_img_on_ab), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn5 = create_button_icon_position("drive-harddisk-system-symbolic", labels[4], G_CALLBACK(preloader_bin_heimdall), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn6 = create_button_icon_position("drive-harddisk-system-symbolic", labels[5], G_CALLBACK(preloader_img_heimdall), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn7 = create_button_icon_position("drive-harddisk-system-symbolic", labels[6], G_CALLBACK(super_img), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn8 = create_button_icon_position("drive-harddisk-system-symbolic", labels[7], G_CALLBACK(super_img_heimdall), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[8], G_CALLBACK(flash_GUI), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    // line 1
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    // line 2
    gtk_grid_attach(GTK_GRID(grid), btn3, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn4, 1, 1, 1, 1);
    // line 3
    gtk_grid_attach(GTK_GRID(grid), btn5, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn6, 1, 2, 1, 1);
    // line 4 
    gtk_grid_attach(GTK_GRID(grid), btn7, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn8, 1, 3, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(flash_preloader_super), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(flash_preloader_super), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "flash_preloader_super")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), flash_preloader_super, "flash_preloader_super");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "flash_preloader_super");
         
    LOGD("end flash_preloader_super");
}
