/**
* connected_devices.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

void connected_devices(const char *command, const char *label) 
{
    if (debug_mode) 
    {
        g_print("[DEBUG] Security check skipped.\n");
        return;
    }
        
    char message[2048];
    FILE *fp;

    // execute the command and capture the output
    fp = popen(command, "r");
    if (fp == NULL) 
    {
        LOGE("Error when opening the process!");
        exit(1);
    }

    // read the output and display it in the message
    snprintf(message, sizeof(message), "%s:\n", label);
    while (fgets(message + strlen(message), sizeof(message) - strlen(message), fp) != NULL) {}

    // show the message
    show_info_dialog(GTK_WIDGET(main_window), message);

    // Close the process
    pclose(fp);
}

// check if device are connected
int is_android_device_connected() 
{
    if (debug_mode) 
    {
        g_print("[DEBUG] Security check skipped.\n");
        return 1;
    }
    
    // check for adb device
    auto_free char *adb_cmd = adb_command();     
    
    char *adb_check[] = {
    	adb_cmd,
    	"devices",
    	"|",
    	"grep",
    	"-w",
    	"'device'",
    	NULL
    };
    char *adb_output = execute_command(adb_check);

    if (adb_output != NULL && strlen(adb_output) > 0) 
    {
        return 1;  // adb device 
    }

    // check for fastboot device
    auto_free char *fastboot_cmd = fastboot_command();
    
    char *fastboot_check[] = {
    	fastboot_cmd,
    	"devices",
    	"|",
    	"grep",
    	"-w",
    	"'fastboot'",
    	NULL
    };
    char *fastboot_output = execute_command(fastboot_check);

    if (fastboot_output != NULL && strlen(fastboot_output) > 0) 
    {
        return 1;  // fastboot device
    }

    return 0;  // no device
}

// check for device in fastboot
int is_android_device_connected_fastboot()
{
	if (debug_mode) 
    {
        g_print("[DEBUG] Security check skipped.\n");
        return 1;
    }
	
	auto_free char *info_command = fastboot_command();
	
	char *fastboot_check[] = {
    	info_command,
    	"devices",
    	"|",
    	"grep",
    	"-w",
    	"'fastboot'",
    	NULL
    };
    char *fastboot_output = execute_command(fastboot_check);

    if (fastboot_output != NULL && strlen(fastboot_output) > 0) 
    {
        return 1;  // fastboot device
    }

    return 0;  // no device
}

// check for device in adb
int is_android_device_connected_adb()
{
	if (debug_mode) 
    {
        g_print("[DEBUG] Security check skipped.\n");
        return 1;
    }
	
	auto_free char *info_command = adb_command();
	
	char *adb_check[] = {
    	info_command,
    	"devices",
    	"|",
    	"grep",
    	"-w",
    	"'device'",
    	NULL
    };
    char *adb_output = execute_command(adb_check);

    if (adb_output != NULL && strlen(adb_output) > 0) 
    {
        return 1;  // fastboot device
    }

    return 0;  // no device
}
