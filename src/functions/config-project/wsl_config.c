/**
* wsl_config.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

char path[128];
char config[512];
char config_two[1024];
char mv_adb[128];
char mv_fastboot[128];
char command_adb[256];
char command_fastboot[256];
char full_command[2048];

const char *base_paths[] = {
	"/mnt/c/platform-tools", 
	"/mnt/c/ADB"
	};
const char *files[] = {
	"adb.exe", 
	"fastboot.exe"
	};

static void config_adb() 
{
    for (int i = 0; i < 2; ++i) 
    {
        for (int j = 0; j < 2; ++j) 
        {
            snprintf(path, sizeof(path), "%s/%s", base_paths[j], files[i]);
            
            // command to move and link adb/fastboot
            snprintf(mv_adb, sizeof(mv_adb), "mv /usr/bin/adb /usr/bin/adb_bk");
            snprintf(mv_fastboot, sizeof(mv_fastboot), "mv /usr/bin/fastboot /usr/bin/fastboot_bk");
            snprintf(command_adb, sizeof(command_adb), "ln -s %s /usr/bin/adb", path);
            snprintf(command_fastboot, sizeof(command_fastboot), "ln -s %s /usr/bin/fastboot", path);

            // create the command
            snprintf(config, sizeof(config), "%s && %s", mv_adb, mv_fastboot);
			snprintf(config_two, sizeof(config_two), "%s && %s", command_adb, command_fastboot);
			snprintf(full_command, sizeof(full_command), "sh -c \"%s && %s\"", config, config_two); // use 'sh -c' to run both big commands with pkexec  
            LOGD("Run: %s", full_command);
			
			const char *title = _("Configuration");
			const char *text = _("Running configuration...");
			
            // run command with pkexec
            command_pkexec_spinner(GTK_WIDGET(main_window), full_command, title, text);
        }
    }
}

// main function wsl_config
void wsl_config() 
{    
    int found = 0;

    // check for adb/fastboot
    for (int i = 0; i < 2; ++i) 
    {
        for (int j = 0; j < 2; ++j) 
        {
            snprintf(path, sizeof(path), "%s/%s", base_paths[j], files[i]);
            
            if (directory_exists(base_paths[j]) && file_exists(path)) 
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            break;
        }
    }
	
	// for the WSL system
    if (found == 1) 
    {
     	// run config for adb/fastboot   
        config_adb();
    }
    
    // no WSL system
    else 
    {
        LOGD("No WSL system");
    }
}

