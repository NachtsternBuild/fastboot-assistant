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
 *       Headerpart - install_with_root		 *
 *											 *
 *-------------------------------------------*
 */

/* headers */ 
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

void install_with_root(GtkButton *button, GtkEntry *password_entry, const gchar *command) 
{
    const gchar *password = gtk_entry_get_text(password_entry);
    gchar *full_command = g_strdup_printf("echo %s | sudo -S %s", password, command);

    // run command in terminal
    int status = system(full_command);

    // close the window after the process
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(window);

    g_free(full_command);
}

