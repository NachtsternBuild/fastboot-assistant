/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das Installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              wsl_config					 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that are used in the main program */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "program_functions.h"

// check if file exists
int file_exists(const char *path) 
{
    char command[2048];
    snprintf(command, sizeof(command), "test -e %s", path);
    return system(command) == 0;
}

// check if path exists
int directory_exists(const char *path) 
{
    char command[2048];
    snprintf(command, sizeof(command), "test -d %s", path);
    return system(command) == 0;
}

// main function
void wsl_config() 
{
    const char *base_paths[] = {"/mnt/c/platform-tools", "/mnt/c/ADB"};
    const char *files[] = {"adb.exe", "fastboot.exe"};

    // check and create the symbolic link
    for (int i = 0; i < 2; ++i) 
    {
        int found = 0;
        for (int j = 0; j < 2; ++j) 
        {
            char path[256];
            snprintf(path, sizeof(path), "%s/%s", base_paths[j], files[i]);
            if (directory_exists(base_paths[j]) && file_exists(path)) 
            {
                // Paths to the possible locations of adb.exe and fastboot.exe
                char path[3072];
                char config[3072];
                char mv_adb[3072];
                char mv_fastboot[3072];
                char command_adb[3072];
                char command_fastboot[3072];
                snprintf(mv_adb, sizeof(mv_adb), "sudo mv /usr/bin/adb /usr/bin/adb_bk");
    			snprintf(mv_fastboot, sizeof(mv_fastboot), "sudo mv /usr/bin/fastboot /usr/bin/fastboot_bk");
   
				snprintf(path, sizeof(path), "%s/%s", base_paths[j], files[i]);
				snprintf(command_adb, sizeof(command_adb), "sudo ln -s %s /usr/bin/adb", path);
				snprintf(command_fastboot, sizeof(command_fastboot), "sudo ln -s %s /usr/bin/fastboot", path);
							
				// move the files
    			g_print(mv_adb);
    			g_print(mv_fastboot);
    			// create link to the .exe files
                g_print(command_adb);
                g_print(command_fastboot);
                // create the command to config everything
                snprintf(config, sizeof(config), "%s && %s && %s && %s && exit", mv_adb, mv_fastboot, command_adb, command_fastboot);
                g_print(config);
                // run command in new terminal
                open_terminal_by_desktop(config);
                
                found = 1;
                break;
            }
        }
        
        if (!found) 
        {
            g_print("Kein WSL System.\n");
        }
    }
    g_print("Fertig.\n");
}

