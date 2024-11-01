/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_gsi		 *
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

static void gsi_text()
{
	g_print("Log: Bringt auch nichts!\n");
}

void instruction_gsi(int argc, char *argv[]) 
{	
	g_print("Log: instruction_gsi\n");
	GtkWidget *window;
    GtkWidget *page_gsi1, *page_gsi2, *page_gsi3, *page_gsi4;
    GtkWidget *label_gsi1_1, *label_gsi1_2, *label_gsi2_1, *label_gsi2_2, *label_gsi2_3, *label_gsi3_1, *label_gsi4_1;
    GtkWidget *button_gsi1, *button_gsi2, *button_gsi3, *button_gsi4, *button_gsi5, *button_gsi6, *button_gsi7;
    
	gtk_init(&argc, &argv);
	apply_theme();
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Generic System Image");
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
    page_gsi1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_gsi1 = gtk_button_new_with_label("Hinweise");
    label_gsi1_1 = gtk_label_new("GSI (Generic System Image) ist ein Android-System-Image, dass \neine Unterstützung von Project Treble (siehe weitere Infos) \nvoraussetzt.");
    label_gsi1_2 = gtk_label_new("GSI ermöglichen Android-Geräten ohne Custom-ROMs für manuelles \naufspielen von neueren Android-Versionen.");
    button_gsi2 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_gsi1), button_gsi1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_gsi1), label_gsi1_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_gsi1), label_gsi1_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_gsi1), button_gsi2, FALSE, FALSE, 0);
    g_signal_connect(button_gsi1, "clicked", G_CALLBACK(gsi_text), notebook);
    g_signal_connect(button_gsi2, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_gsi1, gtk_label_new("Hinweise"));
    
    // run css-provider
    add_css_provider(button_gsi1, provider);
    add_css_provider(label_gsi1_1, provider);
    add_css_provider(label_gsi1_2, provider);
    add_css_provider(button_gsi2, provider);
    
    // page 2
    page_gsi2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_gsi3 = gtk_button_new_with_label("GSI Flashen");
    label_gsi2_1 = gtk_label_new("1. Prüfen sie ob ihr Gerät mit Project Treble kompatibel ist. \n2. Laden sie ein entsprechendes GSI herunter. \n3. Vorbereiten sie die Images für den Flash.\n");
    label_gsi2_2 = gtk_label_new("4. Booten sie ihr Gerät in Fastboot mit der Anwendung. \n5. Öffnen sie den Bootloader.\nManche Geräte unterstützen nicht die Methode über Fastboot.");
    label_gsi2_3 = gtk_label_new("Als Methoden des Flashs gibt es die \nAlternativen 'dirty flash'(1) und 'clean flash'(2).");
    button_gsi4 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_gsi2), button_gsi3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_gsi2), label_gsi2_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_gsi2), label_gsi2_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_gsi2), label_gsi2_3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_gsi2), button_gsi4, FALSE, FALSE, 0);
    g_signal_connect(button_gsi3, "clicked", G_CALLBACK(gsi_text), notebook);
    g_signal_connect(button_gsi4, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_gsi2, gtk_label_new("Vorbereitung"));
    
    // run css-provider
    add_css_provider(button_gsi3, provider);
    add_css_provider(label_gsi2_1, provider);
    add_css_provider(label_gsi2_2, provider);
    add_css_provider(label_gsi2_3, provider);
    add_css_provider(button_gsi4, provider);
    
    // page 3
    page_gsi3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_gsi5 = gtk_button_new_with_label("Clean Flash");
    label_gsi3_1 = gtk_label_new("1. Löschen sie alle Nutzerdaten. \n2. Flashen sie das System-Image \n3. Flashen sie im Bedarfsfall ein vbmeta.img. \n4. Starten sie ihr Gerät neu.");
    button_gsi6 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_gsi3), button_gsi5, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_gsi3), label_gsi3_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_gsi3), button_gsi6, FALSE, FALSE, 0);
    g_signal_connect(button_gsi5, "clicked", G_CALLBACK(gsi_text), notebook);
    g_signal_connect(button_gsi6, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_gsi3, gtk_label_new("Clean Flash"));
    
    // run css-provider
    add_css_provider(button_gsi5, provider);
    add_css_provider(label_gsi3_1, provider);
    add_css_provider(button_gsi6, provider);
    
    // page 4
    page_gsi4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_gsi7 = gtk_button_new_with_label("Dirty Flash");
    label_gsi4_1 = gtk_label_new("Nach einem'dirty flash' bleiben die Nutzerdaten erhalten, \naber nicht jedes GSI startet danach. \n \n1. Flashen sie das System-Image. \n2. Starten sie ihr Gerät neu.");
    gtk_box_pack_start(GTK_BOX(page_gsi4), button_gsi7, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_gsi4), label_gsi4_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_gsi4), button_gsi2, FALSE, FALSE, 0);
    g_signal_connect(button_gsi7, "clicked", G_CALLBACK(gsi_text), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_gsi4, gtk_label_new("Dirty Flash"));
    
    // run css-provider
    add_css_provider(button_gsi7, provider);
    add_css_provider(label_gsi4_1, provider);
    
    // clean the storage
    g_object_unref(provider);
	
	// show all widgets
    gtk_widget_show_all(window);
	
	// run gtk mainloop
    gtk_main();
    g_print("Log: end instruction_gsi\n");
}
