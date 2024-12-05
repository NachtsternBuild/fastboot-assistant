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
extern void make_dir();

extern void run_first_run_setup();


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
static void start_instruction_GUI(GtkWidget *widget, gpointer data) 
{
    instruction_GUI();
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

// create the dir for the setup
void config_dir_setup(const char *pfad) 
{
    g_print("Log: config_dir_setup\n");
    char tmp[2048];
    snprintf(tmp, sizeof(tmp), "%s", pfad);  // copy the path
    char *p = tmp;

    for (; *p; p++) 
    {
        if (*p == '/')
         {
            *p = '\0';  // set temp end
            mkdir(tmp, 0700);  // create the dir
            *p = '/';  // reset the option
        }
    }
    mkdir(tmp, 0700);  // create the dir
	g_print("Log: end config_dir_setup\n");
}

// config the program
void config_start() 
{
    g_print("Log: config_start\n");
    const char *message;
    message = "Konfiguration beendet!\n";
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

static void activate_fastboot_assistant(GtkApplication* app, gpointer user_data)
{
	g_print("Log: activate_fastboot_assistant\n");
	GtkWidget *window, *grid, *button;
    char button_labels[9][30];
    
    gtk_init();
    main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    set_button_labels(button_labels);

    // function that check if the setup run the first time
    // the crazy output came from the experiment with this
    const char *content = "Fisch";
	char fish_path[2048];
	char setup_dir[2048];
	char *homeDir = getenv("HOME");
	if (homeDir == NULL) 
	{
    	fprintf(stderr, "Log: Error: Could not find the home directory.\n");
    	exit(1);  // close the program if there are errors
	}

	// WSL Logik
	const char *user = getenv("USER");
	if (user == NULL) 
	{	
    	g_print("Log: Error: Could not determine the user name.\n");
    	exit(1);  // close the program if there are errors
	}

	char wsl_setup_base[2048];
	snprintf(wsl_setup_base, sizeof(wsl_setup_base), "/mnt/c/Users/%s", user);

	// for linux
	snprintf(setup_dir, sizeof(setup_dir), "%s", homeDir);
	// for wsl
	// snprintf(setup_dir, sizeof(setup_dir), "%s", wsl_setup_base);

	// create the dir for the config
	snprintf(fish_path, sizeof(fish_path), "%s/Downloads/ROM-Install/config", setup_dir);
	config_dir_setup(fish_path);

	// create full path for the config.txt
	snprintf(fish_path, sizeof(fish_path), "%s/Downloads/ROM-Install/config/config.txt", setup_dir);

	FILE *file;

	// check if file exsists
	if ((file = fopen(fish_path, "r")) != NULL) 
	{
    	// file exsists
    	fclose(file);
    	g_print("Log: No Setup\n");
    	g_print("Log: old fish!\n");
	} 
	else 
	{
	    // file not exsists
    	file = fopen(fish_path, "w");
    	if (file == NULL) 
    	{
    	    fprintf(stderr, "Log: Error: Could not create the file.\n");
    	    exit(1);  // close the program if there are errors
    	}
    	fprintf(file, "%s", content);
    	fclose(file);
    	g_print("Log: fish\n");
    	// run setup
    	run_first_run_setup(provider);
    	g_print("Log: Setup completed.\n");
	}

    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Fastboot-Assistant");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);

    
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
	g_print("Log: end activate_fastboot_assistant\n");
}

/* main function - GUI */
int main(int argc, char *argv[]) 
{
    g_print("Log: fastboot-assistant\n");
	GtkApplication *app;
    int status;

    app = gtk_application_new("org.nachtsternbuild.FastbootAssistant", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK (activate_fastboot_assistant), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref(app);

    g_print("Log: end fastboot-assistant\n");
    return status;
}
