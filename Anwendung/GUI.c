/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *          Apache License, Version 2.0      *
 *-------------------------------------------*
 *                                           *
 *  Programm um das Installieren von         *
 *  Custom-ROM und GSIs auf Android-Geräte   *
 *  zu erleichtern - GUI                     *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz        *
 *-------------------------------------------*
 *
 */

/* headers that are used in the program */
#include <glib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include "function_header.h"
#include "program_functions.h"
#include "instruction_header.h"
#include "flash_function_header.h"
#include "language_check.h"

#define MAX_BUFFER_SIZE 256
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

// Callback functions for each button
static void start_get_devices(GtkWidget *widget, gpointer data) 
{
    get_devices();
}

static void start_reboot_GUI(GtkWidget *widget, gpointer data) 
{
    reboot_GUI();
}

static void start_config_projekt(GtkWidget *widget, gpointer data) 
{
    config_projekt_GUI();
}

static void start_preflash(GtkWidget *widget, gpointer data) 
{
    preflash_GUI();
}

static void start_flash_GUI(GtkWidget *widget, gpointer data) 
{
    flash_GUI();
}

static void start_instruction_GUI(GtkWidget *widget, gpointer data) 
{
    instruction_GUI();
}

static void start_info(GtkWidget *widget, gpointer data) 
{
    info();
}

static void start_updater(GtkWidget *widget, gpointer data) 
{
    updater();
}

static void start_about(GtkWidget *widget, gpointer data) 
{
    about();
}

// Function to set up directory structure for the config
void config_dir_setup(const char *path) 
{
    g_print("Log: config_dir_setup\n");
    char tmp[2048];
    snprintf(tmp, sizeof(tmp), "%s", path);  
    char *p = tmp;

    for (; *p; p++) 
    {
        if (*p == '/') 
        {
            *p = '\0';
            mkdir(tmp, 0700);
            *p = '/';
        }
    }
    mkdir(tmp, 0700);
    g_print("Log: end config_dir_setup\n");
}

// Config function to start the application setup
void config_start() 
{
    g_print("Log: config_start\n");
    const char *message = "Konfiguration beendet!\n";
    make_dir();
    wsl_config();
    show_message(message);
    g_print("Log: end config_start\n");
}

// Function to set up button labels based on the language
void set_button_labels(char labels[][30]) 
{
    if (strcmp(language, "en") == 0) 
    {
        strcpy(labels[0], "Devices");
        strcpy(labels[1], "Reboot Device");
        strcpy(labels[2], "Settings");
        strcpy(labels[3], "Prepare Flashing");
        strcpy(labels[4], "Flash");
        strcpy(labels[5], "Instructions");
        strcpy(labels[6], "Info");
        strcpy(labels[7], "Updater");
        strcpy(labels[8], "About");
    } 
    
    else 
    {
        strcpy(labels[0], "Geräte");
        strcpy(labels[1], "Gerät neustarten");
        strcpy(labels[2], "Einstellungen");
        strcpy(labels[3], "Flash vorbereiten");
        strcpy(labels[4], "Flashen");
        strcpy(labels[5], "Anleitungen");
        strcpy(labels[6], "Info");
        strcpy(labels[7], "Updater");
        strcpy(labels[8], "Über das Programm");
    }
}

int main(int argc, char *argv[]) 
{
    g_print("Log: fastboot-assistant\n");
    GtkWidget *window, *grid, *button;
    char button_labels[9][30];
    
    gtk_init();
    apply_theme();
    apply_language();
    set_button_labels(button_labels);

    const char *content = "Fisch";
    char fish_path[2048];
    char setup_dir[2048];
    char *homeDir = getenv("HOME");
    if (homeDir == NULL) 
    {
        fprintf(stderr, "Fehler: Konnte das Home-Verzeichnis nicht finden.\n");
        exit(1);
    }

    const char *user = getenv("USER");
    if (user == NULL) 
    {
        g_print("Fehler: Konnte den Benutzernamen nicht ermitteln.\n");
        exit(1);
    }

    snprintf(setup_dir, sizeof(setup_dir), "%s", homeDir);
    snprintf(fish_path, sizeof(fish_path), "%s/Downloads/ROM-Install/config", setup_dir);
    config_dir_setup(fish_path);

    snprintf(fish_path, sizeof(fish_path), "%s/Downloads/ROM-Install/config/config.txt", setup_dir);
    FILE *file;
    if ((file = fopen(fish_path, "r")) != NULL) 
    {
        fclose(file);
        g_print("\nNo Setup\n");
    } 
    
    else 
    {
        file = fopen(fish_path, "w");
        if (file == NULL) 
        {
            fprintf(stderr, "Fehler: Konnte die Datei nicht erstellen.\n");
            exit(1);
        }
        fprintf(file, "%s", content);
        fclose(file);
        g_print("Fisch\n");
        run_first_run_setup();
    }

    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Fastboot-Assistant");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), grid);

    for (int i = 0; i < 9; i++) 
    {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);

        switch (i) 
        {
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
                g_signal_connect(button, "clicked", G_CALLBACK(start_instruction_GUI), NULL);
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

    gtk_widget_show(window);
    gtk_main();

    g_print("Log: end fastboot-assistant\n");
    return 0;
}
