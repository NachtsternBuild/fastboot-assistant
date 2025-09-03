/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_info		 *
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

#define MAX_BUFFER_SIZE 256

/* main function */
void instruction_info(GtkWidget *widget, gpointer stack) 
{
	LOG_INFO("instruction_info");
	apply_language();
	
	// char for the next page button
	const char *next_page_char = _("Next");
	const char *back_page_char = _("Back");
	const char *exit_page_char = _("Exit");
	
	/* page 1 */
    GtkWidget *page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    GtkWidget *button_info1 = gtk_button_new_with_label(_("Project Treble"));
    // label 1
    GtkWidget *label_info1_1 = gtk_label_new(_("Project Treble is an Android initiative from Google that separates the operating system and hardware components."));
    gtk_label_set_wrap(GTK_LABEL(label_info1_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_info1_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_info1_2 = gtk_label_new(_("This makes it easier for manufacturers to provide updates while the OS is independent of chipset-specific drivers."));
    gtk_label_set_wrap(GTK_LABEL(label_info1_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_info1_2), PANGO_WRAP_WORD_CHAR);	
	
    // new button
    GtkWidget *button_info_1 = create_icon_nav_button_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_info_2 = create_icon_nav_button_no_callback("application-exit-symbolic", exit_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_info1);
    gtk_box_append(GTK_BOX(page1), label_info1_1);
    gtk_box_append(GTK_BOX(page1), label_info1_2);
    gtk_box_append(GTK_BOX(page1), button_info_1);
    gtk_box_append(GTK_BOX(page1), button_info_2);
	
	// position left of the labels
    gtk_widget_set_halign(label_info1_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_info1_2, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_info1_1, 15);
    gtk_widget_set_margin_start(label_info1_2, 15);

    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_info_1")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page1, "inst_info_1");
	}
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "inst_info_1");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_info_1), "stack", stack);
	g_signal_connect(button_info_1, "clicked", G_CALLBACK(switch_page), "inst_info_2");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_info_2), "stack", stack);
	g_signal_connect(button_info_2, "clicked", G_CALLBACK(switch_page), "instruction_GUI");
	
	/* page 2 */
    GtkWidget *page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    GtkWidget *button_info2 = gtk_button_new_with_label(_("a/b Partitioning"));
    // label 1
    GtkWidget *label_info2_1 = gtk_label_new(_("The A/B partitioning scheme uses two system partitions for seamless updates by switching the slot, provides higher security and continuous operation."));
    gtk_label_set_wrap(GTK_LABEL(label_info2_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_info2_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_info2_2 = gtk_label_new(_("The Only-A scheme has only one partition, allows easier management, but is more prone to errors during the update."));
    gtk_label_set_wrap(GTK_LABEL(label_info2_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_info2_2), PANGO_WRAP_WORD_CHAR);	
    
    // new button
    GtkWidget *button_info_3 = create_icon_nav_button_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_info_4 = create_icon_nav_button_no_callback("pan-start-symbolic", back_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_info2);
    gtk_box_append(GTK_BOX(page2), label_info2_1);
    gtk_box_append(GTK_BOX(page2), label_info2_2);
    gtk_box_append(GTK_BOX(page2), button_info_3);
    gtk_box_append(GTK_BOX(page2), button_info_4);
    
    // position left of the labels
    gtk_widget_set_halign(label_info2_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_info2_2, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_info2_1, 15);
    gtk_widget_set_margin_start(label_info2_2, 15);
	
	// add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_info_2")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page2, "inst_info_2");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_info_3), "stack", stack);
	g_signal_connect(button_info_3, "clicked", G_CALLBACK(switch_page), "inst_info_3");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_info_4), "stack", stack);
	g_signal_connect(button_info_4, "clicked", G_CALLBACK(switch_page), "inst_info_1");
	
	/* page 3 */
    GtkWidget *page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    GtkWidget *button_info3 = gtk_button_new_with_label(_("System-as-root"));
    // label 1
	GtkWidget *label_info3_1 = gtk_label_new(_("System-as-root is an Android mechanism in which the system image is mounted as the root file system."));
	gtk_label_set_wrap(GTK_LABEL(label_info3_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_info3_1), PANGO_WRAP_WORD_CHAR);	
	// label 2
	GtkWidget *label_info3_2 = gtk_label_new(_("This improves the separation of system and vendor partitions, increases security and facilitates system updates and the management of authorizations."));
	gtk_label_set_wrap(GTK_LABEL(label_info3_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_info3_2), PANGO_WRAP_WORD_CHAR);	

    // new button
    GtkWidget *button_info_5 = create_icon_nav_button_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_info_6 = create_icon_nav_button_no_callback("pan-start-symbolic", back_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page3), button_info3);
    gtk_box_append(GTK_BOX(page3), label_info3_1);
    gtk_box_append(GTK_BOX(page3), label_info3_2);
    gtk_box_append(GTK_BOX(page3), button_info_5);
    gtk_box_append(GTK_BOX(page3), button_info_6);
    
    // position left of the labels
    gtk_widget_set_halign(label_info3_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_info3_2, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_info3_1, 15);
    gtk_widget_set_margin_start(label_info3_2, 15);
	
	// add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_info_3")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page3, "inst_info_3");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_info_5), "stack", stack);
	g_signal_connect(button_info_5, "clicked", G_CALLBACK(switch_page), "inst_info_4");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_info_6), "stack", stack);
	g_signal_connect(button_info_6, "clicked", G_CALLBACK(switch_page), "inst_info_2");
	
	/* page 4 */
    GtkWidget *page4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    GtkWidget *button_info4 = gtk_button_new_with_label(_("Kernel"));
    // label 1
	GtkWidget *label_info4_1 = gtk_label_new(_("The kernel is the core of an operating system, which communicates directly with the hardware and manages resources such as CPU, memory and devices."));
	gtk_label_set_wrap(GTK_LABEL(label_info4_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_info4_1), PANGO_WRAP_WORD_CHAR);	
	// label 2
	GtkWidget *label_info4_2 = gtk_label_new(_("The kernel forms the interface between hardware, applications and the rest of the system and ensures secure and efficient execution."));
	gtk_label_set_wrap(GTK_LABEL(label_info4_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_info4_2), PANGO_WRAP_WORD_CHAR);	
	// label 3
	GtkWidget *label_info4_3 = gtk_label_new(_("Android versions are only compatible with certain Kernel versions; if incompatible, Android will not start."));
    gtk_label_set_wrap(GTK_LABEL(label_info4_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_info4_3), PANGO_WRAP_WORD_CHAR);	
	
    // new button
    GtkWidget *button_info_7 = create_icon_nav_button_no_callback("pan-start-symbolic", back_page_char);
    GtkWidget *button_info_8 = create_icon_nav_button_no_callback("application-exit-symbolic", exit_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page4), button_info4);
    gtk_box_append(GTK_BOX(page4), label_info4_1);
    gtk_box_append(GTK_BOX(page4), label_info4_2);
    gtk_box_append(GTK_BOX(page4), label_info4_3);
    gtk_box_append(GTK_BOX(page4), button_info_7);
    gtk_box_append(GTK_BOX(page4), button_info_8);
	
	// position left of the labels
    gtk_widget_set_halign(label_info4_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_info4_2, GTK_ALIGN_START);
    gtk_widget_set_halign(label_info4_3, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_info4_1, 15);
    gtk_widget_set_margin_start(label_info4_2, 15);
    gtk_widget_set_margin_start(label_info4_3, 15);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_info_4")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page4, "inst_info_4");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_info_7), "stack", stack);
	g_signal_connect(button_info_7, "clicked", G_CALLBACK(switch_page), "inst_info_3");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_info_8), "stack", stack);
	g_signal_connect(button_info_8, "clicked", G_CALLBACK(switch_page), "instruction_GUI");
	
	LOG_INFO("end instruction_info");
}
