/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_preflash	 *
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

// function to open twrp site
void twrp(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("twrp");
    const char *twrp_url = "https://www.twrp.me/";    
	open_url(twrp_url);
	LOG_INFO("end twrp");
}

// function that open the /e/ OS site
void e_OS(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("e_OS");
    const char *e_OS_url = "https://e.foundation/e-os/";
	open_url(e_OS_url);
	LOG_INFO("end e_OS");
}

// function to open the lineage OS site
void lineage_os(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("lineage_os");
    const char *lineage_os_url = "https://lineageos.org/";
	open_url(lineage_os_url);
	LOG_INFO("end lineage_os");
}

// function to open the site of project elixir
void project_elixir(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("project_elixir");
    const char *project_elixir_url = "https://projectelixiros.com/home";
	open_url(project_elixir_url);
	LOG_INFO("end project_elixir");
}

// function to open the site of crdroid
void crdroid(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("crdroid");
    const char *crdroid_url = "https://crdroid.net/";
	open_url(crdroid_url);
	LOG_INFO("end crdroid");
}

// function to open the site of evolution x
void evolution_x(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("evolution_x");
    const char *evolution_x_url = "https://evolution-x.org/";
	open_url(evolution_x_url);
	LOG_INFO("end evolution_x");
}

/* main function */
void instruction_preflash(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("instruction_preflash");
    apply_language();
	
	// char for the next page button
	const char *next_page_char = strcmp(language, "de") == 0 ? "Weiter" : "Next";
	const char *back_page_char = strcmp(language, "de") == 0 ? "Zurück" : "Back";
	const char *exit_page_char = strcmp(language, "de") == 0 ? "Verlassen" : "Exit";
	
	/* page 1 */
    GtkWidget *page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    GtkWidget *button_preflash1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Vorbereitung Flash" : "Preparation Flash");
    // label 1
    GtkWidget *label_preflash1_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Informieren sie genauer über ihr Gerät und den Chipsatz des Gerätes. \n2. Suchen sie nach entsprechenden Custom-ROMs, Custom-Recoverys oder GSIs." : "1. Provide more detailed information about your device and the chipset of the device. \n2. Search for corresponding custom ROMs, custom recoverys or GSIs.");
    gtk_label_set_wrap(GTK_LABEL(label_preflash1_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_preflash1_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_preflash1_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "3. Prüfen sie die Verfügbarkeit von Project Treble für ihr Gerät. \n4. Prüfen sie welches Partitionierungsschema auf ihrem Gerät vorliegt (a/b-devices oder only-a-devices)." : "3. Check the availability of Project Treble for your device. \n4. Check which partitioning scheme is available on your device (a/b-devices or only-a-devices).");
    gtk_label_set_wrap(GTK_LABEL(label_preflash1_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_preflash1_2), PANGO_WRAP_WORD_CHAR);	
    // label 3
    GtkWidget *label_preflash1_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "5. Sichern sie ihre Daten lokal und wenn sie wollen in einer Cloud. \n6. Laden sie alle Dateien herunter die sie für den flash brauchen." : "5. Back up your data locally and, if you wish, in a cloud. \n6. Download all the files you need for the flash.");
    gtk_label_set_wrap(GTK_LABEL(label_preflash1_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_preflash1_3), PANGO_WRAP_WORD_CHAR);	
    // label 4
    GtkWidget *label_preflash1_4 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "7. Lesen sie die Anleitungen der Entwickler vor dem Flash. \n8. Kopieren sie alle Dateien die geflasht werden, nach: '~/Downloads/ROM-Install/'" : "7. Read the developer's instructions before using Flash. \n8. Copy all files that are flashed to: '~/Downloads/ROM-Install/'");
    gtk_label_set_wrap(GTK_LABEL(label_preflash1_4), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_preflash1_4), PANGO_WRAP_WORD_CHAR);	
	
    // new button
    GtkWidget *button_preflash2 = create_icon_nav_button_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_preflash3 = create_icon_nav_button_no_callback("application-exit-symbolic", exit_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_preflash1);
    gtk_box_append(GTK_BOX(page1), label_preflash1_1);
    gtk_box_append(GTK_BOX(page1), label_preflash1_2);
    gtk_box_append(GTK_BOX(page1), label_preflash1_3);
    gtk_box_append(GTK_BOX(page1), label_preflash1_4);
    gtk_box_append(GTK_BOX(page1), button_preflash2);
    gtk_box_append(GTK_BOX(page1), button_preflash3);
    
    // position left of the labels
    gtk_widget_set_halign(label_preflash1_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_preflash1_2, GTK_ALIGN_START);
    gtk_widget_set_halign(label_preflash1_3, GTK_ALIGN_START);
    gtk_widget_set_halign(label_preflash1_4, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_preflash1_1, 15);
    gtk_widget_set_margin_start(label_preflash1_2, 15);
    gtk_widget_set_margin_start(label_preflash1_3, 15);
    gtk_widget_set_margin_start(label_preflash1_4, 15);

    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_preflash_1")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page1, "inst_preflash_1");
	}
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "inst_preflash_1");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_preflash2), "stack", stack);
	g_signal_connect(button_preflash2, "clicked", G_CALLBACK(switch_page), "inst_preflash_2");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_preflash3), "stack", stack);
	g_signal_connect(button_preflash3, "clicked", G_CALLBACK(switch_page), "instruction_prepare_flash");
    
    // page 2
    GtkWidget *page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    GtkWidget *button_preflash4 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Einige Custom ROMs" : "Some custom ROMs");
    GtkWidget *button_preflash2_1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "TWRP (ein Recovery)" : "TWRP (a recovery)");
    GtkWidget *button_preflash2_2 = gtk_button_new_with_label("/e/ OS");
    GtkWidget *button_preflash2_3 = gtk_button_new_with_label("LineageOS");
    GtkWidget *button_preflash2_4 = gtk_button_new_with_label("Project Elixir");
    GtkWidget *button_preflash2_5 = gtk_button_new_with_label("CrDroid");
    GtkWidget *button_preflash2_6 = gtk_button_new_with_label("Evolution X");
    
    // new button
    GtkWidget *button_preflash5 = create_icon_nav_button_no_callback("pan-start-symbolic", back_page_char);
    GtkWidget *button_preflash6 = create_icon_nav_button_no_callback("application-exit-symbolic", exit_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_preflash4);
    gtk_box_append(GTK_BOX(page2), button_preflash2_1);
    gtk_box_append(GTK_BOX(page2), button_preflash2_2);
    gtk_box_append(GTK_BOX(page2), button_preflash2_3);
    gtk_box_append(GTK_BOX(page2), button_preflash2_4);
    gtk_box_append(GTK_BOX(page2), button_preflash2_5);
    gtk_box_append(GTK_BOX(page2), button_preflash2_6);
    gtk_box_append(GTK_BOX(page2), button_preflash5);
    gtk_box_append(GTK_BOX(page2), button_preflash6);

    // connect everything
    g_signal_connect(button_preflash2_1, "clicked", G_CALLBACK(twrp), stack);
    g_signal_connect(button_preflash2_2, "clicked", G_CALLBACK(e_OS), stack);
    g_signal_connect(button_preflash2_3, "clicked", G_CALLBACK(lineage_os), stack);
    g_signal_connect(button_preflash2_4, "clicked", G_CALLBACK(project_elixir), stack);
    g_signal_connect(button_preflash2_5, "clicked", G_CALLBACK(crdroid), stack);
    g_signal_connect(button_preflash2_6, "clicked", G_CALLBACK(evolution_x), stack);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_preflash_2")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page2, "inst_preflash_2");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_preflash5), "stack", stack);
	g_signal_connect(button_preflash5, "clicked", G_CALLBACK(switch_page), "inst_preflash_1");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_preflash6), "stack", stack);
	g_signal_connect(button_preflash6, "clicked", G_CALLBACK(switch_page), "instruction_prepare_flash");
    
    LOG_INFO("end instruction_preflash");
}
