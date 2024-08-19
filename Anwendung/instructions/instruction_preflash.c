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

// function to open the GitHub website from the fastboot-assistant
void twrp(GtkWidget *widget, gpointer data)
{
    const char *twrp_url = "https://www.twrp.me/";
    
	open_url(twrp_url);
}

// function that open the GitHub Releases page
void e_OS(GtkWidget *widget, gpointer data)
{
    const char *e_OS_url = "https://e.foundation/e-os/";
	open_url(e_OS_url);
}

// function to open the website that used for the feedback for the fastboot-assistant
void lineage_os(GtkWidget *widget, gpointer data)
{
    const char *lineage_os_url = "https://lineageos.org/";
	open_url(lineage_os);
}

// function to open the website from 'Open Android Backup'
void project_elixir(GtkWidget *widget, gpointer data)
{
    const char *project_elixir_url = "https://projectelixiros.com/home";
	open_url(project_elixir_url);
}

// function to open the website from 'Open Android Backup'
void crdroid(GtkWidget *widget, gpointer data)
{
    const char *crdroid_url = "https://crdroid.net/";
	open_url(crdroid_url);
}

// function to open the website from 'Open Android Backup'
void evolution_x(GtkWidget *widget, gpointer data)
{
    const char *evolution_x_url = "https://sourceforge.net/projects/evolution-x/";
	open_url(evolution_x_url);
}

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
    
    // Create button box for the buttons
    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), button_box, FALSE, FALSE, 10);
    
    GtkWidget *button_twrp = gtk_button_new_with_label("TWRP");
    g_signal_connect(button_twrp, "clicked", G_CALLBACK(twrp), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), button_twrp, TRUE, TRUE, 10);
    
    GtkWidget *button_e_OS = gtk_button_new_with_label("/e/ OS");
    g_signal_connect(button_e_OS, "clicked", G_CALLBACK(e_OS), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), button_e_OS, TRUE, TRUE, 10);
    
    GtkWidget *button_lineage_os = gtk_button_new_with_label("LineageOS");
    g_signal_connect(button_lineage_os, "clicked", G_CALLBACK(lineage_os), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), button_lineage_os, TRUE, TRUE, 10);
    
    GtkWidget *button_project_elixir = gtk_button_new_with_label("Project Elixir");
    g_signal_connect(button_project_elixir, "clicked", G_CALLBACK(project_elixir), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), button_project_elixir, TRUE, TRUE, 10);
    
    GtkWidget *button_crdroid = gtk_button_new_with_label("crDroid");
    g_signal_connect(button_crdroid, "clicked", G_CALLBACK(crdroid), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), button_crdroid, TRUE, TRUE, 10);
    
    GtkWidget *button_evolution_x = gtk_button_new_with_label("Evolution X");
    g_signal_connect(button_evolution_x, "clicked", G_CALLBACK(evolution_x), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), button_evolution_x, TRUE, TRUE, 10);
    
    // Show all elements
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}


