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
 *         Headerpart - resize_partition	 *
 *											 *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"
#include "function_header.h"

char partition_command_rs[2048];
// global int for the output
int number_partition_rs = 0;
char *current_partition_rs = NULL;

// function that get the number of the dialog
void get_number_partition_rs(int number) 
{
    number_partition_rs = number;
     // get the fastboot-command
    auto_free char *device_command = fastboot_command(); 
    
    LOG_INFO("Sizeof the new partition: %d", number);
    // for a/b-devices
    if (g_strcmp0(detected_device, "ab_device") == 0) 
	{
		LOG_INFO("a/b-device");
		// create the command
    	snprintf(partition_command_rs, sizeof(partition_command_rs), "%s resize-logical-partition %s_a %d && %s resize-logical-partition %s_b %d", device_command, current_partition_rs, number_partition_rs, device_command, current_partition_rs, number_partition_rs);
    	
    	// run the command
    	LOG_INFO("Run: %s", partition_command_rs);
    	command_with_spinner(partition_command_rs);
    }
    // for only-a-devices
    else if (g_strcmp0(detected_device, "only_a") == 0)
    {
    	LOG_INFO("only-a-device");
    	// create the command
    	snprintf(partition_command_rs, sizeof(partition_command_rs), "%s resize-logical-partition %s %d", device_command, current_partition_rs, number_partition_rs);
    	
    	// run the command
    	LOG_INFO("Run: %s", partition_command_rs);
    	command_with_spinner(partition_command_rs);
    }
    
    // errors with getting the device info
	else
	{
    	LOG_ERROR("Error recognizing the slot/device.");
	}
	
	g_free(current_partition_rs);
}
// function resize the partition
void resize_partition(const char *partition)
{
	LOG_INFO("Resize partition: %s", partition);
	
	apply_language();
	apply_device();
	
	// copy the current partition
	current_partition_rs = g_strdup(partition);
	
	const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);
    
    // text for the entry
    const char *dialog_entry_title = strcmp(language, "de") == 0 ? "Neue Partitionsgröße" : "New Partition Size";
    const char *dialog_entry = strcmp(language, "de") == 0 ? "Partitionsgröße (in kB):" : "Partition Size (in kB)";
         
   	show_dialog_with_entry(dialog_entry_title, dialog_entry, get_number_partition_rs);
	
	LOG_INFO("End resize %s", partition);
}
