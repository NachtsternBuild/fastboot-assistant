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
#include <glib.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "loading_spinner.h"

GtkWidget *spinner_install = NULL;
GtkWidget *spinner_install_window = NULL;

// Funktion, die den Befehl im Hintergrund ausführt
static gpointer run_command_with_spinner(gpointer data) 
{
    gchar *command = (gchar *)data;
    system(command);
    g_free(command);
    return NULL;
}

// Funktion zum Starten des Spinners und Ausführen des Befehls
void install_with_root(GtkButton *button, GtkEntry *password_entry, const gchar *command) 
{
    const gchar *password = gtk_entry_get_text(password_entry);
    gchar *full_command = g_strdup_printf("echo %s | sudo -S %s", password, command);
	
	start_loading_spinner(spinner_install);  // Start the spinner

    // Befehl in einem separaten Thread ausführen, um die UI nicht zu blockieren
    g_thread_new("command-thread", run_command_with_spinner, full_command);

    stop_loading_spinner(spinner_install);  // Stop the spinner when the process finishes
    
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(window);
    
    gtk_main();
}


