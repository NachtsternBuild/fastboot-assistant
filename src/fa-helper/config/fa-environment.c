/**
* application_environment.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

#define SEARCH_STRING "fastboot-assistant" 
#define SOURCES_DIR "/etc/apt/sources.list.d"
	
void application_environment()	
{
	const char *env = get_execution_environment();
    g_print("The app runs in the environment: **%s**\n", env);
	

	// flatpak		
    if (strcmp(env, "flatpak") == 0) 
    {
        flatpak_app = true;
    }
    
    // snap
    else if (strcmp(env, "snap") == 0) 
    {
        snap_app = true;
    }   
        
    // PPA/DEB
    else 
    {
        g_print("Running as PPA/DEB\n");
        int result = search_file_directory(SOURCES_DIR, SEARCH_STRING);
    
    	if (result == -1) 
    	{
        	fprintf(stderr, "Error check for PPA files\n");
        	exit(1);
   	 	}
    
    	else if (result == 1) 
    	{
        	ppa_app = true;
    	} 
    
    	else 
    	{
        	g_print("Running local DEB package.\n");
    	}
    }
}
