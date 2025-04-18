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
 *              Headerpart - ab_detect		 *
 *											 *
 *-------------------------------------------*
 */

/* headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <unistd.h>  
#include <sys/stat.h> 
#include <sys/types.h> 
#include "program_functions.h"

#define AB_FILE "ab_device.txt"

// standard device as only-a-device
const char *detected_device = "only_a";

// function that write the ab_device.txt
// thanks to my book for programming for linux
void write_ab_file() 
{
    char dir_path[512];
    char device_typ_dir[512];
    get_config_dir(dir_path, sizeof(dir_path));
    
    // create the path of the device dir
    snprintf(device_typ_dir, sizeof(device_typ_dir), "%s/device", dir_path);
    
    // create the dir 
    create_directory_if_not_exists(device_typ_dir);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", device_typ_dir, AB_FILE);

    FILE *file = fopen(path, "w");
    if (file == NULL) 
    {
        LOG_ERROR("Error when opening the file for writing.");
        exit(1);
    }
    fprintf(file, "abc");
    fclose(file);
    LOG_INFO("Written to the file '%s'.", path);
}

// thanks to my book for programming for linux
// function that delete the ab_device.txt
void delete_ab_file() 
{
    char dir_path[512];
    char device_typ_dir[512];
    get_config_dir(dir_path, sizeof(dir_path));
    
    // create the path of the device dir
    snprintf(device_typ_dir, sizeof(device_typ_dir), "%s/device", dir_path);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", device_typ_dir, AB_FILE);

    // try to remove the file
    if (remove(path) == 0) 
    {
        LOG_INFO("File '%s' successfully deleted.", path);
    } 
    
    else 
    {
        LOG_ERROR("Error deleting the file.");
    }
}

// function that check if there are the ab_device.txt
void check_ab_file() 
{
    char dir_path[512];
    char device_typ_dir[512];
    get_config_dir(dir_path, sizeof(dir_path));
    
    // create the path of the device dir
    snprintf(device_typ_dir, sizeof(device_typ_dir), "%s/device", dir_path);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", device_typ_dir, AB_FILE);

    FILE *file = fopen(path, "r");
    if (file != NULL) 
    {
        LOG_INFO("a/b-device detected");
        detected_device = "ab_device";
        fclose(file);
    }
     
    else 
    {
        LOG_INFO("only-a-device detected");
        detected_device = "only_a";
    }
}

// function to check for the ab_device.txt and remove this file
void check_ab_file_light() 
{
    char dir_path[512];
    char device_typ_dir[512];
    get_config_dir(dir_path, sizeof(dir_path));
    
    // create the path of the device dir
    snprintf(device_typ_dir, sizeof(device_typ_dir), "%s/device", dir_path);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", device_typ_dir, AB_FILE);

    FILE *file = fopen(path, "r");
    if (file != NULL) 
    {
        LOG_INFO("only-a-device detected");
        detected_device = "only_a";
        delete_ab_file();
        fclose(file);
    }
}

// function that apply the device typ
void apply_device()
{
	check_ab_file();
}
