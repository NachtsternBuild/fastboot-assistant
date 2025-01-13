/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das Installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *        headerpart - write_log			 *
 *											 *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <glib.h>
#include "program_functions.h"

// function that write the log to a file
void write_log() 
{
    char log_dir[4096];
    char log_file[4096];
    
    // get config dir
    get_config_dir(log_dir, sizeof(log_dir));
    
    // log file with path
    snprintf(log_file, sizeof(log_file), "%s/log/log.txt", log_dir);
    LOG_INFO("Log-file: %s", log_file);

    // create log_dir
    // only if it not exsists
    if (access(log_dir, F_OK) == -1) 
    {
        mkdir(log_dir, 0755);
    }

    // open log file or create it
    int log_fd = open(log_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (log_fd == -1) 
    {
        LOG_ERROR("Error when opening the log file.");
        exit(1);
    }

    // write info or errors to the file using dup2
    dup2(log_fd, STDOUT_FILENO);
    dup2(log_fd, STDERR_FILENO);

    // close the log file
    close(log_fd);
}
/*
* Usage:
int main(int argc, char *argv[]) 
{
    // redirect the log
    write_log();

    // example output
    printf("5x Bananen,\n");

    // with g_print
    g_print("500g Kirsche,\n");

    // with system()
    system("echo 'Und bitte 4 Melonen.'");

    return 0;
}
*/

