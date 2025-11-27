/**
* flash_images.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

#define MAX_PATH 256
#define BUFFER_SIZE 512

static void system_images(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, "system", NULL, "system.img", NULL);
}

static void userdata_images(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, "userdata", NULL, "userdata.img", NULL);
}

static void vbmeta_ab_images(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget,"vbmeta_a", "vbmeta_b", "vbmeta.img", "--disable-verity --disable-verification");
}

static void vbmeta_a_images(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, "vbmeta", NULL, "vbmeta.img", "--disable-verity --disable-verification");
}

// function to flash the partitions
int flash_partition(const char *partition, const char *image_path, int ab_device) 
{
    const char *title = _("Fastboot Running");
    
    // flash every partition on a/b-device
    if (ab_device && strcmp(partition, "system") != 0 && strcmp(partition, "userdata") != 0 && strcmp(partition, "vbmeta") != 0) 
    {
        LOGD("Flash other Images (a/b).");
        char function_command[3072];
        auto_free char *device_command = fastboot_command();
        snprintf(function_command, sizeof(function_command), "%s flash %s_a %s && %s flash %s_b %s", device_command, partition, image_path, device_command, partition, image_path);
        LOGD("Run: %s", function_command);
        
        const char *body = _("Flash running...");
        show_progress_dialog(NULL, title, body, function_command);
        LOGD("Finished.");
    } 
    
    // flash system on all devices
    else if (strcmp(partition, "system") == 0 && ab_device) 
    {
        char function_command[3072];
    	auto_free char *device_command = fastboot_command();
    	snprintf(function_command, sizeof(function_command), "%s erase system", device_command);
    	LOGD("Run: %s", function_command);
    	
    	const char *body = _("Erasing files...");
    	show_spinner_dialog(NULL, title, body, function_command);
        system_images(NULL, NULL);  // passing NULL for widget and window
    }
    
    // flash userdata on all devices
    else if (strcmp(partition, "userdata") == 0 && ab_device) 
    {
        userdata_images(NULL, NULL);  // passing NULL for widget and window
    }
    
    // flash vbmeta on a/b-devices
    else if (strcmp(partition, "vbmeta") == 0 && ab_device) 
    {
        vbmeta_ab_images(NULL, NULL);
    }
    
    // flash vbmeta on only-a-devices
    else if (strcmp(partition, "vbmeta") == 0)
    {
        vbmeta_a_images(NULL, NULL);
    }
    
    // for all only-a-devices - flash all partitions
    else 
    {
        LOGD("Flash partitions without slot.");
        char function_command[3072];
        auto_free char *device_command = fastboot_command();
        snprintf(function_command, sizeof(function_command), "%s flash %s %s", device_command, partition, image_path);
        LOGD("Run: %s", function_command);
        
        const char *body = _("Flash running...");
        show_progress_dialog(NULL, title, body, function_command);
        LOGD("Finished.");
    }
    
    LOGD("Image %s successfully flashed on partition %s.", image_path, partition);
    return 0;  // Return 0 to indicate success
}

// function to flash an image from a directory
void flash_dir(const char *directory) 
{
    DIR *dir;
    struct dirent *entry;
    int ab_device = get_slot_of_device();
    
    // open directory
    dir = opendir(directory);
    if (dir == NULL) 
    {
        LOGE("irectory cannot be opened.");
        exit(1);
    }
    
    // read directory
    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_type == DT_REG) 
        {
            char image_path[1024];
            
            // create image_path
            snprintf(image_path, sizeof(image_path), "%s/%s", directory, entry->d_name);

            // get image names as partition
            char partition[MAX_PATH];
            strncpy(partition, entry->d_name, strcspn(entry->d_name, "."));
            partition[strcspn(entry->d_name, ".")] = '\0';  // remove file ending

            if (flash_partition(partition, image_path, ab_device) != 0) 
            {
                LOGE("Error when flashing the partition %s", partition);
                exit(1);
            }
        }
    }
    
    // close directory
    closedir(dir);
}

/* main function - flash_images */
void flash_images(GtkWidget *widget, gpointer stack) 
{
    LOGI("flash_images");
    
    char config_file[512];
    get_config_file_path(config_file, sizeof(config_file));
    // load the path
    const char *directory = load_path_from_file(config_file);

    if (directory) 
    {
        LOGD("Loaded path: %s", directory);
    }
	
    LOGD("Start flashing Images from the %s directory.", directory);
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    // start flash from directory
    flash_dir(directory);
    
	if (directory != NULL) 
	{
    	g_free((gpointer)directory); // free the info (because g_file_get_contents was used)
	}
    
    LOGD("end flash_images");
}

