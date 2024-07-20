/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              about						 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h> 
#include <gtk/gtk.h>

void about(int argc, char *argv[]) 
{
    // Initiate GTK
    gtk_init(&argc, &argv);

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Über das Programm");
    gtk_widget_set_size_request(window, 500, 400);

    // Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_close), NULL);

    // Frame for each information field
    GtkWidget *frame1 = gtk_frame_new(NULL);
    GtkWidget *frame2 = gtk_frame_new(NULL);
    GtkWidget *frame3 = gtk_frame_new(NULL);
    GtkWidget *frame4 = gtk_frame_new(NULL);
    GtkWidget *frame5 = gtk_frame_new(NULL);
    GtkWidget *frame6 = gtk_frame_new(NULL);
    
    // Vertical box layout for the frames
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Creation of text labels with the text to be displayed
    const char *tab_text = "\nProjekt 122\n";
    GtkWidget *label_tab = gtk_label_new(tab_text);
    gtk_container_add(GTK_CONTAINER(frame1), label_tab);

    const char *name_text = "\nApache License, Version 2.0\n";
    GtkWidget *label_name = gtk_label_new(name_text);
    gtk_container_add(GTK_CONTAINER(frame2), label_name);

    const char *version_text = "\nProgramm um das installieren von Custom-ROM und GSIs\n "
                                "auf Android-Geräte zu erleichtern.\n";
    GtkWidget *label_version = gtk_label_new(version_text);
    gtk_container_add(GTK_CONTAINER(frame3), label_version);

    const char *description_text = "\n(C) Copyright 2023 Elias Mörz\n";
    GtkWidget *label_description = gtk_label_new(description_text);
    gtk_container_add(GTK_CONTAINER(frame4), label_description);
    
    const char *description_text = "\nhttps://github.com/NachtsternBuild/Projekt-122\n";
    GtkWidget *label_description = gtk_label_new(description_text);
    gtk_container_add(GTK_CONTAINER(frame5), label_description);

    const char *build_text = "\nVersion 0.5.\n";
    GtkWidget *label_build = gtk_label_new(build_text);
    gtk_container_add(GTK_CONTAINER(frame6), label_build);

    const char *architecture_text = "\n'Sweet Unix'\n";
    GtkWidget *label_architecture = gtk_label_new(architecture_text);
    gtk_container_add(GTK_CONTAINER(frame7), label_architecture);

    // Add frames to the main window
    gtk_box_pack_start(GTK_BOX(vbox), frame1, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame2, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame3, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame4, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame5, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame6, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame7, TRUE, TRUE, 5);

    // Show all elements
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}
