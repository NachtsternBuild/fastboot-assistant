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

static void preflash_text()
{
	g_print("Log: Die Lösung ist: \n");
}

void instruction_preflash(int argc, char *argv[]) 
{
    g_print("Log: instruction_preflash\n");
    GtkWidget *window;
    GtkWidget *page_preflash1, *page_preflash2;
    GtkWidget *label_preflash1_1, *label_preflash1_2, *label_preflash1_3, *label_preflash1_4;
    GtkWidget *button_preflash1, *button_preflash2, *button_preflash3, *button_preflash2_1, *button_preflash2_2, *button_preflash2_3, *button_preflash2_4, *button_preflash2_5, *button_preflash2_6;

    gtk_init(&argc, &argv);
    apply_theme();
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Vorbereitung");
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
    page_preflash1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_preflash1 = gtk_button_new_with_label("Vorbereitung Flash");
    label_preflash1_1 = gtk_label_new("1. Informieren sie genauer über ihr Gerät und den Chipsatz des Gerätes. \n2. Suchen sie nach entsprechenden Custom-ROMs, Custom-Recoverys \noder GSIs.");
    label_preflash1_2 = gtk_label_new("3. Prüfen sie die Verfügbarkeit von Project Treble für ihr Gerät. \n4. Prüfen sie welches Partitionierungsschema auf ihrem Gerät vorliegt \n(a/b-devices oder only-a-devices).");
    label_preflash1_3 = gtk_label_new("5. Sichern sie ihre Daten lokal und wenn sie wollen in einer Cloud. \n6. Laden sie alle Dateien herunter die sie für den flash brauchen.");
    label_preflash1_4 = gtk_label_new("7. Lesen sie die Anleitungen der Entwickler vor dem Flash. \n8. Kopieren sie alle Dateien die geflasht werden, nach: '~/Downloads/ROM-Install/'");
    button_preflash2 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_preflash1), button_preflash1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_preflash1), label_preflash1_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_preflash1), label_preflash1_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_preflash1), label_preflash1_3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_preflash1), label_preflash1_4, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_preflash1), button_preflash2, FALSE, FALSE, 0);
    g_signal_connect(button_preflash1, "clicked", G_CALLBACK(preflash_text), notebook);
    g_signal_connect(button_preflash2, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_preflash1, gtk_label_new("Vorbereitung"));
    
    // run css-provider
    add_css_provider(button_preflash1, provider);
    add_css_provider(label_preflash1_1, provider);
    add_css_provider(label_preflash1_2, provider);
    add_css_provider(label_preflash1_3, provider);
    add_css_provider(label_preflash1_4, provider);
    add_css_provider(button_preflash2, provider);
    
    // page 2
    page_preflash2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_preflash3 = gtk_button_new_with_label("Einige Custom ROMs");
    button_preflash2_1 = gtk_button_new_with_label("TWRP (ein Recovery)");
    button_preflash2_2 = gtk_button_new_with_label("/e/ OS");
    button_preflash2_3 = gtk_button_new_with_label("LineageOS");
    button_preflash2_4 = gtk_button_new_with_label("Project Elixir");
    button_preflash2_5 = gtk_button_new_with_label("CrDroid");
    button_preflash2_6 = gtk_button_new_with_label("Evolution X");
    gtk_box_pack_start(GTK_BOX(page_preflash2), button_preflash3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_preflash2), button_preflash2_1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_preflash2), button_preflash2_2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_preflash2), button_preflash2_3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_preflash2), button_preflash2_4, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_preflash2), button_preflash2_5, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_preflash2), button_preflash2_6, FALSE, FALSE, 0);
    g_signal_connect(button_preflash3, "clicked", G_CALLBACK(preflash_text), notebook);
    g_signal_connect(button_preflash2_1, "clicked", G_CALLBACK(twrp), notebook);
    g_signal_connect(button_preflash2_2, "clicked", G_CALLBACK(e_OS), notebook);
    g_signal_connect(button_preflash2_3, "clicked", G_CALLBACK(lineage_os), notebook);
    g_signal_connect(button_preflash2_4, "clicked", G_CALLBACK(project_elixir), notebook);
    g_signal_connect(button_preflash2_5, "clicked", G_CALLBACK(crdroid), notebook);
    g_signal_connect(button_preflash2_6, "clicked", G_CALLBACK(evolution_x), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_preflash2, gtk_label_new("Custom ROMs"));
    
    // run css-provider
    add_css_provider(button_preflash3, provider);
    add_css_provider(button_preflash2_1, provider);
    add_css_provider(button_preflash2_2, provider);
    add_css_provider(button_preflash2_3, provider);
    add_css_provider(button_preflash2_4, provider);
    add_css_provider(button_preflash2_5, provider);
    add_css_provider(button_preflash2_6, provider);
    
    // clean the storage
    g_object_unref(provider);
	
	// show all widgets
    gtk_widget_show_all(window);
	
	// run gtk mainloop
    gtk_main();
    g_print("Log: end instruction_preflash\n");
}
