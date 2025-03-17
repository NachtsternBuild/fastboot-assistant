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
 *      (C) Copyright 2025 Elias Mörz 		 *
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

// callback functions for each button
// check connected adb devices
static void get_adb(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("get_adb");
    char *device_command = adb_command();
    char command[MAX_BUFFER_SIZE];
    snprintf(command, MAX_BUFFER_SIZE, "%s devices", device_command);
    connected_devices(command, "Geräte (ADB)");
    free(device_command);
    LOG_INFO("end get_adb");
}

// check connected fastboot devices
static void get_fastboot(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("get_fastboot");
    char *device_command = fastboot_command();
    char command[MAX_BUFFER_SIZE];
    snprintf(command, MAX_BUFFER_SIZE, "%s devices", device_command);
    connected_devices(command, "Geräte (fastboot)");
    free(device_command);
    LOG_INFO("end get_fastboot");
}

// get bootloader status
static void bootloader_status_adb(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("bootloader_status_adb");
	char *device_command = adb_command();
    char command[MAX_BUFFER_SIZE];
    snprintf(command, MAX_BUFFER_SIZE, "%s shell getprop ro.boot.flash.locked", device_command);
    connected_devices(command, "Bootloader Status (ADB)");
    free(device_command);
    LOG_INFO("end bootloader_status_adb");
}

// get bootloader status
static void bootloader_status_fastboot(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("bootloader_status_fastboot");
	char *device_command = fastboot_command();
    char command[MAX_BUFFER_SIZE];
    snprintf(command, MAX_BUFFER_SIZE, "%s getvar unlocked", device_command);
    connected_devices(command, "Bootloader Status (fastboot)");
    free(device_command);
    LOG_INFO("bootloader_status_fastboot");
}

// function to set up button labels based on the language
void set_button_labels_get_devices(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Devices in ADB");
        strcpy(labels[1], "Devices in Fastboot");
        strcpy(labels[2], "Bootloader status (ADB)");
        strcpy(labels[3], "Bootloader status (fastboot)");
        strcpy(labels[4], "Back to Home");
    } 
    
    else 
    {
        strcpy(labels[0], "Geräte in ADB");
        strcpy(labels[1], "Geräte in Fastboot");
        strcpy(labels[2], "Bootloader Status (ADB)");
        strcpy(labels[3], "Bootloader Status (fastboot)");
        strcpy(labels[4], "Zurück zur Startseite");
    }
}

/* main function - get_devices */
void get_devices(GtkWidget *widget, gpointer stack) 
{ 
    LOG_INFO("get_devices");
    apply_language();
    
    char labels[5][30];  // labels for the button 
    set_button_labels(labels);  // for both languages
    
    // create box for get_devices
    GtkWidget *get_devices = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(get_devices, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(get_devices, GTK_ALIGN_CENTER);
	
	// create a grid
    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
	
	// create the button for get_devices
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(get_adb), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(get_fastboot), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(bootloader_status_adb), stack);
    GtkWidget *btn4 = create_nav_button(labels[3], G_CALLBACK(bootloader_status_fastboot), stack);
    GtkWidget *btn_back = create_nav_button(labels[4], G_CALLBACK(show_home_page), stack);
	
    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn4, 1, 1, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(get_devices), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(get_devices), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "get_devices")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), sub_page_1, "get_devices");
    }
    
    LOG_INFO("get_devices");
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "get_devices");
	LOG_INFO("end get_devices");
}
