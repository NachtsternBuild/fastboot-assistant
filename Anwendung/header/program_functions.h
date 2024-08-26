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

extern GtkCssProvider *provider;

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
void css_provider();
void next_page(GtkButton *button, gpointer data);

#endif
