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
 *         Headerpart - check_active_slot	 *
 *											 *
 *-------------------------------------------*
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 128

void check_active_slot() 
{
    char buffer[BUFFER_SIZE];
    FILE *pipe;

    // fastboot-command for get boot-slots
    const char *command = "fastboot getvar current-slot 2>&1";

    // open pipe to run command
    pipe = popen(command, "r");
    if (!pipe) 
    {
        fprintf(stderr, "Konnte das Pipe nicht öffnen.\n");
        exit(EXIT_FAILURE);
    }
  
    // read output
    while (fgets(buffer, BUFFER_SIZE, pipe) != NULL) 
    {
        char *pos = strstr(buffer, "current-slot:");
        if (pos) 
        {
            sscanf(pos, "current-slot: %s", slot);
            break;
        }
    }

    // close pipe
    pclose(pipe);
}
