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
#include "language_check.h"
#include "program_functions.h"

char path[3072];
char config[3072];
char mv_adb[3072];
char mv_fastboot[3072];
char command_adb[3072];
char command_fastboot[3072];

const char *base_paths[] = {"/mnt/c/platform-tools", "/mnt/c/ADB"};
const char *files[] = {"adb.exe", "fastboot.exe"};

static void config_adb(GtkButton *button, gpointer user_data) 
{
    for (int i = 0; i < 2; ++i) 
    {
        for (int j = 0; j < 2; ++j) 
        {
            snprintf(path, sizeof(path), "%s/%s", base_paths[j], files[i]);
            
            // command to move and link adb/fastboot
            snprintf(mv_adb, sizeof(mv_adb), "mv /usr/bin/adb /usr/bin/adb_bk");
            snprintf(mv_fastboot, sizeof(mv_fastboot), "mv /usr/bin/fastboot /usr/bin/fastboot_bk");
            snprintf(command_adb, sizeof(command_adb), "ln -s %s /usr/bin/adb", path);
            snprintf(command_fastboot, sizeof(command_fastboot), "ln -s %s /usr/bin/fastboot", path);

            // create the command
            snprintf(config, sizeof(config), "%s && %s && %s && %s", mv_adb, mv_fastboot, command_adb, command_fastboot);

            g_print("Log: Run: %s\n", config);

            // run command with pkexec
            install_with_pkexec(config);
        }
    }
}

// check if file exsists
int file_exists(const char *path) 
{
    char command[2048];
    snprintf(command, sizeof(command), "test -e %s", path);
    return system(command) == 0;
}
/*
// check if dir exsists
int directory_exists(const char *path) 
{
    char command[2048];
    snprintf(command, sizeof(command), "test -d %s", path);
    return system(command) == 0;
}
*/

/* main function wsl_config*/
void wsl_config() 
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *config_adb_button;

    gtk_init();
    GMainLoop *main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    
    int found = 0;

    // check for adb/fastboot
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
	
	// for the WSL system
    if (found == 1) 
    {
        // create the window
        window = gtk_window_new();
        const char *config_window = strcmp(language, "de") == 0 ? "Konfigurieren" : "Configure";
        gtk_window_set_title(GTK_WINDOW(window), config_window);
        gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);
        g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);

        // create the box layout
        vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        gtk_window_set_child(GTK_WINDOW(window), vbox);

        // install button
        config_adb_button = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Installieren" : "Install");
        g_signal_connect(config_adb_button, "clicked", G_CALLBACK(config_adb), NULL);
        gtk_box_append(GTK_BOX(vbox), config_adb_button);

        // show window
    	gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

        const char *message = strcmp(language, "de") == 0 ? "Fertig!" : "Ready!";
        show_message(message);
    }
    
    // no WSL system
    else 
    {
        g_print("Log: No WSL system");

        const char *message = strcmp(language, "de") == 0 ? "Kein WSL-System gefunden." : "No WSL-System.";
        show_message(message);
    }

    // run GTK main loop
    g_main_loop_run(main_loop); 
}

