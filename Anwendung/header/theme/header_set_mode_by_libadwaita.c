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
 *    Headerpart - set_mode_by_libadwaita	 *
 *											 *
 *-------------------------------------------*
 */

/* headers */
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// function to check if libadwaita are available
int check_libadwaita() 
{
    // get libadwaita bib using dlopen 
    void *handle = dlopen("libadwaita-1.so", RTLD_LAZY);
    
    if (handle) 
    {
        dlclose(handle);
        return 1;  // libadwaita are available
    } 
    
    else 
    {
        return 0;  // libadwaita aren't available
    }
}

// function that write the libadwaita status
void set_mode_by_libadwaita()
{
    LOG_INFO("set_mode_by_libadwaita");
    // check for libadwaita
    int libadwaita_available = check_libadwaita();

    if (libadwaita_available) 
    {
        LOG_INFO("libadwaita are available");
        // create the auto.txt
        write_auto_theme_file();
    } 
    
    else 
    {
        LOG_INFO("libadwaita aren't available");
    }
	
	LOG_INFO("end set_mode_by_libadwaita");
    return 0;
}

