/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *          Apache License, Version 2.0      *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von         *
 *  Custom-ROM und GSIs auf Android-Geräte   *
 *  zu erleichtern - run_first_run_setup     *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz        *
 *-------------------------------------------*
 *
 */
 
#include <glib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include "function_header.h"
#include "program_functions.h"

#define MAX_BUFFER_SIZE 256

static void setup_text(GtkButton *button, gpointer data) 
{
	g_print("Log: Hier gibt's nichts!\n");
}

// function that run the setup
void run_first_run_setup(GtkCssProvider *provider) 
{
    g_print("Log: run_first_run_setup\n");
    int argc = 0;
    char **argv = NULL;
    
    gtk_init(&argc, &argv);
    apply_theme();
    
    GtkWidget *window;
    GtkWidget *page1, *page2, *page3, *page4, *page5;
    GtkWidget *label_welcome_1, *label_welcome_2, *label_page2_1, *label_page2_2, *label_page3_1, *label_page3_2, *label_page3_3, *label_page3_4, *label_page4_1, *label_page4_2, *label_page4_3, *label_page4_4, *label_end_1, *label_end_2;
    GtkWidget *button_welcome_1, *button_toggle_theme, *button_welcome_2, *button_page2_1, *button_dir, *button_page2_2, *button_page3_1, *button_page3_2, *button_page4_1, *button_page4_2, *button_end_1, *button_end_2;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Fastboot Assistant Setup");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	// create notebook
	GtkWidget *notebook = gtk_notebook_new();
	if (!notebook) 
	{
    	g_print("Fehler: Konnte Notebook nicht erstellen.\n");
    	exit(1);
	}
    gtk_container_add(GTK_CONTAINER(window), notebook);
    
    // for debugging
    if (!GTK_IS_NOTEBOOK(notebook)) 
    {
    	g_warning("Notebook is not initialized properly.");
    	return;
	}

    // page 1
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    label_welcome_1 = gtk_label_new(" ");
    button_welcome_1 = gtk_button_new_with_label("Willkommen zum Fastboot Assistant!");
    button_toggle_theme = gtk_button_new_with_label("Thema wechseln (hell/dunkel)");
    label_welcome_2 = gtk_label_new(" ");
    button_welcome_2 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page1), label_welcome_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page1), button_welcome_1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page1), button_toggle_theme, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page1), label_welcome_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page1), button_welcome_2, FALSE, FALSE, 0);
    g_signal_connect(button_welcome_1, "clicked", G_CALLBACK(setup_text), notebook);
    g_signal_connect(button_toggle_theme, "clicked", G_CALLBACK(toggle_theme), notebook);
    g_signal_connect(button_welcome_2, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, gtk_label_new("Begrüßung"));

    // page 2
    page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_page2_1 = gtk_button_new_with_label("Zum korrekten Ausführen muss der \nFastboot-Assistant einige Konfigurationen vornehmen.");
    label_page2_1 = gtk_label_new("1. Es werden alle benötigten Ordner erstellt.");
    label_page2_2 = gtk_label_new("2. Anpassungen an das Betriebssystem werden durchgeführt.");
    button_dir = gtk_button_new_with_label("Konfigurieren");
    button_page2_2 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page2), button_page2_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page2), label_page2_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page2), label_page2_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page2), button_dir, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page2), button_page2_2, FALSE, FALSE, 0);
    g_signal_connect(button_page2_1, "clicked", G_CALLBACK(setup_text), notebook);
    g_signal_connect(button_dir, "clicked", G_CALLBACK(config_start), NULL);
    g_signal_connect(button_page2_2, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page2, gtk_label_new("Konfiguration"));

    // page 3
    page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_page3_1 = gtk_button_new_with_label("Hinweise:");
	label_page3_1 = gtk_label_new("1. Die Verwendung erfolgt auf eigene Gefahr.");
	label_page3_2 = gtk_label_new("2. Das Gerät kann beschädigt werden.");
	label_page3_3 = gtk_label_new("3. Nicht jedes Gerät unterstützt alle Funktionen");
	label_page3_4 = gtk_label_new("4. Nicht alle Betriebssystemvarianten haben den gleichen Funktionsumfang.");
    button_page3_2 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page3), button_page3_1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page3), label_page3_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page3), label_page3_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page3), label_page3_3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page3), label_page3_4, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page3), button_page3_2, FALSE, FALSE, 0);
    g_signal_connect(button_page3_1, "clicked", G_CALLBACK(setup_text), notebook);
    g_signal_connect(button_page3_2, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page3, gtk_label_new("Hinweise"));

    // page 4
    page4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_page4_1 = gtk_button_new_with_label("Verwendung:");
	label_page4_1 = gtk_label_new("1. Lesen sie vor der Verwendung die \nAnleitungen.");
	label_page4_2 = gtk_label_new("2. Kopieren sie immer alle Systemabbilder \ndes Flashs nach ~/Downloads/ROM-Install.");
	label_page4_3 = gtk_label_new("3. Sollten sie ein Samsung-Gerät flashen \nwollen nutzen sie immer 'heimdall'.");
	label_page4_4 = gtk_label_new("4. Prüfen sie regelmäßig, ob es Updates für das Programm gibt.");
    button_page4_2 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page4), button_page4_1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page4), label_page4_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page4), label_page4_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page4), label_page4_3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page4), label_page4_4, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page4), button_page4_2, FALSE, FALSE, 0);
    g_signal_connect(button_page4_1, "clicked", G_CALLBACK(setup_text), notebook);
    g_signal_connect(button_page4_2, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page4, gtk_label_new("Verwendung"));

	// page 5
    page5 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    label_end_1 = gtk_label_new(" ");
    button_end_1 = gtk_button_new_with_label("Viel Spaß bei der Verwendung des Fastboot Assistants!");
    label_end_2 = gtk_label_new(" ");
    button_end_2 = gtk_button_new_with_label("Fertig");
    gtk_box_pack_start(GTK_BOX(page5), label_end_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page5), button_end_1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page5), label_end_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page5), button_end_2, FALSE, FALSE, 0);
    g_signal_connect(button_end_1, "clicked", G_CALLBACK(setup_text), notebook);
    g_signal_connect(button_end_2, "clicked", G_CALLBACK(button_finish), notebook);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page5, gtk_label_new("Ende"));

    gtk_widget_show_all(window);
    
    gtk_main();
    g_print("Log: end run_first_run_setup\n");
}
