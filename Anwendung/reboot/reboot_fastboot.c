/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              reboot_fastboot				 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main program */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

#define MAX_BUFFER_SIZE 256

// reboot to bootloader from adb
static void reboot_from_adb(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("reboot_from_adb");
    const char *message = strcmp(language, "de") == 0 ? "Beachten sie, dass USB-Debugging aktiviert ist in den Entwickleroptionen!": "Please note that USB debugging is activated in the developer options!";
    show_message(message);
    
    char *device_command = adb_command();
    char command[256];
    snprintf(command, sizeof(command), "%s -d reboot bootloader", device_command);
    command_with_spinner(command);
    free(device_command);
    // this is the old command
    // system("adb reboot bootloader");
    LOG_INFO("end reboot_from_adb");
}

// reboot to bootloader from fastboot
static void reboot_from_fastboot(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("reboot_from_fastboot");
    const char *message = strcmp(language, "de") == 0 ? "Beachten sie, dass sich ihr Gerät im Fastboot-Modus befindet!" : "Please note that your device is in fastboot mode!";
    show_message(message);
    
    char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot bootloader", device_command);
    command_with_spinner(command);
    free(device_command);
    LOG_INFO("end reboot_from_fastboot");
}
	
// start help-function
static void fastboot_help(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("fastboot_help");
    const char *message = strcmp(language, "de") == 0 ? "Beachten sie, dass sich ihr Gerät im Fastboot-Modus befindet!" : "Please note that your device is in fastboot mode!";
    show_message(message);
    
    char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s help", device_command);
    open_terminal_by_desktop(command);
    free(device_command);
    LOG_INFO("end fastboot_help");
}

// get bootloader variablen-function
static void list_bootloader_var(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("list_bootloader_var");
    const char *message = strcmp(language, "de") == 0 ? "Beachten sie, dass sich ihr Gerät im Fastboot-Modus befindet!" : "Please note that your device is in fastboot mode!";
    show_message(message);
    
    char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s getvar all", device_command);
    open_terminal_by_desktop(command);
    free(device_command);
    LOG_INFO("end list_bootloader_var");
}

// Function to set up button labels based on the language
void set_button_labels_reboot_fast(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Restart ADB");
        strcpy(labels[1], "Restarting Fastboot");
        strcpy(labels[2], "Fastboot help");
        strcpy(labels[3], "Bootloader variables");
        strcpy(labels[4], "Back");
    } 
    
    else 
    {
        strcpy(labels[0], "Neustart von ADB");
        strcpy(labels[1], "Neustart von Fastboot");
        strcpy(labels[2], "Fastboot Hilfe");
        strcpy(labels[3], "Bootloader Variablen");
        strcpy(labels[4], "Zurück");
    }
}

/* main function - reboot_fastboot */
void reboot_fastboot(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("reboot_fastboot");

    apply_language();
    
    char labels[5][30];  // labels for the button 
    set_button_labels_reboot_fast(labels);  // for both languages
    
    GtkWidget *reboot_fastboot = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(reboot_fastboot, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(reboot_fastboot, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(reboot_from_adb), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(reboot_from_fastboot), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(fastboot_help), stack);
    GtkWidget *btn3 = create_nav_button(labels[3], G_CALLBACK(list_bootloader_var), stack);
    GtkWidget *btn_back = create_nav_button(labels[4], G_CALLBACK(reboot_GUI), stack);

    // add the button to the grid
    // line 1
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    // line 2
    gtk_grid_attach(GTK_GRID(grid), btn3, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn4, 1, 1, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(reboot_fastboot), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(reboot_fastboot), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "reboot_fastboot")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), reboot_fastboot, "reboot_fastboot");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "reboot_fastboot");

    LOG_INFO("end reboot_fastboot");
}
