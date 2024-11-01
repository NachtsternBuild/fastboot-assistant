/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_root		 *
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

// function to open the GitHub website from magisk
void magisk(GtkWidget *widget, gpointer data)
{
    g_print("Log: magisk\n");
    const char *magisk_url = "https://github.com/topjohnwu/Magisk";
	open_url(magisk_url);
	g_print("Log: end magisk\n");
}

// open the downloads from the magisk apk
void magisk_apk(GtkWidget *widget, gpointer data)
{
    g_print("Log: magisk_apk\n");
    const char *magisk_apk_url = "https://github.com/topjohnwu/Magisk/releases/download/v27.0/Magisk-v27.0.apk";    
	open_url(magisk_apk_url);
	g_print("Log: end magisk_apk\n");
}

static void root_text()
{
	g_print("Log: Läuft irgendwie nicht, oder?\n");
}

void instruction_root(int argc, char *argv[]) 
{
	g_print("Log: instruction_root\n");
	GtkWidget *window;
    GtkWidget *page_root1, *page_root2, *page_root3;
    GtkWidget *label_root1_1, *label_root1_2, *label_root1_3, *label_root2_1, *label_root2_2, *label_root2_3, *label_root3_1, *label_root3_2, *label_root3_3, *label_root3_4;
    GtkWidget *button_root1, *button_root2, *button_root3, *button_root4, *button_root5, *button_root6, *button_root7;

    gtk_init(&argc, &argv);
    apply_theme();
    //css_provider(); // load css-provider
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Rooten");
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
    page_root1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_root1 = gtk_button_new_with_label("Hinweise");
    label_root1_1 = gtk_label_new("Beim Rooten von Android-Geräten werden dem Nutzer Superuser-Rechte \neingeräumt, die ihm vollen Zugriff auf Android. Damit die \nMöglichkeit weitreichende Änderungen vorzunehmen.");
    label_root1_2 = gtk_label_new("Dies ermöglicht das Entfernen vorinstallierter Anwendungen, \ndas Ändern von Systemeinstellungen und Installieren spezieller Anwendungen, \ndie erweiterte Berechtigungen erfordern.");
    label_root1_3 = gtk_label_new("Mit den umfangreichen Rechten bestehen auch große Gefahren, \nda Nutzer und Software große Schäden an der Software verursachen können.");
    button_root2 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_root1), button_root1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_root1), label_root1_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_root1), label_root1_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_root1), label_root1_3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_root1), button_root2, FALSE, FALSE, 0);
    g_signal_connect(button_root1, "clicked", G_CALLBACK(root_text), notebook);
    g_signal_connect(button_root2, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_root1, gtk_label_new("Hinweise"));

    // run css-provider
    add_css_provider(button_root1, provider);
    add_css_provider(label_root1_1, provider);
    add_css_provider(label_root1_2, provider);
    add_css_provider(label_root1_3, provider);
    add_css_provider(button_root2, provider);
    
    // page 2
    page_root2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_root3 = gtk_button_new_with_label("Magisk");
    label_root2_1 = gtk_label_new("Magisk ist ein Paket von Open-Source-Software für die Anpassung von Android. \nMit folgenden Betsnadteilen:");
    label_root2_2 = gtk_label_new("1. MagiskSU: Bereitstellung von Root-Zugriff für Anwendungen. \n2. Magisk Modules: Ändern von schreibgeschützten Partitionen durch Installation von Modulen.");
    label_root2_3 = gtk_label_new("3. MagiskBoot: Das umfassendste Tool zum Entpacken und Neuverpacken von Android-Boot-Images. \n4. Zygisk: Code in allen Prozessen von Android-Anwendungen ausführen.");
    button_root4 = gtk_button_new_with_label("Magisk");
    button_root5 = gtk_button_new_with_label("Magisk-APK");
    button_root6 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_root2), button_root3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_root2), label_root2_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_root2), label_root2_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_root2), label_root2_3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_root2), button_root4, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_root2), button_root5, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_root2), button_root6, FALSE, FALSE, 0);
    g_signal_connect(button_root3, "clicked", G_CALLBACK(root_text), notebook);
    g_signal_connect(button_root4, "clicked", G_CALLBACK(magisk), notebook);
    g_signal_connect(button_root5, "clicked", G_CALLBACK(magisk_apk), notebook);
    g_signal_connect(button_root6, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_root2, gtk_label_new("Magisk"));

    // run css-provider
    add_css_provider(button_root3, provider);
    add_css_provider(label_root2_1, provider);
    add_css_provider(label_root2_2, provider);
    add_css_provider(label_root2_3, provider);
    add_css_provider(button_root4, provider);
    add_css_provider(button_root5, provider);
    add_css_provider(button_root6, provider);
    
	// page 3
    page_root3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_root7 = gtk_button_new_with_label("Rooten via Magisk");
    label_root3_1 = gtk_label_new("1. Installieren Sie die Magisk-APK auf Ihrem Gerät. \n2. Starten Sie Magisk auf Ihrem Gerät und wählen Sie Magisk installieren.");
    label_root3_2 = gtk_label_new("3. Wählen Sie ein Boot-Image \nfür Ihr Gerät und lassen Sie es von Magisk patchen \n(Meist finden sich die Boot-Images im Internet. \nHier ist Vorsicht geboten.)");
    label_root3_3 = gtk_label_new("4. Kopieren Sie das von Magisk gepatchte Boot-Image \nauf Ihren Computer. \n5. Benennen Sie das Image um boot.img um oder \nlassen Sie es von der Anwendung vorbereiten.");
    label_root3_4 = gtk_label_new("6. Starten sie ihr Gerät in Fastboot \n7. Flashen sie das Boot-Image für Ihren Gerätetyp. \n8. Starten Sie Ihr Gerät neu.\nNun sollte Magisk Root-Rechte bereitstellen.");
    gtk_box_pack_start(GTK_BOX(page_root3), button_root7, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_root3), label_root3_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_root3), label_root3_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_root3), label_root3_3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_root3), label_root3_4, TRUE, TRUE, 0);
    g_signal_connect(button_root7, "clicked", G_CALLBACK(root_text), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_root3, gtk_label_new("Rooten"));
    
    // run css-provider
    add_css_provider(button_root7, provider);
    add_css_provider(label_root3_1, provider);
    add_css_provider(label_root3_2, provider);
    add_css_provider(label_root3_3, provider);
    add_css_provider(label_root3_4, provider);
    
    // clean the storage
    g_object_unref(provider);
	
	// show all widgets
    gtk_widget_show_all(window);
	
	// run gtk mainloop
    gtk_main();
    g_print("Log: end instruction_root\n");
}
