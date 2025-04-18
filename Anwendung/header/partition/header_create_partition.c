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
 *         Headerpart - create_partition	 *
 *											 *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"
#include "function_header.h"

char partition_command_c[2048];
// global int for the output
int number_partition_c = 0;
char *current_partition = NULL;

// function that get the number of the dialog
void get_number_partition_c(int number) 
{
    // get the fastboot-command
    auto_free char *device_command = fastboot_command(); 
    // set the partition size
    number_partition_c = number;
    LOG_INFO("Sizeof the new partition: %d", number);
    // for a/b-devices
    if (g_strcmp0(detected_device, "ab_device") == 0) 
	{
		LOG_INFO("a/b-device");
		// create the command
    	snprintf(partition_command_c, sizeof(partition_command_c), "%s create-logical-partition %s_a %d && %s create-logical-partition %s_b %d", device_command, current_partition, number_partition_c, device_command, current_partition, number_partition_c);
    	
    	// run the command
    	LOG_INFO("Run: %s", partition_command_c);
    	command_with_spinner(partition_command_c);
    }
    // for only-a-devices
    else if (g_strcmp0(detected_device, "only_a") == 0)
    {
    	LOG_INFO("only-a-device");
    	// create the command
    	snprintf(partition_command_c, sizeof(partition_command_c), "%s create-logical-partition %s %d", device_command, current_partition, number_partition_c);
    	
    	// run the command
    	LOG_INFO("Run: %s", partition_command_c);
    	command_with_spinner(partition_command_c);
    }
    
    // errors with getting the device info
	else
	{
    	LOG_ERROR("Error recognizing the slot/device.");
	}
	
	g_free(current_partition);
}
// function that create a partition
void create_partition(const char *partition)
{
	LOG_INFO("Create partition %s", partition);
	
	apply_language();
	apply_device();
	
	// copy the current partition
	current_partition = g_strdup(partition);
	
	const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);
    
    // text for the entry
    const char *dialog_entry_title = strcmp(language, "de") == 0 ? "Neue Partitionsgröße" : "New Partition Size";
    const char *dialog_entry = strcmp(language, "de") == 0 ? "Partitionsgröße (in kB):" : "Partition Size (in kB)";
         
   	show_dialog_with_entry(dialog_entry_title, dialog_entry, get_number_partition_c);
	
	LOG_INFO("End create %s", partition);
}
