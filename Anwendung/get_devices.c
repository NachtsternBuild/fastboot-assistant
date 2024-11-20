/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - get_devices			 *
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
#include <string.h> 
#include "program_functions.h"
#include "function_header.h"
#include "language_check.h"

#define MAX_BUFFER_SIZE 256

// Callback functions for each button
// check connected adb devices
static void get_adb(GtkWidget *widget, gpointer data) 
{
    g_print("Log: Start get_adb\n");
    char *device_command = adb_command();
    char command[MAX_BUFFER_SIZE];
    snprintf(command, MAX_BUFFER_SIZE, "%s devices", device_command);
    connected_devices(command, "Geräte (ADB)");
    free(device_command);
    g_print("Log: End of get_adb\n");
}

// check connected fastboot devices
static void get_fastboot(GtkWidget *widget, gpointer data) 
{
    g_print("Log: Start get_fastboot");
    char *device_command = fastboot_command();
    char command[MAX_BUFFER_SIZE];
    snprintf(command, MAX_BUFFER_SIZE, "%s devices", device_command);
    connected_devices(command, "Geräte (fastboot)");
    free(device_command);
    g_print("Log: End of get_fastboot\n");
}

static void bootloader_status_adb()
{
	g_print("Log: Start bootloader_status_adb\n");
	char *device_command = adb_command();
    char command[MAX_BUFFER_SIZE];
    snprintf(command, MAX_BUFFER_SIZE, "%s shell getprop ro.boot.flash.locked", device_command);
    connected_devices(command, "Bootloader Status (ADB)");
    free(device_command);
    g_print("Log: End of bootloader_status_adb\n");
}

static void bootloader_status_fastboot()
{
	g_print("Log: Start bootloader_status_fastboot\n");
	char *device_command = fastboot_command();
    char command[MAX_BUFFER_SIZE];
    snprintf(command, MAX_BUFFER_SIZE, "%s getvar unlocked", device_command);
    connected_devices(command, "Bootloader Status (fastboot)");
    free(device_command);
    g_print("Log: End of bootloader_status_fastboot\n");
}

// Function to set up button labels based on the language
void set_button_labels_get_devices(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Devices in ADB");
        strcpy(labels[1], "Devices in Fastboot");
        strcpy(labels[2], "Bootloader status (ADB)");
        strcpy(labels[3], "Bootloader status (fastboot)");
    } 
    
    else 
    {
        strcpy(labels[0], "Geräte in ADB");
        strcpy(labels[1], "Geräte in Fastboot");
        strcpy(labels[2], "Bootloader Status (ADB)");
        strcpy(labels[3], "Bootloader Status (fastboot)");
    }
}

/* main function of get_devices*/
void get_devices(int argc, char *argv[]) 
{
	GtkWidget *window, *grid, *button;
    char button_labels[4][30];
    
    gtk_init();
    apply_theme();
    apply_language();
    set_button_labels_get_devices(button_labels);
    
    window = gtk_window_new();
    const char *get_devices_window = strcmp(language, "de") == 0 ? "Geräte" : "devices";
    gtk_window_set_title(GTK_WINDOW(window), get_devices_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);
    
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), grid);

    for (int i = 0; i < 4; i++) 
    {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 2, i / 2, 1, 1);
		
		switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(get_adb), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(get_fastboot), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(bootloader_status_adb), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(bootloader_status_fastboot), NULL);
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
    g_main_loop_run(loop); 
    
    g_print("Log: End of get_devices\n");
}
