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
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "function_header.h"

// button 1 - install dependencies for the backup.sh
static void install_dependencies(GtkWidget *widget, gpointer data)
{
    GtkWidget *dialog;
    const char *message = "Die Installation der benötigen Abhängigkeiten kann nur mit Root-Rechten ausgeführt werden.";
    // show message
    show_message(message);
    
	char function_command[255];
	open_terminal_by_desktop("sudo apt update && sudo apt install p7zip-full adb curl whiptail pv bc secure-delete zenity && exit");
}

// button 2 - download the open_android_backup.zip and unpack it
static void download_backup_sh(GtkWidget *widget, gpointer data)
{
	system("fastboot devices");
	char function_command[255];
	open_terminal_by_desktop("wget -O ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle.zip https://github.com/mrrfv/open-android-backup/releases/download/v1.0.18/Open_Android_Backup_v1.0.18_Bundle.zip && exit");

	system("unzip ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle.zip -d ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle");
	GtkWidget *dialog;
    const char *message = "Open Android Backup ist nun bereit.";
    // show message
    show_message(message);
}

// button 3 - start the backup.sh
static void start_backup_sh(GtkWidget *widget, gpointer data)
{
	char function_command[255];
	open_terminal_by_desktop("bash ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle/backup.sh");
}

/* start main programm */
void backup_noroot(int argc, char *argv[])
{
	// int gtk
	gtk_init(&argc, &argv);
	
	// make main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Backup ohne Root");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// make button for every function with label
    GtkWidget *button_install_dependencies = gtk_button_new_with_label("Installation der Abhängigkeiten");
    GtkWidget *button_download_backup_sh = gtk_button_new_with_label("Download und vorbereiten von Open Android Backup");
    GtkWidget *button_start_backup_sh = gtk_button_new_with_label("Starten Open Android Backup");
    
    // Link the click callback function with the buttons 
    g_signal_connect(button_install_dependencies, "clicked", G_CALLBACK(install_dependencies), NULL);
    g_signal_connect(button_download_backup_sh, "clicked", G_CALLBACK(download_backup_sh), NULL);
    g_signal_connect(button_start_backup_sh, "clicked", G_CALLBACK(start_backup_sh), NULL);
   
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), button_install_dependencies, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_download_backup_sh, TRUE, TRUE, 0);
    
    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), button_start_backup_sh, TRUE, TRUE, 0);
    
     // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all button
    gtk_widget_show(button_install_dependencies);
    gtk_widget_show(button_download_backup_sh);
    gtk_widget_show(button_start_backup_sh);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
}
    
