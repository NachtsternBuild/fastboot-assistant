/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das Installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              wsl_config					 *
 *											 *
 *-------------------------------------------*
 */

/* headers that are used in the main program */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

char path[3072];
char config[3072];
char mv_adb[3072];
char mv_fastboot[3072];
char command_adb[3072];
char command_fastboot[3072];

const char *base_paths[] = {"/mnt/c/platform-tools", "/mnt/c/ADB"};
const char *files[] = {"adb.exe", "fastboot.exe"};

static void config_adb(GtkButton *button, GtkEntry *password_entry) 
{
    // Define i and j as static variables for accessing the right path/file
    for (int i = 0; i < 2; ++i) 
    {
    	for (int j = 0; j < 2; ++j) 
    	{
    		snprintf(path, sizeof(path), "%s/%s", base_paths[j], files[i]);
    
    		// Paths to the possible locations of adb.exe and fastboot.exe
    		snprintf(mv_adb, sizeof(mv_adb), "sudo mv /usr/bin/adb /usr/bin/adb_bk");
    		snprintf(mv_fastboot, sizeof(mv_fastboot), "sudo mv /usr/bin/fastboot /usr/bin/fastboot_bk");
   
    		snprintf(command_adb, sizeof(command_adb), "sudo ln -s %s /usr/bin/adb", path);
    		snprintf(command_fastboot, sizeof(command_fastboot), "sudo ln -s %s /usr/bin/fastboot", path);
							
    		// Create the full command
    		snprintf(config, sizeof(config), "%s && %s && %s && %s && exit", mv_adb, mv_fastboot, command_adb, command_fastboot);
    
    		g_print("Führe aus: %s\n", config);
    
    		// Run the command with root privileges
    		install_with_root(button, password_entry, config);
    	}
    }
}

// Check if file exists
int file_exists(const char *path) 
{
    char command[2048];
    snprintf(command, sizeof(command), "test -e %s", path);
    return system(command) == 0;
}
/*
// Check if directory exists
int directory_exists(const char *path) 
{
    char command[2048];
    snprintf(command, sizeof(command), "test -d %s", path);
    return system(command) == 0;
}
*/
// Main function
void wsl_config() 
{
    int argc = 0;
    char **argv = NULL;
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *password_entry;
    GtkWidget *config_adb_button;

    gtk_init(&argc, &argv);
    apply_theme();
    
    int found = 0;

    // Check for the presence of adb.exe and fastboot.exe in known directories
    for (int i = 0; i < 2; ++i) 
    {
        for (int j = 0; j < 2; ++j) 
        {
            snprintf(path, sizeof(path), "%s/%s", base_paths[j], files[i]);
            
            if (directory_exists(base_paths[j]) && file_exists(path)) 
            {
                found = 1;
                break;
            }
        }

        if (found)
            break;
    }

    if (found == 1) 
    {
        // Create GTK window after a valid path is found
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window), "Konfigurieren");
        gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);

        // the "destroy" signal to gtk_main_quit
        g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        gtk_container_add(GTK_CONTAINER(window), vbox);

        // Password input field
        password_entry = gtk_entry_new();
        gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);  // Hide password input
        gtk_box_pack_start(GTK_BOX(vbox), password_entry, TRUE, TRUE, 0);

        // Install button
        config_adb_button = gtk_button_new_with_label("Installieren");
        g_signal_connect(config_adb_button, "clicked", G_CALLBACK(config_adb), password_entry);
        gtk_box_pack_start(GTK_BOX(vbox), config_adb_button, TRUE, TRUE, 0);

        gtk_widget_show_all(window);
        g_print("Fertig.\n");
        
        // Show message
        const char *message = "Fertig!\n";
        show_message(message);
    }
    else 
    {
        g_print("Log: Kein WSL-System gefunden.\n");

        // Show message
        const char *message = "Kein WSL-System gefunden.\n";
        show_message(message);
        gtk_main_quit();
    }

    // Start the GTK main loop
    gtk_main();
}

