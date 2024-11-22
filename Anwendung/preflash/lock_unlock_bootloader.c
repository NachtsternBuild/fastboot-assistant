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
 *              lock_unlock_bootloader		 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

#define MAX_BUFFER_SIZE 256

char bootloader_lock_command[2048];

// button 1 - unlock bootloader new
static void bootloader_new(GtkWidget *widget, gpointer data)
{
    g_print("Log: bootloader_new\n");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n\nStarte Vorgang um den Bootloader zu öffnen." : "Some chipsets do not support this process in this way. \nStart procedure to open the bootloader.";
    show_message(message);
    
    char *device_command = fastboot_command();
    snprintf(bootloader_lock_command, sizeof(bootloader_lock_command), "%s flashing unlock", device_command);
    g_print("Log: Run: %s\n", bootloader_lock_command);
    command_with_spinner(bootloader_lock_command);
    free(device_command);
    g_print("Log: end bootloader_new\n");
}

// button 2 - unlock bootloader old
static void bootloader_old(GtkWidget *widget, gpointer data)
{
    g_print("Log: bootloader_old\n");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n\nStarte Vorgang um den Bootloader zu öffnen." : "Some chipsets do not support this process in this way.\n\nStart the process to open the bootloader.";
    show_message(message);
    
    char *device_command = fastboot_command();
    snprintf(bootloader_lock_command, sizeof(bootloader_lock_command), "%s oem unlock", device_command);
    g_print("Log: Run: %s\n", bootloader_lock_command);
    command_with_spinner(bootloader_lock_command);
    free(device_command);
    g_print("Log: end bootloader_old\n");
}

// button 3 - lock bootloader
static void bootloader_lock(GtkWidget *widget, gpointer data)
{
    g_print("Log: bootloader_lock\n");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n\nStarte Vorgang um den Bootloader zu schließen." : "Some chipsets do not support this process in this way.\n\nStart the process to close the bootloader.";
    show_message(message);
    
    char *device_command = fastboot_command();
    snprintf(bootloader_lock_command, sizeof(bootloader_lock_command), "%s flashing lock", device_command);
    g_print("Log: Run: %s\n", bootloader_lock_command);
    command_with_spinner(bootloader_lock_command);
    free(device_command);
    g_print("Log: end bootloader_lock\n");
}

// Function to set up button labels based on the language
void set_button_labels_bootloader(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Unlock (new)");
        strcpy(labels[1], "Unlock (old)");
        strcpy(labels[2], "Lock");
    } 
    
    else 
    {
        strcpy(labels[0], "Öffnen (neu)");
        strcpy(labels[1], "Öffnen (alt)");
        strcpy(labels[2], "Schließen");
    }
}

/* start main programm - lock_unlock_bootloader*/
void lock_unlock_bootloader(int argc, char *argv[])
{
	g_print("Log: lock_unlock_bootloader\n");
	GtkWidget *window, *grid, *button;
    char button_labels[3][30];
    
    gtk_init();
    apply_theme();
    apply_language();
    set_button_labels_bootloader(button_labels);
    
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Bootloader:");
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
                g_signal_connect(button, "clicked", G_CALLBACK(bootloader_new), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(bootloader_old), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(bootloader_lock), NULL);
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
    
    g_print("Log: end lock_unlock_bootloader\n");
}
