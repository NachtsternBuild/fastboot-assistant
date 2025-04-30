/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *			funkelnde Datenkristalle		 *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das Installieren von 		 *
 *	Custom-ROMs und GSIs auf Android-Geräte  *
 *	zu erleichtern - remove_old			 	 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "function_header.h"
#include "program_functions.h"
#include "language_check.h"

#define MAX_BUFFER_SIZE 2048

// function that delete ROM-Install
void rm_rom_install()
{
	LOG_INFO("remove_rom_install");
    char command[MAX_BUFFER_SIZE];
    char rom_install_rm_file[4096];
    char main_path_rm[4096];
    
    get_config_file_path(rom_install_rm_file, sizeof(rom_install_rm_file));
    // load the path
    const char *rom_install_rm = load_path_from_file(rom_install_rm_file);

    if (rom_install_rm) 
    {
        LOG_INFO("Loaded path: %s", rom_install_rm);
    }
	
    // create the full path 
    snprintf(main_path_rm, sizeof(main_path_rm), "%s", rom_install_rm);
    snprintf(command, sizeof(command), "rm -rf %s", main_path_rm);
    system(command);
	
	if (rom_install_rm != NULL) 
	{
    	g_free((gpointer)rom_install_rm); // free the info (because g_file_get_contents was used)
	}
	
    LOG_INFO("end remove_rom_install");
}
// callback functions for each button
// remove the 'ROM-Install' directory
static void remove_rom_install(GtkWidget *widget, gpointer stack) 
{
    rm_rom_install();
    const char *message = "Ready.\n";
    show_message(message);
}

// Remove old files in 'ROM-Install'
static void remove_old_files(GtkWidget *widget, gpointer stack) 
{
	LOG_INFO("remove_old_files");
	rm_rom_install();
	make_dir();
	
    const char *message = "Ready.\n";
    show_message(message);
    LOG_INFO("end remove_old_files");
}

// Remove backups
static void remove_backups(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("remove_backups");
    char backup_rm_file[4096];
    char two_commands[8192];
    
    get_config_file_path(backup_rm_file, sizeof(backup_rm_file));
    // load the path
    const char *backup_rm = load_path_from_file(backup_rm_file);

    if (backup_rm) 
    {
        LOG_INFO("Loaded path: %s", backup_rm);
    }
	
    // create the full path and remove the dir
    snprintf(two_commands, sizeof(two_commands), "%s/Backup/* && mkdir -p %s/Backup/Noroot", backup_rm, backup_rm);
    system(two_commands);

	if (backup_rm != NULL) 
	{
    	g_free((gpointer)backup_rm); // free the info (because g_file_get_contents was used)
	}
	
    const char *message = "Ready.\n";
    show_message(message);
    LOG_INFO("end remove_backups");
}

// function to set up button labels based on the language
void set_button_labels_remove(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "ROM-Install");
        strcpy(labels[1], "Old files");
        strcpy(labels[2], "Backups");
        strcpy(labels[3], "Back");
    } 
    
    else 
    {
        strcpy(labels[0], "ROM-Install");
        strcpy(labels[1], "Alte Dateien");
        strcpy(labels[2], "Backups");
        strcpy(labels[3], "Zurück");
    }
}
/* main function - remove_old */
void remove_old(GtkWidget *widget, gpointer stack) 
{
	LOG_INFO("remove_old");
	
    apply_language();
    
    char labels[4][30];  // labels for the button 
    set_button_labels_remove(labels);  // for both languages
    
    GtkWidget *remove_old = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(remove_old, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(remove_old, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_icon_nav_button_with_position("system-file-manager-symbolic", labels[0], G_CALLBACK(remove_rom_install), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_icon_nav_button_with_position("emblem-documents-symbolic", labels[1], G_CALLBACK(remove_old_files), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn3 = create_icon_nav_button_with_position("folder-remote-symbolic", labels[2], G_CALLBACK(remove_backups), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_icon_nav_button_with_position("pan-start-symbolic", labels[3], G_CALLBACK(config_projekt_GUI), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 2, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(remove_old), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(remove_old), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "remove_old")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), remove_old, "remove_old");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "remove_old");
	    
    LOG_INFO("end remove_old");
}
