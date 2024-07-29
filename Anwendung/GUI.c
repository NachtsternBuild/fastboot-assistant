/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *          Sprudelnde PC-Kühlung            *
 *-------------------------------------------*
 *          Apache License, Version 2.0      *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von         *
 *  Custom-ROM und GSIs auf Android-Geräte   *
 *  zu erleichtern - GUI                     *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz        *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include "function_header.h"
#include "program_functions.h"
#include "flash_function_header.h"
// the headers need a rework
#include "instruction_header.h"

#define MAX_BUFFER_SIZE 256
// include all functions
extern void get_devices();
extern void reboot_GUI();
extern void config_projekt_GUI();
extern void preflash_GUI();
extern void flash_GUI();
extern void instruction_GUI();
extern void info();
extern void updater();
extern void about();

// Callback functions for each button
// start get_devices-function
static void start_get_devices(GtkWidget *widget, gpointer data) 
{
    get_devices();
}

// start reboot_GUI-function
static void start_reboot_GUI(GtkWidget *widget, gpointer data) 
{
    reboot_GUI();
}

// start projekt-122-tools-function
static void start_config_projekt(GtkWidget *widget, gpointer data) 
{
    config_projekt_GUI();
}

// start preflash_GUI-function
static void start_preflash(GtkWidget *widget, gpointer data) 
{
    preflash_GUI();
}

// start flash_GUI-function
static void start_flash_GUI(GtkWidget *widget, gpointer data) 
{
    flash_GUI();
}

// start instructions_GUI-function
static void start_instructions(GtkWidget *widget, gpointer data) 
{
    instructions_GUI();
}

// start info-function
static void start_info(GtkWidget *widget, gpointer data) 
{
    info();
}

// start updater-function
static void start_updater(GtkWidget *widget, gpointer data) 
{
    updater();
}

// start about-function
static void start_about(GtkWidget *widget, gpointer data) 
{
    about();
}

/* main function of projekt-122*/
int main(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[9][20] = {"Verbindung überprüfen (ADB/Fastboot)", "Gerät neustarten", "Konfigurieren von Projekt-122", 
                                 "Flash vorbereiten", "Flashen von System-Abbildern", "Anleitungen", 
                                 "Info", "Updater", "Über das Programm"};

    gtk_init(&argc, &argv);

    // create new windows
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Projekt-122");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // create a grid
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // add buttons and connect them with callback
    for (int i = 0; i < 9; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);
        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(start_get_devices), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(start_reboot_GUI), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(start_config_projekt), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(start_preflash), NULL);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(start_flash_GUI), NULL);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(start_instructions), NULL);
                break;
            case 6:
                g_signal_connect(button, "clicked", G_CALLBACK(start_info), NULL);
                break;
            case 7:
                g_signal_connect(button, "clicked", G_CALLBACK(start_updater), NULL);
                break;
            case 8:
                g_signal_connect(button, "clicked", G_CALLBACK(start_about), NULL);
                break;
        }
    }

    /* change the style of the buttons to quick settings buttons from android 12 - css is used for this*/
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "button {\n"
                                    "    background-color: #8B0000;\n" /* darkred */
                                    "    border: none;\n"
                                    "    border-radius: 12px;\n" /* round corners */
                                    "    padding: 12px 24px;\n" /* inside distance */
                                    "    color: #ffffff;\n" /* White text */
                                    "    font-size: 16px;\n" /* Font size */
                                    "    font-weight: 500;\n" /* Medium font */
                                    "    text-align: center;\n" /* Centre text */
                                    "    box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);\n" /* Light shade */
                                    "    transition: background-color 0.3s ease, box-shadow 0.3s ease;\n" /* Animation */
                                    "}\n"
                                    "button:hover {\n"
                                    "    background-color: #A52A2A;\n" /* Brighter red on hover */
                                    "    box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);\n" /* Amplify shadows */
                                    "}\n",
                                    -1,
                                    NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);

    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();

    return 0;
}

