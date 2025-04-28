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
    
       
    // style provider for the setup
	// 1. css provider
	GtkCssProvider *provider_about_1 = gtk_css_provider_new();
        gtk_css_provider_load_from_string(provider_about_1,
    	".about { text-decoration: underline; font-weight: bold; font-size: 22px;}"
    	);
	
	// 2. provider
	GtkCssProvider *provider_about_2 = gtk_css_provider_new();
        gtk_css_provider_load_from_string(provider_about_2,
    	".about2 { font-weight: bold; font-size: 22px;}"
    	);
    	
    // with underline
	GtkCssProvider *provider_about_3 = gtk_css_provider_new();
        gtk_css_provider_load_from_string(provider_about_3,
    	".about3 { text-decoration: underline; font-weight: bold; font-size: 32px;}"
    	);
    
    // char for the next page button
	const char *next_page_char = strcmp(language, "de") == 0 ? "Weiter" : "Next";
	const char *back_page_char = strcmp(language, "de") == 0 ? "Zurück" : "Back";
	const char *exit_page_char = strcmp(language, "de") == 0 ? "Verlassen" : "Exit";
	
	/* page 1 */
	GtkWidget *page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	
    // button and label
    GtkWidget *label_about_1 = gtk_label_new(" ");
    GtkWidget *logo_about;
    // add the fastboot-assistant logo  
    const char *main_icon[] = {
    		"./sweet_unix.png",
    		"/usr/share/fastboot-assistant/icons/sweet_unix.png"
	};

	for (int i = 0; i < 2; ++i) 
	{
    	if (g_file_test(main_icon[i], G_FILE_TEST_EXISTS)) 
    	{
       		// add the logo
       		logo_about = gtk_image_new_from_file(main_icon[i]);
       		break;
    	}
	} 
	gtk_widget_set_size_request(logo_about, 128, 128);
	//gtk_image_set_pixel_size(GTK_IMAGE(logo), 64);
	
	GtkWidget *label_about_2 = gtk_label_new(" ");
	GtkWidget *label_about1 = gtk_label_new("Fastboot Assistant");
	gtk_widget_add_css_class(label_about1, "about3");
	
	// create a frame
	GtkWidget *frame = gtk_frame_new(NULL);

    // create vbox
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // create the label
    GtkWidget *label_about2 = gtk_label_new("Version 0.8.1.beta");
    gtk_widget_add_css_class(label_about2, "about2");
    GtkWidget *label_about3 = gtk_label_new("Glitschiges GNOME 40");
    gtk_widget_add_css_class(label_about3, "about2");
    
    // add the label to the box
    gtk_box_append(GTK_BOX(vbox), label_about2);
    gtk_box_append(GTK_BOX(vbox), label_about3);

    // add the box to the frame
    gtk_frame_set_child(GTK_FRAME(frame), vbox);
    
    GtkWidget *label_about_3 = gtk_label_new(" ");
    
    // new label
    GtkWidget *label_about4 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Programm um das installieren von Custom-ROM und GSIs auf Android-Geräte zu erleichtern." : "Program to facilitate the installation of custom ROM and GSIs on Android devices.");
    gtk_label_set_wrap(GTK_LABEL(label_about4), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_about4), PANGO_WRAP_WORD_CHAR);	
	gtk_widget_add_css_class(label_about4, "about2");
	
	GtkWidget *label_about_4 = gtk_label_new(" ");
	
    // new button
    GtkWidget *button_about_1 = create_icon_nav_button_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_about_2 = create_icon_nav_button_no_callback("application-exit-symbolic", exit_page_char);
    
    // add the widgets to the page
    gtk_box_append(GTK_BOX(page1), label_about_1);
    gtk_box_append(GTK_BOX(page1), logo_about);
    gtk_box_append(GTK_BOX(page1), label_about_2);
    gtk_box_append(GTK_BOX(page1), label_about1);
    gtk_box_append(GTK_BOX(page1), frame);
    gtk_box_append(GTK_BOX(page1), label_about_3);
    gtk_box_append(GTK_BOX(page1), label_about4);
    gtk_box_append(GTK_BOX(page1), label_about_4);
    gtk_box_append(GTK_BOX(page1), button_about_1);
    gtk_box_append(GTK_BOX(page1), button_about_2);
	
	// add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "about_assistant")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page1, "about_assistant");
	}
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "about_assistant");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_about_1), "stack", stack);
	g_signal_connect(button_about_1, "clicked", G_CALLBACK(switch_page), "program");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_about_2), "stack", stack);
	g_signal_connect(button_about_2, "clicked", G_CALLBACK(show_home_page), stack);
	
	// run css for gtk4
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider_about_1),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
    // run css for gtk4
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider_about_2),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
    // run css for gtk4
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider_about_3),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
    	
	/* page 2 */
	GtkWidget *page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	
	GtkWidget *label_about_5 = gtk_label_new(" ");
	GtkWidget *label_about5 = gtk_label_new("Fastboot Assistant");
	gtk_widget_add_css_class(label_about5, "about3");
	
	// create a frame
	GtkWidget *frame2 = gtk_frame_new(NULL);

    // create vbox
    GtkWidget *vbox2_1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	
	// button and label
    GtkWidget *label_about6 = gtk_label_new("(C) Copyright 2025 Elias Mörz\n");
    gtk_widget_add_css_class(label_about6, "about2");
    GtkWidget *label_about7 = gtk_label_new("Apache License, Version 2.0");
    gtk_widget_add_css_class(label_about7, "about2");
    GtkWidget *label_about8 = gtk_label_new("https://github.com/NachtsternBuild/fastboot-assistant");
    gtk_label_set_wrap(GTK_LABEL(label_about8), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_about8), PANGO_WRAP_WORD_CHAR);	
	gtk_widget_add_css_class(label_about8, "about2");
	
	// add the label to the box
    gtk_box_append(GTK_BOX(vbox2_1), label_about6);
    gtk_box_append(GTK_BOX(vbox2_1), label_about7);
    gtk_box_append(GTK_BOX(vbox2_1), label_about8);

    // add the box to the frame
    gtk_frame_set_child(GTK_FRAME(frame2), vbox2_1);
    
    // new button
    const char *update_char = strcmp(language, "de") == 0 ? "Aktualisierungen" : "Updates";
    GtkWidget *button_update = create_icon_nav_button("software-update-available-symbolic", update_char, G_CALLBACK(updater), stack);
    const char *system_info_char = strcmp(language, "de") == 0 ? "System- und Paketinformationen" : "System and package information";
    GtkWidget *button_system_info = create_icon_nav_button("start-here-symbolic", system_info_char, G_CALLBACK(run_tools_info), stack);
    GtkWidget *button_about_3 = create_icon_nav_button_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_about_4 = create_icon_nav_button_no_callback("pan-start-symbolic", back_page_char);
	
	// add widgets to the box
	gtk_box_append(GTK_BOX(page2), label_about_5);
	gtk_box_append(GTK_BOX(page2), label_about5);
	gtk_box_append(GTK_BOX(page2), frame2);
	gtk_box_append(GTK_BOX(page2), button_update);
    gtk_box_append(GTK_BOX(page2), button_system_info);
    gtk_box_append(GTK_BOX(page2), button_about_3);
    gtk_box_append(GTK_BOX(page2), button_about_4);

	// add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "program")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page2, "program");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_about_3), "stack", stack);
	g_signal_connect(button_about_3, "clicked", G_CALLBACK(switch_page), "program_notes");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_about_4), "stack", stack);
	g_signal_connect(button_about_4, "clicked", G_CALLBACK(switch_page), "about_assistant");
	
	/* page 3 */
    GtkWidget *page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    GtkWidget *button_about3_1 = gtk_button_new_with_label("GitHub Seite");
	GtkWidget *button_about3_2 = gtk_button_new_with_label("Versionen");
	GtkWidget *button_about3_3 = gtk_button_new_with_label("Feedback");
	GtkWidget *button_about3_4 = gtk_button_new_with_label("Dokumentation");
	GtkWidget *button_about3_5 = gtk_button_new_with_label("Open Android Backup");
	GtkWidget *button_about3_6 = gtk_button_new_with_label("Jean28518 GitHub");
	GtkWidget *button_about3_7 = create_icon_nav_button_no_callback("application-exit-symbolic", exit_page_char);
    GtkWidget *button_about3_8 = create_icon_nav_button_no_callback("pan-start-symbolic", back_page_char);
    
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
