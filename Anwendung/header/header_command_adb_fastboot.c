/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *  Headerpart - command_adb_fastboot		 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <gtk/gtk.h>
#include "program_functions.h"
 
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
