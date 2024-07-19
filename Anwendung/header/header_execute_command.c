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
 *              Headerpart - run command	 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

// Function to execute a command and capture its output
char *execute_command(const char *command) 
{
    FILE *fp;
    char buffer[128];
    char *result = NULL;

    fp = popen(command, "r");
    if (fp == NULL) 
    {
        perror("Fehler beim Ausführen des Befehls.\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) 
    {
        result = strdup(buffer);
    }

    pclose(fp);

    return result;
}

