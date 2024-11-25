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
 *         Headerpart - check_active_slot	 *
 *											 *
 *-------------------------------------------*
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

#define BUFFER_SIZE 2048

// function that get the active slot
void check_active_slot(char *active_slot, size_t size) 
{
    char buffer[BUFFER_SIZE];
    FILE *pipe;

    // fastboot-command for the boot-slot
    char *device_command = fastboot_command();
    char command[BUFFER_SIZE];
    snprintf(command, BUFFER_SIZE, "%s getvar current-slot 2>&1", device_command);

    // open pipe and run command
    pipe = popen(command, "r");
    if (!pipe) 
    {
        fprintf(stderr, "Log: Could not open the pipe.\n");
        free(device_command);
        exit(EXIT_FAILURE);
    }

    // reading output
    while (fgets(buffer, BUFFER_SIZE, pipe) != NULL) 
    {
        char *pos = strstr(buffer, "current-slot:");
        if (pos) 
        {
            sscanf(pos, "current-slot: %s", active_slot);
            break;
        }
    }

    // close pipe
    pclose(pipe);
    free(device_command);
    // the slot
    g_print("Log: current-slot: %s\n", active_slot);
}
