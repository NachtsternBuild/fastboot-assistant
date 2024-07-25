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
    gtk_widget_set_size_request(window, 500, 400);

    // Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_close), NULL);

    // frame at the box
    GtkWidget *frame = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(window), frame);

    // create vbox
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(frame), vbox);
    
    // Frame for each information field
    GtkWidget *frame15 = gtk_frame_new(NULL);
    GtkWidget *frame16 = gtk_frame_new(NULL);
    
    // Vertical box layout for the frames
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    // show-text
    GtkWidget *inst6_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst6_label), g_strdup_printf("<b><u> Root Info </u></b>"));
    gtk_container_add(GTK_CONTAINER(vbox), inst6_label);

    // Creation of text labels with the text to be displayed
    const char *root_text = "\nBeim Rooten von Android-Geräten \nwerden dem Nutzer Superuser-Rechte eingeräumt, \ndie ihm vollen Zugriff auf \ndas Betriebssystem und die Möglichkeit geben, \nweitreichende Änderungen vorzunehmen, \ndie normalerweise gesperrt sind. \nDies ermöglicht unter anderem \ndas Entfernen vorinstallierter Anwendungen, \ndas Ändern von Systemeinstellungen \nund das Installieren spezieller Anwendungen, \ndie erweiterte Berechtigungen erfordern.\n";
    GtkWidget *label_root = gtk_label_new(adb_text);
    gtk_container_add(GTK_CONTAINER(frame15), label_root);
    
    // show-text
    GtkWidget *inst7_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst7_label), g_strdup_printf("<b><u> Root via Magisk </u></b>"));
    gtk_container_add(GTK_CONTAINER(vbox), inst7_label);
    
    // show-text
    GtkWidget *inst8_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst8_label), g_strdup_printf("Laden sie die Magisk-APK herunter via: \n<u><b>https://github.com/topjohnwu/Magisk/releases/download/v27.0/Magisk-v27.0.apk</u></b>"));
    gtk_container_add(GTK_CONTAINER(vbox), inst8_label);

    const char *prepare_root_text = "\n1. Installieren sie die Magisk-APK auf ihrem Gerät. \n2. Starten sie Magisk auf ihrem Gerät \nund wählen sie Magisk installieren. \n3. Wählen sie ein Boot-Image \nfür ihr Gerät und lassen sie es von der Magisk patchen \n(Meist finden sich die Boot-Images im Internet. \nHier ist Vorsicht geboten.) \n4. Kopieren sie das von Magisk gepatchte Boot-Image \nauf ihren Computer. \n5. benennen sie das Image um boot.img um oder \nlassen sie das von der Dateien von der Anwendung vorbereiten. \n6. Booten sie ihr Gerät in den Fastboot-Modus. \n7. Wählen sie unter 'Flashen von Dateien' \nflashen des Boot-Images für ihren Gerätetyp. \n8. Starten sie ihr Gerät neu.\nNun sollte Magisk Root-Rechte bereit stellen.\n";
    GtkWidget *label_prepare_root = gtk_label_new(prepare_root_text);
    gtk_container_add(GTK_CONTAINER(frame16), label_prepare_root);


    // Add frames to the main window
    gtk_box_pack_start(GTK_BOX(vbox), frame15, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame16, TRUE, TRUE, 5);

    // Show all elements
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}
