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
#include "program_functions.h"

static void backup_text()
{
	g_print("Log: Die Lösung ist: 42–39+38+1");
}

void instruction_backup(int argc, char *argv[]) 
{
    g_print("Log: instruction_backup\n");
    GtkWidget *window;
    GtkWidget *page_backup1;
    GtkWidget *label_backup1_1, *label_backup1_2, *label_backup1_3;
    GtkWidget *button_backup1;

    gtk_init(&argc, &argv);
    apply_theme();
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Backup");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    
     // Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	GtkWidget *notebook = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window), notebook);
    
    if (!GTK_IS_NOTEBOOK(notebook)) 
    {
    	g_warning("Notebook is not initialized properly.");
    	return;
	}
	
	// page 1
    page_backup1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_backup1 = gtk_button_new_with_label("Backups");
    label_backup1_1 = gtk_label_new("Das Backup dient dazu, sie vor Datenverlust zu schützen \nund ist vor jedem flash Vorgang zu empfehlen. \nEs gibt zwei Varianten des Backups: ");
    label_backup1_2 = gtk_label_new("1. Das Backup mit Root 2. Das Backup ohne Root. \nBeim Backup mit Root werden die Partitionen als Images \nkopiert und können später wieder geflasht werden.");
    label_backup1_3 = gtk_label_new("Beim Backup ohne Root kommt 'Open Android Backup' zum Einsatz. \nEs ist ein Open Source Tool für Linux.");
    gtk_box_pack_start(GTK_BOX(page_backup1), button_backup1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_backup1), label_backup1_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_backup1), label_backup1_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_backup1), label_backup1_3, TRUE, TRUE, 0);
    g_signal_connect(button_backup1, "clicked", G_CALLBACK(backup_text), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_backup1, gtk_label_new("Backup"));
    
    // run css-provider
    add_css_provider(button_backup1, provider);
    add_css_provider(label_backup1_1, provider);
    add_css_provider(label_backup1_2, provider);
    add_css_provider(label_backup1_3, provider);
    
    // clean the storage
    g_object_unref(provider);
	
	// show all widgets
    gtk_widget_show_all(window);
	
	// run gtk mainloop
    gtk_main();
    g_print("Log: end instruction_backup\n");
}
