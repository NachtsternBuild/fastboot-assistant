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
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <sys/stat.h>
#include <sys/types.h>

#define TARGET_DIR "Downloads/ROM-Install" // target dir

void unxz_files(const char *xz_filename) 
{
    // get home dir
    char *homeDir = getenv("HOME");
	if (homeDir == NULL) 
	{
    	fprintf(stderr, "Log: Error: Could not find the home directory.\n");
    	exit(1);  // close the program if there are errors
	}
    
    // WSL Logic
	const char *user = getenv("USER");
	if (user == NULL) 
	{	
    	g_print("Log: Error: Could not determine the user name.\n");
    	exit(1);  // close the program if there are errors
	}

	char wsl_setup_base[2048];
	snprintf(wsl_setup_base, sizeof(wsl_setup_base), "/mnt/c/Users/%s", user);

    // make full path
    char output_dir_xz[512];
    // for linux
    snprintf(output_dir_xz, sizeof(output_dir_xz), "%s/%s", home_dir, TARGET_DIR);
    // for wsl
    //snprintf(output_dir_xz, sizeof(output_dir_xz), "%s/%s", wsl_setup_base, TARGET_DIR);

    // remove .xz from the output
    char output_xz_filename[512];
    const char *dot_xz = strrchr(xz_filename, '.');
    if (dot_xz && strcmp(dot_xz, ".xz") == 0) 
    {
        size_t base_length = dot_xz - xz_filename;
        strncpy(output_xz_filename, xz_filename, base_length);
        output_xz_filename[base_length] = '\0';
    } 
    
    else 
    {
        strncpy(output_xz_filename, xz_filename, sizeof(output_xz_filename));
        g_print("Log: No xz-compressed file!\n");
    }
    
    // make full path to outout file
    char output_file_xz[512];
    snprintf(output_file_xz, sizeof(output_file_xz), "%s", output_xz_filename);

    // create unxz command
    char command[1024];
    snprintf(command, sizeof(command), "unxz -c %s > %s", xz_filename, output_file_xz);

    // output of the command
    g_print("Log: Run: %s\n", command);

    // run command
    int result = system(command);
    if (result != 0) 
    {
        g_print("Log: Error when executing the command.\n");
        exit(EXIT_FAILURE);
    }
}
