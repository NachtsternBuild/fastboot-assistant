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
 *       Headerfile - loading_spinner		 *
 *											 *
 *-------------------------------------------*
 */
#ifndef LOADING_SPINNER_H
#define LOADING_SPINNER_H

#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <unistd.h>  
#include <sys/stat.h> 
#include <sys/types.h> 
#include <pthread.h>
#include "program_functions.h"

// global var for spinner

// function to start the spinner
void start_loading_spinner();

// function to stop the spinner
void stop_loading_spinner();

// function to create the window
GtkWidget* create_spinner_window();

// function to run spinner in another thread
void run_with_spinner(void *(*thread_function)(void *));

#endif
