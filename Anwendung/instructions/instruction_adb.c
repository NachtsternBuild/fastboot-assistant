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
    gtk_widget_set_size_request(window, 500, 400);

    // Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_close), NULL);

    // frame at the box
    GtkWidget *frame = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(window), frame);
    
    // Frame for each information field
    GtkWidget *frame9 = gtk_frame_new(NULL);
    GtkWidget *frame10 = gtk_frame_new(NULL);
    GtkWidget *frame11 = gtk_frame_new(NULL);
    GtkWidget *frame12 = gtk_frame_new(NULL);
    GtkWidget *frame13 = gtk_frame_new(NULL);
    GtkWidget *frame14 = gtk_frame_new(NULL);
    
    // Vertical box layout for the frames
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    // show-text
    GtkWidget *inst1_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst1_label), g_strdup_printf("<b><u> Android Debug Bridge (ADB)/ Fastboot </u></b>"));
    gtk_container_add(GTK_CONTAINER(vbox), inst1_label);

    // Creation of text labels with the text to be displayed
    const char *adb_text = "\nADB (Android Debug Bridge) stellt \neine Kommunikationsschnittstelle zwischen einem Computer \nund einem Android-Gerät zur Verfügung, \ndie für Debugging und Dateiübertragung genutzt werden kann.\nFastboot ist ein Befehlszeilenwerkzeug \nfür den Bootloader-Modus von Android-Geräten, \nmit dem benutzerdefinierte Firmware und andere Systemabbilder \ngeflasht werden können. \nBeide Tools sind für Entwickler und fortgeschrittene Nutzer \nvon großem Nutzen, wenn es darum geht, Android-Geräte \nzu modifizieren und zu diagnostizieren.\n";
    GtkWidget *label_adb = gtk_label_new(adb_text);
    gtk_container_add(GTK_CONTAINER(frame9), label_adb);
    
    // show-text
    GtkWidget *inst2_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst2_label), g_strdup_printf("<b><u> Verbinden mit ADB </u></b>"));
    gtk_container_add(GTK_CONTAINER(vbox), inst2_label);

    const char *connect1_text = "\nVerbinden sie ihr das Gerät mit ihrem Computer.\n";
    GtkWidget *label_connect1 = gtk_label_new(connect1_text);
    gtk_container_add(GTK_CONTAINER(frame10), label_connect1);

    const char *connect2_text = "\nEntwickleroptionen aktivieren.\n1.Suchen sie in den Einstellungen nach 'Build-Nummer'. \n2. Tippen sie siebenmal auf die 'Build-Nummer'. \n3. Suchen sie in den Einstellungen 'Debug'. \n4. Aktivieren sie USB-Debbuging. \n5. Aktivieren sie in \nden USB-Einstellungen 'Dateiübertragung'. \n5. Prüfen sie ob eine Verbindung zur ADB besteht.\n";
    GtkWidget *label_connect2 = gtk_label_new(connect2_text);
    gtk_container_add(GTK_CONTAINER(frame11), label_connect2);
    
    // show-text
    GtkWidget *inst3_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst3_label), g_strdup_printf("<b><u> Neustart in Fastboot </u></b>"));
    gtk_container_add(GTK_CONTAINER(vbox), inst3_label);

    const char *connect3_text = "\n1. Navigieren sie in der Anwendung \ndurch 'Gerät neustarten' zu \n'Neustart in Fastboot (von der ADB)'. \n2. Warten sie bis sich \nihr Gerät im Fastboot-Modus befindet. \n3. Prüfen sie ob eine Verbindung \nzum Fastboot-Modus besteht.\n";
    GtkWidget *label_connect3 = gtk_label_new(connect3_text);
    gtk_container_add(GTK_CONTAINER(frame12), label_connect3);
    
    // show-text
    GtkWidget *inst4_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst4_label), g_strdup_printf("<b><u> Weiteres </u></b>"));
    gtk_container_add(GTK_CONTAINER(vbox), inst4_label);
    
    const char *more_text = "\nWollen sie mehr über die \nBedienung von Fastboot erfahren \nstarten sie die Fastboot-Hilfe.\n";
    GtkWidget *label_more = gtk_label_new(more_text);
    gtk_container_add(GTK_CONTAINER(frame13), label_more);
    
    // show-text
    GtkWidget *inst5_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst5_label), g_strdup_printf("<b><u> Bootlader/Preloader </u></b>"));
    gtk_container_add(GTK_CONTAINER(vbox), inst5_label);

    // Creation of text labels with the text to be displayed
    const char *bootloader_text = "\nDer Bootloader ist ein Programm, \ndas beim Starten eines Android-Geräts \ndas Betriebssystem lädt und überprüft, \nob die Software sicher und autorisiert ist. \nDurch das Öffnen des Bootloaders \nwird diese Sicherheitsprüfung umgangen, \num benutzerdefinierte Betriebssysteme oder Software \nauf dem Gerät zu installieren. \nDadurch lassen sich Custom-ROMs \nund andere Image-Dateien flashen.\n";
    GtkWidget *label_bootloader = gtk_label_new(bootloader_text);
    gtk_container_add(GTK_CONTAINER(frame14), label_bootloader);
    
    // Add frames to the main window
    gtk_box_pack_start(GTK_BOX(vbox), frame9, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame10, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame11, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame12, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame13, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame14, TRUE, TRUE, 5);

    // Show all elements
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}
