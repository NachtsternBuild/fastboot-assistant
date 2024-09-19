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
#include "loading_spinner.h"

#define MAX_BUFFER_SIZE 3072

char install_command_backup[2048];

static void install_depends(GtkButton *button, GtkEntry *password_entry) 
{
    snprintf(install_command_backup, sizeof(install_command_backup), "apt-get install p7zip-full adb curl whiptail pv bc secure-delete zenity");
    // for windows
    //snprintf(install_command, sizeof(install_command), "apt-get install p7zip-full secure-delete whiptail curl dos2unix pv bc zenity '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev -y");
    g_print("Installiere: %s", install_command_backup);
    install_with_root(button, password_entry, install_command_backup);
}

// Callback functions for each button
// install depends for open android backup
static void install_depends_function(GtkWidget *widget, gpointer data) 
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *password_entry;
    GtkWidget *info_button, *install_depends_button;
    
    const char *message = "\nDie Installation der benötigen Abhängigkeiten kann nur mit Root-Rechten ausgeführt werden.\n";
    // show message
    show_message(message);
    // create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Aktualisieren");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	
	// info button
    info_button = gtk_button_new_with_label("Legitimation");
   	gtk_box_pack_start(GTK_BOX(vbox), info_button, TRUE, TRUE, 0);

	// password input 
    password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);  // hide the password
    gtk_box_pack_start(GTK_BOX(vbox), password_entry, TRUE, TRUE, 0);

    // install button
    install_depends_button = gtk_button_new_with_label("Installieren");
    g_signal_connect(install_depends_button, "clicked", G_CALLBACK(install_depends), password_entry);
   	gtk_box_pack_start(GTK_BOX(vbox), install_depends_button, TRUE, TRUE, 0);

    gtk_widget_show_all(window);
}

// download open android backup
static void download_backup(GtkWidget *widget, gpointer data) 
{
    const char *message1 = "\nDas Tool 'Open Android Backup' wird heruntergeladen und entpackt.\n";
    show_message(message1);
    
    snprintf(install_command_backup, sizeof(install_command_backup), "wget -O ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle.zip https://github.com/mrrfv/open-android-backup/releases/download/v1.0.18/Open_Android_Backup_v1.0.18_Bundle.zip && unzip ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle.zip -d ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle");
    // for windows
    //snprintf("wget -O %s/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle.zip https://github.com/mrrfv/open-android-backup/releases/download/v1.0.18/Open_Android_Backup_v1.0.18_Bundle.zip && unzip %s/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle.zip -d %s/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle", wsl_dir, wsl_dir, wsl_dir);
    g_print("Führe aus: %s", install_command_backup);
    command_with_spinner(install_command_backup);
}

// open open android backup
static void open_backup(GtkWidget *widget, gpointer data) 
{
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
    char button_labels[3][30] = {"Vorbereiten", "Download", "Starten"};

    gtk_init(&argc, &argv);
    apply_theme();
    
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
	// clean the provider
    g_object_unref(provider);

    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();
}
    
