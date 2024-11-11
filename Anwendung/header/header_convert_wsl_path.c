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
 *      Headerpart - convert_wsl_path		 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// Function to convert WSL path to Windows path
void convert_wsl_path(char *windows_path, size_t size, const char *wsl_path) 
{
    char command[2048];
    FILE *fp;

    // Command to convert WSL path to Windows path using wslpath
    snprintf(command, sizeof(command), "wslpath -w '%s'", wsl_path);

    // Open a pipe to read the output of wslpath command
    fp = popen(command, "r");
    if (fp == NULL) 
    {
        g_print("Log: Error: Could not convert the path.\n");
        exit(1);
    }

    // Read the output of wslpath and store it in windows_path
    if (fgets(windows_path, size, fp) == NULL) 
    {
        g_print("Log: Error: Could not read the converted path.\n");
        pclose(fp);
        exit(1);
    }

    // Remove trailing newline character
    windows_path[strcspn(windows_path, "\n")] = '\0';

    pclose(fp);
}

