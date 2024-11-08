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
 *      (C) Copyright 2024 Elias Mörz        *
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

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300

void run_first_run_setup(GtkCssProvider *provider) 
{
    g_print("Log: run_first_run_setup\n");
    
    // GTK init
    gtk_init();

    apply_theme();
    apply_language();

    GtkWidget *window, *notebook;
    GtkWidget *page1, *label_welcome_1;
    GtkWidget *button_toggle_theme, *button_toggle_language, *button_welcome_2;

    // create the main window
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Fastboot Assistant Setup");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // create the notebook
    notebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // page 1
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    label_welcome_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Willkommen zum Fastboot Assistant!" : "Welcome to the Fastboot Assistant!");
    button_toggle_language = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Sprache wechseln (Deutsch/Englisch)" : "Switch Language (English/German)");
    button_toggle_theme = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Thema wechseln (hell/dunkel)" : "Toggle Theme (Light/Dark)");
    button_welcome_2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");

    // add everything to the page
    gtk_box_append(GTK_BOX(page1), label_welcome_1);
    gtk_box_append(GTK_BOX(page1), button_toggle_language);
    gtk_box_append(GTK_BOX(page1), button_toggle_theme);
    gtk_box_append(GTK_BOX(page1), button_welcome_2);

    // connect everything
    g_signal_connect(button_toggle_language, "clicked", G_CALLBACK(toggle_language), notebook);
    g_signal_connect(button_toggle_theme, "clicked", G_CALLBACK(toggle_theme), notebook);
    g_signal_connect(button_welcome_2, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, gtk_label_new(g_strcmp0(language, "de") == 0 ? "Begrüßung" : "Welcome"));

    // 
    gtk_widget_show(window);
    gtk_widget_show(notebook);
    gtk_widget_show(page1);
    gtk_widget_show(label_welcome_1);
    gtk_widget_show(button_toggle_language);
    gtk_widget_show(button_toggle_theme);
    gtk_widget_show(button_welcome_2);

    gtk_main();
    g_print("Log: end run_first_run_setup\n");
}
