/**
* instruction_backup.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

/* main function */
void instruction_backup(GtkWidget *widget, gpointer stack) 
{
    LOGD("instruction_backup");
    
	// char for the next page button
	const char *exit_page_char = _("Exit");
	
	/* page 1 */
    GtkWidget *page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    GtkWidget *button_backup1 = gtk_button_new_with_label("Backups");
    // label 1
    GtkWidget *label_backup1_1 = gtk_label_new(_("The backup serves to protect you from data loss and is recommended before every flash operation. There are two types of backup: "));
    gtk_label_set_wrap(GTK_LABEL(label_backup1_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_backup1_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_backup1_2 = gtk_label_new(_("1. The backup with root. \n2. The backup without root. \nWhen backing up with root, the partitions are copied as images and can be flashed again later."));
    gtk_label_set_wrap(GTK_LABEL(label_backup1_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_backup1_2), PANGO_WRAP_WORD_CHAR);	
    // label 3
    GtkWidget *label_backup1_3 = gtk_label_new(_("'Open Android Backup' is used for backups without root. It is an open source tool for Linux."));
    gtk_label_set_wrap(GTK_LABEL(label_backup1_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_backup1_3), PANGO_WRAP_WORD_CHAR);	
    
    // new button
    GtkWidget *button_backup2 = create_button_icon_no_callback("application-exit-symbolic", exit_page_char);
    
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
    
    LOGD("end instruction_backup");
}
