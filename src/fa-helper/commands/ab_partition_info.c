/**
* ab_partition.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/

#include "fastboot_assistant.h"

#define BUFFER_SIZE 2048

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
        LOGE("Error when executing the command.");
        LOGE("Command: %s", output_command);
        LOGE("Device type not detected.");
    }

    // remove the \n 
    output[strcspn(output, "\n")] = 0;
	
	// Comparison a/b - only-a
    // a/b device
    if (strcmp(output, "_b") == 0 || strcmp(output, "_a") == 0 || strcmp(output, "a") == 0 || strcmp(output, "b") == 0) 
    {
        LOGD("a/b-device found.");
        write_ab_file();
    } 
    // only-a-device 
    else 
    {
        LOGD("Only-a device found.");
		check_ab_file_light();
    }

	// free the memory
	LOGD("Freeing ouput.");
    free(output); 
}

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
        LOGE("Failed to run command.");
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

// function that get the active slot
void check_active_slot(char *active_slot, size_t size) 
{
    char buffer[BUFFER_SIZE];
    FILE *pipe;

    // fastboot-command for the boot-slot
    auto_free char *device_command = fastboot_command();
    char command[BUFFER_SIZE];
    snprintf(command, BUFFER_SIZE, "%s getvar current-slot 2>&1", device_command);

    // open pipe and run command
    pipe = popen(command, "r");
    if (!pipe) 
    {
        LOGE("Could not open the pipe.");
        free(device_command);
        exit(1);
    }

    // reading output
    while (fgets(buffer, BUFFER_SIZE, pipe) != NULL) 
    {
        char *pos = strstr(buffer, "current-slot:");
        if (pos) 
        {
            sscanf(pos, "current-slot: %s", active_slot);
            break;
        }
    }

    // close pipe
    pclose(pipe);
    // the slot
    LOGD("current-slot: %s", active_slot);
}

// get the active slot with adb
char *get_inactive_slot() 
{
    FILE *fp;
    char slot_command[2048];
    char buffer[128];
    auto_free char *inactive_slot = malloc(4);
    auto_free char *device_command = adb_command();
    if (!inactive_slot) 
    {	
    	return NULL; // if malloc won't work
	}
	
	snprintf(slot_command, sizeof(slot_command), "%s shell getprop ro.boot.slot_suffix", device_command);
	
    fp = popen(slot_command, "r");
    if (!fp) 
    {
        LOGE("Error: Unable to get current slot.\n");
        return NULL;
    }

    if (fgets(buffer, sizeof(buffer), fp) != NULL) 
    {
        if (strstr(buffer, "_a")) 
        {
            strcpy(inactive_slot, "_b");
        }
        
        else if (strstr(buffer, "_b")) 
        {
            strcpy(inactive_slot, "_a");
        }
        
        else 
        {
            inactive_slot = NULL;
        }
    }

    pclose(fp);
    return inactive_slot;
}
