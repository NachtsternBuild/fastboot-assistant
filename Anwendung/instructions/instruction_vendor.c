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
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

static void vndk_text()
{
	g_print("Die Lösung ist: 42–39+38+1");
}

void instruction_vendor(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *page_vndk1;
    GtkWidget *label_vndk1_1, *label_vndk1_2, *label_vndk1_3;
    GtkWidget *button_vndk1;

    gtk_init(&argc, &argv);
    css_provider(); // load css-provider
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Vendor Native Development Kit (VNDK)");
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
    page_vndk1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_vndk1 = gtk_button_new_with_label("VNDK");
    label_vndk1_1 = gtk_label_new("Alles was mit 'Vendor' bezeichnet wird, sind hersteller- oder \ngerätspezifische Komponenten des Betriebssystems. \nÄnderungen daran können zu Problemen führen.");
    label_vndk1_2 = gtk_label_new("Die VNDK-Version (Vendor Native Development Kit) ist eine Sammlung von \nBibliotheken und Richtlinien, durch die den hardwarespezifische Teil \nvon Rest des Androids trennt.");
    label_vndk1_3 = gtk_label_new("Dadurch lassen sich Updates und Wartung erleichtern, weil herstellerspezifische \nAnpassungen nicht die Kompatibilität und Stabilität \ndes Android-Systems beeinträchtigen.");
    gtk_box_pack_start(GTK_BOX(page_vndk1), button_vndk1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_vndk1), label_vndk1_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_vndk1), label_vndk1_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_vndk1), label_vndk1_3, TRUE, TRUE, 0);
    g_signal_connect(button_vndk1, "clicked", G_CALLBACK(vndk_text), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_vndk1, gtk_label_new("VNDK"));
    
    // run css-provider
    add_css_provider(button_vndk1, provider);
    add_css_provider(label_vndk1_1, provider);
    add_css_provider(label_vndk1_2, provider);
    add_css_provider(label_vndk1_3, provider);
    
    // clean the storage
    g_object_unref(provider);
	
	// show all widgets
    gtk_widget_show_all(window);
	
	// run gtk mainloop
    gtk_main();
}
