/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *          Apache License, Version 2.0      *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von         *
 *  Custom-ROM und GSIs auf Android-Geräte   *
 *  zu erleichtern - run_first_run_setup     *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz        *
 *-------------------------------------------*
 *
 */
 
#include <glib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include "function_header.h"
#include "language_check.h"
#include "program_functions.h"
#include "language_check.h"

GtkWidget *window;

// function to quit the application
gboolean quit_application(gpointer data)
{
    exit(1);
    return FALSE;  // Return FALSE to ensure the timeout callback is called only once
}

// callback to switch the language in the setup
void toggle_language_setup(GtkWidget *button, gpointer user_data) 
{

    if (strcmp(language, "de") == 0) 
    {
        language = "en";
        write_language_file();
        delete_config_file();
        apply_language();
        const char *message = "Please restart the Fastboot Assistant.";
        show_message(message);
    }
     
    else 
    {
        language = "de";
        check_language_file_light();
        delete_config_file();
        apply_language();
        const char *message = "Bitte starten Sie den Fastboot-Assistant erneut.";
        show_message(message);
    }

    // set a timeout and quit the application
    g_timeout_add(2000, (GSourceFunc)quit_application, NULL); // After 5 seconds
}

// config the program
void config_start() 
{
    LOG_INFO("config_start");
    const char *message;
    message = "Konfiguration beendet!\n";
    make_dir();
    wsl_config();
    show_message(message);
    LOG_INFO("end config_start");
}

