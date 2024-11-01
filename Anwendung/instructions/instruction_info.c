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
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

#define MAX_BUFFER_SIZE 256

static void info_text()
{
	g_print("Log: Nischt da!\n");
}

void instruction_info(int argc, char *argv[]) 
{
	g_print("Log: instruction_info\n");
	GtkWidget *window;
    GtkWidget *page_info1, *page_info2, *page_info3, *page_info4;
    GtkWidget *label_info1_1, *label_info1_2, *label_info2_1, *label_info2_2, *label_info3_1, *label_info3_2, *label_info4_1, *label_info4_2, *label_info4_3;
    GtkWidget *button_info1, *button_info2, *button_info3, *button_info4, *button_info5, *button_info6, *button_info7;

    gtk_init(&argc, &argv);
    apply_theme();
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Weitere Infos");
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
    page_info1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_info1 = gtk_button_new_with_label("Project Treble");
    label_info1_1 = gtk_label_new("Project Treble ist eine Android-Initiative von Google, \ndie Betriebssystem- und Hardwarekomponenten trennt.");
    label_info1_2 = gtk_label_new("Dadurch können Hersteller leichter Updates bereitstellen, \nda das OS unabhängig von chipsatzspezifischen Treibern ist.");
    button_info2 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_info1), button_info1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_info1), label_info1_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_info1), label_info1_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_info1), button_info2, FALSE, FALSE, 0);
    g_signal_connect(button_info1, "clicked", G_CALLBACK(info_text), notebook);
    g_signal_connect(button_info2, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_info1, gtk_label_new("Project Treble"));

    // run css-provider
    add_css_provider(button_info1, provider);
    add_css_provider(label_info1_1, provider);
    add_css_provider(label_info1_2, provider);
    add_css_provider(button_info2, provider);
    

    // page 2
    page_info2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_info3 = gtk_button_new_with_label("a/b Partitionierung");
    label_info2_1 = gtk_label_new("Das A/B-Partitionsschema nutzt zwei Systempartitionen \nfür nahtlose Updates durch Wechsel, \nbietet höhere Sicherheit und kontinuierlichen Betrieb.");
    label_info2_2 = gtk_label_new("Das Only-A-Schema hat nur eine Partition, \nermöglicht einfachere Verwaltung, \naber ist anfälliger für Fehler während des Updates.");
    button_info4 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_info2), button_info3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_info2), label_info2_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_info2), label_info2_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_info2), button_info4, FALSE, FALSE, 0);
    g_signal_connect(button_info3, "clicked", G_CALLBACK(info_text), notebook);
    g_signal_connect(button_info4, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_info2, gtk_label_new("a/b Partitionierung"));

    // run css-provider
    add_css_provider(button_info3, provider);
    add_css_provider(label_info2_1, provider);
    add_css_provider(label_info2_2, provider);
    add_css_provider(button_info4, provider);
    
    // page 3
    page_info3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_info5 = gtk_button_new_with_label("System-as-root");
	label_info3_1 = gtk_label_new("System-as-root ist ein Android-Mechanismus, \nbei dem das System-Image als Root-Dateisystem gemountet wird.");
	label_info3_2 = gtk_label_new("Dies verbessert die Trennung von System- und Vendor-Partitionen, \nerhöht die Sicherheit und erleichtert System-Updates \nsowie die Verwaltung von Berechtigungen.");
	button_info6 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_info3), button_info5, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_info3), label_info3_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_info3), label_info3_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_info3), button_info6, FALSE, FALSE, 0);
    g_signal_connect(button_info5, "clicked", G_CALLBACK(info_text), notebook);
    g_signal_connect(button_info6, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_info3, gtk_label_new("System-as-root"));
    
    // run css-provider
    add_css_provider(button_info5, provider);
    add_css_provider(label_info3_1, provider);
    add_css_provider(label_info3_2, provider);
    add_css_provider(button_info6, provider);

    // page 4
    page_info4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_info7 = gtk_button_new_with_label("Kernel");
	label_info4_1 = gtk_label_new("Der Kernel ist der Kern eines Betriebssystems, \nder direkt mit der Hardware kommuniziert und Ressourcen wie CPU, \nSpeicher und Geräte verwaltet.");
	label_info4_2 = gtk_label_new("Der Kernel bildet die Schnittstelle zwischen Hardware, \nAnwendungen und dem Rest des Systems und sorgt für eine \nsichere und effiziente Ausführung.");
	label_info4_3 = gtk_label_new("Android-Versionen sind nur mit bestimmten \nKernel-Versionen kompatibel; bei Inkompatibilität startet Android nicht.");
    gtk_box_pack_start(GTK_BOX(page_info4), button_info7, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_info4), label_info4_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_info4), label_info4_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_info4), label_info4_3, TRUE, TRUE, 0);
    g_signal_connect(button_info7, "clicked", G_CALLBACK(info_text), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_info4, gtk_label_new("Kernel"));
    

    // run css-provider
    add_css_provider(button_info7, provider);
    add_css_provider(label_info4_1, provider);
    add_css_provider(label_info4_2, provider);
    add_css_provider(label_info4_3, provider);
    
    // clean the storage
    g_object_unref(provider);
	
	// show all widgets
    gtk_widget_show_all(window);
	
	// run gtk mainloop
    gtk_main();
    g_print("Log: end instruction_info\n");
}
