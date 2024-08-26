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
 *         Headerpart - check_first_run	 	 *
 *											 *
 *-------------------------------------------*
 */

/* headers */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // for access()
#include "program_functions.h"

#define FILENAME ".fastboot-assistant"
#define FILEPATH "/usr/bin/fastboot-assistant/"

char* program_path()
{
    char* filepath_first = malloc(strlen(FILEPATH) + strlen(FILENAME) + 2);
    if (filepath_first == NULL) 
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    sprintf(filepath_first, "%s/%s", FILEPATH, FILENAME);
    return filepath_first;
}

gboolean check_first_run() 
{
    char* filepath_first = program_path();
    gboolean first_run = FALSE;

    if (access(filepath_first, F_OK) == -1) 
    {
        first_run = TRUE;
    }

    free(filepath_first);  // Freigabe des dynamisch allozierten Speichers
    return first_run;
}


