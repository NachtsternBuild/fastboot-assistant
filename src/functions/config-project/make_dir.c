/**
* make_dir.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// function to create config dirs
void make_dir() 
{
    char rom_install_dirs_file[128];
    char main_path[256];
    char backup_path[512];
    char path_images[512];
    
    get_config_file_path(rom_install_dirs_file, sizeof(rom_install_dirs_file));
    // load the path
    const char *rom_install_dirs = load_path_from_file(rom_install_dirs_file);

    if (rom_install_dirs) 
    {
        LOGD("Loaded path: %s", rom_install_dirs);
    }
	
    // create the full path 
    snprintf(main_path, sizeof(main_path), "%s", rom_install_dirs);
    snprintf(backup_path, sizeof(backup_path), "%s/Backup", rom_install_dirs);
    snprintf(path_images, sizeof(path_images), "%s/Images", rom_install_dirs);

    // create path
    create_directory(main_path);
    create_directory(backup_path);
    create_directory(path_images);

	if (rom_install_dirs != NULL) 
	{
    	g_free((gpointer)rom_install_dirs);
	}	
	
    LOGD("all directories successfully created.");
}

