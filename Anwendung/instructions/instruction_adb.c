/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_adb		 *
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

static void adb_text()
{
	g_print("Die Lösung ist: 42");
}

void instruction_adb(int argc, char *argv[]) 
{
	GtkWidget *window;
    GtkWidget *page_adb1, *page_adb2, *page_adb3, *page_adb4;
    GtkWidget *label_adb1_1, *label_adb1_2, *label_adb1_3, *label_adb2_1, *label_adb2_2, *label_adb2_3, *label_adb3_1, *label_adb3_2, *label_adb3_3, *label_adb4_1, *label_adb4_2, *label_adb4_3;
    GtkWidget *button_adb1, *button_adb2, *button_adb3, *button_adb4, *button_adb5, *button_adb6, *button_adb7;

    gtk_init(&argc, &argv);
    css_provider(); // load css-provider
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "ADB/Fastboot");
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
    page_adb1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_adb1 = gtk_button_new_with_label("ADB/Fastboot");
    label_adb1_1 = gtk_label_new("ADB (Android Debug Bridge) dient als \nKommunikationsschnittstelle zwischen Computer und einem Android-Gerät. \nSie wird zum Debugging und Dateiübertragung verwendet.");
    label_adb1_2 = gtk_label_new("Fastboot ist ein Befehlszeilenwerkzeug \nfür den Bootloader von Android-Geräten, mit dem benutzerdefinierte Firmware \nund andere Systemabbilder geflasht werden können.");
    label_adb1_3 = gtk_label_new("Beide Tools sind für Entwickler und fortgeschrittene Nutzer \nvon großem Nutzen, wenn es darum geht, Android-Geräte zu modifizieren \nund zu diagnostizieren.");
    button_adb2 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_adb1), button_adb1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_adb1), label_adb1_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_adb1), label_adb1_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_adb1), label_adb1_3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_adb1), button_adb2, FALSE, FALSE, 0);
    g_signal_connect(button_adb1, "clicked", G_CALLBACK(adb_text), notebook);
    g_signal_connect(button_adb2, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_adb1, gtk_label_new("ADB/Fastboot"));

    // run css-provider
    add_css_provider(button_adb1, provider);
    add_css_provider(label_adb1_1, provider);
    add_css_provider(label_adb1_2, provider);
    add_css_provider(label_adb1_3, provider);
    add_css_provider(button_adb2, provider);
    
    // page 2
    page_adb2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_adb3 = gtk_button_new_with_label("Bootloader/Preloader");
    label_adb2_1 = gtk_label_new("Der Bootloader ist ein Programm, das beim Starten eines Android-Geräts \ndas Betriebssystem lädt und überprüft, ob die Software sicher und \nautorisiert ist.");
    label_adb2_2 = gtk_label_new("Durch das Öffnen des Bootloaders wird diese Sicherheitsprüfung umgangen, \num benutzerdefinierte Betriebssysteme oder Software \nauf dem Gerät zu installieren.");
    label_adb2_3 = gtk_label_new("\nDadurch lassen sich Custom-ROMs und andere Image-Dateien flashen.");
    button_adb4 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_adb2), button_adb3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_adb2), label_adb2_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_adb2), label_adb2_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_adb2), label_adb2_3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_adb2), button_adb4, FALSE, FALSE, 0);
    g_signal_connect(button_adb3, "clicked", G_CALLBACK(adb_text), notebook);
    g_signal_connect(button_adb4, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_adb2, gtk_label_new("Bootloader"));

    // run css-provider
    add_css_provider(button_adb3, provider);
    add_css_provider(label_adb2_1, provider);
    add_css_provider(label_adb2_2, provider);
    add_css_provider(label_adb2_3, provider);
    add_css_provider(button_adb4, provider);
    
	// page 3
    page_adb3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_adb5 = gtk_button_new_with_label("Verbinden mit ADB");
    label_adb3_1 = gtk_label_new("Verbinden sie ihr Gerät mit ihrem Computer. \n1.Enwickleroptionen aktivieren.\n1.1 Suchen sie in den Einstellungen nach 'Build-Nummer'.");
    label_adb3_2 = gtk_label_new("1.2. Tippen sie siebenmal auf die 'Build-Nummer' \n1.3. Suchen sie in den Einstellungen 'Debug'. \n1.4. Aktivieren sie USB-Debbuging. \n1.5. Aktivieren sie in den USB-Einstellungen 'Dateiübertragung'.");
    label_adb3_3 = gtk_label_new("2. Prüfen sie mithilfe des Programms ob Verbindung zur ADB besteht.");
    button_adb6 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_adb3), button_adb5, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_adb3), label_adb3_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_adb3), label_adb3_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_adb3), label_adb3_3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_adb3), button_adb6, FALSE, FALSE, 0);
    g_signal_connect(button_adb5, "clicked", G_CALLBACK(adb_text), notebook);
    g_signal_connect(button_adb6, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_adb3, gtk_label_new("ADB"));
    
    // run css-provider
    add_css_provider(button_adb5, provider);
    add_css_provider(label_adb3_1, provider);
    add_css_provider(label_adb3_2, provider);
    add_css_provider(label_adb3_3, provider);
    add_css_provider(button_adb6, provider);
    
    // page 4
    page_adb4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_adb7 = gtk_button_new_with_label("Neustart Fastboot");
    label_adb4_1 = gtk_label_new("1. Navigieren sie in der Anwendung durch 'Gerät neustarten' \nzu 'Neustart in Fastboot (von der ADB)'.");
    label_adb4_2 = gtk_label_new("2. Warten sie bis sich ihr Gerät im Fastboot-Modus befindet.");
    label_adb4_3 = gtk_label_new("3. Prüfen sie ob eine Verbindung zum Fastboot-Modus besteht.");
    gtk_box_pack_start(GTK_BOX(page_adb4), button_adb7, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_adb4), label_adb4_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_adb4), label_adb4_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_adb4), label_adb4_3, TRUE, TRUE, 0);
    g_signal_connect(button_adb5, "clicked", G_CALLBACK(adb_text), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_adb4, gtk_label_new("Fastboot"));
    
    // run css-provider
    add_css_provider(button_adb7, provider);
    add_css_provider(label_adb4_1, provider);
    add_css_provider(label_adb4_2, provider);
    add_css_provider(label_adb4_3, provider);
    
    // clean the storage
    g_object_unref(provider);
	
	// show all widgets
    gtk_widget_show_all(window);
	
	// run gtk mainloop
    gtk_main();
}
