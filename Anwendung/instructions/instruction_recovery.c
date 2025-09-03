/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_recovery	 *
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
void instruction_recovery(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("instruction_recovery");  
    apply_language();
	
	// char for the next page button
	const char *next_page_char = _("Next");
	const char *back_page_char = _("Back");
	const char *exit_page_char = _("Exit");
	
    // page 1
    GtkWidget *page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    GtkWidget *button_reco1 = gtk_button_new_with_label(_("Recovery"));
    // label 1
    GtkWidget *label_reco1_1 = gtk_label_new(_("Recovery mode is a special boot menu on Android devices that is used to maintain and restore the system."));
    gtk_label_set_wrap(GTK_LABEL(label_reco1_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_reco1_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_reco1_2 = gtk_label_new(_("This enables functions such as resetting to factory settings, installing updates and some other basic functions to restore the system."));
    gtk_label_set_wrap(GTK_LABEL(label_reco1_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_reco1_2), PANGO_WRAP_WORD_CHAR);	
    // label 3
    GtkWidget *label_reco1_3 = gtk_label_new(_("Custom coverys have many more functions than the stock recoverys from the same manufacturer. These usually only have basic features on board."));
    gtk_label_set_wrap(GTK_LABEL(label_reco1_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_reco1_3), PANGO_WRAP_WORD_CHAR);	
    
    // new button
    GtkWidget *button_reco_1 = create_icon_nav_button_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_reco_2 = create_icon_nav_button_no_callback("application-exit-symbolic", exit_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_reco1);
    gtk_box_append(GTK_BOX(page1), label_reco1_1);
    gtk_box_append(GTK_BOX(page1), label_reco1_2);
    gtk_box_append(GTK_BOX(page1), label_reco1_3);
    gtk_box_append(GTK_BOX(page1), button_reco_1);
    gtk_box_append(GTK_BOX(page1), button_reco_2);
    
    // position left of the labels
    gtk_widget_set_halign(label_reco1_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_reco1_2, GTK_ALIGN_START);
    gtk_widget_set_halign(label_reco1_3, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_reco1_1, 15);
    gtk_widget_set_margin_start(label_reco1_2, 15);
    gtk_widget_set_margin_start(label_reco1_3, 15);

    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_reco_1")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page1, "inst_reco_1");
	}
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "inst_reco_1");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_reco_1), "stack", stack);
	g_signal_connect(button_reco_1, "clicked", G_CALLBACK(switch_page), "inst_reco_2");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_reco_2), "stack", stack);
	g_signal_connect(button_reco_2, "clicked", G_CALLBACK(switch_page), "instruction_flash");
    
    /* page 2 */
    GtkWidget *page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    GtkWidget *button_reco2 = gtk_button_new_with_label(_("Flashing the recovery"));
    // label 1
    GtkWidget *label_reco2_1 = gtk_label_new(_("1. Check whether there is a custom recovery for your device. \n2. Download a corresponding recovery. \n3. Prepare the images for the flash."));
    gtk_label_set_wrap(GTK_LABEL(label_reco2_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_reco2_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_reco2_2 = gtk_label_new(_("4. Boot your device into fastboot mode. \n5. Open the bootloader. Some devices do not support the fastboot method."));
    gtk_label_set_wrap(GTK_LABEL(label_reco2_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_reco2_2), PANGO_WRAP_WORD_CHAR);	
    // label 3
    GtkWidget *label_reco2_3 = gtk_label_new(_("Find out more about your chipset and the device. \n6. Flash the recovery image with this application. \n7. Boot your device into the recovery."));
    gtk_label_set_wrap(GTK_LABEL(label_reco2_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_reco2_3), PANGO_WRAP_WORD_CHAR);	
    // new button
    GtkWidget *button_reco_3 = create_icon_nav_button_no_callback("pan-start-symbolic", back_page_char);
    GtkWidget *button_reco_4 = create_icon_nav_button_no_callback("application-exit-symbolic", exit_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_reco2);
    gtk_box_append(GTK_BOX(page2), label_reco2_1);
    gtk_box_append(GTK_BOX(page2), label_reco2_2);
    gtk_box_append(GTK_BOX(page2), label_reco2_3);
    gtk_box_append(GTK_BOX(page2), button_reco_3);
    gtk_box_append(GTK_BOX(page2), button_reco_4);
    
    // position left of the labels
    gtk_widget_set_halign(label_reco2_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_reco2_2, GTK_ALIGN_START);
    gtk_widget_set_halign(label_reco2_3, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_reco2_1, 15);
    gtk_widget_set_margin_start(label_reco2_2, 15);
    gtk_widget_set_margin_start(label_reco2_3, 15);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_reco_2")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page2, "inst_reco_2");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_reco_3), "stack", stack);
	g_signal_connect(button_reco_3, "clicked", G_CALLBACK(switch_page), "inst_reco_1");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_reco_4), "stack", stack);
	g_signal_connect(button_reco_4, "clicked", G_CALLBACK(switch_page), "instruction_flash");
    
    LOG_INFO("end instruction_recovery");
}