/* the setup wizard */
void run_first_run_setup(GtkWidget *widget, gpointer stack) 
{
	LOG_INFO("run_first_run_setup");
	
	apply_language();
	
	char *auto_theme = auto_path_theme();
	
	
	// widgets
	GtkWidget *page1, *page2, *page3, *page4, *page5;
    GtkWidget *label_welcome_1, *label_welcome_2, *label_page2_1, *label_page2_2, *label_page3_1, *label_page3_2, *label_page3_3, *label_page3_4, *label_page4_1, *label_page4_2, *label_page4_3, *label_page4_4, *label_end_1, *label_end_2;
    GtkWidget *button_welcome_1, *button_setup_dir, *button_toggle_language, *button_toggle_theme, *button_welcome_2, *button_page2_1, *button_dir, *button_page2_2, *button_page3_1, *button_page3_2, *button_page4_1, *button_page4_2, *button_end_1, *button_end_2;
	
	/* page 1 */
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    button_welcome_1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Willkommen zum Fastboot Assistant!" : "Welcome to the Fastboot Assistant!");
    label_welcome_1 = gtk_label_new(" ");
    button_setup_dir = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Ordner für den Flash festlegen" : "Set folder for the flash");
    button_toggle_language = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Sprache wechseln/Switch Language (Deutsch/Englisch)" : "Switch Language/Sprache wechseln (English/German)");
    button_toggle_theme = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Thema wechseln (hell/dunkel)" : "Toggle Theme (Light/Dark)");
    label_welcome_2 = gtk_label_new(" ");
    button_welcome_2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
	
	// check if theme is auto or css only
	// theme = auto (css + libadwaita)
	if (file_exists(auto_theme))
	{
        // disable the button 
        gtk_widget_set_visible(GTK_WIDGET(button_toggle_theme), FALSE);
    } 
    // theme = css only
    else 
    {
        // enable the button
        gtk_widget_set_visible(GTK_WIDGET(button_toggle_theme), TRUE);
    }
	
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_welcome_1);
    gtk_box_append(GTK_BOX(page1), label_welcome_1);
    gtk_box_append(GTK_BOX(page1), button_setup_dir);
    gtk_box_append(GTK_BOX(page1), button_toggle_language);
    gtk_box_append(GTK_BOX(page1), button_toggle_theme);
    gtk_box_append(GTK_BOX(page1), label_welcome_2);
    gtk_box_append(GTK_BOX(page1), button_welcome_2);

    // connect everything
    g_signal_connect(button_setup_dir, "clicked", G_CALLBACK(show_folder_chooser), stack);
    g_signal_connect(button_toggle_language, "clicked", G_CALLBACK(toggle_language_setup), stack);
    g_signal_connect(button_toggle_theme, "clicked", G_CALLBACK(toggle_theme_css), stack);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "welcome")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page1, "welcome");
	}
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "welcome");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_welcome_2), "stack", stack);
	g_signal_connect(button_welcome_2, "clicked", G_CALLBACK(switch_page), "config");
	
	/* page 2 */
    page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_page2_1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Zum korrekten Ausführen muss der \nFastboot-Assistant einige Konfigurationen vornehmen." : "To run correctly, the Fastboot \nAssistant must make some configurations.");
    label_page2_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Es werden alle benötigten Ordner erstellt." : "1. All required folders are created.");
    label_page2_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "2. Anpassungen an das Betriebssystem werden durchgeführt." : "2. Adjustments are made to the operating system.");
    button_dir = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Konfigurieren" : "Configure" );
    button_page2_2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_page2_1);
    gtk_box_append(GTK_BOX(page2), label_page2_1);
    gtk_box_append(GTK_BOX(page2), label_page2_2);
    gtk_box_append(GTK_BOX(page2), button_dir);
    gtk_box_append(GTK_BOX(page2), button_page2_2);

    // connect everything
    g_signal_connect(button_dir, "clicked", G_CALLBACK(config_start), stack);
    
	// add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "config")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page2, "config");
	}
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_page2_2), "stack", stack);
	g_signal_connect(button_page2_2, "clicked", G_CALLBACK(switch_page), "notes");
	
	/* page 3 */
    page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_page3_1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Hinweise" : "Notes");
	label_page3_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Die Verwendung erfolgt auf eigene Gefahr." : "1. Use at your own risk.");
	label_page3_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "2. Das Gerät kann beschädigt werden." : "2. The device may be damaged.");
	label_page3_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "3. Nicht jedes Gerät unterstützt alle Funktionen" : "3. Not every device supports all functions");
	label_page3_4 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "4. Nicht alle Betriebssystemvarianten haben den gleichen Funktionsumfang." : "4. Not all operating system variants have the same range of functions.");
    button_page3_2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page3), button_page3_1);
    gtk_box_append(GTK_BOX(page3), label_page3_1);
    gtk_box_append(GTK_BOX(page3), label_page3_2);
    gtk_box_append(GTK_BOX(page3), label_page3_3);
    gtk_box_append(GTK_BOX(page3), label_page3_4);
    gtk_box_append(GTK_BOX(page3), button_page3_2);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "notes")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page3, "notes");
	}
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_page3_2), "stack", stack);
	g_signal_connect(button_page3_2, "clicked", G_CALLBACK(switch_page), "use");
	
	/* page 4 */
    page4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_page4_1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Verwendung" : "Use");
	label_page4_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Lesen sie vor der Verwendung die \nAnleitungen und die Dokumentation." : "1. Read the instructions and \ndocumentation before use.");
	label_page4_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "2. Kopieren sie immer alle Systemabbilder \ndes Flashs nach '/ROM-Install'." : "2. Always copy all system images \ndes Flashs to '/ROM-Install'.");
	label_page4_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "3. Sollten sie ein Samsung-Gerät flashen \nwollen nutzen sie immer 'heimdall'." : "3. If you want to flash a Samsung device, \nalways use 'heimdall'.");
	label_page4_4 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "4. Prüfen sie regelmäßig, ob es Updates für das Programm gibt." : "4. Check regularly whether there are updates for the program.");
    button_page4_2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page4), button_page4_1);
    gtk_box_append(GTK_BOX(page4), label_page4_1);
    gtk_box_append(GTK_BOX(page4), label_page4_2);
    gtk_box_append(GTK_BOX(page4), label_page4_3);
    gtk_box_append(GTK_BOX(page4), label_page4_4);
    gtk_box_append(GTK_BOX(page4), button_page4_2);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "use")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page4, "use");
	}
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_page4_2), "stack", stack);
	g_signal_connect(button_page4_2, "clicked", G_CALLBACK(switch_page), "end");
	
	// page 5
    page5 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    label_end_1 = gtk_label_new(" ");
    button_end_1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Viel Spaß bei der Verwendung des Fastboot Assistants!" : "Have fun using the Fastboot Assistant!");
    label_end_2 = gtk_label_new(" ");
    button_end_2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Fertig" : "Finished");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page5), label_end_1);
    gtk_box_append(GTK_BOX(page5), button_end_1);
    gtk_box_append(GTK_BOX(page5), label_end_2);
    gtk_box_append(GTK_BOX(page5), button_end_2);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "end")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page5, "end");
	}
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_end_2), "stack", stack);
	g_signal_connect(button_end_2, "clicked", G_CALLBACK(show_home_page), stack);
	
	LOG_INFO("end run_first_setup");
}	
