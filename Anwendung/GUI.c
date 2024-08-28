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
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

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
// a function for the setup
extern void make_dir();


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
    struct stat st = {0};
    if (stat(pfad, &st) == -1) 
    {
        if (mkdir(pfad, 0700) != 0)
         {
            perror("Fehler beim Erstellen des Verzeichnisses");
            exit(EXIT_FAILURE);
        }
    }
}


// config the program
static void config_start() 
{
    GtkWidget *dialog;
    const char *message;
    message = "Konfiguration beendet!\n";
    make_dir();
    wsl_config();
    show_message(message);
    
}

// button after the setup finished
static void button_finish(GtkButton *button, gpointer data) 
{
    gtk_main_quit();
}

static void setup_text(GtkButton *button, gpointer data) 
{
	g_print("Hier gibt's nichts!\n");
}

// function that run the setup
static void run_first_run_setup(GtkCssProvider *provider) 
{
    GtkWidget *window;
    GtkWidget *page1, *page2, *page3, *page4, *page5;
    GtkWidget *label_welcome_1, *label_welcome_2, *label_page2_1, *label_page2_2, *label_page3_1, *label_page3_2, *label_page3_3, *label_page3_4, *label_page4_1, *label_page4_2, *label_page4_3, *label_page4_4, *label_end_1, *label_end_2;
    GtkWidget *button_welcome_1, *button_welcome_2, *button_page2_1, *button_dir, *button_page2_2, *button_page3_1, *button_page3_2, *button_page4_1, *button_page4_2, *button_end_1, *button_end_2;
    GtkStyleContext *context;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Fastboot Assistant Setup");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
	
	GtkWidget *notebook = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window), notebook);
    
    if (!GTK_IS_NOTEBOOK(notebook)) 
    {
    	g_warning("Notebook is not initialized properly.");
    	return;
	}

    // page 1
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    label_welcome_1 = gtk_label_new(" ");
    button_welcome_1 = gtk_button_new_with_label("Willkommen zum Fastboot Assistant!");
    label_welcome_2 = gtk_label_new(" ");
    button_welcome_2 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page1), label_welcome_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page1), button_welcome_1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page1), label_welcome_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page1), button_welcome_2, FALSE, FALSE, 0);
    g_signal_connect(button_welcome_1, "clicked", G_CALLBACK(setup_text), notebook);
    g_signal_connect(button_welcome_2, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, gtk_label_new("Begrüßung"));

    // run css-provider
    add_css_provider(button_welcome_1, provider);
    add_css_provider(button_welcome_2, provider);
    

    // page 2
    page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_page2_1 = gtk_button_new_with_label("Zum korrekten Ausführen muss der \nFastboot-Assistant einige Konfigurationen vornehmen.");
    label_page2_1 = gtk_label_new("1. Es werden alle benötigten Ordner erstellt.");
    label_page2_2 = gtk_label_new("2. Anpassungen an das Betriebssystem werden durchgeführt.");
    button_dir = gtk_button_new_with_label("Konfigurieren");
    button_page2_2 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page2), button_page2_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page2), label_page2_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page2), label_page2_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page2), button_dir, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page2), button_page2_2, FALSE, FALSE, 0);
    g_signal_connect(button_page2_1, "clicked", G_CALLBACK(setup_text), notebook);
    g_signal_connect(button_dir, "clicked", G_CALLBACK(config_start), NULL);
    g_signal_connect(button_page2_2, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page2, gtk_label_new("Konfiguration"));

    // run css-provider
    add_css_provider(button_page2_1, provider);
    add_css_provider(label_page2_1, provider);
    add_css_provider(label_page2_2, provider);
    add_css_provider(button_dir, provider);
    add_css_provider(button_page2_2, provider);

    // page 3
    page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_page3_1 = gtk_button_new_with_label("Hinweise:");
	label_page3_1 = gtk_label_new("1. Die Verwendung erfolgt auf eigene Gefahr.");
	label_page3_2 = gtk_label_new("2. Das Gerät kann beschädigt werden.");
	label_page3_3 = gtk_label_new("3. Nicht jedes Gerät unterstützt alle Funktionen");
	label_page3_4 = gtk_label_new("4. Nicht alle Betriebssystemvarianten haben den gleichen Funktionsumfang.");
    button_page3_2 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page3), button_page3_1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page3), label_page3_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page3), label_page3_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page3), label_page3_3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page3), label_page3_4, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page3), button_page3_2, FALSE, FALSE, 0);
    g_signal_connect(button_page3_1, "clicked", G_CALLBACK(setup_text), notebook);
    g_signal_connect(button_page3_2, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page3, gtk_label_new("Hinweise"));

    // run css-provider
    add_css_provider(button_page3_1, provider);
    add_css_provider(label_page3_1, provider);
    add_css_provider(label_page3_2, provider);
    add_css_provider(label_page3_3, provider);
    add_css_provider(label_page3_4, provider);
    add_css_provider(button_page3_2, provider);
    
    // page 4
    page4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_page4_1 = gtk_button_new_with_label("Verwendung:");
	label_page4_1 = gtk_label_new("1. Lesen sie vor der Verwendung die \nAnleitungen.");
	label_page4_2 = gtk_label_new("2. Kopieren sie immer alle Systemabbilder \ndes Flashs nach ~/Downloads/ROM-Install.");
	label_page4_3 = gtk_label_new("3. Sollten sie ein Samsung-Gerät flashen \nwollen nutzen sie immer 'heimdall'.");
	label_page4_4 = gtk_label_new("4. Prüfen sie regelmäßig, ob es Updates für das Programm gibt.");
    button_page4_2 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page4), button_page4_1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page4), label_page4_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page4), label_page4_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page4), label_page4_3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page4), label_page4_4, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page4), button_page4_2, FALSE, FALSE, 0);
    g_signal_connect(button_page4_1, "clicked", G_CALLBACK(setup_text), notebook);
    g_signal_connect(button_page4_2, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page4, gtk_label_new("Verwendung"));

    // run css-provider
	add_css_provider(button_page4_1, provider);
	add_css_provider(label_page4_1, provider);
	add_css_provider(label_page4_2, provider);
	add_css_provider(label_page4_3, provider);
	add_css_provider(label_page4_4, provider);
	add_css_provider(button_page4_2, provider);
	
	// page 5
    page5 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    label_end_1 = gtk_label_new(" ");
    button_end_1 = gtk_button_new_with_label("Viel Spaß bei der Verwendung des Fastboot Assistants!");
    label_end_2 = gtk_label_new(" ");
    button_end_2 = gtk_button_new_with_label("Fertig");
    gtk_box_pack_start(GTK_BOX(page5), label_end_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page5), button_end_1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page5), label_end_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page5), button_end_2, FALSE, FALSE, 0);
    g_signal_connect(button_end_1, "clicked", G_CALLBACK(setup_text), notebook);
    g_signal_connect(button_end_2, "clicked", G_CALLBACK(button_finish), notebook);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page5, gtk_label_new("Ende"));

    // run css-provider
    add_css_provider(button_end_1, provider);
	add_css_provider(button_end_2, provider);
	
    gtk_widget_show_all(window);

    gtk_main();
}

