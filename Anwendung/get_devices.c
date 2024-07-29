/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - get_devices			 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// i think that can be a header
// function to get adb/fastboot info
void search_for_device(char *adb_device, char *fastboot_device)
{
	// get device that connected via adb
	strcpy(adb_device, execute_command("adb devices"));
	
	// get device thet connectet via fastboot
	strcpy(fastboot_device, execute_command("fastboot devices"));
}

// create function that display the info
void get_devices(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	
	//strings for system-info
	char adb_device[255];
	char fastboot_device[255];
	
	// get infos
	search_for_device(adb_device, fastboot_device);
	
	// create gtk-main windows
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Info");
    gtk_widget_set_size_request(window, 700, 600);

    // connect the 'destroy'-function
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // frame at the box
    GtkWidget *frame = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(window), frame);

    // create vbox
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(frame), vbox);
    
    // show-text
    GtkWidget *get_device1_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(get_device1_label), g_strdup_printf("<b><u> Geräte mit ADB verbunden: </u></b>"));
    gtk_container_add(GTK_CONTAINER(vbox), get_device1_label);

    // adb-label
    GtkWidget *adb_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(adb_label), g_strdup_printf("<b>Geräte: </b> %s", adb_device));
    gtk_container_add(GTK_CONTAINER(vbox), adb_label);
    
    // show text 2
    GtkWidget *get_device2_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(get_device2_label), g_strdup_printf("<b><u> Geräte via Fastboot verbunden: </u></b>"));
    gtk_container_add(GTK_CONTAINER(vbox), get_device2_label);
    
    // fastboot-label
    GtkWidget *fastboot_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(fastboot_label), g_strdup_printf("<b>Geräte: </b> %s", fastboot_device));
    gtk_container_add(GTK_CONTAINER(vbox), fastboot_label);
    
    // show all elements
    gtk_widget_show_all(window);
    
    // GTK-mainloop start
    gtk_main();
}    
