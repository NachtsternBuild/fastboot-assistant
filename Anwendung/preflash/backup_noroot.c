/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das Installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - backup_noroot		 	 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 */

/* headers used in the program */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "loading_spinner.h"
#include "language_check.h"
#include "function_header.h"

#define MAX_BUFFER_SIZE 3072

GtkWidget *backup_window;

char install_command_backup[2048];

// function that Install dependencies with root rights 
static void install_depends(GtkButton *button) 
{
    // for linux
    snprintf(install_command_backup, sizeof(install_command_backup), "apt install p7zip-full adb curl whiptail pv bc secure-delete zenity -y");
    // for windows
    //snprintf(install_command, sizeof(install_command), "apt-get install p7zip-full secure-delete whiptail curl dos2unix pv bc zenity '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev -y");
    
    LOG_INFO("Run: %s", install_command_backup);

    // run command with pkexec
    install_with_pkexec(install_command_backup);
    gtk_window_destroy(GTK_WINDOW(backup_window));
}

// Callback function to install dependencies 
static void install_depends_function(GtkWidget *widget, gpointer stack) 
{
    GtkWidget *vbox, *install_depends_button;

    const char *message = strcmp(language, "de") == 0 ? "Die Installation der benötigten \nAbhängigkeiten erfordert Root-Rechte." : "The installation of the required \ndependencies requires root rights.";
    show_message(message);

    // create window
    backup_window = gtk_window_new();
    const char *backup_noroot_window = strcmp(language, "de") == 0 ? "Abhängigkeiten installieren" : "Install dependencies";
    gtk_window_set_title(GTK_WINDOW(backup_window), backup_noroot_window);
    gtk_window_set_default_size(GTK_WINDOW(backup_window), 500, 200);
    g_signal_connect(backup_window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(backup_window), vbox);

    // install button
    install_depends_button = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Installieren" : "Install");
    g_signal_connect(install_depends_button, "clicked", G_CALLBACK(install_depends), NULL);
    gtk_box_append(GTK_BOX(vbox), install_depends_button);

    gtk_window_present(GTK_WINDOW(backup_window));
}

// download the backup
static void download_backup(GtkWidget *widget, gpointer stack) 
{
    const char *message1 = strcmp(language, "de") == 0 ? "Das Tool 'Open Android Backup' wird heruntergeladen und entpackt." : "The 'Open Android Backup' tool is downloaded and unpacked.";
    show_message(message1);
	char path_file[4096];
    char main_path_build[4096];
    char wget_command[16384];
    // load path
    get_config_file_path(path_file, sizeof(path_file));
    // load the path
    const char *path_file_load = load_path_from_file(path_file);

    if (path_file_load) 
    {
        LOG_INFO("Loaded path: %s", path_file_load);
    }
    snprintf(main_path_build, sizeof(main_path_build), "%s/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle.zip", path_file_load);
    snprintf(wget_command, sizeof(wget_command), "wget -O %s https://github.com/mrrfv/open-android-backup/releases/download/v1.0.18/Open_Android_Backup_v1.0.18_Bundle.zip && unzip %s -d %s", main_path_build, main_path_build, main_path_build);
	
    LOG_INFO("Run: %s", wget_command);
    command_with_spinner(wget_command);
    
    if (path_file_load != NULL) 
	{
    	g_free((gpointer)path_file_load); // free the info (because g_file_get_contents was used)
	}
}

// start backup
static void open_backup(GtkWidget *widget, gpointer stack) 
{
    char bash_command[4096];
    char run_open_backup[4096];
    // load path
    get_config_file_path(run_open_backup, sizeof(run_open_backup));
    // load the path
    const char *run_open_backup_bash = load_path_from_file(run_open_backup);

    if (run_open_backup_bash) 
    {
        LOG_INFO("Loaded path: %s", run_open_backup_bash);
    }
    // build command
    snprintf(bash_command, sizeof(bash_command), "bash %s/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle/backup.sh", run_open_backup_bash);
    open_terminal_by_desktop(bash_command);
    
    if (run_open_backup_bash != NULL) 
	{
    	g_free((gpointer)run_open_backup_bash); // free the info (because g_file_get_contents was used)
	}
}

// Function to set up button labels based on the language
void set_button_labels_backup_noroot(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Prepare");
        strcpy(labels[1], "Download");
        strcpy(labels[2], "Start");
        strcpy(labels[3], "Back");
    }
    
    else
    {
    	strcpy(labels[0], "Vorbereiten");
    	strcpy(labels[1], "Download");
    	strcpy(labels[2], "Starten");
    	strcpy(labels[3], "Zurück");
    }
} 

/* main function - backup_noroot */
void backup_noroot(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("backup_noroot");
    
	apply_language();
    
    char labels[4][30];  // labels for the button 
    set_button_labels_backup_noroot(labels);  // for both languages
    
    GtkWidget *backup_noroot = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(backup_noroot, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(backup_noroot, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
	
	// create button
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(install_depends_function), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(download_backup), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(open_backup), stack);
    GtkWidget *btn_back = create_nav_button(labels[3], G_CALLBACK(preflash_GUI), stack);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 2, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(backup_noroot), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(backup_noroot), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "backup_noroot")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), backup_noroot, "backup_noroot");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "backup_noroot");
    
    LOG_INFO("end backup_noroot");
}

