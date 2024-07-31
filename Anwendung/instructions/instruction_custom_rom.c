/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_custom_rom	 *
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

void instruction_custom_rom(int argc, char *argv[]) 
{
    // Initiate GTK
    gtk_init(&argc, &argv);

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Anleitung Custom ROMs");
    gtk_widget_set_size_request(window, 500, 400);

    // Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Vertical box layout for the frames
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // show-text for Custom ROMs title
    GtkWidget *inst13_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst13_label), "<b><u>Custom ROMs</u></b>");
    gtk_box_pack_start(GTK_BOX(vbox), inst13_label, FALSE, FALSE, 5);

    // Frame and label for Custom ROMs description
    GtkWidget *frame21 = gtk_frame_new(NULL);
    GtkWidget *label_custom_rom = gtk_label_new("\nCustom-ROMs sind modifizierte Versionen \ndes Android, die von unabhängigen Entwicklern erstellt werden, \num zusätzliche Funktionen, \nLeistungsverbesserungen oder eine andere Benutzeroberfläche zu bieten. \nSie ersetzen das vorinstallierte Betriebssystem \nauf einem Android-Gerät und enthalten oft \nneuere Softwareversionen oder spezielle Anpassungen, \ndie der Hersteller nicht anbietet.\n");
    gtk_container_add(GTK_CONTAINER(frame21), label_custom_rom);
    gtk_box_pack_start(GTK_BOX(vbox), frame21, TRUE, TRUE, 5);

    // show-text for Flashing Custom ROMs title
    GtkWidget *inst14_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst14_label), "<b><u>Flashen von Custom-ROMs</u></b>");
    gtk_box_pack_start(GTK_BOX(vbox), inst14_label, FALSE, FALSE, 5);

    // Frame and label for Flashing Custom ROMs steps
    GtkWidget *frame22 = gtk_frame_new(NULL);
    GtkWidget *label_flash_custom_rom = gtk_label_new("\n1. Prüfen sie ob es für ihr Gerät Custom-Roms gibt und laden sie es herunter. \n2. Booten sie ihr Gerät in den Fastboot-Modus. \n3. Öffnen sie den Bootloader. \nManche Geräte unterstützen nicht \ndie Methode über Fastboot. \nInformieren sie sich genauer \nüber ihr Chipssatz und das Gerät. \n \n4. Flashen sie den Custom-Recovery, das Boot-Image und dtbo.img. \n5. Führen sie einen Neustart in den Recovery aus. \n6. Kopieren sie das Zip des Custom-ROMs auf ihr Gerät.\n7. Tippen sie installieren und flashen sie das Zip. \nOptional kann jetzt noch ein Magisk.zip, \nzum rooten des Gerätes geflasht werden \noder falls nicht im Custom-ROM enthalten, \ndie Google-Dienste. \n8. Starten sie ihr Gerät neu.\n");
    gtk_container_add(GTK_CONTAINER(frame22), label_flash_custom_rom);
    gtk_box_pack_start(GTK_BOX(vbox), frame22, TRUE, TRUE, 5);

    // Show all elements
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}
