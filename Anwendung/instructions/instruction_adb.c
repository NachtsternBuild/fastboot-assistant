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
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

void instruction_adb(int argc, char *argv[]) 
{
    // Initiate GTK
    gtk_init(&argc, &argv);

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Anleitung ADB/Fastboot");
    gtk_widget_set_size_request(window, 1000, 950);

    // Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Vertical box layout for the frames
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // show-text for ADB/Fastboot title
    GtkWidget *inst1_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst1_label), "<b><u>Android Debug Bridge (ADB)/ Fastboot</u></b>");
    gtk_box_pack_start(GTK_BOX(vbox), inst1_label, FALSE, FALSE, 5);

    // Frame and label for ADB/Fastboot description
    GtkWidget *frame9 = gtk_frame_new(NULL);
    GtkWidget *label_adb = gtk_label_new("\nADB (Android Debug Bridge) stellt \neine Kommunikationsschnittstelle zwischen einem Computer \nund einem Android-Gerät zur Verfügung, \ndie für Debugging und Dateiübertragung genutzt werden kann.\nFastboot ist ein Befehlszeilenwerkzeug \nfür den Bootloader-Modus von Android-Geräten, \nmit dem benutzerdefinierte Firmware und andere Systemabbilder \ngeflasht werden können. \nBeide Tools sind für Entwickler und fortgeschrittene Nutzer \nvon großem Nutzen, wenn es darum geht, Android-Geräte \nzu modifizieren und zu diagnostizieren.\n");
    gtk_container_add(GTK_CONTAINER(frame9), label_adb);
    gtk_box_pack_start(GTK_BOX(vbox), frame9, TRUE, TRUE, 5);

    // show-text for connecting with ADB
    GtkWidget *inst2_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst2_label), "<b><u>Verbinden mit ADB</u></b>");
    gtk_box_pack_start(GTK_BOX(vbox), inst2_label, FALSE, FALSE, 5);

    // Frame and labels for ADB connection steps
    GtkWidget *frame10 = gtk_frame_new(NULL);
    GtkWidget *label_connect1 = gtk_label_new("\nVerbinden sie ihr das Gerät mit ihrem Computer.\n");
    gtk_container_add(GTK_CONTAINER(frame10), label_connect1);
    gtk_box_pack_start(GTK_BOX(vbox), frame10, TRUE, TRUE, 5);

    GtkWidget *frame11 = gtk_frame_new(NULL);
    GtkWidget *label_connect2 = gtk_label_new("\nEntwickleroptionen aktivieren. \n \n1. Suchen sie in den Einstellungen nach 'Build-Nummer'. \n2. Tippen sie siebenmal auf die 'Build-Nummer'. \n3. Suchen sie in den Einstellungen 'Debug'. \n4. Aktivieren sie USB-Debbuging. \n5. Aktivieren sie in \nden USB-Einstellungen 'Dateiübertragung'. \n6. Prüfen sie ob eine Verbindung zur ADB besteht.\n");
    gtk_container_add(GTK_CONTAINER(frame11), label_connect2);
    gtk_box_pack_start(GTK_BOX(vbox), frame11, TRUE, TRUE, 5);

    // show-text for restarting in Fastboot
    GtkWidget *inst3_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst3_label), "<b><u>Neustart in Fastboot</u></b>");
    gtk_box_pack_start(GTK_BOX(vbox), inst3_label, FALSE, FALSE, 5);

    // Frame and label for Fastboot connection steps
    GtkWidget *frame12 = gtk_frame_new(NULL);
    GtkWidget *label_connect3 = gtk_label_new("\n1. Navigieren sie in der Anwendung \ndurch 'Gerät neustarten' zu \n'Neustart in Fastboot (von der ADB)'. \n2. Warten sie bis sich \nihr Gerät im Fastboot-Modus befindet. \n3. Prüfen sie ob eine Verbindung \nzum Fastboot-Modus besteht.\n");
    gtk_container_add(GTK_CONTAINER(frame12), label_connect3);
    gtk_box_pack_start(GTK_BOX(vbox), frame12, TRUE, TRUE, 5);

    // show-text for additional information
    GtkWidget *inst4_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst4_label), "<b><u>Weiteres</u></b>");
    gtk_box_pack_start(GTK_BOX(vbox), inst4_label, FALSE, FALSE, 5);

    // Frame and label for additional information
    GtkWidget *frame13 = gtk_frame_new(NULL);
    GtkWidget *label_more = gtk_label_new("\nWollen sie mehr über die \nBedienung von Fastboot erfahren \nstarten sie die Fastboot-Hilfe.\n");
    gtk_container_add(GTK_CONTAINER(frame13), label_more);
    gtk_box_pack_start(GTK_BOX(vbox), frame13, TRUE, TRUE, 5);

    // show-text for Bootloader/Preloader
    GtkWidget *inst5_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst5_label), "<b><u>Bootloader/Preloader</u></b>");
    gtk_box_pack_start(GTK_BOX(vbox), inst5_label, FALSE, FALSE, 5);

    // Frame and label for Bootloader information
    GtkWidget *frame14 = gtk_frame_new(NULL);
    GtkWidget *label_bootloader = gtk_label_new("\nDer Bootloader ist ein Programm, \ndas beim Starten eines Android-Geräts \ndas Betriebssystem lädt und überprüft, \nob die Software sicher und autorisiert ist. \nDurch das Öffnen des Bootloaders \nwird diese Sicherheitsprüfung umgangen, \num benutzerdefinierte Betriebssysteme oder Software \nauf dem Gerät zu installieren. \nDadurch lassen sich Custom-ROMs \nund andere Image-Dateien flashen.\n");
    gtk_container_add(GTK_CONTAINER(frame14), label_bootloader);
    gtk_box_pack_start(GTK_BOX(vbox), frame14, TRUE, TRUE, 5);

    // Show all elements
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}

