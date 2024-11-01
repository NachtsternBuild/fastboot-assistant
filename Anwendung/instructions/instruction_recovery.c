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
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

static void recovery_text()
{
	g_print("Log: Die Lösung ist: \n");
}

void instruction_recovery(int argc, char *argv[]) 
{
    g_print("Log: instruction_recovery\n");
    GtkWidget *window;
    GtkWidget *page_reco1, *page_reco2;
    GtkWidget *label_reco1_1, *label_reco1_2, *label_reco1_3, *label_reco2_1, *label_reco2_2, *label_reco2_3;
    GtkWidget *button_reco1, *button_reco2, *button_reco3;

    gtk_init(&argc, &argv);
    apply_theme();
    //css_provider(); // load css-provider
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Recovery");
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
    page_reco1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_reco1 = gtk_button_new_with_label("Recovery");
    label_reco1_1 = gtk_label_new("Der Recovery-Modus ist ein spezielles Boot-Menü auf Android-Geräten, \ndas zur Wartung und Wiederherstellung des Systems dient.");
    label_reco1_2 = gtk_label_new("Dieser ermöglicht Funktionen wie das Zurücksetzen auf Werkseinstellungen, \ndas Installieren von Updates, und einige andere Grundfunktionen \num das System wiederherzustellen.");
    label_reco1_3 = gtk_label_new("Custom-Recoverys bringen viel mehr Funktionen mit, als die Stock-Recoverys \ndes Herstellers. Diese haben meist nur Grundausstattung an Bord.");
    button_reco2 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_reco1), button_reco1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_reco1), label_reco1_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_reco1), label_reco1_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_reco1), label_reco1_3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_reco1), button_reco2, FALSE, FALSE, 0);
    g_signal_connect(button_reco1, "clicked", G_CALLBACK(recovery_text), notebook);
    g_signal_connect(button_reco2, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_reco1, gtk_label_new("Recovery"));
    
    // run css-provider
    add_css_provider(button_reco1, provider);
    add_css_provider(label_reco1_1, provider);
    add_css_provider(label_reco1_2, provider);
    add_css_provider(label_reco1_3, provider);
    add_css_provider(button_reco2, provider);
    
    // page 2
    page_reco2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_reco3 = gtk_button_new_with_label("Flashen des Recoverys");
    label_reco2_1 = gtk_label_new("1. Prüfen Sie, ob es für Ihr Gerät einen Custom-Recovery gibt. \n2. Laden Sie einen entsprechenden Recovery herunter. \n3. Bereiten Sie die Images für den Flash vor.");
    label_reco2_2 = gtk_label_new("4. Booten Sie Ihr Gerät in den Fastboot-Modus. \n5. Öffnen Sie den Bootloader. \nManche Geräte unterstützen nicht die Methode über Fastboot.");
    label_reco2_3 = gtk_label_new("Informieren Sie sich genauer über Ihren Chipsatz und das Gerät. \n6. Flashen Sie das Recovery-Image mit dieser Anwendung. \n7. Lassen Sie Ihr Gerät in den Recovery booten.");
    gtk_box_pack_start(GTK_BOX(page_reco2), button_reco3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_reco2), label_reco2_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_reco2), label_reco2_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_reco2), label_reco2_3, TRUE, TRUE, 0);
    g_signal_connect(button_reco3, "clicked", G_CALLBACK(recovery_text), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_reco2, gtk_label_new("Flashen"));
    
    // run css-provider
    add_css_provider(button_reco3, provider);
    add_css_provider(label_reco2_1, provider);
    add_css_provider(label_reco2_2, provider);
    add_css_provider(label_reco2_3, provider);
    
    // clean the storage
    g_object_unref(provider);
	
	// show all widgets
    gtk_widget_show_all(window);
	
	// run gtk mainloop
    gtk_main();
    g_print("Log: end instruction_recovery\n");
}
