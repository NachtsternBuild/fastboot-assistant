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
    GtkWidget *frame7 = gtk_frame_new(NULL);
    
    // Vertical box layout for the frames
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Creation of text labels with the text to be displayed
    const char *name_text = "\nProjekt 122\n";
    GtkWidget *label_name = gtk_label_new(name_text);
    gtk_container_add(GTK_CONTAINER(frame1), label_name);

    const char *licence_text = "\nApache License, Version 2.0\n";
    GtkWidget *label_licence = gtk_label_new(licence_text);
    gtk_container_add(GTK_CONTAINER(frame2), label_licence);

    const char *information_text = "\nProgramm um das installieren von Custom-ROM und GSIs\n "
                                "auf Android-Geräte zu erleichtern.\n";
    GtkWidget *label_information = gtk_label_new(information_text);
    gtk_container_add(GTK_CONTAINER(frame3), label_information);

    const char *copyright_text = "\n(C) Copyright 2023 Elias Mörz\n";
    GtkWidget *label_copyright = gtk_label_new(copyright_text);
    gtk_container_add(GTK_CONTAINER(frame4), label_copyright);
    
    const char *github_text = "\nhttps://github.com/NachtsternBuild/Projekt-122\n";
    GtkWidget *label_github = gtk_label_new(github_text);
    gtk_container_add(GTK_CONTAINER(frame5), label_github);

    const char *build_version_text = "\nVersion 0.5.dev\n";
    GtkWidget *label_build_version = gtk_label_new(build_version_text);
    gtk_container_add(GTK_CONTAINER(frame6), label_build_version);

    const char *build_name_text = "\n'Sweet Unix'\n";
    GtkWidget *label_build_name = gtk_label_new(build_name_text);
    gtk_container_add(GTK_CONTAINER(frame7), label_build_name);

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
