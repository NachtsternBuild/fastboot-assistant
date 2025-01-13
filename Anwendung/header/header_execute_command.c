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
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *         Headerpart - execute_command		 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// Function to execute a command and capture its output
char *execute_command(const char *command) 
{
    FILE *fp;
    char buffer[2048];
    char *result = NULL;

    fp = popen(command, "r");
    if (fp == NULL) 
    {
        LOG_ERROR("Error when executing the command.");
        exit(1);
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) 
    {
        result = strdup(buffer);
    }

    pclose(fp);

    return result;
}

