/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - partitions				 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */
 
/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"
#include "function_header.h"

#define MAX_BUFFER_SIZE 256

char partition_command[2048];

// callback functions for each button
// remove the boot partition
static void remove_boot(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("remove_boot");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    auto_free char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s delete-logical-partition boot_a && %s delete-logical-partition boot_b", device_command, device_command);
    
    LOG_INFO("Run: %s", partition_command);
    command_with_spinner(partition_command);
    LOG_INFO("end remove_boot");
}

// remove the vendor partition
static void remove_vendor(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("remove_vendor");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    auto_free char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s delete-logical-partition vendor_a && %s delete-logical-partition vendor_b", device_command, device_command);
    
	LOG_INFO("Run: %s", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    LOG_INFO("end remove_vendor");
}

// remove the system partition
static void remove_system(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("remove_system");
    const char *message = strcmp(language, "de") == 0 ?  "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    auto_free char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s delete-logical-partition system_a && %s delete-logical-partition system_b", device_command, device_command);
    
	LOG_INFO("Run: %s", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    LOG_INFO("end remove_system");
}

// resize of the boot partition
static void resize_boot(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("resize_boot");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);
 
    auto_free char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s resize-logical-partition boot_a 400000000 && %s resize-logical-partition boot_b 400000000", device_command, device_command);
    
    LOG_INFO("Run: %s", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    LOG_INFO("end resize_boot");
}

// resize of the vendor partition
static void resize_vendor(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("resize_vendor");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    auto_free char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s resize-logical-partition vendor_a 900000000 && %s resize-logical-partition vendor_b 900000000", device_command, device_command);
    
	LOG_INFO("Run: %s", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    LOG_INFO("end resize_vendor");
}

// resize of the system partition
static void resize_system(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("resize_system");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    auto_free char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s resize-logical-partition system_a 7500000000 && %s resize-logical-partition system_b 7500000000", device_command, device_command);
    
	LOG_INFO("Run: %s", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    LOG_INFO("end resize_system");
}

// create boot partition
static void create_boot(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("create_boot");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    auto_free char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s create-logical-partition boot_a 400000000 && %s create-logical-partition boot_b 400000000", device_command, device_command);
    
	LOG_INFO("Run: %s", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    LOG_INFO("end create_boot");
}

// create vendor partition
static void create_vendor(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("create_vendor");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    auto_free char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s create-logical-partition vendor_a 900000000 && %s create-logical-partition vendor_b 900000000", device_command, device_command);
    
	LOG_INFO("Run: %s", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    LOG_INFO("end create_vendor");
}

// create system partition
static void create_system(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("create_system");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);
    
    auto_free char *device_command = fastboot_command();
    snprintf(partition_command, sizeof(partition_command), "%s create-logical-partition system_a 7500000000 && %s create-logical-partition system_b 7500000000", device_command, device_command);
    
	LOG_INFO("Run: %s", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    LOG_INFO("end create_system");
}

// function to set up button labels based on the language
void set_button_labels_partitions(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Delete Boot");
        strcpy(labels[1], "Delete Vendor");
        strcpy(labels[2], "Delete System");
        strcpy(labels[3], "Resize Boot");
        strcpy(labels[4], "Resize Vendor");
        strcpy(labels[5], "Resize System");
        strcpy(labels[6], "Create Boot");
        strcpy(labels[7], "Create Vendor");
        strcpy(labels[8], "Create System");
        strcpy(labels[9], "Back");
    } 
    
    else 
    {
        strcpy(labels[0], "Lösche Boot");
        strcpy(labels[1], "Lösche Vendor");
        strcpy(labels[2], "Lösche System");
        strcpy(labels[3], "Resize Boot");
        strcpy(labels[4], "Resize Vendor");
        strcpy(labels[5], "Resize System");
        strcpy(labels[6], "Erstelle Boot");
        strcpy(labels[7], "Erstelle Vendor");
        strcpy(labels[8], "Erstelle System");
        strcpy(labels[9], "Zurück");
    }
}

/* main function - partitions*/
void partitions(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("partitions");
       
    apply_language();
    
    char button_labels[10][30];  // labels for the button 
    set_button_labels_partitions(labels);  // for both languages
    
    GtkWidget *partitions = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(partitions, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(partitions, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(remove_boot), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(remove_vendor), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(remove_system), stack);
    GtkWidget *btn4 = create_nav_button(labels[3], G_CALLBACK(resize_boot), stack);
    GtkWidget *btn5 = create_nav_button(labels[4], G_CALLBACK(resize_vendor), stack);
    GtkWidget *btn6 = create_nav_button(labels[5], G_CALLBACK(resize_system), stack);
    GtkWidget *btn7 = create_nav_button(labels[6], G_CALLBACK(create_boot), stack);
    GtkWidget *btn8 = create_nav_button(labels[7], G_CALLBACK(create_vendor), stack);
    GtkWidget *btn9 = create_nav_button(labels[8], G_CALLBACK(create_system), stack);
    GtkWidget *btn_back = create_nav_button(labels[9], G_CALLBACK(preflash_GUI), stack);

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
    gtk_box_append(GTK_BOX(partitions), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(partitions), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "partitions")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), partitions, "partitions");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "partitions");
        
    LOG_INFO("end partitions");
}

