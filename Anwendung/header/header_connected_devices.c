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
 *         Headerpart - connected_devices	 *
 *											 *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

void connected_devices(const char *command, const char *label) 
{
    char message[512];
    FILE *fp;

    // Execute the command and capture the output
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Fehler beim Öffnen des Prozesses!");
        exit(EXIT_FAILURE);
    }

    // Read the output and display it in the message
    snprintf(message, sizeof(message), "%s:\n", label);
    while (fgets(message + strlen(message), sizeof(message) - strlen(message), fp) != NULL) {}

    // Show the message
    show_message(message);

    // Close the process
    pclose(fp);
}
