/**
* updater.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// define strings for searching ppa
#define SEARCH_STRING "fastboot-assistant" 
#define SOURCES_DIR "/etc/apt/sources.list.d"

// function that check enviroment
const char* get_execution_environment() 
{
    if (getenv("SNAP") != NULL || getenv("SNAP_NAME") != NULL) 
    {
        return "snap";
    } 
    
    else if (getenv("FLATPAK_ID") != NULL) 
    {
        return "flatpak";
    } 
    
    else if (directory_exists("/app/bin")) 
    {
    	return "flatpak";
    }
    
    else 
    {
        return "traditional"; 
    }
}

/**
* main updater function
*
* Note:
* the updater check the environment to use the right updater
*/
void updater(GtkWidget *widget, gpointer stack)
{
    char *command = NULL;
    int result = -1;
    const char *env = get_execution_environment();
    LOGD("The app runs in the environment: **%s**\n", env);
	
	// flatpak		
    if (strcmp(env, "flatpak") == 0) 
    {
        LOGD("Running as flatpak");
        command = "gnome-software || plasma-discover || xdg-open 'appstream://'"; 
    }
    // snap
    else if (strcmp(env, "snap") == 0) 
    {
        LOGD("Running as snap");
        command = "snap-store";
    } 
    
    // PPA/DEB
    else 
    {
        LOGD("Running as PPA/DEB");
        int result = search_file_directory(SOURCES_DIR, SEARCH_STRING);
    
    	if (result == -1) 
    	{
        	LOGE("Error check for PPA files");
        	exit(1);
   	 	}
    
    	else if (result == 1) 
    	{
        	LOGD("Running as PPA");
        	ppa_updater();
    	} 
    
    	else 
    	{
        	LOGD("Running local DEB package.");
        	local_updater();
    	}
    }
    
    // open stores for snap/flatpak
    if (command != NULL) 
    {
        LOGD("Run command: %s", command);
        result = system(command);
    }
    
    if (result == -1) 
    {
        LOGE("Error executing the system() command");
        perror("Error executing the system() command");
    } 
    
    else if (result != 0) 
    {
        LOGW("Store command executed, but the store may not have been opened (exit code: %d).", result);
    } 
    
    else 
    {
        LOGD("Store successfully opened.");
    }
}
