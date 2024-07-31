/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_backup		 *
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

void instruction_backup(int argc, char *argv[]) 
{
    // Initiate GTK
    gtk_init(&argc, &argv);

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Anleitung Backup");
    gtk_widget_set_size_request(window, 1000, 950);

    // Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Frame for each information field
    GtkWidget *frame25 = gtk_frame_new(NULL);
    
    // Vertical box layout for the frames
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Creation of text labels with the text to be displayed
    const char *backup_text = "\nDas Backup dient dazu, sie vor Datenverlust zu schützen \nund ist vor jedem flash Vorgang zu empfehlen. \nEs gibt zwei Varianten des Backups: \n \n1. Das Backup mit Root \n2. Das Backup ohne Root.\n \nBeim Backup mit Root werden die Partitionen als Images \nkopiert und können später wieder geflasht werden. \nBeim Backup ohne Root kommt 'Open Android Backup' zum Einsatz. \nEs ist ein Open Source Tool für Linux.\n";
    GtkWidget *label_backup = gtk_label_new(backup_text);
    gtk_container_add(GTK_CONTAINER(frame25), label_backup);
    
    // Add frames to the main window
    gtk_box_pack_start(GTK_BOX(vbox), frame25, TRUE, TRUE, 5);

    // Show all elements
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}

