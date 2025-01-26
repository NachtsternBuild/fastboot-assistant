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
#include "language_check.h"
#include "program_functions.h"

void instruction_gsi(int argc, char *argv[]) 
{	
	LOG_INFO("instruction_gsi");
	
	// GTK init
    gtk_init();
	main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    
	GtkWidget *window, *notebook;
    GtkWidget *page1, *page2, *page3, *page4;
    GtkWidget *label_gsi1_1, *label_gsi1_2, *label_gsi2_1, *label_gsi2_2, *label_gsi2_3, *label_gsi3_1, *label_gsi4_1;
    GtkWidget *button_gsi1, *button_gsi2, *button_gsi3, *button_gsi4, *button_gsi5, *button_gsi6, *button_gsi7;
    
    // create the main window
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Generic System Image");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
	g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);

    // create the notebook
    notebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // page 1
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    button_gsi1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Hinweise" : "Notes");
    label_gsi1_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "GSI (Generic System Image) ist ein Android-System-Image, dass \neine Unterstützung von Project Treble (siehe weitere Infos) \nvoraussetzt." : "GSI (Generic System Image) is an Android system image that \nrequires support for Project Treble (see further information).");
    label_gsi1_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "GSIs ermöglichen Android-Geräten ohne Custom-ROMs für manuelles \naufspielen von neueren Android-Versionen." : "GSI enable Android devices without custom ROMs for manual flashing of newer Android versions.");
    button_gsi2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_gsi1);
    gtk_box_append(GTK_BOX(page1), label_gsi1_1);
    gtk_box_append(GTK_BOX(page1), label_gsi1_2);
    gtk_box_append(GTK_BOX(page1), button_gsi2);

    // connect everything
    g_signal_connect(button_gsi1, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, gtk_label_new(g_strcmp0(language, "de") == 0 ? "Hinweise" : "Notes"));
    
    // page 2
    page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_gsi3 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "GSI Flashen" : "GSI Flashing");
    label_gsi2_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Prüfen sie ob ihr Gerät mit Project Treble kompatibel ist. \n2. Laden sie ein entsprechendes GSI herunter. \n3. Vorbereiten sie die Images für den Flash.\n" : "1. Check if your device is compatible with Project Treble. \n2. Download a corresponding GSI. \n3. Prepare the images for the Flash.\n");
    label_gsi2_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "4. Booten sie ihr Gerät in Fastboot. \n5. Öffnen sie den Bootloader.\nManche Geräte unterstützen nicht die Methode über Fastboot." : "4. Boot your device in Fastboot. \n5. Open the bootloader.\nSome devices do not support the Fastboot method.");
    label_gsi2_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Als Methoden des Flashs gibt es die \nAlternativen 'dirty flash'(1) und 'clean flash'(2)." : "The alternatives 'dirty flash'(1) and \n'clean flash'(2) are available as flash methods.");
    button_gsi4 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");  
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_gsi3);
    gtk_box_append(GTK_BOX(page2), label_gsi2_1);
    gtk_box_append(GTK_BOX(page2), label_gsi2_2);
    gtk_box_append(GTK_BOX(page2), label_gsi2_3);
    gtk_box_append(GTK_BOX(page2), button_gsi4);

    // connect everything
    g_signal_connect(button_gsi3, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page2, gtk_label_new(g_strcmp0(language, "de") == 0 ? "Vorbereitung" : "Preparation"));
    
    // page 3
    page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_gsi5 = gtk_button_new_with_label("Clean Flash");
    label_gsi3_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Löschen sie alle Nutzerdaten. \n2. Flashen sie das System-Image \n3. Flashen sie im Bedarfsfall ein vbmeta.img. \n4. Starten sie ihr Gerät neu." : "1. Delete all user data. \n2. Flash the system image \n3. If necessary, flash a vbmeta.img. \n4. Restart your device.");
    button_gsi6 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");    
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page3), button_gsi5);
    gtk_box_append(GTK_BOX(page3), label_gsi3_1);
    gtk_box_append(GTK_BOX(page3), button_gsi6);

    // connect everything
    g_signal_connect(button_gsi6, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page3, gtk_label_new("Clean Flash"));
    
    // page 4
    page4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_gsi7 = gtk_button_new_with_label("Dirty Flash");
    label_gsi4_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Nach einem'dirty flash' bleiben die Nutzerdaten erhalten, \naber nicht jedes GSI startet danach. \n \n1. Flashen sie das System-Image. \n2. Starten sie ihr Gerät neu." : "After a 'dirty flash', the user data is retained, \nbut not every GSI starts afterwards. \n \n1. Flash the system image. \n2. Restart your device.");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page4), button_gsi7);
    gtk_box_append(GTK_BOX(page4), label_gsi4_1);  
    
    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page4, gtk_label_new("Dirty Flash"));
    
    // show all widgets
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop); 
    
    if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
	
    LOG_INFO("end instruction_gsi");
}
