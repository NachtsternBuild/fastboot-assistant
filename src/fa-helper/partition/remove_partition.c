/**
* remove_partition.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

char partition_command_rm[2048];

// function that remove a partition
void remove_partition(const char *partition)
{
	LOGI("Remove partition: %s", partition);
	
	// prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    // get the fastboot-command
    auto_free char *device_command = fastboot_command();  
    
    const char *title = _("Partitions");
    const char *message = _("Removing partition...");
    
	// for a/b-devices
	if (g_strcmp0(detected_device, "ab_device") == 0) 
	{
    	LOGD("a/b-device");
    	snprintf(partition_command_rm, sizeof(partition_command_rm), "%s delete-logical-partition %s_a && %s delete-logical-partition %s_b", device_command, partition, device_command, partition);
    	
    	// run the command
    	LOGD("Run: %s", partition_command_rm);
    	show_spinner_dialog(GTK_WIDGET(main_window), title, message, partition_command_rm);
	} 
	// only-a-devices
	else if (g_strcmp0(detected_device, "only_a") == 0)  
	{
    	LOGD("only-a-device");
    	snprintf(partition_command_rm, sizeof(partition_command_rm), "%s delete-logical-partition %s", device_command, partition);
    	
    	// run the command
    	LOGD("Run: %s", partition_command_rm);
    	show_spinner_dialog(GTK_WIDGET(main_window), title, message, partition_command_rm);
	}
	
	// errors with getting the device info
	else
	{
    	LOGE("Error recognizing the slot/device.");
	}
	
    LOGD("End Remove %s", partition);
}
