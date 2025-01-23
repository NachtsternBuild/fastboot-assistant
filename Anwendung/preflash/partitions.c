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
static void remove_boot(GtkWidget *widget, gpointer data) 
{
    LOG_INFO("remove_boot");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s delete-logical-partition boot_a && %s delete-logical-partition boot_b", device_command, device_command);
    
    LOG_INFO("Run: %s", partition_command);
    command_with_spinner(partition_command);
    LOG_INFO("end remove_boot");
}

// remove the vendor partition
static void remove_vendor(GtkWidget *widget, gpointer data) 
{
    LOG_INFO("remove_vendor");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s delete-logical-partition vendor_a && %s delete-logical-partition vendor_b", device_command, device_command);
    
	LOG_INFO("Run: %s", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    LOG_INFO("end remove_vendor");
}

// remove the system partition
static void remove_system(GtkWidget *widget, gpointer data) 
{
    LOG_INFO("remove_system");
    const char *message = strcmp(language, "de") == 0 ?  "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s delete-logical-partition system_a && %s delete-logical-partition system_b", device_command, device_command);
    
	LOG_INFO("Run: %s", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    LOG_INFO("end remove_system");
}

// resize of the boot partition
static void resize_boot(GtkWidget *widget, gpointer data) 
{
    LOG_INFO("resize_boot");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);
 
    char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s resize-logical-partition boot_a 400000000 && %s resize-logical-partition boot_b 400000000", device_command, device_command);
    
    LOG_INFO("Run: %s", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    LOG_INFO("end resize_boot");
}

// resize of the vendor partition
static void resize_vendor(GtkWidget *widget, gpointer data) 
{
    LOG_INFO("resize_vendor");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s resize-logical-partition vendor_a 900000000 && %s resize-logical-partition vendor_b 900000000", device_command, device_command);
    
	LOG_INFO("Run: %s", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    LOG_INFO("end resize_vendor");
}

// resize of the system partition
static void resize_system(GtkWidget *widget, gpointer data) 
{
    LOG_INFO("resize_system");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s resize-logical-partition system_a 7500000000 && %s resize-logical-partition system_b 7500000000", device_command, device_command);
    
	LOG_INFO("Run: %s", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    LOG_INFO("end resize_system");
}

// create boot partition
static void create_boot(GtkWidget *widget, gpointer data) 
{
    LOG_INFO("create_boot");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s create-logical-partition boot_a 400000000 && %s create-logical-partition boot_b 400000000", device_command, device_command);
    
	LOG_INFO("Run: %s", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    LOG_INFO("end create_boot");
}

// create vendor partition
static void create_vendor(GtkWidget *widget, gpointer data) 
{
    LOG_INFO("create_vendor");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s create-logical-partition vendor_a 900000000 && %s create-logical-partition vendor_b 900000000", device_command, device_command);
    
	LOG_INFO("Run: %s", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    LOG_INFO("end create_vendor");
}

// create system partition
static void create_system(GtkWidget *widget, gpointer data) 
{
    LOG_INFO("create_system");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);
    
    char *device_command = fastboot_command();
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
    }
}

/* main function - partitions*/
void partitions(int argc, char *argv[]) 
{
    LOG_INFO("partitions");
    GtkWidget *window, *grid, *button;
    char button_labels[9][30];
    
    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_partitions(button_labels);
    
    window = gtk_window_new();
    const char *preflash_window = strcmp(language, "de") == 0 ? "Partitionen" : "Partitions";
    gtk_window_set_title(GTK_WINDOW(window), preflash_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);
    
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), grid);
    
    for (int i = 0; i < 9; i++) 
    {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);
        
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(remove_boot), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(remove_vendor), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(remove_system), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(resize_boot), NULL);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(resize_vendor), NULL);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(resize_system), NULL);
                break;
            case 6:
            	g_signal_connect(button, "clicked", G_CALLBACK(create_boot), NULL);
            	break;
            case 7:
            	g_signal_connect(button, "clicked", G_CALLBACK(create_vendor), NULL);
            	break;
            case 8:
            	g_signal_connect(button, "clicked", G_CALLBACK(create_system), NULL);
            	break;
        }
    }
	
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop);
    
    // free the provider
    if (provider != NULL) 
    {
    	g_object_unref(provider);
    	provider = NULL;
	}

	if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
	
    LOG_INFO("end partitions");
}

