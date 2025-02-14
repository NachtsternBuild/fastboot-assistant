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
 *      (C) Copyright 2025 Elias Mörz        *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "function_header.h"
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

// function for start the updater
void run_updater(GtkWidget *widget, gpointer data)
{
	updater();
}

// function that output version infos about the system and installed packages
void run_tools_info(GtkWidget *widget, gpointer data)
{
	info_tools();
}

// the main function
void about(int argc, char *argv[]) 
{
    LOG_INFO("about");
    
    // GTK init
    gtk_init();
    main_loop = g_main_loop_new(NULL, FALSE);

    apply_theme();
    apply_language();
    
    GtkWidget *window, *notebook;
    GtkWidget *page1, *page2, *page3;
    GtkWidget *label_about2;
    GtkWidget *button_about_1, *button_about_2, *button_about_3, *button_about_4, *button_about_5, *button_about_6, *button_about2_1, *button_about2_2, *button_about2_3, *button_about2_4, *button_about2_5, *button_about3_1, *button_about3_2, *button_about3_3, *button_about3_4, *button_about3_5, *button_about3_6;
    
    // create the main window
    window = gtk_window_new();
    const char *about_window = strcmp(language, "de") == 0 ? "Über das Programm" : "About the program";
    gtk_window_set_title(GTK_WINDOW(window), about_window);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
	g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);

    // create the notebook
    notebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // page 1
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    button_about_1 = gtk_button_new_with_label("Fastboot Assistant");
    button_about_2 = gtk_button_new_with_label("Version 0.7.2.dev");
    button_about_3 = gtk_button_new_with_label("Mutiges Mint 20.3");
    button_about_4 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Programm um das installieren von Custom-ROM \nund GSIs auf Android-Geräte zu erleichtern." : "Program to facilitate the installation of custom ROM \nand GSIs on Android devices.");
    button_about_5 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Aktualisierungen" : "Updates");
    button_about_6 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_about_1);
    gtk_box_append(GTK_BOX(page1), button_about_2);
    gtk_box_append(GTK_BOX(page1), button_about_3);
    gtk_box_append(GTK_BOX(page1), button_about_4);
    gtk_box_append(GTK_BOX(page1), button_about_5);
    gtk_box_append(GTK_BOX(page1), button_about_6);

    // connect everything
    g_signal_connect(button_about_5, "clicked", G_CALLBACK(run_updater), notebook);
    g_signal_connect(button_about_6, "clicked", G_CALLBACK(next_page), notebook);
    
    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, gtk_label_new("Version"));
    
    // page 2
    page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    button_about2_1 = gtk_button_new_with_label("(C) Copyright 2025 Elias Mörz");
    button_about2_2 = gtk_button_new_with_label("Apache License, Version 2.0");
    button_about2_3 = gtk_button_new_with_label("https://github.com/NachtsternBuild/fastboot-assistant");
    label_about2 = gtk_button_new_with_label("thanks to:\n@mrrfv → Open Android Backup\n@Jean28518 → my build-fastboot-assistant.sh \nbased on his build-scripts for DEB.");
    button_about2_4 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "System- und Paketinformationen" : "System and package information");
    button_about2_5 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_about2_1);
    gtk_box_append(GTK_BOX(page2), button_about2_2);
    gtk_box_append(GTK_BOX(page2), button_about2_3);
    gtk_box_append(GTK_BOX(page2), label_about2);
    gtk_box_append(GTK_BOX(page2), button_about2_4);
    gtk_box_append(GTK_BOX(page2), button_about2_5);

    // connect everything
    g_signal_connect(button_about2_4, "clicked", G_CALLBACK(info_tools), notebook);
    g_signal_connect(button_about2_5, "clicked", G_CALLBACK(next_page), notebook);   
    
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
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page3, gtk_label_new(g_strcmp0(language, "de") == 0 ? "Hinweise" : "Notes"));
    
    // show all widgets
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop); 
    
    // free the provider
    if (provider != NULL) 
    {
    	g_object_unref(provider);
    	provider = NULL;
	}

	if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
    
    LOG_INFO("end about");
}
