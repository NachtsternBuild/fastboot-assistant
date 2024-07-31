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
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

void instruction_root(int argc, char *argv[]) 
{
    // Initiate GTK
    gtk_init(&argc, &argv);

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Anleitung Gerät rooten");
    gtk_widget_set_size_request(window, 1000, 950);

    // Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Vertical box layout for the frames
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    // Root Info header
    GtkWidget *inst6_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst6_label), "<b><u>Root Info</u></b>");
    gtk_box_pack_start(GTK_BOX(vbox), inst6_label, FALSE, FALSE, 5);

    // Description about root
    const char *root_text = "\nBeim Rooten von Android-Geräten \nwerden dem Nutzer Superuser-Rechte eingeräumt, \ndie ihm vollen Zugriff auf \ndas Betriebssystem und die Möglichkeit geben, \nweitreichende Änderungen vorzunehmen, \ndie normalerweise gesperrt sind. \nDies ermöglicht unter anderem \ndas Entfernen vorinstallierter Anwendungen, \ndas Ändern von Systemeinstellungen \nund das Installieren spezieller Anwendungen, \ndie erweiterte Berechtigungen erfordern.\n";
    GtkWidget *label_root = gtk_label_new(root_text);
    gtk_box_pack_start(GTK_BOX(vbox), label_root, TRUE, TRUE, 5);
    
    // Root via Magisk header
    GtkWidget *inst7_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst7_label), "<b><u>Root via Magisk</u></b>");
    gtk_box_pack_start(GTK_BOX(vbox), inst7_label, FALSE, FALSE, 5);
    
    // Magisk download link
    GtkWidget *inst8_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst8_label), "<b>Laden Sie die Magisk-APK herunter via:</b> \nhttps://github.com/topjohnwu/Magisk/releases/download/v27.0/Magisk-v27.0.apk");
    gtk_box_pack_start(GTK_BOX(vbox), inst8_label, FALSE, FALSE, 5);

    // Steps to root the device
    const char *prepare_root_text = "\n1. Installieren Sie die Magisk-APK auf Ihrem Gerät. \n2. Starten Sie Magisk auf Ihrem Gerät \nund wählen Sie Magisk installieren. \n3. Wählen Sie ein Boot-Image \nfür Ihr Gerät und lassen Sie es von Magisk patchen \n(Meist finden sich die Boot-Images im Internet. \nHier ist Vorsicht geboten.) \n4. Kopieren Sie das von Magisk gepatchte Boot-Image \nauf Ihren Computer. \n5. Benennen Sie das Image um boot.img um oder \nlassen Sie es von der Anwendung vorbereiten. \n6. Booten Sie Ihr Gerät in den Fastboot-Modus. \n7. Wählen Sie unter 'Flashen von Dateien' \nFlashen des Boot-Images für Ihren Gerätetyp. \n8. Starten Sie Ihr Gerät neu.\nNun sollte Magisk Root-Rechte bereitstellen.\n";
    GtkWidget *label_prepare_root = gtk_label_new(prepare_root_text);
    gtk_box_pack_start(GTK_BOX(vbox), label_prepare_root, TRUE, TRUE, 5);

    // Show all elements
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}

