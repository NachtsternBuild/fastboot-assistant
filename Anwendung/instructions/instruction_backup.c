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
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

void instruction_backup(int argc, char *argv[]) 
{
    g_print("Log: instruction_backup\n");
    // GTK init
    gtk_init();

    apply_theme();
    apply_language();
    
    GtkWidget *window, *notebook;
    GtkWidget *page_backup1;
    GtkWidget *label_backup1_1, *label_backup1_2, *label_backup1_3;
    GtkWidget *button_backup1;
    
    // create the main window
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Backup");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);

    // create the notebook
    notebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // page 1
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    button_backup1 = gtk_button_new_with_label("Backups");
    label_backup1_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Das Backup dient dazu, sie vor Datenverlust zu schützen \nund ist vor jedem flash Vorgang zu empfehlen. \nEs gibt zwei Varianten des Backups: " : "The backup serves to protect you from data loss \nand is recommended before every flash operation. \nThere are two types of backup: ");
    label_backup1_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Das Backup mit Root 2. Das Backup ohne Root. \nBeim Backup mit Root werden die Partitionen als Images \nkopiert und können später wieder geflasht werden." : "1. the backup with root 2. the backup without root. \nWhen backing up with root, the partitions are copied as images and can be flashed again later.");
    label_backup1_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Beim Backup ohne Root kommt 'Open Android Backup' zum Einsatz. \nEs ist ein Open Source Tool für Linux." : "'Open Android Backup' is used for backups without root. \nIt is an open source tool for Linux.");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_backup1);
    gtk_box_append(GTK_BOX(page1), label_backup1_1);
    gtk_box_append(GTK_BOX(page1), label_backup1_2);
    gtk_box_append(GTK_BOX(page1), label_backup1_3);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, gtk_label_new("Backup");
    
    // show all widgets
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop); 
    g_print("Log: end instruction_backup\n");
}
