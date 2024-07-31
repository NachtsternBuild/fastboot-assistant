/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_preflash	 *
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

void instruction_preflash(int argc, char *argv[]) 
{
    // Initiate GTK
    gtk_init(&argc, &argv);

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Anleitung Vorbereitungen flash");
    gtk_widget_set_size_request(window, 1000, 950);

    // Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Vertical box layout for the frames
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Creation of text labels with the text to be displayed
    const char *preflash_text = "\n1. Informieren sie genauer über \nihr Gerät und den Chipsatz ihres Gerätes. \n2. Suchen sie nach entsprechenden \nCustom-ROMs, Custom-Recoverys oder GSIs. \n3. Prüfen sie die Verfügbarkeit von Project Treble für ihr Gerät. \n4. Prüfen sie welches Partitionierungsschema \nauf ihrem Gerät vorliegt (a/b-devices oder only-a-devices).\n5. Sichern sie ihre Daten lokal und wenn sie wollen in einer Cloud. \n6. Laden sie alle Dateien herunter die für das Custom-ROM \noder GSI gebraucht werden und lesen sie die Anleitungen \nder Entwickler der Custom-ROMs vor dem Flash. \n7. Benennen sie alle Dateien der folgenden Liste nach um. \nEs gibt eine Funktion, die das übernimmt, \naber es ist nicht garantiert, dass es funktioniert. \n8. Kopieren sie alle Dateien \ndie geflasht werden sollen in das Verzeichnis:\n \n'~/Downloads/ROM-Install/'\n";
    GtkWidget *label_preflash = gtk_label_new(preflash_text);
    gtk_box_pack_start(GTK_BOX(vbox), label_preflash, TRUE, TRUE, 5);
    
    // show-text for list of all file names that are flashed
    GtkWidget *inst17_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst17_label), "<b><u>Liste aller Dateien</u></b>");
    gtk_box_pack_start(GTK_BOX(vbox), inst17_label, FALSE, FALSE, 5);

    // Creation of text labels with the text to be displayed
    const char *file_list_text = "\n- preloader.bin \n- preloader.img \n- super.img \n- recovery.img \n- boot.img \n- init_boot.img \n- vendor_boot.img \n- vendor.img \n- system.img \n- vbmeta.img \n- dtbo.img \n- metadata.img \n- userdata.img \n- payload.zip (das ist die Zip-Datei eines jeden Custom-ROMs)\n";
    GtkWidget *label_file_list = gtk_label_new(file_list_text);
    gtk_box_pack_start(GTK_BOX(vbox), label_file_list, TRUE, TRUE, 5);

    // show-text for some interesting links
    GtkWidget *inst18_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst18_label), "<b><u>Einige Custom-ROMs und Recoverys</u></b>");
    gtk_box_pack_start(GTK_BOX(vbox), inst18_label, FALSE, FALSE, 5);
    
    GtkWidget *inst19_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst19_label), "<b>TWRP:</b> https://www.twrp.me/\n");
    gtk_box_pack_start(GTK_BOX(vbox), inst19_label, FALSE, FALSE, 5);

    GtkWidget *inst20_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst20_label), "<b>/e/ OS:</b> https://e.foundation/e-os/\n");
    gtk_box_pack_start(GTK_BOX(vbox), inst20_label, FALSE, FALSE, 5);

    GtkWidget *inst21_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst21_label), "<b>LineageOS:</b> https://lineageos.org/\n");
    gtk_box_pack_start(GTK_BOX(vbox), inst21_label, FALSE, FALSE, 5);

    GtkWidget *inst22_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst22_label), "<b>Project Elixir:</b> https://projectelixiros.com/home\n");
    gtk_box_pack_start(GTK_BOX(vbox), inst22_label, FALSE, FALSE, 5);

    GtkWidget *inst23_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst23_label), "<b>crDroid:</b> https://crdroid.net/\n");
    gtk_box_pack_start(GTK_BOX(vbox), inst23_label, FALSE, FALSE, 5);

    GtkWidget *inst24_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst24_label), "<b>Evolution X:</b> https://sourceforge.net/projects/evolution-x/\n");
    gtk_box_pack_start(GTK_BOX(vbox), inst24_label, FALSE, FALSE, 5);
    
    // Show all elements
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}
