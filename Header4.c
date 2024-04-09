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
 *              Headerpart - start_terminal	 *
 *											 *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For chdir()
#include <errno.h>  // For perror()
#include <string.h> // For strlen()

#define MAX_FILENAME_LENGTH 256

void start_terminal(const char *command)
{
    char terminal_command[MAX_FILENAME_LENGTH + 50]; // +50 for the space needed by gnome-terminal command
    snprintf(terminal_command, sizeof(terminal_command), "gnome-terminal -- bash -c \"%s; exec bash\"", command);
    system(terminal_command);
}

