/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *          Apache License, Version 2.0      *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von         *
 *  Custom-ROM und GSIs auf Android-Geräte   *
 *  zu erleichtern - GUI                     *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz        *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
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
}



// config the program
void config_start() 
{
    const char *message;
    message = "Konfiguration beendet!\n";
    make_dir();
    wsl_config();
    show_message(message);
    
}

/* the main function */
int main(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[9][30] = {"Geräte", "Gerät neustarten", "Einstellungen", 
                                 "Flash vorbereiten", "Flashen", "Anleitungen", 
                                 "Info", "Updater", "Über das Programm"};

    gtk_init(&argc, &argv);
    apply_theme();

    // function that check if the setup run the first time
    // the crazy output came from the experiment with this
    const char *content = "Fisch";
	char fish_path[2048];
	char setup_dir[2048];
	char *homeDir = getenv("HOME");
	if (homeDir == NULL) 
	{
    	fprintf(stderr, "Fehler: Konnte das Home-Verzeichnis nicht finden.\n");
    	exit(1);  // close the program if there are errors
	}

	// WSL Logik
	const char *user = getenv("USER");
	if (user == NULL) 
	{	
    	g_print("Fehler: Konnte den Benutzernamen nicht ermitteln.\n");
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
    	g_print("\nNo Setup\n");
    	g_print("Alter Fisch!\n");
	} 
	else 
	{
	    // file not exsists
    	file = fopen(fish_path, "w");
    	if (file == NULL) 
    	{
    	    fprintf(stderr, "Fehler: Konnte die Datei nicht erstellen.\n");
    	    exit(1);  // close the program if there are errors
    	}
    	fprintf(file, "%s", content);
    	fclose(file);
    	g_print("Fisch\n");
    	// run setup
    	run_first_run_setup(provider);
	}
		
    // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Fastboot-Assistant");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
    // create the grid and centre it
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    // add the grid to the window
    gtk_container_add(GTK_CONTAINER(window), grid);

    // add and centre all button
    for (int i = 0; i < 9; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);

        // execute css-provider for all buttons
        add_css_provider(button, provider);

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
	
	// free the provider
	if (provider != NULL) 
	{
	    g_object_unref(provider);
	}

    
    // show all button
    gtk_widget_show_all(window);

    // gtk mainloop
    gtk_main();    

    return 0;
}
