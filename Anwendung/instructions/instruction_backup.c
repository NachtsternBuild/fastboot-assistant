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
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

/* main function */
void instruction_backup(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("instruction_backup");
    apply_language();
	
	// char for the next page button
	const char *exit_page_char = strcmp(language, "de") == 0 ? "Verlassen" : "Exit";
	
	/* page 1 */
    GtkWidget *page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    GtkWidget *button_backup1 = gtk_button_new_with_label("Backups");
    // label 1
    GtkWidget *label_backup1_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Das Backup dient dazu, sie vor Datenverlust zu schützen und ist vor jedem flash Vorgang zu empfehlen. Es gibt zwei Varianten des Backups: " : "The backup serves to protect you from data loss and is recommended before every flash operation. There are two types of backup: ");
    gtk_label_set_wrap(GTK_LABEL(label_backup1_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_backup1_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_backup1_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Das Backup mit Root \n2. Das Backup ohne Root. \nBeim Backup mit Root werden die Partitionen als Images kopiert und können später wieder geflasht werden." : "1. The backup with root. \n2. The backup without root. \nWhen backing up with root, the partitions are copied as images and can be flashed again later.");
    gtk_label_set_wrap(GTK_LABEL(label_backup1_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_backup1_2), PANGO_WRAP_WORD_CHAR);	
    // label 3
    GtkWidget *label_backup1_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Beim Backup ohne Root kommt 'Open Android Backup' zum Einsatz. Es ist ein Open Source Tool für Linux." : "'Open Android Backup' is used for backups without root. It is an open source tool for Linux.");
    gtk_label_set_wrap(GTK_LABEL(label_backup1_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_backup1_3), PANGO_WRAP_WORD_CHAR);	
    
    // new button
    GtkWidget *button_backup2 = create_icon_nav_button_no_callback("application-exit-symbolic", exit_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_backup1);
    gtk_box_append(GTK_BOX(page1), label_backup1_1);
    gtk_box_append(GTK_BOX(page1), label_backup1_2);
    gtk_box_append(GTK_BOX(page1), label_backup1_3);
    gtk_box_append(GTK_BOX(page1), button_backup2);
    
    // position left of the labels
    gtk_widget_set_halign(label_backup1_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_backup1_2, GTK_ALIGN_START);
    gtk_widget_set_halign(label_backup1_3, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_backup1_1, 15);
    gtk_widget_set_margin_start(label_backup1_2, 15);
    gtk_widget_set_margin_start(label_backup1_3, 15);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_backup")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page1, "inst_backup");
	}
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "inst_backup");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_backup2), "stack", stack);
	g_signal_connect(button_backup2, "clicked", G_CALLBACK(switch_page), "instruction_prepare_flash");
    
    LOG_INFO("end instruction_backup");
}
