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

// function that check if the device are a/b-device
int get_slot_of_device() 
{
    FILE *fp;
    char result[2048];

    // fastboot-command for the boot slot
    auto_free char *device_command = fastboot_command();
    char command[BUFFER_SIZE];
    snprintf(command, BUFFER_SIZE, "%s getvar slot-count 2>&1", device_command);

    // run command that check for a/b device
    fp = popen(command, "r");
    if (fp == NULL) 
    {
        LOG_ERROR("Failed to run command.");
        free(device_command);
        exit(1);
    }

    // read the output
    int ab_device = 0;
    while (fgets(result, sizeof(result)-1, fp) != NULL) 
    {
        if (strstr(result, "slot-count") && strstr(result, "2")) 
        {
            ab_device = 1;
            break;
        }
    }
	
	// close the pipe
    pclose(fp);
    return ab_device;
}
