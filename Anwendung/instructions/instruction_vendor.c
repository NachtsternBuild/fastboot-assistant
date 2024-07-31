/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_vendor		 *
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

void instruction_vendor(int argc, char *argv[]) 
{
    // Initiate GTK
    gtk_init(&argc, &argv);

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Anleitung und Info Vendor");
    gtk_widget_set_size_request(window, 1000, 950);

    // Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create vertical box layout for the frames
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    // Vendor Native Development Kit (VNDK) header
    GtkWidget *inst9_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst9_label), "<b><u>Vendor Native Development Kit (VNDK)</u></b>");
    gtk_box_pack_start(GTK_BOX(vbox), inst9_label, FALSE, FALSE, 5);

    // Description about VNDK
    const char *vndk_text = "\nAlles was mit 'Vendor' bezeichnet wird, \nstellen hersteller- oder \ngerätspezifische Komponenten des Betriebssystems da. \nÄnderungen daran sind mit äußerster Vorsicht zu betrachten.\n \nDie VNDK-Version (Vendor Native Development Kit) \nstellt eine Sammlung von Bibliotheken und Richtlinien dar, \ndie es ermöglichen, den hardware-spezifischen Teil \neines Android-Systems von \ngenerischen Systemimplementierungen zu trennen. \nDadurch lassen sich Updates und Wartung erleichtern, \nindem sichergestellt wird, dass herstellerspezifische \nAnpassungen nicht die Kompatibilität und Stabilität \ndes Android-Betriebssystems beeinträchtigen.\n";
    GtkWidget *label_vndk = gtk_label_new(vndk_text);
    gtk_box_pack_start(GTK_BOX(vbox), label_vndk, TRUE, TRUE, 5);

    // Show all elements
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}

