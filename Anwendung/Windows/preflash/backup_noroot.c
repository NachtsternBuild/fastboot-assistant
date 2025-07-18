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

#define MAX_BUFFER_SIZE 3072

GtkWidget *backup_window;

char install_command_backup[2048];

// function that Install dependencies with root rights 
static void install_depends(GtkButton *button) 
{
    // for linux
    //snprintf(install_command_backup, sizeof(install_command_backup), "apt install p7zip-full adb curl whiptail pv bc secure-delete zenity -y");
    // for windows
    snprintf(install_command_backup, sizeof(install_command_backup), "apt-get install p7zip-full secure-delete whiptail curl dos2unix pv bc zenity '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev -y");
    
    LOG_INFO("Run: %s", install_command_backup);

    // run command with pkexec
    install_with_pkexec(install_command_backup);
    gtk_window_destroy(GTK_WINDOW(backup_window));
}

// Callback function to install dependencies 
static void install_depends_function(GtkWidget *widget, gpointer data) 
{
    GtkWidget *vbox, *install_depends_button;

    const char *message = strcmp(language, "de") == 0 ? "Die Installation der benötigten \nAbhängigkeiten erfordert Root-Rechte." : "The installation of the required \ndependencies requires root rights.";
    show_message(message);

    // create window
    backup_window = gtk_window_new();
    const char * backup_noroot_window = strcmp(language, "de") == 0 ? "Abhängigkeiten installieren" : "Install dependencies";
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
static void download_backup(GtkWidget *widget, gpointer data) 
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
    snprintf(wget_command, sizeof(wget_command), "wget -O %s https://github.com/mrrfv/open-android-backup/releases/download/v1.1.0/Open_Android_Backup_v1.1.0_Bundle.zip && unzip %s -d %s", main_path_build, main_path_build, main_path_build);
	
    LOG_INFO("Run: %s", wget_command);
    command_with_spinner(wget_command);
    
    if (path_file_load != NULL) 
	{
    	g_free((gpointer)path_file_load); // free the info (because g_file_get_contents was used)
	}
}

// start backup
static void open_backup(GtkWidget *widget, gpointer data) 
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
    }
    
    else
    {
    	strcpy(labels[0], "Vorbereiten");
    	strcpy(labels[1], "Download");
    	strcpy(labels[2], "Starten");
    }
} 

/* main function - backup_noroot */
void backup_noroot(int argc, char *argv[]) 
{
    LOG_INFO("backup_noroot");
    GtkWidget *window, *grid, *button;
    char button_labels[3][30];
    
    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels_backup_noroot(button_labels);
    
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Open Android Backup");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);
    
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), grid);

    // add button
    for (int i = 0; i < 3; i++) 
    {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);

        // callback
        switch (i) 
        {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(install_depends_function), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(download_backup), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(open_backup), NULL);
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
    
    LOG_INFO("end backup_noroot");
}

