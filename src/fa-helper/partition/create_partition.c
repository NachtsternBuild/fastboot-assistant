/**
* create_partition.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

char partition_command_c[2048];
// global int for the output
int number_partition_c = 0;
char *current_partition = NULL;

// function that get the number of the dialog
void get_number_partition_c(const gchar *text, gpointer user_data)
{
    const gchar *input = text;
    gint number_partition_c;
    
	char *endptr;
	long temp_long;

	// convert string to int
	temp_long = strtol(input, &endptr, 10); 

	// error checks
	if (*endptr == '\0' && input != endptr) 
	{
    	// success
    	number_partition_c = (gint)temp_long; // cast from long to gint
    	LOGD("Successfully converted: %d", number_partition_c);
	} 
	
	else 
	{
    	// error
    	LOGE("Error during conversion or invalid characters found.");
    	return;
	}
    
    // get the fastboot-command
    auto_free char *device_command = fastboot_command(); 

    LOGI("Sizeof the new partition: %d", number_partition_c);
    
    const char *title = _("Partitions");
    const char *message = _("Creating partition...");
       
    // for a/b-devices
    if (g_strcmp0(detected_device, "ab_device") == 0) 
	{
		LOGD("a/b-device");
		// create the command
    	snprintf(partition_command_c, sizeof(partition_command_c), "%s create-logical-partition %s_a %d && %s create-logical-partition %s_b %d", device_command, current_partition, number_partition_c, device_command, current_partition, number_partition_c);
    	
    	// run the command
    	LOGD("Run: %s", partition_command_c);    	
    	show_spinner_dialog(GTK_WIDGET(main_window), title, message, partition_command_c);
    }
    // for only-a-devices
    else if (g_strcmp0(detected_device, "only_a") == 0)
    {
    	LOGD("only-a-device");
    	// create the command
    	snprintf(partition_command_c, sizeof(partition_command_c), "%s create-logical-partition %s %d", device_command, current_partition, number_partition_c);
    	
    	// run the command
    	LOGD("Run: %s", partition_command_c);
    	show_spinner_dialog(GTK_WIDGET(main_window), title, message, partition_command_c);
    }
    
    // errors with getting the device info
	else
	{
    	LOGE("Error recognizing the slot/device.");
	}
	
	g_free(current_partition);
}

// function that create a partition
void create_partition(const char *partition)
{
	LOGI("Create partition %s", partition);
	
	// copy the current partition
	current_partition = g_strdup(partition);
	
	// prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    // text for the entry
    const char *dialog_entry_title = _("Creat Partition");
    const char *dialog_message = _("Enter the partition size:");
    const char *dialog_label = _("Partition Size:");
         
    show_entry_dialog(GTK_WIDGET(main_window),
                            dialog_entry_title,
                            dialog_message,
                            _("Confirm"),
                            _("Cancel"),
                            dialog_label,
                            "10000000",
                            get_number_partition_c,
                            NULL);
         	
	LOGD("End create %s", partition);
}
