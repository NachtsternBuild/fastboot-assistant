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
 *      (C) Copyright 2025 Elias Mörz        *
 *-------------------------------------------*
 *                                           *
 *         Headerpart - on_window_destroy    *
 *                                           *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

//GMainLoop *main_loop = NULL; 

// function to end the gtk mainloop
void on_window_destroy(GtkWidget *widget, gpointer data) 
{
    LOG_INFO("Close window, end main loop.");
    g_main_loop_quit((GMainLoop *)data); // end mainloop
}
