/**
* resize_partition.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

/**
* @brief function to validate the partition name
*/
int valid_partition_name(const char *name) 
{
    if (!name || *name == '\0') 
    {
    	return 0;
    }
    
    // check the name for special characters
    for (int i = 0; name[i] != '\0'; i++) 
    {
        if (!isalnum(name[i]) && name[i] != '_' && name[i] != '-')  // allows only alphanumeric characters, underscores, and hyphens
        {
            return 0;
        }
    }
    return 1;
}
