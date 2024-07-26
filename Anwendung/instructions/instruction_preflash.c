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
    GtkWidget *frame26 = gtk_frame_new(NULL);
    
    // Vertical box layout for the frames
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Creation of text labels with the text to be displayed
    const char *preflash_text = "\n1. Informieren sie genauer über \nihr Gerät und den Chipsatz ihres Gerätes. \n2. Suchen sie nach entsprechenden \nCustom-ROMs, Custom-Recoverys oder GSIs. \n3. Prüfen sie die Verfügbarkeit von Project Treble für ihr Gerät. \n4. Prüfen sie welche Partitionierungsschema \nauf ihrem Gerät vorliegt (a/b-devices oder only-a-devices).\n5.Sichern sie ihr Daten lokal und wenn sie wollen in einer Cloud. \n6. Laden sie alle Dateien herunter die für das Custom-ROM \noder GSI gebraucht werden und lesen sie die Anleitungen \nder Entwickler der Custom-ROMs vor dem flash. \n7. Benennen sie alle Dateien der folgenden Liste nach um. \nEs gibt ein Funktion, die das übernimmt, \naber es ist nicht garantiert, dass es funktioniert. \n8. Kopieren sie alle Dateien \ndie geflasht werden sollen in das Verzeichnis:\n \n'~/Downlaods/ROM-Install/'\n";
    GtkWidget *label_preflash = gtk_label_new(preflash_text);
    gtk_container_add(GTK_CONTAINER(frame26), label_preflash);
    
    // list of all file names that are flashed
    // show-text
    GtkWidget *inst17_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst17_label), g_strdup_printf("<b><u> Liste aller Dateien </u></b>"));
    gtk_container_add(GTK_CONTAINER(vbox), inst17_label);
    
    // Creation of text labels with the text to be displayed
    const char *file_list_text = "\n- preloader.bin \n- preloader.img \n-super.img \n- recovery.img \n- boot.img \n- init_boot.img \n- vendor_boot.img \n- vendor.img \n- system.img \n- vbmeta.img \n- dtbo.img \n- metadata.img \n- userdata.img \n- payload.zip (das ist die Zip-Datei eines jeden Custom-ROMs)\n";
    GtkWidget *label_file_list = gtk_label_new(file_list_text);
    gtk_container_add(GTK_CONTAINER(frame27), label_file_list);
    // end of the list
    // list with some interesting links
    GtkWidget *inst18_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst18_label), g_strdup_printf("<b><u> Einige Custom-ROMs und Recoverys </u></b>"));
    gtk_container_add(GTK_CONTAINER(vbox), inst18_label);
    
    GtkWidget *inst19_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst19_label), g_strdup_printf("<b>TWRP: </b> \nhttps://www.twrp.me/\n"));
    gtk_container_add(GTK_CONTAINER(vbox), inst17_label);
    
    GtkWidget *inst20_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst20_label), g_strdup_printf("<b>/e/ OS: </b> \nhttps://e.foundation/e-os/\n"));
    gtk_container_add(GTK_CONTAINER(vbox), inst20_label);
    
    GtkWidget *inst21_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst21_label), g_strdup_printf("<b>LineageOS: </b> \nhttps://lineageos.org/\n"));
    gtk_container_add(GTK_CONTAINER(vbox), inst21_label);
    
     GtkWidget *inst22_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst22_label), g_strdup_printf("<b>Project Elixir: </b> \nhttps://projectelixiros.com/home\n"));
    gtk_container_add(GTK_CONTAINER(vbox), inst22_label);
    
     GtkWidget *inst23_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst23_label), g_strdup_printf("<b>crDroid: </b> \nhttps://crdroid.net/\n"));
    gtk_container_add(GTK_CONTAINER(vbox), inst23_label);
    
     GtkWidget *inst24_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(inst24_label), g_strdup_printf("<b>Evolution X: </b> \nhttps://sourceforge.net/projects/evolution-x/\n"));
    gtk_container_add(GTK_CONTAINER(vbox), inst24_label);
    // end of the list
    
    // Add frames to the main window
    gtk_box_pack_start(GTK_BOX(vbox), frame26, TRUE, TRUE, 5);

    // Show all elements
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}
