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

#define MAX_BUFFER_SIZE 256
// Callback functions for each button
// install depends for open android backup
static void install_depends(GtkWidget *widget, gpointer data) 
{
    GtkWidget *dialog;
    const char *message = "\nDie Installation der benötigen Abhängigkeiten kann nur mit Root-Rechten ausgeführt werden.\n";
    // show message
    show_message(message);
    
	char function_command[255];
	open_terminal_by_desktop("sudo apt update && sudo apt-get install p7zip-full adb curl whiptail pv bc secure-delete zenity && exit");
}

// download open android backup
static void download_backup(GtkWidget *widget, gpointer data) 
{
    GtkWidget *dialog;
    const char *message = "\nDas Tool 'Open Android Backup' wird heruntergeladen und entpackt.\n";
    char function_command[255];
	open_terminal_by_desktop("wget -O ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle.zip https://github.com/mrrfv/open-android-backup/releases/download/v1.0.18/Open_Android_Backup_v1.0.18_Bundle.zip && exit");

	system("unzip ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle.zip -d ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle");
    const char *message = "\nOpen Android Backup ist nun bereit.\n";
    // show message
    show_message(message);
}

// open open android backup
static void open_backup(GtkWidget *widget, gpointer data) 
{
    char function_command[255];
	open_terminal_by_desktop("bash ~/Downloads/ROM-Install/Backup/Noroot/Open_Android_Backup_v1.0.18_Bundle/backup.sh");
}

/* main function of backup_noroot*/
void backup_noroot(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[3][20] = {"install depends" "Download", "Starten"};

    gtk_init(&argc, &argv);

    // create new windows
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Open Android Backup");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // create a grid
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // add buttons and connect them with callback
    for (int i = 0; i < 3; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);
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

    /* change the style of the buttons to quick settings buttons from android 12 - css is used for this*/
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "button {\n"
                                    "    background-color: #8B0000;\n" /* darkred */
            						"	 border: none;\n"
            						"	 border-radius: 12px;\n" /* round corners */
            						"	 padding: 12px 24px;\n" /* inside distance */
            						"	 color: #ffffff;\n" /* White text */
            						"	 font-size: 16px;\n" /* Font size */
            						"	 font-weight: 500;\n" /* Medium font */
            						"	 text-align: center;\n" /* Centre text */
            						"	 box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);\n" /* Light shade */
            						"	 transition: background-color 0.3s ease, box-shadow 0.3s ease;\n" /* Animation */
                                    "}\n"
                                    "button:hover {\n"
                                    "    background-color: #A52A2A;\n" /* Brighter red on hover */
            						"	 box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);\n" /* Amplify shadows */
                                    "}\n",
                                    -1,
                                    NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);

    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();
}
    
