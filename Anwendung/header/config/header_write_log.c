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
    char create_log_dir[4096];
    
    // get config dir
    get_config_dir(log_dir, sizeof(log_dir));
    
    // log file with path
    snprintf(create_log_dir, sizeof(create_log_dir), "%s/log", log_dir);
    snprintf(log_file, sizeof(log_file), "%s/log/log.txt", log_dir);
    LOG_INFO("Log-file: %s", log_file);

    // create log_dir if it doesn't exist
    if (access(log_dir, F_OK) == -1) 
    {
        create_directory(create_log_dir);
    }

    // open log file or create it if it doesn't exist
    int log_fd = open(log_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (log_fd == -1) 
    {
        perror("Error when opening the log file");
        return;
    }

    // redirect STDOUT and STDERR to the log file
    if (dup2(log_fd, STDOUT_FILENO) == -1) 
    {
        perror("Failed to redirect STDOUT");
        close(log_fd);
        return;
    }
    
    if (dup2(log_fd, STDERR_FILENO) == -1) 
    {
        perror("Failed to redirect STDERR");
        close(log_fd);
        return;
    }

    // write log information
    LOG_INFO("Logging started.");

    close(log_fd); // This closes the file descriptor, but since dup2() is used, the redirection of the output is not terminated.

    LOG_INFO("Log closed.");
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

