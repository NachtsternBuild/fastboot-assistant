/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_info		 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

// add unlock bootloader

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

void instruction_info(int argc, char *argv[]) 
{
    // Initiate GTK
    gtk_init(&argc, &argv);

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Anleitung Info");
    gtk_widget_set_size_request(window, 1000, 950);

    // Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Vertical box layout for the frames
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // show-text for more info title
    GtkWidget *inst26_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst26_label), "<b><u>Weitere Infos</u></b>");
    gtk_box_pack_start(GTK_BOX(vbox), inst26_label, FALSE, FALSE, 5);

    // Frame and label for detailed information
    GtkWidget *frame27 = gtk_frame_new(NULL);
    const char *info_text = "\nA/B Partitionsschema verwendet zwei Systempartitionen, \num nahtlose Updates zu ermöglichen, \nindem es zwischen ihnen wechselt. \nDas only-A Partitionsschema \nhat nur eine Systempartition und erfordert einen Neustart für Updates. \nA/B bietet redundante Sicherheit und ermöglicht ein \nkontinuierliches Betriebssystem, während Only-A \neinfachere Verwaltung erfordert.\n \nProject Treble ist eine Android-Initiative von Google, \ndie die Trennung von Betriebssystem- und Hardwarekomponenten ermöglicht. \nDies erleichtert Herstellern \ndie Bereitstellung von Android-Updates, \nindem das Betriebssystem unabhängig \nvon den spezifischen Treibern für den Chipsatz ist.\n \nSystem-as-root ist ein Mechanismus in Android, \nbei dem das System-Image als Root-Dateisystem gemountet wird. \nDies verbessert die Trennung von System- und Vendor-Partitionen \nund erhöht die Sicherheit. \nDies erleichtert das Aktualisieren des Systems \nund die Verwaltung von Berechtigungen, \nda systemkritische Dateien \nund Konfigurationen besser geschützt und isoliert werden.\n \nEin System on a Chip (SoC) ist ein integrierter Schaltkreis, \nder alle wesentlichen Komponenten eines Computersystems, \neinschließlich CPU, GPU, Speicher und Ein-/Ausgabeschnittstellen, \nauf einem einzigen Chip vereint. \nSoCs werden häufig verwendet, \num Platz und Energie zu sparen.\n";
    GtkWidget *label_info = gtk_label_new(info_text);
    gtk_container_add(GTK_CONTAINER(frame27), label_info);
    gtk_box_pack_start(GTK_BOX(vbox), frame27, TRUE, TRUE, 5);
    
    // show-text for Samsung devices
    GtkWidget *inst27_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst27_label), "<b><u>Für Samsung Nutzer</b></u>");
    gtk_box_pack_start(GTK_BOX(vbox), inst27_label, FALSE, FALSE, 5);
    
    // show-text for Samsung devices
    GtkWidget *inst28_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst28_label), "<b>Nutzen sie 'heimdall' statt 'fastboot' zum flashen!</b>");
    gtk_box_pack_start(GTK_BOX(vbox), inst28_label, FALSE, FALSE, 5);

    // Show all elements
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}
