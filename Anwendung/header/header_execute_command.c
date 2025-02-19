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
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *         Headerpart - execute_command		 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

/* for debugging *
*
* Usage:
* DEBUG 0 ← no debugging
* DEBUG 1 ← active debugging
*/

#define DEBUG 0

// function to execute a command and capture its output
char *execute_command(const char *command) 
{
    FILE *fp;
    char buffer[2048];
    auto_free char *result = calloc(1, 8192);  // autofree the memory

    if (!result) 
        return NULL;

    fp = popen(command, "r");
    if (!fp) 
        return NULL;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) 
    {
        strncat(result, buffer, 8192 - strlen(result) - 1);
    }

    pclose(fp);

#ifdef DEBUG
    // output for debugging
    LOG_INFO("Command Output: %s", result);
#endif

    return buffer;  // autofree the memory
}



