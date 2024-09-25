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
#define WINDOW_HEIGHT 400

extern GtkCssProvider *provider;
// global use of the theme 
extern const char *current_theme;

void delete_files_in_dir();
char *execute_command();
void show_message();
void open_terminal_by_desktop();
void connected_devices();
int get_slot_of_device();
void check_active_slot();
void show_message_with_title();
int get_slot_of_device();
void get_info();
void show_file_chooser(GtkWidget *widget, gpointer data);
gchar* get_home(const gchar *path);
void open_url();
void set_main_dir();
const char* get_home_directory_flash();
void get_wsl_directory(char* wsl_dir, size_t size);
void set_main_dir_with_wsl(char *path, size_t size, const char *filename);
void show_error_message(GtkWidget *parent_window, const char *message);
void flash_image(GtkWidget *widget, GtkWindow *parent_window, const char *partition1, const char *partition2, const char *image_name);
void flash_heimdall(GtkWidget *widget, GtkWindow *parent_window, const char *partition, const char *image_name);
void next_page(GtkButton *button, gpointer data);
void button_finish(GtkButton *button, gpointer data);
void convert_wsl_path(char *windows_path, size_t size, const char *wsl_path);
int directory_exists(const char *path);
char* adb_command();
char* fastboot_command();
// everything for the css provider
void add_css_provider(GtkWidget *widget, GtkCssProvider *provider);
void add_css_provider_blue(GtkWidget *widget, GtkCssProvider *darkblue_provider);
void load_css(const char *theme);
void load_css_blue(const char *theme);
void toggle_theme(GtkWidget *button, gpointer user_data);
void apply_theme();
void write_dark_file();
void check_dark_file();
void check_dark_file_light();
// functions with spinner
void install_with_root(GtkButton *button, GtkEntry *password_entry, const gchar *command);
void command_with_spinner(const gchar *command);

#endif
