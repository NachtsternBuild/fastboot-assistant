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
void fastboot_assistant(GtkWidget *widget, gpointer stack)
{
    const char *git_url = "https://github.com/NachtsternBuild/fastboot-assistant";
    
	open_url(git_url);
}

// function that open the GitHub Releases page
void fastboot_assistant_release(GtkWidget *widget, gpointer stack)
{
    const char *release_url = "https://github.com/NachtsternBuild/fastboot-assistant/releases";
	open_url(release_url);
}

// function to open the website that used for the feedback for the fastboot-assistant
void feedback(GtkWidget *widget, gpointer stack)
{
    const char *feedback_url = "https://forms.gle/dBWBawwqNgFWCLz58";
	open_url(feedback_url);
}

// function to open the dokumentation of the fastboot-assistant
void dokumentation(GtkWidget *widget, gpointer stack)
{
    const char *feedback_url = "https://github.com/NachtsternBuild/fastboot-assistant/wiki";
	open_url(feedback_url);
}

// function to open the website from 'Open Android Backup'
void open_android_backup(GtkWidget *widget, gpointer stack)
{
    const char *open_android_backup_url = "https://github.com/mrrfv/open-android-backup";
	open_url(open_android_backup_url);
}

// function to open the website from 'Open Android Backup'
void brownie_jean(GtkWidget *widget, gpointer stack)
{
    const char *brownie_jean_url = "https://github.com/Jean28518";
	open_url(brownie_jean_url);
}

// function that output version infos about the system and installed packages
void run_tools_info(GtkWidget *widget, gpointer stack)
{
	info_tools();
}

/* main function - about */
void about(GtkWidget *widget, gpointer stack) 
{
    LOG_INFO("about");
    apply_language();
    
    GtkWidget *page1, *page2, *page3;
    GtkWidget *label_about1, *label_about2, *label_about3, *label_about4, *label_about5, *label_about6, *label_about7, *label_about8;
    GtkWidget *button_about_1, *button_about_2, *button_about_3, *button_about_4, *button_about_5, *button_about_6, *button_about3_1, *button_about3_2, *button_about3_3, *button_about3_4, *button_about3_5, *button_about3_6, *button_about3_7;
    
    /* page 1 */
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	
	// button and label    
    label_about1 = gtk_label_new("Fastboot Assistant");
    label_about2 = gtk_label_new("Version 0.8.1.beta");
    label_about3 = gtk_label_new("Glitschiges GNOME 40");
    label_about4 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Programm um das installieren von Custom-ROM \nund GSIs auf Android-Geräte zu erleichtern." : "Program to facilitate the installation of custom ROM \nand GSIs on Android devices.");
    button_about_1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Aktualisierungen" : "Updates");
    button_about_2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    button_about_3 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Verlassen" : "Exit"); 
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), label_about1);
    gtk_box_append(GTK_BOX(page1), label_about2);
    gtk_box_append(GTK_BOX(page1), label_about3);
    gtk_box_append(GTK_BOX(page1), label_about4);
    gtk_box_append(GTK_BOX(page1), button_about_1);
    gtk_box_append(GTK_BOX(page1), button_about_2);
    gtk_box_append(GTK_BOX(page1), button_about_3);
    

    // connect everything
    g_signal_connect(button_about_1, "clicked", G_CALLBACK(updater), stack);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "about_assistant")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page1, "about_assistant");
	}
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "about_assistant");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_about_2), "stack", stack);
	g_signal_connect(button_about_2, "clicked", G_CALLBACK(switch_page), "program");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_about_3), "stack", stack);
	g_signal_connect(button_about_3, "clicked", G_CALLBACK(show_home_page), stack);
	
	/* page 2 */
    page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    label_about5 = gtk_label_new("(C) Copyright 2025 Elias Mörz");
    label_about6 = gtk_label_new("Apache License, Version 2.0");
    label_about7 = gtk_label_new("https://github.com/NachtsternBuild/fastboot-assistant");
    label_about8 = gtk_label_new("thanks to:\n@mrrfv → Open Android Backup\n@Jean28518 → my build-fastboot-assistant.sh \nbased on his build-scripts for DEB.");
    button_about_4 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "System- und Paketinformationen" : "System and package information");
    button_about_5 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    button_about_6 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Zurück" : "Back");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), label_about5);
    gtk_box_append(GTK_BOX(page2), label_about6);
    gtk_box_append(GTK_BOX(page2), label_about7);
    gtk_box_append(GTK_BOX(page2), label_about8);
    gtk_box_append(GTK_BOX(page2), button_about_4);
    gtk_box_append(GTK_BOX(page2), button_about_5);
    gtk_box_append(GTK_BOX(page2), button_about_6);

    // connect everything
    g_signal_connect(button_about_4, "clicked", G_CALLBACK(info_tools), stack);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "program")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page2, "program");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_about_5), "stack", stack);
	g_signal_connect(button_about_5, "clicked", G_CALLBACK(switch_page), "program_notes");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_about_6), "stack", stack);
	g_signal_connect(button_about_6, "clicked", G_CALLBACK(switch_page), "about_assistant");
	
	/* page 3 */
    page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_about3_1 = gtk_button_new_with_label("GitHub Seite");
	button_about3_2 = gtk_button_new_with_label("Versionen");
	button_about3_3 = gtk_button_new_with_label("Feedback");
	button_about3_4 = gtk_button_new_with_label("Dokumentation");
	button_about3_5 = gtk_button_new_with_label("Open Android Backup");
	button_about3_6 = gtk_button_new_with_label("Jean28518 GitHub");
	button_about3_7 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Verlassen" : "Exit");
	button_about3_8 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Zurück" : "Back");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page3), button_about3_1);
    gtk_box_append(GTK_BOX(page3), button_about3_2);
    gtk_box_append(GTK_BOX(page3), button_about3_3);
    gtk_box_append(GTK_BOX(page3), button_about3_4);
    gtk_box_append(GTK_BOX(page3), button_about3_5);
    gtk_box_append(GTK_BOX(page3), button_about3_6);
    gtk_box_append(GTK_BOX(page3), button_about3_7);
    gtk_box_append(GTK_BOX(page3), button_about3_8);
    
    // connect everything
    g_signal_connect(button_about3_1, "clicked", G_CALLBACK(fastboot_assistant), stack);
    g_signal_connect(button_about3_2, "clicked", G_CALLBACK(fastboot_assistant_release), stack);
    g_signal_connect(button_about3_3, "clicked", G_CALLBACK(feedback), stack);
    g_signal_connect(button_about3_4, "clicked", G_CALLBACK(dokumentation), stack);
    g_signal_connect(button_about3_5, "clicked", G_CALLBACK(open_android_backup), stack);
    g_signal_connect(button_about3_6, "clicked", G_CALLBACK(brownie_jean), stack);
    
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "program_notes")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page3, "program_notes");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_about3_7), "stack", stack);
	g_signal_connect(button_about3_7, "clicked", G_CALLBACK(show_home_page), stack);
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_about3_8), "stack", stack);
	g_signal_connect(button_about3_8, "clicked", G_CALLBACK(switch_page), "program");

    LOG_INFO("end about");
}
