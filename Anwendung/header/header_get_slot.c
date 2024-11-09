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
 *         Headerpart - get_slot			 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "function_header.h"

#define BUFFER_SIZE 2048

int get_slot_of_device() 
{
    FILE *fp;
    char result[2048];
	
	// fastboot-command for get boot-slots
    char *device_command = fastboot_command();
    char command[BUFFER_SIZE];
    snprintf(command, BUFFER_SIZE, "%s getvar current-slot 2>&1", device_command);
    
    // Execute the command to check for A/B partition scheme
    fp = popen(command, "r");
    if (fp == NULL) 
    {
        fprintf(stderr, "Log: Failed to run command\n" );
        exit(1);
    }

    // Read the output
    while (fgets(result, sizeof(result)-1, fp) != NULL) 
    {
        if (strstr(result, "slot-count") && strstr(result, "2")) 
        {
            pclose(fp);
            return 1;
        }
    }

    pclose(fp);
    free(device_command);
    return 0;
}
