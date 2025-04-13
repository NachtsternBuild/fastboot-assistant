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

// function that get the number of the dialog
void get_number_partition_c(int number) 
{
    number_partition_c = number;
    LOG_INFO("Sizeof the new partition: %d", number);
}

// function that create a partition
void create_partition(const char *partition)
{
	LOG_INFO("Create partition %s", partition);
	
	apply_language();
	
	const char *message = strcmp(language, "de") == 0 ? "Manche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise." : "Some chipsets do not support this process in this way.";
    // show message
    show_message(message);
    
    // text for the entry
    const char *dialog_entry_title = strcmp(language, "de") == 0 ? "Neue Partitionsgröße" : "New Partition Size";
    const char *dialog_entry = strcmp(language, "de") == 0 ? "Partitionsgröße (in kB):" : "Partition Size (in kB)";
    // get the fastboot-command
    auto_free char *device_command = fastboot_command(); 
    
    // get the info of the partitions
	int info_ab_c = ab_partition_info();
      
	// for a/b-devices
	if (info_ab_c == AB_DEVICE) 
	{
    	LOG_INFO("a/b-device");
    	// dialog with entry
    	show_dialog_with_entry(dialog_entry_title, dialog_entry, get_number_partition_c);
    	LOG_INFO("Change partition size to: %d", number_partition_c);
    	
    	// create the command
    	snprintf(partition_command_c, sizeof(partition_command_c), "%s create-logical-partition %s_a %d && %s create-logical-partition %s_b %d", device_command, partition, number_partition_c, device_command, partition, number_partition_c);
    	
    	// run the command
    	LOG_INFO("Run: %s", partition_command_c);
    	command_with_spinner(partition_command_c);
	}
	 
	// only-a-devices
	else if (info_ab_c == NOT_AB_DEVICE) 
	{
    	LOG_INFO("only-a-device");
    	// dialog with entry
    	show_dialog_with_entry(dialog_entry_title, dialog_entry, get_number_partition_c);
    	LOG_INFO("Change partition size to: %d", number_partition_c);
    	
    	// create the command
    	snprintf(partition_command_c, sizeof(partition_command_c), "%s create-logical-partition %s %d", device_command, partition, number_partition_c);
    	
    	// run the command
    	LOG_INFO("Run: %s", partition_command_c);
    	command_with_spinner(partition_command_c);
	}
	
	// errors with getting the device info
	else if (info_ab_c == AB_DEVICE_ERROR) 
	{
    	LOG_ERROR("Error recognizing the slot/device.");
	}
	LOG_INFO("End resize %s", partition);
}
