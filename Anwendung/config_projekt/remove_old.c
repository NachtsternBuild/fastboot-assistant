/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *			funkelnde Datenkristalle		 *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - remove_old			 	 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include "program_functions.h"

void remove_old_function(const char *option) 
{
    GtkWidget *dialog;
    const char *title, *message;

    if (strcmp(option, "rom_install") == 0) 
    {
        title = "Löschen ROM-Install";
        message = "Lösche ~/Downloads/ROM-Install\n";
        system("rm -r ~/Downloads/ROM-Install");
    } 
    
    else if (strcmp(option, "update_project") == 0) 
    {
        title = "Löschen Update-Verzeichnis";
        message = "Lösche ~/Downloads/UpdateProjekt122\n";
        system("rm -r ~/Downloads/UpdateProjekt122");
    } 
    
    else if (strcmp(option, "file_on_rom_install") == 0) 
    {
        title = "Lösche Dateien in ROM-Install";
        message = "Lösche Dateien\n";
        const char *directory_path = "~/Downloads/ROM-Install/";
        delete_files_in_dir(directory_path);
    } 
    
    else 
    {
        title = "Unbekannte Option";
        message = "Sie wissen auch nicht was sie wollen, oder?";
    }

    dialog = gtk_message_dialog_new(NULL,
                                     GTK_DIALOG_MODAL,
                                     GTK_MESSAGE_INFO,
                                     GTK_BUTTONS_OK,
                                     "%s\n\n%s", title, message);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Callback function when the button is clicked
void button_remove_old_start(GtkWidget *widget, gpointer data) 
{
    const char *option = (const char *)data;
    remove_old_function(option);
}

void remove_old(int argc, char *argv[]) 
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Löschen von:");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create buttons
    GtkWidget *button_rom_install = gtk_button_new_with_label("ROM-Install");
    g_signal_connect(button_rom_install, "clicked", G_CALLBACK(button_remove_old_start), "rom_install");

    GtkWidget *button_update_project = gtk_button_new_with_label("UpdateProjekt122");
    g_signal_connect(button_update_project, "clicked", G_CALLBACK(button_remove_old_start), "update_project");
    
    GtkWidget *button_files_rom_install = gtk_button_new_with_label("Dateien in ROM-Install");
    g_signal_connect(button_files_rom_install, "clickes", G_CALLBACK(button_remove_old_start), "file_on_rom_install");

    // Pack buttons into the box
    gtk_box_pack_start(GTK_BOX(vbox), button_rom_install, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_update_project, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_files_rom_install, TRUE, TRUE, 0);
    
    // Show all the widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}
