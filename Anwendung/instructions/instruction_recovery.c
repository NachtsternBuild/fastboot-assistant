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

// main function
void instruction_recovery(int argc, char *argv[]) 
{
    LOG_INFO("instruction_recovery");
    
    // GTK init
    gtk_init();
	main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();

    GtkWidget *window, *notebook;
    GtkWidget *page1, *page2;
    GtkWidget *label_reco1_1, *label_reco1_2, *label_reco1_3, *label_reco2_1, *label_reco2_2, *label_reco2_3;
    GtkWidget *button_reco1, *button_reco2, *button_reco3;
    
    // create the main window
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Recovery");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
	g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);

    // create the notebook
    notebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // page 1
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    button_reco1 = gtk_button_new_with_label("Recovery");
    label_reco1_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Der Recovery-Modus ist ein spezielles Boot-Menü auf Android-Geräten, \ndas zur Wartung und Wiederherstellung des Systems dient." : "Recovery mode is a special boot menu on Android devices \nthat is used to maintain and restore the system.");
    label_reco1_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Dieser ermöglicht Funktionen wie das Zurücksetzen auf Werkseinstellungen, \ndas Installieren von Updates, und einige andere Grundfunktionen \num das System wiederherzustellen." : "This enables functions such as resetting to factory settings, installing updates \nand some other basic functions to restore the system.");
    label_reco1_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Custom-Recoverys bringen viel mehr Funktionen mit, als die Stock-Recoverys \ndes Herstellers. Diese haben meist nur Grundausstattung an Bord." : "Custom coverys have many more functions than the stock recoverys from \nthe same manufacturer. These usually only have basic features on board.");
    button_reco2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_reco1);
    gtk_box_append(GTK_BOX(page1), label_reco1_1);
    gtk_box_append(GTK_BOX(page1), label_reco1_2);
    gtk_box_append(GTK_BOX(page1), label_reco1_3);
    gtk_box_append(GTK_BOX(page1), button_reco2);

    // connect everything
    g_signal_connect(button_reco2, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, gtk_label_new("Recovery"));
    
    // page 2
    page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_reco3 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Flashen des Recoverys" :"Flashing the recovery");
    label_reco2_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Prüfen Sie, ob es für Ihr Gerät einen Custom-Recovery gibt. \n2. Laden Sie einen entsprechenden Recovery herunter. \n3. Bereiten Sie die Images für den Flash vor." : "1. Check whether there is a custom recovery for your device. \n2. Download a corresponding recovery. \n3. Prepare the images for the flash.");
    label_reco2_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "4. Booten Sie Ihr Gerät in den Fastboot-Modus. \n5. Öffnen Sie den Bootloader. \nManche Geräte unterstützen nicht die Methode über Fastboot." : "4. Boot your device into fastboot mode. \n5. Open the bootloader. \nSome devices do not support the fastboot method.");
    label_reco2_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Informieren Sie sich genauer über Ihren Chipsatz und das Gerät. \n6. Flashen Sie das Recovery-Image mit dieser Anwendung. \n7. Lassen Sie Ihr Gerät in den Recovery booten." : "Find out more about your chipset and the device. \n6. Flash the recovery image with this application. \n7. Boot your device into the recovery.");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_reco3);
    gtk_box_append(GTK_BOX(page2), label_reco2_1);
    gtk_box_append(GTK_BOX(page2), label_reco2_2);
    gtk_box_append(GTK_BOX(page2), label_reco2_3);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page2, gtk_label_new(g_strcmp0(language, "de") == 0 ? "Flashen" : "Flashing"));
    
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
    
    LOG_INFO("end instruction_recovery");
}
