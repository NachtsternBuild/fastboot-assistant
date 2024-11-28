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
#include "language_check.h"
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

void instruction_root(int argc, char *argv[]) 
{
	g_print("Log: instruction_root\n");
	
	// GTK init
    gtk_init();

    apply_theme();
    apply_language();
    
	GtkWidget *window, *notebook;
    GtkWidget *page1, *page2, *page3;
    GtkWidget *label_root1_1, *label_root1_2, *label_root1_3, *label_root2_1, *label_root2_2, *label_root2_3, *label_root3_1, *label_root3_2, *label_root3_3, *label_root3_4;
    GtkWidget *button_root1, *button_root2, *button_root3, *button_root4, *button_root5, *button_root6, *button_root7;
    
    // create the main window
    window = gtk_window_new();
    const char *instruction_root_window = strcmp(language, "de") == 0 ? "Rooten" : "Rooting";
    gtk_window_set_title(GTK_WINDOW(window), instruction_root_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);

    // create the notebook
    notebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // page 1
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    button_root1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Hinweise" : "Notes");
    label_root1_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Beim Rooten von Android-Geräten werden dem Nutzer Superuser-Rechte \neingeräumt, die ihm vollen Zugriff auf Android. Damit die \nMöglichkeit weitreichende Änderungen vorzunehmen." : "When rooting Android devices, the user is granted superuser \nrights that give them full access to Android. This gives them the possibility \nto make far-reaching changes.");
    label_root1_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Dies ermöglicht das Entfernen vorinstallierter Anwendungen, \ndas Ändern von Systemeinstellungen und Installieren spezieller Anwendungen, \ndie erweiterte Berechtigungen erfordern." : "This allows you to remove pre-installed applications, \nchange system settings and install special applications \nthat require extended permissions.");
    label_root1_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Mit den umfangreichen Rechten bestehen auch große Gefahren, \nda Nutzer und Software große Schäden an der Software verursachen können." : "With the extensive rights, there are also great dangers \nwhile users and software can cause great damage to the software.");
    button_root2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_root1);
    gtk_box_append(GTK_BOX(page1), label_root1_1);
    gtk_box_append(GTK_BOX(page1), label_root1_2);
    gtk_box_append(GTK_BOX(page1), label_root1_3);
    gtk_box_append(GTK_BOX(page1), button_root2);

    // connect everything
    g_signal_connect(button_root2, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, gtk_label_new(g_strcmp0(language, "de") == 0 ? "Hinweise" : "Notes"));
    
    // page 2
    page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_root3 = gtk_button_new_with_label("Magisk");
    label_root2_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Magisk ist ein Paket von Open-Source-Software für die Anpassung von Android. \nMit folgenden Bestandteilen:" : "Magisk is a package of open source software for Android customization. \nWith the following components:");
    label_root2_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. MagiskSU: Bereitstellung von Root-Zugriff für Anwendungen. \n2. Magisk Modules: Ändern von schreibgeschützten Partitionen durch Installation von Modulen." : "1. MagiskSU: Provision of root access for applications. \n2. Magisk Modules: Change read-only partitions by installing modules.");
    label_root2_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "3. MagiskBoot: Das umfassendste Tool zum Entpacken und Neuverpacken von Android-Boot-Images. \n4. Zygisk: Code in allen Prozessen von Android-Anwendungen ausführen." : "3. MagiskBoot: The most comprehensive tool for unpacking and repacking Android boot images. \n4. Zygisk: Execute code in all processes of Android applications.");
    button_root4 = gtk_button_new_with_label("Magisk");
    button_root5 = gtk_button_new_with_label("Magisk-APK");
    button_root6 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_root3);
    gtk_box_append(GTK_BOX(page2), label_root2_1);
    gtk_box_append(GTK_BOX(page2), label_root2_2);
    gtk_box_append(GTK_BOX(page2), label_root2_3);
    gtk_box_append(GTK_BOX(page2), button_root4);
    gtk_box_append(GTK_BOX(page2), button_root5);
    gtk_box_append(GTK_BOX(page2), button_root5);

    // connect everything
    g_signal_connect(button_root4, "clicked", G_CALLBACK(magisk), notebook);
    g_signal_connect(button_root5, "clicked", G_CALLBACK(magisk_apk), notebook);
    g_signal_connect(button_root6, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page2, gtk_label_new("Magisk"));
    
    // page 3
    page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_root7 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Rooten via Magisk" : "Rooting via Magisk");
    label_root3_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Installieren Sie die Magisk-APK auf Ihrem Gerät. \n2. Starten Sie Magisk auf Ihrem Gerät und wählen Sie Magisk installieren." : "1. Install the Magisk APK on your device. \n2. Start Magisk on your device and select Install Magisk.");
    label_root3_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "3. Wählen Sie ein Boot-Image \nfür Ihr Gerät und lassen Sie es von Magisk patchen \n(Meist finden sich die Boot-Images im Internet. \nHier ist Vorsicht geboten.)" : "3. Select a boot image \nfor your device and have it patched by Magisk \n(Usually the boot images can be found on the Internet. \nCaution is advised here).");
    label_root3_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "4. Kopieren Sie das von Magisk gepatchte Boot-Image \nauf Ihren Computer. \n5. Benennen Sie das Image um boot.img um oder \nlassen Sie es von der Anwendung vorbereiten." : "4. Copy the boot image patched by Magisk to your computer. \n5. Rename the image to boot.img or \nlet the application prepare it.");
    label_root3_4 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "6. Starten sie ihr Gerät in Fastboot \n7. Flashen sie das Boot-Image für Ihren Gerätetyp. \n8. Starten Sie Ihr Gerät neu.\nNun sollte Magisk Root-Rechte bereitstellen." : "6. Start your device in Fastboot \n7. Flash the boot image for your device type. \n8. Reboot your device \nNow Magisk should provide root privileges.");
    
     // add everything to the page
    gtk_box_append(GTK_BOX(page3), button_root7);
    gtk_box_append(GTK_BOX(page3), label_root3_1);
    gtk_box_append(GTK_BOX(page3), label_root3_2);
    gtk_box_append(GTK_BOX(page3), label_root3_3);
    gtk_box_append(GTK_BOX(page3), label_root3_4);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page3, gtk_label_new(g_strcmp0(language, "de") == 0 ? "Rooten" : "Rooting"));
    
     // show all widgets
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop); 
    g_print("Log: end instruction_root\n");
}
