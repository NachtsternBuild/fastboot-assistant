/**
* command_adb_fastboot.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/

#include "fastboot_assistant.h"
 
// function that use adb or adb.exe
char* adb_command() 
{
    if (directory_exists("/mnt/c/Users")) 
    {
        return strdup("adb.exe"); 
    } 
    
    else 
    {
        return strdup("adb"); 
    }
}

// function that use fastboot or fastboot.exe
char* fastboot_command() 
{
    if (directory_exists("/mnt/c/Users")) 
    {
        return strdup("fastboot.exe"); 
    } 
    
    else 
    {
        return strdup("fastboot");
    }
}
