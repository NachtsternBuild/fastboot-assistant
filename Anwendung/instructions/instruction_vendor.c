/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_vendor		 *
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
void instruction_vendor(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("instruction_vendor");
    apply_language();
	
	// char for the next page button
	const char *exit_page_char = strcmp(language, "de") == 0 ? "Verlassen" : "Exit";
	
	/* page 1 */
    GtkWidget *page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    GtkWidget *button_vndk1 = gtk_button_new_with_label("VNDK");
    // label 1
    GtkWidget *label_vndk1_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Alles was mit 'Vendor' bezeichnet wird, sind hersteller- oder gerätspezifische Komponenten des Betriebssystems. Änderungen daran können zu Problemen führen." : "Everything labeled 'Vendor' are manufacturer- or device-specific components of the operating system. Changes to these can lead to problems.");
    gtk_label_set_wrap(GTK_LABEL(label_vndk1_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_vndk1_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_vndk1_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Die VNDK-Version (Vendor Native Development Kit) ist eine Sammlung von Bibliotheken und Richtlinien, durch die den hardwarespezifische Teil von Rest des Androids trennt." : "The VNDK version (Vendor Native Development Kit) is a collection of libraries and guidelines that separates the hardware-specific part from the rest of Android.");
    gtk_label_set_wrap(GTK_LABEL(label_vndk1_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_vndk1_2), PANGO_WRAP_WORD_CHAR);	
    // label 3
    GtkWidget *label_vndk1_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Dadurch lassen sich Updates und Wartung erleichtern, weil herstellerspezifische Anpassungen nicht die Kompatibilität und Stabilität des Android-Systems beeinträchtigen." : "This makes updates and maintenance easier because manufacturer-specific adjustments do not affect the compatibility and stability of the Android system.");
    gtk_label_set_wrap(GTK_LABEL(label_vndk1_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_vndk1_3), PANGO_WRAP_WORD_CHAR);	
	
    // new button
    GtkWidget *button_vndk2 = create_icon_nav_button_no_callback("application-exit-symbolic", exit_page_char);
      
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_vndk1);
    gtk_box_append(GTK_BOX(page1), label_vndk1_1);
    gtk_box_append(GTK_BOX(page1), label_vndk1_2);
    gtk_box_append(GTK_BOX(page1), label_vndk1_3);
    gtk_box_append(GTK_BOX(page1), button_vndk2);
    
    // position left of the labels
    gtk_widget_set_halign(label_vndk1_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_vndk1_2, GTK_ALIGN_START);
    gtk_widget_set_halign(label_vndk1_3, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_vndk1_1, 15);
    gtk_widget_set_margin_start(label_vndk1_2, 15);
    gtk_widget_set_margin_start(label_vndk1_3, 15);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_vndk")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page1, "inst_vndk");
	}
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "inst_vndk");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_vndk2), "stack", stack);
	g_signal_connect(button_vndk2, "clicked", G_CALLBACK(switch_page), "instruction_flash");
    
    
    LOG_INFO("end instruction_vendor");
}
