/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_others			 *
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
#include <string.h>
#include <dirent.h>

// a function for flash the files
void flash_partition(const char *partition, const char *img_file) 
{
    char command[256];
    snprintf(command, sizeof(command), "fastboot flash %s %s", partition, img_file);
    printf("Executing: %s\n", command);
    system(command);
}

// the list of files that flashable
void process_file(const char *filename) 
{
    if (strstr(filename, "gz.img")) 
    {
        flash_partition("gz_a", filename);
        flash_partition("gz_b", filename);
    } 
    
    else if (strstr(filename, "lk.img")) 
    {
        flash_partition("lk_a", filename);
        flash_partition("lk_b", filename);
    } 
    
    else if (strstr(filename, "logo.img")) 
    {
        flash_partition("logo", filename);
    } 
    
    else if (strstr(filename, "md1img.img")) 
    {
        flash_partition("md1img_a", filename);
        flash_partition("md1img_b", filename);
    }
    
    else if (strstr(filename, "metadata.img")) 
    {
        flash_partition("metadata", filename);
    }
    // Weitere Partitionen je nach Bedarf hinzufügen
    else if (strstr(filename, "protect.img")) 
    {
        flash_partition("protect_a", filename);
        flash_partition("protect_b", filename);
    } 
    
    else if (strstr(filename, "scp.img")) 
    {
        flash_partition("scp_a", filename);
        flash_partition("scp_b", filename);
    }
     
    else if (strstr(filename, "spmfw.img")) 
    {
        flash_partition("spmfw_a", filename);
        flash_partition("spmfw_b", filename);
    } 
    
    else if (strstr(filename, "sspm.img")) 
    {
        flash_partition("sspm_a", filename);
        flash_partition("sspm_b", filename);
    }
    
    else if (strstr(filename, "tee.img")) 
    {
        flash_partition("tee_a", filename);
        flash_partition("tee_b", filename);
    } 
}

// function that open the dir, read the filenames and flash it
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
                char filepath[256];
                snprintf(filepath, sizeof(filepath), "%s/%s", directory, ent->d_name);
                // flash the partitions
                process_file(filepath);
            }
        }
        // close the dir
        closedir(dir);
    } 
    
    else 
    {
        perror("Could not open directory");
    }
}

void  flash_other() 
{
    // path to the other .img-files
    const char *directory = "~/Downloads/ROM-Install/Images"; 
    flash_images_in_directory(directory);
}

