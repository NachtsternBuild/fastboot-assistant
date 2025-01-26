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

void instruction_vendor(int argc, char *argv[]) 
{
    LOG_INFO("instruction_vendor");
    
    // GTK init
    gtk_init();
	main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    
    GtkWidget *window, *notebook;
    GtkWidget *page1;
    GtkWidget *label_vndk1_1, *label_vndk1_2, *label_vndk1_3;
    GtkWidget *button_vndk1;
	
	// create the main window
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Vendor Native Development Kit (VNDK)");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
	g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);

    // create the notebook
    notebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // page 1
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    button_vndk1 = gtk_button_new_with_label("VNDK");
    label_vndk1_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Alles was mit 'Vendor' bezeichnet wird, sind hersteller- oder \ngerätspezifische Komponenten des Betriebssystems. \nÄnderungen daran können zu Problemen führen." : "Everything labeled 'Vendor' are manufacturer- or device-specific \ncomponents of the operating system. Changes to these can \nlead to problems.");
    label_vndk1_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Die VNDK-Version (Vendor Native Development Kit) ist eine Sammlung von \nBibliotheken und Richtlinien, durch die den hardwarespezifische Teil \nvon Rest des Androids trennt." : "The VNDK version (Vendor Native Development Kit) is a collection of \nlibraries and guidelines that separates the hardware-specific part \nfrom the rest of Android.");
    label_vndk1_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Dadurch lassen sich Updates und Wartung erleichtern, weil herstellerspezifische \nAnpassungen nicht die Kompatibilität und Stabilität \ndes Android-Systems beeinträchtigen." : "This makes updates and maintenance easier because manufacturer-specific \nadjustments do not affect the compatibility and stability \nof the Android system.");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_vndk1);
    gtk_box_append(GTK_BOX(page1), label_vndk1_1);
    gtk_box_append(GTK_BOX(page1), label_vndk1_2);
    gtk_box_append(GTK_BOX(page1), label_vndk1_3);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, gtk_label_new("VNDK"));
    
    // show all widgets
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop); 
    
    // free the provider
    if (provider != NULL) 
    {
    	g_object_unref(provider);
    	provider = NULL;
	}
    
    if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
	
    LOG_INFO("end instruction_vendor");
}
