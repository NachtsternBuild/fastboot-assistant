/**
* resize_partition.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

char partition_command_rs[2048];
// global int for the output
int number_partition_rs = 0;
char *current_partition_rs = NULL;

// function that get the number of the dialog
void get_number_partition_rs(const gchar *text, gpointer user_data) 
{
    const gchar *input = text;
    gint number_partition_rs;
    
	char *endptr;
	long temp_long;

	// convert string to int
	temp_long = strtol(input, &endptr, 10); 

	// error checks
	if (*endptr == '\0' && input != endptr) 
	{
    	// success
    	number_partition_rs = (gint)temp_long; // cast from long to gint
    	LOGD("Successfully converted: %d", number_partition_rs);
	} 
	
	else 
	{
    	// error
    	LOGE("Error during conversion or invalid characters found.");
    	return;
	}
     // get the fastboot-command
    auto_free char *device_command = fastboot_command(); 
    
    LOGI("Sizeof the new partition: %d", number_partition_rs);
        
    const char *title = _("Partitions");
    const char *message = _("Resizing partition...");
        
    // for a/b-devices
    if (g_strcmp0(detected_device, "ab_device") == 0) 
	{
		LOGD("a/b-device");
		// create the command
    	snprintf(partition_command_rs, sizeof(partition_command_rs), "%s resize-logical-partition %s_a %d && %s resize-logical-partition %s_b %d", device_command, current_partition_rs, number_partition_rs, device_command, current_partition_rs, number_partition_rs);
    	
    	// run the command
    	LOGD("Run: %s", partition_command_rs);
    	show_spinner_dialog(GTK_WIDGET(main_window), title, message, partition_command_rs);
    }
    // for only-a-devices
    else if (g_strcmp0(detected_device, "only_a") == 0)
    {
    	LOGD("only-a-device");
    	// create the command
    	snprintf(partition_command_rs, sizeof(partition_command_rs), "%s resize-logical-partition %s %d", device_command, current_partition_rs, number_partition_rs);
    	
    	// run the command
    	LOGD("Run: %s", partition_command_rs);
    	show_spinner_dialog(GTK_WIDGET(main_window), title, message, partition_command_rs);
    }
    
    // errors with getting the device info
	else
	{
    	LOGE("Error recognizing the slot/device.");
	}
	
	g_free(current_partition_rs);
}
// function resize the partition
void resize_partition(const char *partition)
{
	LOGI("Resize partition: %s", partition);
	
	// copy the current partition
	current_partition_rs = g_strdup(partition);
	
	// prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    // text for the entry
    const char *dialog_entry_title = _("Resize Partition");
    const char *dialog_message = _("Enter the partition size:");
    const char *dialog_label = _("Partition Size:");
         
    show_entry_dialog(GTK_WIDGET(main_window),
                            dialog_entry_title,
                            dialog_message,
                            _("Confirm"),
                            _("Cancel"),
                            dialog_label,
                            "10000000",
                            get_number_partition_rs,
                            NULL);
         	
	LOGD("End resize %s", partition);
}
