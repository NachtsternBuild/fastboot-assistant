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
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 500

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
// function that print so text, but no real useage
static void about_text()
{
	g_print("Nix da!\n");
}

// the main function
void about(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *page_about1, *page_about2, *page_about3;
    GtkWidget *label_about2;
    GtkWidget *button_about_1, *button_about_2, *button_about_3, *button_about_4, *button_about_5, *button_about2_1, *button_about2_2, *button_about2_3, *button_about2_4, *button_about3_1, *button_about3_2, *button_about3_3, *button_about3_4, *button_about3_5;

    gtk_init(&argc, &argv);
    css_provider(); // load css-provider
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Über das Programm");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    
     // Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	GtkWidget *notebook = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window), notebook);
    
    if (!GTK_IS_NOTEBOOK(notebook)) 
    {
    	g_warning("Notebook is not initialized properly.");
    	return;
	}

    // page 1
    page_about1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_about_1 = gtk_button_new_with_label("Fastboot Assistant");
    button_about_2 = gtk_button_new_with_label("Version 0.5.5.beta");
    button_about_3 = gtk_button_new_with_label("Sweet Unix System V");
    button_about_4 = gtk_button_new_with_label("Programm um das installieren von Custom-ROM \nund GSIs auf Android-Geräte zu erleichtern.");
    button_about_5 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_about1), button_about_1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_about1), button_about_2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_about1), button_about_3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_about1), button_about_4, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_about1), button_about_5, FALSE, FALSE, 0);
    g_signal_connect(button_about_1, "clicked", G_CALLBACK(about_text), notebook);
    g_signal_connect(button_about_2, "clicked", G_CALLBACK(about_text), notebook);
    g_signal_connect(button_about_3, "clicked", G_CALLBACK(about_text), notebook);
    g_signal_connect(button_about_4, "clicked", G_CALLBACK(about_text), notebook);
    g_signal_connect(button_about_5, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_about1, gtk_label_new("Version"));

    // run css-provider
    add_css_provider(button_about_1, provider);
    add_css_provider(button_about_2, provider);
    add_css_provider(button_about_3, provider);
    add_css_provider(button_about_4, provider);
    add_css_provider(button_about_5, provider);
    

    // page 2
    page_about2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_about2_1 = gtk_button_new_with_label("(C) Copyright 2024 Elias Mörz");
    button_about2_2 = gtk_button_new_with_label("Apache License, Version 2.0");
    button_about2_3 = gtk_button_new_with_label("https://github.com/NachtsternBuild/fastboot-assistant");
    label_about2 = gtk_button_new_with_label("thanks to:\n@mrrfv → Open Android Backup\n@Jean28518 → my build-fastboot-assistant.sh \nbased on his build-scripts.");
    button_about2_4 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_about2), button_about2_1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_about2), button_about2_2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_about2), button_about2_3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_about2), label_about2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_about2), button_about2_4, FALSE, FALSE, 0);
    g_signal_connect(button_about2_1, "clicked", G_CALLBACK(about_text), notebook);
    g_signal_connect(button_about2_2, "clicked", G_CALLBACK(about_text), notebook);
    g_signal_connect(button_about2_3, "clicked", G_CALLBACK(about_text), notebook);
    g_signal_connect(button_about2_4, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_about2, gtk_label_new("Das Programm"));

    // run css-provider
    add_css_provider(button_about2_1, provider);
    add_css_provider(button_about2_2, provider);
    add_css_provider(button_about2_3, provider);
    add_css_provider(label_about2, provider);
    add_css_provider(button_about2_4, provider);

    // page 3
    page_about3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_about3_1 = gtk_button_new_with_label("GitHub Seite");
	button_about3_2 = gtk_button_new_with_label("Versionen");
	button_about3_3 = gtk_button_new_with_label("Feedback");
	button_about3_4 = gtk_button_new_with_label("Open Android Backup");
	button_about3_5 = gtk_button_new_with_label("Jean28518 GitHub");
    gtk_box_pack_start(GTK_BOX(page_about3), button_about3_1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_about3), button_about3_2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_about3), button_about3_3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_about3), button_about3_4, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_about3), button_about3_5, FALSE, FALSE, 0);
    g_signal_connect(button_about3_1, "clicked", G_CALLBACK(fastboot_assistant), NULL);
    g_signal_connect(button_about3_2, "clicked", G_CALLBACK(fastboot_assistant_release), NULL);
    g_signal_connect(button_about3_3, "clicked", G_CALLBACK(feedback), NULL);
    g_signal_connect(button_about3_4, "clicked", G_CALLBACK(open_android_backup), NULL);
    g_signal_connect(button_about3_5, "clicked", G_CALLBACK(brownie_jean), NULL);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_about3, gtk_label_new("Hinweise"));

    // run css-provider
    add_css_provider(button_about3_1, provider);
    add_css_provider(button_about3_2, provider);
    add_css_provider(button_about3_3, provider);
    add_css_provider(button_about3_4, provider);
    add_css_provider(button_about3_5, provider);
    
    // clean the storage
    g_object_unref(provider);
	
	// show all widgets
    gtk_widget_show_all(window);
	
	// run gtk mainloop
    gtk_main();
}

