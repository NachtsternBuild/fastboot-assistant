/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_preflash	 *
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

// function to open the GitHub website from the fastboot-assistant
void twrp(GtkWidget *widget, gpointer data)
{
    g_print("Log: twrp\n");
    const char *twrp_url = "https://www.twrp.me/";    
	open_url(twrp_url);
	g_print("Log: end twrp\n");
}

// function that open the GitHub Releases page
void e_OS(GtkWidget *widget, gpointer data)
{
    g_print("Log: e_OS\n");
    const char *e_OS_url = "https://e.foundation/e-os/";
	open_url(e_OS_url);
	g_print("Log: end e_OS\n");
}

// function to open the website that used for the feedback for the fastboot-assistant
void lineage_os(GtkWidget *widget, gpointer data)
{
    g_print("Log: lineage_os\n");
    const char *lineage_os_url = "https://lineageos.org/";
	open_url(lineage_os_url);
	g_print("Log: end lineage_os\n");
}

// function to open the website from 'Open Android Backup'
void project_elixir(GtkWidget *widget, gpointer data)
{
    g_print("Log: project_elixir\n");
    const char *project_elixir_url = "https://projectelixiros.com/home";
	open_url(project_elixir_url);
	g_print("Log: end project_elixir\n");
}

// function to open the website from 'Open Android Backup'
void crdroid(GtkWidget *widget, gpointer data)
{
    g_print("Log: crdroid\n");
    const char *crdroid_url = "https://crdroid.net/";
	open_url(crdroid_url);
	g_print("Log: end crdroid\n");
}

// function to open the website from 'Open Android Backup'
void evolution_x(GtkWidget *widget, gpointer data)
{
    g_print("Log: evolution_x\n");
    const char *evolution_x_url = "https://sourceforge.net/projects/evolution-x/";
	open_url(evolution_x_url);
	g_print("Log: end evolution_x\n");
}

/* main function */
void instruction_preflash(int argc, char *argv[]) 
{
    g_print("Log: instruction_preflash\n");
    
    // GTK init
    gtk_init();

    apply_theme();
    apply_language();
    
    GtkWidget *window, *notebook;
    GtkWidget *page_preflash1, *page_preflash2;
    GtkWidget *label_preflash1_1, *label_preflash1_2, *label_preflash1_3, *label_preflash1_4;
    GtkWidget *button_preflash1, *button_preflash2, *button_preflash3, *button_preflash2_1, *button_preflash2_2, *button_preflash2_3, *button_preflash2_4, *button_preflash2_5, *button_preflash2_6;
    
    // create the main window
    window = gtk_window_new();
    const char *instruction_preflash_window = strcmp(language, "de") == 0 ? "Vorbereitung" : "Preparation";
    gtk_window_set_title(GTK_WINDOW(window), instruction_preflash_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);

    // create the notebook
    notebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // page 1
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    button_preflash1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Vorbereitung Flash" : "Preparation Flash");
    label_preflash1_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Informieren sie genauer über ihr Gerät und den Chipsatz des Gerätes. \n2. Suchen sie nach entsprechenden Custom-ROMs, Custom-Recoverys \noder GSIs." : "1. Provide more detailed information about your device and the chipset of the device. \n2. Search for corresponding custom ROMs, custom recoverys \nor GSIs.");
    label_preflash1_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "3. Prüfen sie die Verfügbarkeit von Project Treble für ihr Gerät. \n4. Prüfen sie welches Partitionierungsschema auf ihrem Gerät vorliegt \n(a/b-devices oder only-a-devices)." : "3. Check the availability of Project Treble for your device. \n4. Check which partitioning scheme is available on your device \n(a/b-devices or only-a-devices).");
    label_preflash1_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "5. Sichern sie ihre Daten lokal und wenn sie wollen in einer Cloud. \n6. Laden sie alle Dateien herunter die sie für den flash brauchen." : "5. Back up your data locally and, if you wish, in a cloud. \n6. Download all the files you need for the flash.);
    label_preflash1_4 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "7. Lesen sie die Anleitungen der Entwickler vor dem Flash. \n8. Kopieren sie alle Dateien die geflasht werden, nach: '~/Downloads/ROM-Install/'" : "7. Read the developer's instructions before using Flash. \n8. Copy all files that are flashed to: '~/Downloads/ROM-Install/'");
    button_preflash2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_preflash1);
    gtk_box_append(GTK_BOX(page1), label_preflash1_1);
    gtk_box_append(GTK_BOX(page1), label_preflash1_2);
    gtk_box_append(GTK_BOX(page1), label_preflash1_3);
    gtk_box_append(GTK_BOX(page1), label_preflash1_4);
    gtk_box_append(GTK_BOX(page1), button_preflash2);

    // connect everything
    g_signal_connect(button_preflash2, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, gtk_label_new(g_strcmp0(language, "de") == 0 ? "Vorbereitung" : "Preparation"));
    
    // page 2
    page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_preflash3 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Einige Custom ROMs" : "Some custom ROMs");
    button_preflash2_1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "TWRP (ein Recovery)" : "TWRP (a recovery)");
    button_preflash2_2 = gtk_button_new_with_label("/e/ OS");
    button_preflash2_3 = gtk_button_new_with_label("LineageOS");
    button_preflash2_4 = gtk_button_new_with_label("Project Elixir");
    button_preflash2_5 = gtk_button_new_with_label("CrDroid");
    button_preflash2_6 = gtk_button_new_with_label("Evolution X");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_preflash3);
    gtk_box_append(GTK_BOX(page2), button_preflash2_1);
    gtk_box_append(GTK_BOX(page2), button_preflash2_2);
    gtk_box_append(GTK_BOX(page2), button_preflash2_3);
    gtk_box_append(GTK_BOX(page2), button_preflash2_4);
    gtk_box_append(GTK_BOX(page2), button_preflash2_5);
    gtk_box_append(GTK_BOX(page2), button_preflash2_6);

    // connect everything
    g_signal_connect(button_preflash2_1, "clicked", G_CALLBACK(twrp), notebook);
    g_signal_connect(button_preflash2_2, "clicked", G_CALLBACK(e_OS), notebook);
    g_signal_connect(button_preflash2_3, "clicked", G_CALLBACK(lineage_os), notebook);
    g_signal_connect(button_preflash2_4, "clicked", G_CALLBACK(project_elixir), notebook);
    g_signal_connect(button_preflash2_5, "clicked", G_CALLBACK(crdroid), notebook);
    g_signal_connect(button_preflash2_6, "clicked", G_CALLBACK(evolution_x), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page2, gtk_label_new("Custom ROMs");
    
    // show all widgets
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop); 
    g_print("Log: end instruction_preflash\n");
}
