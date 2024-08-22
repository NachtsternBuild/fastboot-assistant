#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include "program_functions.h"

// function to open the GitHub website from the fastboot-assistant
void fastboot_assistant(GtkWidget *widget, gpointer data)
{
    const char *git_url = "https://github.com/NachtsternBuild/fastboot-assistant";
    
	open_url(git_url);
}

// function that open the GitHub Releases page
void fastboot_assistant_release(GtkWidget *widget, gpointer data)
{
    const char *release_url = "https://github.com/NachtsternBuild/fastboot-assistant/releases";
	open_url(release_url);
}

// function to open the website that used for the feedback for the fastboot-assistant
void feedback(GtkWidget *widget, gpointer data)
{
    const char *feedback_url = "https://forms.gle/dBWBawwqNgFWCLz58";
	open_url(feedback_url);
}

// function to open the website from 'Open Android Backup'
void open_android_backup(GtkWidget *widget, gpointer data)
{
    const char *open_android_backup_url = "https://github.com/mrrfv/open-android-backup";
	open_url(open_android_backup_url);
}

// function to open the website from 'Open Android Backup'
void brownie_jean(GtkWidget *widget, gpointer data)
{
    const char *brownie_jean_url = "https://github.com/Jean28518";
	open_url(brownie_jean_url);
}

void about(int argc, char *argv[]) 
{
    // Initiate GTK
    gtk_init(&argc, &argv);

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Über das Programm");
    gtk_widget_set_size_request(window, 700, 650);

    // Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Frame for each information field
    GtkWidget *frame1 = gtk_frame_new(NULL);
    GtkWidget *frame2 = gtk_frame_new(NULL);
    GtkWidget *frame3 = gtk_frame_new(NULL);
    GtkWidget *frame4 = gtk_frame_new(NULL);
    GtkWidget *frame5 = gtk_frame_new(NULL);
    GtkWidget *frame6 = gtk_frame_new(NULL);
    GtkWidget *frame7 = gtk_frame_new(NULL);
    GtkWidget *frame8 = gtk_frame_new(NULL);
    
    // Vertical box layout for the frames
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Creation of text labels with the text to be displayed
    const char *name_text = "\nFastboot Assistant\n";
    GtkWidget *label_name = gtk_label_new(name_text);
    gtk_container_add(GTK_CONTAINER(frame1), label_name);

    const char *licence_text = "Apache License, Version 2.0";
    GtkWidget *label_licence = gtk_label_new(licence_text);
    gtk_container_add(GTK_CONTAINER(frame2), label_licence);

    const char *information_text = "\nProgramm um das installieren von Custom-ROM und GSIs\n "
                                "auf Android-Geräte zu erleichtern.\n";
    GtkWidget *label_information = gtk_label_new(information_text);
    gtk_container_add(GTK_CONTAINER(frame3), label_information);

    const char *copyright_text = "(C) Copyright 2024 Elias Mörz";
    GtkWidget *label_copyright = gtk_label_new(copyright_text);
    gtk_container_add(GTK_CONTAINER(frame4), label_copyright);
    
    const char *github_text = "https://github.com/NachtsternBuild/fastboot-assistant";
    GtkWidget *label_github = gtk_label_new(github_text);
    gtk_container_add(GTK_CONTAINER(frame5), label_github);

    const char *build_version_text = "\nVersion 0.5.4.beta\n";
    GtkWidget *label_build_version = gtk_label_new(build_version_text);
    gtk_container_add(GTK_CONTAINER(frame6), label_build_version);

    const char *build_name_text = "\nSweet Unix\n";
    GtkWidget *label_build_name = gtk_label_new(build_name_text);
    gtk_container_add(GTK_CONTAINER(frame7), label_build_name);
    
    const char *brownies_text = "\nthanks to:\n@mrrfv → Open Android Backup\n@Jean28518 → my build-fastboot-assistant.sh \nis a modified version.\n";
    GtkWidget *label_brownies = gtk_label_new(brownies_text);
    gtk_container_add(GTK_CONTAINER(frame8), label_brownies);

    // Add frames to the main window
    gtk_box_pack_start(GTK_BOX(vbox), frame1, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame2, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame3, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame4, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame5, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame6, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame7, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), frame8, TRUE, TRUE, 5);

    // Create button box for the buttons
    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), button_box, FALSE, FALSE, 10);

    // Create and add buttons to the button box
    // the button for the website of 'Open Android Backup'
    GtkWidget *button_open_android_backup = gtk_button_new_with_label("Open Android Backup");
    g_signal_connect(button_open_android_backup, "clicked", G_CALLBACK(open_android_backup), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), button_open_android_backup, TRUE, TRUE, 10);
    
    // the button for the GitHub website
    GtkWidget *button_fastboot_assistant = gtk_button_new_with_label("GitHub Seite");
    g_signal_connect(button_fastboot_assistant, "clicked", G_CALLBACK(fastboot_assistant), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), button_fastboot_assistant, TRUE, TRUE, 10);
    
    // the buttom for the release website
    GtkWidget *button_fastboot_assistant_release = gtk_button_new_with_label("Versionen");
    g_signal_connect(button_fastboot_assistant_release, "clicked", G_CALLBACK(fastboot_assistant_release), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), button_fastboot_assistant_release, TRUE, TRUE, 10);

    // the button for the feedback website
    GtkWidget *button_feedback = gtk_button_new_with_label("Feedback");
    g_signal_connect(button_feedback, "clicked", G_CALLBACK(feedback), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), button_feedback, TRUE, TRUE, 10);
    
    // the button for @jean28518 GitHub page 
    GtkWidget *button_brownie_jean = gtk_button_new_with_label("Jean28518 GitHub");
    g_signal_connect(button_brownie_jean, "clicked", G_CALLBACK(brownie_jean), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), button_brownie_jean, TRUE, TRUE, 10);

    // Show all elements
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}

