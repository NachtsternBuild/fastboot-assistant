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
 *         Headerpart - remove_partition	 *
 *											 *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"
#include "function_header.h"

char partition_command_rm[2048];

// function that remove a partition
void remove_partition(const char *partition)
{
	LOG_INFO("Remove partition: %s", partition);
	
	apply_language();
	apply_device();
	
	const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);
    // get the fastboot-command
    auto_free char *device_command = fastboot_command();  
        
	// for a/b-devices
	if (g_strcmp0(detected_device, "ab_device") == 0) 
	{
    	LOG_INFO("a/b-device");
    	snprintf(partition_command_rm, sizeof(partition_command_rm), "%s delete-logical-partition %s_a && %s delete-logical-partition %s_b", device_command, partition, device_command, partition);
    	
    	// run the command
    	LOG_INFO("Run: %s", partition_command_rm);
    	command_with_spinner(partition_command_rm);
	} 
	// only-a-devices
	else if (g_strcmp0(detected_device, "only_a") == 0)  
	{
    	LOG_INFO("only-a-device");
    	snprintf(partition_command_rm, sizeof(partition_command_rm), "%s delete-logical-partition %s", device_command, partition);
    	
    	// run the command
    	LOG_INFO("Run: %s", partition_command_rm);
    	command_with_spinner(partition_command_rm);
	}
	
	// errors with getting the device info
	else
	{
    	LOG_ERROR("Error recognizing the slot/device.");
	}
	
    LOG_INFO("End Remove %s", partition);
}
