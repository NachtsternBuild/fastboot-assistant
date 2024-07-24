/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_gsi		 *
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

void instruction_gsi(int argc, char *argv[]) 
{
    // Initiate GTK
    gtk_init(&argc, &argv);

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Anleitung Generic System Image");
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
    GtkWidget *frame18 = gtk_frame_new(NULL);
    GtkWidget *frame19 = gtk_frame_new(NULL);
    GtkWidget *frame20 = gtk_frame_new(NULL);
    
    // Vertical box layout for the frames
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    // show-text
    GtkWidget *inst10_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst10_label), g_strdup_printf("<b><u> Generic System Image </u></b>"));
    gtk_container_add(GTK_CONTAINER(vbox), inst10_label);

    // Creation of text labels with the text to be displayed
    const char *gsi_text = "\nGSI (Generic System Image) ist ein unverändertes Android-System-Image, \ndass eine Unterstützung von Project Treble voraussetzt. \nProject Treble ist ein Projekt des \nAndroid Open Source Project (AOSP), \ndass die hersteller- und gerätspezifischen Betriebssystemteile \nvon dem Rest des Betriebssystems trennt. \nEs dient dazu, Entwicklern und Herstellern die Möglichkeit zu geben, \nneue Android-Versionen und Funktionen zu testen, \nohne auf gerätespezifische Anpassungen erfolgen müssen. \nAußerdem ermöglicht stellt das GSI \neine Möglichkeit Android-Geräten ohne Custom-ROMs \nUnterstützung das manuelle aufspielen neuer Android-Versionen.\n";
    GtkWidget *label_gsi = gtk_label_new(gsi_text);
    gtk_container_add(GTK_CONTAINER(frame18), label_gsi);
    
    // show-text
    GtkWidget *inst11_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst11_label), g_strdup_printf("<b><u> Kernel </u></b>"));
    gtk_container_add(GTK_CONTAINER(vbox), inst11_label);

    // Creation of text labels with the text to be displayed
    const char *kernel_text = "\nDer Kernel stellt den zentralen Bestandteil \neines Betriebssystems dar. \nEr kommuniziert direkt mit der Hardware und verwaltet \ngrundlegende Systemressourcen wie CPU, Speicher und Geräte. \nEr stellt eine Schnittstelle zwischen der Hardware \nund den Anwendungsprogrammen \nund dem Rest des Betriebssystemsbereit, \num eine effiziente und sichere Ausführung zu gewährleisten.\n Verschiedene Android-Versionen nur mit \neiner Reihe an Kernel-Versionen kompatibel. \nSollte das nicht der Fall sein, \nstartet das Android gar nicht erst.\n";
    GtkWidget *label_kernel = gtk_label_new(kernel_text);
    gtk_container_add(GTK_CONTAINER(frame19), label_kernel);
    
    // show-text
    GtkWidget *inst12_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst12_label), g_strdup_printf("<b><u> Flashen eines GSI </u></b>"));
    gtk_container_add(GTK_CONTAINER(vbox), inst12_label);

    const char *flash_gsi_text = "\n1. Prüfen sie ob ihr Gerät mit Project Treble kompatibel ist. \n2. Laden sie ein entsprechendes GSI herunter. \n3. Booten sie ihr Gerät in Fastboot. \n 4. Öffnen sie den Bootloader.\nManche Geräte unterstützen sie nicht \ndie Methode über Fastboot. \nInformieren sie sich genauer über ihr Chipssatz. \n \nAls Methoden des Flashs gibt es die \nAlternativen 'dirty flash'(1) und 'clean flash'(2). \nBei einem 'dirty flash' bleiben die Nutzerdaten erhalten, \naber nicht jedes GSI startet danach. \nWählen sie eine Variante. \n5.1. Führen sie einen flash des System-Images durch. \n6.1. Starten sie ihr Gerät neu. \n \n5.2. Löschen sie alle Nutzerdaten. \n6.2. Führen sie flash des System-Images aus. \n \n7. Starten sie ihr Gerät neu.\n";
    GtkWidget *label_flash_gsi = gtk_label_new(flash_gsi_text);
    gtk_container_add(GTK_CONTAINER(frame20), label_flash_gsi);


    // Add frames to the main window
    gtk_box_pack_start(GTK_BOX(vbox), frame18, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame19, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame20, TRUE, TRUE, 5);

    // Show all elements
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}
