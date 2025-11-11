/**
* unxz_files.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"
// function to decompress xz-files
void unxz_files(const char *xz_filename) 
{
    char unxz_file_system_path[4096];
    get_config_file_path(unxz_file_system_path, sizeof(unxz_file_system_path));
    // load the path
    const char *file_path_unxz = load_path_from_file(unxz_file_system_path);

    if (file_path_unxz) 
    {
        LOGD("Loaded path: %s", file_path_unxz);
    }

    // generate output filename by removing ".xz" extension
    const char *dot_xz = strrchr(xz_filename, '.');
    if (!dot_xz || strcmp(dot_xz, ".xz") != 0) 
    {
        LOGE("Input file is not an xz-compressed file.");
    }

    char output_xz_filename[512];
    size_t base_length = dot_xz - xz_filename;
    if (base_length >= sizeof(output_xz_filename)) 
    {
        LOGE("Output filename buffer too small.");
        exit(1);
    }
    // create full file name
    //snprintf(output_xz_filename, sizeof(output_xz_filename), "%s/%.*s", file_path_unxz, (int)base_length, xz_filename);
    snprintf(output_xz_filename, sizeof(output_xz_filename), "%.*s", (int)base_length, xz_filename);

    // create unxz command
    char command[1024];
    int command_length = snprintf(command, sizeof(command), "unxz -c '%s' > '%s'", xz_filename, output_xz_filename);
    if (command_length < 0 || command_length >= sizeof(command)) 
    {
        LOGE("Command buffer too small");
    	exit(1);
    }

    // run the command with spinner
    LOGD("Run: %s", command);
   
    show_spinner_dialog(GTK_WIDGET(main_window), _("Decompressing File"), _("Please wait..."), command);
        
    if (file_path_unxz != NULL) 
	{
    	g_free((gpointer)file_path_unxz); // free the info (because g_file_get_contents was used)
	}
}

