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
void instruction_others(GtkWidget *widget, gpointer stack)
{
	LOG_INFO("instruction_others");
	
	// GTK init
    gtk_init();
	main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    
	GtkWidget *window, *notebook;
    GtkWidget *page1, *page2, *page3;
    GtkWidget *label_others_1, *label_others_2, *label_others_3;
    GtkWidget *button_others_1, *button_others_2, *button_others_3, *button_others_4, *button_others_5;
    
    // create the main window
    window = gtk_window_new();
    const char *instruction_others_window = strcmp(language, "de") == 0 ? "Anderes" : "Others";
    gtk_window_set_title(GTK_WINDOW(window), instruction_others_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
	g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);

    // create the notebook
    notebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // page 1
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); 
    
    // button and label
    button_others_1 = gtk_button_new_with_label("dtbo");
    label_others_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Dabei handelt es sich um eine Partition, \ndie den Gerätebaum des Gerätes gespeichert ist. \nDieser ist essentiell für die Kommunikation der Hardware \nmit dem Bootloader und dem Kernel." : "This is a partition \nwhich is stored in the device tree of the device. \nThis is essential for the communication of the hardware \nwith the boot loader and the kernel.");
    button_others_2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_others_1);
    gtk_box_append(GTK_BOX(page1), label_others_1);
    gtk_box_append(GTK_BOX(page1), button_others_2);

    // connect everything
    g_signal_connect(button_others_2, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, gtk_label_new("dtbo"));
    
    // page 2
    page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_others_3 = gtk_button_new_with_label("Super");
	label_others_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Dabei handelt es sich um eine Partition, die alle \nanderen Partitionen auf Geräten mit dynamischen Partitionen umfasst." : "This is a partition that includes all \nother partitions on devices with dynamic partitions.");
    button_others_4 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_others_3);
    gtk_box_append(GTK_BOX(page2), label_others_2);
    gtk_box_append(GTK_BOX(page2), button_others_4);

    // connect everything
    g_signal_connect(button_others_4, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page2, gtk_label_new("super"));
    
    // page 3
    page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_others_5 = gtk_button_new_with_label("vbmeta");
	label_others_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "'vbmeta' stellt sicher, dass der Bootvorgang von \nStock-Android sicher abläuft. Manche Custom-ROMs lassen \nsich nur starten wenn ein neues vbmeta-Image geflasht wurde." : "'vbmeta' ensures that the boot process of \nStock-Android runs safely. Some custom ROMs can only be started if a new vbmeta image has been flashed.");
	
	// add everything to the page
    gtk_box_append(GTK_BOX(page3), button_others_5);
    gtk_box_append(GTK_BOX(page3), label_others_3);
	
	// add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page3, gtk_label_new("vbmeta"));
    
    // show all widgets
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop);
    
    if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
    
    LOG_INFO("end instruction_others");
}
	
