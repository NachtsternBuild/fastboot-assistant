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
#include <gtk/gtk.h>
#include <unistd.h>
#include "function_header.h"
#include "language_check.h"
#include "program_functions.h"
#include "language_check.h"

// the setup wizard
void run_first_run_setup(GtkCssProvider *provider) 
{
    g_print("Log: run_first_run_setup\n");
    
    // GTK init
    gtk_init();

    apply_theme();
    apply_language();

    GtkWidget *window, *notebook;
    GtkWidget *page1, *page2, *page3, *page4, *page5;
    GtkWidget *label_welcome_1, *label_welcome_2, *label_page2_1, *label_page2_2, *label_page3_1, *label_page3_2, *label_page3_3, *label_page3_4, *label_page4_1, *label_page4_2, *label_page4_3, *label_page4_4, *label_end_1, *label_end_2;
    GtkWidget *button_welcome_1, *button_toggle_language, *button_toggle_theme, *button_welcome_2, *button_page2_1, *button_dir, *button_page2_2, *button_page3_1, *button_page3_2, *button_page4_1, *button_page4_2, *button_end_1, *button_end_2;

    // create the main window
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Fastboot Assistant Setup");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);

    // create the notebook
    notebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // page 1
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    button_welcome_1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Willkommen zum Fastboot Assistant!" : "Welcome to the Fastboot Assistant!");
    label_welcome_1 = gtk_label_new(" ");
    button_toggle_language = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Sprache wechseln (Deutsch/Englisch)" : "Switch Language (English/German)");
    button_toggle_theme = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Thema wechseln (hell/dunkel)" : "Toggle Theme (Light/Dark)");
    label_welcome_2 = gtk_label_new(" ");
    button_welcome_2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");

    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_welcome_1);
    gtk_box_append(GTK_BOX(page1), label_welcome_1);
    gtk_box_append(GTK_BOX(page1), button_toggle_language);
    gtk_box_append(GTK_BOX(page1), button_toggle_theme);
    gtk_box_append(GTK_BOX(page1), label_welcome_2);
    gtk_box_append(GTK_BOX(page1), button_welcome_2);

    // connect everything
    g_signal_connect(button_toggle_language, "clicked", G_CALLBACK(toggle_language), notebook);
    g_signal_connect(button_toggle_theme, "clicked", G_CALLBACK(toggle_theme), notebook);
    g_signal_connect(button_welcome_2, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, gtk_label_new(g_strcmp0(language, "de") == 0 ? "Begrüßung" : "Welcome"));
    
    // page 2
    page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_page2_1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Zum korrekten Ausführen muss der \nFastboot-Assistant einige Konfigurationen vornehmen." : "To run correctly, the Fastboot \nAssistant must make some configurations.");
    label_page2_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Es werden alle benötigten Ordner erstellt." : "1. All required folders are created.");
    label_page2_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "2. Anpassungen an das Betriebssystem werden durchgeführt." : "2. Adjustments are made to the operating system.");
    button_dir = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Konfigurieren" : "Configure" );
    button_page2_2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_page2_1);
    gtk_box_append(GTK_BOX(page2), label_page2_1);
    gtk_box_append(GTK_BOX(page2), label_page2_2);
    gtk_box_append(GTK_BOX(page2), button_dir);
    gtk_box_append(GTK_BOX(page2), button_page2_2);

    // connect everything
    g_signal_connect(button_toggle_language, "clicked", G_CALLBACK(config_start), notebook);
    g_signal_connect(button_page2_2, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page2, gtk_label_new(g_strcmp0(language, "de") == 0 ? "Konfiguration" : "Configuration"));
	
	// page 3
    page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_page3_1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Hinweise" : "Notes");
	label_page3_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Die Verwendung erfolgt auf eigene Gefahr." : "1. Use at your own risk.");
	label_page3_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "2. Das Gerät kann beschädigt werden." : "2. The device may be damaged.");
	label_page3_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "3. Nicht jedes Gerät unterstützt alle Funktionen" : "3. Not every device supports all functions");
	label_page3_4 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "4. Nicht alle Betriebssystemvarianten haben den gleichen Funktionsumfang." : "4. Not all operating system variants have the same range of functions.");
    button_page3_2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page3), button_page3_1);
    gtk_box_append(GTK_BOX(page3), label_page3_1);
    gtk_box_append(GTK_BOX(page3), label_page3_2);
    gtk_box_append(GTK_BOX(page3), label_page3_3);
    gtk_box_append(GTK_BOX(page3), label_page3_4);
    gtk_box_append(GTK_BOX(page3), button_page3_2);
    
    // connect everything
    g_signal_connect(button_page3_2, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page3, gtk_label_new(g_strcmp0(language, "de") == 0 ? "Hinweise" : "Notes"));
    
    // page 4
    page4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_page4_1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Verwendung" : "Use");
	label_page4_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Lesen sie vor der Verwendung die \nAnleitungen und die Dokumentation." : "1. Read the instructions and \ndocumentation before use.");
	label_page4_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "2. Kopieren sie immer alle Systemabbilder \ndes Flashs nach ~/Downloads/ROM-Install." : "2. Always copy all system images \ndes Flashs to ~/Downloads/ROM-Install.");
	label_page4_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "3. Sollten sie ein Samsung-Gerät flashen \nwollen nutzen sie immer 'heimdall'." : "3. If you want to flash a Samsung device, \nalways use 'heimdall'.");
	label_page4_4 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "4. Prüfen sie regelmäßig, ob es Updates für das Programm gibt." : "4. Check regularly whether there are updates for the program.");
    button_page4_2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page3), button_page4_1);
    gtk_box_append(GTK_BOX(page3), label_page4_1);
    gtk_box_append(GTK_BOX(page3), label_page4_2);
    gtk_box_append(GTK_BOX(page3), label_page4_3);
    gtk_box_append(GTK_BOX(page3), label_page4_4);
    gtk_box_append(GTK_BOX(page3), button_page4_2);
    
    // connect everything
    g_signal_connect(button_page4_2, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page4, gtk_label_new(g_strcmp0(language, "de") == 0 ? "Verwendung" : "Use"));
    
    // page 5
    page5 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    label_end_1 = gtk_label_new(" ");
    button_end_1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Viel Spaß bei der Verwendung des Fastboot Assistants!" : "Have fun using the Fastboot Assistant!");
    label_end_2 = gtk_label_new(" ");
    button_end_2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Fertig" : "Finished");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page5), label_end_1);
    gtk_box_append(GTK_BOX(page5), button_end_1);
    gtk_box_append(GTK_BOX(page5), label_end_2);
    gtk_box_append(GTK_BOX(page5), button_end_2);
    
    // connect everything
    g_signal_connect(button_end_2, "clicked", G_CALLBACK(gtk_window_destroy), notebook);
    
    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page4, gtk_label_new(g_strcmp0(language, "de") == 0 ? "Ende" : "End"));
    
    // show all widgets
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop); 
    g_print("Log: end run_first_run_setup\n");
}
