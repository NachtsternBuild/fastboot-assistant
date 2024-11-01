/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_others		 *
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

static void others_text()
{
	g_print("Log: Nix los!\n");
}

// the main function
void instruction_others(int argc, char *argv[])
{
	g_print("Log: instruction_others\n");
	GtkWidget *window;
    GtkWidget *page_others1, *page_others2, *page_others3;
    GtkWidget *label_others_1, *label_others_2, *label_others_3;
    GtkWidget *button_others_1, *button_others_2, *button_others_3, *button_others_4, *button_others_5;

    gtk_init(&argc, &argv);
    apply_theme();
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Anderes");
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
    page_others1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_others_1 = gtk_button_new_with_label("dtbo");
    label_others_1 = gtk_label_new("Dabei handelt es sich um eine Partition, \ndie den Gerätebaum des Gerätes gespeichert ist. \nDieser ist essentiell für die Kommunikation der Hardware \nmit dem Bootloader und dem Kernel.");
    button_others_2 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_others1), button_others_1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_others1), label_others_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_others1), button_others_2, FALSE, FALSE, 0);
    g_signal_connect(button_others_1, "clicked", G_CALLBACK(others_text), notebook);
    g_signal_connect(button_others_2, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_others1, gtk_label_new("dtbo"));

    // run css-provider
    add_css_provider(button_others_1, provider);
    add_css_provider(label_others_1, provider);
    add_css_provider(button_others_2, provider);
    

    // page 2
    page_others2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_others_3 = gtk_button_new_with_label("Super");
	label_others_2 = gtk_label_new("Dabei handelt es sich um eine Partition, die alle \nanderen Partitionen auf Geräten mit dynamischen Partitionen umfasst.");
    button_others_4 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_others2), button_others_3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_others2), label_others_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_others2), button_others_4, FALSE, FALSE, 0);
    g_signal_connect(button_others_3, "clicked", G_CALLBACK(others_text), notebook);
    g_signal_connect(button_others_4, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_others2, gtk_label_new("Super"));

    // run css-provider
    add_css_provider(button_others_3, provider);
    add_css_provider(label_others_2, provider);
    add_css_provider(button_others_4, provider);
    
    // page 2
    page_others3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_others_5 = gtk_button_new_with_label("vbmeta");
	label_others_3 = gtk_label_new("'vbmeta' stellt sicher, dass der Bootvorgang von \nStock-Android sicher abläuft. Manche Custom-ROMs lassen \nsich nur starten wenn ein neues vbmeta-Image geflasht wurde.");
    gtk_box_pack_start(GTK_BOX(page_others3), button_others_5, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_others3), label_others_3, TRUE, TRUE, 0);
    g_signal_connect(button_others_5, "clicked", G_CALLBACK(others_text), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_others3, gtk_label_new("vbmeta"));

    // run css-provider
    add_css_provider(button_others_5, provider);
    add_css_provider(label_others_3, provider);
    
    // clean the storage
    g_object_unref(provider);
	
	// show all widgets
    gtk_widget_show_all(window);
	
	// run gtk mainloop
    gtk_main();
    g_print("Log: end instruction_others\n");
}
