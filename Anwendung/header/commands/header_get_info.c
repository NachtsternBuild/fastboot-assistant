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
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *         Headerpart - get_info			 *
 *											 *
 *-------------------------------------------*
 */

/*
***This is an experimental header. I don't if this work's.***
*/
/* header used in the programm*/ 
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "function_header.h"
#include "program_functions.h"

void get_info(char *android_version, char *kernel_version, char *device_name, char *project_treble, char *active_slot, char *get_root, char *get_soc, char *get_distro, char *get_version, char *get_desktop, char *get_language, char *get_session_type, char *adb_device, char *fastboot_device)
{
	// get android-version
    strcpy(android_version, execute_command("adb shell getprop ro.build.version.release"));
    
    // get kernel-info
    strcpy(kernel_version, execute_command("adb shell uname -r"));
    
    // get devicename
    strcpy(device_name, execute_command("adb shell getprop ro.product.model"));

    // get project-treble support info
    strcpy(project_treble, execute_command("adb shell getprop ro.treble.enabled"));

    // get activ-slot
    strcpy(active_slot, execute_command("adb shell getprop ro.boot.slot_suffix"));
    
    // get superuser
    strcpy(get_root, execute_command("adb shell su -c id"));
        
    // get SoC
    strcpy(get_soc, execute_command("adb shell cat /proc/cpuinfo"));
    
    /* thanks to @jean28518*/
    // get distribution
    strcpy(get_distro, execute_command("grep '^NAME=' /etc/os-release | cut -d'=' -f2 | tr -d ''"));
    
    // get version
    strcpy(get_version, execute_command("grep '^VERSION=' /etc/os-release | cut -d'=' -f2 | cut -d' ' -f1 | tr -d ''"));
    
    // get desktop
    strcpy(get_desktop, execute_command("echo $XDG_CURRENT_DESKTOP"));
    
    // get language
    strcpy(get_language, execute_command("echo $LANG | cut -d'_' -f1"));
	
	// get session type
    strcpy(get_session_type, execute_command("echo $XDG_SESSION_TYPE"));
    
    // get device that connected via adb
	strcpy(adb_device, execute_command("adb devices"));
	
	// get device thet connectet via fastboot
	strcpy(fastboot_device, execute_command("fastboot devices"));
}
