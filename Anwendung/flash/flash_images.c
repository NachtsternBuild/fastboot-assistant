/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_images		  	 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include "program_functions.h"

#define MAX_PATH 256
#define BUFFER_SIZE 512

static void system_images(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "system", NULL, "system.img");
}

static void userdata_images(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "userdata", NULL, "userdata.img");
}

// function to flash the partitions
int flash_partition(const char *partition, const char *image_path, int ab_device) 
{
    // flash every partition on a/b-device
    if (ab_device && strcmp(partition, "system") != 0 && strcmp(partition, "userdata") != 0 && strcmp(partition, "vbmeta") != 0) 
    {
        g_print("Log: Flash other Images (a/b).\n");
        char function_command[3072];
        char *device_command = fastboot_command();
        snprintf(function_command, sizeof(function_command), "%s flash %s_a %s && %s flash %s_b %s", device_command, partition, image_path, device_command, partition, image_path);
        g_print("Log: Run: %s\n", function_command);
        command_with_spinner(function_command);
        free(device_command);
        g_print("Log: Finished.\n");
    } 
    // flash system on all devices
    else if (strcmp(partition, "system") == 0 && ab_device) 
    {
        system_images(NULL, NULL);  // Passing NULL for widget and window
    }
    // flash userdata on all devices
    else if (strcmp(partition, "userdata") == 0 && ab_device) 
    {
        userdata_images(NULL, NULL);  // Passing NULL for widget and window
    }
    // flash vbmeta on a/b-devices
    else if (strcmp(partition, "vbmeta") == 0 && ab_device) 
    {
        g_print("Log: Flash vbmeta on a/b-devices.\n");
        char function_command[3072];
        char *device_command = fastboot_command();
        snprintf(function_command, sizeof(function_command), "%s flash --disable-verity --disable-verification vbmeta_a %s && %s flash --disable-verity --disable-verification vbmeta_b %s && exit", device_command, image_path, device_command, image_path);
        g_print("Log: Run: %s", function_command);
        open_terminal_by_desktop(function_command);
        free(device_command);
        g_print("Log: Finished.\n");
    }
    // flash vbmeta on only-a-devices
    else if (strcmp(partition, "vbmeta") == 0)
    {
        g_print("Log: Flash vbmeta on only-a-devices.\n");
        char function_command[3072];
        char *device_command = fastboot_command();
        snprintf(function_command, sizeof(function_command), "%s flash --disable-verity --disable-verification vbmeta %s && exit", device_command, image_path);
        g_print("Log: Run: %s", function_command);
        open_terminal_by_desktop(function_command);
        free(device_command);
        g_print("Log: Finished.\n");
    }
    // for all only-a-devices - flash all partitions
    else 
    {
        g_print("Log: Flash partitions without slot.\n");
        char function_command[3072];
        char *device_command = fastboot_command();
        snprintf(function_command, sizeof(function_command), "%s flash %s %s", device_command, partition, image_path);
        g_print("Log: Run: %s\n", function_command);
        command_with_spinner(function_command);
        free(device_command);
        g_print("Log: Finished.\n");
    }
    g_print("Log: Image %s successfully flashed on partition %s.\n", image_path, partition);
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
        perror("Log: Directory cannot be opened.\n");
        exit(EXIT_FAILURE);
    }
    
    // read directory
    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_type == DT_REG) 
        {
            char image_path[MAX_PATH];
            
            // create image_path
            snprintf(image_path, sizeof(image_path), "%s/%s", directory, entry->d_name);

            // get image names as partition
            char partition[MAX_PATH];
            strncpy(partition, entry->d_name, strcspn(entry->d_name, "."));
            partition[strcspn(entry->d_name, ".")] = '\0';  // remove file ending

            if (flash_partition(partition, image_path, ab_device) != 0) 
            {
                fprintf(stderr, "Log: Error when flashing the partition %s\n", partition);
                exit(EXIT_FAILURE);
            }
        }
    }
    
    // close directory
    closedir(dir);
}

/* main function - flash_images */
void flash_images() 
{
    g_print("Log: flash_images\n");
    // for Linux
    const char *home = getenv("HOME");
    if (home == NULL) 
    {
        g_print("Log: Environment variable HOME is not set.\n");
        exit(EXIT_FAILURE);
    }
    
    // WSL logic
    const char *user = getenv("USER");
    if (user == NULL) 
    {    
        g_print("Log: Error: Could not determine the user name.\n");
        exit(EXIT_FAILURE);  // close the program if there are errors
    }

    char wsl_setup_base[MAX_PATH];
    snprintf(wsl_setup_base, sizeof(wsl_setup_base), "/mnt/c/Users/%s", user);

    // Set default path to ~/Downloads/ROM-Install
    char directory[MAX_PATH];
    // for Linux 
    snprintf(directory, sizeof(directory), "%s/Downloads/ROM-Install", home);
    // for WSL
    snprintf(directory, sizeof(directory), "%s/Downloads/ROM-Install", wsl_setup_base);

    g_print("Log: Images from the %s directory are flashed.\n", directory);
    // start flash from directory
    flash_dir(directory);
    
    g_print("Log: end flash_images\n");
}

