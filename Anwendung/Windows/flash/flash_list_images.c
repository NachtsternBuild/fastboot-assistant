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
 *      (C) Copyright 2023 Elias Mörz 		 *
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
    g_print("Log: flash_partition\n");
    char command[512];
    char *device_command = fastboot_command();
    snprintf(command, sizeof(command), "%s flash %s %s", device_command, partition, img_file);
    g_print("Executing: %s\n", command);
    int ret = system(command);
    if (ret != 0)
    {
        g_print("Log: Error: The command '%s' was not executed successfully.\n", command);
    }
    free(device_command);
    g_print("Log: end flash_partition\n");
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
        g_print("Log: Unknown file: %s, will be skipped.\n", filepath);
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
        g_print("Log: Error: Could not open directory '%s'.\n", directory);
    }
}

void flash_list_images() 
{
    g_print("Log: flash_other\n");
    char *homeDir = getenv("HOME");
	if (homeDir == NULL) 
	{
    	fprintf(stderr, "Log: Error: Could not find the home directory.\n");
    	exit(1);  // close the program if there are errors
	}

	// WSL Logik
	const char *user = getenv("USER");
	if (user == NULL) 
	{	
    	g_print("Log: Error: Could not determine the user name.\n");
    	exit(1);  // close the program if there are errors
	}
	
    char wsl_setup_base[2048];
    char other_dir[2048];
    char directory[2048];
	snprintf(wsl_setup_base, sizeof(wsl_setup_base), "/mnt/c/Users/%s", user);

	// for linux
	// snprintf(other_dir, sizeof(other_dir), "%s", homeDir);
	// for wsl
	snprintf(other_dir, sizeof(other_dir), "%s", wsl_setup_base);
    snprintf(directory, sizeof(directory), "%s/Downloads/ROM-Install/Images", other_dir);
    flash_images_in_directory(directory);
    
    free(directory);
    g_print("Log: end flash_other\n");
}
