/**
* ab_detect.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

#define AB_FILE "ab_device.conf"

// standard device as only-a-device
const char *detected_device = "only_a";

// function that write the ab_device.txt
// thanks to my book for programming for linux
void write_ab_file() 
{
    char dir_path[512];
    char safe_base[PATH_MAX];
    char path[PATH_MAX];
    char device_typ_dir[1024];
    get_config_dir(dir_path, sizeof(dir_path));
    
    if (!is_safe_home_dir(dir_path)) 
    {
        LOGE("Unsafe config directory path!");
        exit(1);
    }

    // canonicalize path
    if (realpath(dir_path, safe_base) == NULL) 
    {
        LOGE("Failed to resolve config path: %s", strerror(errno));
        exit(1);
    }

    // build device directory path safely
    if (snprintf(device_typ_dir, sizeof(device_typ_dir), "%s/device", safe_base) >= sizeof(device_typ_dir)) 
    {
        LOGE("Path too long");
        exit(1);
    }

    create_directory(device_typ_dir);

    // build file path safely
    if (snprintf(path, sizeof(path), "%s/%s", device_typ_dir, AB_FILE) >= sizeof(path)) 
    {
        LOGE("Path too long");
        exit(1);
    }

    // secure file creation
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_NOFOLLOW, S_IRUSR | S_IWUSR);
    if (fd == -1) 
    {
        LOGE("Error opening file: %s", strerror(errno));
        exit(1);
    }
    	
    FILE *file = fdopen(fd, "w");
    if (file == NULL) 
    {
        LOGE("Error when opening the file for writing.");
        exit(1);
    }
    fprintf(file, "abc");
    fclose(file);
    LOGI("Written to the file '%s'.", path);
}

// function that check if there are the ab_device.txt
void check_ab_file() 
{
    char dir_path[512];
    char safe_base[PATH_MAX];
    char device_typ_dir[1024];
    get_config_dir(dir_path, sizeof(dir_path));
    
    if (!is_safe_home_dir(dir_path)) 
    {
    	LOGE("Unsafe config directory path!");
    	return;
	}

	if (realpath(dir_path, safe_base) == NULL) 
	{
    	LOGE("Path resolve failed");
    	return;
	}
    
    // create the path of the device dir
    snprintf(device_typ_dir, sizeof(device_typ_dir), "%s/device", dir_path);

    char path[1040];
    snprintf(path, sizeof(path), "%s/%s", device_typ_dir, AB_FILE);
	
	// check if the file exists
    if (access(path, R_OK) == 0) 
    {
        LOGI("a/b-device detected");
        detected_device = "ab_device";
    }
    else 
    {
        LOGI("only-a-device detected");
        detected_device = "only_a";
    }
}

// function to check for the ab_device.txt and remove this file
void check_ab_file_light() 
{
    char dir_path[512];
    char safe_base[PATH_MAX];
    char device_typ_dir[1024];
    get_config_dir(dir_path, sizeof(dir_path));
    
    if (!is_safe_home_dir(dir_path)) 
    {
    	LOGE("Unsafe config directory path!");
    	return;
	}

	if (realpath(dir_path, safe_base) == NULL) 
	{
    	LOGE("Path resolve failed");
    	return;
	}
    
    // create the path of the device dir
    snprintf(device_typ_dir, sizeof(device_typ_dir), "%s/device", dir_path);

    char path[1040];
    snprintf(path, sizeof(path), "%s/%s", device_typ_dir, AB_FILE);
	
	if (remove(path) == 0) 
    {
        LOGI("A/B config found and removed. Setting to only-a-device.");
        detected_device = "only_a";
    }
    else 
    {
        // can't remove the file, so the device is a only_a device
        detected_device = "only_a";
    }
}

// function that apply the device typ
void apply_device()
{
	check_ab_file();
}
