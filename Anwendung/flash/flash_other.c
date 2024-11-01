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
#include "loading_spinner.h"
#include <string.h>
#include <dirent.h>
#include <unistd.h>

void flash_partition(const char *partition, const char *img_file) 
{
    g_print("Log: flash_partition\n");
    char command[512];
    char *device_command = fastboot_command();
    snprintf(command, sizeof(command), "%s flash %s %s", device_command, partition, img_file);
    g_print("Executing: %s\n", command);
    int ret = system(command);
    if (ret != 0)
    {
        g_print("Fehler: Der Befehl '%s' wurde nicht erfolgreich ausgeführt.\n", command);
    }
    free(device_command);
    g_print("Log: end flash_partition\n");
}

void process_file(const char *filepath) 
{
    if (strstr(filepath, "gz.img")) 
    {
        flash_partition("gz_a", filepath);
        flash_partition("gz_b", filepath);
    } 
    else if (strstr(filepath, "lk.img")) 
    {
        flash_partition("lk_a", filepath);
        flash_partition("lk_b", filepath);
    } 
    else if (strstr(filepath, "logo.img")) 
    {
        flash_partition("logo", filepath);
    } 
    else if (strstr(filepath, "md1img.img")) 
    {
        flash_partition("md1img_a", filepath);
        flash_partition("md1img_b", filepath);
    } 
    else if (strstr(filepath, "metadata.img")) 
    {
        flash_partition("metadata", filepath);
    }
    else if (strstr(filepath, "protect.img")) 
    {
        flash_partition("protect_a", filepath);
        flash_partition("protect_b", filepath);
    } 
    else if (strstr(filepath, "scp.img")) 
    {
        flash_partition("scp_a", filepath);
        flash_partition("scp_b", filepath);
    } 
    else if (strstr(filepath, "spmfw.img")) 
    {
        flash_partition("spmfw_a", filepath);
        flash_partition("spmfw_b", filepath);
    } 
    else if (strstr(filepath, "sspm.img")) 
    {
        flash_partition("sspm_a", filepath);
        flash_partition("sspm_b", filepath);
    } 
    else if (strstr(filepath, "tee.img")) 
    {
        flash_partition("tee_a", filepath);
        flash_partition("tee_b", filepath);
    } 
    else 
    {
        g_print("Log: Unbekannte Datei: %s, wird übersprungen.\n", filepath);
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
        g_print("Fehler: Konnte Verzeichnis '%s' nicht öffnen.\n", directory);
    }
}

void flash_other() 
{
    g_print("Log: flash_other\n");
    char *homeDir = getenv("HOME");
	if (homeDir == NULL) 
	{
    	fprintf(stderr, "Fehler: Konnte das Home-Verzeichnis nicht finden.\n");
    	exit(1);  // close the program if there are errors
	}

	// WSL Logik
	const char *user = getenv("USER");
	if (user == NULL) 
	{	
    	g_print("Fehler: Konnte den Benutzernamen nicht ermitteln.\n");
    	exit(1);  // close the program if there are errors
	}
	
    char wsl_setup_base[2048];
    char other_dir[2048];
    char directory[2048];
	snprintf(wsl_setup_base, sizeof(wsl_setup_base), "/mnt/c/Users/%s", user);

	// for linux
	snprintf(other_dir, sizeof(other_dir), "%s", homeDir);
	// for wsl
	// snprintf(other_dir, sizeof(other_dir), "%s", wsl_setup_base);
    snprintf(directory, sizeof(directory), "%s/Downloads/ROM-Install/Images", other_dir);
    flash_images_in_directory(directory);
    
    free(directory);
    g_print("Log: end flash_other\n");
}
