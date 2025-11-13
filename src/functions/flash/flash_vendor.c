/**
* flash_vendor.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// function to flash vendor.img on only-a-devices
void vendor_on_a(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, "vendor", NULL, "vendor.img", NULL);
}

// function to flash vendor.img (a/b-devices)
void vendor_on_ab(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, "vendor_a", "vendor_b", "vendor.img", NULL);
}

// function to flash vendor_boot.img (only-a-devices)
void vendor_boot_on_a(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, "vendor_boot", NULL, "vendor_boot.img", NULL);
}

// function to flash vendor_boot.img (a/b-devices)
void vendor_boot_on_ab(GtkWidget *widget, gpointer stack)
{
    flash_image(widget, "vendor_boot_a", "vendor_boot_b", "vendor_boot.img", NULL);
}

// function to flash boot.img (heimdall)
void vendor_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, "VENDOR", "vendor.img");
}

// function to flash vendor_kernel_boot
void vendor_kernel_boot(GtkWidget *widget, gpointer stack)
{
	flash_image(widget, "vendor_kernel_boot", NULL, "vendor_kernel_boot.img", NULL);
}

// function to flash init_boot.img (heimdall)
void vendor_boot_heimdall(GtkWidget *widget, gpointer stack)
{
    flash_heimdall(widget, "VENDOR_BOOT", "vendor_boot.img");
}

// function to flash vendor_kernel_boot (heimdall)
void vendor_kernel_boot_heimdall(GtkWidget *widget, gpointer stack)
{
	flash_heimdall(widget, "VENDOR_KERNEL_BOOT", "vendor_kernel_boot.img");
}

// function to set up button labels based on the language
void set_button_labels_flash_vendor(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Vendor"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Vendor (a/b"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Vendor (heimdall)"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("vendor_boot"), sizeof(labels[3]));
    g_strlcpy(labels[4], _("vendor_boot (a/b)"), sizeof(labels[4]));
    g_strlcpy(labels[5], _("vendor_boot (heimdall)"), sizeof(labels[5]));
    g_strlcpy(labels[6], _("vendor_kernel_boot"), sizeof(labels[4]));
    g_strlcpy(labels[7], _("vendor_kernel_boot (heimdall)"), sizeof(labels[5]));
    g_strlcpy(labels[8], _("Back"), sizeof(labels[6]));
}

// main function
void flash_vendor(GtkWidget *widget, gpointer stack)
{
	LOGD("flash_vendor");
    
    char labels[9c][30];  // labels for the button 
    set_button_labels_flash_vendor(labels);  // for both languages
    
    GtkWidget *flash_vendor = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(flash_vendor, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(flash_vendor, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button(labels[0], G_CALLBACK(vendor_on_a), stack);
    GtkWidget *btn2 = create_button(labels[1], G_CALLBACK(vendor_on_ab), stack);
    GtkWidget *btn3 = create_button(labels[2], G_CALLBACK(vendor_heimdall), stack);
    GtkWidget *btn4 = create_button(labels[3], G_CALLBACK(vendor_boot_on_a), stack);
    GtkWidget *btn5 = create_button(labels[4], G_CALLBACK(vendor_boot_on_ab), stack);
    GtkWidget *btn6 = create_button(labels[5], G_CALLBACK(vendor_boot_heimdall), stack);
    GtkWidget *btn7 = create_button(labels[6], G_CALLBACK(vendor_kernel_boot), stack);
    GtkWidget *btn8 = create_button(labels[7], G_CALLBACK(vendor_kernel_boot_heimdall), stack);
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
    gtk_box_append(GTK_BOX(flash_vendor), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(flash_vendor), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "flash_vendor")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), flash_vendor, "flash_vendor");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "flash_vendor");
        
    LOGD("end flash_vendor");
}
