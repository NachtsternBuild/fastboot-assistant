/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_list_images  	 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "flash_function_header.h"
#include "loading_spinner.h"
#include <string.h>
#include <dirent.h>
#include <unistd.h>

void flash_partition_list(const char *partition, const char *img_file) 
{
    LOG_INFO("flash_partition");
    char command[512];
    auto_free char *device_command = fastboot_command();
    snprintf(command, sizeof(command), "%s flash %s %s", device_command, partition, img_file);
    LOG_INFO("Executing: %s", command);
    int ret = system(command);
    if (ret != 0)
    {
        LOG_ERROR("The command '%s' was not executed successfully.", command);
    }
    LOG_INFO("end flash_partition");
}

void process_file(const char *filepath) 
{
    if (strstr(filepath, "gz.img")) 
    {
        flash_partition_list("gz_a", filepath);
        flash_partition_list("gz_b", filepath);
    } 
    
    else if (strstr(filepath, "lk.img")) 
    {
        flash_partition_list("lk_a", filepath);
        flash_partition_list("lk_b", filepath);
    } 
    
    else if (strstr(filepath, "logo.img")) 
    {
        flash_partition_list("logo", filepath);
    } 
    
    else if (strstr(filepath, "md1img.img")) 
    {
        flash_partition_list("md1img_a", filepath);
        flash_partition_list("md1img_b", filepath);
    } 
    
    else if (strstr(filepath, "metadata.img")) 
    {
        flash_partition_list("metadata", filepath);
    }
    
    else if (strstr(filepath, "protect.img")) 
    {
        flash_partition_list("protect_a", filepath);
        flash_partition_list("protect_b", filepath);
    } 
    
    else if (strstr(filepath, "scp.img")) 
    {
        flash_partition_list("scp_a", filepath);
        flash_partition_list("scp_b", filepath);
    } 
    
    else if (strstr(filepath, "spmfw.img")) 
    {
        flash_partition_list("spmfw_a", filepath);
        flash_partition_list("spmfw_b", filepath);
    } 
    else if (strstr(filepath, "sspm.img")) 
    {
        flash_partition_list("sspm_a", filepath);
        flash_partition_list("sspm_b", filepath);
    } 
    
    else if (strstr(filepath, "tee.img")) 
    {
        flash_partition_list("tee_a", filepath);
        flash_partition_list("tee_b", filepath);
    } 
    
    else 
    {
        LOG_INFO("Unknown file: %s, will be skipped.", filepath);
    }
}

void flash_images_in_directory(const char *directory) 
{
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(directory)) != NULL) 
    {
        while ((ent = readdir(dir)) != NULL) 
        {
            if (ent->d_type == DT_REG) 
            {
                char filepath[512];
                snprintf(filepath, sizeof(filepath), "%s/%s", directory, ent->d_name);
                process_file(filepath);
            }
        }
        closedir(dir);
    } 
    else 
    {
        LOG_ERROR("Could not open directory '%s'.", directory);
    }
}

void flash_list_images() 
{
    LOG_INFO("flash_other");
	
    char directory[2048];

	// snprintf(other_dir, sizeof(other_dir), "%s", wsl_setup_base);
	char config_file_images[2048];
    get_config_file_path(config_file_images, sizeof(config_file_images));
    // load the path
    const char *other_dir = load_path_from_file(config_file_images);

    if (other_dir) 
    {
        LOG_INFO("Loaded path: %s", other_dir);
    }
    snprintf(directory, sizeof(directory), "%s/Images", other_dir);
    flash_images_in_directory(directory);
    
    if (other_dir != NULL) 
	{
    	g_free((gpointer)other_dir); // free the info (because g_file_get_contents was used)
	}
	
    if (directory != NULL) 
    {
    	g_free((gpointer)directory); 
	}
    LOG_INFO("end flash_other");
}
