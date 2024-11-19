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
 *       Headerpart - install_with_pkexec    *
 *                                           *
 *-------------------------------------------*
 */

/* headers */ 
#include <glib.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// function to run a command via root use pkexec
void install_with_pkexec(const gchar *command)
{
    gchar *full_command = g_strdup_printf("pkexec %s", command);
    g_print("Log: %s\n", full_command);
    system(full_command);
    g_free(full_command);
}

