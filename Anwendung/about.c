/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *          Apache License, Version 2.0      *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von         *
 *  Custom-ROM und GSIs auf Android-Geräte   *
 *  zu erleichtern - about                   *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz        *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

#define MAX_BUFFER_SIZE 256

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

// function to open the dokumentation of the fastboot-assistant
void dokumentation(GtkWidget *widget, gpointer data)
{
    const char *feedback_url = "https://github.com/NachtsternBuild/fastboot-assistant/wiki";
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

// the main function
void about(int argc, char *argv[]) 
{
    g_print("Log: about\n");
    
    // GTK init
    gtk_init();

    apply_theme();
    apply_language();
    
    GtkWidget *window;
    GtkWidget *page_about1, *page_about2, *page_about3;
    GtkWidget *label_about2;
    GtkWidget *button_about_1, *button_about_2, *button_about_3, *button_about_4, *button_about_5, *button_about2_1, *button_about2_2, *button_about2_3, *button_about2_4, *button_about3_1, *button_about3_2, *button_about3_3, *button_about3_4, *button_about3_5, *button_about3_6;
    
    // create the main window
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Über das Programm");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);

    // create the notebook
    notebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // page 1
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    button_about_1 = gtk_button_new_with_label("Fastboot Assistant");
    button_about_2 = gtk_button_new_with_label("Version 0.6.2.dev");
    button_about_3 = gtk_button_new_with_label("Rostiges Red Hat");
    button_about_4 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Programm um das installieren von Custom-ROM \nund GSIs auf Android-Geräte zu erleichtern." : "Program to facilitate the installation of custom ROM \nand GSIs on Android devices.");
    button_about_5 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_about_1);
    gtk_box_append(GTK_BOX(page1), button_about_2);
    gtk_box_append(GTK_BOX(page1), button_about_3);
    gtk_box_append(GTK_BOX(page1), button_about_4);
    gtk_box_append(GTK_BOX(page1), button_about_5);

    // connect everything
    g_signal_connect(button_about_5, "clicked", G_CALLBACK(next_page), notebook);
    
    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, gtk_label_new("Version"));
    
    // page 2
    page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    button_about2_1 = gtk_button_new_with_label("(C) Copyright 2024 Elias Mörz");
    button_about2_2 = gtk_button_new_with_label("Apache License, Version 2.0");
    button_about2_3 = gtk_button_new_with_label("https://github.com/NachtsternBuild/fastboot-assistant");
    label_about2 = gtk_button_new_with_label("thanks to:\n@mrrfv → Open Android Backup\n@Jean28518 → my build-fastboot-assistant.sh \nbased on his build-scripts.");
    button_about2_4 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_about2_1);
    gtk_box_append(GTK_BOX(page2), button_about2_2);
    gtk_box_append(GTK_BOX(page2), button_about2_3);
    gtk_box_append(GTK_BOX(page2), label_about2);
    gtk_box_append(GTK_BOX(page2), button_about2_4);

    // connect everything
    g_signal_connect(button_about2_4, "clicked", G_CALLBACK(next_page), notebook);   
    
    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page2, gtk_label_new(g_strcmp0(language, "de") == 0 ? "Das Programm" : "The program"));
    
    // page 3
    page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    button_about3_1 = gtk_button_new_with_label("GitHub Seite");
	button_about3_2 = gtk_button_new_with_label("Versionen");
	button_about3_3 = gtk_button_new_with_label("Feedback");
	button_about3_4 = gtk_button_new_with_label("Dokumentation");
	button_about3_5 = gtk_button_new_with_label("Open Android Backup");
	button_about3_6 = gtk_button_new_with_label("Jean28518 GitHub");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page3), button_about3_1);
    gtk_box_append(GTK_BOX(page3), button_about3_2);
    gtk_box_append(GTK_BOX(page3), button_about3_3);
    gtk_box_append(GTK_BOX(page3), button_about3_4);
    gtk_box_append(GTK_BOX(page3), button_about3_5);
    gtk_box_append(GTK_BOX(page3), button_about3_6);
    
    // connect everything
    g_signal_connect(button_about3_1, "clicked", G_CALLBACK(fastboot_assistant), notebook);
    g_signal_connect(button_about3_2, "clicked", G_CALLBACK(fastboot_assistant_release), notebook);
    g_signal_connect(button_about3_3, "clicked", G_CALLBACK(feedback), notebook);
    g_signal_connect(button_about3_4, "clicked", G_CALLBACK(dokumentation), notebook);
    g_signal_connect(button_about3_5, "clicked", G_CALLBACK(open_android_backup), notebook);
    g_signal_connect(button_about3_6, "clicked", G_CALLBACK(brownie_jean), notebook);
    
    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page2, gtk_label_new(g_strcmp0(language, "de") == 0 ? "Hinweise" : "Notes"));
    
    // show all widgets
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop); 
    
    g_print("Log: end about\n");
}
