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

#define MAX_BUFFER_SIZE 2048

// Callback functions for each button
// Remove the 'ROM-Install' directory
static void remove_rom_install(GtkWidget *widget, gpointer data) 
{
    const char *message = "Lösche ~/Downloads/ROM-Install\n";
    show_message(message);

    char command[MAX_BUFFER_SIZE];
    snprintf(command, sizeof(command), "rm -rf %s/Downloads/ROM-Install", get_home_directory_flash());
    system(command);
	
	/*
    char wsl_dir[MAX_BUFFER_SIZE];
    get_wsl_directory(wsl_dir, sizeof(wsl_dir));
    snprintf(command, sizeof(command), "rm -rf %s/Downloads/ROM-Install", wsl_dir);
    system(command);
	*/
	
    message = "Fertig.\n";
    show_message(message);
}

// Remove old files in 'ROM-Install'
static void remove_old_files(GtkWidget *widget, gpointer data) 
{
    const char *message = "Lösche alle Dateien in ROM-Install.\n";
    show_message(message);
	
	// add the config.txt
    char command[MAX_BUFFER_SIZE];
    snprintf(command, sizeof(command), "rm -rf %s/Downloads/ROM-Install/*", get_home_directory_flash());
    system(command);
    snprintf(command, sizeof(command), "mkdir -p %s/Downloads/ROM-Install/Backup", get_home_directory_flash());
    system(command);
    snprintf(command, sizeof(command), "mkdir -p %s/Downloads/ROM-Install/Backup/Noroot", get_home_directory_flash());
    system(command);
    snprintf(command, sizeof(command), "mkdir -p %s/Downloads/ROM-Install/Images", get_home_directory_flash());
    system(command);
	
	/*
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
	*/
	
    message = "Fertig.\n";
    show_message(message);
}

// Remove backups
static void remove_backups(GtkWidget *widget, gpointer data) 
{
    const char *message = "Lösche alle Dateien im Backup-Ordner.\n";
    show_message(message);

    char command[MAX_BUFFER_SIZE];
    snprintf(command, sizeof(command), "rm -rf %s/Downloads/ROM-Install/Backup/*", get_home_directory_flash());
    system(command);
    snprintf(command, sizeof(command), "mkdir -p %s/Downloads/ROM-Install/Backup/Noroot", get_home_directory_flash());
    system(command);
	
	/*
    char wsl_dir[MAX_BUFFER_SIZE];
    get_wsl_directory(wsl_dir, sizeof(wsl_dir));
    snprintf(command, sizeof(command), "rm -rf %s/Downloads/ROM-Install/Backup/*", wsl_dir);
    system(command);
    snprintf(command, sizeof(command), "mkdir -p %s/Downloads/ROM-Install/Backup/Noroot", wsl_dir);
    system(command);
	*/
	
    message = "Fertig.\n";
    show_message(message);
}

/* main function of preflash_GUI */
void remove_old(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    
    char button_labels[3][30] = {"ROM-Install", "alte Dateien", "Backups"};

    gtk_init(&argc, &argv);
    
    apply_theme();
    
    // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Löschen von:");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // create the grid and centre it
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    // add the grid to the window
    gtk_container_add(GTK_CONTAINER(window), grid);

    // add and centre all button
    for (int i = 0; i < 3; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);

        // execute css-provider for all buttons
        add_css_provider(button, provider);
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
	
	// clean the storage
    g_object_unref(provider);
    
    // show window
    gtk_widget_show_all(window);

    // run main gtk loop
    gtk_main();
}

