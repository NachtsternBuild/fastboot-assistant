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
 *      (C) Copyright 2024 Elias Mörz 		 *
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
static void reboot_from_adb(GtkWidget *widget, gpointer data)
{
    g_print("Log: reboot_from_adb\n");
    const char *message = strcmp(language, "de") == 0 ? "Beachten sie, dass USB-Debugging aktiviert ist in den Entwickleroptionen!": "Please note that USB debugging is activated in the developer options!";
    show_message(message);
    
    char *device_command = adb_command();
    char command[256];
    snprintf(command, sizeof(command), "%s -d reboot bootloader", device_command);
    open_terminal_by_desktop(command);
    free(device_command);
    // this is the old command
    // system("adb reboot bootloader");
    g_print("Log: end reboot_from_adb\n");
}

// reboot to bootloader from fastboot
static void reboot_from_fastboot(GtkWidget *widget, gpointer data)
{
    g_print("Log: reboot_from_fastboot\n");
    const char *message = strcmp(language, "de") == 0 ? "Beachten sie, dass sich ihr Gerät im Fastboot-Modus befindet!" : "Please note that your device is in fastboot mode!";
    show_message(message);
    
    char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot bootloader", device_command);
    open_terminal_by_desktop(command);
    free(device_command);
    g_print("Log: end reboot_from_fastboot\n");
}
	
// start help-function
static void fastboot_help(GtkWidget *widget, gpointer data) 
{
    g_print("Log: fastboot_help\n");
    const char *message = strcmp(language, "de") == 0 ? "Beachten sie, dass sich ihr Gerät im Fastboot-Modus befindet!" : "Please note that your device is in fastboot mode!";
    show_message(message);
    
    char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s help", device_command);
    open_terminal_by_desktop(command);
    free(device_command);
    g_print("Log: end fastboot_help\n");
}

// get bootloader variablen-function
static void list_bootloader_var(GtkWidget *widget, gpointer data) 
{
    g_print("Log: list_bootloader_var\n");
    const char *message = strcmp(language, "de") == 0 ? "Beachten sie, dass sich ihr Gerät im Fastboot-Modus befindet!" : "Please note that your device is in fastboot mode!";
    show_message(message);
    
    char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s getvar all", device_command);
    open_terminal_by_desktop(command);
    free(device_command);
    g_print("Log: end list_bootloader_var\n");
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
    } 
    
    else 
    {
        strcpy(labels[0], "Neustart von ADB");
        strcpy(labels[1], "Neustart von Fastboot");
        strcpy(labels[2], "Fastboot Hilfe");
        strcpy(labels[3], "Bootloader Variablen");
    }
}

/* start main programm */
void reboot_fastboot(int argc, char *argv[])
{
	g_print("Log: reboot_fastboot\n");
	GtkWidget *window, *grid, *button;
    char button_labels[4][30];
    
    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_reboot_fast(button_labels);
    
    window = gtk_window_new();
    const char *reboot_fast_window = strcmp(language, "de") == 0 ? "Neustart Fastboot" : "Reboot Fastboot";
    gtk_window_set_title(GTK_WINDOW(window), reboot_fast_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);
    
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
                g_signal_connect(button, "clicked", G_CALLBACK(reboot_from_adb), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(reboot_from_fastboot), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(fastboot_help), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(list_bootloader_var), NULL);
                break;          
        }
    }
    
    // free the provider
	if (provider != NULL) 
	{
	    g_object_unref(provider);
	    provider = NULL;
	}
	
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop); 
    
    if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
    
    g_print("Log: end reboot_fastboot\n");
}
