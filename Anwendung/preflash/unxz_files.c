/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - unxz_files				 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "program_functions.h"

// function to decompress xz-files
void unxz_files(const char *xz_filename) 
{
    char unxz_file_system_path[4096];
    get_config_file_path(unxz_file_system_path, sizeof(unxz_file_system_path));
    // load the path
    const char *file_path_unxz = load_path_from_file(unxz_file_system_path);

    if (file_path_unxz) 
    {
        LOG_INFO("Loaded path: %s", file_path_unxz);
    }

    // generate output filename by removing ".xz" extension
    const char *dot_xz = strrchr(xz_filename, '.');
    if (!dot_xz || strcmp(dot_xz, ".xz") != 0) 
    {
        LOG_ERROR("Input file is not an xz-compressed file.");
    }

    char output_xz_filename[512];
    size_t base_length = dot_xz - xz_filename;
    if (base_length >= sizeof(output_xz_filename)) 
    {
        LOG_INFO("Output filename buffer too small.");
        exit(1);
    }
    // create full file name
    snprintf(output_xz_filename, sizeof(output_xz_filename), "%s/%.*s", file_path_unxz, (int)base_length, xz_filename);

    // create unxz command
    char command[1024];
    int command_length = snprintf(command, sizeof(command), "unxz -c '%s' > '%s'", xz_filename, output_xz_filename);
    if (command_length < 0 || command_length >= sizeof(command)) 
    {
        LOG_INFO("Command buffer too small");
    	exit(1);
    }

    // run the command with spinner
    LOG_INFO("Run: %s", command);
    command_with_spinner(command);
    LOG_INFO("File successfully decompressed to: %s", output_xz_filename);
}

