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
 *      (C) Copyright 2024 Elias Mörz 		 *
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

// Callback functions for each button
// remove the boot partition
static void remove_boot(GtkWidget *widget, gpointer data) 
{
    g_print("Log: remove_boot\n");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s delete-logical-partition boot_a && %s delete-logical-partition boot_b", device_command, device_command);
    
    g_print("Log: Run: %s\n", partition_command);
    command_with_spinner(partition_command);
    g_print("Log: end remove_boot\n");
}

// remove the vendor partition
static void remove_vendor(GtkWidget *widget, gpointer data) 
{
    g_print("Log: remove_vendor\n");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s delete-logical-partition vendor_a && %s delete-logical-partition vendor_b", device_command, device_command);
    
	g_print("Log: Run: %s\n", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    g_print("Log: end remove_vendor\n");
}

// remove the system partition
static void remove_system(GtkWidget *widget, gpointer data) 
{
    g_print("Log: remove_system\n");
    const char *message = strcmp(language, "de") == 0 ?  "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s delete-logical-partition system_a && %s delete-logical-partition system_b", device_command, device_command);
    
	g_print("Log: Run: %s\n", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    g_print("Log: end remove_system\n");
}

// resize of the boot partition
static void resize_boot(GtkWidget *widget, gpointer data) 
{
    g_print("Log: resize_boot\n");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);
 
    char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s resize-logical-partition boot_a 400000000 && %s resize-logical-partition boot_b 400000000", device_command, device_command);
    
    g_print("Führe aus: %s", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    g_print("Log: end resize_boot\n");
}

// resize of the vendor partition
static void resize_vendor(GtkWidget *widget, gpointer data) 
{
    g_print("Log: resize_vendor\n");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s resize-logical-partition vendor_a 900000000 && %s resize-logical-partition vendor_b 900000000", device_command, device_command);
    
	g_print("Log: Run: %s\n", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    g_print("Log: end resize_vendor\n");
}

// resize of the system partition
static void resize_system(GtkWidget *widget, gpointer data) 
{
    g_print("Log: resize_system\n");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s resize-logical-partition system_a 7500000000 && %s resize-logical-partition system_b 7500000000", device_command, device_command);
    
	g_print("Log: Run: %s\n", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    g_print("Log: end resize_system\n");
}

// create boot partition
static void create_boot(GtkWidget *widget, gpointer data) 
{
    g_print("Log: create_boot \n");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s create-logical-partition boot_a 400000000 && %s create-logical-partition boot_b 400000000", device_command, device_command);
    
	g_print("Log: Run: %s\n", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    g_print("Log: end create_boot\n");
}

// create vendor partition
static void create_vendor(GtkWidget *widget, gpointer data) 
{
    g_print("Log: create_vendor\n");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);

    char *device_command = fastboot_command();    
    snprintf(partition_command, sizeof(partition_command), "%s create-logical-partition vendor_a 900000000 && %s create-logical-partition vendor_b 900000000", device_command, device_command);
    
	g_print("Log: Run: %s\n", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    g_print("Log: end create_vendor\n");
}

// create system partition
static void create_system(GtkWidget *widget, gpointer data) 
{
    g_print("Log: create_system\n");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);
    
    char *device_command = fastboot_command();
    snprintf(partition_command, sizeof(partition_command), "%s create-logical-partition system_a 7500000000 && %s create-logical-partition system_b 7500000000", device_command, device_command);
    
	g_print("Log: Run: %s\n", partition_command);
    command_with_spinner(partition_command);
    free(device_command);
    g_print("Log: end create_system\n");
}

// Function to set up button labels based on the language
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

/* main function of partitions*/
void partitions(int argc, char *argv[]) 
{
    g_print("Log: partitions\n");
    GtkWidget *window, *grid, *button;
    char button_labels[9][30];
    
    gtk_init();
    apply_theme();
    apply_language();
    set_button_labels_partitions(button_labels);
    
    window = gtk_window_new();
    const char *preflash_window = strcmp(language, "de") == 0 ? "Partitionen" : "Partitions";
    gtk_window_set_title(GTK_WINDOW(window), preflash_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);
    
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), grid);
    
    for (int i = 0; i < 3; i++) 
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
    
    // free the provider
	if (provider != NULL) 
	{
	    g_object_unref(provider);
	}
	
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop); // GTK-Hauptschleife starten
    
    g_print("Log: end partitions\n");
}

