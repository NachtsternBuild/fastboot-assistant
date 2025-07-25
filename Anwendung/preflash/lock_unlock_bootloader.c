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
 *              lock_unlock_bootloader		 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"
#include "function_header.h"

#define MAX_BUFFER_SIZE 256

char bootloader_lock_command[2048];

// button 1 - unlock bootloader new
static void bootloader_new(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("bootloader_new");
    auto_free const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n\nStarte Vorgang um den Bootloader zu öffnen." : "Some chipsets do not support this process in this way. \nStart procedure to open the bootloader.";
    show_message(message);
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = strcmp(language, "de") == 0 ? "Kein Gerät erkannt." : "No device detected.";
        show_error_message(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    auto_free char *device_command = fastboot_command();
    snprintf(bootloader_lock_command, sizeof(bootloader_lock_command), "%s flashing unlock", device_command);
    LOG_INFO("Run: %s", bootloader_lock_command);
    command_with_spinner(bootloader_lock_command);
    LOG_INFO("end bootloader_new");
}

// button 2 - unlock bootloader old
static void bootloader_old(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("bootloader_old");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n\nStarte Vorgang um den Bootloader zu öffnen." : "Some chipsets do not support this process in this way.\n\nStart the process to open the bootloader.";
    show_message(message);
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = strcmp(language, "de") == 0 ? "Kein Gerät erkannt." : "No device detected.";
        show_error_message(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    auto_free char *device_command = fastboot_command();
    snprintf(bootloader_lock_command, sizeof(bootloader_lock_command), "%s oem unlock", device_command);
    LOG_INFO("Run: %s", bootloader_lock_command);
    command_with_spinner(bootloader_lock_command);
    LOG_INFO("end bootloader_old");
}

// button 3 - lock bootloader
static void bootloader_lock(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("bootloader_lock");
    const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n\nStarte Vorgang um den Bootloader zu schließen." : "Some chipsets do not support this process in this way.\n\nStart the process to close the bootloader.";
    show_message(message);
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = strcmp(language, "de") == 0 ? "Kein Gerät erkannt." : "No device detected.";
        show_error_message(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    auto_free char *device_command = fastboot_command();
    snprintf(bootloader_lock_command, sizeof(bootloader_lock_command), "%s flashing lock", device_command);
    LOG_INFO("Run: %s", bootloader_lock_command);
    command_with_spinner(bootloader_lock_command);
    LOG_INFO("end bootloader_lock");
}

// function to set up button labels based on the language
void set_button_labels_bootloader(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Unlock (new)");
        strcpy(labels[1], "Unlock (old)");
        strcpy(labels[2], "Lock");
        strcpy(labels[3], "Back");
    } 
    
    else 
    {
        strcpy(labels[0], "Öffnen (neu)");
        strcpy(labels[1], "Öffnen (alt)");
        strcpy(labels[2], "Schließen");
        strcpy(labels[3], "Zurück");
    }
}

/* main programm - lock_unlock_bootloader*/
void lock_unlock_bootloader(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("lock_unlock_bootloader");
	
	apply_language();
    
    char labels[4][30];  // labels for the button 
    set_button_labels_bootloader(labels);  // for both languages
    
    GtkWidget *lock_unlock_bootloader = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(lock_unlock_bootloader, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(lock_unlock_bootloader, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_icon_nav_button_with_position("changes-allow-symbolic", labels[0], G_CALLBACK(bootloader_new), stack, GTK_ALIGN_CENTER); 
    GtkWidget *btn2 = create_icon_nav_button_with_position("changes-allow-symbolic", labels[1], G_CALLBACK(bootloader_old), stack, GTK_ALIGN_CENTER); 
    GtkWidget *btn3 = create_icon_nav_button_with_position("changes-prevent-symbolic", labels[2], G_CALLBACK(bootloader_lock), stack, GTK_ALIGN_CENTER); 
    GtkWidget *btn_back = create_icon_nav_button_with_position("pan-start-symbolic", labels[3], G_CALLBACK(preflash_GUI), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 2, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(lock_unlock_bootloader), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(lock_unlock_bootloader), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "lock_unlock_bootloader")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), lock_unlock_bootloader, "lock_unlock_bootloader");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "lock_unlock_bootloader");
        
    LOG_INFO("end lock_unlock_bootloader");
}
