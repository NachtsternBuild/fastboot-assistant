/**
* flash_image.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// global vars
GtkWidget *spinner_window_flash;
GtkWidget *spinner_flash;

// Usage:
/*
// Flashing the boot partitions for an A/B device (without additional flags)
flash_image(widget, parent_window, "boot_a", "boot_b", "boot.img", NULL);

// Flashing vbmeta with specific flags for Verity and Verification
flash_image(widget, parent_window, "vbmeta", NULL, "vbmeta.img", "--disable-verity --disable-verification");

*/

// list of errors from fastboot
// if you know some others, please add it to this list
const char *check_fastboot_error(const char *fastboot_output)
{
    if (strstr(fastboot_output, "target didn't report max-download-size"))
    {
        return _("Error: Target did not report max-download-size.");
    }
    
    if (strstr(fastboot_output, "FAILED"))
    {
        return _("Error: A general error occurred. Check the log for details.");
    }
    
    if (strstr(fastboot_output, "Invalid sparse file format at header magic"))
    {
        return _("Error: Invalid sparse file format. Please check the image.");
    }
    
    if (strstr(fastboot_output, "Writing 'system' FAILED"))
    {
        return _("Error: Writing to partition 'system' failed. Check the device and connection.");
    }
    
    if (strstr(fastboot_output, "Writing 'system_a' FAILED"))
    {
        return _("Error: Writing to partition 'system' failed. Check the device and connection.");
    }
    
    if (strstr(fastboot_output, "Writing 'system_b' FAILED"))
    {
        return _("Error: Writing to partition 'system' failed. Check the device and connection.");
    }
    
    if (strstr(fastboot_output, "Resizing 'system' FAILED"))
    {
        return _("Error: Resizing partition 'system' failed.");
    }
    
    if (strstr(fastboot_output, "Resizing 'system_a' FAILED"))
    {
        return _("Error: Resizing partition 'system_a' failed.");
    }
    
    if (strstr(fastboot_output, "Resizing 'system_b' FAILED"))
    {
        return _("Error: Resizing partition 'system_a' failed.");
    }
    
    if (strstr(fastboot_output, "Partition not found"))
    {
    	return _("Error: The specified partition was not found. Please check the partition.");
    }
    
    if (strstr(fastboot_output, "timeout"))
    {
    	return _("Error: The connection to Fastboot has expired. Please check the device and USB connection.");
    }
    
    if (strstr(fastboot_output, "Permission denied"))
    {
    	return _("Error: No authorization to execute fastboot command. Please try as root.");
    }
    
    if (strstr(fastboot_output, "device is locked"))
    {
    	return _("Error: The device is locked. Please unlock the bootloader and try again.");
    }
    
    if (strstr(fastboot_output, "remote: Operation not permitted"))
    {
        return _("Error: The operation is not permitted. Please check the device.");
    }
    
    if (strstr(fastboot_output, "Command not allowed"))
    {
        return _("Error: The command is not allowed.");
    }
    
    if (strstr(fastboot_output, "No such file or directory"))
    {
        return _("Error: File or directory not found. Please check path and file.");
    }
    
    if (strstr(fastboot_output, "cannot load"))
    {
        return _("Error: Image could not be loaded. Please check the file.");
    }
    
    if (strstr(fastboot_output, "Unknown partition"))
    {
        return _("Error: Unknown partition. Please check partition.");
    }

    return NULL; // unknown error
}

// function to create the flash command
char *build_flash_command(const char *device_command, const char *partition1, const char *partition2, const char *image_info, const char *optional_flags)
{
    char *command = malloc(8192);  

	// for a/b devices
    if (partition2) 
    {
        snprintf(command, 8192, "%s flash %s %s %s && %s flash %s %s %s",
                 device_command, partition1, image_info, optional_flags ? optional_flags : "",
                 device_command, partition2, image_info, optional_flags ? optional_flags : "");
    }
    
    // for only-a devices
    else  
    {
        snprintf(command, 8192, "%s flash %s %s %s", device_command, partition1, image_info, optional_flags ? optional_flags : "");
    }

    return command;
}


// get the flash details and 
void flash_details(const gchar *output, gpointer user_data)
{
	LOGD(output);
	const char *flash_details_data = check_fastboot_error(output);
	if (flash_details_data)
    {
    	// errors in the flash process
        const char *error_message = g_strdup_printf("%s", flash_details_data);    
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        LOGE("%s", error_message);
        g_free((char *)error_message);
    }
}

// function to flash an image
void flash_image(GtkWidget *widget, const char *partition1, const char *partition2, const char *image_name, const char *optional_flags)
{
    
    // let's see if we still need that with the new adw dialog
    //setenv("GSK_RENDERER", "cairo", 1);
    
    char config_file[4096];
    char image_info[4096];
    
    // create the path for the image
    get_config_file_path(config_file, sizeof(config_file));
    // load the path
    const char *image_path = load_path_from_file(config_file);

    if (image_path) 
    {
        LOGD("Loaded path: %s", image_path);
    }
	
	// create the image path
	snprintf(image_info, sizeof(image_info), "%s/%s", image_path, image_name);
	
    // check if the image not exists
    if (!debug_mode && access(image_info, F_OK) == -1)
    {      
        const char *error_message = _("Image file not found.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
    else if (debug_mode)
	{
    	g_print("[DEBUG] Security check skipped.\n");
    }
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    // create the command
    auto_free const char *device_command = fastboot_command();
    char *function_command = build_flash_command(device_command, partition1, partition2, image_info, optional_flags);
    
    const char *title = _("Fastboot running");
    const char *message = g_strdup_printf("Flashing %s...", image_name);
    
    // run command and return the output
    //show_spinner_dialog_return(GTK_WIDGET(parent_window), title, message, function_command, flash_details, NULL);
    // option:
    // use the porgress bar
    show_progress_dialog_return(GTK_WIDGET(main_window), title, message, function_command, flash_details, NULL);    
        
	if (image_path != NULL) 
	{
    	g_free((gpointer)image_path); // free the info (because g_file_get_contents was used)
	}
	g_free((char *)message);
}
