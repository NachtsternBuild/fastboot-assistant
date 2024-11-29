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
 *      (C) Copyright 2024 Elias Mörz 		 *
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

// Function that Install dependencies with root rights 
static void install_depends(GtkButton *button) 
{
    // for linux
    snprintf(install_command_backup, sizeof(install_command_backup), "apt-get install p7zip-full adb curl whiptail pv bc secure-delete zenity");
    // for windows
    //snprintf(install_command, sizeof(install_command), "apt-get install p7zip-full secure-delete whiptail curl dos2unix pv bc zenity '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev -y");
    
    g_print("Log: Run: %s\n", install_command_backup);

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

    // Fenster erstellen
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
	
	// for linux
    snprintf(install_command_backup, sizeof(install_command_backup), "wget -O ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle.zip https://github.com/mrrfv/open-android-backup/releases/download/v1.0.18/Open_Android_Backup_v1.0.18_Bundle.zip && unzip ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle.zip -d ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle");
    // for windows
    //snprintf("wget -O %s/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle.zip https://github.com/mrrfv/open-android-backup/releases/download/v1.0.18/Open_Android_Backup_v1.0.18_Bundle.zip && unzip %s/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle.zip -d %s/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle", wsl_dir, wsl_dir, wsl_dir);
    g_print("Log: Run: %s", install_command_backup);
    command_with_spinner(install_command_backup);
}

// start backup
static void open_backup(GtkWidget *widget, gpointer data) 
{
    // for linux
    open_terminal_by_desktop("bash ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle/backup.sh");
    // for Windows
	/*
	char wsl_dir[MAX_BUFFER_SIZE];
    get_wsl_directory(wsl_dir, sizeof(wsl_dir));
    snprintf(command, sizeof(command), "%s/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle/backup.sh", wsl_dir);
    open_terminal_by_desktop(command);
    */
}

// Function to set up button labels based on the language
void set_button_labels_backup_noroot(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Prepare");
        strcpy(labels[1], "Download");
        strcpy(labels[1], "Start");
    }
    
    else
    {
    	strcpy(labels[0], "Vorbereiten");
    	strcpy(labels[1], "Download");
    	strcpy(labels[1], "Starten");
    }
} 

/* main function - backup_noroot */
void backup_noroot(int argc, char *argv[]) 
{
    g_print("Log: backup_noroot\n");
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

    // free the provider
	if (provider != NULL) 
	{
	    g_object_unref(provider);
	    provider = NULL;
	}
	
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop); // GTK-Hauptschleife starten
    
    g_print("Log: end backup_noroot\n");
}

