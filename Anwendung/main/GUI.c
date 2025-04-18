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
 *      (C) Copyright 2025 Elias Mörz        *
 *-------------------------------------------*
 *
 */

/* headers that are used in the program */
#include <glib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <adwaita.h>
#include <sys/stat.h>  
#include "language_check.h"
#include "function_header.h"
#include "program_functions.h"
#include "instruction_header.h"
#include "flash_function_header.h"

#define MAX_BUFFER_SIZE 256

// include all functions
extern void get_devices(GtkWidget *widget, gpointer stack);
extern void reboot_GUI(GtkWidget *widget, gpointer stack);
extern void config_projekt_GUI(GtkWidget *widget, gpointer stack);
extern void preflash_GUI(GtkWidget *widget, gpointer stack);
extern void flash_GUI(GtkWidget *widget, gpointer stack);
extern void instruction_GUI(GtkWidget *widget, gpointer stack);
extern void info();
extern void updater(GtkWidget *widget, gpointer stack);
extern void treble_updater(GtkWidget *widget, gpointer stack);
extern void about();
extern void make_dir();

extern void run_first_run_setup(GtkWidget *widget, gpointer stack);
extern void post_update();

// for the main window
GtkWindow *main_window = NULL;

// start info-function
static void start_info(GtkWidget *widget, gpointer stack) 
{
    info();
}

// labels
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
        strcpy(labels[7], "Treble Updater");
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
        strcpy(labels[6], "Infos");
        strcpy(labels[7], "Treble Updater");
        strcpy(labels[8], "Über das Programm");
    }
}

// function that show the fastboot-assistant window
static void activate_fastboot_assistant(GtkApplication* app, gpointer user_data)
{
	LOG_INFO("activate_fastboot_assistant");
    
    // init GTK
    gtk_init();
    // new mainloop 
    main_loop = g_main_loop_new(NULL, FALSE);
    // get theme and language
    apply_theme();
    apply_language();

	// run post update function
	post_update();
	
	// function that check if the setup run the first time
    // the crazy output came from the experiment with this
    const char *content = "Fisch";
	char fish_path[2048];
	char setup_dir[2048];
	char setup_file[2048];
	char setup_info[2048];
	
	// get config path
	get_config_dir(fish_path, sizeof(fish_path));
	snprintf(setup_dir, sizeof(setup_dir), "%s/config", fish_path);
	LOG_INFO("Config path: %s", setup_dir);
	// create dir 
	create_directory(setup_dir);
	
	// create config file
	snprintf(setup_file, sizeof(setup_file), "%s/config.txt", setup_dir);
	
	LOG_INFO("Get setup info");
	FILE *file;
	
	// check if file exsists
	if ((file = fopen(setup_file, "r")) != NULL) 
	{
    	// file exsists
    	fclose(file);
    	snprintf(setup_info, sizeof(setup_info), "old_fish");
    	LOG_INFO("old fish!");
	} 
	
	else 
	{
	    // remove logic and give this to the first setup
	    // file not exsists
    	file = fopen(setup_file, "w");
    	if (file == NULL) 
    	{
    	    LOG_ERROR("Could not create the file.");
    	    exit(1);  // close the program if there are errors
    	}
    	fprintf(file, "%s", content);
    	fclose(file);
    	snprintf(setup_info, sizeof(setup_info), "fish");
    	LOG_INFO("fish");
	}
	 
    // create the main window
    main_window = GTK_WINDOW(gtk_window_new());
    gtk_window_set_title(GTK_WINDOW(main_window), "Fastboot-Assistant");
    gtk_window_set_default_size(GTK_WINDOW(main_window),  WINDOW_WIDTH, WINDOW_HEIGHT);
	
    // signal to close the application
    g_signal_connect(main_window, "destroy", G_CALLBACK(on_window_destroy), main_loop);

	char labels[9][30];  // labels for the button 
    set_button_labels(labels);  // for both languages
    
    // create a box container for the main content
    GtkWidget *content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(main_window), content_box);
    gtk_widget_set_halign(content_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(content_box, GTK_ALIGN_CENTER);

    // create the stack for navigation
    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    gtk_stack_set_transition_duration(GTK_STACK(stack), 300);
    gtk_box_append(GTK_BOX(content_box), stack);

    // create the home page
	GtkWidget *home_page = gtk_grid_new();
	gtk_grid_set_row_homogeneous(GTK_GRID(home_page), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(home_page), TRUE);
    gtk_widget_set_halign(home_page, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(home_page, GTK_ALIGN_CENTER);
    
    // create the button with the labels
    GtkWidget *btn1 = create_nav_button(labels[0], G_CALLBACK(get_devices), stack);
    GtkWidget *btn2 = create_nav_button(labels[1], G_CALLBACK(reboot_GUI), stack);
    GtkWidget *btn3 = create_nav_button(labels[2], G_CALLBACK(config_projekt_GUI), stack);
    GtkWidget *btn4 = create_nav_button(labels[3], G_CALLBACK(preflash_GUI), stack);
    GtkWidget *btn5 = create_nav_button(labels[4], G_CALLBACK(flash_GUI), stack);
    GtkWidget *btn6 = create_nav_button(labels[5], G_CALLBACK(instruction_GUI), stack);
    GtkWidget *btn7 = create_nav_button(labels[6], G_CALLBACK(start_info), stack);
    GtkWidget *btn8 = create_nav_button(labels[7], G_CALLBACK(treble_updater), stack);
    GtkWidget *btn9 = create_nav_button(labels[8], G_CALLBACK(about), stack);
    // add the button to the grid 
    // line 1 (0)
    gtk_grid_attach(GTK_GRID(home_page), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(home_page), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(home_page), btn3, 2, 0, 1, 1);
    // line 2 (1)
    gtk_grid_attach(GTK_GRID(home_page), btn4, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(home_page), btn5, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(home_page), btn6, 2, 1, 1, 1);
    // line 3 (2)
    gtk_grid_attach(GTK_GRID(home_page), btn7, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(home_page), btn8, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(home_page), btn9, 2, 2, 1, 1);
    
    // add grid to the stack and show it
    gtk_stack_add_named(GTK_STACK(stack), home_page, "home_page");
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "home_page");
    
    // add grid to the main box
	//gtk_box_append(GTK_BOX(content_box), home_page);
	
    gtk_window_present(GTK_WINDOW(main_window)); // gtk_window_present instead of gtk_widget_show
	
	// function that run setup or not
	if (g_strcmp0(setup_info, "fish") == 0) 
    {
		LOG_INFO("run setup");
		set_mode_by_libadwaita();
		// run setup
    	run_first_run_setup(GTK_WIDGET(main_window), stack);
    	LOG_INFO("Setup completed.");
    }
    
    else 
    {
    	LOG_INFO("no setup");
    }
    
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
	
	// delete the old if it exsits ab_device.txt
	check_ab_file_light();
	
	LOG_INFO("end activate_fastboot_assistant");
}

/* main function - GUI */ //background-color: #000000;
int main(int argc, char *argv[]) 
{
	// start writing the log
	write_log();
    LOG_INFO("start fastboot-assistant\n");
	GtkApplication *app;
    int status;

    app = gtk_application_new("io.github.nachtsternbuild.Fastboot-Assistant", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK (activate_fastboot_assistant), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    LOG_INFO("end fastboot-assistant\n\n");
    return status;
}
