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
 *       Headerpart - ab_partition_info		 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// function that check the device for a/b partition or not
void ab_partition_info() 
{
    auto_free char *device_command = fastboot_command();
    char output_command[256];
    // get the current slot
    snprintf(output_command, sizeof(output_command), "%s getvar current-slot 2>&1", device_command);
    char *output = execute_command(output_command);
	
	// errors
    if (output == NULL) 
    {
        LOG_ERROR("Error when executing the command.");
        LOG_ERROR("Command: %s", output_command);
        LOG_ERROR("Device type not detected.");
    }

    // remove the \n 
    output[strcspn(output, "\n")] = 0;
	
	// Comparison a/b - only-a
    // a/b device
    if (strcmp(output, "_b") == 0 || strcmp(output, "_a") == 0 || strcmp(output, "a") == 0 || strcmp(output, "b") == 0) 
    {
        LOG_INFO("a/b-device found.");
        write_ab_file();
    } 
    // only-a-device 
    else 
    {
        LOG_INFO("Only-a device found.");
		check_ab_file_light();
    }

	// free the memory
	LOG_INFO("Freeing ouput.");
    free(output); 
}

