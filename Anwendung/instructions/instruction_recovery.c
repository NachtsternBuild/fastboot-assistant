/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_recovery	 *
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

void instruction_recovery(int argc, char *argv[]) 
{
    // Initiate GTK
    gtk_init(&argc, &argv);

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Anleitung Recovery");
    gtk_widget_set_size_request(window, 1000, 950);

    // Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Vertical box layout for the frames
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    // show-text
    GtkWidget *inst15_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst15_label), "<b><u>Recovery</u></b>");
    gtk_box_pack_start(GTK_BOX(vbox), inst15_label, FALSE, FALSE, 5);

    // Creation of text labels with the text to be displayed
    const char *recovery_text = "\nDer Recovery-Modus ist ein spezielles Boot-Menü auf Android-Geräten, \ndas zur Wartung und Wiederherstellung des Systems dient. \nEr ermöglicht Funktionen wie \ndas Zurücksetzen auf Werkseinstellungen, \ndas Installieren von Updates, das Löschen des Cache-Speichers \nund einige andere Grundfunktionen \num das System wiederherzustellen. \nDie vom Hersteller vorinstallierten Recoverys, \nhaben meist nur eine Grundausstattung an Funktionen an Bord. \nCustom-Recoverys bringen viel mehr Funktionen mit, \ndie weit über die Grundausstattung hinausgehen.\n";
    GtkWidget *label_recovery = gtk_label_new(recovery_text);
    gtk_box_pack_start(GTK_BOX(vbox), label_recovery, TRUE, TRUE, 5);
    
    // show-text
    GtkWidget *inst16_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst16_label), "<b><u>Flashen des Recoverys</u></b>");
    gtk_box_pack_start(GTK_BOX(vbox), inst16_label, FALSE, FALSE, 5);

    const char *flash_recovery_text = "\n1. Prüfen Sie, ob es für Ihr Gerät einen Custom-Recovery gibt. \n2. Laden Sie einen entsprechenden Recovery herunter. \n3. Bereiten Sie die Images für den Flash vor.\n4. Booten Sie Ihr Gerät in den Fastboot-Modus. \n5. Öffnen Sie den Bootloader. \nManche Geräte unterstützen nicht \ndie Methode über Fastboot. \nInformieren Sie sich genauer über Ihren Chipsatz und das Gerät. \n6. Flashen Sie das Recovery-Image. \n7. Lassen Sie Ihr Gerät in den Recovery booten.\n";
    GtkWidget *label_flash_recovery = gtk_label_new(flash_recovery_text);
    gtk_box_pack_start(GTK_BOX(vbox), label_flash_recovery, TRUE, TRUE, 5);

    // Show all elements
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}
