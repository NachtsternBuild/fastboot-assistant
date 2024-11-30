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
#include "program_functions.h"
#include "language_check.h"

#define MAX_BUFFER_SIZE 2048

// Callback functions for each button
// Remove the 'ROM-Install' directory
static void remove_rom_install(GtkWidget *widget, gpointer data) 
{
    /*
    char command[MAX_BUFFER_SIZE];
    snprintf(command, sizeof(command), "rm -rf %s/Downloads/ROM-Install", get_home_directory_flash());
    system(command);
	*/
    char wsl_dir[MAX_BUFFER_SIZE];
    get_wsl_directory(wsl_dir, sizeof(wsl_dir));
    snprintf(command, sizeof(command), "rm -rf %s/Downloads/ROM-Install", wsl_dir);
    system(command);
	
    const char *message = "Ready.\n";
    show_message(message);
}

// Remove old files in 'ROM-Install'
static void remove_old_files(GtkWidget *widget, gpointer data) 
{
	// add the config.txt
	/*
    char command[MAX_BUFFER_SIZE];
    snprintf(command, sizeof(command), "rm -rf %s/Downloads/ROM-Install/*", get_home_directory_flash());
    system(command);
    snprintf(command, sizeof(command), "mkdir -p %s/Downloads/ROM-Install/Backup", get_home_directory_flash());
    system(command);
    snprintf(command, sizeof(command), "mkdir -p %s/Downloads/ROM-Install/Backup/Noroot", get_home_directory_flash());
    system(command);
    snprintf(command, sizeof(command), "mkdir -p %s/Downloads/ROM-Install/Images", get_home_directory_flash());
    system(command);
	*/
	
    char wsl_dir[MAX_BUFFER_SIZE];
    get_wsl_directory(wsl_dir, sizeof(wsl_dir));
    snprintf(command, sizeof(command), "rm -rf %s/Downloads/ROM-Install/*", wsl_dir);
    system(command);
    snprintf(command, sizeof(command), "mkdir -p %s/Downloads/ROM-Install/Backup", wsl_dir);
    system(command);
    snprintf(command, sizeof(command), "mkdir -p %s/Downloads/ROM-Install/Backup/Noroot", wsl_dir);
    system(command);
    snprintf(command, sizeof(command), "mkdir -p %s/Downloads/ROM-Install/Images", wsl_dir);
    system(command);
	
    const char *message = "Ready.\n";
    show_message(message);
}

// Remove backups
static void remove_backups(GtkWidget *widget, gpointer data) 
{
    /*
    char command[MAX_BUFFER_SIZE];
    snprintf(command, sizeof(command), "rm -rf %s/Downloads/ROM-Install/Backup/*", get_home_directory_flash());
    system(command);
    snprintf(command, sizeof(command), "mkdir -p %s/Downloads/ROM-Install/Backup/Noroot", get_home_directory_flash());
    system(command);
	
	*/
    char wsl_dir[MAX_BUFFER_SIZE];
    get_wsl_directory(wsl_dir, sizeof(wsl_dir));
    snprintf(command, sizeof(command), "rm -rf %s/Downloads/ROM-Install/Backup/*", wsl_dir);
    system(command);
    snprintf(command, sizeof(command), "mkdir -p %s/Downloads/ROM-Install/Backup/Noroot", wsl_dir);
    system(command);
	
    const char *message = "Ready.\n";
    show_message(message);
}

// Function to set up button labels based on the language
void set_button_labels_remove(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "ROM-Install");
        strcpy(labels[1], "old files");
        strcpy(labels[2], "Backups");
    } 
    
    else 
    {
        strcpy(labels[0], "ROM-Install");
        strcpy(labels[1], "alte Dateien");
        strcpy(labels[2], "Backups");
    }
}
/* main function of preflash_GUI */
void remove_old(int argc, char *argv[]) 
{
	GtkWidget *window, *grid, *button;
    char button_labels[3][30];
    
    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_remove(button_labels);
    
    window = gtk_window_new();
    const char *remove_old_window = strcmp(language, "de") == 0 ? "Löschen von:" : "Remove:";
    gtk_window_set_title(GTK_WINDOW(window), remove_old_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);
    
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
                g_signal_connect(button, "clicked", G_CALLBACK(remove_rom_install), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(remove_old_files), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(remove_backups), NULL);
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
    
    g_print("Log: end remove_old\n");
}
