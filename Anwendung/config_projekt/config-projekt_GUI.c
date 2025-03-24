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
static void start_make_dir_function(GtkWidget *widget, gpointer stack) 
{
    const char *message = strcmp(language, "de") == 0 ? "Fertig!": "Ready!";
    make_dir();
    show_message(message);
}

// function that start remove_old
// will replaced
static void start_remove_old(GtkWidget *widget, gpointer stack) 
{
    remove_old();
}

// function that start wsl_config
static void start_wsl_config(GtkWidget *widget, gpointer stack) 
{
    wsl_config();
}

// function start post_update
static void run_post_update(GtkWidget *widget, gpointer stack)
{
	post_update();
}

// function restart the update
static void run_setup(GtkWidget *widget, gpointer stack)
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
	run_first_run_setup(stack);
	LOG_INFO("end run_setup");
}

// function to clean the log
static void clean_log(GtkWidget *widget, gpointer stack)
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
static void new_setup_dir(GtkWidget *widget, gpointer stack)
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
        strcpy(labels[9], "Back to Home");
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
        strcpy(labels[9], "Zurück zur Startseite");
    }
}

/* main function - config-projekt_GUI*/
void config_projekt_GUI(GtkWidget *widget, gpointer stack) 
{
	LOG_INFO("config_projekt_GUI");
    
    apply_theme();
    apply_language();
    
    char button_labels[10][30];  // labels for the button 
    set_button_labels_config_projekt(labels);  // for both languages
    
    GtkWidget *config_projekt_GUI = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(config_projekt_GUI, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(config_projekt_GUI, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(start_make_dir_function), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(remove_old), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(start_wsl_config), stack);
    GtkWidget *btn4 = create_nav_button(labels[3], G_CALLBACK(toggle_language), stack);
    GtkWidget *btn5 = create_nav_button(labels[4], G_CALLBACK(toggle_theme), stack);
    GtkWidget *btn6 = create_nav_button(labels[5], G_CALLBACK(clean_log), stack);
    GtkWidget *btn7 = create_nav_button(labels[6], G_CALLBACK(new_setup_dir), stack);
    GtkWidget *btn8 = create_nav_button(labels[7], G_CALLBACK(run_post_update), stack);
    GtkWidget *btn9 = create_nav_button(labels[8], G_CALLBACK(run_setup), stack);
    GtkWidget *btn_back = create_nav_button(labels[9], G_CALLBACK(show_home_page), stack);

    // add the button to the grid
    // line 1
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 2, 0, 1, 1);
    // line 2 (1)
    gtk_grid_attach(GTK_GRID(grid), btn4, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn5, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn6, 2, 1, 1, 1);
    // line 3 (2)
    gtk_grid_attach(GTK_GRID(grid), btn7, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn8, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn9, 2, 2, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(config_projekt_GUI), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(config_projekt_GUI), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "config_projekt_GUI")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), config_projekt_GUI, "config_projekt_GUI");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "config_projekt_GUI");

    LOG_INFO("end config_projekt_GUI");
}