/* the main function */
int main(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkStyleContext *context;
    char button_labels[9][30] = {"Geräte", "Gerät neustarten", "Einstellungen", 
                                 "Flash vorbereiten", "Flashen", "Anleitungen", 
                                 "Info", "Updater", "Über das Programm"};

    gtk_init(&argc, &argv);
    css_provider(); // load css-provider
    
    // function that check if the setup run the first time
    // the crazy output came from the experiment with this
    const char *content = "Fisch";
    char fish_path[256];
    char setup_dir[1024];
    char *homeDir = getenv("HOME");
    if (homeDir == NULL) 
    {
        fprintf(stderr, "Fehler: Konnte das Home-Verzeichnis nicht finden.\n");
        return;
    }
    
    // the wsl logic
    const char *user = getenv("USER");
    if (user == NULL) 
    {
        g_print("Fehler: Konnte den Benutzernamen nicht ermitteln.\n");
        return;
    }

    char wsl_setup_base[1024];
    snprintf(wsl_setup_base, sizeof(wsl_setup_base), "/mnt/c/Users/%s", user);
    
    // set the needed path construction active
    // this is for linux
    snprintf(setup_dir, sizeof(setup_dir), "%s", homeDir);
    // this for the WSL
    // snprintf(setup_dir, sizeof(setup_dir), "%s", wsl_setup_base);
    g_print(setup_dir);
    
    // create the config dir
    snprintf(fish_path, sizeof(fish_path), "%s/Downloads/ROM-Install/config", setup_dir);
    config_dir_setup(fish_path);
    
    // create the full path to the config.txt
    snprintf(fish_path, sizeof(fish_path), "%s/Downloads/ROM-Install/config/config.txt", setup_dir);

    FILE *file;

    // check whether the file still exists
    if ((file = fopen(fish_path, "r")) != NULL) 
    {
        // file exists
        fclose(file);
        g_print("No Setup\n");
        // the crazy output came from the experiment with this
        g_print("Alter Fisch!\n");
    } 
    
    else 
    {
        // file not exists
        file = fopen(fish_path, "w");
        if (file == NULL) 
        {
            fprintf(stderr, "Fehler: Konnte die Datei nicht erstellen.\n");
            return;
        }
        fprintf(file, "%s", content);
        fclose(file);
        // the crazy output came from the experiment with this
        g_print("Fisch\n");
        // run the setup
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

    // show all button
    gtk_widget_show_all(window);

    // gtk mainloop
    gtk_main();

    // clean the storage
    g_object_unref(provider);

    return 0;
}
