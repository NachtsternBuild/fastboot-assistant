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
 *         Headerpart - get_slot			 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "function_header.h"

int get_slot_of_device() 
{
    FILE *fp;
    char result[128];

    // Execute the command to check for A/B partition scheme
    fp = popen("fastboot getvar slot-count 2>&1", "r");
    if (fp == NULL) 
    {
        fprintf(stderr, "Failed to run command\n" );
        exit(1);
    }

    // Read the output
    while (fgets(result, sizeof(result)-1, fp) != NULL) 
    {
        if (strstr(result, "slot-count") && strstr(result, "2")) 
        {
            pclose(fp);
            return 1;
        }
    }

    pclose(fp);
    return 0;
}