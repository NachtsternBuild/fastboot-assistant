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
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *       Headerfile - program_functions		 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#ifndef PROGRAM_FUNCTIONS_H
#define PROGRAM_FUNCTIONS_H

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

#endif
