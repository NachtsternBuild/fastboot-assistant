/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - backup_noroot		 	 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "function_header.h"

#define MAX_BUFFER_SIZE 3072
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 350

// Callback functions for each button
// install depends for open android backup
static void install_depends(GtkWidget *widget, gpointer data) 
{
    const char *message = "\nDie Installation der benötigen Abhängigkeiten kann nur mit Root-Rechten ausgeführt werden.\n";
    // show message
    show_message(message);
    
	char function_command[255];
	open_terminal_by_desktop("sudo apt update && sudo apt-get install p7zip-full adb curl whiptail pv bc secure-delete zenity && exit");
	// for Windows
	/*
	open_terminal_by_desktop("sudo apt install p7zip-full secure-delete whiptail curl dos2unix pv bc zenity '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev -y");
	*/
}

// download open android backup
static void download_backup(GtkWidget *widget, gpointer data) 
{
    const char *message1 = "\nDas Tool 'Open Android Backup' wird heruntergeladen und entpackt.\n";
    show_message(message1);
    
    char function_command[3072];
	open_terminal_by_desktop("wget -O ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle.zip https://github.com/mrrfv/open-android-backup/releases/download/v1.0.18/Open_Android_Backup_v1.0.18_Bundle.zip && exit");
	system("unzip ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle.zip -d ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle");
	// for Windows
	/*
	char wsl_dir[MAX_BUFFER_SIZE];
    get_wsl_directory(wsl_dir, sizeof(wsl_dir));
    snprintf(command, sizeof(command), "wget -O %s/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle.zip https://github.com/mrrfv/open-android-backup/releases/download/v1.0.18/Open_Android_Backup_v1.0.18_Bundle.zip && exit", wsl_dir);
    system(command);
    snprintf(command, sizeof(command), "unzip %s/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle.zip -d %s/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle", wsl_dir, wsl_dir);
	*/
    const char *message2 = "\nOpen Android Backup ist nun bereit.\n";
    // show message
    show_message(message2);
}

// open open android backup
static void open_backup(GtkWidget *widget, gpointer data) 
{
    char function_command[3072];
	open_terminal_by_desktop("bash ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle/backup.sh");
	// for Windows
	/*
	char wsl_dir[MAX_BUFFER_SIZE];
    get_wsl_directory(wsl_dir, sizeof(wsl_dir));
    snprintf(command, sizeof(command), "%s/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle/backup.sh", wsl_dir);
    open_terminal_by_desktop(command);
    */
}

/* main function of backup_noroot*/
void backup_noroot(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[3][30] = {"Vorbereiten" "Download", "Starten"};

    gtk_init(&argc, &argv);
    
    css_provider(); // load css-provider

    
    // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Open Android Backup");
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
                g_signal_connect(button, "clicked", G_CALLBACK(install_depends), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(download_backup), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(open_backup), NULL);
                break;
        }
    }
	// clean the provider
    g_object_unref(provider);

    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();
}
    
