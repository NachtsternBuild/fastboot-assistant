/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - config-projekt_GUI 	 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <glib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"
#include "function_header.h"

// include all functions
extern void make_dir();
extern void remove_old();
extern void wsl_config();
extern void post_update();

char success_message[4096];

// Callback functions for each button
// function that start make_dir
static void start_make_dir_function(GtkWidget *widget, gpointer data) 
{
    const char *message = strcmp(language, "de") == 0 ? "Fertig!": "Ready!";
    make_dir();
    show_message(message);
}

// function that start remove_old
static void start_remove_old(GtkWidget *widget, gpointer data) 
{
    remove_old();
}

// function that start wsl_config
static void start_wsl_config(GtkWidget *widget, gpointer data) 
{
    wsl_config();
}

// function start post_update
static void run_post_update(GtkWidget *widget, gpointer data)
{
	post_update();
}

// function restart the update
static void run_setup(GtkWidget *widget, gpointer data)
{
	LOG_INFO("run_setup");
	char restart_setup[2048];
	char restart_setup_file_dark[2048];
	char restart_setup_file_path[2048];
	
	// get config dir
    get_config_dir(restart_setup, sizeof(restart_setup));
    
    // config files
    snprintf(restart_setup_file_dark, sizeof(restart_setup_file_dark), "%s/dark.txt", restart_setup);
    snprintf(restart_setup_file_path, sizeof(restart_setup_file_path), "%s/path_config.txt", restart_setup);
	
	// delete config files
	delete_config_files(restart_setup_file_dark);
	delete_config_files(restart_setup_file_path);
	
	// start first setup
	run_first_run_setup(provider);
	LOG_INFO("end run_setup");
}

// function to clean the log
static void clean_log(GtkWidget *widget, gpointer data)
{
	LOG_INFO("clean_log");
	char log_dir_settings[4096];
    char log_file_settings_path[4096];
    char log_file_settings[4096];
        
    // get config dir
    get_config_dir(log_dir_settings, sizeof(log_dir_settings));
    
    // log file with path
    snprintf(log_file_settings_path, sizeof(log_file_settings_path), "%s/log", log_dir_settings);
    snprintf(log_file_settings, sizeof(log_file_settings), "%s/log/log.txt", log_dir_settings);
    // delete files in dir
    LOG_INFO("Remove: %s", log_file_settings_path);
    delete_files_in_dir(log_file_settings_path);
    
    // create log_dir
    // only if it not exsists
    if (access(log_file_settings_path, F_OK) == -1) 
    {
        create_directory(log_file_settings_path);
    }
    // open log file or create it
    int log_fd = open(log_file_settings, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (log_fd == -1) 
    {
        LOG_ERROR("Error when opening the log file.");
        exit(1);
    }
    close(log_fd);
    
    snprintf(success_message, sizeof(success_message), g_strcmp0(language, "de") == 0 ? "Beendet" : "Completed");
    show_message(success_message);
    
    LOG_INFO("end clean_log");
}

// function to create a new setup dir
static void new_setup_dir(GtkWidget *widget, gpointer data)
{
	LOG_INFO("new_setup_dir");
	char old_dir_path[4096];
    char old_dir_file[4096];
    
    // logic to remove old path_config.txt
    // get config dir
    get_config_dir(old_dir_path, sizeof(old_dir_path));
    
    // remove path_config
    snprintf(old_dir_file, sizeof(old_dir_file), "%s/path_config.txt", old_dir_path);
    // delete file in dir
    delete_config_files(old_dir_file);
	
	// start the folder chooser
	show_folder_chooser(widget, data);
	
	LOG_INFO("end new_setup_dir");
}

// Function to set up button labels based on the language
void set_button_labels_config_projekt(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Create folder");
        strcpy(labels[1], "Clean up");
        strcpy(labels[2], "Configure");
        strcpy(labels[3], "Change language");
        strcpy(labels[4], "Change theme");
        strcpy(labels[5], "Clean log");
        strcpy(labels[6], "Define new directory");
        strcpy(labels[7], "Post update");
        strcpy(labels[8], "Restart Setup");
    } 
    
    else 
    {
        strcpy(labels[0], "Anlegen Ordner");
        strcpy(labels[1], "Aufräumen");
        strcpy(labels[2], "Konfigurieren");
        strcpy(labels[3], "Sprache wechseln");
        strcpy(labels[4], "Thema wechseln");
        strcpy(labels[5], "Log löschen");
        strcpy(labels[6], "Neues Verzeichnis festlegen");
        strcpy(labels[7], "Update Nachbearbeitung");
        strcpy(labels[8], "Erneutes Setup");
    }
}

/* main function of config-projekt_GUI*/
void config_projekt_GUI(int argc, char *argv[]) 
{
	LOG_INFO("config_projekt_GUI");
	GtkWidget *window, *grid, *button;
    char button_labels[9][30];
    
    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_config_projekt(button_labels);
    
    window = gtk_window_new();
    const char *config_projekt_window = strcmp(language, "de") == 0 ? "Zusätze" : "Additions";
    gtk_window_set_title(GTK_WINDOW(window), config_projekt_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);
    
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), grid);
    
    for (int i = 0; i < 9; i++) 
    {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);
        
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(start_make_dir_function), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_remove_old), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(start_wsl_config), NULL);
                break;
            case 3:
            	g_signal_connect(button, "clicked", G_CALLBACK(toggle_language), NULL);
            	break;
            case 4:
            	g_signal_connect(button, "clicked", G_CALLBACK(toggle_theme), NULL);
            	break;
            case 5:
            	g_signal_connect(button, "clicked", G_CALLBACK(clean_log), NULL);
            	break;
            case 6:
            	g_signal_connect(button, "clicked", G_CALLBACK(new_setup_dir), NULL);
            	break;
            case 7:
            	g_signal_connect(button, "clicked", G_CALLBACK(run_post_update), NULL);
            	break;
            case 8:
            	g_signal_connect(button, "clicked", G_CALLBACK(run_setup), NULL);
            	break;
        }
    }

    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop); 
    
    // free the provider
    if (provider != NULL) 
    {
    	g_object_unref(provider);
    	provider = NULL;
	}

	if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
	
    LOG_INFO("end config_projekt_GUI");
}
