/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *       Headerfile - program_functions		 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>

#ifndef PROGRAM_FUNCTIONS_H
#define PROGRAM_FUNCTIONS_H

#define WINDOW_WIDTH 750
#define WINDOW_HEIGHT 600

/* global variables that are used in each file */
// for the css-provider
extern GtkCssProvider *provider;

// global use of the theme 
extern const char *current_theme;

// and the language
extern const char *language;

// for GTK main loop
extern GMainLoop *main_loop;

/* function from the header */
// destroy window/dialog/loops
// end  GTK main loop
void on_window_destroy(GtkWidget *widget, gpointer data);

// close window
void close_window(GtkButton *button, GtkWidget *window);

// close dialog
void close_dialog(GtkButton *button, GtkWidget *dialog);

// close window and mainloop
void close_window_mainloop(GtkWidget *widget, gpointer data);

// execute command
char *execute_command();

// messages
void show_message();
void show_message_with_title();
void open_terminal_by_desktop();
void show_error_message();

// check and get the slot
int get_slot_of_device();
void check_active_slot();

// get devices
void get_info();
int is_android_device_connected();
void connected_devices();
void get_android_info();

// show file chooser
void show_file_chooser(GtkWidget *widget, gpointer data);

// get home
gchar* get_home(const gchar *path);
const char* get_home_directory_flash();

// open url in browser
void open_url();

// for work with dirs or WSL
void set_main_dir();
void get_wsl_directory(char* wsl_dir, size_t size);
void set_main_dir_with_wsl(char *path, size_t size, const char *filename);
void convert_wsl_path(char *windows_path, size_t size, const char *wsl_path);
int directory_exists(const char *path);
void delete_files_in_dir();

// delete config file
void delete_config_file();


// flash functions
void flash_image(GtkWidget *widget, GtkWindow *parent_window, const char *partition1, const char *partition2, const char *image_name);
void flash_heimdall(GtkWidget *widget, GtkWindow *parent_window, const char *partition, const char *image_name);

// button connection for UI
void next_page(GtkButton *button, gpointer data);
// void button_finish(GtkButton *button, gpointer data);

// adb/fastboot command
char* adb_command();
char* fastboot_command();

// everything for the css provider
void add_css_provider(GtkWidget *widget, GtkCssProvider *provider);
void load_css(const char *theme);
void toggle_theme(GtkWidget *button, gpointer user_data);
void apply_theme();
void write_dark_file();
void check_dark_file();
void check_dark_file_light();

// functions with spinner
//void install_with_root(GtkButton *button, GtkEntry *password_entry, const gchar *command);
void command_with_spinner(const gchar *command);

// function with pkexec
void install_with_pkexec(const gchar *command);

// for setup
void config_start();
void config_dir_setup(const char *pfad); 

#endif
