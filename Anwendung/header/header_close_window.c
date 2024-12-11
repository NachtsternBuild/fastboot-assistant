/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *      Apache License, Version 2.0          *
 *-------------------------------------------*
 *                                           *
 *  Programm um das Installieren von         *
 *  Custom-ROM und GSIs auf Android-Geräte   *
 *  zu erleichtern                           *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz        *
 *-------------------------------------------*
 *                                           *
 *              Headerpart - close_window    *
 *                                           *
 *-------------------------------------------*
 */

/* headers */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// close dialog
void close_dialog(GtkButton *button, GtkWidget *dialog) 
{
    gtk_window_destroy(GTK_WINDOW(dialog));
    //gtk_window_close(GTK_WINDOW(dialog));
}

// close window
void close_window(GtkButton *button, GtkWidget *window) 
{
    gtk_window_destroy(GTK_WINDOW(window));
    //gtk_window_close(GTK_WINDOW(window));
}

// close window
void close_window_mainloop(GtkWidget *widget, gpointer data) 
{
    GtkWidget *window = GTK_WIDGET(data);
    g_print("Log: Close window, end main loop.\n");
    gtk_window_destroy(GTK_WINDOW(window));
    g_main_loop_quit(main_loop);
}

