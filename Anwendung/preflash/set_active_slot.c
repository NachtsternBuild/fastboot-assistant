/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - set_active_slot		 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"
#include "flash_function_header.h"

#define MAX_BUFFER_SIZE 256

char slot_command[2048];

// button 1 - set slot a
static void set_slot_a(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("set_slot_a");
    auto_free char *device_command = fastboot_command();
	snprintf(slot_command, sizeof(slot_command), "%s set_active a && %s getvar current-slot", device_command, device_command);
	LOG_INFO("Run: %s", slot_command);
    command_with_spinner(slot_command);
    LOG_INFO("end set_slot_a");
}

// button 2 - set slot b
static void set_slot_b(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("set_slot_b");
    auto_free char *device_command = fastboot_command();
	snprintf(slot_command, sizeof(slot_command), "%s set_active b && %s getvar current-slot", device_command, device_command);
	LOG_INFO("Run: %s", slot_command);
    command_with_spinner(slot_command);
    free(device_command);
    LOG_INFO("end set_slot_b");
}

// button 3 - set the slot automatic
static void set_slot_auto(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("set_slot_auto");
	char active_slot[BUFFER_SIZE] = {0};
    char inactive_slot[BUFFER_SIZE] = {0};

    // get active slot
    check_active_slot(active_slot, sizeof(active_slot));
    LOG_INFO("active slot: %s", active_slot);

    // get inactive slot
    if (strcmp(active_slot, "a") == 0) 
    {
        strncpy(inactive_slot, "b", sizeof(inactive_slot) - 1);
        LOG_INFO("inactive slot: %s", inactive_slot);
    } 
    
    else if (strcmp(active_slot, "b") == 0) 
    {
        strncpy(inactive_slot, "a", sizeof(inactive_slot) - 1);
        LOG_INFO("inactive slot: %s", inactive_slot);
    } 
    
    else 
    {
        LOG_ERROR("Unknown active slot: %s", active_slot);
        exit(1);
    }
    
    auto_free char *device_command = fastboot_command();
    // create the command
    snprintf(slot_command, sizeof(slot_command), "%s set_active %s && %s getvar current-slot", device_command, inactive_slot, device_command);
    LOG_INFO("Run: %s", slot_command);
       
    // set the new active slot
    command_with_spinner(slot_command);
   
	LOG_INFO("end set_slot_auto");
}

// function to set up button labels based on the language
void set_button_labels_slot(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Set 'a'");
        strcpy(labels[1], "Set 'b'");
        strcpy(labels[2], "Set slot auto");
        strcpy(labels[3], "Back");
    } 
    
    else 
    {
        strcpy(labels[0], "Setze 'a'");
        strcpy(labels[1], "Setze 'b'");
        strcpy(labels[2], "Setze Slot automatisch");
        strcpy(labels[3], "Zurück");
    }
}

/* start main programm */
void set_active_slot(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("set_active_slot");
    
	apply_language();
    
    char labels[4][30];  // labels for the button 
    set_button_labels_slot(labels);  // for both languages
    
    GtkWidget *set_active_slot = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(set_active_slot, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(set_active_slot, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(set_slot_a), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(set_slot_b), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(set_slot_auto), stack);
    GtkWidget *btn_back = create_nav_button(labels[3], G_CALLBACK(preflash_GUI), stack);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 2, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(set_active_slot), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(set_active_slot), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "set_active_slot")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), set_active_slot, "set_active_slot");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "set_active_slot");
        
    LOG_INFO("end set_active_slot");
}
    
