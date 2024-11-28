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
#include "language_check.h"
#include "program_functions.h"

#define MAX_BUFFER_SIZE 256

void instruction_info(int argc, char *argv[]) 
{
	g_print("Log: instruction_info\n");
	
	// GTK init
    gtk_init();

    apply_theme();
    apply_language();
    
	GtkWidget *window, *notebook;
    GtkWidget *page1, *page2, *page3, *page4;
    GtkWidget *label_info1_1, *label_info1_2, *label_info2_1, *label_info2_2, *label_info3_1, *label_info3_2, *label_info4_1, *label_info4_2, *label_info4_3;
    GtkWidget *button_info1, *button_info2, *button_info3, *button_info4, *button_info5, *button_info6, *button_info7;
    
    // create the main window
    window = gtk_window_new();
    const char *instruction_info_window = strcmp(language, "de") == 0 ? "Weitere Infos" : "More info";
    gtk_window_set_title(GTK_WINDOW(window), instruction_info_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);

    // create the notebook
    notebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // page 1
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    button_info1 = gtk_button_new_with_label("Project Treble");
    label_info1_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Project Treble ist eine Android-Initiative von Google, \ndie Betriebssystem- und Hardwarekomponenten trennt." : "Project Treble is an Android initiative from \nGoogle that separates the operating system and hardware components.");
    label_info1_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Dadurch können Hersteller leichter Updates bereitstellen, \nda das OS unabhängig von chipsatzspezifischen Treibern ist." : "This makes it easier for manufacturers to provide updates \nwhile the OS is independent of chipset-specific drivers.");
    button_info2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_info1);
    gtk_box_append(GTK_BOX(page1), label_info1_1);
    gtk_box_append(GTK_BOX(page1), label_info1_2);
    gtk_box_append(GTK_BOX(page1), button_info2);

    // connect everything
    g_signal_connect(button_info2, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, gtk_label_new("Project Treble"));
    
    // page 2
    page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_info3 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "a/b Partitionierung" : "a/b Partitioning");
    label_info2_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Das A/B-Partitionsschema nutzt zwei Systempartitionen \nfür nahtlose Updates durch Wechsel, \nbietet höhere Sicherheit und kontinuierlichen Betrieb." : "The A/B partitioning scheme uses two system partitions \nfor seamless updates by switching, \nprovides higher security and continuous operation.");
    label_info2_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Das Only-A-Schema hat nur eine Partition, \nermöglicht einfachere Verwaltung, \naber ist anfälliger für Fehler während des Updates." : "The Only-A scheme has only one partition, \nallows easier management, \nbut is more prone to errors during the update.");
    button_info4 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_info3);
    gtk_box_append(GTK_BOX(page2), label_info2_1);
    gtk_box_append(GTK_BOX(page2), label_info2_2);
    gtk_box_append(GTK_BOX(page2), button_info4);

    // connect everything
    g_signal_connect(button_info4, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page2, gtk_label_new(g_strcmp0(language, "de") == 0 ? "a/b Partitionierung" : "a/b Partitioning"));
    
    // page 3
    page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_info5 = gtk_button_new_with_label("System-as-root");
	label_info3_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "System-as-root ist ein Android-Mechanismus, \nbei dem das System-Image als Root-Dateisystem gemountet wird." : "System-as-root is an Android mechanism in which the \nsystem image is mounted as the root file system.");
	label_info3_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Dies verbessert die Trennung von System- und Vendor-Partitionen, \nerhöht die Sicherheit und erleichtert System-Updates \nsowie die Verwaltung von Berechtigungen." : "This improves the separation of system and vendor partitions, \nincreases security and facilitates system updates and \nthe management of authorizations.");
	button_info6 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page3), button_info5);
    gtk_box_append(GTK_BOX(page3), label_info3_1);
    gtk_box_append(GTK_BOX(page3), label_info3_2);
    gtk_box_append(GTK_BOX(page3), button_info6);

    // connect everything
    g_signal_connect(button_info6, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page3, gtk_label_new("System-as-root"));
    
    // page 4
    page4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_info7 = gtk_button_new_with_label("Kernel");
	label_info4_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Der Kernel ist der Kern eines Betriebssystems, \nder direkt mit der Hardware kommuniziert und Ressourcen wie CPU, \nSpeicher und Geräte verwaltet." : "The kernel is the core of an operating system, \nwhich communicates directly with the hardware and manages resources such as CPU, \nmemory and devices.");
	label_info4_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Der Kernel bildet die Schnittstelle zwischen Hardware, \nAnwendungen und dem Rest des Systems und sorgt für eine \nsichere und effiziente Ausführung." : "The kernel forms the interface between hardware, \napplications and the rest of the system and ensures \nsecure and efficient execution.");
	label_info4_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Android-Versionen sind nur mit bestimmten \nKernel-Versionen kompatibel; bei Inkompatibilität startet Android nicht." : "Android versions are only compatible with certain \nKernel versions; if incompatible, Android will not start.");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page4), button_info7);
    gtk_box_append(GTK_BOX(page4), label_info4_1);
    gtk_box_append(GTK_BOX(page4), label_info4_2);
    gtk_box_append(GTK_BOX(page4), label_info4_3);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page4, gtk_label_new("Kernel"));
    
    // show all widgets
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop); 
    g_print("Log: end instruction_info\n");
}
